#pragma once
#include "afxdialogex.h"


// CCoupleHardDlg 대화 상자

class CCoupleHardDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCoupleHardDlg)

public:
	CCoupleHardDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CCoupleHardDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COUPLE_HARD_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	HICON m_hIcon;
	CFont m_tFont1, m_tFont2, m_tFont3;
	CBrush m_tBrush;

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();

	const char m_PlusPoint = 1; //맞출 시 추가되는 점수
	int m_nPoint1; //플레이어별 점수 합계
	int m_nPoint2;
	bool m_bTurn = true; //player1 start
	const char m_length = 60; //카드 크기
	const char m_height = 80;
	bool m_bTimerRun = false;
	int m_nSecond;


	CImage m_card_list[34];
	char m_game_table[64];
	char m_front_back = 1; //1=클릭 못함
	char m_card_choice = -1;

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnClickedButtonHint1();
	afx_msg void OnClickedButtonHint2();
	afx_msg void OnClickedButtonTimer();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	bool IsGameComplete();
	afx_msg void OnStnClicked1007();
};
