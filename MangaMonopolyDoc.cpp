
// MangaMonopolyDoc.cpp : CMangaMonopolyDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MangaMonopoly.h"
#endif

#include "MangaMonopolyDoc.h"
#include "Panel.h"
#include "Player.h"
#include <time.h>
#include <propkey.h>
#include <queue>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMangaMonopolyDoc

IMPLEMENT_DYNCREATE(CMangaMonopolyDoc, CDocument)

BEGIN_MESSAGE_MAP(CMangaMonopolyDoc, CDocument)
END_MESSAGE_MAP()

///////////////////////////////////////////////////// Game Customized Functions
void CMangaMonopolyDoc::InitMap()
{
	CPanel::InitPanelClass();

	//panel[0].cod[1].SetPoint(591,596);
	//panel[0].cod[2].SetPoint(591,620);

	panel[0].SetPanel(0);
	panel[0].cod.SetPoint(590,618); 
	
	int i;
	for(i=1;i<=10;i++)
	{
		panel[i].SetPanel(i);
		panel[i].cod.SetPoint( panel[i-1].cod.x - CPublic::PWIDTH , panel[i-1].cod.y );
	}
    for (i=1;i<=10;i++)
    {
		if(i==1)
			panel[i].cod.x-=2;
		if(i<=3)
			panel[i].cod.x-=3;
		else if(i<=6)
			panel[i].cod.x-=1;
    }

	panel[10].cod.SetPoint(25, 590);

	for(i=11;i<=20;i++)
	{
		panel[i].SetPanel(i);
		panel[i].cod.SetPoint( panel[i-1].cod.x  , panel[i-1].cod.y - CPublic::PWIDTH );
	}

	panel[20].cod.SetPoint(52,23);

	for(i=21;i<=30;i++)
	{
		panel[i].SetPanel(i);
		panel[i].cod.SetPoint( panel[i-1].cod.x + CPublic::PWIDTH , panel[i-1].cod.y );
	}
	panel[29].cod.x -= 3;

	panel[30].cod.SetPoint(616,50);

	for(i=31;i<=39;i++)
	{
		panel[i].SetPanel(i);
		panel[i].cod.SetPoint( panel[i-1].cod.x , panel[i-1].cod.y + CPublic::PWIDTH );
	}
	return;
}

void CMangaMonopolyDoc::MovePlayerOnce()
{
	player[now_player].now_place = ( player[now_player].now_place + 1 ) % 40;
	return;
}

void CMangaMonopolyDoc::ChangeState(int target)
{
	now_state = target;
}

void CMangaMonopolyDoc::NextPlayer()
{
	bool book_update = false;
	int i = now_player+1;
	if(i==CPublic::SUPPORT_PLAYER+1)
	{
		i = 1;
		book_update = true;
	}
	while(player[i].alive == false)
	{
		i = i+1;
		if(i==CPublic::SUPPORT_PLAYER +1)
		{
			i=1;
			book_update = true;
		}
	}
	now_player = i;
	if(book_update)
		UpdateBookPrice();
	return;
}

void CMangaMonopolyDoc::RefreshMoney()
{
	int player_i;
	for(player_i =1 ; player_i <= CPublic::SUPPORT_PLAYER; player_i++)
	{
		player[player_i] .total = player[player_i].money + player[player_i].invest;
		player[player_i] .book_value = 0;

		int i;
		for(i=1;i<=3;i++)
		{
			player[player_i].book_value += player[player_i].book[i] * book_price[i];
		}

		player[player_i].total += player[player_i].book_value;
	}
	
	return;
}


int CMangaMonopolyDoc::AskNowPlaceNum()
{
	return player[now_player].now_place;
}

CString CMangaMonopolyDoc::AskNowPlaceName()
{
	return panel[ player[ now_player ]. now_place].name;
}

int CMangaMonopolyDoc::AskNowPrice()
{
	return panel[ player[ now_player ]. now_place].price;
}


CPanel CMangaMonopolyDoc::GetNowPanel()
{
	return panel[ player[ now_player ].now_place ];
}

int CMangaMonopolyDoc::GetCurrentMoney()
{
	return player[now_player].money;
}

bool CMangaMonopolyDoc::CanBuy(void)
{
	int now_point = player[now_player].now_place;
	if(player[now_player].money >= panel[ now_point ].price)
		return true;
	return false;
}

void CMangaMonopolyDoc::Buy()
{
	int now_point = player[now_player].now_place;
	player[now_player].money -= panel[now_point].price;
	player[now_player].invest += panel[now_point].price;
	panel[now_point].occupied = true;
	panel[now_point].owner = now_player;
	panel[now_point].level++;
}

void CMangaMonopolyDoc::CutMoney(int amount)
{
	player[now_player].money -= amount;
}

void CMangaMonopolyDoc::GiveMoney(int amount, int target)
{
	player[now_player].money -= amount;
	player[target].money += amount;
	return;
}

bool CMangaMonopolyDoc::CanUpgrade()
{
    int now_point = player[now_player].now_place;
	if(player[now_player].money >= panel[now_point].price)
		return true;
    return false;
}

void CMangaMonopolyDoc::Upgrade()
{
	int now_point = player[now_player].now_place;
	panel[now_point]. level++;
	return;
}

bool CMangaMonopolyDoc::Buyable()
{
	CPanel now_panel = panel [ player[now_player].now_place ];
	if(now_panel.type == CPublic::NORMAL || now_panel.type == CPublic::FACILITY || now_panel.type == CPublic::RAILWAY)
		return true;
	else 
		return false;
}

