//=========================================================
//
// result.cppで使う関数[result.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _result_H
#define _result_H//二重インクルード防止

#include "object.h"
#include "d3dx9.h"//描写処理に使う
#include "main.h"
//
class CResultUI : public CObject
{
public:
	static const int TEXNUM = 1;
	CResultUI(int nPriority = CObject::LAYERINDEX_RESULTUI);//コンストラクタ
	~CResultUI() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CResultUI* Create();//object生成
private:

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff[TEXNUM] = {};//頂点バッファ
	LPDIRECT3DTEXTURE9 m_pTexture[TEXNUM] = {};     //テクスチャ
	int m_nTexIdx[TEXNUM] = {};						//テクスチャ番号
	D3DXVECTOR3 m_Pos[TEXNUM] = {};					//座標
};

#endif