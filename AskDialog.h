#pragma once
#include "afxwin.h"


// CAskDialog 对话框

class CAskDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CAskDialog)

public:
	CAskDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAskDialog();

// 对话框数据
	enum { IDD = IDD_ASKDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()

public:
	
	virtual BOOL OnInitDialog();

	///////////////Customized variables
public:
	CString place;
	int price;
	int type;
	CImage icon;

	void SetInfo(CString place, int price, int type);
	afx_msg void OnStnClickedPlaceText();
	afx_msg void OnBnClickedOk();
//	afx_msg void OnEnChangeBook1();
	afx_msg void OnBnClickedButton1();
	CStatic ask_icon_control;
	afx_msg void OnPaint();
};
