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

	static const int MAXWORD_SCORE = 1000;//ワードのサイズ
	
	static const int TANK_SCORE1 = 1000;//撃破時スコア
	static const int TANK_SCORE2 = 1500;
	static const int TANK_SCORE3 = 2000;
	static const int TANK_SCORE4 = 2500;
	static const int DETH_PENALTY = 1000;//死亡時スコアペナルティ
	static const int TIMEBONUS = 50;	//タイムボーナス

	CScore(int nPriority = CObject::LAYERINDEX_SCORE);
	~CScore() override;//デストラクタ

	
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static void AddScore(int AddScore);	//スコア加算
	static void ResetScore();			//スコアリセット
	static CScore* Create();			//オブジェクト生成

	static int GetScore();				//スコア取得

private:
	char m_cData[MAXWORD_SCORE] = {};	//描画する文字列格納
	DATA m_Data[2] = {};
	static int m_score;					//スコア格納
};

#endif