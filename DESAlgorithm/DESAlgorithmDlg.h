
// DESAlgorithmDlg.h : header file
//

#pragma once


// CDESAlgorithmDlg dialog
class CDESAlgorithmDlg : public CDialogEx
{
// Construction
public:
	CDESAlgorithmDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DESALGORITHM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickChooseJiamiFile();
	afx_msg void OnClickChooseJiemiFile();

private:
	CEdit *jiamiEdit;	//加密文件路径
	CEdit *jiemiEdit;	//解密文件路径
	CEdit *jiamiAfterEdit;	//加密后文件路径
	CEdit *jiemiAfterEdit;	//解密后文件路径
	CEdit *keyEdit;			//加解密密钥输入框
	CButton *btnExcJiami;	//执行加密算法按钮
	CButton *btnExcJiemi;	//执行解密算法按钮
	char defKey[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
public:
	afx_msg void ExcJiamiAlgorithm();
	afx_msg void ExcJiemiAlgorithm();
};
