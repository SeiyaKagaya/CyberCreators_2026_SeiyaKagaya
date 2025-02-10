//=========================================================
//
// object_billboard.cppで使う関数[object_billboard.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _OBJECTBILL_H
#define _OBJECTBILL_H//二重インクルード防止

#include "object.h"
#include "d3dx9.h"//描写処理に使う
#include "main.h"

class CObjectBillBoard : public CObject
{
public:
	static const int SIZE = 1650;//サイズ

	CObjectBillBoard(int nPriority = CObject::LAYERINDEX_BILLBOARD);//コンストラクタ
	~CObjectBillBoard() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectBillBoard* Create();//object生成

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

	//Zバッファ
	void SetZDrawDeth(bool bDraw);

private:

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = nullptr;//頂点バッファ
	LPDIRECT3DTEXTURE9 m_pTexture = nullptr;//テクスチャ
	DATA m_Data = DataInit();

	//テクスチャや頂点座標などの保持
	VERTEX_3D m_pVtx[BASE_INDEX] = {};

	bool m_AddDrawMode = false;//加算合成モード
	bool m_ZDethDrawMode = false;//Zバッファを無効に

	D3DXMATRIX m_mtxWorld = {};
};
#endif