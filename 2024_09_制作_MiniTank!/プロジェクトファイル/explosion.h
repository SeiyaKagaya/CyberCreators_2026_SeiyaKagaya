//=========================================================
//
// explosion.cppで使う関数[explosion.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _POLYGON_H
#define _POLYGON_H//二重インクルード防止

#include "object.h"
#include "object2D.h"

#include <Windows.h>
#include "d3dx9.h"//描写処理に使う
//
class CExplosion : public CObject2D
{
public:

	static const int SIZE = 150;			//大きさ
	static const int START_LIFE = 120;		//寿命
	static const int DIVISION_NUMBER = 8;	//テクスチャ分割数

	CExplosion(int nPriority = CObject::LAYERINDEX_EXPLOSION);//コンストラクタ
	~CExplosion() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	//頂点格納
	void InputpVtx()override;

	static CExplosion* Create(DATA data);//オブジェクト生成
private:
	int m_nLife = 0;		//寿命
	int m_nPatternAnim = 0;	//テクスチャ位置
};

#endif