// CAloneDlg.cpp: 구현 파일
//

#include "pch.h"
#include "CardMatching.h"
#include "afxdialogex.h"
#include "CAloneDlg.h"
#include "CResultDlg.h"


// CAloneDlg 대화 상자

IMPLEMENT_DYNAMIC(CAloneDlg, CDialogEx)

CAloneDlg::CAloneDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ALONE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	srand((unsigned int)time(NULL));

	for (int i = 0; i < 36; i++)
	{
		m_game_table[i] = i % 18;
	}

	int first_choice, second_choice, temp;
	for (int i = 0; i < 35; i++)
	{
		first_choice = rand() % 36;
		second_choice = rand() % 36;

		temp = m_game_table[first_choice];
		m_game_table[first_choice] = m_game_table[second_choice];
		m_game_table[second_choice] = temp;
	}

	m_nScore = 0;
}

CAloneDlg::~CAloneDlg()
{
}

void CAloneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAloneDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_HINT, &CAloneDlg::OnBnClickedButtonHint)

	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CAloneDlg 메시지 처리기

// CCardMatchingDlg 메시지 처리기

BOOL CAloneDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.
	SetIcon(m_hIcon, TRUE);          // 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);         // 작은 아이콘을 설정합니다.

	// 카드 이미지 로드
	CString str;
	for (int i = 0; i < 19; i++)
	{
		str.Format(L"Image\\%03d.bmp", i);
		m_card_list[i].Load(str);
	}

	SetTimer(1, 3000, NULL); // 카드 뒷면으로 돌아가는 타이머 설정
	SetTimer(2, 1000, NULL); // 1초마다 업데이트 타이머 (IDC_STATIC_SECOND 갱신)

	m_nTime = 180; // 3분(180초)
	SetDlgItemInt(IDC_STATIC_TIME, m_nTime);
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CAloneDlg::OnPaint()
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
		CPaintDC dc(this);
		int index;

		for (int i = 0; i < 36; i++)
		{
			index = m_game_table[i] + 1; //index는 1~18
			// 0번은 뒷면이기 때문에 +1을 해주어 뒷면이 나오지 않게 한다.

			if (index == 0) continue; //m_game_table=-1이면 카드 짝을 맞춘 경우
			//따라서 카드를 draw하지 않는다.

			if (m_front_back == 0) index = 0;

			m_card_list[index].Draw(dc, (i % 6) * 60, (i / 6) * 80, 60, 80);
		}
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CAloneDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAloneDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
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


void CAloneDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_front_back) return; //m_front_back 이 1이면 마우스 클릭을 못함

	if (point.x < 60 * 6 && point.y < 80 * 6)
	{
		int x = point.x / 60;
		int y = point.y / 80;
		int pos = y * 6 + x;
		int index = m_game_table[pos] + 1;

		if (index == 0) return;

		CClientDC dc(this);
		m_card_list[index].Draw(dc, x * 60, y * 80, 60, 80);

		if (m_card_choice == -1) m_card_choice = pos; //먼저 선택된 카드가 없다.
		else //먼저 선택된 카드가 있다.
		{
			if (m_card_choice != pos)
				//첫 카드와 두 번째 카드가 같은 위치가 아닐 때
			{
				if (m_game_table[m_card_choice] == m_game_table[pos])
					//첫 번째 테이블 값과 두 번째 테이블 값이 같으면
				{
					m_nScore+=2;
					SetDlgItemInt(IDC_STATIC_SCORE, m_nScore);
					m_game_table[m_card_choice] = -1;
					m_game_table[pos] = -1;
				}
				m_card_choice = -1; //다시 첫 번째 카드를 선택하는 상황

				m_front_back = 1; //WM_TIMER 메세지가 호출되기 전까지 아무것도 못 누르게

				SetTimer(1, 1000, NULL);

				// 게임을 끝내거나 시간이 초과된 경우
				if (IsGameComplete() || m_nTime == 0) {
					KillTimer(2);

					CResultDlg resultDlg;
					resultDlg.DoModal();
				}
			}
		}

	}


	CDialogEx::OnLButtonDown(nFlags, point);
}


void CAloneDlg::OnBnClickedButtonHint()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_card_choice == -1) {
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


bool CAloneDlg::IsGameComplete() {
	for (int i = 0; i < 36; i++) {
		if (m_game_table[i] != -1) {
			return false; // There is still an unmatched card
		}
	}
	return true; // All cards are matched
}



void CAloneDlg::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnClose();

}
