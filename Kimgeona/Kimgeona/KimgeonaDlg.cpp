
// KimgeonaDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Kimgeona.h"
#include "KimgeonaDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CKimgeonaDlg 대화 상자



CKimgeonaDlg::CKimgeonaDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_KIMGEONA_DIALOG, pParent)
	, m_ImgWidth(0)
	, m_ImgHeight(0)
	, m_ImgBPP(0)
	, m_StartX(0)
	, m_StartY(0)
	, m_Radius(15)
	, m_Border(5)
	, m_Threading(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKimgeonaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_INPUT, m_Radius);
	DDV_MinMaxInt(pDX, m_Radius, 1, INT_MAX);
	DDX_Text(pDX, IDC_INPUT2, m_Border);
	DDV_MinMaxInt(pDX, m_Border, 1, INT_MAX);
}

BEGIN_MESSAGE_MAP(CKimgeonaDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BTN_INIT, &CKimgeonaDlg::OnBnClickedBtnInit)
	ON_BN_CLICKED(IDC_BTN_RANDOM, &CKimgeonaDlg::OnBnClickedBtnRandom)
	ON_BN_CLICKED(IDC_BTN_APPLY, &CKimgeonaDlg::OnBnClickedBtnApply)
	ON_BN_CLICKED(IDC_BTN_APPLY2, &CKimgeonaDlg::OnBnClickedBtnApply2)
END_MESSAGE_MAP()


// CKimgeonaDlg 메시지 처리기

BOOL CKimgeonaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	Init();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CKimgeonaDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CKimgeonaDlg::OnPaint()
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
		// 기존 그리기 작업 수행
		CDialogEx::OnPaint();

		// 나의 그리기 작업
		Draw();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CKimgeonaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool CKimgeonaDlg::Init(int nBPP, int nRadius, int nBorder)
{
	// 스레딩 작업중이 진행중인 경우 기달리기
	while (m_Threading);

	// 윈도우 크기 가져오기
	CRect rect;
	GetClientRect(&rect);

	// 변수들 초기화
	m_ImgWidth	= rect.Width() * 0.73;	// 이미지 너비
	m_ImgHeight = rect.Height() * 0.75;	// 이미지 높이
	m_ImgBPP	= nBPP;					// 이미지 비트
	m_StartX	= rect.Width() * 0.03;	// 이미지 시작 좌표 x
	m_StartY	= rect.Height() * 0.03;	// 이미지 시작 좌표 y
	m_Radius	= nRadius;				// 마우스로 생성할 원의 반지름
	m_Border	= nBorder;				// 큰 원의 가장자리 두께
	m_Selected  = -1;					// 선택된 원의 index 번호
	//
	m_Threading = false;	// 현재 스레딩 여부

	// 좌표 초기화
	m_Points.clear();

	// 이미지 초기화
	InitImage();

	return TRUE;
}

void CKimgeonaDlg::InitImage()
{
	// 기존 이미지 정리
	if (m_Image != NULL) {
		m_Image.Destroy();
	}

	// 이미지 생성
	if (m_Image.Create(m_ImgWidth, m_ImgHeight, m_ImgBPP) == FALSE) {
		AfxMessageBox(_T("이미지 생성 실패!"));
	}

	// 이미지 팔레트 설정
	if (m_ImgBPP == 8) {
		static RGBQUAD palette[256];
		for (int i = 0; i < 256; i++) {
			palette[i].rgbRed = palette[i].rgbGreen = palette[i].rgbBlue = i;
			palette[i].rgbReserved = 0;
		}
		m_Image.SetColorTable(0, 256, palette);
	}

	// 이미지 흰색으로 초기화
	int nPitch = m_Image.GetPitch();
	BYTE* pBits = (BYTE*)m_Image.GetBits();
	if (m_ImgBPP == 8) {
		// TODO: 추후 memset()를 이용하여 코드를 더 간결하게 수정해야 합니다. 
		for (int r = 0; r < m_ImgHeight; r++) {
			for (int c = 0; c < m_ImgWidth; c++) {
				pBits[r * nPitch + c] = 255;
			}
		}
	}
	else if (m_ImgBPP == 24) {
		for (int r = 0; r < m_ImgHeight; r++) {
			for (int c = 0; c < m_ImgWidth; c++) {
				int index = r * nPitch + c * 3;
				pBits[index] = pBits[index + 1] = pBits[index + 2] = 255;
			}
		}
	}
}

