
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
	CEdit *jiamiEdit;	//�����ļ�·��
	CEdit *jiemiEdit;	//�����ļ�·��
	CEdit *jiamiAfterEdit;	//���ܺ��ļ�·��
	CEdit *jiemiAfterEdit;	//���ܺ��ļ�·��
	CEdit *keyEdit;			//�ӽ�����Կ�����
	CButton *btnExcJiami;	//ִ�м����㷨��ť
	CButton *btnExcJiemi;	//ִ�н����㷨��ť
	char defKey[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
public:
	afx_msg void ExcJiamiAlgorithm();
	afx_msg void ExcJiemiAlgorithm();
};
