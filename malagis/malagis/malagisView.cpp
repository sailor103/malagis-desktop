// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。  
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。  
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://go.microsoft.com/fwlink/?LinkId=238214。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// malagisView.cpp : CmalagisView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "malagis.h"
#endif

#include "malagisDoc.h"
#include "malagisView.h"
#include "MainFrm.h"

//自定义头文件
#include "_malaPoints.h"
#include "_malaTools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmalagisView

IMPLEMENT_DYNCREATE(CmalagisView, CView)

BEGIN_MESSAGE_MAP(CmalagisView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CmalagisView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BUTTON_POINTS_INPUT, &CmalagisView::OnButtonPointsInput)
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_BUTTON_ZOOM_IN, &CmalagisView::OnButtonZoomIn)
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_BUTTON_ZOOM_RESET, &CmalagisView::OnButtonZoomReset)
	ON_COMMAND(ID_BUTTON_ZOOMOUT, &CmalagisView::OnButtonZoomout)
	ON_COMMAND(ID_BUTTON_ZOOM_MOVE, &CmalagisView::OnButtonZoomMove)
	ON_COMMAND(ID_BUTTON_ZOOM_REFRESH, &CmalagisView::OnButtonZoomRefresh)
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_BUTTON_POINTS_SELECT, &CmalagisView::OnButtonPointsSelect)
	ON_COMMAND(ID_BUTTON_POINTS_MOVE, &CmalagisView::OnButtonPointsMove)
	ON_COMMAND(ID_BUTTON_POINTS_COPY, &CmalagisView::OnButtonPointsCopy)
	ON_COMMAND(ID_BUTTON_POINTS_CHANGE_PRO, &CmalagisView::OnButtonPointsChangePro)
	ON_COMMAND(ID_BUTTON_POINTS_DELETE, &CmalagisView::OnButtonPointsDelete)
	ON_COMMAND(ID_BUTTON_POINTS_DELETE_ALL, &CmalagisView::OnButtonPointsDeleteAll)
END_MESSAGE_MAP()

// CmalagisView 构造/析构

CmalagisView::CmalagisView()
{
	// TODO:  在此处添加构造代码
	mBaseOper = NULL;
	//屏幕坐标初始化
	mScreen.lbx = 0.0;
	mScreen.lby = 0.0;
	mScreen.scale = 1.0;
	mouseCursor = 0;
	
}

CmalagisView::~CmalagisView()
{
}

BOOL CmalagisView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CmalagisView 绘制

void CmalagisView::OnDraw(CDC* /*pDC*/)
{
	CmalagisDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
	displayAllGraphs();
}


// CmalagisView 打印


void CmalagisView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CmalagisView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CmalagisView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CmalagisView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}

void CmalagisView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CmalagisView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CmalagisView 诊断

#ifdef _DEBUG
void CmalagisView::AssertValid() const
{
	CView::AssertValid();
}

void CmalagisView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CmalagisDoc* CmalagisView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CmalagisDoc)));
	return (CmalagisDoc*)m_pDocument;
}
#endif //_DEBUG

// CmalagisView 消息处理程序

//获取目录树
void CmalagisView::upadteTree()
{
	mNode.clear();
	CMainFrame *pMainFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	if (pMainFrame)
	{
		mNode = pMainFrame->m_wndPrjManage.fileNodeTree;
	}
	
}

//获取当前激活的文件
CString CmalagisView::getActiveFile(CString fileType)
{
	upadteTree();
	for (size_t i = 0; i < mNode.size(); i++)
	{
		if (mNode[i].fileType == fileType&&mNode[i].isActive == true)
			return mNode[i].filePath;
	}
	return L"";
}

//重绘函数
void CmalagisView::displayAllGraphs()
{
	upadteTree();
	for (size_t i = 0; i < mNode.size(); i++)
	{
		if (mNode[i].isOpen == true)
		{
			//重绘点文件
			if (mNode[i].fileType==L"mpt")
			{
				//先获取所有符合条件的点
				CPointIO pio;
				vector<malaPointFile>allPoints;
				pio.getAllPoint(mScreen, allPoints,mNode[i].filePath);
				//再依次画点
				malaCDC dc(this,mScreen);
				for (size_t j = 0; j < allPoints.size();j++)
				{
					dc.pointDrawAuto(allPoints[j].m_point, allPoints[j].m_pointpro);
				}
				if (allPoints.size())
					allPoints.clear();
			}
		}
	}
}

