#pragma once


// CNoMoneyUpDialog dialog

class CNoMoneyUpDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CNoMoneyUpDialog)

public:
	CNoMoneyUpDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNoMoneyUpDialog();

// Dialog Data
	enum { IDD = IDD_NO_MONEY_UP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	///////////////Customized variables
public:
	CString place;
	int price;

	void SetPlacePrice(CString place, int price);
	virtual BOOL OnInitDialog();
};
