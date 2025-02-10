//=========================================================
//
// targetuiで使う関数[targetui.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _TARGETUI_H
#define _TARGETUI_H//二重インクルード防止

#include "Object_billboard.h"
#include "d3dx9.h"//描写処理に使う
#include "main.h"

class CObjectTargetUI : public CObjectBillBoard
{
public:

	static const int  PRINTSIZE_X = 70;//サイズ
	static const int  PRINTSIZE_Z = 70;
	static const int  START_LIFE = 3;  //寿命
	static const int ADD_CNT = 20;	   //加算回数

	CObjectTargetUI(int nPriority = CObject::LAYERINDEX_TARGETUI);//コンストラクタ
	~CObjectTargetUI() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectTargetUI* Create(D3DXVECTOR3 Pos);//object生成

	//座標格納
	void SetPos(D3DXVECTOR3 Pos);

	//頂点格納
	void InputpVtx()override;

private:

	D3DXVECTOR3 m_Pos = {};
	D3DXCOLOR m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	int m_nLife = START_LIFE;
};

#endif