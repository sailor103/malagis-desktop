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

#include "stdafx.h"
#include "mainfrm.h"
#include "PrjManage.h"
#include "Resource.h"
#include "malagis.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileView

CPrjManage::CPrjManage()
{
}

CPrjManage::~CPrjManage()
{
}

BEGIN_MESSAGE_MAP(CPrjManage, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_PROPERTIES, OnProperties)
	ON_COMMAND(ID_OPEN, OnFileOpen)
	ON_COMMAND(ID_OPEN_WITH, OnFileOpenWith)
	ON_COMMAND(ID_DUMMY_COMPILE, OnDummyCompile)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar 消息处理程序

int CPrjManage::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 创建视图: 
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE  | TVS_LINESATROOT | TVS_HASBUTTONS;

	if (!m_wndPrjView.Create(dwViewStyle, rectDummy, this, 4))
	{
		TRACE0("未能创建文件视图\n");
		return -1;      // 未能创建
	}

	// 加载视图图像: 
	m_PrjViewImages.Create(IDB_FILE_VIEW, 16, 0, RGB(255, 0, 255));
	m_wndPrjView.SetImageList(&m_PrjViewImages, TVSIL_NORMAL);

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EXPLORER);
	//m_wndToolBar.LoadToolBar(IDR_EXPLORER, 0, 0, TRUE /* 已锁定*/);

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// 所有命令将通过此控件路由，而不是通过主框架路由: 
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	// 填入一些静态树视图数据(此处只需填入虚拟代码，而不是复杂的数据)
	FillPrjView();//默认内容
	AdjustLayout();

	return 0;
}

void CPrjManage::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CPrjManage::FillPrjView()
{
	/*HTREEITEM hRoot = m_wndPrjView.InsertItem(_T("FakeApp 文件"), 0, 0);
	m_wndPrjView.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);

	HTREEITEM hSrc = m_wndPrjView.InsertItem(_T("FakeApp 源文件"), 0, 1, hRoot);

	m_wndPrjView.InsertItem(_T("FakeApp.cpp"), 1, 1, hSrc);
	m_wndPrjView.InsertItem(_T("FakeApp.rc"), 1, 1, hSrc);
	m_wndPrjView.InsertItem(_T("FakeAppDoc.cpp"), 1, 1, hSrc);
	m_wndPrjView.InsertItem(_T("FakeAppView.cpp"), 1, 1, hSrc);
	m_wndPrjView.InsertItem(_T("MainFrm.cpp"), 1, 1, hSrc);
	m_wndPrjView.InsertItem(_T("StdAfx.cpp"), 1, 1, hSrc);

	HTREEITEM hInc = m_wndPrjView.InsertItem(_T("FakeApp 头文件"), 0, 0, hRoot);

	m_wndPrjView.InsertItem(_T("FakeApp.h"), 2, 2, hInc);
	m_wndPrjView.InsertItem(_T("FakeAppDoc.h"), 2, 2, hInc);
	m_wndPrjView.InsertItem(_T("FakeAppView.h"), 2, 2, hInc);
	m_wndPrjView.InsertItem(_T("Resource.h"), 2, 2, hInc);
	m_wndPrjView.InsertItem(_T("MainFrm.h"), 2, 2, hInc);
	m_wndPrjView.InsertItem(_T("StdAfx.h"), 2, 2, hInc);

	HTREEITEM hRes = m_wndPrjView.InsertItem(_T("FakeApp 资源文件"), 0, 0, hRoot);

	m_wndPrjView.InsertItem(_T("FakeApp.ico"), 2, 2, hRes);
	m_wndPrjView.InsertItem(_T("FakeApp.rc2"), 2, 2, hRes);
	m_wndPrjView.InsertItem(_T("FakeAppDoc.ico"), 2, 2, hRes);
	m_wndPrjView.InsertItem(_T("FakeToolbar.bmp"), 2, 2, hRes);

	m_wndPrjView.Expand(hRoot, TVE_EXPAND);
	m_wndPrjView.Expand(hSrc, TVE_EXPAND);
	m_wndPrjView.Expand(hInc, TVE_EXPAND);*/

	HTREEITEM prjRoot = m_wndPrjView.InsertItem(_T("空工程"), 0, 0);
	HTREEITEM prjPoint = m_wndPrjView.InsertItem(_T("点文件"), 0, 0, prjRoot);
	HTREEITEM prjPointFile = m_wndPrjView.InsertItem(_T("sfsdfds文件"), 0, 0, prjPoint);
	HTREEITEM prjLine = m_wndPrjView.InsertItem(_T("线文件"), 0, 0, prjRoot);
	HTREEITEM prjPoly = m_wndPrjView.InsertItem(_T("区文件"), 0, 0, prjRoot);
	HTREEITEM prjLabel = m_wndPrjView.InsertItem(_T("注释文件"), 0, 0, prjRoot);

	
	//m_wndPrjView.Expand(hSrc, TVE_EXPAND);
	//m_wndPrjView.Expand(prjRoot, TVE_EXPAND);

}

