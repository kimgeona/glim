
// KimgeonaDlg.h: 헤더 파일
//

#pragma once


// CKimgeonaDlg 대화 상자
class CKimgeonaDlg : public CDialogEx
{
// 생성입니다.
public:
	CKimgeonaDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KIMGEONA_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

// 변수들
private:
	// 데이터
	CImage m_Image;	// 이미지(8bit, 명암채널)
	//
	std::deque<std::tuple<int, int, int>> m_Points;	// 마우스로 생성할 원(x, y, r)
	//
	int m_ImgWidth;		// 이미지 너비
	int m_ImgHeight;	// 이미지 높이
	int m_ImgBPP;		// 이미지 비트
	int m_StartX;		// 이미지 시작 좌표 x
	int m_StartY;		// 이미지 시작 좌표 y
	int m_Radius;		// 마우스로 생성할 원의 반지름
	int m_Border;		// 큰 원의 가장자리 두께
	int m_Selected;		// 선택된 원의 index 번호

public:
	bool m_Threading;	// 현재 스레딩 여부

private:
	// 함수들
	bool Init(int nBPP=8, int nRadius=15, int nBorder=5);
	void InitImage();
	void Draw();
	void DrawCircle(int x, int y, int r, int border=0);
	void DrawBigCircle();
	bool IsCircleSelected(CPoint point);

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedBtnInit();
	afx_msg void OnBnClickedBtnRandom();
	afx_msg void OnBnClickedBtnApply();
	afx_msg void OnBnClickedBtnApply2();
};
