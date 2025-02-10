//=========================================================
//
// HpLatterで使う関数[HpLatter.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _HPLATTERUI_H
#define _HPLATTERUI_H//二重インクルード防止

#include "Object_billboard.h"
#include "d3dx9.h"//描写処理に使う
#include "main.h"

class CObjectHPLatterUI : public CObjectBillBoard
{
public:

	static const int  PRINTSIZE_X = 45;//サイズ
	static const int  PRINTSIZE_Z = 45;

	CObjectHPLatterUI(int nPriority = CObject::LAYERINDEX_HPLATTERUI);//コンストラクタ
	~CObjectHPLatterUI() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectHPLatterUI* Create(D3DXVECTOR3 Pos);//object生成

	//座標格納
	void SetPos(D3DXVECTOR3 Pos);

	//頂点格納
	void InputpVtx()override;

private:

	D3DXVECTOR3 m_Pos = {};

	D3DXCOLOR m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
};

#endif