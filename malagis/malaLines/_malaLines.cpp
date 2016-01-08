#include "stdafx.h"
#include "_malaLines.h"
#include "_malaDialogs.h"
#include "_malaIO.h"

/*
* 输入点
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
	
	/*CoConnect conn(m_DB.szDsn, m_DB.szName, m_DB.szPassword);
	CoFeatureset feature;
	if (m_Line.size())
	{
		feature.Open(&conn, m_ActiveTable);
		feature.LineAdd(m_Line, m_LinePro);
		m_Line.clear();
	}*/
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