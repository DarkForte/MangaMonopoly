// AskBuyDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MangaMonopoly.h"
#include "AskBuyDialog.h"
#include "afxdialogex.h"


// CAskBuyDialog �Ի���

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


// CAskBuyDialog ��Ϣ�������


BOOL CAskBuyDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	SetDlgItemText(IDC_PLACE_TEXT, place);
	SetDlgItemInt(IDC_PRICE_TEXT, price);
	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CAskBuyDialog::OnStnClickedPlaceText()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
