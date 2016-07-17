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

// malagisView.h : CmalagisView 类的接口
//

#pragma once

//自定义头文件
#include "_malaBase.h"

class CmalagisView : public CView
{
protected: // 仅从序列化创建
	CmalagisView();
	DECLARE_DYNCREATE(CmalagisView)

// 特性
public:
	CmalagisDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CmalagisView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnButtonPointsInput();

//自定义变量
private:
	CmalaMouseAction *mBaseOper;
	int mouseCursor;//0 默认 1 放大 2 缩小 3 移动
	HACCEL hAccel;//快捷键

public:
	malaScreen mScreen;
	vector <malaTree> mNode;//存放当前工程中的目录树
	void upadteTree();//获取目录树
	CString getActiveFile(CString fileType);//获取当前激活文件
	void displayAllGraphs();//重绘
	void setActionStr(CString str);//设置当前操作字符串
	void clearActionStr();//清除当前操作
	void setCurrentCursor();//设置当前鼠标指针


public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnButtonZoomIn();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnButtonZoomReset();
	afx_msg void OnButtonZoomout();
	afx_msg void OnButtonZoomMove();
	afx_msg void OnButtonZoomRefresh();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnButtonPointsSelect();
	afx_msg void OnButtonPointsMove();
	afx_msg void OnButtonPointsCopy();
	afx_msg void OnButtonPointsChangePro();
	afx_msg void OnButtonPointsDelete();
	afx_msg void OnButtonPointsDeleteAll();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnButtonLinesInput();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnButtonLinesSelect();
	afx_msg void OnButtonLinesCopy();
	afx_msg void OnButtonLinesMove();
	afx_msg void OnButtonLinesChangePro();
	afx_msg void OnButtonLinesCut();
	afx_msg void OnButtonLinesPointAdd();
	afx_msg void OnButtonLinesPointMove();
	afx_msg void OnButtonLinesPointDelete();
	afx_msg void OnButtonLinesDelete();
	afx_msg void OnButtonLinesDeleteAll();
	afx_msg void OnButtonPolygonInput();
	afx_msg void OnButtonPolysSelect();
	afx_msg void OnButtonPolysMove();
	afx_msg void OnButtonPolysCopy();
	afx_msg void OnButtonPolysModify();
	afx_msg void OnButtonPolysAddPoint();
	afx_msg void OnButtonPolysMovePoint();
	afx_msg void OnButtonPolysDeletePoint();
	afx_msg void OnButtonPolysDelete();
	afx_msg void OnButtonPolysDeleteAll();
	afx_msg void OnButtonLabelInput();
	afx_msg void OnButtonLabelSelect();
	afx_msg void OnButtonLabelMove();
	afx_msg void OnButtonLabelCopy();
	afx_msg void OnButtonLabelModify();
	afx_msg void OnButtonLabelDelete();
	afx_msg void OnButtonLabelDeleteAll();
	afx_msg void OnButtonTopoSelectPoint();
	afx_msg void OnButtonTopoSelectLine();
	afx_msg void OnButtonTopoSelectPoly();
	afx_msg void OnButtonLineOriDis();
	afx_msg void OnButtonLineDisDiy();
	afx_msg void OnButtonPolygonMeasure();
};

#ifndef _DEBUG  // malagisView.cpp 中的调试版本
inline CmalagisDoc* CmalagisView::GetDocument() const
   { return reinterpret_cast<CmalagisDoc*>(m_pDocument); }
#endif

