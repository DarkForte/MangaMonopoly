#pragma once
#include "afxwin.h"
#include <queue>
using namespace std;

// CHistoryDialog dialog

class CHistoryDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CHistoryDialog)

public:
	CHistoryDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CHistoryDialog();

// Dialog Data
	enum { IDD = IDD_HISTORY_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CStatic history_pic;
	CStatic line_a;
	CStatic line_b;
	CStatic line_c;
	int prices[4][31];
	int p_prices;

	void setData(int p[4][31], int p_p);
	void DrawLine(CDC* main_pic, int num, CRect history_rect, int factor);
	void DrawSmallLine(CDC* now_dc, int s_x, int s_y, int e_x, int e_y);
	virtual BOOL OnInitDialog();
	int CalcFactor();
	afx_msg void OnPaint();
};
