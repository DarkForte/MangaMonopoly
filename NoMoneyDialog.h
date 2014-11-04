#pragma once
#include "afxwin.h"


// CNoMoneyDialog dialog

class CNoMoneyDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CNoMoneyDialog)

public:
	CNoMoneyDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNoMoneyDialog();

// Dialog Data
	enum { IDD = IDD_NO_MONEY_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()


public:
	virtual BOOL OnInitDialog();

public:
	CString place;
	int price;
	int type;
	CImage icon;

	void SetInfo(CString place, int price, int type);
	CStatic nomoney_icon_control;
	afx_msg void OnPaint();
	afx_msg void OnStnClickedPriceText();
};
