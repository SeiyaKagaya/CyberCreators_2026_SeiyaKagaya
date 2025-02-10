//=========================================================
//
// ExplosionBillで使う関数[ExplosionBill.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _EXPRO_H
#define _EXPRO_H//二重インクルード防止

#include "Object_billboard.h"
#include "d3dx9.h"//描写処理に使う
#include "main.h"

class CObjectExplosionBill : public CObjectBillBoard
{
public:

	static const int  PRINTSIZE = 100;		//サイズ
	static const int DIVISION_NUMBER = 30;	//テクスチャ分割数

	CObjectExplosionBill(int nPriority = CObject::LAYERINDEX_EXPRO_BILL);//コンストラクタ
	~CObjectExplosionBill() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectExplosionBill* Create(D3DXVECTOR3 Pos);//object生成

	//座標格納
	void SetPos(D3DXVECTOR3 Pos);

	//頂点格納
	void InputpVtx()override;

private:

	int m_nPatternAnim = 0;//分割カウンタ
};

#endif