#pragma once
#include "afxwin.h"


// GaussNoiseDlg 对话框

class GaussNoiseDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GaussNoiseDlg)

public:
	GaussNoiseDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~GaussNoiseDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAUSS_NOISE };
#endif

	double mu;
	double sigmaSquare;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit edit_avg;
	CEdit edit_var;
	virtual BOOL OnInitDialog();
};