bool CMangaMonopolyDoc::isTax()
{
	int p = player[now_player].now_place;
	if(panel[p].type == CPublic::BUZZ)
		return true;
	else 
		return false;
}

int CMangaMonopolyDoc::CalcNowTotal()
{
	int money = player[now_player].money;
	int invest = player[now_player].invest;
	int book_money=0;
	int i;
	for(i=1;i<=3;i++)
		book_money += player[now_player].book[i] * book_price[i];
	
	return money + invest + book_money; 
}

void CMangaMonopolyDoc::BuyBook(int amount[])
{
	int cost = 0;
	int i;
	for(i=1; i<=3; i++)
	{
		cost += book_price[i] * amount[i];
		player[now_player].book[i] += amount[i];
	}
    player[now_player].money -= cost;
	RefreshMoney();
}

void CMangaMonopolyDoc::SellBook(int amount[])
{
	int cost = 0;
	int i;
	for(i=1; i<=3; i++)
	{
		cost += book_price[i] * amount[i];
		player[now_player].book[i] -= amount[i];
	}
	player[now_player].money += cost;
	RefreshMoney();
}

void CMangaMonopolyDoc::UpdateBookPrice()
{
	int i;
	p_book_price++;
	if(p_book_price == 31) // if more than 30 days then keep only the recent 30 days
	{
		for(int k=1; k<=3; k++)
		{
			for(i=1;i<=29;i++)
			{
				book_history_price[k][i] = book_history_price[k][i+1]; 
			}
		}
		p_book_price=30;
	}
	for(i=1;i<=3;i++)
	{
		double range = book_price[i] * 0.3;
		int tmp = rand() % ( (2*(int)range +1) );
		tmp -= (int)range;
		book_price[i] += tmp;

		book_history_price[i][p_book_price] = book_price[i];
	}

	RefreshMoney();
	return;
}

bool CMangaMonopolyDoc::KnockOut()
{
	if(player[now_player].money <= 0)
		return true;
	else
		return false;
}

void CMangaMonopolyDoc::DeletePlayer()
{
	player[now_player].toZero();
	rest_num--;

	//delete all panels owned by him
	int i;
	for(i=0; i<=39;i++)
	{
		if(panel[i].occupied && panel[i].owner == now_player)
		{
			panel[i].occupied = false;
			panel[i].owner = 0;
			panel[i].level = 0;
		}
	}
	return;
}

int CMangaMonopolyDoc::GetLastPlayer()
{
	int i;
	for(i=1; i<=CPublic::SUPPORT_PLAYER; i++)
	{
		if(player[i].alive)
			return i;
	}
	return -1;
}

bool CMangaMonopolyDoc::PlayerAlive(int q)
{
	return player[q].alive;
}


// CMangaMonopolyDoc 构造/析构

CMangaMonopolyDoc::CMangaMonopolyDoc()
{
	// TODO: 在此添加一次性构造代码
	
	InitMap();

	int i;
	for(i=1;i<= CPublic::SUPPORT_PLAYER;i++)
	{
		player[i].Init(i);
	}
	now_player=1;
	now_state = CPublic::WAIT_DICE;
	rest_num = CPublic::SUPPORT_PLAYER;

	p_book_price = 1;
	for(i=1;i<=3;i++)
	{
		book_price[i] = 10;
		book_history_price[i][p_book_price] = 10;
	}

	srand( (unsigned)time(0) );
	return;
}

CMangaMonopolyDoc::~CMangaMonopolyDoc()
{
}

BOOL CMangaMonopolyDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	int i;
	for(i=0; i<=39; i++)
	{
		panel[i].toZero();
	}
	for(i=1;i<= CPublic::SUPPORT_PLAYER;i++)
	{
		player[i].NoPicInit(i);
	}
	now_player=1;
	now_state = CPublic::WAIT_DICE;
	rest_num = CPublic::SUPPORT_PLAYER;

	p_book_price = 1;
	for(i=1;i<=3;i++)
	{
		book_price[i] = 10;
		book_history_price[i][p_book_price] = 10;
	}

	return TRUE;
}

// CMangaMonopolyDoc 序列化

void CMangaMonopolyDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
		ar<<now_player;
		ar<<now_state;
		int i;
		for(i=1;i<=3;i++)
			ar<<book_price[i];

		ar<<p_book_price;
		int j;
		for(i=1;i<=3;i++)
		{
			for(j=1;j<=p_book_price;j++)
			{
				ar<<book_history_price[i][j];
			}
		}

		ar<<rest_num;

		for(i=0;i<=39;i++)
			panel[i].Serialize(ar);

		for(i=1;i<=CPublic::SUPPORT_PLAYER; i++)
			player[i].Serialize(ar);


	}
	else
	{
		// TODO: 在此添加加载代码
		ar>>now_player;
		ar>>now_state;
		int i;
		for(i=1;i<=3;i++)
			ar>>book_price[i];

		ar>>p_book_price;
		int j;
		for(i=1;i<=3;i++)
		{
			for(j=1;j<=p_book_price;j++)
			{
				ar>>book_history_price[i][j];
			}
		}

		ar>>rest_num;

		for(i=0;i<=39;i++)
			panel[i].Serialize(ar);

		for(i=1;i<=CPublic::SUPPORT_PLAYER; i++)
			player[i].Serialize(ar);
	}
	UpdateAllViews(NULL); // update all views
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CMangaMonopolyDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CMangaMonopolyDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CMangaMonopolyDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMangaMonopolyDoc 诊断

#ifdef _DEBUG
void CMangaMonopolyDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMangaMonopolyDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMangaMonopolyDoc 命令





