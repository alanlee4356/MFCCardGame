// CCoupleDlg.cpp: 구현 파일
//

#include "pch.h"
#include "CardMatching.h"
#include "afxdialogex.h"
#include "CCoupleDlg.h"

#include "CStartDlg.h"
#include "CCoupleResultDlg.h"


// CCoupleDlg 대화 상자

IMPLEMENT_DYNAMIC(CCoupleDlg, CDialogEx)

CCoupleDlg::CCoupleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_COUPLE_DIALOG, pParent)
	, m_nPoint1(0)
	, m_nPoint2(0)
	, m_nSecond(10)
{
	m_hIcon = AfxGetApp()->LoadIconW(IDR_MAINFRAME);

	for (int i = 0; i < 36; i++) {
		m_game_table[i] = i % 18;
	}

	srand((unsigned int)time(NULL));

	int first_choice, second_choice, temp;

	for (int i = 0; i < 35; i++) {
		first_choice = rand() % 36;
		second_choice = rand() % 36;

		temp = m_game_table[first_choice];
		m_game_table[first_choice] = m_game_table[second_choice];
		m_game_table[second_choice] = temp;

	}
}

CCoupleDlg::~CCoupleDlg()
{
}

void CCoupleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_POINT1, m_nPoint1);
	DDX_Text(pDX, IDC_EDIT_POINT2, m_nPoint2);
	DDX_Text(pDX, IDC_STATIC_TIME, m_nSecond);
}


BEGIN_MESSAGE_MAP(CCoupleDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_HINT1, &CCoupleDlg::OnClickedButtonHint1)
	ON_BN_CLICKED(IDC_BUTTON_HINT2, &CCoupleDlg::OnClickedButtonHint2)
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_TIMER, &CCoupleDlg::OnClickedButtonTimer)
END_MESSAGE_MAP()


// CCoupleDlg 메시지 처리기


void CCoupleDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

}


BOOL CCoupleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	// 플레이어 폰트
	m_tFont1.CreateFont(30, 10, 0, 0, 1000, 1, 0, 0, 0, OUT_DEFAULT_PRECIS, 0, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("굴림"));
	GetDlgItem(IDC_STATIC_PLAYER1)->SetFont(&m_tFont1);
	GetDlgItem(IDC_STATIC_PLAYER2)->SetFont(&m_tFont1);

	m_tFont2.CreateFont(20, 10, 0, 0, 1000, 1, 0, 0, 0, OUT_DEFAULT_PRECIS, 0, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("굴림"));
	GetDlgItem(IDC_EDIT_POINT1)->SetFont(&m_tFont2);
	GetDlgItem(IDC_EDIT_POINT2)->SetFont(&m_tFont2);

	m_tFont3.CreateFont(20, 10, 0, 0, 1000, 0, 0, 0, 0, OUT_DEFAULT_PRECIS, 0, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("굴림"));
	GetDlgItem(IDC_STATIC_TIME)->SetFont(&m_tFont3);



	CString str;

	for (int i = 0; i < 19; i++)
	{
		str.Format(L"Image\\%03d.bmp", i);
		m_card_list[i].Load(str);
	}

	SetTimer(1, 3000, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CCoupleDlg::OnPaint()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	if (IsIconic()) {
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
		CPaintDC dc(this);
		int index;

		for (int i = 0; i < 36; i++)
		{
			index = m_game_table[i] + 1; //index는 1~18
			// 0번은 뒷면이기 때문에 +1을 해주어 뒷면이 나오지 않게 한다.

			if (index == 0) continue; //m_game_table=-1이면 카드 짝을 맞춘 경우
			//따라서 카드를 draw하지 않는다.

			if (m_front_back == 0) index = 0;

			m_card_list[index].Draw(dc, 300 + (i % 6) * m_length, 50 + (i / 6) * m_height, m_length, m_height);
		}

	}
}


void CCoupleDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (nIDEvent == 1)
	{
		KillTimer(1);
		m_front_back = 0;
		Invalidate();
	}
	else if (nIDEvent == 2)
	{
		m_nSecond -= 1;
		UpdateData(FALSE);

		if (m_nSecond == 0)
		{
			if (m_bTurn)
				m_bTurn = false;
			else
				m_bTurn = true;

			m_nSecond = 10;
			UpdateData(FALSE);
			Invalidate();
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CCoupleDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_front_back) return; //m_front_back 이 1이면 마우스 클릭을 못함
	if (!m_bTimerRun) return;

	if (point.x > 300 && point.x < 300 + (m_length * 6) && point.x > 50 && point.y < 50 + (m_height * 6))
	{
		int x = (point.x - 300) / m_length;
		int y = (point.y - 50) / m_height;

		int pos = y * 6 + x;
		int index = m_game_table[pos] + 1;

		if (index == 0) return;

		CClientDC dc(this);
		m_card_list[index].Draw(dc, 300 + x * m_length, 50 + y * m_height, m_length, m_height);

		if (m_card_choice == -1) m_card_choice = pos; //먼저 선택된 카드가 없다.
		else //먼저 선택된 카드가 있다.
		{
			if (m_card_choice != pos)
				//첫 카드와 두 번째 카드가 같은 위치가 아닐 때
			{
				if (m_game_table[m_card_choice] == m_game_table[pos])
					//첫 번째 테이블 값과 두 번째 테이블 값이 같으면
				{
					m_game_table[m_card_choice] = -1;
					m_game_table[pos] = -1;

					if (m_bTurn)
					{
						m_nPoint1++;
						m_bTurn = false;
						UpdateData(FALSE);
					}
					else
					{
						m_nPoint2++;
						m_bTurn = true;
						UpdateData(FALSE);
					}

					m_nSecond = 10;
					UpdateData(FALSE);
				}
				else
				{
					if (m_bTurn)
					{
						m_bTurn = false;
						UpdateData(FALSE);
					}
					else
					{
						m_bTurn = true;
						UpdateData(FALSE);
					}

					m_nSecond = 10;
					UpdateData(FALSE);
				}

				m_card_choice = -1; //다시 첫 번째 카드를 선택하는 상황

				m_front_back = 1; //WM_TIMER 메세지가 호출되기 전까지 아무것도 못 누르게

				SetTimer(1, 1000, NULL);

				if (IsGameComplete())
				{
					KillTimer(2);
					CCoupleResultDlg coupleresult_dlg;
					coupleresult_dlg.DoModal();
				}
			}
		}

	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CCoupleDlg::OnClickedButtonHint1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_front_back) return; //카드가 앞면이면 누르지 못함
	if (!m_bTurn) return;

	CString str;
	GetDlgItemText(IDC_BUTTON_HINT1, str);

	int num = _wtoi(str);

	if (num > 0) {
		str.Format(L"%d", num - 1);
		SetDlgItemText(IDC_BUTTON_HINT1, str);

		m_front_back = 1;
		Invalidate();
		SetTimer(1, 800, NULL);
	}
}


void CCoupleDlg::OnClickedButtonHint2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_front_back) return; //카드가 앞면이면 누르지 못함
	if (m_bTurn) return;

	CString str;
	GetDlgItemText(IDC_BUTTON_HINT2, str);

	int num = _wtoi(str);

	if (num > 0) {
		str.Format(L"%d", num - 1);
		SetDlgItemText(IDC_BUTTON_HINT2, str);

		m_front_back = 1;
		Invalidate();
		SetTimer(1, 800, NULL);
	}
}


HCURSOR CCoupleDlg::OnQueryDragIcon()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return static_cast<HCURSOR>(m_hIcon);
}


HBRUSH CCoupleDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.

	if (m_bTurn)
	{
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_PLAYER1)
		{
			pDC->SetTextColor(RGB(255, 0, 0));
		}
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_PLAYER2)
		{
			pDC->SetTextColor(RGB(0, 0, 0));
		}
	}
	else
	{
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_PLAYER2)
		{
			pDC->SetTextColor(RGB(255, 0, 0));
		}
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_PLAYER1)
		{
			pDC->SetTextColor(RGB(0, 0, 0));
		}
	}


	return hbr;
}


void CCoupleDlg::OnClickedButtonTimer()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_bTimerRun)
	{
		m_bTimerRun = true;
		UpdateData(FALSE);

		SetTimer(2, 1000, NULL); //1초마다 timer 호출
	}
	else return;

}


bool CCoupleDlg::IsGameComplete()
{
	// TODO: 여기에 구현 코드 추가.
	int count = 0;
	for (int i = 0; i < 18; i++)
	{
		if (m_game_table[i] == -1)
		{
			count++;
		}
	}

	if (count == 18)
	{
		m_nScore = (m_nPoint1)*2;
		m_nScore2 = (m_nPoint2)*2;
		return true;
	}

	return false;
}
