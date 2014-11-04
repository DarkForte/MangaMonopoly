#pragma once

class CPanel : public CObject
{

public:
	static CString place_names[41];
	static int prices[41];
	int type;
	int owner;
	int price;
	CString name;
	bool occupied;
	int level;

	//CPoint cod;//cod means the coodinate for the player when he is standing on the panel
	CPoint cod;

	CPanel(void);
	~CPanel(void);
	static void InitPlace();
	static void InitPanelClass();

	void SetPanel(int n);
	void toZero();
	
	virtual void Serialize(CArchive& ar);

	CPanel(const CPanel &x); // CObject's copy function is private

	DECLARE_SERIAL(CPanel)
};

