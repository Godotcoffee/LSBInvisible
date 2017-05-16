
// LSBInvisibleDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "afxdialogex.h"

#include <conio.h>
#include <sstream>
#include <algorithm>

#include "LSBInvisible.h"
#include "LSBInvisibleDlg.h"
#include "MessageHidden.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define CONSOLE_DEBUG


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLSBInvisibleDlg 对话框



CLSBInvisibleDlg::CLSBInvisibleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LSBINVISIBLE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLSBInvisibleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LABEL_TOTAL_BYTE, label_totByte);
	DDX_Control(pDX, IDC_LABEL_USED_BYTE, label_usedByte);
	DDX_Control(pDX, IDC_EDIT_CONTENT, edit_content);
	DDX_Control(pDX, IDC_BUTTON_CHOOSE_ALL, btn_chooseAll);
	DDX_Control(pDX, IDC_SCROLLBAR_V_ORIGIN, vsb_origin);
	DDX_Control(pDX, IDC_SCROLLBAR_H_ORIGIN, hsb_origin);
	DDX_Control(pDX, IDC_SCROLLBAR_V_RESULT, vsb_result);
	DDX_Control(pDX, IDC_SCROLLBAR_H_RESULT, hsb_result);
	DDX_Control(pDX, IDC_BUTTON_INSERT, btn_insert);
	DDX_Control(pDX, IDC_BUTTON_GET, btn_getMsg);
	DDX_Control(pDX, IDC_EDIT_MESSAGE, edit_messageShow);
}

BEGIN_MESSAGE_MAP(CLSBInvisibleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_32771, &CLSBInvisibleDlg::OnClickReadImage)
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_EDIT_CONTENT, &CLSBInvisibleDlg::OnEnChangeEditContent)
	ON_UPDATE_COMMAND_UI(ID_MENU_SAVE_IMAGE, &CLSBInvisibleDlg::OnUpdateSaveImage)
	ON_WM_INITMENUPOPUP()
	ON_BN_CLICKED(IDC_BUTTON_CHOOSE_ALL, &CLSBInvisibleDlg::OnBnClickedButtonChooseAll)
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON_INSERT, &CLSBInvisibleDlg::OnBnClickedButtonInsert)
	ON_COMMAND(ID_MENU_SAVE_IMAGE, &CLSBInvisibleDlg::OnMenuSaveImage)
	ON_BN_CLICKED(IDC_BUTTON_GET, &CLSBInvisibleDlg::OnBnClickedButtonGet)
END_MESSAGE_MAP()

// 下面函数代码是拷贝的,为了让对话框模式能响应菜单弹出事件
void CLSBInvisibleDlg::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	ASSERT(pPopupMenu != NULL);
	// Check the enabled state of various menu items.

	CCmdUI state;
	state.m_pMenu = pPopupMenu;
	ASSERT(state.m_pOther == NULL);
	ASSERT(state.m_pParentMenu == NULL);

	// Determine if menu is popup in top-level menu and set m_pOther to
	// it if so (m_pParentMenu == NULL indicates that it is secondary popup).
	HMENU hParentMenu;
	if (AfxGetThreadState()->m_hTrackingMenu == pPopupMenu->m_hMenu)
		state.m_pParentMenu = pPopupMenu;    // Parent == child for tracking popup.
	else if ((hParentMenu = ::GetMenu(m_hWnd)) != NULL)
	{
		CWnd* pParent = this;
		// Child Windows don't have menus--need to Go to the top!
		if (pParent != NULL &&
			(hParentMenu = ::GetMenu(pParent->m_hWnd)) != NULL)
		{
			int nIndexMax = ::GetMenuItemCount(hParentMenu);
			for (int nIndex = 0; nIndex < nIndexMax; nIndex++)
			{
				if (::GetSubMenu(hParentMenu, nIndex) == pPopupMenu->m_hMenu)
				{
					// When popup is found, m_pParentMenu is containing menu.
					state.m_pParentMenu = CMenu::FromHandle(hParentMenu);
					break;
				}
			}
		}
	}

	state.m_nIndexMax = pPopupMenu->GetMenuItemCount();
	for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax;
		state.m_nIndex++)
	{
		state.m_nID = pPopupMenu->GetMenuItemID(state.m_nIndex);
		if (state.m_nID == 0)
			continue; // Menu separator or invalid cmd - ignore it.

		ASSERT(state.m_pOther == NULL);
		ASSERT(state.m_pMenu != NULL);
		if (state.m_nID == (UINT)-1)
		{
			// Possibly a popup menu, route to first item of that popup.
			state.m_pSubMenu = pPopupMenu->GetSubMenu(state.m_nIndex);
			if (state.m_pSubMenu == NULL ||
				(state.m_nID = state.m_pSubMenu->GetMenuItemID(0)) == 0 ||
				state.m_nID == (UINT)-1)
			{
				continue;       // First item of popup can't be routed to.
			}
			state.DoUpdate(this, TRUE);   // Popups are never auto disabled.
		} else
		{
			// Normal menu item.
			// Auto enable/disable if frame window has m_bAutoMenuEnable
			// set and command is _not_ a system command.
			state.m_pSubMenu = NULL;
			state.DoUpdate(this, FALSE);
		}

		// Adjust for menu deletions and additions.
		UINT nCount = pPopupMenu->GetMenuItemCount();
		if (nCount < state.m_nIndexMax)
		{
			state.m_nIndex -= (state.m_nIndexMax - nCount);
			while (state.m_nIndex < nCount &&
				pPopupMenu->GetMenuItemID(state.m_nIndex) == state.m_nID)
			{
				state.m_nIndex++;
			}
		}
		state.m_nIndexMax = nCount;
	}
}


