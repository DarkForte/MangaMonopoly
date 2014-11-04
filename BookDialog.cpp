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
		title.Format(L"买入漫画书");
		greeting.Format(L"要买入多少漫画书？");
	}
	else
	{
		title.Format(L"卖出漫画书");
		greeting.Format(L"要卖出多少漫画书？");
	}

	int i;
	for(i=1;i<=3;i++)
		book_price_text[i].Format(L"价格：%d", book_price[i]);

	book1_num = 0;
	book2_num = 0;
	book3_num = 0;

	total_text.Format(L"价格总计：0");
	after_text.Format(L"剩余现金：%d", now_money);

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

		total_text.Format(L"价格总计：%d", now_total);
		after_text.Format(L"剩余现金：%d", now_after);

		UpdateData(false);
	}
	else
	{
		int now_total = book1_num*book_price[1] + book2_num * book_price[2] + book3_num * book_price[3];
		int now_after = now_money + now_total;

		total_text.Format(L"价格总计：%d", now_total);
		after_text.Format(L"剩余现金：%d", now_after);

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
			MessageBox(L"现金好像不够了……");
			return;
		}
	}
	else 
	{
		if(book1_num > now_book[1])
		{
			MessageBox(L"漫画书1并没有那么多");
			return;
		}
		else if(book2_num > now_book[2])
		{
			MessageBox(L"漫画书2并没有那么多");
			return;
		}
	    else if(book3_num > now_book[3])
		{
			MessageBox(L"漫画书1并没有那么多");
			return;
		}
		
	}
	CDialogEx::OnOK();
}
