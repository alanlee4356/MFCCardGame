// CCoupleResultDlg.cpp: 구현 파일
//

#include "pch.h"
#include "CardMatching.h"
#include "afxdialogex.h"
#include "CCoupleResultDlg.h"
#include "resource.h"


// CCoupleResultDlg 대화 상자

IMPLEMENT_DYNAMIC(CCoupleResultDlg, CDialogEx)

CCoupleResultDlg::CCoupleResultDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_COUPLE_RESULT_DIALOG, pParent)
{
}

CCoupleResultDlg::~CCoupleResultDlg()
{
}

void CCoupleResultDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);


	DDX_Control(pDX, IDC_STATIC_WINNER, m_winner);
	DDX_Control(pDX, IDC_STATIC_COUPLE_FINALSCORE, m_finalScore);
	DDX_Control(pDX, IDC_STATIC_COUPLE_FINALSCORE, m_finalScore);
	DDX_Control(pDX, IDC_STATIC_COUPLE_FINALSCORE2, m_finalScore2);
	DDX_Control(pDX, IDC_STATIC_COUPLE_SCORE, m_score);
	DDX_Control(pDX, IDC_STATIC_COUPLE_SCORE2, m_score2);
	DDX_Control(pDX, IDC_STATIC_COUPLE_TIME, m_time);
	DDX_Control(pDX, IDC_STATIC_COUPLE_TIME2, m_time2);
}


BEGIN_MESSAGE_MAP(CCoupleResultDlg, CDialogEx)
END_MESSAGE_MAP()


// CCoupleResultDlg 메시지 처리기


BOOL CCoupleResultDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CString str_Score;
	CString str_Time;
	CString str_FinalScore;
	CString str_Score2;
	CString str_Time2;
	CString str_FinalScore2;
	CString str_Winner;

	//전역변수에 있는 score, time 값을 바탕으로 값을 계산 후 표시
	m_nFinalScore = m_nScore + 10 * m_nTime;
	str_Score.Format(_T("%d"), m_nScore);
	str_Time.Format(_T("%d"), m_nTime);
	str_FinalScore.Format(_T("%d"), m_nFinalScore);
	m_nFinalScore2 = m_nScore2 + 10 * m_nTime2;
	str_Score2.Format(_T("%d"), m_nScore2);
	str_Time2.Format(_T("%d"), m_nTime2);
	str_FinalScore2.Format(_T("%d"), m_nFinalScore2);
	
	if (m_nFinalScore > m_nFinalScore2) {
		str_Winner.Format(_T("1P Win!"));
	}
	else if (m_nFinalScore == m_nFinalScore2) {
		str_Winner.Format(_T("Draw"));
	}
	else {
		str_Winner.Format(_T("2P Win!"));
	}
	
	m_score.SetWindowTextW(str_Score);
	m_finalScore.SetWindowTextW(str_FinalScore);
	m_time.SetWindowTextW(str_Time);
	m_score2.SetWindowTextW(str_Score2);
	m_finalScore2.SetWindowTextW(str_FinalScore2);
	m_time2.SetWindowTextW(str_Time2);
	m_winner.SetWindowTextW(str_Winner);
	

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
