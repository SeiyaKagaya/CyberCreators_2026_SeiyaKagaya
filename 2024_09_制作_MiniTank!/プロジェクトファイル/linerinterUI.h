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
	static const int  PRINTSIZE_X = 20;//サイズ
	static const int  PRINTSIZE_Z = 20;
	static const int LIFE = 3;		   //寿命
	static const int ADD_CNT = 20;	   //加算回数
	
	CObjectLINEUI(int nPriority = CObject::LAYERINDEX_LINEUI);//コンストラクタ
	~CObjectLINEUI() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectLINEUI* Create(D3DXVECTOR3 Pos);//object生成

	//Pos格納
	void SetPos(D3DXVECTOR3 Pos);

	//頂点格納
	void InputpVtx()override;
private:

	D3DXVECTOR3 m_Pos = {};

	D3DXCOLOR m_col = D3DXCOLOR(0.0f,0.0f, 1.0f, 1.0f);

	int m_nLife = LIFE;
};

#endif