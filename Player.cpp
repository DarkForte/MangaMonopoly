#include "StdAfx.h"
#include "Player.h"
#include "MangaMonopolyDoc.h"

IMPLEMENT_SERIAL(CPlayer, CObject, 1);

CPlayer::CPlayer()
{
}


CPlayer::~CPlayer(void)
{
}

CPlayer::CPlayer(const CPlayer &x)
{
	num = x.num;
	money = x.money;
	int i;
	for(i=1;i<=3;i++)
		book[i] = x.book[i];
    total = x.total;
	jail_days = x.jail_days;
	now_place = x.now_place;
	invest = x.invest;
	book_value = x.book_value;
	alive = alive;
}

void CPlayer:: Init(int n)
{
	num = n;
	money = 500;
	now_place = 0;
	memset(book,0,sizeof(book));
	jail_days = 0;
	invest = 0;
	book_value = 0;
	alive = true;

	CString string_buffer;
	string_buffer.Format(L"picture\\player%d.png", n);
	player_icon.Load(string_buffer);
	
	total=money + invest + book_value;
	return;
}

void CPlayer::NoPicInit(int n)
{
	num = n;
	money = 500;
	now_place = 0;
	memset(book,0,sizeof(book));
	jail_days = 0;
	invest = 0;
	book_value = 0;
	alive = true;

	total=money + invest + book_value;
	return;
}

void CPlayer:: Move(int steps)
{
	return;
}

void CPlayer::toZero()
{
	money = 0;
	now_place = 0;
	memset(book,0,sizeof(book));
	jail_days = 0;
	invest = 0;
	book_value = 0;
	alive = false;

	total=money + invest + book_value;
	return;
	
}

void CPlayer::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
		ar<<num<<money<<total<<jail_days<<now_place<<invest;
		ar<<book_value;
		ar<<alive;
		for(int i=1; i<=3; i++)
			ar<<book[i];
	}
	else
	{	// loading code
		ar>>num>>money>>total>>jail_days>>now_place>>invest>>book_value>>alive;
		for(int i=1; i<=3; i++)
			ar>>book[i];
	}
	return;
}
