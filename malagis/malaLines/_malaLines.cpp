#include "stdafx.h"
#include "_malaLines.h"
#include "_malaDialogs.h"
#include "_malaIO.h"

/*
* 输入线
*/
CmalaLinesInput::CmalaLinesInput(CView* mView, malaScreen *pScreen, CString &fileFullPath)
{

	mBaseView = mView;
	mPath = fileFullPath;
	m_bDraw = FALSE;
	GetLinePro();
	mScreen = pScreen;
}
CmalaLinesInput::~CmalaLinesInput()
{

}
void CmalaLinesInput::LButtonDown(UINT nFlags, malaPoint point)
{
	m_bDraw = TRUE;
	m_PerPoint = m_PtOrigin = point;
	m_Line.push_back(point);
}
void CmalaLinesInput::MouseMove(UINT nFlags, malaPoint point)
{
	//橡皮线
	malaCDC dc(mBaseView, *mScreen);
	if (m_bDraw)
	{
		dc.lineDrawX(m_PtOrigin, m_PerPoint, m_LinePro);
		dc.lineDrawX(m_PtOrigin, point, m_LinePro);
		m_PerPoint = point;
	}
}

void CmalaLinesInput::RButtonDown(UINT nFlags, malaPoint point)
{
	m_bDraw = FALSE;
	
	//保存线
	if (m_Line.size())
	{
		CLineIO lio;
		lio.lineAdd(m_Line, m_LinePro, mPath);
		m_Line.clear();
	}
}

void CmalaLinesInput::GetLinePro()
{
	if (dlgInputLine(m_LinePro) == FALSE)
	{
		m_LinePro.lineColor = RGB(0, 0, 0);
		m_LinePro.lineStyle = 0;
		m_LinePro.lineWidth = 1;
	}
	
}

/*
* 选择线实现
*/
vector<malaPoint> CmalaLinesSelect::mLine;
malaLinePro CmalaLinesSelect::mLinePro;
CView* CmalaLinesSelect::m_StaticView = NULL;
malaScreen* CmalaLinesSelect::m_Screen = NULL;

CmalaLinesSelect::CmalaLinesSelect()
{

}

CmalaLinesSelect::CmalaLinesSelect(CView* mView, malaScreen *pScreen, CString &fileFullPath)
{
	mBaseView = mView;
	m_StaticView = mView;
	mPath = fileFullPath;

	m_bDraw = FALSE;
	m_Selected = FALSE;
	m_Screen = pScreen;
}

CmalaLinesSelect::~CmalaLinesSelect()
{

}

void CmalaLinesSelect::LButtonDown(UINT nFlags, malaPoint point)
{
	m_bDraw = TRUE;
	m_ptOrigin = m_perPoint = point;
}

void CmalaLinesSelect::LButtonUp(UINT nFlags, malaPoint point)
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
	CLineIO pio;
	vector<malaLineFile>allLines;
	pio.getAllLines(*m_Screen, allLines, mPath);
	//再查找是否被选中
	malaLogic tlog;
	for (size_t j = 0; j < allLines.size(); j++)
	{
		//先获取一条线的外接矩形
		if (tlog.isLineInRect(m_rect, allLines[j].mLine))
		{
			mLine = allLines[j].mLine;
			mLinePro = allLines[j].mLinePro;
			
			SetTimer(mBaseView->m_hWnd, 1, 500, TimerLine);
			if (MessageBox(mBaseView->m_hWnd, L"选择该线吗?", L"提示", MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				malaCDC dc(mBaseView, *m_Screen);
				dc.lineDrawAll(mLine, mLinePro);
				KillTimer(mBaseView->m_hWnd, 1);
				//绘制选中标志
				for (size_t k = 0; k < mLine.size(); k++)
				{
					malaPointPro tpPointPro;
					tpPointPro.pointRadio = mLinePro.lineWidth+2;
					tpPointPro.pointColor = mLinePro.lineColor;
					
					dc.drawSelectRectPoint(mLine[k], tpPointPro);
				}
				
				m_Selected = TRUE;
				break;
			}
			malaCDC dc(mBaseView, *m_Screen);
			dc.lineDrawAll(mLine, mLinePro);
			KillTimer(mBaseView->m_hWnd, 1);
			//mBaseView->InvalidateRect(CRect(A, B), TRUE);
		}
	}
}

void CmalaLinesSelect::MouseMove(UINT nFlags, malaPoint point)
{
	if (m_bDraw)
	{
		malaCDC dc(mBaseView, *m_Screen);
		dc.drawRectNULLFill(m_ptOrigin, m_perPoint);
		dc.drawRectNULLFill(m_ptOrigin, point);
		m_perPoint = point;
	}

}

/*
* 移动线实现
*/
CmalaLinesMove::CmalaLinesMove(CView* mView, malaScreen *pScreen, CString &fileFullPath)
{
	mBaseView = mView;
	mPath = fileFullPath;
	m_Screen = pScreen;
	CmalaLinesSelect obj(mView, pScreen, fileFullPath);
	m_SelectLine = obj;
	m_Selected = FALSE;
	m_bDraw = FALSE;
}

CmalaLinesMove::~CmalaLinesMove()
{

}

void CmalaLinesMove::LButtonDown(UINT nFlags, malaPoint point)
{
	if (!m_Selected)
		m_SelectLine.LButtonDown(nFlags, point);
	else
	{
		m_bDraw = TRUE;
		m_ptOrigin = point;
	}
}

