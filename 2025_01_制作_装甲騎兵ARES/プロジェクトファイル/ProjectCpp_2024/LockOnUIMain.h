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

class CLockOnUIMain : public CObjectBillBoard
{
public:
	const float  PRINTSIZE = 80.0f;
	
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

	void SetPos(D3DXVECTOR3 Pos);//座標格納

	void SetCol(D3DXCOLOR col) { m_col = col; };//色格納

private:

	D3DXVECTOR3 m_Pos = {};

	D3DXCOLOR m_col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 0.95f);

	bool m_bDrawOk = false;//描画可能か
};

#endif