// 初始化
void CLSBInvisibleDlg::init()
{
	saveImgEnable = false;
	usedByteClr = RGB(0, 0, 0);

	menu_dlg.LoadMenuW(IDR_MENU1);
	SetMenu(&menu_dlg);

	edit_content.LimitText(CONTENT_LIMIT);

	vsb_origin.GetWindowRect(&vsbOriginRect);
	hsb_origin.GetWindowRect(&hsbOriginRect);
	vsb_result.GetWindowRect(&vsbResultRect);
	hsb_result.GetWindowRect(&hsbResultRect);
	ScreenToClient(&vsbOriginRect);
	ScreenToClient(&hsbOriginRect);
	ScreenToClient(&vsbResultRect);
	ScreenToClient(&hsbResultRect);

	originRect = maxOriginRect = CRect(hsbOriginRect.left, vsbOriginRect.top, vsbOriginRect.left, hsbOriginRect.top);
	originX = originY = 0;

	resultRect = maxResultRect = CRect(hsbResultRect.left, vsbResultRect.top, vsbResultRect.left, hsbResultRect.top);
	resultX = resultY = 0;
}

// 将MyBMPAlter转成CBITMAP
void CLSBInvisibleDlg::transBmp(CBitmap &cbitmap, const MyBMPAlter &myBmp, CDC &pDC)
{
	int width = myBmp.getInfoHeader().biWidth;
	int height = myBmp.getInfoHeader().biHeight;
	bool reversed = height < 0;
	height = std::abs(height);
	int bitPerPixel = myBmp.getInfoHeader().biBitCount;
	const RGBQUAD *quad = myBmp.getQuad();
	int quadSize = myBmp.getQuadSize();
	const BYTE *imgData = myBmp.getImageData();
	int imgSize = myBmp.getImageSize();
	int extRowLen = (width * bitPerPixel + 31) >> 5 << 2;

	CDC dcMem;
	cbitmap.DeleteObject();
	cbitmap.CreateCompatibleBitmap(&pDC, width, height);
	dcMem.CreateCompatibleDC(&pDC);

	CBitmap *oldBitmap = dcMem.SelectObject(&cbitmap);

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			if (bitPerPixel <= 8) {
				int bIdx = j * bitPerPixel / 8;
				int bOffset = j * bitPerPixel % 8;
				int bPos = i * extRowLen + bIdx;
				if (bPos < imgSize) {
					int quadIdx = (imgData[bPos] >> bOffset) & ((1 << bitPerPixel) - 1);
					if (quadIdx >= 0 && quadIdx < quadSize) {
						RGBQUAD q = quad[quadIdx];
						if (reversed) {
							dcMem.SetPixel(j, i, RGB(q.rgbRed, q.rgbGreen, q.rgbBlue));
						} else {
							dcMem.SetPixel(j, height - 1 - i, RGB(q.rgbRed, q.rgbGreen, q.rgbBlue));
						}
					}
				}
			} else if (bitPerPixel == 24) {
				int bWidth = bitPerPixel / 8;
				int bIdx = j * bWidth + i * extRowLen;
				if (bIdx + bWidth - 1 < imgSize) {
					unsigned int b = imgData[bIdx];
					unsigned int g = imgData[bIdx + 1];
					unsigned int r = imgData[bIdx + 2];
					if (reversed) {
						dcMem.SetPixel(j, i, RGB(r, g, b));
					} else {
						dcMem.SetPixel(j, height - 1 - i, RGB(r, g, b));
					}
				}
			}
		}
	}
	dcMem.SelectObject(oldBitmap);
	dcMem.DeleteDC();
}

