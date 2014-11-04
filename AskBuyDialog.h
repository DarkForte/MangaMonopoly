#pragma once


// CAskBuyDialog 对话框

class CAskBuyDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CAskBuyDialog)

public:
	CAskBuyDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAskBuyDialog();

// 对话框数据
	enum { IDD = IDD_ASKBUYDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()

public:
	
	virtual BOOL OnInitDialog();

	///////////////Customized variables
public:
	CString place;
	int price;

	void SetPlacePrice(CString place, int price);
//	CString place_text;
//	CString price_text;
	afx_msg void OnStnClickedPlaceText();
};
