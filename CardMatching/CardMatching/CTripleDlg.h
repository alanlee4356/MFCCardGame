#pragma once
#include "afxdialogex.h"


// CTripleDlg 대화 상자

class CTripleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTripleDlg)

private:
	CImage m_card_list[19];
	char m_game_table[36];
	char m_front_back = 1;
	char m_card_choice01 = -1;
	char m_card_choice02 = -1;
	int count = 0;
	int score = 0; // pch.h에 static int m_score를 선언하고 사용
	CString str_score; // pch.h에 static CString m_score를 선언하고 사용

public:
	CTripleDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CTripleDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRIPLE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP();
	HICON m_hIcon;

// 구현입니다.
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedOk();
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	
};
