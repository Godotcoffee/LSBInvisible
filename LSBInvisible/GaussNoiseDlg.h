#pragma once
#include "afxwin.h"


// GaussNoiseDlg �Ի���

class GaussNoiseDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GaussNoiseDlg)

public:
	GaussNoiseDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~GaussNoiseDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAUSS_NOISE };
#endif

	double mu;
	double sigmaSquare;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit edit_avg;
	CEdit edit_var;
	virtual BOOL OnInitDialog();
};
