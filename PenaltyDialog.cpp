// PenaltyDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MangaMonopoly.h"
#include "PenaltyDialog.h"
#include "afxdialogex.h"


// CPenaltyDialog dialog

IMPLEMENT_DYNAMIC(CPenaltyDialog, CDialogEx)

CPenaltyDialog::CPenaltyDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPenaltyDialog::IDD, pParent)
{

}

CPenaltyDialog::~CPenaltyDialog()
{
}

void CPenaltyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PENALTYICON, penalty_icon_control);
}

void CPenaltyDialog::SetInfo(CString place, int price, int owner, int type = CPublic::GIVE)
{
	this->place = place;
	this->price = price;
	this->owner = owner;
	this->type = type;

	if(type == CPublic::GIVE)
		icon.Load(L"picture\\Penalty.jpg");
	else if(type == CPublic::TAX)
		icon.Load(L"picture\\Tax.jpg");
}

BOOL CPenaltyDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	if(type == CPublic::GIVE)
	{
		penalty_icon_control.MoveWindow(47,79, icon.GetWidth(), icon.GetHeight());
		CString owner_info;
		owner_info.Format(L"这里的所有者是：玩家%d", owner);
		CString fine_info;
		fine_info.Format(L"您需要支付%d元的过路费。" , price);

		SetDlgItemText(IDC_PLACE_TEXT, place);
		SetDlgItemText(IDC_OWNER_INFO, owner_info);
		SetDlgItemText(IDC_PENALTY_INFO, fine_info);
	}
	else if(type == CPublic::TAX)
	{
		penalty_icon_control.MoveWindow(30, 79, icon.GetWidth(), icon.GetHeight());
		CString place_info;
		place_info.Format(L"这里是个人所得税中心，\n您主动纳税真是太好了！");
		CString tax_info;
		tax_info.Format(L"请您缴纳%d元的个人所得税！", CPublic::TAX_MONEY);

		SetDlgItemText(IDC_PLACE_TEXT, place);
		SetDlgItemText(IDC_OWNER_INFO, place_info);
		SetDlgItemText(IDC_PENALTY_INFO, tax_info);
	}
	
	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


BEGIN_MESSAGE_MAP(CPenaltyDialog, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CPenaltyDialog message handlers


void CPenaltyDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for painting messages

	CDC * pdc = penalty_icon_control.GetDC();
	icon.Draw(*pdc, 0, 0, icon.GetWidth(), icon.GetHeight() );
	pdc->DeleteDC();

	return;
}