void CPrjManage::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndPrjView;
	ASSERT_VALID(pWndTree);

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}
	HTREEITEM selTreeItem=NULL;
	if (point != CPoint(-1, -1))
	{
		// 选择已单击的项: 
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			pWndTree->SelectItem(hTreeItem);
			selTreeItem = hTreeItem;
		}
	}

	pWndTree->SetFocus();
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EXPLORER, point.x, point.y, this, TRUE);
	
	/*
	* 加载自定义的右键菜单
	*/
	CMenu menu;
	CString str = m_wndPrjView.GetItemText(selTreeItem);

	if (selTreeItem == m_wndPrjView.GetRootItem())
	{
		menu.LoadMenu(IDR_MENU_PRJ);
		//m_DelItem = hItem; 
	}
	else if (str==L"点文件")
	{
		menu.LoadMenu(IDR_MENU_PRJ_POINT);
	}
	else if (str == L"线文件")
	{
		menu.LoadMenu(IDR_MENU_PRJ_LINE);
	}
	else if (str == L"区文件")
	{
		menu.LoadMenu(IDR_MENU_PRJ_PLOY);
	}
	else if (str == L"注释文件")
	{
		menu.LoadMenu(IDR_MENU_PRJ_LABEL);
	}
	else
	{
		menu.LoadMenu(IDR_MENU_PRJ_FILE_CTRL);
	}
	
	CMenu *pPopup = menu.GetSubMenu(0);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}

void CPrjManage::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndPrjView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

void CPrjManage::OnProperties()
{
	AfxMessageBox(_T("属性??????"));

}

void CPrjManage::OnFileOpen()
{
	// TODO:  在此处添加命令处理程序代码
}

void CPrjManage::OnFileOpenWith()
{
	// TODO:  在此处添加命令处理程序代码
}

void CPrjManage::OnDummyCompile()
{
	// TODO:  在此处添加命令处理程序代码
}

void CPrjManage::OnEditCut()
{
	// TODO:  在此处添加命令处理程序代码
}

void CPrjManage::OnEditCopy()
{
	// TODO:  在此处添加命令处理程序代码
}

void CPrjManage::OnEditClear()
{
	// TODO:  在此处添加命令处理程序代码
}

void CPrjManage::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文

	CRect rectTree;
	m_wndPrjView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CPrjManage::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndPrjView.SetFocus();
}

void CPrjManage::OnChangeVisualStyle()
{
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_EXPLORER_24 : IDR_EXPLORER, 0, 0, TRUE /* 锁定*/);

	m_PrjViewImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_FILE_VIEW_24 : IDB_FILE_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("无法加载位图:  %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_PrjViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_PrjViewImages.Add(&bmp, RGB(255, 0, 255));

	m_wndPrjView.SetImageList(&m_PrjViewImages, TVSIL_NORMAL);
#if _WIN32_WINNT>= 0x0600
	SetWindowTheme(m_wndPrjView, L"Explorer", NULL);
#endif
	
}


