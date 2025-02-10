//=========================================================
//
// background.cppで使う関数[background.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _BACKGROUND_H
#define _BACKGROUND_H//二重インクルード防止

#include "object.h"
#include "object2D.h"

#include <Windows.h>
#include "d3dx9.h"//描写処理に使う
//
class CBG : public CObject
{
public:

	CBG();//コンストラクタ
	~CBG() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CBG* Create();//オブジェクト生成
private:

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = nullptr;//頂点バッファ
	LPDIRECT3DTEXTURE9 m_pTexture = nullptr;//テクスチャ
};

#endif