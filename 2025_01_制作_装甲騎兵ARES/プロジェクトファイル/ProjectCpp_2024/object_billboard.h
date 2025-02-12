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
#include "objectX.h"

class CObjectBillBoard : public CObjectX
{
public:

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

	//描画重ね回数
	void SetAddDrawCnt(int nCnt) { nAddDrawCnt = nCnt; };

	void SetLight(bool bSet) { bSetLight = bSet; };

private:

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;//頂点バッファ
	LPDIRECT3DTEXTURE9 m_pTexture;//テクスチャ	
	DATA m_Data;

	//テクスチャや頂点座標などの保持
	VERTEX_3D m_pVtx[BASE_INDEX];

	bool m_AddDrawMode;//加算合成モード
	bool m_ZDethDrawMode;//Zバッファを無効に

	int nAddDrawCnt = 1;//最低回数

	D3DXMATRIX m_mtxWorld;

	bool bSetLight = false;
};

#endif