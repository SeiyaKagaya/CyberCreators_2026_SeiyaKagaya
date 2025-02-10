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
	static const int MAX_TEXTURE_XFILE = 50;

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
	
	DATA GetDATA();//基礎情報取得
	void SetDATA(DATA data);//基礎情報設定

	void BindTexture(LPDIRECT3DTEXTURE9 pTex,int Index);//テクスチャ設定

	void ChangeModelPartsbool(bool parts);	//モデルパーツか

	void SetModelMtxWorld(D3DXMATRIX mtx);	//モデルのとき使用のマトリックス格納

	void SetColorChangeBool(bool ChangeColorBool);	//色変更あるか

	void SetChangeColor(D3DXCOLOR ChangeCol);	//色変更カラー

private:			  

	DATA m_Data = DataInit();
	D3DXMATRIX m_mtxWorld = {};							//マトリックス
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE_XFILE];	//テクスチャ
	LPD3DXMESH m_pMesh = nullptr;						//Meshポインタ
	LPD3DXBUFFER m_pBuffMat = nullptr;					//マテリアルへのポインタ
	DWORD m_dwNumMat = {};								//マテリアルの数
	D3DXVECTOR3 m_SizeMag = {};							//倍率格納(1.0が平均)
	D3DXMATRIX m_ModelmtxWorld = {};					//モデルパーツのときのマトリックス
	D3DXCOLOR m_ChangeCol = {};							//変える色
	D3DXCOLOR m_OriginalColor = {};						//オリジナルカラー
	bool m_bMagChange = false;							//倍率変動
	bool m_ChangeColorBool = false;						//色変えbool
	bool m_bModelParts = false;							//モデルパーツか
	bool bFast = false;									//最初の一回のみ
};

#endif