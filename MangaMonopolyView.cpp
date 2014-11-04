
// MangaMonopolyView.cpp : CMangaMonopolyView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MangaMonopoly.h"
#endif

#include "MangaMonopolyDoc.h"
#include "MangaMonopolyView.h"
#include "Player.h"
#include<time.h>
#include "AskDialog.h"
#include "NoMoneyDialog.h"
#include "PenaltyDialog.h"
#include "BookDialog.h"
#include "HistoryDialog.h"
#include "CompareDialog.h"
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMangaMonopolyView

IMPLEMENT_DYNCREATE(CMangaMonopolyView, CView)

BEGIN_MESSAGE_MAP(CMangaMonopolyView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_BUY_BOOKS, &CMangaMonopolyView::OnBuyBooks)
	ON_COMMAND(ID_HISTORY_PRICE, &CMangaMonopolyView::OnHistoryPrice)
	ON_COMMAND(ID_SELL_BOOKS, &CMangaMonopolyView::OnSellBooks)
	ON_COMMAND(ID_COMPARE_ALL, &CMangaMonopolyView::OnCompareAll)
	ON_COMMAND(ID_APP_HELP, &CMangaMonopolyView::OnAppHelp)
//	ON_COMMAND(ID_ABOUT, &CMangaMonopolyView::OnAbout)
//ON_COMMAND(ID_FILE_LOAD, &CMangaMonopolyView::OnFileLoad)
END_MESSAGE_MAP()

/*
0: start
10: jail
20:free park
30: goto jail
40 = 0
*/

void TransparentPNG(CImage *png)
{
	for(int i = 0; i <png->GetWidth(); i++)
	{
		for(int j = 0; j <png->GetHeight(); j++)
		{
			unsigned char* pucColor = reinterpret_cast<unsigned char*>(png->GetPixelAddress(i , j));
			pucColor[0] = pucColor[0] *pucColor[3] / 255;
			pucColor[1] = pucColor[1] *pucColor[3] / 255;
			pucColor[2] = pucColor[2] *pucColor[3] / 255;
		}
	}
}


// CMangaMonopolyView 构造/析构

CMangaMonopolyView::CMangaMonopolyView()
{
	// TODO: 在此处添加构造代码
	game_map.Load(L"picture\\map.bmp");
	dice.Load(L"picture\\dice.png");
	star_back.Load(L"picture\\star_back.jpg");
	TransparentPNG(&dice);

	int i;
	for (i=1;i<=CPublic::SUPPORT_PLAYER; i++)
	{
		string_buffer.Format(L"picture\\house%d.png", i);
		player_mark[i].Load(string_buffer);
		TransparentPNG(&player_mark[i]);
	}

	srand( (unsigned)time(0) );
}

CMangaMonopolyView::~CMangaMonopolyView()
{
}

BOOL CMangaMonopolyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	return CView::PreCreateWindow(cs);
}



// CMangaMonopolyView 绘制

