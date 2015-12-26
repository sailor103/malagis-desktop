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
#include "_malaDialogs.h"
#include "_malaIO.h"
#include "_malaBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileView

CPrjManage::CPrjManage()
{
	mBasePath = L"";
	selTreeItem = NULL;
	actPointItem = NULL;
	actLineItem = NULL;
	actPloyItem = NULL;
	actLabelItem = NULL;
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
	ON_COMMAND(ID_NEW_PRJ, OnNewPrj)
	ON_COMMAND(ID_OPEN_PRJ,OnOpenPrj)
	ON_COMMAND(ID_PRJ_NEW_POINTS_FILE, OnNewPoint)
	ON_COMMAND(ID_PRJ_FILE_DISPLAY, OnDisplayFile)
	ON_COMMAND(ID_PRJ_FILE_HIDE, OnHideFile)
	ON_COMMAND(ID_PRJ_FILE_ACTIVE, OnActiveFile)
	
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

	HTREEITEM prjRoot = m_wndPrjView.InsertItem(_T("----------"), 0, 0);

	
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
	//HTREEITEM selTreeItem=NULL;
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
			selTreeItem = hTreeItem;//记录下选中的ITEM
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

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_PRJ_VIEW : IDB_FILE_VIEW;

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

/*
* 新建工程
*/
void CPrjManage::OnNewPrj()
{
	CString prjPathName, prjName, prjExt;
	if (dlgNewPrj(prjPathName,prjName,prjExt))
	{
		int i = prjPathName.ReverseFind(_T('\\'));
		mBasePath = prjPathName.Left(i + 1);

		malaTree prjNode;
		prjNode.filePath = prjPathName;
		prjNode.fileType = prjExt;
		prjNode.itemnode = prjName;
		prjNode.isActive = false;
		prjNode.isOpen = true;
		//写文件
		currentPrj.setPrjPath(prjPathName);
		currentPrj.newPrj(prjNode);
		
		//清空之前的状态
		delAllChildrenItem();
		
		//创建node
		HTREEITEM hItem = m_wndPrjView.GetRootItem();
		m_wndPrjView.SetItemText(hItem, prjName);

		//更新容器
		fileNodeTree.push_back(prjNode);

	}
	else
	{
		//MessageBox(L"创建失败", L"提示", MB_ICONASTERISK);
	}
}

/*
* 打开工程
*/
void CPrjManage::OnOpenPrj()
{
	CString prjPathName;
	if (IDOK==dlgOpenPrj(prjPathName))
	{
		//基础目录
		int i = prjPathName.ReverseFind(_T('\\'));
		mBasePath = prjPathName.Left(i + 1);
		
		//清空之前的状态
		delAllChildrenItem();

		//打开工程文件
		currentPrj.setPrjPath(prjPathName);
		currentPrj.openPrj(fileNodeTree);
		//遍历Tree并更新Tree
		int nodelengh = fileNodeTree.size();
		for (int i = 0; i < nodelengh; i++)
		{
			HTREEITEM hItem = m_wndPrjView.GetRootItem();
			if (i==0)//root节点
			{
				m_wndPrjView.SetItemText(hItem, fileNodeTree[i].itemnode);
			}
			else
			{
				//点图标
				if (fileNodeTree[i].fileType == L"mpt"&&fileNodeTree[i].isOpen == true && fileNodeTree[i].isActive == true)
				{
					actPointItem = m_wndPrjView.InsertItem(fileNodeTree[i].itemnode, 4, 4, hItem);
				}
				if (fileNodeTree[i].fileType == L"mpt"&&fileNodeTree[i].isOpen == true && fileNodeTree[i].isActive == false)
				{
					m_wndPrjView.InsertItem(fileNodeTree[i].itemnode, 3, 3, hItem);
				}
				if (fileNodeTree[i].fileType == L"mpt"&&fileNodeTree[i].isOpen == false && fileNodeTree[i].isActive == false)
				{
					m_wndPrjView.InsertItem(fileNodeTree[i].itemnode, 2, 2, hItem);
				}
				//线图标
				if (fileNodeTree[i].fileType == L"mle"&&fileNodeTree[i].isOpen == true && fileNodeTree[i].isActive == true)
				{
					actLineItem = m_wndPrjView.InsertItem(fileNodeTree[i].itemnode, 7, 7, hItem);
				}
				if (fileNodeTree[i].fileType == L"mle"&&fileNodeTree[i].isOpen == true && fileNodeTree[i].isActive == false)
				{
					m_wndPrjView.InsertItem(fileNodeTree[i].itemnode, 6, 6, hItem);
				}
				if (fileNodeTree[i].fileType == L"mle"&&fileNodeTree[i].isOpen == false && fileNodeTree[i].isActive == false)
				{
					m_wndPrjView.InsertItem(fileNodeTree[i].itemnode, 5, 5, hItem);
				}
				//面图标
				if (fileNodeTree[i].fileType == L"mpn"&&fileNodeTree[i].isOpen == true && fileNodeTree[i].isActive == true)
				{
					actPloyItem = m_wndPrjView.InsertItem(fileNodeTree[i].itemnode, 10, 10, hItem);
				}
				if (fileNodeTree[i].fileType == L"mpn"&&fileNodeTree[i].isOpen == true && fileNodeTree[i].isActive == false)
				{
					m_wndPrjView.InsertItem(fileNodeTree[i].itemnode, 9, 9, hItem);
				}
				if (fileNodeTree[i].fileType == L"mpn"&&fileNodeTree[i].isOpen == false && fileNodeTree[i].isActive == false)
				{
					m_wndPrjView.InsertItem(fileNodeTree[i].itemnode, 8, 8, hItem);
				}
				//注释图标
				if (fileNodeTree[i].fileType == L"mll"&&fileNodeTree[i].isOpen == true && fileNodeTree[i].isActive == true)
				{
					actLabelItem = m_wndPrjView.InsertItem(fileNodeTree[i].itemnode, 13, 13, hItem);
				}
				if (fileNodeTree[i].fileType == L"mll"&&fileNodeTree[i].isOpen == true && fileNodeTree[i].isActive == false)
				{
					m_wndPrjView.InsertItem(fileNodeTree[i].itemnode, 12, 12, hItem);
				}
				if (fileNodeTree[i].fileType == L"mll"&&fileNodeTree[i].isOpen == false && fileNodeTree[i].isActive == false)
				{
					m_wndPrjView.InsertItem(fileNodeTree[i].itemnode, 11, 11, hItem);
				}
			}
		}

		//重绘图
	}
}
/*
* 新建点文件
*/
void CPrjManage::OnNewPoint()
{
	//MessageBox(L"点文件", L"提示", MB_ICONASTERISK);
	//先判断有没打开工程
	if (mBasePath!=L"")
	{
		CString pointFileName;
		if (dlgNewPointFile(pointFileName))
		{
			malaTree tpNode;
			if (makeTree(tpNode, pointFileName, L"mpt"))
			{
				CFileFind fFind;
				if (!fFind.FindFile(tpNode.filePath))
				{
					fileNodeTree.push_back(tpNode);
					if (currentPrj.newPointFile(fileNodeTree, tpNode.filePath))
					{
						HTREEITEM hItem = m_wndPrjView.GetRootItem();
						m_wndPrjView.InsertItem(tpNode.itemnode, 2, 2, hItem);
					}
					else
					{
						MessageBox(L"创建文件失败", L"提示", MB_ICONWARNING);
					}
				}
				else
				{
					MessageBox(L"文件已经存在", L"提示", MB_ICONWARNING);
				}
			}
			else
			{
				MessageBox(L"创建文件失败", L"提示", MB_ICONWARNING);
			}

			
		}
		else
		{
			MessageBox(L"创建文件失败", L"提示", MB_ICONWARNING);
		}
	}
	else
	{
		MessageBox(L"当前没有工程文件，请先新建工程或者打开已有工程", L"提示", MB_ICONWARNING);
	}
}

//显示文件
void CPrjManage::OnDisplayFile()
{
	//更新fileNodeTree
	CString str = m_wndPrjView.GetItemText(selTreeItem);
	for (size_t i = 0; i < fileNodeTree.size(); i++)
	{
		if (fileNodeTree[i].itemnode == str)
		{
			fileNodeTree[i].isOpen = true;
			fileNodeTree[i].isActive = false;
			int imgindex = 0;
			if (fileNodeTree[i].fileType == L"mpt")
				imgindex = 3;
			if (fileNodeTree[i].fileType == L"mle")
				imgindex = 6;
			if (fileNodeTree[i].fileType == L"mpn")
				imgindex = 9;
			if (fileNodeTree[i].fileType == L"mll")
				imgindex = 12;
			if (currentPrj.writeAllNode(fileNodeTree))
				m_wndPrjView.SetItemImage(selTreeItem, imgindex, imgindex);
			else
				MessageBox(L"打开文件失败", L"提示", MB_ICONWARNING);
		}
	}
	//...ondraw

}

//隐藏文件
void CPrjManage::OnHideFile()
{
	//更新fileNodeTree
	CString str = m_wndPrjView.GetItemText(selTreeItem);
	for (size_t i = 0; i < fileNodeTree.size(); i++)
	{
		if (fileNodeTree[i].itemnode == str)
		{
			fileNodeTree[i].isOpen = false;
			fileNodeTree[i].isActive = false;
			int imgindex = 0;
			if (fileNodeTree[i].fileType==L"mpt")
				imgindex = 2;
			if (fileNodeTree[i].fileType == L"mle")
				imgindex = 5;
			if (fileNodeTree[i].fileType == L"mpn")
				imgindex = 8;
			if (fileNodeTree[i].fileType == L"mll")
				imgindex = 11;
			if(currentPrj.writeAllNode(fileNodeTree))
				m_wndPrjView.SetItemImage(selTreeItem, imgindex, imgindex);
			else
				MessageBox(L"隐藏文件失败", L"提示", MB_ICONWARNING);
		}
	}
	//...ondraw

}

//激活文件
void CPrjManage::OnActiveFile()
{
	//更新fileNodeTree
	CString str = m_wndPrjView.GetItemText(selTreeItem);
	for (size_t i = 0; i < fileNodeTree.size(); i++)
	{
		if (fileNodeTree[i].itemnode == str)
		{
			//清除之前激活状态
			cleanActiveMask(fileNodeTree[i].fileType, selTreeItem);
			
			//设置激活状态
			fileNodeTree[i].isOpen = true;
			fileNodeTree[i].isActive = true;
			int imgindex = 0;
			if (fileNodeTree[i].fileType == L"mpt")
				imgindex = 4;
			if (fileNodeTree[i].fileType == L"mle")
				imgindex = 7;
			if (fileNodeTree[i].fileType == L"mpn")
				imgindex = 10;
			if (fileNodeTree[i].fileType == L"mll")
				imgindex = 13;
			if (currentPrj.writeAllNode(fileNodeTree))
				m_wndPrjView.SetItemImage(selTreeItem, imgindex, imgindex);
			else
				MessageBox(L"激活文件失败", L"提示", MB_ICONWARNING);
			
		}
	}
	//...ondraw

}

//构造文件节点
bool CPrjManage::makeTree(malaTree &rTree, CString fileName, CString fileType)
{
	rTree.filePath = mBasePath  + fileName +L"."+ fileType;
	rTree.fileType = fileType;
	rTree.itemnode = fileName + L"." + fileType;
	rTree.isActive = false;
	rTree.isOpen = false;
	for (size_t i = 0; i < fileNodeTree.size(); i++)
	{
		if (fileNodeTree[i].filePath == rTree.filePath)
		{
			return false;
		}
	}
	return true;
}
//删除所有子节点
void CPrjManage::delAllChildrenItem()
{
	fileNodeTree.clear();
	m_wndPrjView.DeleteAllItems();
	HTREEITEM prjRoot = m_wndPrjView.InsertItem(_T("----------"), 0, 0);
}
//清除激活状态
void CPrjManage::cleanActiveMask(CString &activeType, HTREEITEM newActive)
{
	//vector清除状态
	for (size_t i = 0; i < fileNodeTree.size(); i++)
	{
		if (fileNodeTree[i].fileType == activeType&&fileNodeTree[i].isActive==true)
		{
			fileNodeTree[i].isActive = false;
		}
	}
	//图标清除状态
	if (activeType == L"mpt")
	{
		if (actPointItem)
		{
			m_wndPrjView.SetItemImage(actPointItem, 3, 3);

		}
		actPointItem = newActive;
	}	
	if (activeType == L"mle")
	{
		if (actLineItem)
		{
			m_wndPrjView.SetItemImage(actLineItem, 6, 6);
		}
		actLineItem = newActive;
	}
	if (activeType == L"mpn")
	{
		if (actPloyItem)
		{
			m_wndPrjView.SetItemImage(actPloyItem, 9, 9);
		}
		actPloyItem = newActive;
	}	
	if (activeType == L"mll")
	{
		if (actLabelItem)
		{
			m_wndPrjView.SetItemImage(actLabelItem, 12, 12);
		}
		actLabelItem = newActive;
	}
}