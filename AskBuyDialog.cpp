// AskBuyDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "MangaMonopoly.h"
#include "AskBuyDialog.h"
#include "afxdialogex.h"


// CAskBuyDialog 对话框

IMPLEMENT_DYNAMIC(CAskBuyDialog, CDialogEx)

CAskBuyDialog::CAskBuyDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAskBuyDialog::IDD, pParent)
{

}

CAskBuyDialog::~CAskBuyDialog()
{
}

void CAskBuyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_PLACE_TEXT, place_text);
	//  DDX_Text(pDX, IDC_PRICE_TEXT, price_text);
}

void CAskBuyDialog::SetPlacePrice(CString place, int price)
{
	this->place = place;
	this->price = price;
}


BEGIN_MESSAGE_MAP(CAskBuyDialog, CDialogEx)
	ON_STN_CLICKED(IDC_PLACE_TEXT, &CAskBuyDialog::OnStnClickedPlaceText)
END_MESSAGE_MAP()


// CAskBuyDialog 消息处理程序


BOOL CAskBuyDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	SetDlgItemText(IDC_PLACE_TEXT, place);
	SetDlgItemInt(IDC_PRICE_TEXT, price);
	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CAskBuyDialog::OnStnClickedPlaceText()
{
	// TODO: 在此添加控件通知处理程序代码
}