void CMangaMonopolyView::OnDraw(CDC* pDC)
{
	CMangaMonopolyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	CRect client_rect;
	GetClientRect(&client_rect);
	CBitmap cache_bitmap;

	mdc.CreateCompatibleDC(pDC);
	cache_bitmap.CreateCompatibleBitmap(pDC,client_rect.Width(),client_rect.Height());
	mdc.SelectObject(cache_bitmap);

	//////////////////////////Draw Background

	star_back.Draw(mdc, 30,0, star_back.GetWidth(), star_back.GetHeight());

	///////////////////////////Draw Map

	game_map.Draw(mdc,0, 0, game_map.GetWidth(), game_map.GetHeight());
	if(pDoc->now_state == CPublic::WAIT_DICE)
		dice.Draw(mdc, 250,250, dice.GetWidth(), dice.GetHeight());
	
	/////////////////////// Draw Player

	int i;
	for(i=1;i<=CPublic::SUPPORT_PLAYER;i++)
	{
		if(pDoc->PlayerAlive(i) == false)
			continue;
		CPoint now_cod = ( pDoc->panel[pDoc->player[i].now_place] ).cod;
		pDoc->player[i].player_icon.Draw(  mdc  , now_cod.x  , now_cod.y  , pDoc->player[i].player_icon.GetWidth()  , pDoc->player[i].player_icon.GetHeight() );
	}

	//////////////////////////////////////////// Draw Houses

	for(i=1;i<=10;i++)
	{
		if(pDoc -> panel[i].occupied == true)
		{
			CPanel now_panel = pDoc->panel[i];
			int j;
			for(j=1;j<=now_panel.level;j++)
			{
				if(j<=2)
					player_mark[ now_panel.owner ].Draw(  mdc , now_panel.cod.x - 12 + 20*(j-1) , now_panel.cod.y - 45, player_mark[ now_panel.owner ].GetWidth() , player_mark[ now_panel.owner ].GetHeight() );
				else if(j<=4)
					player_mark[ now_panel.owner ].Draw(  mdc , now_panel.cod.x - 12 + 20*(j-3) , now_panel.cod.y - 25, player_mark[ now_panel.owner ].GetWidth() , player_mark[ now_panel.owner ].GetHeight() );
			}
		}
	}

	for(i=11;i<=20;i++)
	{
		if(pDoc -> panel[i].occupied == true)
		{
			CPanel now_panel = pDoc->panel[i];
			int j;
			for(j=1;j<=now_panel.level;j++)
			{
				if(j<=2)
					player_mark[ now_panel.owner ].Draw(  mdc , now_panel.cod.x +45 , now_panel.cod.y - 15 + 20*(j-1), player_mark[ now_panel.owner ].GetWidth() , player_mark[ now_panel.owner ].GetHeight() );
				else if(j<=4)
					player_mark[ now_panel.owner ].Draw(  mdc , now_panel.cod.x +25 , now_panel.cod.y - 15 + 20*(j-3), player_mark[ now_panel.owner ].GetWidth() , player_mark[ now_panel.owner ].GetHeight() );
			}
		}
	}

	for(i=21;i<=30;i++)
	{
		if(pDoc -> panel[i].occupied == true)
		{
			CPanel now_panel = pDoc->panel[i];
			int j;
			for(j=1;j<=now_panel.level;j++)
			{
				if(j<=2)
					player_mark[ now_panel.owner ].Draw(  mdc , now_panel.cod.x +15 - 20*(j-1) , now_panel.cod.y + 45, player_mark[ now_panel.owner ].GetWidth() , player_mark[ now_panel.owner ].GetHeight() );
				else if(j<=4)
					player_mark[ now_panel.owner ].Draw(  mdc , now_panel.cod.x +15 - 20*(j-3) , now_panel.cod.y + 25, player_mark[ now_panel.owner ].GetWidth() , player_mark[ now_panel.owner ].GetHeight() );
			}
		}
	}

	for(i=30;i<=39;i++)
	{
		if(pDoc -> panel[i].occupied == true)
		{
			CPanel now_panel = pDoc->panel[i];
			int j;
			for(j=1;j<=now_panel.level;j++)
			{
				if(j<=2)
					player_mark[ now_panel.owner ].Draw(  mdc , now_panel.cod.x -45 , now_panel.cod.y + 17 - 20*(j-1), player_mark[ now_panel.owner ].GetWidth() , player_mark[ now_panel.owner ].GetHeight() );
				else if(j<=4)
					player_mark[ now_panel.owner ].Draw(  mdc , now_panel.cod.x -25 , now_panel.cod.y + 17 - 20*(j-3), player_mark[ now_panel.owner ].GetWidth() , player_mark[ now_panel.owner ].GetHeight() );
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////////

	pDC->BitBlt(0, 0, client_rect.Width() ,client_rect.Height() ,&mdc, 0, 0, SRCCOPY);

	int now_player = pDoc->now_player;

	CFont font;
	font.CreatePointFont(120, L"微软雅黑", pDC);
	pDC->SelectObject(font);

	string_buffer.Format(L"现在轮到第%d位玩家了", now_player);
	pDC->SetTextColor( RGB(100,100,100) );
	pDC->TextOutW(700, 50, string_buffer);

	string_buffer.Format(L"现金：%d", pDoc->player[ now_player ].money );
	pDC->TextOutW(700, 100, string_buffer);
	string_buffer.Format(L"漫画书1：%d 本", pDoc->player[ now_player ]. book[1]);
	pDC->TextOutW(700, 150, string_buffer);
	string_buffer.Format(L"漫画书2：%d 本", pDoc->player[ now_player ]. book[2]);
	pDC->TextOutW(700, 200, string_buffer);
	string_buffer.Format(L"漫画书3：%d 本", pDoc->player[ now_player ]. book[3] );
	pDC->TextOutW(700,250, string_buffer);
	string_buffer.Format(L"总资产： %d", pDoc->player[ now_player ].total );
	pDC->TextOutW(700,300, string_buffer);

	string_buffer.Format(L"今天的漫画书价格：");
	pDC->TextOutW(700,350, string_buffer);
	string_buffer.Format(L"漫画书1：%d", pDoc->book_price[1]);
	pDC->TextOutW(700,400, string_buffer);
	string_buffer.Format(L"漫画书2：%d", pDoc->book_price[2]);
	pDC->TextOutW(700,450, string_buffer);
	string_buffer.Format(L"漫画书3：%d", pDoc->book_price[3]);
	pDC->TextOutW(700,500, string_buffer);

	ValidateRect(client_rect);

	cache_bitmap.DeleteObject();
	mdc.DeleteDC();
	font.DeleteObject();
}

void CMangaMonopolyView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMangaMonopolyView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMangaMonopolyView 诊断

#ifdef _DEBUG
void CMangaMonopolyView::AssertValid() const
{
	CView::AssertValid();
}

void CMangaMonopolyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMangaMonopolyDoc* CMangaMonopolyView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMangaMonopolyDoc)));
	return (CMangaMonopolyDoc*)m_pDocument;
}
#endif //_DEBUG


