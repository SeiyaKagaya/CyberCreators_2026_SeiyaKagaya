//=========================================================
//
// Tutorial.cppで使う関数[Tutorial.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _TUTORIAL_H

#define _TUTORIAL_H//二重インクルード防止

#include "object.h"
#include "d3dx9.h"//描写処理に使う
#include "main.h"
//
class CTutorialUI //: public CObject
{
public:
	static const int TEXNUM = 3;
	CTutorialUI(/*int nPriority = CObject::LAYERINDEX_OBJECT2D*/);//コンストラクタ
	~CTutorialUI() /*override*/;//デストラクタ
	HRESULT Init()/*override*/;
	void Uninit()/*override*/;
	void Update()/*override*/;
	void Draw()/*override*/;

	static CTutorialUI* Create();//object生成

	void AddSelectNum(int addnum);
	void DirectSetNum(int Num);

	int GetSelectNum();

private:

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff[TEXNUM];//頂点バッファ
	LPDIRECT3DTEXTURE9 m_pTexture[TEXNUM];//テクスチャ
	int m_nTexIdx[TEXNUM];

	D3DXVECTOR3 m_Pos[TEXNUM];

	//テクスチャや頂点座標などの保持
//	VERTEX_2D m_pVtx[BASE_INDEX];

//	bool m_AddDrawMode;//加算合成モード

	int m_SelectNum = 0;

	bool m_bPhase2 = false;
};

#endif