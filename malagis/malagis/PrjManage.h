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

#pragma once

#include "ViewTree.h"
#include "malaStruct.h"
#include "_malaIO.h"
#include <vector>
using namespace std;

class CPrjManageToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CPrjManage : public CDockablePane
{
// 构造
public:
	CPrjManage();

	void AdjustLayout();
	void OnChangeVisualStyle();

// 特性
protected:

	CViewTree m_wndPrjView;
	CImageList m_PrjViewImages;
	CPrjManageToolBar m_wndToolBar;
	HTREEITEM selTreeItem;

	//记录当前激活的4张表
	HTREEITEM actPointItem;
	HTREEITEM actLineItem;
	HTREEITEM actPloyItem;
	HTREEITEM actLabelItem;

protected:
	void FillPrjView();

// 实现
public:
	virtual ~CPrjManage();

public:
	vector <malaTree> fileNodeTree;//存放当前工程中的目录树
	CProjectIO currentPrj;//记录当前的工程
	CString mBasePath;//记录当前的工程目录

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnProperties();
	afx_msg void OnFileOpen();
	afx_msg void OnFileOpenWith();
	afx_msg void OnDummyCompile();
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnNewPrj();//新建工程
	afx_msg void OnOpenPrj();//打开工程
	afx_msg void OnNewPoint();//新建点文件
	afx_msg void OnDisplayFile();//显示文件
	afx_msg void OnHideFile();//显示文件
	afx_msg void OnActiveFile();//显示文件
	afx_msg void OnDelFile();//移除文件
	afx_msg void OnGraphFilePro();//文件属性

	DECLARE_MESSAGE_MAP()
protected:
	bool makeTree(malaTree &rTree,CString fileName,CString fileType);//构造文件节点
	void delAllChildrenItem();//删除所以子节点
	void cleanActiveMask(CString &activeType, HTREEITEM newActive);//清除激活状态
	void pjOnDraw();//调用CXXXXView的重绘
};

