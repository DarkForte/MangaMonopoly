// AskDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MangaMonopoly.h"
#include "AskDialog.h"
#include "afxdialogex.h"


// CAskDialog �Ի���

IMPLEMENT_DYNAMIC(CAskDialog, CDialogEx)

CAskDialog::CAskDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAskDialog::IDD, pParent)
{

}

CAskDialog::~CAskDialog()
{
}

void CAskDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_PLACE_TEXT, place_text);
	//  DDX_Text(pDX, IDC_PRICE_TEXT, price_text);
	DDX_Control(pDX, IDC_ASKPIC, ask_icon_control);
}

void CAskDialog::SetInfo(CString place, int price, int type)
{
	this->place = place;
	this->price = price;
	this->type = type;

	if(type == CPublic::BUY)
		icon.Load(L"picture\\Ask.jpg");
	else
		icon.Load(L"picture\\Ask2.jpg");

	
}


BEGIN_MESSAGE_MAP(CAskDialog, CDialogEx)
	//ON_STN_CLICKED(IDC_PLACE_TEXT, &CAskDialog::OnStnClickedPlaceText)
	//ON_BN_CLICKED(IDOK, &CAskDialog::OnBnClickedOk)
	//ON_BN_CLICKED(IDC_BUTTON1, &CAskDialog::OnBnClickedButton1)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CAskDialog ��Ϣ�������


BOOL CAskDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if(type == CPublic::BUY)
		ask_icon_control.MoveWindow(40, 55, icon.GetWidth(), icon.GetHeight());
	else
		ask_icon_control.MoveWindow(40, 65, icon.GetWidth(), icon.GetHeight());

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString price_name, ask_text;

	if(type == CPublic::BUY)
	{
		price_name = L"�۸�";
		ask_text = L"Ͷ����";
	}
	else if(type == CPublic::UPGRADE)
	{
		price_name = L"����Ͷ�ʼ۸�";
		ask_text = L"Ҫ����Ͷ����";
	}

	SetDlgItemText(IDC_PLACE_TEXT, place);
	SetDlgItemText(IDC_PRICE_NAME, price_name);
	SetDlgItemInt(IDC_PRICE_TEXT, price);
	SetDlgItemText(IDC_QUESTION_TEXT, ask_text);

	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


/*void CAskDialog::OnStnClickedPlaceText()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


/*void CAskBuyDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	CDialogEx::OnOK();
}
*/

void CAskDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for painting messages
	CDC * pdc = ask_icon_control.GetDC();
	icon.Draw(*pdc, 0, 0, icon.GetWidth(), icon.GetHeight() );
	pdc->DeleteDC();

	return;
}
