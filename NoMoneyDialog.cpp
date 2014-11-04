// NoMoneyDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MangaMonopoly.h"
#include "NoMoneyDialog.h"
#include "afxdialogex.h"


// CNoMoneyDialog dialog

IMPLEMENT_DYNAMIC(CNoMoneyDialog, CDialogEx)

CNoMoneyDialog::CNoMoneyDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNoMoneyDialog::IDD, pParent)
{

}

CNoMoneyDialog::~CNoMoneyDialog()
{
}

void CNoMoneyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NOMONEYICON, nomoney_icon_control);
}


BEGIN_MESSAGE_MAP(CNoMoneyDialog, CDialogEx)
	ON_WM_PAINT()
	ON_STN_CLICKED(IDC_PRICE_TEXT, &CNoMoneyDialog::OnStnClickedPriceText)
END_MESSAGE_MAP()


// CNoMoneyDialog message handlers

void CNoMoneyDialog::SetInfo(CString place, int price, int type)
{
	this->place = place;
	this->price = price;
	this->type = type;

	icon.Load(L"picture\\NoMoney.jpg");
	
}

BOOL CNoMoneyDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	nomoney_icon_control.MoveWindow(30, 55, icon.GetWidth(), icon.GetHeight() );

	// TODO:  在此添加额外的初始化
	CString price_name, show_text;

	if(type == CPublic::BUY)
	{
		price_name = L"价格：";
		show_text = L"很可惜您的现金不足，无法投资。";
	}
	else if(type == CPublic::UPGRADE)
	{
		price_name = L"扩大投资价格：";
	    show_text = L"很可惜您的现金不足，无法扩大投资。";
	}

	SetDlgItemText(IDC_PLACE_TEXT, place);
	SetDlgItemText(IDC_PRICE_NAME, price_name);
	SetDlgItemInt(IDC_PRICE_TEXT, price);
	SetDlgItemText(IDC_INFO, show_text);
	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CNoMoneyDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for painting messages
	CDC * pdc = nomoney_icon_control.GetDC();
	icon.Draw(*pdc, 0, 0, icon.GetWidth(), icon.GetHeight() );
	pdc->DeleteDC();

	return;
}


void CNoMoneyDialog::OnStnClickedPriceText()
{
	// TODO: Add your control notification handler code here
}