//设置当前操作字符串
void CmalagisView::setActionStr(CString str)
{
	//View中获取MainFrame指针
	CMainFrame *pMainFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	//获取状态栏指针
	CMFCRibbonStatusBar *statusBar = (CMFCRibbonStatusBar *)pMainFrame->GetDescendantWindow(AFX_IDW_STATUS_BAR);
	
	statusBar->GetElement(5)->SetText(str);
	statusBar->GetElement(5)->Redraw();
}

//清除当前操作
void CmalagisView::clearActionStr()
{
	setActionStr(L"浏览地图");
	mouseCursor = 0;
	if (mBaseOper)
		mBaseOper = NULL;
}

//设置当前鼠标指针
void CmalagisView::setCurrentCursor()
{
	if (mouseCursor == 1)
	{
		HCURSOR hCursor = AfxGetApp()->LoadCursor(IDC_CURSOR_ZOOMIN);
		SetCursor(hCursor);
	}
	if (mouseCursor == 2)
	{
		HCURSOR hCursor = AfxGetApp()->LoadCursor(IDC_CURSOR_ZOOMOUT);
		SetCursor(hCursor);
	}
	if (mouseCursor == 3)
	{
		HCURSOR hCursor = AfxGetApp()->LoadCursor(IDC_CURSOR_HAND);
		SetCursor(hCursor);
	}
}

void CmalagisView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	setCurrentCursor();
	malaPoint tmpPoint;
	ScreenToCoord(point.x, point.y, mScreen, &tmpPoint.x, &tmpPoint.y);
	if (mBaseOper)
	{
		mBaseOper->LButtonDown(nFlags, tmpPoint);
	}
	
	CView::OnLButtonDown(nFlags, point);
}


void CmalagisView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	setCurrentCursor();
	/*
	* 实时显示坐标
	*/
	//View中获取MainFrame指针
	CMainFrame *pMainFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	//获取状态栏指针
	CMFCRibbonStatusBar *statusBar = (CMFCRibbonStatusBar *)pMainFrame->GetDescendantWindow(AFX_IDW_STATUS_BAR);
	//更改坐标
	malaPoint MyPoint;
	ScreenToCoord(point.x, point.y, mScreen, &MyPoint.x, &MyPoint.y);
	CString str;
	str.Format(_T("X=%f,Y=%f"), MyPoint.x, MyPoint.y);
	statusBar->GetElement(2)->SetText(str);
	statusBar->GetElement(2)->Redraw();

	malaPoint tmpPoint;
	ScreenToCoord(point.x, point.y, mScreen, &tmpPoint.x, &tmpPoint.y);
	if (mBaseOper)
	{
		mBaseOper->MouseMove(nFlags, tmpPoint);
	}

	CView::OnMouseMove(nFlags, point);
}

void CmalagisView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	setCurrentCursor();
	malaPoint tmpPoint;
	ScreenToCoord(point.x, point.y, mScreen, &tmpPoint.x, &tmpPoint.y);
	if (mBaseOper)
	{
		mBaseOper->LButtonUp(nFlags, tmpPoint);
	}

	CView::OnLButtonUp(nFlags, point);
}

BOOL CmalagisView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	malaZoom tpZoom(this, &mScreen);
	malaPoint tmpPoint;
	ScreenToCoord(pt.x, pt.y, mScreen, &tmpPoint.x, &tmpPoint.y);
	tpZoom.MouseWheel(nFlags, zDelta, tmpPoint);
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CmalagisView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	mScreen.hScreen = cy;//Client窗口高度
	mScreen.wScreen = cx;//Client窗口宽度
}

/*
* 放大地图
*/
void CmalagisView::OnButtonZoomIn()
{
	// TODO:  在此添加命令处理程序代码
	clearActionStr();
	setActionStr(L"放大地图");
	mBaseOper = new malaZoonIn(this,&mScreen);
	mouseCursor = 1;
}

