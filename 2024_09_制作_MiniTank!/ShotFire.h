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

	static const int  PRINTSIZE_X = 200;//サイズ
	static const int  PRINTSIZE_Z = 200;
	static const int START_LIFE = 60;		//寿命
	static const int DIVISION_NUMBER = 15;	//テクスチャ分割数

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
};

#endif