void CLSBInvisibleDlg::paintImage(CDC &dc, CRect rect, CBitmap &cbitmap, int x, int y)
{
	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);
	CBitmap *oldBitmap = dcMem.SelectObject(&cbitmap);
	dcMem.GetPixel(0, 0);

	dc.BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &dcMem, x, y, SRCCOPY);

	dcMem.SelectObject(oldBitmap);
	dcMem.DeleteDC();
}

// CLSBInvisibleDlg 消息处理程序

BOOL CLSBInvisibleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
#ifdef CONSOLE_DEBUG
	AllocConsole();
#endif

	init();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLSBInvisibleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLSBInvisibleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		
		if (originBmp.checkIsRead()) {
			paintImage(dc, originRect, originCBitmap, originX, originY);
		}
		if (resultBmp.checkIsRead()) {
			paintImage(dc, resultRect, resultCBitmap, resultX, resultY);
		}
		
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLSBInvisibleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 点击打开图片按钮事件
void CLSBInvisibleDlg::OnClickReadImage()
{
	CFileDialog fileDlg(true, _T("txt"), NULL, 0, _T("位图文件(*.bmp)|*.bmp||"), this);
	if (fileDlg.DoModal() == IDOK) {
		CString filePath = fileDlg.GetPathName();
		MyBMPAlter newBMP((CT2A(filePath)));
		if (!newBMP) {
			MessageBox(_T("打开图片失败"), _T("错误"), MB_OK);
		} else {
			originBmp = newBMP;
			resultBmp = MyBMPAlter();
			// 将MyBMPAlter转换成内存中的CBitmap保存
			transBmp(originCBitmap, originBmp, *GetWindowDC());
			// 获得图像的长宽
			int width = originBmp.getInfoHeader().biWidth;
			int height = originBmp.getInfoHeader().biHeight;

			// 计算原图像显示的范围，maxOriginRect为能显示的最大范围
			originRect.right = min(maxOriginRect.left + width, maxOriginRect.right);
			originRect.bottom = min(maxOriginRect.top + height, maxOriginRect.bottom);

			// 计算滚动条的位置
			vsbOriginRect.OffsetRect(originRect.right - vsbOriginRect.left, 0);
			vsbOriginRect.top = originRect.top;
			vsbOriginRect.bottom = originRect.bottom;
			hsbOriginRect.OffsetRect(0, originRect.bottom - hsbOriginRect.top);
			hsbOriginRect.left = originRect.left;
			hsbOriginRect.right = originRect.right;

			// 移动滚动条
			vsb_origin.MoveWindow(&vsbOriginRect);
			hsb_origin.MoveWindow(&hsbOriginRect);

			// 显示滚动条
			vsb_origin.ShowWindow(TRUE);
			hsb_origin.ShowWindow(TRUE);

			// 隐藏滚动条
			vsb_result.ShowWindow(FALSE);
			hsb_result.ShowWindow(FALSE);

			// 原图像绘制原点
			originX = originY = 0;

			// 调整滚动条
			SCROLLINFO vsi, hsi;
			vsi.fMask = SIF_ALL;
			vsi.nMin = 0;
			vsi.nMax = max(height - originRect.Height(), 0);
			vsi.nPage = SCROLLBAR_V_PAGE;
			vsi.nPos = 0;

			hsi.fMask = SIF_ALL;
			hsi.nMin = 0;
			hsi.nMax = max(width - originRect.Width(), 0);
			hsi.nPage = SCROLLBAR_H_PAGE;
			hsi.nPos = 0;
			vsb_origin.SetScrollInfo(&vsi);
			hsb_origin.SetScrollInfo(&hsi);

			// 初始化控件
			edit_content.EnableWindow();
			btn_chooseAll.EnableWindow();
			btn_insert.EnableWindow();
			btn_getMsg.EnableWindow();
			edit_messageShow.SetWindowText(_T(""));

			// 禁用保存
			saveImgEnable = false;

#ifdef CONSOLE_DEBUG
			std::ostringstream os;
			originBmp.outputInfo(os);
			_cprintf("%s\n%s\n", (const char *) CT2A(filePath), os.str().c_str());
#endif

			// 显示能存储的字节数(位数/8)
			CString cstr;
			cstr.Format(_T("%d"), originBmp.getImageSize() >> 3);
			label_totByte.SetWindowText(cstr);

			label_usedByte.SetWindowText(_T("0"));
			
			edit_content.SetWindowText(_T(""));

			Invalidate();
			UpdateWindow();
		}

	}

	SetMenu(&menu_dlg);	// 返回后菜单栏会失焦，通过重新设置菜单可以恢复。PS：不清楚有什么影响
}