// CMangaMonopolyView 消息处理程序


void CMangaMonopolyView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CMangaMonopolyDoc* pDoc = GetDocument();
	if(pDoc->now_state == CPublic::WAIT_DICE) // Ready to go
	{
		if(point.x >= 250 && point.x <= 250 + dice.GetWidth() && point.y >= 250 && point.y <= 250 + dice.GetHeight() )
		{
			int step1 = rand()%6+1;
			int step2 = rand()%6+1;
			int step = step1 + step2;

			CDC* dc = GetDC();
			CFont font;
			font.CreatePointFont(120, L"微软雅黑", dc);
			dc->SelectObject(font);
			
			string_buffer.Format(L"投出了 %d 点！", step);
			dc->TextOutW(248, 403, string_buffer);
			font.DeleteObject();
			dc->DeleteDC();
			
			pDoc->ChangeState(CPublic::WAIT_WALK);
			Sleep(500);
			dc = GetDC();
			int i;
			for(i=1;i<=step;i++)
			{
				Sleep(100);
			    pDoc->MovePlayerOnce();
				OnDraw(dc);
			}
			dc->DeleteDC();
			/////////////////////////////////////////////////// Event Handling

			int now_player= pDoc->now_player;

			CPanel now_panel = pDoc->GetNowPanel();

			//1. If it is a buyable panel
			if( pDoc->Buyable() )
			{
				if(now_panel.occupied == false) //buy
				{
					if( pDoc->CanBuy() ) // can buy
					{
						CAskDialog ask_buy_dialog;
						ask_buy_dialog.SetInfo(now_panel.name, now_panel.price, CPublic::BUY);
						if( ask_buy_dialog.DoModal()  == IDOK)
						{
							pDoc->Buy();
						}
					}
					else //no money to buy
					{
						CNoMoneyDialog no_money_dialog;
						no_money_dialog.SetInfo(now_panel.name, now_panel.price, CPublic::BUY);
						no_money_dialog.DoModal();
					}
				}

				else if(now_panel.occupied == true && now_panel.owner != now_player) // buzz
				{
					CPenaltyDialog penalty_dialog;
					penalty_dialog.SetInfo(now_panel.name, now_panel.price * now_panel.level, now_panel.owner, CPublic::GIVE);
					penalty_dialog.DoModal();
					pDoc->GiveMoney(now_panel.price * now_panel.level, now_panel.owner);
				}
				else if(now_panel.occupied == true && now_panel.owner == now_player) //upgrade
				{
					if( pDoc->CanUpgrade() ) 
					{
						CAskDialog ask_upgrade_dialog;
						ask_upgrade_dialog.SetInfo(now_panel.name, now_panel.price, CPublic::UPGRADE);
						if ( ask_upgrade_dialog.DoModal() == IDOK )
						{
							pDoc->Upgrade();
						}
					}
					else
					{
						CNoMoneyDialog no_money_up_dialog;
						no_money_up_dialog.SetInfo(now_panel.name, now_panel.price, CPublic::UPGRADE);
						no_money_up_dialog.DoModal();
					}
				}
			}

			//2. if it is a penalty panel
			else if( pDoc->isTax() )
			{
	            CPenaltyDialog penalty_dialog;
				penalty_dialog.SetInfo(now_panel.name, now_panel.price, now_panel.owner, CPublic::TAX);
				penalty_dialog.DoModal();
				pDoc->CutMoney(CPublic::TAX_MONEY);
			}

			pDoc->RefreshMoney();
			if(pDoc->KnockOut())
			{
				CString s;
				s.Format(L"玩家%d破产了！", pDoc->now_player);
				MessageBox(s);
				pDoc->DeletePlayer();
				if(pDoc->rest_num == 1)
				{
					int last_player;
					last_player = pDoc->GetLastPlayer();
					CString victory_message;
					victory_message.Format(L"恭喜玩家%d取得了最后的胜利！", last_player);
					MessageBox(victory_message);
					pDoc->ChangeState(CPublic::GAME_OVER);
				}
			}

			/////////////////////////////Refresh Screen

			dc = GetDC();
			OnDraw(dc);

			///////////////////////////Ready for next
			Sleep(500);
			if(pDoc->now_state == CPublic::WAIT_WALK)
			{
				pDoc->ChangeState(CPublic::WAIT_DICE);
				pDoc->NextPlayer();
			}
			
			dc = GetDC();
			OnDraw(dc);

			//////////////////////////////////End
			dc->DeleteDC();
		}

		pDoc->SetModifiedFlag();
	}

	CView::OnLButtonDown(nFlags, point);
}


