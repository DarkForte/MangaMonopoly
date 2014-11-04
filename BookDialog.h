#pragma once


// CBookDialog dialog

class CBookDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CBookDialog)

public:
	CBookDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CBookDialog();

// Dialog Data
	enum { IDD = IDD_BOOK_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	int buy;
	int book_price[4];
	int now_money;
	int now_book[4];
	virtual BOOL OnInitDialog();
	void SetInfo(int buy, int book_price[], int now_money, int now_book[]);
	CString total_text;
	CString after_text;
	int book1_num;
	int book2_num;
	int book3_num;
	afx_msg void OnChangeBook1();
	afx_msg void OnChangeBook2();
	afx_msg void OnChangeBook3();

	void OnChangeBook();
	afx_msg void OnBnClickedOk();
};
