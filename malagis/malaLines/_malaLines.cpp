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
	if (m_Line.size())
		m_Line.clear();
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
	if (mSLine.size())
		mSLine.clear();
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
		mSLine.clear();
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
	if (mSLine.size())
		mSLine.clear();
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
		mSLine.clear();
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
}

CmalaLinesModify::~CmalaLinesModify()
{
	if (mSLine.size())
		mSLine.clear();
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
		mSLine.clear();
		m_Selected = FALSE;
		m_SelectLine.m_Selected = FALSE;
	}

}

void CmalaLinesModify::MouseMove(UINT nFlags, malaPoint point)
{
	if (!m_Selected)
		m_SelectLine.MouseMove(nFlags, point);
}

/*
* 剪断线实现
*/
CmalaLinesCut::CmalaLinesCut(CView* mView, malaScreen *pScreen, CString &fileFullPath)
{
	mBaseView = mView;
	mPath = fileFullPath;
	m_Screen = pScreen;
	CmalaLinesSelect obj(mView, pScreen, fileFullPath);
	m_SelectLine = obj;
	m_Selected = FALSE;
	callSel = false;
}

CmalaLinesCut::~CmalaLinesCut()
{
	if (mSLine.size())
		mSLine.clear();
	if (mPLine.size())
		mPLine.clear();
}

void CmalaLinesCut::LButtonDown(UINT nFlags, malaPoint point)
{
	if (!m_Selected&&!callSel)
		m_SelectLine.LButtonDown(nFlags, point);
	else
	{
		malaLogic cutlog;
		if (cutlog.cutLine(point,mSLine,mPLine))
		{
			CLineIO lio;
			lio.lineUpdate(mSLine, mSLinePro,mPath);
			lio.lineAdd(mPLine, mSLinePro,mPath);
			
			//mBaseView->Invalidate(TRUE);

			malaCDC cutcdc(mBaseView, *m_Screen);
			malaPointPro tPro;
			tPro.pointColor = mSLinePro.lineColor;
			tPro.pointRadio = mSLinePro.lineWidth + 2;
			tPro.pointStyle = 0;
			cutcdc.drawSelectCirclePoint(mSLine[mSLine.size()-1], tPro);

			mSLine.clear();
			mPLine.clear();
			m_Selected = FALSE;
			m_SelectLine.m_Selected = FALSE;
			callSel = true;
		}
		
	}
}

void CmalaLinesCut::LButtonUp(UINT nFlags, malaPoint point)
{
	if (!m_Selected&&!callSel)
		m_SelectLine.LButtonUp(nFlags, point);

	m_Selected = m_SelectLine.m_Selected;

	if (m_Selected)
	{
		this->mSLine = m_SelectLine.mLine;
		this->mSLinePro = m_SelectLine.mLinePro;
	}

}

void CmalaLinesCut::MouseMove(UINT nFlags, malaPoint point)
{
	if (!m_Selected)
		m_SelectLine.MouseMove(nFlags, point);
}

/*
* 线上加点实现
*/
CmalaLinesAddPoint::CmalaLinesAddPoint(CView* mView, malaScreen *pScreen, CString &fileFullPath)
{
	mBaseView = mView;
	mPath = fileFullPath;
	m_Screen = pScreen;
	CmalaLinesSelect obj(mView, pScreen, fileFullPath);
	m_SelectLine = obj;
	m_Selected = FALSE;
	callSel = false;
}

CmalaLinesAddPoint::~CmalaLinesAddPoint()
{
	if (mSLine.size())
		mSLine.clear();
}

void CmalaLinesAddPoint::LButtonDown(UINT nFlags, malaPoint point)
{
	if (!m_Selected&&!callSel)
		m_SelectLine.LButtonDown(nFlags, point);
	else
	{
		malaLogic cutlog;
		if (cutlog.addPointInLine(point, mSLine))
		{
			CLineIO lio;
			lio.lineUpdate(mSLine, mSLinePro, mPath);

			//绘制选中标志
			malaCDC cutcdc(mBaseView, *m_Screen);
			for (size_t k = 0; k < mSLine.size(); k++)
			{
				malaPointPro tpPointPro;
				tpPointPro.pointRadio = mSLinePro.lineWidth + 2;
				tpPointPro.pointColor = mSLinePro.lineColor;

				cutcdc.drawSelectRectPoint(mSLine[k], tpPointPro);
			}

			mSLine.clear();
			m_Selected = FALSE;
			m_SelectLine.m_Selected = FALSE;
			callSel = true;
		}

	}
}

