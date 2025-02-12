//=========================================================
//
// shotfireで使う関数[shorfire.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _SHOTFIRE_H
#define _SHOTFIRE_H//二重インクルード防止

#include "Object_billboard.h"
#include "d3dx9.h"//描写処理に使う
#include "main.h"

class CObjectShotFire : public CObjectBillBoard
{
public:

	const int START_LIFE = 30;
	const int DIVISION_NUMBER = 15;	//テクスチャ分割数
	const float  PRINTSIZE = 200.0f;

	CObjectShotFire(int nPriority = CObject::LAYERINDEX_SHOTFIRE);//コンストラクタ
	~CObjectShotFire() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectShotFire* Create(D3DXVECTOR3 Pos);//object生成

	void SetPos(D3DXVECTOR3 Pos);

	//頂点格納
	void InputpVtx()override;

private:

	int m_nLife = 0;//寿命で消す

	int m_nPatternAnim = 0;//分割

	int m_nDelay = 0;
};

#endif