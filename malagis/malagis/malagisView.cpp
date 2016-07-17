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
#include "_malaLines.h"
#include "_malaPolygon.h"
#include "_malaLabel.h"
#include "_malaAnalysis.h"

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
	ON_COMMAND(ID_BUTTON_LINES_INPUT, &CmalagisView::OnButtonLinesInput)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_BUTTON_LINES_SELECT, &CmalagisView::OnButtonLinesSelect)
	ON_COMMAND(ID_BUTTON_LINES_COPY, &CmalagisView::OnButtonLinesCopy)
	ON_COMMAND(ID_BUTTON_LINES_MOVE, &CmalagisView::OnButtonLinesMove)
	ON_COMMAND(ID_BUTTON_LINES_CHANGE_PRO, &CmalagisView::OnButtonLinesChangePro)
	ON_COMMAND(ID_BUTTON_LINES_CUT, &CmalagisView::OnButtonLinesCut)
	ON_COMMAND(ID_BUTTON_LINES_POINT_ADD, &CmalagisView::OnButtonLinesPointAdd)
	ON_COMMAND(ID_BUTTON_LINES_POINT_MOVE, &CmalagisView::OnButtonLinesPointMove)
	ON_COMMAND(ID_BUTTON_LINES_POINT_DELETE, &CmalagisView::OnButtonLinesPointDelete)
	ON_COMMAND(ID_BUTTON_LINES_DELETE, &CmalagisView::OnButtonLinesDelete)
	ON_COMMAND(ID_BUTTON_LINES_DELETE_ALL, &CmalagisView::OnButtonLinesDeleteAll)
	ON_COMMAND(ID_BUTTON_POLYGON_INPUT, &CmalagisView::OnButtonPolygonInput)
	ON_COMMAND(ID_BUTTON_POLYS_SELECT, &CmalagisView::OnButtonPolysSelect)
	ON_COMMAND(ID_BUTTON_POLYS_MOVE, &CmalagisView::OnButtonPolysMove)
	ON_COMMAND(ID_BUTTON_POLYS_COPY, &CmalagisView::OnButtonPolysCopy)
	ON_COMMAND(ID_BUTTON_POLYS_MODIFY, &CmalagisView::OnButtonPolysModify)
	ON_COMMAND(ID_BUTTON_POLYS_ADD_POINT, &CmalagisView::OnButtonPolysAddPoint)
	ON_COMMAND(ID_BUTTON_POLYS_MOVE_POINT, &CmalagisView::OnButtonPolysMovePoint)
	ON_COMMAND(ID_BUTTON_POLYS_DELETE_POINT, &CmalagisView::OnButtonPolysDeletePoint)
	ON_COMMAND(ID_BUTTON_POLYS_DELETE, &CmalagisView::OnButtonPolysDelete)
	ON_COMMAND(ID_BUTTON_POLYS_DELETE_ALL, &CmalagisView::OnButtonPolysDeleteAll)
	ON_COMMAND(ID_BUTTON_LABEL_INPUT, &CmalagisView::OnButtonLabelInput)
	ON_COMMAND(ID_BUTTON_LABEL_SELECT, &CmalagisView::OnButtonLabelSelect)
	ON_COMMAND(ID_BUTTON_LABEL_MOVE, &CmalagisView::OnButtonLabelMove)
	ON_COMMAND(ID_BUTTON_LABEL_COPY, &CmalagisView::OnButtonLabelCopy)
	ON_COMMAND(ID_BUTTON_LABEL_MODIFY, &CmalagisView::OnButtonLabelModify)
	ON_COMMAND(ID_BUTTON_LABEL_DELETE, &CmalagisView::OnButtonLabelDelete)
	ON_COMMAND(ID_BUTTON_LABEL_DELETE_ALL, &CmalagisView::OnButtonLabelDeleteAll)
	ON_COMMAND(ID_BUTTON_TOPO_SELECT_POINT, &CmalagisView::OnButtonTopoSelectPoint)
	ON_COMMAND(ID_BUTTON_TOPO_SELECT_LINE, &CmalagisView::OnButtonTopoSelectLine)
	ON_COMMAND(ID_BUTTON_TOPO_SELECT_POLY, &CmalagisView::OnButtonTopoSelectPoly)
	ON_COMMAND(ID_BUTTON_LINE_ORI_DIS, &CmalagisView::OnButtonLineOriDis)
	ON_COMMAND(ID_BUTTON_LINE_DIS_DIY, &CmalagisView::OnButtonLineDisDiy)
	ON_COMMAND(ID_BUTTON_POLYGON_MEASURE, &CmalagisView::OnButtonPolygonMeasure)
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
	hAccel = ::LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_RIBBON));
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
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
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
			//重绘线文件
			if (mNode[i].fileType == L"mle")
			{
				//先获取可视范围所有的线
				CLineIO lio;
				vector<malaLineFile>allLines;
				lio.getAllLines(mScreen, allLines, mNode[i].filePath);
				//再依次画区
				malaCDC dc(this, mScreen);
				for (size_t j = 0; j < allLines.size();j++)
				{
					dc.lineDrawAll(allLines[j].mLine,allLines[j].mLinePro);
				}
				if (allLines.size())
					allLines.clear();
			}
			//重绘区文件
			if (mNode[i].fileType == L"mpn")
			{
				//先获取可视范围所有的线
				CPolyIO lio;
				vector<malaPolyFile>allPolys;
				lio.getAllPolys(mScreen, allPolys, mNode[i].filePath);
				//再依次画区
				malaCDC dc(this, mScreen);
				for (size_t j = 0; j < allPolys.size(); j++)
				{
					dc.polyDrawAuto(allPolys[j].mPoly, allPolys[j].mPolyPro);
				}
				if (allPolys.size())
					allPolys.clear();
			}
			//重绘注释文件
			if (mNode[i].fileType == L"mll")
			{
				//先获取可视范围所有的注释
				CLabelIO lio;
				vector<malaLabelFile>allLabels;
				lio.getAllLabel(mScreen, allLabels, mNode[i].filePath);
				//再依次画
				malaCDC dc(this, mScreen);
				for (size_t j = 0; j < allLabels.size(); j++)
				{
					dc.textDraw(allLabels[j].mLabel, allLabels[j].mLabelPro);
				}
				if (allLabels.size())
					allLabels.clear();
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

/*
* 快捷键响应
*/
BOOL CmalagisView::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (::TranslateAccelerator(GetSafeHwnd(), hAccel, pMsg))
		return true;
	return CView::PreTranslateMessage(pMsg);
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

void CmalagisView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	malaPoint tmpPoint;
	ScreenToCoord(point.x, point.y, mScreen, &tmpPoint.x, &tmpPoint.y);
	if (mBaseOper)
	{
		mBaseOper->RButtonDown(nFlags, tmpPoint);
	}
	CView::OnRButtonDown(nFlags, point);
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
	clearActionStr();
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
	if (getActiveFile(L"mpt") != L"")
	{
		clearActionStr();
		setActionStr(L"删除所有点");
		if (MessageBox(L"删除后将无法恢复，确定删除所有的点吗?", L"警告", MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			CPointIO pio;
			pio.pointDeleteAll(getActiveFile(L"mpt"));
			this->Invalidate(TRUE);
		}
	}
	else
		MessageBox(L"没有找到点文件,请新建或激活已有的点文件！", L"提示", MB_OK | MB_ICONASTERISK);
}


/*
* 输入线
*/
void CmalagisView::OnButtonLinesInput()
{
	// TODO:  在此添加命令处理程序代码
	if (getActiveFile(L"mle") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaLinesInput(this, &mScreen, getActiveFile(L"mle"));
		setActionStr(L"输入线");
	}
	else
		MessageBox(L"没有找到线文件,请新建或激活已有的线文件！", L"提示", MB_OK | MB_ICONASTERISK);

}

/*
* 选择线
*/
void CmalagisView::OnButtonLinesSelect()
{
	// TODO:  在此添加命令处理程序代码
	if (getActiveFile(L"mle") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaLinesSelect(this, &mScreen, getActiveFile(L"mle"));
		setActionStr(L"选择线");
	}
	else
		MessageBox(L"没有找到线文件,请新建或激活已有的线文件！", L"提示", MB_OK | MB_ICONASTERISK);
}

/*
* 移动线
*/
void CmalagisView::OnButtonLinesMove()
{
	// TODO:  在此添加命令处理程序代码
	if (getActiveFile(L"mle") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaLinesMove(this, &mScreen, getActiveFile(L"mle"));
		setActionStr(L"移动线");
	}
	else
		MessageBox(L"没有找到线文件,请新建或激活已有的线文件！", L"提示", MB_OK | MB_ICONASTERISK);
}

/*
* 复制线
*/
void CmalagisView::OnButtonLinesCopy()
{
	// TODO:  在此添加命令处理程序代码
	if (getActiveFile(L"mle") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaLinesCopy(this, &mScreen, getActiveFile(L"mle"));
		setActionStr(L"复制线");
	}
	else
		MessageBox(L"没有找到线文件,请新建或激活已有的线文件！", L"提示", MB_OK | MB_ICONASTERISK);
}

/*
* 修改线属性
*/
void CmalagisView::OnButtonLinesChangePro()
{
	// TODO:  在此添加命令处理程序代码
	if (getActiveFile(L"mle") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaLinesModify(this, &mScreen, getActiveFile(L"mle"));
		setActionStr(L"修改线属性");
	}
	else
		MessageBox(L"没有找到线文件,请新建或激活已有的线文件！", L"提示", MB_OK | MB_ICONASTERISK);
}

/*
* 剪断线
*/
void CmalagisView::OnButtonLinesCut()
{
	// TODO:  在此添加命令处理程序代码
	if (getActiveFile(L"mle") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaLinesCut(this, &mScreen, getActiveFile(L"mle"));
		setActionStr(L"剪断线");
	}
	else
		MessageBox(L"没有找到线文件,请新建或激活已有的线文件！", L"提示", MB_OK | MB_ICONASTERISK);
}

/*
* 线上加点
*/
void CmalagisView::OnButtonLinesPointAdd()
{
	// TODO:  在此添加命令处理程序代码
	if (getActiveFile(L"mle") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaLinesAddPoint(this, &mScreen, getActiveFile(L"mle"));
		setActionStr(L"线上加点");
	}
	else
		MessageBox(L"没有找到线文件,请新建或激活已有的线文件！", L"提示", MB_OK | MB_ICONASTERISK);
}

/*
* 线上移点
*/
void CmalagisView::OnButtonLinesPointMove()
{
	// TODO:  在此添加命令处理程序代码
	if (getActiveFile(L"mle") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaLinesMovePoint(this, &mScreen, getActiveFile(L"mle"));
		setActionStr(L"线上移点");
	}
	else
		MessageBox(L"没有找到线文件,请新建或激活已有的线文件！", L"提示", MB_OK | MB_ICONASTERISK);
}

/*
* 线上删点
*/
void CmalagisView::OnButtonLinesPointDelete()
{
	// TODO:  在此添加命令处理程序代码
	if (getActiveFile(L"mle") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaLinesDeletePoint(this, &mScreen, getActiveFile(L"mle"));
		setActionStr(L"线上删点");
	}
	else
		MessageBox(L"没有找到线文件,请新建或激活已有的线文件！", L"提示", MB_OK | MB_ICONASTERISK);
}

/*
* 删除一条线
*/
void CmalagisView::OnButtonLinesDelete()
{
	// TODO:  在此添加命令处理程序代码
	if (getActiveFile(L"mle") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaLinesDelete(this, &mScreen, getActiveFile(L"mle"));
		setActionStr(L"删除线");
	}
	else
		MessageBox(L"没有找到线文件,请新建或激活已有的线文件！", L"提示", MB_OK | MB_ICONASTERISK);
}

/*
* 删除所有线
*/
void CmalagisView::OnButtonLinesDeleteAll()
{
	// TODO:  在此添加命令处理程序代码
	if (getActiveFile(L"mle") != L"")
	{
		clearActionStr();
		setActionStr(L"删除所有线");
		if (MessageBox(L"删除后将无法恢复，确定删除所有的线吗?", L"警告", MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			CLineIO lio;
			lio.lineDeleteAll(getActiveFile(L"mle"));
			this->Invalidate(TRUE);
		}
	}
	else
		MessageBox(L"没有找到线文件,请新建或激活已有的线文件！", L"提示", MB_OK | MB_ICONASTERISK);
}

/*
* 输入区
*/
void CmalagisView::OnButtonPolygonInput()
{
	// TODO:  在此添加命令处理程序代码
	if (getActiveFile(L"mpn") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaPolysInput(this, &mScreen, getActiveFile(L"mpn"));
		setActionStr(L"输入区");
	}
	else
		MessageBox(L"没有找到区文件,请新建或激活已有的区文件！", L"提示", MB_OK | MB_ICONASTERISK);
}

/*
* 选择区
*/
void CmalagisView::OnButtonPolysSelect()
{
	// TODO:  在此添加命令处理程序代码
	if (getActiveFile(L"mpn") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaPolysSelect(this, &mScreen, getActiveFile(L"mpn"));
		setActionStr(L"选择区");
	}
	else
		MessageBox(L"没有找到区文件,请新建或激活已有的区文件！", L"提示", MB_OK | MB_ICONASTERISK);
}

/*
* 移动区
*/
void CmalagisView::OnButtonPolysMove()
{
	// TODO:  在此添加命令处理程序代码
	if (getActiveFile(L"mpn") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaPolysMove(this, &mScreen, getActiveFile(L"mpn"));
		setActionStr(L"移动区");
	}
	else
		MessageBox(L"没有找到区文件,请新建或激活已有的区文件！", L"提示", MB_OK | MB_ICONASTERISK);
}

/*
* 复制区
*/
void CmalagisView::OnButtonPolysCopy()
{
	// TODO:  在此添加命令处理程序代码
	if (getActiveFile(L"mpn") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaPolysCopy(this, &mScreen, getActiveFile(L"mpn"));
		setActionStr(L"复制区");
	}
	else
		MessageBox(L"没有找到区文件,请新建或激活已有的区文件！", L"提示", MB_OK | MB_ICONASTERISK);
}

/*
* 修改区属性
*/
void CmalagisView::OnButtonPolysModify()
{
	// TODO:  在此添加命令处理程序代码
	if (getActiveFile(L"mpn") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaPolysModify(this, &mScreen, getActiveFile(L"mpn"));
		setActionStr(L"修改区属性");
	}
	else
		MessageBox(L"没有找到区文件,请新建或激活已有的区文件！", L"提示", MB_OK | MB_ICONASTERISK);
}

/*
* 边界加点
*/
void CmalagisView::OnButtonPolysAddPoint()
{
	// TODO:  在此添加命令处理程序代码
	if (getActiveFile(L"mpn") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaPolysAddPoint(this, &mScreen, getActiveFile(L"mpn"));
		setActionStr(L"边界加点");
	}
	else
		MessageBox(L"没有找到区文件,请新建或激活已有的区文件！", L"提示", MB_OK | MB_ICONASTERISK);
}

/*
* 边界移点
*/
void CmalagisView::OnButtonPolysMovePoint()
{
	// TODO:  在此添加命令处理程序代码
	if (getActiveFile(L"mpn") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaPolysMovePoint(this, &mScreen, getActiveFile(L"mpn"));
		setActionStr(L"边界移点");
	}
	else
		MessageBox(L"没有找到区文件,请新建或激活已有的区文件！", L"提示", MB_OK | MB_ICONASTERISK);
}

/*
* 边界删点
*/
void CmalagisView::OnButtonPolysDeletePoint()
{
	// TODO:  在此添加命令处理程序代码
	if (getActiveFile(L"mpn") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaPolysDeletePoint(this, &mScreen, getActiveFile(L"mpn"));
		setActionStr(L"边界删点");
	}
	else
		MessageBox(L"没有找到区文件,请新建或激活已有的区文件！", L"提示", MB_OK | MB_ICONASTERISK);
}

/*
* 删除区
*/
void CmalagisView::OnButtonPolysDelete()
{
	// TODO:  在此添加命令处理程序代码
	if (getActiveFile(L"mpn") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaPolysDelete(this, &mScreen, getActiveFile(L"mpn"));
		setActionStr(L"删除区");
	}
	else
		MessageBox(L"没有找到区文件,请新建或激活已有的区文件！", L"提示", MB_OK | MB_ICONASTERISK);
}

/*
* 删除所有区
*/
void CmalagisView::OnButtonPolysDeleteAll()
{
	// TODO:  在此添加命令处理程序代码
	if (getActiveFile(L"mpn") != L"")
	{
		clearActionStr();
		setActionStr(L"删除所有区");
		if (MessageBox(L"删除后将无法恢复，确定删除所有的区吗?", L"警告", MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			CPolyIO lio;
			lio.polyDeleteAll(getActiveFile(L"mpn"));
			this->Invalidate(TRUE);
		}
	}
	else
		MessageBox(L"没有找到区文件,请新建或激活已有的区文件！", L"提示", MB_OK | MB_ICONASTERISK);
}

/*
* 输入注释
*/
void CmalagisView::OnButtonLabelInput()
{
	// TODO:  在此添加命令处理程序代码
	if (getActiveFile(L"mll") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaLabelsInput(this, &mScreen, getActiveFile(L"mll"));
		setActionStr(L"输入注释");
	}
	else
		MessageBox(L"没有找到注释文件,请新建或激活已有的注释文件！", L"提示", MB_OK | MB_ICONASTERISK);
}

/*
* 选择注释
*/
void CmalagisView::OnButtonLabelSelect()
{
	// TODO:  在此添加命令处理程序代码
	if (getActiveFile(L"mll") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaLabelsSelect(this, &mScreen, getActiveFile(L"mll"));
		setActionStr(L"选择注释");
	}
	else
		MessageBox(L"没有找到注释文件,请新建或激活已有的注释文件！", L"提示", MB_OK | MB_ICONASTERISK);
}

/*
* 移动注释
*/
void CmalagisView::OnButtonLabelMove()
{
	// TODO:  在此添加命令处理程序代码
	if (getActiveFile(L"mll") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaLabelsMove(this, &mScreen, getActiveFile(L"mll"));
		setActionStr(L"移动注释");
	}
	else
		MessageBox(L"没有找到注释文件,请新建或激活已有的注释文件！", L"提示", MB_OK | MB_ICONASTERISK);
}

/*
* 复制注释
*/
void CmalagisView::OnButtonLabelCopy()
{
	// TODO:  在此添加命令处理程序代码
	if (getActiveFile(L"mll") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaLabelsCopy(this, &mScreen, getActiveFile(L"mll"));
		setActionStr(L"复制注释");
	}
	else
		MessageBox(L"没有找到注释文件,请新建或激活已有的注释文件！", L"提示", MB_OK | MB_ICONASTERISK);
}

/*
* 修改注释属性
*/
void CmalagisView::OnButtonLabelModify()
{
	// TODO:  在此添加命令处理程序代码
	if (getActiveFile(L"mll") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaLabelsModify(this, &mScreen, getActiveFile(L"mll"));
		setActionStr(L"修改注释属性");
	}
	else
		MessageBox(L"没有找到注释文件,请新建或激活已有的注释文件！", L"提示", MB_OK | MB_ICONASTERISK);
}

/*
* 删除注释
*/
void CmalagisView::OnButtonLabelDelete()
{
	// TODO:  在此添加命令处理程序代码
	if (getActiveFile(L"mll") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaLabelsDelete(this, &mScreen, getActiveFile(L"mll"));
		setActionStr(L"删除注释");
	}
	else
		MessageBox(L"没有找到注释文件,请新建或激活已有的注释文件！", L"提示", MB_OK | MB_ICONASTERISK);
}

/*
* 删除所有注释
*/
void CmalagisView::OnButtonLabelDeleteAll()
{
	// TODO:  在此添加命令处理程序代码
	if (getActiveFile(L"mll") != L"")
	{
		clearActionStr();
		setActionStr(L"删除所有注释");
		if (MessageBox(L"删除后将无法恢复，确定删除所有的注释吗?", L"警告", MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			CLabelIO lio;
			lio.labelDeleteAll(getActiveFile(L"mll"));
			this->Invalidate(TRUE);
		}
	}
	else
		MessageBox(L"没有找到区文件,请新建或激活已有的区文件！", L"提示", MB_OK | MB_ICONASTERISK);
}

/*
* 拓扑选点
*/
void CmalagisView::OnButtonTopoSelectPoint()
{
	// TODO:  在此添加命令处理程序代码
	if (getActiveFile(L"mpt") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaTopo(this, &mScreen, getActiveFile(L"mpt"),1);
		setActionStr(L"拓扑选点");
	}
	else
		MessageBox(L"没有找到点文件,请新建或激活已有的点文件！", L"提示", MB_OK | MB_ICONASTERISK);
}

/*
* 拓扑选线
*/
void CmalagisView::OnButtonTopoSelectLine()
{
	// TODO:  在此添加命令处理程序代码
	if (getActiveFile(L"mle") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaTopo(this, &mScreen, getActiveFile(L"mle"), 2);
		setActionStr(L"拓扑选线");
	}
	else
		MessageBox(L"没有找到线文件,请新建或激活已有的线文件！", L"提示", MB_OK | MB_ICONASTERISK);
}

/*
* 拓扑选区
*/
void CmalagisView::OnButtonTopoSelectPoly()
{
	// TODO:  在此添加命令处理程序代码
	if (getActiveFile(L"mpn") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaTopo(this, &mScreen, getActiveFile(L"mpn"), 3);
		setActionStr(L"拓扑选区");
	}
	else
		MessageBox(L"没有找到区文件,请新建或激活已有的区文件！", L"提示", MB_OK | MB_ICONASTERISK);
}

/*
* 已知线段量算
*/
void CmalagisView::OnButtonLineOriDis()
{
	// TODO:  在此添加命令处理程序代码
	if (getActiveFile(L"mle") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaLineMeasure(this, &mScreen, getActiveFile(L"mle"));
		setActionStr(L"线段量算");
	}
	else
		MessageBox(L"没有找到线文件,请新建或激活已有的线文件！", L"提示", MB_OK | MB_ICONASTERISK);
}

/*
* 自定义量算
*/
void CmalagisView::OnButtonLineDisDiy()
{
	// TODO:  在此添加命令处理程序代码
	clearActionStr();
	mBaseOper = new CmalaLineMeasureCustom(this, &mScreen);
	setActionStr(L"自定义量算");
}


void CmalagisView::OnButtonPolygonMeasure()
{
	// TODO:  在此添加命令处理程序代码
	if (getActiveFile(L"mpn") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaPolyMeasure(this, &mScreen, getActiveFile(L"mpn"));
		setActionStr(L"区量算");
	}
	else
		MessageBox(L"没有找到区文件,请新建或激活已有的区文件！", L"提示", MB_OK | MB_ICONASTERISK);
}