void CMangaMonopolyView::OnBuyBooks()
{
	// TODO: Add your command handler code here
	CMangaMonopolyDoc* pDoc = GetDocument();
	CBookDialog BookDialog;
	BookDialog.SetInfo(1, pDoc->book_price, pDoc->GetCurrentMoney(), pDoc->player[pDoc->now_player].book);
	if( BookDialog.DoModal() == IDOK)
	{
		int buy_books[4];
		buy_books[1] = BookDialog.book1_num;
		buy_books[2] = BookDialog.book2_num;
		buy_books[3] = BookDialog.book3_num;

		pDoc->BuyBook(buy_books);

		CDC *dc = GetDC();
		OnDraw(dc);
		dc->DeleteDC();
	}
	pDoc->SetModifiedFlag();
}


void CMangaMonopolyView::OnSellBooks()
{
	// TODO: Add your command handler code here
	CMangaMonopolyDoc* pDoc = GetDocument();
	CBookDialog BookDialog;
	BookDialog.SetInfo(0, pDoc->book_price, pDoc->GetCurrentMoney(), pDoc->player[pDoc->now_player].book);
	if( BookDialog.DoModal()  == IDOK)
	{
		int sell_books[4];
		sell_books[1] = BookDialog.book1_num;
		sell_books[2] = BookDialog.book2_num;
		sell_books[3] = BookDialog.book3_num;

		pDoc->SellBook(sell_books);

		CDC *dc = GetDC();
		OnDraw(dc);
		dc->DeleteDC();
	}
	pDoc->SetModifiedFlag();
}


void CMangaMonopolyView::OnHistoryPrice()
{
	// TODO: Add your command handler code here
	CMangaMonopolyDoc *pDoc = GetDocument();
	CHistoryDialog history_dialog;
	history_dialog.setData(pDoc->book_history_price, pDoc->p_book_price);
	history_dialog.DoModal();
}


void CMangaMonopolyView::OnCompareAll()
{
	CMangaMonopolyDoc* pDoc = GetDocument();
	CCompareDialog dialog;
	dialog.setData(pDoc->player);
	dialog.DoModal();
}


void CMangaMonopolyView::OnAppHelp()
{
	// TODO: Add your command handler code here
}


//void CMangaMonopolyView::OnAbout()
//{
//	// TODO: Add your command handler code here
//}


//void CMangaMonopolyView::OnFileLoad()
//{
//	// TODO: Add your command handler code here
//	CDC* dc = GetDC();
//	OnDraw(dc);
//	dc->DeleteDC();
//}