void CKimgeonaDlg::Draw()
{
	// 기존 이미지 초기화
	InitImage();

	// 벡터에 저장된 원 이미지에 그리기
	for (const auto& p : m_Points) {
		DrawCircle(std::get<0>(p), std::get<1>(p), std::get<2>(p), 0);
	}

	// 세 점을 지나는 정원 그리기
	if (m_Points.size() == 3) {
		DrawBigCircle();
	}

	// 그리기
	CClientDC dc(this);
	if (m_Image) {
		m_Image.Draw(dc, m_StartX, m_StartY);
	}
}

void CKimgeonaDlg::DrawCircle(int nX, int nY, int nRadius, int border)
{
	// 이미지 정보 가져오기
	int nWidth = m_Image.GetWidth();
	int nHeight = m_Image.GetHeight();
	int nPitch = m_Image.GetPitch();

	// 이미지 데이터 접근
	BYTE* pBits = (BYTE*)m_Image.GetBits();

	// TODO: 8bit*3 영상 처리도 가능하게 해야함.
	// XXX: bmp 이미지의 메모리 상의 저장방식을 알아봐야함. 
	//		현재는 좌측 상단부터 픽셀이 메모리에 차례로 저장됨을 기준으로 코드를작성함.
	// 이미지에 원 그리기 (선분)
	if (border > 0) 
	{
		for (int r = 0; r < m_ImgHeight; r++) {
			for (int c = 0; c < m_ImgWidth; c++) {
				if (abs(sqrt((nX - c)*(nX - c) + (nY - r)*(nY - r)) - nRadius) <= border / 2) {
					pBits[r * nPitch + c] = 0;
				}
			}
		}
	}
	// 이미지에 원 그리기 (채워진)
	else 
	{
		for (int r = 0; r < m_ImgHeight; r++) {
			for (int c = 0; c < m_ImgWidth; c++) {
				if (((nX - c) * (nX - c) + (nY - r) * (nY - r)) <= nRadius * nRadius) {
					pBits[r * nPitch + c] = 0;
				}
			}
		}
	}
}

void CKimgeonaDlg::DrawBigCircle()
{
	// XXX: 행렬을 이용한 원 방정식 계산에 대한 검증이 필요함.
	//		(현재 계산은 잘됨.)

	// 세개의 좌표 준비
	double x1 = std::get<0>(m_Points[0]), y1 = std::get<1>(m_Points[0]);
	double x2 = std::get<0>(m_Points[1]), y2 = std::get<1>(m_Points[1]);
	double x3 = std::get<0>(m_Points[2]), y3 = std::get<1>(m_Points[2]);

	// 연립방정식 행렬 설정
	double A[3][4] = {
		{x1, y1, 1, -(x1 * x1 + y1 * y1)},
		{x2, y2, 1, -(x2 * x2 + y2 * y2)},
		{x3, y3, 1, -(x3 * x3 + y3 * y3)}
	};

	// 가우스 소거법 수행
	for (int i = 0; i < 3; i++) 
	{
		// 피벗 요소를 1로 만들기
		double pivot = A[i][i];
		for (int j = 0; j < 4; j++) {
			A[i][j] /= pivot;
		}

		// 다른 행에서 i번째 열을 0으로 만들기
		for (int k = 0; k < 3; k++) {
			if (k != i) {
				double factor = A[k][i];
				for (int j = 0; j < 4; j++) {
					A[k][j] -= factor * A[i][j];
				}
			}
		}
	}

	// 원의 방정식 일반형의 D, E, F 값 추출
	double D = A[0][3];
	double E = A[1][3];
	double F = A[2][3];

	// 원의 중심과 반지름 계산
	int h = -D / 2;						// x
	int k = -E / 2;						// y
	int r = sqrt(h * h + k * k - F);	// r

	// m_Points에 저장된 세 점을 지나는 정원 그리기
	DrawCircle(h, k, r, m_Border);
}

void CKimgeonaDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 원 생성
	if (IsCircleSelected(point) == false)
	{
		// 현재 마우스 좌표와 원 반지름 저장
		int x = point.x - m_StartX;
		int y = point.y - m_StartY;
		if (x >= 0 &&
			y >= 0 &&
			x <  m_ImgWidth &&
			y <  m_ImgHeight &&
			m_Points.size() < 3)
		{
			m_Points.push_back({ x, y, m_Radius }); // 저장
			Draw();									// 화면 그리기
		}
	}
	else {
		// 마우스가 창 밖을 나가도 계속해서 이벤트를 받도록 함
		SetCapture();
	}

	// 기본 처리
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CKimgeonaDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// 선택된 도형이 있고 마우스 좌클릭 상태이면
	if ((m_Selected > -1) && (nFlags & MK_LBUTTON))
	{
		// 현재 마우스 좌표 계산 및 범위 처리
		int nNewX = max(0, min(point.x - m_StartX, m_ImgWidth-1));
		int nNewY = max(0, min(point.y - m_StartY, m_ImgHeight - 1));

		// 현재 마우스 좌표로 도형 이동
		m_Points[m_Selected] = { nNewX, nNewY, std::get<2>(m_Points[m_Selected]) };

		// 화면 다시 그리기
		Draw();
	}
	
	// 기본 처리
	CDialogEx::OnMouseMove(nFlags, point);
}

void CKimgeonaDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// 선택된 도형 해제
	m_Selected = -1;

	// 창밖을 넘어가는 마우스 이벤트 받기 해제
	ReleaseCapture();

	// 기본 처리
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CKimgeonaDlg::OnBnClickedBtnInit()
{
	// 쓰레딩 작업중일 경우
	if (m_Threading) {
		AfxMessageBox(_T("랜덤 이동 작업(스레드)이 완료되면 진행할 수 있습니다."));
		return;
	}

	// 초기화
	Init();
	
	// 화면 그리기
	Draw();
}

void CKimgeonaDlg::OnBnClickedBtnRandom()
{
	if (m_Points.size() < 3) {
		AfxMessageBox(_T("원 세 개를 먼저 생성해 주세요."));
	}
	else if (m_Threading) {
		AfxMessageBox(_T("이미 실행중입니다."));
	}
	else 
	{
		// 스레딩 상태 변경
		m_Threading = true;

		// 단일 스레드로 분리 실행. (병렬처리 x)
		// XXX: 지금은 정상 작동하지만, 만일 다이얼로그 UI가 종료 되어 버릴 경우 현재 t.detach() 
		//		되어버린 스레드가 UI를 업데이트하는 과정에서 문제가 발생할 수 있음. 대안 탐색 필요.
		std::thread t([this] {
			// 시드 생성기
			std::random_device rd;

			// 난수 생성기
			std::mt19937 gen(rd());

			// 범위 제한기
			std::uniform_int_distribution<int> disX(0, this->m_ImgWidth);		// x 좌표
			std::uniform_int_distribution<int> disY(0, this->m_ImgHeight);	// y 좌표

			// 랜덤 이동 (초당 2회, 총 10번)
			for (int i = 0; i < 10; i++)
			{
				// 좌표 변경
				for (int j = 0; j < 3; j++) {
					this->m_Points[j] = { disX(gen), disY(gen), std::get<2>(this->m_Points[j])};
				}

				// 화면에 그리기
				// XXX: 별도의 스레드에서 메인 스레드가 관리하는 UI를 제어하면 위험함. 
				//		추후 이에 대한 추가적인 처리가 필요.
				this->Draw();

				// 쉬기
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
			}

			// 스레딩 여부 false로 바꾸기
			this->m_Threading = false;
		});
		t.detach();
	}
}

bool CKimgeonaDlg::IsCircleSelected(CPoint point)
{
	// 원이 세개 그려져있는지 확인
	if (m_Points.size() < 3) {
		return false;
	}

	// 가장 최근에 추가된 원 좌표부터 검사
	for (int i = 2; i >= 0; i--) {
		// 원의 중심점과 point 사이의 거리 계산
		int dis = pow((point.x - m_StartX) - std::get<0>(m_Points[i]), 2) + pow((point.y - m_StartY) - std::get<1>(m_Points[i]), 2);
		int r = pow(std::get<2>(m_Points[i]), 2);

		// 현재 point가 원 내부에 있을 경우
		if (dis <= r) {
			m_Selected = i;
			return true;
		}
	}
	return false;
}

void CKimgeonaDlg::OnBnClickedBtnApply()
{
	// UI -> 변수 업데이트
	UpdateData(TRUE);

	// 변수 -> UI 업데이트
	UpdateData(FALSE);
}


void CKimgeonaDlg::OnBnClickedBtnApply2()
{
	// UI -> 변수 업데이트
	UpdateData(TRUE);

	// 변수 -> UI 업데이트
	UpdateData(FALSE);

	// 화면 그리기
	Draw();
}
