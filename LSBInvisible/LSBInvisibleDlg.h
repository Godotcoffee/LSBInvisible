
// LSBInvisibleDlg.h : 头文件
//

#pragma once
#include "afxwin.h"

#include "MyBMPAlter.h"


// CLSBInvisibleDlg 对话框
class CLSBInvisibleDlg : public CDialogEx
{
// 构造
public:
	CLSBInvisibleDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LSBINVISIBLE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CMenu menu_dlg;
	afx_msg void OnClickReadImage();

/* 其它变量 */
private:
	const int CONTENT_LIMIT = 0;		// 输入框的最大长度，0表示无限制
	const int SCROLLBAR_V_LINE = 20;	// 垂直滚动条行的长度
	const int SCROLLBAR_H_LINE = 20;	// 水平滚动条行的长度
	const int SCROLLBAR_V_PAGE = 50;	// 垂直滚动条页的长度
	const int SCROLLBAR_H_PAGE = 50;	// 水平滚动条页的长度

	void init();
	void initOrigin(const MyBMPAlter &bmp);
	void initResult(const MyBMPAlter &bmp);
	void transBmp(CBitmap &cbitmap, const MyBMPAlter &myBmp, CDC &pDC);
	void paintImage(CDC &dc, CRect rect, CBitmap &cbitmap, int x, int y);

	// 下面函数用于\r\n与\n的相互转换
	CString transCRLFToLF(const CString &cstr);
	CString transLFToCRLF(const CString &cstr);

	COLORREF usedByteClr;
	bool saveImgEnable;

	MyBMPAlter originBmp;
	CBitmap originCBitmap;
	CRect maxOriginRect;
	CRect originRect;					// 原始图像绘制区域
	CRect vsbOriginRect;				// 原始图像垂直滚动条位置
	CRect hsbOriginRect;				// 原始图像水平滚动条位置
	int originX;
	int originY;

	MyBMPAlter resultBmp;
	CBitmap resultCBitmap;
	CRect maxResultRect;
	CRect resultRect;					// 处理后图像绘制区域
	CRect vsbResultRect;				// 处理后图像垂直滚动条位置
	CRect hsbResultRect;				// 处理后图像水平滚动条位置
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
