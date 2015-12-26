#include "stdafx.h"
#include "_malaDialogs.h"
#include "DialogPointInput.h"
#include "DialogNewPointFile.h"

/*
* 输入点的对话框实现
*/
bool maladialogsdll dlgInputPoint(malaPointPro& paramPointPro)
{
	CDialogPointInput dlg;
	if (IDOK==dlg.DoModal())
	{
		paramPointPro.pointStyle = dlg.mPointStyle;
		paramPointPro.pointLayer = dlg.mPointLayer;
		paramPointPro.pointRadio = dlg.mPointRadio;
		paramPointPro.pointColor = dlg.mPointColor;
		return true;
	}
	return false;
}
/*
* 新建工程对话框实现
*/
bool maladialogsdll dlgNewPrj(CString &paramPrjPath, CString&prjName, CString&prjExt)
{
	CFileDialog prjDlg(FALSE, L"mpj", L"我的工程.mpj", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"工程文件(*.mpj)|*mpj||");
	prjDlg.m_ofn.lpstrTitle = L"设置工程名称";
	if (IDOK == prjDlg.DoModal())
	{
		paramPrjPath = prjDlg.GetPathName();
		prjName = prjDlg.GetFileName();
		prjExt = prjDlg.GetFileExt();
		return true;
	}
	else
	{
		paramPrjPath = L"";
		prjName = L"";
		prjExt = L"";
		return false;
	}
}

/*
* 打开工程对话框实现
*/
bool maladialogsdll dlgOpenPrj(CString &paramPrjPath)
{
	CFileDialog prjDlg(TRUE, L"mpj", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"工程文件(*.mpj)|*mpj||");
	prjDlg.m_ofn.lpstrTitle = L"打开工程文件";
	if (IDOK == prjDlg.DoModal())
	{
		paramPrjPath = prjDlg.GetPathName();
		return true;
	}
	else
	{
		paramPrjPath = L"";
		return false;
	}
}

/*
* 新建点文件对话框实现
*/
bool maladialogsdll dlgNewPointFile(CString &pointName)
{
	CDialogNewPointFile dlg;
	if (IDOK == dlg.DoModal())
	{
		pointName = dlg.mPointFileName;
		return true;
	}
	return false;
}