void CmalaLinesAddPoint::LButtonUp(UINT nFlags, malaPoint point)
{
	if (!m_Selected&&!callSel)
		m_SelectLine.LButtonUp(nFlags, point);

	m_Selected = m_SelectLine.m_Selected;

	if (m_Selected)
	{
		this->mSLine = m_SelectLine.mLine;
		this->mSLinePro = m_SelectLine.mLinePro;
	}

}

void CmalaLinesAddPoint::MouseMove(UINT nFlags, malaPoint point)
{
	if (!m_Selected)
		m_SelectLine.MouseMove(nFlags, point);
}

/*
* 线上移点实现
*/
CmalaLinesMovePoint::CmalaLinesMovePoint(CView* mView, malaScreen *pScreen, CString &fileFullPath)
{
	mBaseView = mView;
	mPath = fileFullPath;
	m_Screen = pScreen;
	CmalaLinesSelect obj(mView, pScreen, fileFullPath);
	m_SelectLine = obj;
	m_Selected = FALSE;
	m_bDraw = FALSE;
	m_Pos = 0;
	m_Double = TRUE;
}

CmalaLinesMovePoint::~CmalaLinesMovePoint()
{
	if (m_line.size())
		m_line.clear();
}

void CmalaLinesMovePoint::LButtonDown(UINT nFlags, malaPoint point)
{
	if (!m_Selected)
		m_SelectLine.LButtonDown(nFlags, point);
	else
	{
		malaLogic math;
		m_Pos = math.getPointPosInLine(point, m_line);
		if (m_Pos >= 0)
		{
			m_bDraw = TRUE;
			if (m_Pos == 0)
			{
				m_Double = FALSE;
				mPerPoint = m_line[m_Pos + 1];
			}
			if (m_Pos == m_line.size() - 1)
			{
				m_Double = FALSE;
				mPerPoint = m_line[m_Pos - 1];
			}
			if (m_Double)
			{
				mPerPoint = m_line[m_Pos];
				//m_perPoint2 = m_line[m_Pos + 1];
			}
		}
	}
}

void CmalaLinesMovePoint::LButtonUp(UINT nFlags, malaPoint point)
{
	if (!m_Selected)
		m_SelectLine.LButtonUp(nFlags, point);

	if (m_bDraw)
	{
		m_bDraw = FALSE;
		m_line[m_Pos] = point;

		CLineIO lio;
		lio.lineUpdate(m_line, m_linepro, mPath);

		m_line.clear();
		m_SelectLine.m_Selected = FALSE;
		m_Double = TRUE;//+
		mBaseView->Invalidate(TRUE);//+
	}
	m_Selected = m_SelectLine.m_Selected;
	if (m_Selected)
	{
		m_line  = m_SelectLine.mLine;
		m_linepro = m_SelectLine.mLinePro;
	}
}

void CmalaLinesMovePoint::MouseMove(UINT nFlags, malaPoint point)
{
	malaCDC dc(mBaseView, *m_Screen);
	if (!m_Selected)
		m_SelectLine.MouseMove(nFlags, point);
	if (m_bDraw)
	{
		if (m_Double)
		{
			dc.lineDrawX(m_line[m_Pos - 1], mPerPoint, m_linepro);
			dc.lineDrawX(m_line[m_Pos - 1], point, m_linepro);

			dc.lineDrawX(m_line[m_Pos + 1], mPerPoint, m_linepro);
			dc.lineDrawX(m_line[m_Pos + 1], point, m_linepro);
		}
		else
		{
			if (m_Pos == 0)
			{
				dc.lineDrawX(m_line[m_Pos + 1], mPerPoint, m_linepro);
				dc.lineDrawX(m_line[m_Pos + 1], point, m_linepro);
			}
			else
			{
				dc.lineDrawX(m_line[m_Pos - 1], mPerPoint, m_linepro);
				dc.lineDrawX(m_line[m_Pos - 1], point, m_linepro);
			}
		}

		mPerPoint  = point;
	}
}

