// CStartDlg.cpp: 구현 파일
//

#include "pch.h"
#include "CardMatching.h"
#include "afxdialogex.h"
#include "CStartDlg.h"

#include "CardMatchingDlg.h"
#include "CAloneDlg.h"
#include "CCoupleDlg.h"
#include "CAloneHardDlg.h"
#include "CCoupleHardDlg.h"


// CStartDlg 대화 상자

IMPLEMENT_DYNAMIC(CStartDlg, CDialogEx)

CStartDlg::CStartDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_START_DIALOG, pParent)
{
	m_bPlayAlone = false;
	m_bPlayCouple = false;
	m_bEasy = false;
	m_bHard = false;
}

CStartDlg::~CStartDlg()
{
}

void CStartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CStartDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ALONE, &CStartDlg::OnClickedButtonAlone)
	ON_BN_CLICKED(IDC_BUTTON_COUPLE, &CStartDlg::OnClickedButtonCouple)
	ON_BN_CLICKED(IDC_BUTTON_EIGHT, &CStartDlg::OnClickedButtonEight)
	ON_BN_CLICKED(IDC_BUTTON_SIX, &CStartDlg::OnClickedButtonSix)
END_MESSAGE_MAP()


// CStartDlg 메시지 처리기

void CStartDlg::OnClickedButtonEight()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bHard = true;
	m_bEasy = false;
}


void CStartDlg::OnClickedButtonSix()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bEasy = true;
	m_bHard = false;
}

void CStartDlg::OnClickedButtonAlone()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//m_bPlayAlone = true;

	if (m_bHard)// 솔로 8x8 CAloneDlgHard 호출
	{
		CAloneHardDlg alone_hard_dlg;
		alone_hard_dlg.DoModal();
		
	}
	else// 솔로 6x6
	{
		CAloneDlg alone_dlg;
		alone_dlg.DoModal();
	}
}


void CStartDlg::OnClickedButtonCouple()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//m_bPlayCouple = true;

	if (m_bHard)// 커플 8x8 CCoupleDlgHard 호출
	{
		CCoupleHardDlg couple_hard_dlg;
		couple_hard_dlg.DoModal();
	}
	else// 커플 6x6
	{
		CCoupleDlg couple_dlg;
		couple_dlg.DoModal();
	}
}



