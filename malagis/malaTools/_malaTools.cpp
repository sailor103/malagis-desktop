#include "stdafx.h"
#include "_malaTools.h"


/*
* 放大图形实现
*/
malaZoonIn::malaZoonIn()
{

}
malaZoonIn::malaZoonIn(CView* ptView, malaScreen *Screen)
{
	mBaseView = ptView;
	m_Screen = Screen;
	m_bDraw = FALSE;
}

malaZoonIn::~malaZoonIn()
{

}

void malaZoonIn::LButtonDown(UINT nFlags, malaPoint point)
{
	m_bDraw = TRUE;
	m_PtOrigin.x = m_perPoint.x = point.x;
	m_PtOrigin.y = m_perPoint.y = point.y;
}

void malaZoonIn::MouseMove(UINT nFlags, malaPoint point)
{
	if (m_bDraw)
	{
		malaCDC dc(mBaseView, *m_Screen);
		dc.drawRectNULLFill(m_PtOrigin, m_perPoint);
		dc.drawRectNULLFill(m_PtOrigin, point);
		m_perPoint.x = point.x;
		m_perPoint.y = point.y;
	}
}

void malaZoonIn::LButtonUp(UINT nFlags, malaPoint point)
{
	m_bDraw = FALSE;
	if ((m_PtOrigin.x == point.x) && (m_PtOrigin.y == point.y))
	{
		//中心点坐标
		long xmid = m_Screen->wScreen / 2;
		long ymid = m_Screen->hScreen / 2;
		malaPoint tmpPoint;
		ScreenToCoord(xmid, ymid, *m_Screen, &tmpPoint.x, &tmpPoint.y);
		
		//先把图形移到中心
		m_Screen->lbx = m_Screen->lbx + (point.x - tmpPoint.x);
		m_Screen->lby = m_Screen->lby + (point.y - tmpPoint.y);

		//再将图形放大
		m_Screen->lbx = m_Screen->lbx + xmid * m_Screen->scale * 0.1;
		m_Screen->lby = m_Screen->lby + ymid * m_Screen->scale * 0.1;
		m_Screen->scale = m_Screen->scale*0.9;
		

		/*double xo = point.x;
		double yo = point.y;
		m_Screen->lbx = xo - (m_Screen->scale*(x - n)) / 2;
		m_Screen->lby = yo - (m_Screen->scale*(y - n)) / 2;
		b11 = (x - n) / x;
		b12 = (y - n) / y;
		m_Screen->scale = m_Screen->scale*max(b11, b12);*/
	}
	else
	{
		double x1 = min(m_PtOrigin.x, point.x);
		double y1 = min(m_PtOrigin.y, point.y);
		double x2 = max(m_PtOrigin.x, point.x);
		double y2 = max(m_PtOrigin.y, point.y);
		m_Screen->lbx = x1;
		m_Screen->lby = y1;

		double blc1 = (x2 - x1) / (double)m_Screen->wScreen;
		double blc2 = (y2 - y1) / (double)m_Screen->hScreen;
		m_Screen->scale = (blc1 > blc2) ? blc1 : blc2;
	}
	mBaseView->Invalidate(TRUE);
}