#pragma once
class CPublic
{
public:
	static const int WAIT_DICE = 1;
	static const int WAIT_WALK = 2;
	static const int GAME_OVER = 3;
	static const int PWIDTH = 54;
	static const int PHEIGHT = 91;
	static const int SUPPORT_PLAYER=2;
	
	static const int NORMAL = 1;
	static const int START = 2;
	static const int JAIL = 3;
	static const int SAFE = 4;
	static const int GO_TO_JAIL = 5;
	static const int CHANCE = 6;
	static const int RAILWAY = 7;
	static const int BUZZ = 8;
	static const int FACILITY = 9;

	static const int BUY = 1;
	static const int UPGRADE = 2;

	static const int GIVE = 1, TAX = 2;
	static const int TAX_MONEY = 100;

	CPublic(void);
	~CPublic(void);
};