/*
* 线上删点实现
*/
CmalaLinesDeletePoint::CmalaLinesDeletePoint(CView* mView, malaScreen *pScreen, CString &fileFullPath)
{
	mBaseView = mView;
	mPath = fileFullPath;
	m_Screen = pScreen;
	CmalaLinesSelect obj(mView, pScreen, fileFullPath);
	m_SelectLine = obj;
	m_Selected = FALSE;
	callSel = FALSE;
	m_Pos = 0;
}

CmalaLinesDeletePoint::~CmalaLinesDeletePoint()
{
	if (m_line.size())
		m_line.clear();
	if (m_perLine.size())
		m_perLine.clear();
}

void CmalaLinesDeletePoint::LButtonDown(UINT nFlags, malaPoint point)
{
	if (!m_Selected&&!callSel)
		m_SelectLine.LButtonDown(nFlags, point);
	else
	{
		malaLogic math;
		m_Pos = math.getPointPosInLine(point, m_line);
		if (m_Pos >= 0)
		{
			for (size_t i = 0; i < m_line.size(); i++)
			{
				if (i!=m_Pos)
					m_perLine.push_back(m_line[i]);	
			}

			CLineIO lio;
			lio.lineUpdate(m_perLine, m_linepro, mPath);

			m_line.clear();
			m_SelectLine.m_Selected = FALSE;
			mBaseView->Invalidate(TRUE);//+
			callSel = true;
		}
	}
}

void CmalaLinesDeletePoint::LButtonUp(UINT nFlags, malaPoint point)
{
	if (!m_Selected&&!callSel)
		m_SelectLine.LButtonUp(nFlags, point);

	m_Selected = m_SelectLine.m_Selected;
	if (m_Selected)
	{
		m_line = m_SelectLine.mLine;
		m_linepro = m_SelectLine.mLinePro;
	}
}

void CmalaLinesDeletePoint::MouseMove(UINT nFlags, malaPoint point)
{
	if (!m_Selected&&!callSel)
		m_SelectLine.MouseMove(nFlags, point);
}

/*
* 删除线实现
*/
CmalaLinesDelete::CmalaLinesDelete(CView* mView, malaScreen *pScreen, CString &fileFullPath)
{
	mBaseView = mView;
	mPath = fileFullPath;
	m_Screen = pScreen;
	CmalaLinesSelect obj(mView, pScreen, fileFullPath);
	m_SelectLine = obj;
	m_Selected = FALSE;
}

CmalaLinesDelete::~CmalaLinesDelete()
{
	if (mSLine.size())
		mSLine.clear();
}

void CmalaLinesDelete::LButtonDown(UINT nFlags, malaPoint point)
{
	if (!m_Selected)
		m_SelectLine.LButtonDown(nFlags, point);
}

void CmalaLinesDelete::LButtonUp(UINT nFlags, malaPoint point)
{
	if (!m_Selected)
		m_SelectLine.LButtonUp(nFlags, point);

	m_Selected = m_SelectLine.m_Selected;

	if (m_Selected)
	{
		this->mSLine = m_SelectLine.mLine;
		this->mSLinePro = m_SelectLine.mLinePro;

		if (MessageBox(mBaseView->m_hWnd, L"删除后将无法恢复，确定删除吗？", L"警告", MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			//feature.LineDelete(m_linepro.LineID);
			CLineIO lio;
			lio.lineDelete(mSLinePro.lineId,mPath);
			mBaseView->Invalidate(TRUE);
		}
		
		mSLine.clear();
		m_Selected = FALSE;
		m_SelectLine.m_Selected = FALSE;
	}

}

void CmalaLinesDelete::MouseMove(UINT nFlags, malaPoint point)
{
	if (!m_Selected)
		m_SelectLine.MouseMove(nFlags, point);
}
