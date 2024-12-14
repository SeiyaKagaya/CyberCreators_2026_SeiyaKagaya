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

	////objectPass管理構造体
	//typedef struct
	//{
	//	LPDIRECT3DTEXTURE9 m_pTexture;//テクスチャ格納
	//	const char* pFilePass;	// ファイルパス
	//	CObject::OBJECTTYPE objectType;	// objectネーム
	//} TEXTUREINFO;

	//プロトタイプ宣言
	void Init();
	void Uninit();

	void Unload();//テクスチャ破棄
	int Regist(const char* pTextureName, LPDIRECT3DDEVICE9 pDevice);//テクスチャ登録

	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);//テクスチャ

//	static LPDIRECT3DTEXTURE9 GetTexture(CObject::OBJECTTYPE ObjectType, LPDIRECT3DDEVICE9 pDevice);//テクスチャ

private:
	static const int m_nMaxTexture = 150;//テクスチャ総数
	LPDIRECT3DTEXTURE9 m_pTexture[m_nMaxTexture];//テクスチャ格納
	char* m_pFilePass[m_nMaxTexture];	// ファイルパス
	int m_nNumAll;//テクスチャ数

	//パス管理構造体
//	static 	TEXTUREINFO m_TextureInfo[CObject::OBJECT_MAX];
};

#endif // !_TEXT_H_