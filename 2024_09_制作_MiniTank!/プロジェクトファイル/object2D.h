//=========================================================
//
// object2D.cppで使う関数[object2D.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _OBJECT2D_H
#define _OBJECT2D_H//二重インクルード防止

#include "object.h"
#include "d3dx9.h"//描写処理に使う
#include "main.h"

class CObject2D: public CObject
{
public:
	
	CObject2D(int nPriority=CObject::LAYERINDEX_OBJECT2D);//コンストラクタ
	 ~CObject2D() override ;//デストラクタ
	 HRESULT Init()override;
	 void Uninit()override;
	 void Update()override;
	 void Draw()override;

	static CObject2D *Create();//object生成

	void BindTexture(LPDIRECT3DTEXTURE9 pTex);			//テクスチャ設定
	LPDIRECT3DTEXTURE9 GetTexture();					//テクスチャ取得
	
	void BindVtxBuffer(LPDIRECT3DVERTEXBUFFER9 pVtx);	//バッファ設定

	LPDIRECT3DVERTEXBUFFER9 GetpVtxBuffer();			//バッファ取得

	DATA GetDATA();										//基礎情報取得
	void SetDATA(DATA data);							//基礎情報設定
	void ChangeRGBA(D3DCOLOR col);						//色変更
	void ChengeAddDrawMode(bool bSet);					//加算合成か

	void SetpVtx(VERTEX_2D pVtx[BASE_INDEX]);			//頂点格納

	virtual	void InputpVtx();							//頂点セット

	void SetTexIndex(int TexIdx);						//テクスチャid格納

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = nullptr;//頂点バッファ
	LPDIRECT3DTEXTURE9 m_pTexture = nullptr;	 //テクスチャ

	int m_nTexIdx = 0;//テクスチャ番号
	
	DATA m_Data = DataInit();

	//テクスチャや頂点座標などの保持
	VERTEX_2D m_pVtx[BASE_INDEX] = {};

	bool m_AddDrawMode = false;//加算合成モード
};
#endif