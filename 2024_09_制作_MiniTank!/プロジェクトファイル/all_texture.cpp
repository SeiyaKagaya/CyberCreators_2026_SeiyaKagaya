//=======================================================
//
//all_textureに関する処理[all_texture.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "all_texture.h"
#include "renderer.h"
#include "manager.h"

//=============================
// コンストラクタ
//=============================
CAllTexture::CAllTexture()
{
	m_nNumAll = 0;
	for (int i = 0; i < m_nMaxTexture; i++)
	{
		m_pTexture[i] = nullptr;
		m_pFilePass[i] = nullptr;
	}
}

//=============================
// デストラクタ
//=============================
CAllTexture::~CAllTexture()
{
}

//=============================
// 初期化
//=============================
void CAllTexture::Init()
{
}

//=============================
// 破棄処理
//=============================
void CAllTexture::Uninit()
{
	Unload();//テクスチャ破棄
}

//=============================
// テクスチャ破棄処理
//=============================
void CAllTexture::Unload()
{
	for (int nCnt = 0; nCnt < m_nMaxTexture; nCnt++)
	{
		if (m_pTexture[nCnt] != nullptr)
		{
			m_pTexture[nCnt]->Release();//-------------------------こーれ大事
			m_pTexture[nCnt] = nullptr;
		}
		if (m_pFilePass[nCnt] != nullptr)
		{//メモリを確保しているため
			delete[] m_pFilePass[nCnt];
			m_pFilePass[nCnt] = nullptr;
		}
	}
}

//=============================
// テクスチャ登録処理
//=============================
int CAllTexture::Regist(const char* pTextureName, LPDIRECT3DDEVICE9 pDevice)
{
	int nIdx = 0;
	for (int nCnt = 0; nCnt < m_nMaxTexture; nCnt++)
	{
		if (m_pTexture[nCnt] == nullptr)
		{
			// テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice, pTextureName, &m_pTexture[nCnt]); // 通常時
			nIdx = nCnt; // Id設定
			m_nNumAll++;

			// 文字列のメモリを確保してコピー
			m_pFilePass[nCnt] = new char[strlen(pTextureName) + 1];
			strcpy(m_pFilePass[nCnt], pTextureName);

			break;
		}
		else if (strcmp(pTextureName, m_pFilePass[nCnt]) == 0)
		{//すでにあるパスと一致
			nIdx = nCnt;
			break;
		}
	}
	return nIdx;
}

//=============================
// テクスチャ取得
//=============================
LPDIRECT3DTEXTURE9 CAllTexture::GetAddress(int nIdx)
{
	//安全なコピーをするっぽい
	m_pTexture[nIdx]->AddRef();//これ必須？？？

	return m_pTexture[nIdx];
}