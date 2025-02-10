//=========================================================
//
// movesmokeで使う関数[movesmoke.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _MOVESMOKE_H
#define _MOVESMOKE_H//二重インクルード防止

#include "Object_billboard.h"
#include "d3dx9.h"//描写処理に使う
#include "main.h"

class CMoveSmoke : public CObjectBillBoard
{
public:

	static const int  PRINTSIZE_X = 120;	//サイズ
	static const int  PRINTSIZE_Z = 120;
	static const int START_LIFE = 60;		//寿命
	static const int DIVISION_NUMBER = 8;	//テクスチャ分割数

	CMoveSmoke(int nPriority = CObject::LAYERINDEX_ReflectEffect);//コンストラクタ
	~CMoveSmoke() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CMoveSmoke* Create(D3DXVECTOR3 Pos);//object生成

	//POS格納
	void SetPos(D3DXVECTOR3 Pos);

	//頂点格納
	void InputpVtx()override;

private:

	int m_nLife = 0;//寿命で消す

	int m_nPatternAnim = 0;//分割カウント

	D3DXCOLOR m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//カラー

	int m_nACnt = 100;//カラーのアルファ値
};

#endif