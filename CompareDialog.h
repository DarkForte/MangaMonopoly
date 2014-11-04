#pragma once
#include "afxwin.h"
#include "Player.h"


// CCompareDialog 对话框

class CCompareDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CCompareDialog)

public:
	CCompareDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCompareDialog();

// 对话框数据
	enum { IDD = IDD_COMPARE_DIALOG};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CStatic main_pic;
	CStatic rect_a;
	CStatic rect_b;

	CPlayer player[6];

	void setData(CPlayer pl[]);
	double CalcFactor();
	void DrawRect(CDC* dc, int num, int height, double factor);
	void DrawSmallRect(CDC* dc, CRect rect);
	afx_msg void OnPaint();
};
