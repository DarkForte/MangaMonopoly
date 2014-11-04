#pragma once
#include "afxwin.h"


// CPenaltyDialog dialog

class CPenaltyDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CPenaltyDialog)

public:
	CPenaltyDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPenaltyDialog();

// Dialog Data
	enum { IDD = IDD_PENALTY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();

	///////////////Customized variables
public:
	CString place;
	int price;
	int owner;
	int type;
	CImage icon;

	void SetInfo(CString place, int price, int owner, int type);
	CStatic penalty_icon_control;
	afx_msg void OnPaint();
};
