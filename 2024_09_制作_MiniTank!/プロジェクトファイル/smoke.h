//=========================================================
//
// smokeで使う関数[smoke.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _SMOKE_H
#define _SMOKE_H//二重インクルード防止

#include "Object_billboard.h"
#include "d3dx9.h"//描写処理に使う
#include "main.h"

class CObjectSmoke: public CObjectBillBoard
{
public:

	static const int  PRINTSIZE_X = 30;		//サイズ
	static const int  PRINTSIZE_Z = 15;
	static const int START_LIFE = 60;		//寿命
	static const int DIVISION_NUMBER = 8;	//テクスチャ分割数
	const float RGB_A = 0.35f;				//アルファ値

	CObjectSmoke(int nPriority = CObject::LAYERINDEX_SMOKE);//コンストラクタ
	~CObjectSmoke() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectSmoke* Create(D3DXVECTOR3 Pos);//object生成

	void SetPos(D3DXVECTOR3 Pos);

	//頂点格納
	void InputpVtx()override;

private:

	int m_nLife=0;		 //寿命で消す
	int m_nPatternAnim=0;//分割
};

#endif