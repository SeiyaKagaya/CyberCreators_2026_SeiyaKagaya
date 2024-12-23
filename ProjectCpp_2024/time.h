//=========================================================
//
// time.cppで使う関数[time.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _TIME_H

#define _TIME_H//二重インクルード防止

#include "object.h"
#include "main.h"

#include <cstdio> // snprintf
#include <cstring> // memset


class CTime : public CObject
{
public:

	static const int MAXWORD_TIME = 1000;


	CTime(int nPriority = CObject::LAYERINDEX_TIME);
	~CTime() override;//デストラクタ


	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static void AddTime();

	static CTime* Create();//オブジェクト生成

	static int GetTime();
	static void ChangeTime(int time) { m_LimitTime = time; };
private:
	char m_cData[MAXWORD_TIME] = {};

	DATA m_Data;
	static int m_LimitTime;
	static int m_flame;
	int m_StartLimitTime=0;//後に使用
};

#endif