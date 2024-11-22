// CTripleDlg.cpp: 구현 파일
//

#include "pch.h"
#include "CardMatching.h"
#include "afxdialogex.h"
#include "CTripleDlg.h"
#include "framework.h"
#include "CResultDlg.h"


// CTripleDlg 대화 상자

IMPLEMENT_DYNAMIC(CTripleDlg, CDialogEx)

CTripleDlg::CTripleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TRIPLE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	for (int i = 0; i < 36; i++) {
		m_game_table[i] = i % 12;
	}

	srand(time(NULL));

	int first_choice, second_choice, temp;

	for (int i = 0; i < 35; i++) {
		first_choice = rand() % 35;
		second_choice = rand() % 35;

		temp = m_game_table[first_choice];
		m_game_table[first_choice] = m_game_table[second_choice];
		m_game_table[second_choice] = temp;
	}
}

CTripleDlg::~CTripleDlg()
{
}

void CTripleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTripleDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CTripleDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CTripleDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CTripleDlg::OnBnClickedOk)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_HINT, &CTripleDlg::OnBnClickedButtonHint)
END_MESSAGE_MAP()


// CTripleDlg 메시지 처리기


void CTripleDlg::OnBnClickedButton1() // 힌트 관련 버튼 IDC_BUTTON_HINT
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_front_back)
		return;

	CString str;
	GetDlgItemText(IDC_BUTTON1, str);

	int num = _wtoi(str);

	if (num > 0) {
		str.Format(L"%d", num - 1);
		SetDlgItemText(IDC_BUTTON1, str);

		m_front_back = 1;
		Invalidate();

		SetTimer(1, 800, NULL);
	}
}


void CTripleDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CTripleDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


//int CTripleDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
//{
//	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
//		return -1;
//
	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

//	return 0;
//}


BOOL CTripleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	CString str;

	for (int i = 0; i < 13; i++) {
		str.Format(L".\\Image\\%03d.bmp", i);
		m_card_list[i].Load(str);
	}

	SetTimer(1, 3000, NULL);
	SetTimer(2, 1000, NULL); // 1초마다 업데이트 타이머 (IDC_STATIC_SECOND 갱신)

	m_nTime = 300; // 5분(300초)
	SetDlgItemInt(IDC_STATIC_TIME, m_nTime);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}


void CTripleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);

	}
	else
	{
		// CDialogEx::OnPaint();

		CPaintDC dc(this);
		char index;

		/*for (int i = 0; i < 19; i++) {
			m_card_list[i].Draw(dc, 10 + i * 36, 56);
		} */

		for (int i = 0; i < 36; i++) {
			index = m_game_table[i] + 1;

			if (index == 0)
				continue;

			if (m_front_back == 0)
				index = 0;

			// m_card_list[m_game_table[i] + 1].Draw(dc, (i % 6) * 36, (i / 6) * 56);
			m_card_list[index].Draw(dc, (i % 6) * 60, (i / 6) * 80, 60, 80);
		}

		str_score.Format(L"%d", m_nScore);
		SetDlgItemText(IDC_STATIC_SCORE, str_score);
	}
}


HCURSOR CTripleDlg::OnQueryDragIcon()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return static_cast<HCURSOR>(m_hIcon);
}


void CTripleDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == 1) {
		KillTimer(1);
		m_front_back = 0;
		Invalidate();
	}
	else if (nIDEvent == 2)
	{
		if (m_nTime > 0)
		{
			// 남은 시간 갱신
			m_nTime--;
			SetDlgItemInt(IDC_STATIC_TIME, m_nTime);

			// 시간이 다 됐을 경우 처리
			if (m_nTime == 0)
			{
				KillTimer(2); // 타이머 종료
				//AfxMessageBox(L"시간 초과로 게임이 종료됩니다.");

				// 결과 다이얼로그 호출
				CResultDlg resultDlg;
				resultDlg.DoModal();

				// 다이얼로그 종료
				//EndDialog(IDOK);
			}
		}
	}
	else
	{
		CDialogEx::OnTimer(nIDEvent);
	}

}


void CTripleDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_front_back)
		return;

	if (point.x < 60 * 6 && point.y < 80 * 6) {
		int x = point.x / 60;
		int y = point.y / 80;
		char num = x + y * 6; // 좌표 -> 카드 index 변환

		char index = m_game_table[num] + 1;

		if (index == 0)
			return;

		CClientDC dc(this);
		m_card_list[index].Draw(dc, x * 60, y * 80, 60, 80);

		/* if (m_card_choice == -1)
			m_card_choice = num;
		else {
			if (m_card_choice != num) {
				if (m_game_table[m_card_choice] == m_game_table[num]) {
					m_game_table[m_card_choice] = -1;
					m_game_table[num] = -1;
				}

				m_card_choice = -1;

				m_front_back = 1;

				SetTimer(1, 1000, NULL);
			}

		}*/

		if (m_card_choice01 == -1) {
			m_card_choice01 = num;
		}
		else if (m_card_choice02 == -1) {
			if (m_card_choice01 != num) {
				m_card_choice02 = num;

				// 첫 번째 시도와 두 번째 시도가 다를 경우 다시 처음으로
				/* if (m_game_table[m_card_choice01] != m_game_table[m_card_choice02]) {
					m_card_choice01 = -1;
					m_card_choice02 = -1;

					SetTimer(1, 100, NULL);
				}*/
			}
		}
		else {
			if (m_card_choice01 != num && m_card_choice02 != num) {
				if (m_game_table[m_card_choice01] == m_game_table[m_card_choice02] && m_game_table[m_card_choice02] == m_game_table[num]) {
					m_game_table[m_card_choice01] = -1;
					m_game_table[m_card_choice02] = -1;
					m_game_table[num] = -1;
					m_card_choice01 = -1;
					m_card_choice02 = -1;
					m_nScore += 3;
					m_front_back = 1;
					SetTimer(1, 0, NULL);
				}
				else {
					m_card_choice01 = -1;
					m_card_choice02 = -1;
				}
			}
			m_front_back = 1;
			SetTimer(1, 1000, NULL);

		}

		if (IsGameComplete() || m_nTime == 0) {
			KillTimer(2);

			CResultDlg resultDlg;
			resultDlg.DoModal();
		}

	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


bool CTripleDlg::IsGameComplete() {
	for (int i = 0; i < 36; i++) {
		if (m_game_table[i] != -1) {
			return false; // There is still an unmatched card
		}
	}
	return true; // All cards are matched
}


void CTripleDlg::OnBnClickedButtonHint()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_card_choice01 == -1 && m_card_choice02 == -1) {
		if (m_front_back) return; //카드가 앞면이면 누르지 못함

		CString str;
		GetDlgItemText(IDC_BUTTON_HINT, str);

		int num = _wtoi(str);

		if (num > 0) {
			str.Format(L"%d", num - 1);
			SetDlgItemText(IDC_BUTTON_HINT, str);

			m_front_back = 1;
			Invalidate();
			SetTimer(1, 800, NULL);
		}
	}

}
