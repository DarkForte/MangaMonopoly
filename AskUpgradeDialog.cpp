// AskUpgradeDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MangaMonopoly.h"
#include "AskUpgradeDialog.h"
#include "afxdialogex.h"


// CAskUpgradeDialog dialog

IMPLEMENT_DYNAMIC(CAskUpgradeDialog, CDialogEx)

CAskUpgradeDialog::CAskUpgradeDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAskUpgradeDialog::IDD, pParent)
{

}

CAskUpgradeDialog::~CAskUpgradeDialog()
{
}

void CAskUpgradeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAskUpgradeDialog, CDialogEx)
END_MESSAGE_MAP()


// CAskUpgradeDialog message handlers


void CAskUpgradeDialog::SetPlacePrice(CString place, int price)
{
	this->place = place;
	this->price = price;
}

BOOL CAskUpgradeDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	SetDlgItemText(IDC_PLACE_TEXT, place);
	SetDlgItemInt(IDC_PRICE_TEXT, price);
	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
