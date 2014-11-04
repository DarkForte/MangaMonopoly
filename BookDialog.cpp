// BookDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MangaMonopoly.h"
#include "BookDialog.h"
#include "afxdialogex.h"


// CBookDialog dialog

IMPLEMENT_DYNAMIC(CBookDialog, CDialogEx)

CBookDialog::CBookDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBookDialog::IDD, pParent)
	, total_text(_T(""))
	, after_text(_T(""))
	, book1_num(0)
	, book2_num(0)
	, book3_num(0)
{

}

CBookDialog::~CBookDialog()
{
}

void CBookDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TOTAL, total_text);
	DDX_Text(pDX, IDC_AFTER, after_text);
	DDX_Text(pDX, IDC_BOOK1, book1_num);
	DDV_MinMaxInt(pDX, book1_num, 0, 1000000000);
	DDX_Text(pDX, IDC_BOOK2, book2_num);
	DDV_MinMaxInt(pDX, book2_num, 0, 1000000000);
	DDX_Text(pDX, IDC_BOOK3, book3_num);
	DDV_MinMaxInt(pDX, book3_num, 0, 1000000000);
}


BEGIN_MESSAGE_MAP(CBookDialog, CDialogEx)
	ON_EN_CHANGE(IDC_BOOK1, &CBookDialog::OnChangeBook1)
	ON_EN_CHANGE(IDC_BOOK2, &CBookDialog::OnChangeBook2)
	ON_EN_CHANGE(IDC_BOOK3, &CBookDialog::OnChangeBook3)
	ON_BN_CLICKED(IDOK, &CBookDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CBookDialog message handlers

void CBookDialog::SetInfo(int buy, int book_price[], int now_money, int now_book[])
{
	this->buy = buy;
    int i;
	for(i=1;i<=3;i++)
		this->book_price[i] = book_price[i];
    this->now_money = now_money;
	for(i=1;i<=3;i++)
		this->now_book[i] = now_book[i];

	return;
}

BOOL CBookDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	CString title;
	CString greeting;
	CString book_price_text[4];
	CString total;
	CString after;

	if(buy)
	{
		title.Format(L"����������");
		greeting.Format(L"Ҫ������������飿");
	}
	else
	{
		title.Format(L"����������");
		greeting.Format(L"Ҫ�������������飿");
	}

	int i;
	for(i=1;i<=3;i++)
		book_price_text[i].Format(L"�۸�%d", book_price[i]);

	book1_num = 0;
	book2_num = 0;
	book3_num = 0;

	total_text.Format(L"�۸��ܼƣ�0");
	after_text.Format(L"ʣ���ֽ�%d", now_money);

	SetWindowText(title);
	
	SetDlgItemText(IDC_GREETING, greeting);
	SetDlgItemText(IDC_BOOK1PRICE, book_price_text[1]);
	SetDlgItemText(IDC_BOOK2PRICE, book_price_text[2]);
	SetDlgItemText(IDC_BOOK3PRICE, book_price_text[3]);

	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CBookDialog::OnChangeBook()
{
	UpdateData(true);
	if(buy)
	{
		int now_total = book1_num*book_price[1] + book2_num * book_price[2] + book3_num * book_price[3];
		int now_after = now_money - now_total;

		total_text.Format(L"�۸��ܼƣ�%d", now_total);
		after_text.Format(L"ʣ���ֽ�%d", now_after);

		UpdateData(false);
	}
	else
	{
		int now_total = book1_num*book_price[1] + book2_num * book_price[2] + book3_num * book_price[3];
		int now_after = now_money + now_total;

		total_text.Format(L"�۸��ܼƣ�%d", now_total);
		after_text.Format(L"ʣ���ֽ�%d", now_after);

		UpdateData(false);
	}
}

void CBookDialog::OnChangeBook1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	OnChangeBook();
	
}


void CBookDialog::OnChangeBook2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	OnChangeBook();
}


void CBookDialog::OnChangeBook3()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	OnChangeBook();
}

void CBookDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
    if(buy)
	{
		int now_total = book1_num*book_price[1] + book2_num * book_price[2] + book3_num * book_price[3];
		int now_after = now_money - now_total;

		if(now_after <= 0)
		{
			MessageBox(L"�ֽ���񲻹��ˡ���");
			return;
		}
	}
	else 
	{
		if(book1_num > now_book[1])
		{
			MessageBox(L"������1��û����ô��");
			return;
		}
		else if(book2_num > now_book[2])
		{
			MessageBox(L"������2��û����ô��");
			return;
		}
	    else if(book3_num > now_book[3])
		{
			MessageBox(L"������1��û����ô��");
			return;
		}
		
	}
	CDialogEx::OnOK();
}
