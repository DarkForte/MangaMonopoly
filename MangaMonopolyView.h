
// MangaMonopolyView.h : CMangaMonopolyView ��Ľӿ�
//

#pragma once
#include "Player.h"
#include "Panel.h"



class CMangaMonopolyView : public CView
{
protected: // �������л�����
	CMangaMonopolyView();
	DECLARE_DYNCREATE(CMangaMonopolyView)

// ����
public:
	CMangaMonopolyDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CMangaMonopolyView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // MangaMonopolyView.cpp �еĵ��԰汾
inline CMangaMonopolyDoc* CMangaMonopolyView::GetDocument() const
   { return reinterpret_cast<CMangaMonopolyDoc*>(m_pDocument); }
#endif

