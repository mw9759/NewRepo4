
// OMokView.cpp: COMokView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "OMok.h"
#endif

#include "OMokDoc.h"
#include "OMokView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// COMokView

IMPLEMENT_DYNCREATE(COMokView, CView)

BEGIN_MESSAGE_MAP(COMokView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_CHAR()
END_MESSAGE_MAP()

// COMokView 생성/소멸

COMokView::COMokView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

COMokView::~COMokView()
{
}

BOOL COMokView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// COMokView 그리기

void COMokView::OnDraw(CDC* pDC)
{
	COMokDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CPen pen, * oldpen;
	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	oldpen = pDC->SelectObject(&pen);
	CRect rt;
	rt.left = 90;
	rt.top = 30;
	rt.right = 540;
	rt.bottom = 70;
	pDC->DrawText(L"*오목게임 시작*",
		&rt, DT_CENTER | DT_VCENTER);
	
    CBrush brush(RGB(255,128,0)), *oldBrush;
	oldBrush = pDC->SelectObject(&brush);
	pDC->Rectangle(60, 60, 571, 571);
	for (int y = 3; y < 18; y++) {
		for (int x = 3; x < 18; x++) {
			pDC->Rectangle(x * 30, y * 30, x * 30 + 31, y * 30 + 31);
		}
    }
	pDC->SelectObject(oldBrush);
	CRect at;
	rt.left = 700;
	rt.top = 90;
	rt.right = 1180;
	rt.bottom = 570;
	pDC->DrawText(L"**게임 방법**\n\n\n1.돌을 5개 연달아 놓으면 '승'!\n\n\n2.흰돌은 왼쪽 마우스 클릭! 흑돌은 오른쪽 마우스 클릭!\n\n\n3.보통 초급자의 경우 먼저 선을 잡습니다!(흰돌)\n\n\n4.필요에 따라 플레이어만의 룰을 추가하셔도 됩니다!!\n\n\n5.재경기를 위해선 'Backspace'를 눌러 주세요~!\n\n\n**추가 예정**\n\n'승''패'이벤트 출력\n\n'무르기'버튼", &rt, DT_CENTER | DT_TOP);
	
	
}


// COMokView 인쇄

BOOL COMokView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void COMokView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void COMokView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// COMokView 진단

#ifdef _DEBUG
void COMokView::AssertValid() const
{
	CView::AssertValid();
}

void COMokView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COMokDoc* COMokView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COMokDoc)));
	return (COMokDoc*)m_pDocument;
}
#endif //_DEBUG


// COMokView 메시지 처리기


void COMokView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientDC dc(this);
	int x = (point.x + 15) / 30, y = (point.y + 15) / 30;
	if (x >= 3 && y >= 3 && x <= 18 && y <= 18) {
		x *= 30;
		y *= 30;

		dc.Ellipse(x - 15, y - 15, x + 15, y + 15);
     }
	CView::OnLButtonDown(nFlags, point);
}




void COMokView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientDC dc(this);
	CBrush brush(RGB(0,0,0));
    dc.SelectObject(&brush);

	int x = (point.x + 15) / 30, y = (point.y + 15) / 30;
	if (x >= 3 && y >= 3 && x <= 18 && y <= 18) {
		x *= 30;
		y *= 30;

		dc.Ellipse(x - 15, y - 15, x + 15, y + 15);
	}
	
	CView::OnRButtonDown(nFlags, point);
}


void COMokView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nChar == VK_BACK) {
		Invalidate(FALSE);
		AfxMessageBox(_T("게임을 재시작합니다."));
	}
	CView::OnChar(nChar, nRepCnt, nFlags);
}
