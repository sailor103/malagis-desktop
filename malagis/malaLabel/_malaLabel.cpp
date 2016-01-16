#include "stdafx.h"
#include "_malaLabel.h"
#include "_malaDialogs.h"
#include "_malaIO.h"

/*
* 输入注释
*/
CmalaLabelsInput::CmalaLabelsInput(CView* mView, malaScreen *pScreen, CString &fileFullPath)
{
	mBaseView = mView;
	mPath = fileFullPath;
	mScreen = pScreen;
	getLabelPro();
	mIsInput = false;
}
CmalaLabelsInput::~CmalaLabelsInput()
{
}
void CmalaLabelsInput::LButtonDown(UINT nFlags, malaPoint point)
{
	if (!mIsInput)
	{
		if (mLabelPro.textStr != L"")
		{
			malaCDC dc(mBaseView, *mScreen);
			dc.textDraw(point, mLabelPro);
			CLabelIO lio;
			lio.labelAdd(point, mLabelPro,mPath);
		}
		else
		{
			MessageBox(mBaseView->m_hWnd, L"输入内容不得为空", L"提示", MB_ICONQUESTION);
		}
		mIsInput = true;
	}
	
}

void CmalaLabelsInput::getLabelPro()
{
	//字体对话框
	if (dlgInputLabel(mLabelPro) == FALSE)
	{
		mLabelPro.labelHeight = 20;    //字体高度
		mLabelPro.labelHeight = 10;     //字体宽度
		mLabelPro.labelAngle = 0;  //字体角度
		mLabelPro.textAngle = 0; //文本角度
		mLabelPro.textColor = RGB(0, 0, 0);//字体颜色
		mLabelPro.textOff = 1;  //字体间距
		mLabelPro.textFont = L"华文楷体";  //字体类型
		mLabelPro.fontWeight = 400;
	}
}
/*
* 选择注释实现
*/
malaPoint CmalaLabelsSelect::m_pnt;
malaPointPro CmalaLabelsSelect::m_PntPro;
CView* CmalaLabelsSelect::m_StaticView = NULL;
malaScreen* CmalaLabelsSelect::m_Screen = NULL;

CmalaLabelsSelect::CmalaLabelsSelect()
{

}

CmalaLabelsSelect::CmalaLabelsSelect(CView* mView, malaScreen *pScreen, CString &fileFullPath)
{
	mBaseView = mView;
	m_StaticView = mView;
	mPath = fileFullPath;

	m_bDraw = FALSE;
	m_Selected = FALSE;
	m_Screen = pScreen;
}

CmalaLabelsSelect::~CmalaLabelsSelect()
{

}

void CmalaLabelsSelect::LButtonDown(UINT nFlags, malaPoint point)
{
	m_bDraw = TRUE;
	m_ptOrigin = m_perPoint = point;
}

void CmalaLabelsSelect::LButtonUp(UINT nFlags, malaPoint point)
{
	m_bDraw = FALSE;
	malaCDC dc(mBaseView, *m_Screen);
	dc.drawRectNULLFill(m_ptOrigin, point);
	if (m_ptOrigin.x > point.x)
	{
		m_rect.xmax = m_ptOrigin.x;
		m_rect.xmin = point.x;
	}
	else
	{
		m_rect.xmin = m_ptOrigin.x;
		m_rect.xmax = point.x;
	}

	if (m_ptOrigin.y > point.y)
	{
		m_rect.ymax = m_ptOrigin.y;
		m_rect.ymin = point.y;
	}
	else
	{
		m_rect.ymin = m_ptOrigin.y;
		m_rect.ymax = point.y;
	}
	//先获取所有符合条件的点
	CLabelIO pio;
	vector<malaLabelFile>allLabels;
	pio.getAllLabel(*m_Screen, allLabels, mPath);
	//再查找是否被选中
	malaLogic tlog;
	for (size_t j = 0; j < allLabels.size(); j++)
	{
		if (tlog.isPntInRect(allLabels[j].mLabel, m_rect))
		{
			m_pnt = allLabels[j].mLabel;
			mLablePro = allLabels[j].mLabelPro;
			CPoint A, B;
			m_PntPro.pointColor = RGB(0, 255, 0);
			m_PntPro.pointRadio = 10;
			m_PntPro.pointStyle = 2;
			A.x = long(m_pnt.x - m_PntPro.pointRadio);
			A.y = long(m_pnt.y - m_PntPro.pointRadio);
			B.x = long(m_pnt.x + m_PntPro.pointRadio);
			B.y = long(m_pnt.y + m_PntPro.pointRadio);
			SetTimer(mBaseView->m_hWnd, 1, 500, TimerProc);
			if (MessageBox(mBaseView->m_hWnd, L"选择该注释吗?", L"提示", MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				KillTimer(mBaseView->m_hWnd, 1);
				mBaseView->InvalidateRect(CRect(A, B), TRUE);
				malaCDC dc(mBaseView, *m_Screen);
				dc.drawSelectCirclePoint(m_pnt, m_PntPro);
				dc.pointDrawAuto(m_pnt, m_PntPro);
				m_Selected = TRUE;
				break;
			}
			KillTimer(mBaseView->m_hWnd, 1);
			mBaseView->InvalidateRect(CRect(A, B), TRUE);
		}
	}
}

void CmalaLabelsSelect::MouseMove(UINT nFlags, malaPoint point)
{
	if (m_bDraw)
	{
		malaCDC dc(mBaseView, *m_Screen);
		dc.drawRectNULLFill(m_ptOrigin, m_perPoint);
		dc.drawRectNULLFill(m_ptOrigin, point);
		m_perPoint = point;
	}

}