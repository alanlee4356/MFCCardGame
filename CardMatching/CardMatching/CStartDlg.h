#pragma once
#include "afxdialogex.h"


// CStartDlg 대화 상자

class CStartDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStartDlg)

public:
	CStartDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CStartDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_START_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedButtonAlone();
	afx_msg void OnClickedButtonCouple();
	bool m_bPlayAlone;
	bool m_bPlayCouple;
	bool m_bEasy;
	bool m_bHard;
	bool m_bTriple;
	afx_msg void OnClickedButtonEight();
	afx_msg void OnClickedButtonSix();
	afx_msg void OnBnClickedTripleDialog();
};
