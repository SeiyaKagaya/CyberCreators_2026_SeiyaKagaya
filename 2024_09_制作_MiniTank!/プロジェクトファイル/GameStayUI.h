//=========================================================
//
// GameStayUI.cppで使う関数[GameStayUI.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _stayUI_H
#define _stayUI_H//二重インクルード防止

#include "object.h"
#include "d3dx9.h"//描写処理に使う
#include "main.h"

class CStayUI 
{
public:
	static const int TEXNUM = 2;

	const D3DXVECTOR3 SETPOS[TEXNUM] = {
	D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 380.0f, SCREEN_HEIGHT / 2.0f - 50.0f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 150.0f, SCREEN_HEIGHT / 2.0f - 50.0f, 0.0f) };//UIの座標
	
	CStayUI();//コンストラクタ
	~CStayUI() ;//デストラクタ
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	static CStayUI* Create();//object生成

private:

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff[TEXNUM] = {};//頂点バッファ
	LPDIRECT3DTEXTURE9 m_pTexture[TEXNUM] = {};		//テクスチャ
	int m_nTexIdx[TEXNUM] = {};					  	//テクスチャID
	D3DXVECTOR3 m_Pos[TEXNUM] = {};			    	//座標
};

#endif