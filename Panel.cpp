#include "StdAfx.h"
#include "Panel.h"

IMPLEMENT_SERIAL(CPanel, CObject,1)

CString CPanel::place_names[41] = {L"0", L"Ê¾Àý"};
int CPanel::prices[41]={0};

CPanel::CPanel(void)
	: occupied(false)
{
}


CPanel::~CPanel(void)
{
}

CPanel::CPanel(const CPanel &x)
{
	type = x.type;
	owner = x.owner;
	price = x.price;
	name = x.name;
	occupied = x.occupied;
	level = x.level;
	cod = x.cod;
}

void CPanel::InitPlace()
{
    int i;
	for(i=0;i<=39;i++)
		place_names[i].Format(L"µØµã%d", i+1);
}

void CPanel::InitPanelClass()
{
	InitPlace();

	int i;
	for(i=0;i<=39;i++)
	{
		prices[i] = i;
	}
	return;
}

void CPanel::SetPanel(int n)
{
	name = place_names[n];
	price = prices[n];
	occupied = false;
	
	if(n==0)
		type = CPublic::START;
	else if(n==10)
		type = CPublic::JAIL;
	else if(n==20)
		type = CPublic::SAFE;
	else if(n==30)
		type = CPublic::GO_TO_JAIL;
	else if (n==2 || n==7 || n==17 || n==22 || n==33 || n==36)
		type = CPublic::CHANCE;
	else if (n==5 || n==15 || n==25 || n==35)
		type = CPublic::RAILWAY;
	else if(n==12 || n==28)
		type = CPublic::FACILITY;
	else if(n==4 || n== 38)
		type = CPublic::BUZZ;
	else	
		type = CPublic::NORMAL;

	owner = 0;
	level=0;
	cod.SetPoint(0,0);
	return;
}

void CPanel::toZero()
{
	owner = 0;
	occupied = false;
	level = 0;
	return;
}

void CPanel::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
		ar<<type<<owner<<price;
		ar<<name<<occupied<<level;
		ar<<cod.x<<cod.y;
	}
	else
	{	// loading code
		ar>>type>>owner>>price;
		ar>>name>>occupied>>level;
		ar>>cod.x>>cod.y;
	}
}
