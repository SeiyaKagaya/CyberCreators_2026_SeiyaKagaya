//=========================================================
//
// objectX.cppで使う関数[objectX.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _OBJECTX_H

#define _OBJECTX_H//二重インクルード防止

#include "object.h"
#include "d3dx9.h"//描写処理に使う
#include "main.h"
//
class CObjectX : public CObject
{
public:
	static const int MAX_MAT = 200;
	static const int MAX_TEXTURE_XFILE = 200;

	CObjectX(int nPriority = CObject::LAYERINDEX_OBJECTX);//コンストラクタ
	~CObjectX() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;


	static CObjectX* Create();//object生成

	void SetXfireData(LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD dwNumMat);//Xfailを読んだデータ格納

	void SizeMagChangebool(bool bChange);//サイズ変動の有無
	void SetSizeMag(D3DXVECTOR3 SizeMag);//倍率
	D3DXVECTOR3 GetSizeMag();

	DATA GetDATA();//基礎情報取得
	void SetDATA(DATA data);//基礎情報設定

	void BindTexture(LPDIRECT3DTEXTURE9 pTex,int Index);//テクスチャ設定

	//モデルパーツか
	void ChangeModelPartsbool(bool parts);

	//モデルのとき使用のマトリックス格納
	void SetModelMtxWorld(D3DXMATRIX mtx);


	void SetColorChangeBool(bool ChangeColorBool);
	void SetChangeColor(D3DXCOLOR ChangeCol);



	void ChengeStageTex(bool Change);

	void SetNotLight(bool NotRight) { m_NotRight = NotRight; };
	bool GetNotLight() { return m_NotRight; };

private:			  

	DATA m_Data;
	D3DXMATRIX m_mtxWorld;
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE_XFILE];//テクスチャ


	LPD3DXMESH m_pMesh;//Meshポインタ
	LPD3DXBUFFER m_pBuffMat;//マテリアルへのポインタ
	DWORD m_dwNumMat;//マテリアルの数

	D3DXVECTOR3 m_SizeMag;//倍率格納(1.0が平均)
	bool m_bMagChange;//倍率変動

	bool m_bModelParts;//モデルパーツか
	D3DXMATRIX m_ModelmtxWorld;//モデルパーツのときのマトリックス

	bool m_ChangeColorBool;//色変えbool
	D3DXCOLOR m_ChangeCol;//変える色


	D3DXCOLOR m_OriginalColor[MAX_MAT];
	bool m_bFast[MAX_MAT];//最初の一回のみ

	bool m_bStageTexChange = false;


	bool m_NotRight = false;//ライト無視

	//bool bFast[30] = false;
};

#endif