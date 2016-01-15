#include "stdafx.h"
#include "_malaPolygon.h"
#include "_malaDialogs.h"
#include "_malaIO.h"

/*
* 输入区实现
*/
CmalaPolysInput::CmalaPolysInput(CView* mView, malaScreen *pScreen, CString &fileFullPath)
{
	mBaseView = mView;
	mScreen = pScreen;
	mPath = fileFullPath;
	mIsDraw = false;
	GetPolyPro();//获取输入区的属性
}
CmalaPolysInput::~CmalaPolysInput()
{
	if (mPoly.size())
		mPoly.clear();
}
void CmalaPolysInput::GetPolyPro()
{
	if (dlgInputPoly(mPolyPro) == FALSE)
	{
		mPolyPro.polyStyle = 0;
		mPolyPro.borderColor = RGB(0, 0, 0);
		mPolyPro.borderStyle = 0;
		mPolyPro.fillStyle = 0;
		mPolyPro.fillColor = RGB(0, 0, 0);
	}
}
void CmalaPolysInput::LButtonDown(UINT nFlags, malaPoint point)
{
	mPoly.push_back(point);
	mPerPoint = point;
	mIsDraw = true;
}

void CmalaPolysInput::MouseMove(UINT nFlags, malaPoint point)
{
	if (mIsDraw)
	{
		vector<malaPoint>tpPoly;
		tpPoly = mPoly;
		tpPoly.push_back(mPerPoint);
		malaCDC mycdc(mBaseView,*mScreen);
		mycdc.polyDrawAutoX(tpPoly, mPolyPro);
		tpPoly.pop_back();
		tpPoly.push_back(point);
		mycdc.polyDrawAutoX(tpPoly, mPolyPro);
		mPerPoint = point;
		tpPoly.clear();
	}

}

void CmalaPolysInput::RButtonDown(UINT nFlags, malaPoint point)
{
	mIsDraw = false;
	mPoly.push_back(point);
	malaCDC mycdc(mBaseView, *mScreen);
	mycdc.polyDrawAuto(mPoly, mPolyPro);
	//保存点
	if (mPoly.size()>=2)
	{
		CPolyIO pio;
		pio.polyAdd(mPoly, mPolyPro, mPath);
	}
	mPoly.clear();
}

/*
* 选择区实现
*/
vector<malaPoint> CmalaPolysSelect::mSPoly;
malaPolyPro CmalaPolysSelect::mSPolyPro;
CView* CmalaPolysSelect::m_StaticView = NULL;
malaScreen* CmalaPolysSelect::m_Screen = NULL;

CmalaPolysSelect::CmalaPolysSelect()
{

}

CmalaPolysSelect::CmalaPolysSelect(CView* mView, malaScreen *pScreen, CString &fileFullPath)
{
	mBaseView = mView;
	m_StaticView = mView;
	mPath = fileFullPath;

	m_bDraw = FALSE;
	m_Selected = FALSE;
	m_Screen = pScreen;
}

CmalaPolysSelect::~CmalaPolysSelect()
{

}

void CmalaPolysSelect::LButtonDown(UINT nFlags, malaPoint point)
{
	m_bDraw = TRUE;
	m_ptOrigin = m_perPoint = point;
}

void CmalaPolysSelect::LButtonUp(UINT nFlags, malaPoint point)
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
	//先获取所有符合条件的区
	CPolyIO pio;
	vector<malaPolyFile>allPolys;
	pio.getAllPolys(*m_Screen, allPolys, mPath);
	//再查找是否被选中
	malaLogic tlog;
	for (size_t j = 0; j < allPolys.size(); j++)
	{
		if ((allPolys[j].mPolyPro.polyStyle == 0 && tlog.isPolyInRect(m_rect, allPolys[j].mPoly)) || (allPolys[j].mPolyPro.polyStyle == 1 && tlog.isRectIntersect(m_rect,tlog.getRect(allPolys[j].mPoly))))
		{
			mSPoly = allPolys[j].mPoly;
			mSPolyPro = allPolys[j].mPolyPro;

			SetTimer(mBaseView->m_hWnd, 1, 500, TimerPoly);
			if (MessageBox(mBaseView->m_hWnd, L"选择该区吗?", L"提示", MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				malaCDC dc(mBaseView, *m_Screen);
				dc.polyDrawAuto(mSPoly, mSPolyPro);
				KillTimer(mBaseView->m_hWnd, 1);
				//绘制选中标志
				for (size_t k = 0; k < mSPoly.size(); k++)
				{
					malaPointPro tpPointPro;
					tpPointPro.pointRadio = mSPolyPro.borderWidth + 2;
					tpPointPro.pointColor = mSPolyPro.borderColor;

					dc.drawSelectRectPoint(mSPoly[k], tpPointPro);
				}
				if (mSPolyPro.polyStyle == 1)
				{
					malaPolyPro tpolypro = mSPolyPro;
					tpolypro.fillColor = RGB(0, 139, 139);
					tpolypro.borderColor = RGB(255, 0, 0);
					tpolypro.borderStyle = 0;
					tpolypro.fillStyle = 6;
					dc.polyDraw(mSPoly, tpolypro);
				}
				m_Selected = TRUE;
				break;
			}
			KillTimer(mBaseView->m_hWnd, 1);
		}
	}
}

void CmalaPolysSelect::MouseMove(UINT nFlags, malaPoint point)
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
* 移动区实现
*/
CmalaPolysMove::CmalaPolysMove(CView* mView, malaScreen *pScreen, CString &fileFullPath)
{
	mBaseView = mView;
	mPath = fileFullPath;
	mScreen = pScreen;
	CmalaPolysSelect obj(mView, pScreen, fileFullPath);
	mSelectPoly = obj;
	mSelected = FALSE;
	mIsDraw = FALSE;
}

CmalaPolysMove::~CmalaPolysMove()
{
	if (mSPoly.size())
		mSPoly.clear();
}

void CmalaPolysMove::LButtonDown(UINT nFlags, malaPoint point)
{
	if (!mSelected)
		mSelectPoly.LButtonDown(nFlags, point);
	else
	{
		mIsDraw = TRUE;
		mPointOri = point;
	}
}

void CmalaPolysMove::LButtonUp(UINT nFlags, malaPoint point)
{
	if (!mSelected)
		mSelectPoly.LButtonUp(nFlags, point);
	else
	{
		CPolyIO lio;
		lio.polyUpdate(mPerPoly, mSPolyPro, mPath);
		mBaseView->Invalidate(TRUE);
		mIsDraw = FALSE;
		mSelected = FALSE;
		mSelectPoly.m_Selected = FALSE;
		mSPoly.clear();
	}

	mSelected = mSelectPoly.m_Selected;
	if (mSelected)
	{
		this->mSPoly = mSelectPoly.mSPoly;
		this->mSPolyPro = mSelectPoly.mSPolyPro;
		mPerPoly = mSPoly;
	}

}

void CmalaPolysMove::MouseMove(UINT nFlags, malaPoint point)
{
	if (!mSelected)
		mSelectPoly.MouseMove(nFlags, point);
	else if (mIsDraw)
	{
		malaCDC dc(mBaseView, *mScreen);
		dc.polyDrawAutoX(mPerPoly, mSPolyPro);
		for (size_t i = 0; i < mPerPoly.size(); i++)
		{
			mPerPoly[i].x = mSPoly[i].x + point.x - mPointOri.x;
			mPerPoly[i].y = mSPoly[i].y + point.y - mPointOri.y;
		}
		dc.polyDrawAutoX(mPerPoly, mSPolyPro);
	}
}