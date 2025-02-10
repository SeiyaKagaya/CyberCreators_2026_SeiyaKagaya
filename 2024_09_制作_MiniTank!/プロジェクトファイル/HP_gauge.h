//=========================================================
//
// HP_gaugeで使う関数[HP_gauge.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _HPGAUGEUI_H
#define _HPGAUGEUI_H//二重インクルード防止

#include "Object_billboard.h"
#include "d3dx9.h"//描写処理に使う
#include "main.h"

class CObjectHPGaugeUI : public CObjectBillBoard
{
public:

	CObjectHPGaugeUI(int nPriority = CObject::LAYERINDEX_HPGAUGEUI);//コンストラクタ
	~CObjectHPGaugeUI() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectHPGaugeUI* Create(D3DXVECTOR3 Pos);//object生成

	void SetPos(D3DXVECTOR3 Pos);//サイズ格納

	void SetSize(D3DXVECTOR3 size);//サイズ格納

	void InputpVtx()override;//頂点セット

	void SetCol(D3DXCOLOR col);//色格納

private:

	D3DXVECTOR3 m_Pos = {};									//座標
	D3DXCOLOR m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//色
	D3DXVECTOR3 m_SetSize = {};								//サイズ
};

#endif