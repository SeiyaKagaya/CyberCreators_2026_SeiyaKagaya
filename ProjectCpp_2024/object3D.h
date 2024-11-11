//=========================================================
//
// object3D.cppで使う関数[object3D.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _OBJECT3D_H

#define _OBJECT3D_H//二重インクルード防止

#include "object.h"
#include "d3dx9.h"//描写処理に使う
#include "main.h"
//
class CObject3D : public CObject
{
public:

	CObject3D(int nPriority = CObject::LAYERINDEX_OBJECT3D);//コンストラクタ
	~CObject3D() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObject3D* Create();//object生成

	void BindTexture(LPDIRECT3DTEXTURE9 pTex);//テクスチャ設定
	LPDIRECT3DTEXTURE9 GetTexture();//テクスチャ取得

	void BindVtxBuffer(LPDIRECT3DVERTEXBUFFER9 pVtx);//バッファ設定

	LPDIRECT3DVERTEXBUFFER9 GetpVtxBuffer();//バッファ取得

	DATA GetDATA();//基礎情報取得
	void SetDATA(DATA data);//基礎情報設定


	void ChangeRGBA(D3DCOLOR col);//色

	void ChengeAddDrawMode(bool bSet);//描画モード

	//頂点など
	void SetpVtx(VERTEX_3D pVtx[BASE_INDEX]);

	//頂点格納
	virtual	void InputpVtx();




//	static HRESULT Load();
//	static void UnLoad();;

private:
	//protected:

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;//頂点バッファ
	LPDIRECT3DTEXTURE9 m_pTexture;//テクスチャ

	DATA m_Data;



	//テクスチャや頂点座標などの保持
	VERTEX_3D m_pVtx[BASE_INDEX];

	bool m_AddDrawMode;//加算合成モード
	float m_texOffsetX = 0.0f;
	float m_texOffsetY = 0.0f;


	D3DXMATRIX m_mtxWorld;
};

#endif