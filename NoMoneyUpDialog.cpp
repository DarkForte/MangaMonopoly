// NoMoneyUpDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MangaMonopoly.h"
#include "NoMoneyUpDialog.h"
#include "afxdialogex.h"


// CNoMoneyUpDialog dialog

IMPLEMENT_DYNAMIC(CNoMoneyUpDialog, CDialogEx)

CNoMoneyUpDialog::CNoMoneyUpDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNoMoneyUpDialog::IDD, pParent)
{

}

CNoMoneyUpDialog::~CNoMoneyUpDialog()
{
}

void CNoMoneyUpDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNoMoneyUpDialog, CDialogEx)
END_MESSAGE_MAP()


// CNoMoneyUpDialog message handlers

void CNoMoneyUpDialog::SetPlacePrice(CString place, int price)
{
	this->place = place;
	this->price = price;
}

BOOL CNoMoneyUpDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	SetDlgItemText(IDC_PLACE_TEXT, place);
	SetDlgItemInt(IDC_PRICE_TEXT, price);
	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
