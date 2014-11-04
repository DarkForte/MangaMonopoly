
// MangaMonopolyDoc.h : CMangaMonopolyDoc ��Ľӿ�
//


#pragma once
#include "Player.h"
#include "Panel.h"
#include "Public.h"
using namespace std;

class CMangaMonopolyDoc : public CDocument
{
protected: // �������л�����
	CMangaMonopolyDoc();
	DECLARE_DYNCREATE(CMangaMonopolyDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CMangaMonopolyDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
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