void CmalaLinesMove::LButtonUp(UINT nFlags, malaPoint point)
{
	if (!m_Selected)
		m_SelectLine.LButtonUp(nFlags, point);
	else
	{
		CLineIO lio;
		lio.lineUpdate(m_perLine, mSLinePro, mPath);
		mBaseView->Invalidate(TRUE);
		m_bDraw = FALSE;
		m_Selected = FALSE;
		m_SelectLine.m_Selected = FALSE;

	}

	m_Selected = m_SelectLine.m_Selected;
	if (m_Selected)
	{
		this->mSLine = m_SelectLine.mLine;
		this->mSLinePro = m_SelectLine.mLinePro;
		m_perLine = mSLine;
	}

}

void CmalaLinesMove::MouseMove(UINT nFlags, malaPoint point)
{
	if (!m_Selected)
		m_SelectLine.MouseMove(nFlags, point);
	else if (m_bDraw)
	{
		malaCDC dc(mBaseView, *m_Screen);
		dc.lineDrawAllX(m_perLine, mSLinePro);
		for (size_t i = 0; i < m_perLine.size(); i++)
		{
			m_perLine[i].x = mSLine[i].x + point.x - m_ptOrigin.x;
			m_perLine[i].y = mSLine[i].y + point.y - m_ptOrigin.y;
		}
		dc.lineDrawAllX(m_perLine, mSLinePro);
	}
}

/*
* 复制线实现
*/
CmalaLinesCopy::CmalaLinesCopy(CView* mView, malaScreen *pScreen, CString &fileFullPath)
{
	mBaseView = mView;
	mPath = fileFullPath;
	m_Screen = pScreen;
	CmalaLinesSelect obj(mView, pScreen, fileFullPath);
	m_SelectLine = obj;
	m_Selected = FALSE;
	m_bDraw = FALSE;
}

CmalaLinesCopy::~CmalaLinesCopy()
{

}

void CmalaLinesCopy::LButtonDown(UINT nFlags, malaPoint point)
{
	if (!m_Selected)
		m_SelectLine.LButtonDown(nFlags, point);
	else
	{
		m_bDraw = TRUE;
		m_ptOrigin = point;
	}
}

void CmalaLinesCopy::LButtonUp(UINT nFlags, malaPoint point)
{
	if (!m_Selected)
		m_SelectLine.LButtonUp(nFlags, point);
	else
	{
		CLineIO lio;
		lio.lineAdd(m_perLine, mSLinePro, mPath);
		mBaseView->Invalidate(TRUE);
		m_bDraw = FALSE;
		m_Selected = FALSE;
		m_SelectLine.m_Selected = FALSE;

	}

	m_Selected = m_SelectLine.m_Selected;
	if (m_Selected)
	{
		this->mSLine = m_SelectLine.mLine;
		this->mSLinePro = m_SelectLine.mLinePro;
		m_perLine = mSLine;
	}

}

void CmalaLinesCopy::MouseMove(UINT nFlags, malaPoint point)
{
	if (!m_Selected)
		m_SelectLine.MouseMove(nFlags, point);
	else if (m_bDraw)
	{
		malaCDC dc(mBaseView, *m_Screen);
		dc.lineDrawAllX(m_perLine, mSLinePro);
		for (size_t i = 0; i < m_perLine.size(); i++)
		{
			m_perLine[i].x = mSLine[i].x + point.x - m_ptOrigin.x;
			m_perLine[i].y = mSLine[i].y + point.y - m_ptOrigin.y;
		}
		dc.lineDrawAllX(m_perLine, mSLinePro);
		dc.lineDrawAll(mSLine, mSLinePro);
	}
}

/*
* 修改线属性实现
*/
CmalaLinesModify::CmalaLinesModify(CView* mView, malaScreen *pScreen, CString &fileFullPath)
{
	mBaseView = mView;
	mPath = fileFullPath;
	m_Screen = pScreen;
	CmalaLinesSelect obj(mView, pScreen, fileFullPath);
	m_SelectLine = obj;
	m_Selected = FALSE;
	m_bDraw = FALSE;
}

CmalaLinesModify::~CmalaLinesModify()
{

}

void CmalaLinesModify::LButtonDown(UINT nFlags, malaPoint point)
{
	if (!m_Selected)
		m_SelectLine.LButtonDown(nFlags, point);
}

void CmalaLinesModify::LButtonUp(UINT nFlags, malaPoint point)
{
	if (!m_Selected)
		m_SelectLine.LButtonUp(nFlags, point);
	
	m_Selected = m_SelectLine.m_Selected;

	if (m_Selected)
	{
		this->mSLine = m_SelectLine.mLine;
		this->mSLinePro = m_SelectLine.mLinePro;

		if (dlgModifyLinePro(mSLinePro))
		{
			CLineIO lio;
			lio.lineUpdate(mSLine, mSLinePro, mPath);
			mBaseView->Invalidate(TRUE);
		}
		
		m_bDraw = FALSE;
		m_Selected = FALSE;
		m_SelectLine.m_Selected = FALSE;
	}

}

void CmalaLinesModify::MouseMove(UINT nFlags, malaPoint point)
{
	if (!m_Selected)
		m_SelectLine.MouseMove(nFlags, point);
}