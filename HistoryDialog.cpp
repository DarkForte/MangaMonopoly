// HistoryDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MangaMonopoly.h"
#include "HistoryDialog.h"
#include "afxdialogex.h"

// CHistoryDialog dialog

IMPLEMENT_DYNAMIC(CHistoryDialog, CDialogEx)

CHistoryDialog::CHistoryDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHistoryDialog::IDD, pParent)
{

}

CHistoryDialog::~CHistoryDialog()
{
}

void CHistoryDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HISTORY_PIC, history_pic);
	DDX_Control(pDX, IDC_LINE_A, line_a);
	DDX_Control(pDX, IDC_LINE_B, line_b);
	DDX_Control(pDX, IDC_LINE_C, line_c);
}


BEGIN_MESSAGE_MAP(CHistoryDialog, CDialogEx)
//	ON_WM_PAINT()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CHistoryDialog message handlers
using namespace std;
void CHistoryDialog::setData(int p[4][31], int p_p)
{
	memcpy(prices, p, sizeof(int) * 4*31);
	p_prices = p_p;
	return;
}

BOOL CHistoryDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

int CHistoryDialog::CalcFactor()
{
	int i,j;
	int max1 = 0, min1 = 1<<29;

	for(i=1;i<=3;i++)
	{
		for(j=1;j<=p_prices; j++)
		{
			max1 = max(max1, prices[i][j]);
			min1 = min(min1, prices[i][j]);
		}
	}

	if(max1 == min1)
		return 15;
	else
		return min( 120 / (max1 - min1), 15 );
}

void CHistoryDialog::DrawLine(CDC* main_pic, int num, CRect history_rect, int factor)
{
	int i;
	int dis = 30;
	CPoint now_point(10, (int) (history_rect.Height() - factor* prices[num][1] ) );
	CPoint next_point;
	for(i=1;i<=p_prices;i++)
	{
		main_pic->MoveTo(now_point);
		main_pic->Ellipse(now_point.x-3, now_point.y-3, now_point.x+3, now_point.y+3);
		if(i<p_prices)
		{
			next_point.SetPoint(now_point.x + dis, (int)( history_rect.Height() - factor*prices[num][i+1] ) );
			main_pic->LineTo(next_point);
			now_point = next_point;
		}
	}
}

void CHistoryDialog::DrawSmallLine(CDC* now_dc, int s_x, int s_y, int e_x, int e_y)
{
	now_dc->MoveTo(s_x, s_y);
	now_dc->Ellipse(s_x-3, s_y-3, s_x+3, s_y+3);
	now_dc->LineTo(e_x, e_y);
	now_dc->Ellipse(e_x-3, e_y-3, e_x+3, e_y+3);
	return;
}

void CHistoryDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here

	//draw background
	CBrush brush(RGB(255,255,255));
	CWnd *history_pic_wind = GetDlgItem(IDC_HISTORY_PIC);
	CRect history_rect;
	history_pic_wind->GetClientRect(&history_rect);
	CDC *main_pic = history_pic_wind->GetDC();
	main_pic->SelectObject(brush);
	main_pic->Rectangle(history_rect);

	int factor = CalcFactor();

	//draw lines
	CPen pen(PS_SOLID, 5, RGB(255, 0, 0));
    main_pic->SelectObject(pen);
	DrawLine(main_pic, 1, history_rect, factor);

	CDC* line_a_dc = line_a.GetDC();
	line_a_dc->SelectObject(pen);
	DrawSmallLine(line_a_dc, 10, 16, 80,16);

	pen.DeleteObject();
	pen.CreatePen(PS_SOLID, 5, RGB(0, 255, 0));
	main_pic->SelectObject(pen);
	DrawLine(main_pic, 2, history_rect, factor);

	CDC* line_b_dc = line_b.GetDC();
	line_b_dc->SelectObject(pen);
	DrawSmallLine(line_b_dc, 10,16,80, 16);

	pen.DeleteObject();
	pen.CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
	main_pic->SelectObject(pen);
	DrawLine(main_pic, 3, history_rect, factor);

	CDC* line_c_dc = line_c.GetDC();
	line_c_dc->SelectObject(pen);
	DrawSmallLine(line_c_dc, 10, 16, 80, 16);

	UpdateData(false);

	ReleaseDC(main_pic);
	ReleaseDC(line_a_dc);
	ReleaseDC(line_b_dc);
	ReleaseDC(line_c_dc);
	// Do not call CDialogEx::OnPaint() for painting messages
}
