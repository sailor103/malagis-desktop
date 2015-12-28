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
					switch (allPoints[j].m_pointpro.pointStyle)
					{
					case 0:
						dc.pointDrawRect(allPoints[j].m_point, allPoints[j].m_pointpro);
						break;
					case 1:
						dc.pointDrawTriangle(allPoints[j].m_point, allPoints[j].m_pointpro);
						break;
					case 2:
						dc.pointDrawCircle(allPoints[j].m_point, allPoints[j].m_pointpro);
						break;
					default:
						break;
					}
				}
				if (allPoints.size())
					allPoints.clear();
			}
		}
	}
}

void CmalagisView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
		
	malaPoint tmpPoint;
	ScreenToCoord(point.x, point.y, mScreen, &tmpPoint.x, &tmpPoint.y);
	if (mBaseOper)
	{
		mBaseOper->LButtonDown(nFlags, tmpPoint);
	}
	
	CView::OnLButtonDown(nFlags, point);
}

void CmalagisView::OnButtonPointsInput()
{
	// TODO:  在此添加命令处理程序代码
	if (getActiveFile(L"mpt")!=L"")
		mBaseOper = new CmalaPointsInput(this, &mScreen, getActiveFile(L"mpt"));
	else
		MessageBox(L"没有找到点文件,请新建或激活已有的点文件！", L"提示", MB_OK | MB_ICONASTERISK);

}


void CmalagisView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	mScreen.hScreen = cy;//Client窗口高度
	mScreen.wScreen = cx;//Client窗口宽度
}


void CmalagisView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
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

	CView::OnMouseMove(nFlags, point);
}
