#pragma once
#include "afxdialogex.h"


// CCoupleResultDlg 대화 상자

class CCoupleResultDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCoupleResultDlg)

public:
	CCoupleResultDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CCoupleResultDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COUPLE_RESULT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
//	CStatic m_finalScore;
//	CStatic m_finalScore2;
//	CStatic m_score;
//	CStatic m_score2;
//	CStatic m_time;
//	CStatic m_time2;
//	CStatic m_winner;
//	CStatic m_finalScore;
//	CStatic m_finalScore2;
//	CStatic m_winner;
//	CStatic m_winner;
//	CStatic m_winner;
//	CStatic m_asdf;
	CStatic m_time;
	CStatic m_time2;
	CStatic m_score2;
	CStatic m_score;
	CStatic m_finalScore2;
	CStatic m_finalScore;
	virtual BOOL OnInitDialog();
	CStatic m_winner;
};
