
// LSBInvisibleDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"

#include "MyBMPAlter.h"


// CLSBInvisibleDlg �Ի���
class CLSBInvisibleDlg : public CDialogEx
{
// ����
public:
	CLSBInvisibleDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LSBINVISIBLE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CMenu menu_dlg;
	afx_msg void OnClickReadImage();

/* �������� */
private:
	const int CONTENT_LIMIT = 0;		// ��������󳤶ȣ�0��ʾ������
	const int SCROLLBAR_V_LINE = 20;	// ��ֱ�������еĳ���
	const int SCROLLBAR_H_LINE = 20;	// ˮƽ�������еĳ���
	const int SCROLLBAR_V_PAGE = 50;	// ��ֱ������ҳ�ĳ���
	const int SCROLLBAR_H_PAGE = 50;	// ˮƽ������ҳ�ĳ���

	void init();
	void initOrigin(const MyBMPAlter &bmp);
	void initResult(const MyBMPAlter &bmp);
	void transBmp(CBitmap &cbitmap, const MyBMPAlter &myBmp, CDC &pDC);
	void paintImage(CDC &dc, CRect rect, CBitmap &cbitmap, int x, int y);

	// ���溯������\r\n��\n���໥ת��
	CString transCRLFToLF(const CString &cstr);
	CString transLFToCRLF(const CString &cstr);

	COLORREF usedByteClr;
	bool saveImgEnable;

	MyBMPAlter originBmp;
	CBitmap originCBitmap;
	CRect maxOriginRect;
	CRect originRect;					// ԭʼͼ���������
	CRect vsbOriginRect;				// ԭʼͼ��ֱ������λ��
	CRect hsbOriginRect;				// ԭʼͼ��ˮƽ������λ��
	int originX;
	int originY;

	MyBMPAlter resultBmp;
	CBitmap resultCBitmap;
	CRect maxResultRect;
	CRect resultRect;					// �����ͼ���������
	CRect vsbResultRect;				// �����ͼ��ֱ������λ��
	CRect hsbResultRect;				// �����ͼ��ˮƽ������λ��
	int resultX;
	int resultY;

public:
	CStatic label_totByte;
	CStatic label_usedByte;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CEdit edit_content;
	afx_msg void OnEnChangeEditContent();
	afx_msg void OnUpdateSaveImage(CCmdUI *pCmdUI);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnBnClickedButtonChooseAll();
	CButton btn_chooseAll;
	CScrollBar vsb_origin;
	CScrollBar hsb_origin;
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CScrollBar vsb_result;
	CScrollBar hsb_result;
	CButton btn_insert;
	afx_msg void OnBnClickedButtonInsert();
	afx_msg void OnMenuSaveImage();
	afx_msg void OnBnClickedButtonGet();
	CButton btn_getMsg;
	CEdit edit_messageShow;
	CButton btn_clipboard;
	afx_msg void OnBnClickedButtonClipboard();
	afx_msg void OnMenuExit();
	afx_msg void OnMenuGaussNoise();
};
