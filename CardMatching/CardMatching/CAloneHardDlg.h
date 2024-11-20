#pragma once
#include "afxdialogex.h"


// CAloneHardDlg 대화 상자

class CAloneHardDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAloneHardDlg)

public:
	CAloneHardDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CAloneHardDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ALONE_HARD_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

		// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
public:
	CImage m_card_list[34];
	char m_game_table[64];
	char m_front_back = 1; //1=앞면, 0=뒷면
	char m_card_choice = -1;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonHint();
	afx_msg void OnClose();
	afx_msg bool IsGameComplete();
};
