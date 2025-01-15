//=========================================================
//
// score.cppで使う関数[score.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _SCORE_H

#define _SCORE_H//二重インクルード防止

#include "object.h"
#include "main.h"

#include <cstdio> // snprintf
#include <cstring> // memset


class CScore : public CObject
{
public:

	static const int MAXWORD_SCORE = 1000;
	
	static const int TANK_SCORE1 = 1000;
	static const int TANK_SCORE2 = 1500;
	static const int TANK_SCORE3 = 2000;
	static const int TANK_SCORE4 = 2500;
	static const int DETH_PENALTY = 1000;
	static const int TIMEBONUS = 50;



	CScore(int nPriority = CObject::LAYERINDEX_SCORE);
	~CScore() override;//デストラクタ

	
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static void AddScore(int AddScore);
	static void ResetScore();
	static CScore* Create();//オブジェクト生成

	static int GetScore();

private:
	char m_cData[MAXWORD_SCORE];

	DATA m_Data[2];
	static int m_score;

};

#endif