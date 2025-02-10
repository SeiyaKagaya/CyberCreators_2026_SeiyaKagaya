//=========================================================
//
//objectたちで使うテクスチャ管理構造体[all_texture.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _ALLTEXTURE_H
#define _ALLTEXTURE_H//二重インクルード防止

#include"main.h"
#include <d3d9.h>
#include "object.h"

//テクスチャ管理クラス
class CAllTexture
{
public:
	CAllTexture();
	~CAllTexture();

	//プロトタイプ宣言
	void Init();
	void Uninit();

	void Unload();//テクスチャ破棄
	int Regist(const char* pTextureName, LPDIRECT3DDEVICE9 pDevice);//テクスチャ登録

	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);//テクスチャ

private:
	static const int m_nMaxTexture = 100;				//テクスチャ総数
	LPDIRECT3DTEXTURE9 m_pTexture[m_nMaxTexture] = {};	//テクスチャ格納
	char* m_pFilePass[m_nMaxTexture] = {};				// ファイルパス
	int m_nNumAll = 0;									//テクスチャ数
};

#endif // !_TEXT_H_