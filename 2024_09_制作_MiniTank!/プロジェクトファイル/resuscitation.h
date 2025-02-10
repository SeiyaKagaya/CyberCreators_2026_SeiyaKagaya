//=========================================================
//
// resuscitationで使う関数[resuscitation.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _RESCUE_H

#define _RESCUE_H//二重インクルード防止

#include "Object_billboard.h"
#include "d3dx9.h"//描写処理に使う
#include "main.h"

class CRescue : public CObjectBillBoard
{
public:

	static const int  PRINTSIZE_X = 300;	//サイズ
	static const int  PRINTSIZE_Z = 150;
	static const int START_LIFE = 120;		//寿命
	static const int DIVISION_NUMBER = 15;	//テクスチャ分割数

	CRescue(int nPriority = CObject::LAYERINDEX_RESCUE);//コンストラクタ
	~CRescue() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CRescue* Create(D3DXVECTOR3 Pos);//object生成

	//座標格納
	void SetPos(D3DXVECTOR3 Pos);

	//頂点格納
	void InputpVtx()override;

private:

	D3DXVECTOR3 m_Pos = {};

	D3DXCOLOR m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
};

#endif