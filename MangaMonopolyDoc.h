
// MangaMonopolyDoc.h : CMangaMonopolyDoc 类的接口
//


#pragma once
#include "Player.h"
#include "Panel.h"
#include "Public.h"
using namespace std;

class CMangaMonopolyDoc : public CDocument
{
protected: // 仅从序列化创建
	CMangaMonopolyDoc();
	DECLARE_DYNCREATE(CMangaMonopolyDoc)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CMangaMonopolyDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

	//Customized Variables

public:
	CPlayer player[6];
	int now_player;
	int now_state;
	CPanel panel[40];
	int book_price[4];
	int book_history_price[4][31];
	int p_book_price;

	void InitMap();
	void MovePlayerOnce();
	void ChangeState(int target);
	void NextPlayer();
	void RefreshMoney();

	CString AskNowPlaceName();
	int AskNowPrice();
	int AskNowPlaceNum(void);
	CPanel GetNowPanel(void);
	int GetCurrentMoney();

	bool CanBuy(void);
	void Buy();

	void CutMoney(int amount);
	void GiveMoney(int amount, int target);

	bool CanUpgrade();
	void Upgrade();
	
	bool Buyable();
	bool isTax();

	int CalcNowTotal();

	void BuyBook(int amount[]);
	void SellBook(int amount[]);
	void UpdateBookPrice();

	int rest_num;
    bool KnockOut();
    void DeletePlayer();
	int GetLastPlayer();
	bool PlayerAlive(int q);

};
