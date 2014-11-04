#pragma once
class CPlayer : public CObject
{
	public:
		int num;
		int money;
		int book[4];
		int total;
		int jail_days;
		int now_place;
		int invest;
		int book_value;
		bool alive;
		CImage player_icon;

	public:
		CPlayer();
		~CPlayer(void);
		void Move(int steps);
		void LoseMoney(int amount);
		void Init(int n);
		void NoPicInit(int n);
		virtual void Serialize(CArchive& ar);

	    CPlayer(const CPlayer &x);
		void toZero();

		DECLARE_SERIAL(CPlayer)
};

