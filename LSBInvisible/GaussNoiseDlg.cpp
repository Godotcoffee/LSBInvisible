// GaussNoiseDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LSBInvisible.h"
#include "GaussNoiseDlg.h"
#include "afxdialogex.h"


// GaussNoiseDlg 对话框

IMPLEMENT_DYNAMIC(GaussNoiseDlg, CDialogEx)

GaussNoiseDlg::GaussNoiseDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GAUSS_NOISE, pParent)
{

}

GaussNoiseDlg::~GaussNoiseDlg()
{
}

void GaussNoiseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_GAUSS_AVG, edit_avg);
	DDX_Control(pDX, IDC_EDIT_GAUSS_VAR, edit_var);
}


BEGIN_MESSAGE_MAP(GaussNoiseDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &GaussNoiseDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// GaussNoiseDlg 消息处理程序

BOOL GaussNoiseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	edit_avg.SetWindowText(_T("0"));
	edit_var.SetWindowText(_T("50"));

	return TRUE;  // return TRUE unless you set the focus to a control
}

void GaussNoiseDlg::OnBnClickedOk()
{
	CString cstr;
	edit_avg.GetWindowText(cstr);
	mu = _ttof(cstr);
	edit_var.GetWindowText(cstr);
	sigmaSquare = _ttof(cstr);
	CDialogEx::OnOK();
}