// 保存图片
void CLSBInvisibleDlg::OnMenuSaveImage()
{
	if (!resultBmp.checkIsRead()) {
		return;
	}
	CFileDialog fileDlg(false, _T("bmp"), NULL, 0, _T("位图文件(*.bmp)|*.bmp||"), this);
	if (fileDlg.DoModal() == IDOK) {
		CString filePathName = fileDlg.GetPathName();
		resultBmp.saveAsFile(CT2A(filePathName));
	}
	SetMenu(&menu_dlg);	// 同上
}


// 利用消息事件来实现CStatic的颜色变换
HBRUSH CLSBInvisibleDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (nCtlColor == CTLCOLOR_STATIC) {
		switch (pWnd->GetDlgCtrlID()) {
		case IDC_LABEL_USED_BYTE:
			pDC->SetTextColor(usedByteClr);
			break;
		}
	}
	return hbr;
}

// 插入消息编辑框的变化消息事件
void CLSBInvisibleDlg::OnEnChangeEditContent()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	// 先转换成多字节模式,以正确地处理中文字符
	CString content;
	edit_content.GetWindowTextW(content);
	int length = ((CStringA)CT2A(content)).GetLength();

	// 如果使用的字节数超过总可使用的字节数,则显示为红色
	if (length > originBmp.getImageSize() >> 3) {
		usedByteClr = RGB(255, 0, 0);
	} else {
		usedByteClr = RGB(0, 0, 0);
	}

	// 改变已用字节数
	CString cstr;
	cstr.Format(_T("%d"), length);
	label_usedByte.SetWindowTextW(cstr);
}

// 保存图片菜单项是否可用
void CLSBInvisibleDlg::OnUpdateSaveImage(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(saveImgEnable);
}


void CLSBInvisibleDlg::OnBnClickedButtonChooseAll()
{
	edit_content.SetSel(0, -1);
	edit_content.SetFocus();
}

// 嵌入信息
void CLSBInvisibleDlg::OnBnClickedButtonInsert()
{
	CString cstr;
	edit_content.GetWindowText(cstr);
	CStringA cstra = CT2A(cstr);		// 获取多字节模式的字符串
	int imgSize = originBmp.getImageSize();
	int totByte = imgSize >> 3;
	int usedByte = cstra.GetLength();
	if (usedByte > totByte) {
		MessageBox(_T("超过可用最大字节数"), _T("错误"), MB_OK);
		return;
	}

#ifdef CONSOLE_DEBUG
	_cprintf("%d", cstra.GetLength());
#endif
	BYTE *newImgData;
	if ((newImgData = new BYTE[imgSize]) == NULL) {
		CString errorMsg;
		errorMsg.Format(_T("无法分配%d字节内存"), imgSize);
		MessageBox(errorMsg, _T("错误"), MB_OK);
		return;
	}
	memcpy(newImgData, originBmp.getImageData(), imgSize * sizeof(BYTE));

	// 嵌入
	MessageHidden::hiddenMessageInLSB(newImgData, imgSize, (BYTE *) cstra.GetString(), cstra.GetLength());

	resultBmp = MyBMPAlter(
		originBmp.getFileHeader(), originBmp.getInfoHeader(), 
		originBmp.getQuad(), originBmp.getQuadSize(), 
		newImgData, imgSize);
	delete[] newImgData;		// 释放

	transBmp(resultCBitmap, resultBmp, *GetWindowDC());
	int width = resultBmp.getInfoHeader().biWidth;
	int height = resultBmp.getInfoHeader().biHeight;

	// 计算处理后图像的绘制区域
	resultRect.right = min(maxResultRect.left + width, maxResultRect.right);
	resultRect.bottom = min(maxResultRect.top + height, maxResultRect.bottom);

	// 计算滚动条位置
	vsbResultRect.OffsetRect(resultRect.right - vsbResultRect.left, 0);
	vsbResultRect.top = resultRect.top;
	vsbResultRect.bottom = resultRect.bottom;
	hsbResultRect.OffsetRect(0, resultRect.bottom - hsbResultRect.top);
	hsbResultRect.left = resultRect.left;
	hsbResultRect.right = resultRect.right;

	// 移动滚动条
	vsb_result.MoveWindow(&vsbResultRect);
	hsb_result.MoveWindow(&hsbResultRect);

	// 显示滚动条
	vsb_result.ShowWindow(TRUE);
	hsb_result.ShowWindow(TRUE);

	// 设置滚动条参数
	SCROLLINFO vsi;
	vsi.fMask = SIF_ALL;
	vsi.nMin = 0;
	vsi.nMax = max(height - resultRect.Height(), 0);
	vsi.nPage = SCROLLBAR_V_PAGE;
	vsi.nPos = 0;
	vsb_result.SetScrollInfo(&vsi);

	SCROLLINFO hsi;
	hsi.fMask = SIF_ALL;
	hsi.nMin = 0;
	hsi.nMax = max(width - resultRect.Width(), 0);
	hsi.nPage = SCROLLBAR_H_PAGE;
	hsi.nPos = 0;
	hsb_result.SetScrollInfo(&hsi);

	resultX = resultY = 0;

	saveImgEnable = true;

	InvalidateRect(&resultRect);
	UpdateWindow();
}


