
// DESAlgorithmDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DESAlgorithm.h"
#include "DESAlgorithmDlg.h"
#include "afxdialogex.h"
#include "DESClass.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CDESAlgorithmDlg dialog



CDESAlgorithmDlg::CDESAlgorithmDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DESALGORITHM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDESAlgorithmDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDESAlgorithmDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTNJIAMI, &CDESAlgorithmDlg::OnClickChooseJiamiFile)
	ON_BN_CLICKED(IDC_BTNJIEMI, &CDESAlgorithmDlg::OnClickChooseJiemiFile)
	ON_BN_CLICKED(IDEXCJIAMI, &CDESAlgorithmDlg::ExcJiamiAlgorithm)
	ON_BN_CLICKED(IDEXCJIEMI, &CDESAlgorithmDlg::ExcJiemiAlgorithm)
END_MESSAGE_MAP()


// CDESAlgorithmDlg message handlers

BOOL CDESAlgorithmDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	jiamiEdit = (CEdit *)GetDlgItem(IDC_EDITJIAMI);
	jiemiEdit = (CEdit *)GetDlgItem(IDC_EDITJIEMI);
	jiamiAfterEdit = (CEdit *)GetDlgItem(IDC_EDITJIAMIAFTER);
	jiemiAfterEdit = (CEdit *)GetDlgItem(IDC_EDITJIEMIAFTER);
	btnExcJiami = (CButton *)GetDlgItem(IDEXCJIAMI);
	btnExcJiemi = (CButton *)GetDlgItem(IDEXCJIEMI); 
	keyEdit = (CEdit *)GetDlgItem(IDC_EDITKEY);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDESAlgorithmDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDESAlgorithmDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDESAlgorithmDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CDESAlgorithmDlg::OnClickChooseJiamiFile()
{
	CFileDialog *dialog = new CFileDialog(TRUE, NULL, NULL, OFN_HIDEREADONLY, L"All Files(*.*)|*.*", NULL);
	if (dialog->DoModal()) {
		CString jiamiFilePath = dialog->GetPathName();
		jiamiEdit->SetWindowTextW(jiamiFilePath);
	}
	delete dialog;
}


void CDESAlgorithmDlg::OnClickChooseJiemiFile()
{
	CFileDialog *dialog = new CFileDialog(TRUE, NULL, NULL, OFN_HIDEREADONLY, L"All Files(*.*)|*.*", NULL);
	if (dialog->DoModal()) {
		CString jiemiFilePath = dialog->GetPathName();
		jiemiEdit->SetWindowTextW(jiemiFilePath);
	}
	delete dialog;
}


void CDESAlgorithmDlg::ExcJiamiAlgorithm()
{
	CString jiamiFilePath; 
	CString jiamiAfterFilePath;
	CString key;
	bool useDefKey = false;

	jiamiEdit->GetWindowTextW(jiamiFilePath);
	jiamiAfterEdit->GetWindowTextW(jiamiAfterFilePath);
	keyEdit->GetWindowTextW(key);
	if (jiamiFilePath.IsEmpty() || jiamiAfterFilePath.IsEmpty()) {
		AfxMessageBox(L"请先选择加密的文件，并输入加密后的文件路径");
		return;
	}
	if (!PathFileExists(jiamiFilePath)) {
		AfxMessageBox(L"待加密的文件不存在，请重新选择！");
		return;
	}
	if (key.IsEmpty()) {
		int retVal = AfxMessageBox(L"您没有输入自己的密钥，点击YES使用默认密钥，NO输入密钥！", MB_YESNO);
		if (IDNO == retVal) {
			return;
		}
		else {
			useDefKey = true;
		}
	}
	if (!useDefKey &&  key.GetLength() < 8) {
		AfxMessageBox(L"密钥的长度要大于等于8个字符！");
		return;
	}

	DESClass des;

	if (useDefKey) {
		des.DES_Encrypt(jiamiFilePath, defKey, jiamiAfterFilePath);
	}
	else {
		char data[8];
		//	key.GetBuffer(0) 这个函数可以将CString转为char *
		memcpy(data, key.GetBuffer(0), 8);
		des.DES_Encrypt(jiamiFilePath, data, jiamiAfterFilePath);
	}
	AfxMessageBox(L"加密文件成功！");
}


void CDESAlgorithmDlg::ExcJiemiAlgorithm()
{
	CString jiemiFilePath;
	CString jiemiAfterFilePath;
	CString key;
	bool useDefKey = false;

	jiemiEdit->GetWindowTextW(jiemiFilePath);
	jiemiAfterEdit->GetWindowTextW(jiemiAfterFilePath);
	keyEdit->GetWindowTextW(key);
	if (jiemiFilePath.IsEmpty() || jiemiAfterFilePath.IsEmpty()) {
		AfxMessageBox(L"请先选择加密的文件，并输入加密后的文件路径");
		return;
	}
	if (!PathFileExists(jiemiFilePath)) {
		AfxMessageBox(L"待加密的文件不存在，请重新选择！");
		return;
	}
	if (key.IsEmpty()) {
		int retVal = AfxMessageBox(L"您没有输入自己的密钥，点击YES使用默认密钥，NO输入密钥！", MB_YESNO);
		if (IDNO == retVal) {
			return;
		}
		else {
			useDefKey = true;
		}
	}
	if (!useDefKey && key.GetLength() < 8) {
		AfxMessageBox(L"密钥的长度要大于等于8个字符！");
		return;
	}

	DESClass des;
	if (useDefKey) {
		des.DES_Decrypt(jiemiFilePath, defKey, jiemiAfterFilePath);
	}
	else {
		char data[8];
		//	key.GetBuffer(0) 这个函数可以将CString转为char *
		memcpy(data, key.GetBuffer(0), 8);
		des.DES_Decrypt(jiemiFilePath, data, jiemiAfterFilePath);
	}
	AfxMessageBox(L"解密文件成功！");
}
