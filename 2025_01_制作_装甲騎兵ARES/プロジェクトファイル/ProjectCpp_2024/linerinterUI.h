//=========================================================
//
// linerinterUIで使う関数[linerinterUI.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _LINEUI_H
#define _LINEUI_H//二重インクルード防止

#include "Object_billboard.h"
#include "d3dx9.h"//描写処理に使う
#include "main.h"

class CObjectLINEUI : public CObjectBillBoard
{
public:

	const float  PRINTSIZE = 20.0f;
	static const int LIFE = 6;

	CObjectLINEUI(int nPriority = CObject::LAYERINDEX_LINEUI);//コンストラクタ
	~CObjectLINEUI() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectLINEUI* Create(D3DXVECTOR3 Pos);//object生成

	void SetPos(D3DXVECTOR3 Pos);//座標格納

	//頂点格納
	void InputpVtx()override;

private:

	D3DXVECTOR3 m_Pos;

	D3DXCOLOR m_col;

	int m_nLife = 0;
};

#endif