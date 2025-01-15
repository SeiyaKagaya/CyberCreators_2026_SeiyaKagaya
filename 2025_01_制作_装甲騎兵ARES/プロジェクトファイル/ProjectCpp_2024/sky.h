//=========================================================
//
// objectX.cppで使う関数[objectX.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _SKY3D_H

#define _SKY3D_H//二重インクルード防止

#include "object.h"
#include "d3dx9.h"//描写処理に使う
#include "main.h"
//
class Sky3D : public CObject
{
public:

	static const int ANIMNUM = 36000;
	static const int MAX_TEXTURE_XFILE = 50;

	Sky3D(int nPriority = CObject::LAYERINDEX_SKY);//コンストラクタ
	~Sky3D() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;


	static Sky3D* Create(D3DXVECTOR3 Pos);//object生成

	void SizeMagChangebool(bool bChange);//サイズ変動の有無
	void SetSizeMag(D3DXVECTOR3 SizeMag);//倍率
	void SetPos(D3DXVECTOR3 pos);



private:

	DATA m_Data;
	D3DXMATRIX m_mtxWorld;
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE_XFILE];//テクスチャ


	LPD3DXMESH m_pMesh;//Meshポインタ
	LPD3DXBUFFER m_pBuffMat;//マテリアルへのポインタ
	DWORD m_dwNumMat;//マテリアルの数





	D3DXVECTOR3 m_SizeMag;//倍率格納(1.0が平均)
	bool m_bMagChange;//倍率変動


	bool m_ChangeColorBool;//色変えbool
	D3DXCOLOR m_ChangeCol;//変える色


	D3DXCOLOR m_OriginalColor;
	bool bFast = false;//最初の一回のみ


//	int m_nLife;


	//テクスチャ読み込み
	LPDIRECT3DTEXTURE9	m_ESCpTexture=nullptr;

	float m_texOffsetX = 0.0f;
	float m_texOffsetY = 0.0f;

	int m_nCnt=0;

	D3DXVECTOR3 m_SetSize;
};

#endif