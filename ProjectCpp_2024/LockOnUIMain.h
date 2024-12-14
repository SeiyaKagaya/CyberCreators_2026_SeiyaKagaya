//=========================================================
//
// LockOnUIMainで使う関数[LockOnUIMain.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _LOCKONUIMAIN_H

#define _LOCKONUIMAIN_H//二重インクルード防止

#include "Object_billboard.h"
#include "d3dx9.h"//描写処理に使う
#include "main.h"
//#include "LockOnUI.h"
///

class CLockOnUIMain : public CObjectBillBoard
{
public:

//	static const int EX_WIDE = 140;
//	static const int EX_HEIGHT = 140;

//	const int START_LIFE = 120;
//	const int DIVISION_NUMBER = 15;	//テクスチャ分割数


//	static const int STANPLIFE = 2 * 60;
	static const int  PRINTSIZE = 80;
	

	CLockOnUIMain(int nPriority = CObject::LAYERINDEX_LOCKONUIMAIN);//コンストラクタ
	~CLockOnUIMain() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CLockOnUIMain* Create();//object生成



	//頂点格納
	void InputpVtx()override;

	//描画可能か
	void SetDrawOk(bool bSet) { m_bDrawOk = bSet; };
	bool bGetDrawOk() { return m_bDrawOk; };

	void SetPos(D3DXVECTOR3 Pos);
	void SetCol(D3DXCOLOR col) { m_col = col; };

private:

	D3DXVECTOR3 m_Pos = {};

	D3DXCOLOR m_col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 0.95f);

	//int m_nLife = 6;
	bool m_bDrawOk = false;

};

#endif