// CResultDlg.cpp: 구현 파일
//

#include "pch.h"
#include "CardMatching.h"
#include "afxdialogex.h"
#include "CResultDlg.h"


// CResultDlg 대화 상자

IMPLEMENT_DYNAMIC(CResultDlg, CDialogEx)

CResultDlg::CResultDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RESULT_DIALOG, pParent)
{	
	/*
	CString str_Score;
	CString str_Time;
	CString str_FinalScore;
	
	//전역변수에 있는 score, time 값을 바탕으로 값을 계산 후 표시
	m_nFinalScore = m_nScore + m_nTime;
	str_Score.Format(_T("%d"), m_nScore);
	str_Time.Format(_T("%d"), m_nTime);
	str_FinalScore.Format(_T("%d"), m_nFinalScore);
	*/
	//m_score.SetWindowTextW(str_Score);
	//m_finalScore.SetWindowTextW(str_FinalScore);
	//m_time.SetWindowTextW(str_Time);
}

CResultDlg::~CResultDlg()
{
}

void CResultDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_SCORE, m_score);
	DDX_Control(pDX, IDC_STATIC_FINALSCORE, m_finalScore);
	DDX_Control(pDX, IDC_STATIC_TIME, m_time);
}


BEGIN_MESSAGE_MAP(CResultDlg, CDialogEx)
END_MESSAGE_MAP()


// CResultDlg 메시지 처리기


BOOL CResultDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	CString str_Score;
	CString str_Time;
	CString str_FinalScore;

	//전역변수에 있는 score, time 값을 바탕으로 값을 계산 후 표시
	m_nFinalScore = m_nScore + m_nTime;
	str_Score.Format(_T("%d"), m_nScore);
	str_Time.Format(_T("%d"), m_nTime);
	str_FinalScore.Format(_T("%d"), m_nFinalScore);

	m_score.SetWindowTextW(str_Score);
	m_finalScore.SetWindowTextW(str_FinalScore);
	m_time.SetWindowTextW(str_Time);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
