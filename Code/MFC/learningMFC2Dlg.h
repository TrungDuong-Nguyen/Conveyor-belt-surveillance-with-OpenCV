
// learningMFC2Dlg.h : header file
//

#pragma once
#include "cxcore.h"
#include "eroder.h"


// ClearningMFC2Dlg dialog
class ClearningMFC2Dlg : public CDialogEx
{
// Construction
public:
	ClearningMFC2Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_LEARNINGMFC2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	IplImage *image;	// This is the image pointer (input)
	Eroder eroder;		// The image processor as an automatic variable

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOpenImage();
	afx_msg void OnOk();
//	afx_msg void OnBnClickedCancel();
//	afx_msg void OnProcess();
	afx_msg void OnBnClickedOk();
	CString m_strFILENAME;
//	afx_msg void OnEnChangeFilename();
//	afx_msg void OnBnClickedButton2();
	afx_msg void OnOpenVideo();
	CString m_strFILENAME2;
	afx_msg void OnViewInfo3();
	CString m_strINFO;
//	CEdit m_strINFOLINK;
	CString m_strINFOLINK;
	afx_msg void OnOpenCAM();
	CString m_strMODE;
	afx_msg void OnMODE1();
	afx_msg void OnMODE2();
	afx_msg void OnMODE3();
};