// 获得信息
void CLSBInvisibleDlg::OnBnClickedButtonGet()
{
	if (!originBmp.checkIsRead()) {
		return;
	}
	int imgSize = originBmp.getImageSize();
	BYTE *msgData;
	if ((msgData = new BYTE[imgSize + 1]) == NULL) {
		CString errorMsg;
		errorMsg.Format(_T("无法分配%d字节内存"), imgSize + 1);
		MessageBox(errorMsg, _T("错误"), MB_OK);
		return;
	}
	MessageHidden::getMessageFromLSB(msgData, imgSize + 1, originBmp.getImageData(), imgSize);
	CString msg(msgData);
	delete[] msgData;	// 释放内存

	edit_messageShow.SetWindowText(msg);
}


// 垂直滚动条事件响应
void CLSBInvisibleDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int rangeMin, rangeMax;
	pScrollBar->GetScrollRange(&rangeMin, &rangeMax);
	int oldPos = pScrollBar->GetScrollPos();
	int newPos = nPos;
	switch (nSBCode) {
	case SB_LINEUP:
		newPos = max(oldPos - SCROLLBAR_V_LINE, rangeMin);
		break;
	case SB_LINEDOWN:
		newPos = min(oldPos + SCROLLBAR_V_LINE, rangeMax);
		break;
	case SB_PAGEUP:
		newPos = max(oldPos - SCROLLBAR_V_PAGE, rangeMin);
		break;
	case SB_PAGEDOWN:
		newPos = min(oldPos + SCROLLBAR_V_PAGE, rangeMax);
		break;
	case SB_THUMBTRACK: case SB_THUMBPOSITION:
		newPos = nPos;
		break;
	case SB_ENDSCROLL:
		return;
	}
	pScrollBar->SetScrollPos(newPos);
#ifdef CONSOLE_DEBUG
	//_cprintf("nSBCode:%d newPos:%d\n", nSBCode, newPos);
#endif
	if (pScrollBar == &vsb_origin) {
		originY = newPos;
		InvalidateRect(&originRect, FALSE);
		UpdateWindow();
	} else if (pScrollBar == &vsb_result) {
		resultY = newPos;
		InvalidateRect(&resultRect, FALSE);
		UpdateWindow();
	}

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}

// 水平滚动条事件响应
void CLSBInvisibleDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int rangeMin, rangeMax;
	pScrollBar->GetScrollRange(&rangeMin, &rangeMax);
	int oldPos = pScrollBar->GetScrollPos();
	int newPos = nPos;
	switch (nSBCode) {
	case SB_LINERIGHT:
		newPos = max(oldPos - SCROLLBAR_H_LINE, rangeMin);
		break;
	case SB_LINELEFT:
		newPos = min(oldPos + SCROLLBAR_H_LINE, rangeMax);
		break;
	case SB_PAGERIGHT:
		newPos = max(oldPos - SCROLLBAR_H_PAGE, rangeMin);
		break;
	case SB_PAGELEFT:
		newPos = min(oldPos + SCROLLBAR_H_PAGE, rangeMax);
		break;
	case SB_THUMBTRACK: case SB_THUMBPOSITION:
		newPos = nPos;
		break;
	case SB_ENDSCROLL:
		return;
	}
	pScrollBar->SetScrollPos(newPos);
#ifdef CONSOLE_DEBUG
	//_cprintf("nSBCode:%d newPos:%d\n", nSBCode, newPos);
#endif
	if (pScrollBar == &hsb_origin) {
		originX = newPos;
		InvalidateRect(&originRect, FALSE);
		UpdateWindow();
	} else if (pScrollBar == &hsb_result) {
		resultX = newPos;
		InvalidateRect(&resultRect, FALSE);
		UpdateWindow();
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
