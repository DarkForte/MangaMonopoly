
// MangaMonopolyView.h : CMangaMonopolyView 类的接口
//

#pragma once
#include "Player.h"
#include "Panel.h"



class CMangaMonopolyView : public CView
{
protected: // 仅从序列化创建
	CMangaMonopolyView();
	DECLARE_DYNCREATE(CMangaMonopolyView)

// 特性
public:
	CMangaMonopolyDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CMangaMonopolyView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
//Customized variables
public:
	CImage game_map;
	CImage info_bg;
	CImage dice;
	CImage star_back;
	CImage player_mark[CPublic::SUPPORT_PLAYER+1];
	CDC mdc;
	
	CString string_buffer;




	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBuyBooks();
	afx_msg void OnHistoryPrice();
	afx_msg void OnSellBooks();
	afx_msg void OnCompareAll();
	afx_msg void OnAppHelp();
//	afx_msg void OnAbout();
//	afx_msg void OnFileLoad();
};

#ifndef _DEBUG  // MangaMonopolyView.cpp 中的调试版本
inline CMangaMonopolyDoc* CMangaMonopolyView::GetDocument() const
   { return reinterpret_cast<CMangaMonopolyDoc*>(m_pDocument); }
#endif

