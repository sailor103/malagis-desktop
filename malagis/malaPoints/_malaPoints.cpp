#include "stdafx.h"
#include "_malaPoints.h"
#include "_malaDialogs.h"
#include "_malaIO.h"

/*
* 输入点
*/
CmalaPointsInput::CmalaPointsInput(CView* mView, malaScreen *pScreen,CString &fileFullPath)
{
	mBaseView = mView;
	mScreen = pScreen;
	mPath = fileFullPath;
	GetPointPro();
}
 
CmalaPointsInput::~CmalaPointsInput(){}

void CmalaPointsInput::LButtonDown(UINT nFlags, malaPoint point)
{
	malaCDC dc(mBaseView, *mScreen);
	switch (mPointPro.pointStyle)
	{
	case 0:
		dc.pointDrawRect(point, mPointPro);
		break;
	case 1:
		dc.pointDrawTriangle(point, mPointPro);
		break;
	case 2:
		dc.pointDrawCircle(point, mPointPro);
		break;
	default:
		break;
	}
	CPointIO pio;
	pio.pointAdd(point, mPointPro, mPath);

}
void CmalaPointsInput::GetPointPro()
{
	if (dlgInputPoint(mPointPro)==false)
	{
		mPointPro.pointStyle = 0;
		mPointPro.pointRadio = 1;
		mPointPro.pointColor = RGB(0,0,0);
	}
}

/*
* 选择点实现
*/
malaPoint CmalaPointsSelect::m_pnt;
malaPointPro CmalaPointsSelect::m_PntPro;
CView* CmalaPointsSelect::m_StaticView = NULL;
malaScreen* CmalaPointsSelect::m_Screen = NULL;

CmalaPointsSelect::CmalaPointsSelect()
{

}

CmalaPointsSelect::CmalaPointsSelect(CView* mView, malaScreen *pScreen, CString &fileFullPath)
{
	mBaseView = mView;
	m_StaticView = mView;
	mPath = fileFullPath;

	m_bDraw = FALSE;
	m_Selected = FALSE;
	m_Screen = pScreen;
}

CmalaPointsSelect::~CmalaPointsSelect()
{

}

void CmalaPointsSelect::LButtonDown(UINT nFlags, malaPoint point)
{
	m_bDraw = TRUE;
	m_ptOrigin = m_perPoint = point;
}

void CmalaPointsSelect::LButtonUp(UINT nFlags, malaPoint point)
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
	CPointIO pio;
	vector<malaPointFile>allPoints;
	pio.getAllPoint(*m_Screen, allPoints, mPath);
	//再查找是否被选中
	malaLogic tlog;
	for (size_t j = 0; j < allPoints.size(); j++)
	{
		if (tlog.isPntInRect(allPoints[j].m_point, m_rect))
		{
			m_pnt = allPoints[j].m_point;
			m_PntPro = allPoints[j].m_pointpro;
			CPoint A, B;
			A.x = long(m_pnt.x - m_PntPro.pointRadio);
			A.y = long(m_pnt.y - m_PntPro.pointRadio);
			B.x = long(m_pnt.x + m_PntPro.pointRadio);
			B.y = long(m_pnt.y + m_PntPro.pointRadio);
			SetTimer(mBaseView->m_hWnd, 1, 500, TimerProc);
			if (MessageBox(mBaseView->m_hWnd, L"选择该点吗?", L"提示", MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				KillTimer(mBaseView->m_hWnd, 1);
				mBaseView->InvalidateRect(CRect(A, B), TRUE);
				malaCDC dc(mBaseView,*m_Screen);
				dc.drawSelectRectPoint(m_pnt, m_PntPro);
				m_Selected = TRUE;
				break;
			}
			KillTimer(mBaseView->m_hWnd, 1);
			mBaseView->InvalidateRect(CRect(A, B), TRUE);
		}
	}
}

void CmalaPointsSelect::MouseMove(UINT nFlags, malaPoint point)
{
	if (m_bDraw)
	{
		malaCDC dc(mBaseView, *m_Screen);
		dc.drawRectNULLFill(m_ptOrigin, m_perPoint);
		dc.drawRectNULLFill(m_ptOrigin, point);
		m_perPoint = point;
	}

}
