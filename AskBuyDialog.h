#pragma once


// CAskBuyDialog �Ի���

class CAskBuyDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CAskBuyDialog)

public:
	CAskBuyDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAskBuyDialog();

// �Ի�������
	enum { IDD = IDD_ASKBUYDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
