#pragma once


// CAskUpgradeDialog dialog

class CAskUpgradeDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CAskUpgradeDialog)

public:
	CAskUpgradeDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAskUpgradeDialog();

// Dialog Data
	enum { IDD = IDD_ASKDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	///////////////Customized variables
public:
	CString place;
	int price;

	void SetPlacePrice(CString place, int price);
};