/*
* 重置地图
*/
void CmalagisView::OnButtonZoomReset()
{
	// TODO:  在此添加命令处理程序代码
	clearActionStr();
	setActionStr(L"浏览地图");
	mScreen.lbx = 0;
	mScreen.lby = 0;
	mScreen.scale = 1;
	displayAllGraphs();
	Invalidate(TRUE);
}

/*
* 缩小地图
*/
void CmalagisView::OnButtonZoomout()
{
	// TODO:  在此添加命令处理程序代码
	clearActionStr();
	setActionStr(L"缩小地图");
	mBaseOper = new malaZoonOut(this, &mScreen);
	mouseCursor = 2;
}

/*
* 移动地图
*/
void CmalagisView::OnButtonZoomMove()
{
	// TODO:  在此添加命令处理程序代码
	clearActionStr();
	setActionStr(L"移动地图");
	mBaseOper = new malaMoveMap(this, &mScreen);
	mouseCursor = 3;
}

/*
* 刷新地图
*/
void CmalagisView::OnButtonZoomRefresh()
{
	// TODO:  在此添加命令处理程序代码
	Invalidate(TRUE);
}

/*
* 输入点
*/
void CmalagisView::OnButtonPointsInput()
{
	// TODO:  在此添加命令处理程序代码
	if (getActiveFile(L"mpt") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaPointsInput(this, &mScreen, getActiveFile(L"mpt"));
		setActionStr(L"输入点");
	}
	else
		MessageBox(L"没有找到点文件,请新建或激活已有的点文件！", L"提示", MB_OK | MB_ICONASTERISK);

}

/*
* 选择点
*/
void CmalagisView::OnButtonPointsSelect()
{
	// TODO:  在此添加命令处理程序代码
	if (getActiveFile(L"mpt") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaPointsSelect(this, &mScreen, getActiveFile(L"mpt"));
		setActionStr(L"选择点");
	}
	else
		MessageBox(L"没有找到点文件,请新建或激活已有的点文件！", L"提示", MB_OK | MB_ICONASTERISK);
}

/*
* 移动点
*/
void CmalagisView::OnButtonPointsMove()
{
	// TODO:  在此添加命令处理程序代码
	if (getActiveFile(L"mpt") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaPointsMove(this, &mScreen, getActiveFile(L"mpt"));
		setActionStr(L"移动点");
	}
	else
		MessageBox(L"没有找到点文件,请新建或激活已有的点文件！", L"提示", MB_OK | MB_ICONASTERISK);
}

/*
* 复制点
*/
void CmalagisView::OnButtonPointsCopy()
{
	// TODO:  在此添加命令处理程序代码
	if (getActiveFile(L"mpt") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaPointsCopy(this, &mScreen, getActiveFile(L"mpt"));
		setActionStr(L"复制点");
	}
	else
		MessageBox(L"没有找到点文件,请新建或激活已有的点文件！", L"提示", MB_OK | MB_ICONASTERISK);
}

/*
* 修改点属性
*/
void CmalagisView::OnButtonPointsChangePro()
{
	// TODO:  在此添加命令处理程序代码
	if (getActiveFile(L"mpt") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaPointsModify(this, &mScreen, getActiveFile(L"mpt"));
		setActionStr(L"修改点参数");
	}
	else
		MessageBox(L"没有找到点文件,请新建或激活已有的点文件！", L"提示", MB_OK | MB_ICONASTERISK);
}

/*
* 删除点
*/
void CmalagisView::OnButtonPointsDelete()
{
	// TODO:  在此添加命令处理程序代码
	if (getActiveFile(L"mpt") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaPointsDelete(this, &mScreen, getActiveFile(L"mpt"));
		setActionStr(L"删除点");
	}
	else
		MessageBox(L"没有找到点文件,请新建或激活已有的点文件！", L"提示", MB_OK | MB_ICONASTERISK);
}

/*
* 删除所有点
*/
void CmalagisView::OnButtonPointsDeleteAll()
{
	// TODO:  在此添加命令处理程序代码
}
