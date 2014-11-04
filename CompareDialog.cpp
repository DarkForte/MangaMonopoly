// CompareDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "MangaMonopoly.h"
#include "CompareDialog.h"
#include "afxdialogex.h"


// CCompareDialog 对话框

IMPLEMENT_DYNAMIC(CCompareDialog, CDialogEx)

CCompareDialog::CCompareDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCompareDialog::IDD, pParent)
{

}

CCompareDialog::~CCompareDialog()
{
}

void CCompareDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAINPIC, main_pic);
	DDX_Control(pDX, IDC_RECTA, rect_a);
	DDX_Control(pDX, IDC_RECTB, rect_b);
}

void CCompareDialog::setData(CPlayer pl[])
{
	int i;
	for(i=1;i<=CPublic::SUPPORT_PLAYER;i++)
	{
		player[i].total = pl[i].total;
		player[i].book_value = pl[i].book_value;
		player[i].invest = pl[i].invest;
		player[i].money = pl[i].money;
	}
	return;
}

double CCompareDialog::CalcFactor()
{
	int i;
	double min1=1e9, max1 = 0;
	for(i=1;i<=CPublic::SUPPORT_PLAYER; i++)
	{
		min1 = min(min1, player[i].total);
		max1 = max(max1, player[i].total);
	}

	double default_f = 0.1;
	if(min1 == max1)
		return default_f;
	else
		return min(default_f, 120.0/(max1 - min1));
}

void CCompareDialog::DrawSmallRect(CDC* dc, CRect rect)
{
	dc->Rectangle(rect);
	return;
}

void CCompareDialog::DrawRect(CDC* dc, int num , int height, double factor)
{
	int start_x[5] = {0, 70, 210, 350, 500};
	int blank = 15;
	int width = 10;

	int left = start_x[1] + blank*(num-1);
	int top = height - factor * player[num].total ;
	dc->Rectangle( left, top, left + width, height);

	left = start_x[2] + blank* (num-1);
	top = height - factor * player[num].money;
	dc->Rectangle(left, top, left+width, height);

	left = start_x[3] + blank* (num-1);
	top = height - factor * player[num].invest;
	dc->Rectangle(left, top, left+width, height);

	left = start_x[4] + blank* (num-1);
	top = height - factor * player[num].book_value;
	dc->Rectangle(left, top, left+width, height);
}

BEGIN_MESSAGE_MAP(CCompareDialog, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CCompareDialog 消息处理程序

void CCompareDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	CDC* main_dc = main_pic.GetDC();
	CBrush brush(RGB(255,255,255));
	CRect main_rect;
	main_pic.GetClientRect(&main_rect);

	main_dc->SelectObject(brush);
	main_dc->Rectangle(main_rect);

	double factor = CalcFactor();
	int height = main_rect.Height();

	brush.DeleteObject();
	brush.CreateSolidBrush(RGB(255,0,0));
	main_dc->SelectObject(brush);
	DrawRect(main_dc, 1, height, factor);

	CDC* rect_a_dc = rect_a.GetDC();
	CRect rect_a_rect;
	rect_a.GetClientRect(&rect_a_rect);

	rect_a_dc->SelectObject(brush);
	DrawSmallRect(rect_a_dc, rect_a_rect);

	brush.DeleteObject();
	brush.CreateSolidBrush(RGB(0,0,255));
	main_dc->SelectObject(brush);
	DrawRect(main_dc, 2, height, factor);

	CDC* rect_b_dc = rect_b.GetDC();
	rect_b_dc->SelectObject(brush);
	CRect rect_b_rect;
	rect_b.GetClientRect(&rect_b_rect);
	DrawSmallRect(rect_b_dc, rect_b_rect);

	UpdateData(false);

	ReleaseDC(main_dc);
	ReleaseDC(rect_a_dc);
	ReleaseDC(rect_b_dc);

	// 不为绘图消息调用 CDialogEx::OnPaint()
}
