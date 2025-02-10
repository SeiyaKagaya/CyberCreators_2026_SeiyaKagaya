//=========================================================
//
// ReflectEffectで使う関数[ReflectEffect.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _REFLECTEFFECT_H
#define _REFLECTEFFECT_H//二重インクルード防止

#include "Object_billboard.h"
#include "d3dx9.h"//描写処理に使う
#include "main.h"



class CObjectReflectEffect : public CObjectBillBoard
{
public:
	static const int  PRINTSIZE_X = 120;//サイズ
	static const int  PRINTSIZE_Z = 120;
	static const int DIVISION_NUMBER = 30;		//テクスチャ分割数

	CObjectReflectEffect(int nPriority = CObject::LAYERINDEX_ReflectEffect);//コンストラクタ
	~CObjectReflectEffect() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectReflectEffect* Create(D3DXVECTOR3 Pos);//object生成

	//POS格納
	void SetPos(D3DXVECTOR3 Pos);

	//頂点格納
	void InputpVtx()override;

private:

	int m_nPatternAnim = 0;//分割
};

#endif