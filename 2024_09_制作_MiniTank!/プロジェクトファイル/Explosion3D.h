//=========================================================
//
// objectX.cppで使う関数[objectX.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _EXPLOSION3D_H
#define _EXPLOSION3D_H//二重インクルード防止

#include "object.h"
#include "d3dx9.h"//描写処理に使う
#include "main.h"
//
class Explosion3D : public CObject
{
public:

	static const int ANIMNUM = 60;			//アニメーション分割数
	static const int FARST_ACTION_CNT = 18;	//初めのアクションするカウント
	static const int SECOND_ACTION_CNT = 40;//2個目のアクションするカウント

	static const int SET_SAKE_FARST = 85;	//変動震度1
	static const int SET_SAKE_SECOND = 55;	//変動震度2
	static const int SET_SAKE_SARD = 5;		//変動震度3

	const float SIZE_MAG = 3.0f;			//倍率
	const float SET_SIZE_FARST = 2.3f;		//変動倍率1
	const float SET_SIZE_SECOND = 0.7f;		//変動倍率2
	const float SET_SIZE_SARD = 0.3f;		//変動倍率3
	const float ROT_MOVE = 0.03f;			//回転

	Explosion3D(int nPriority = CObject::LAYERINDEX_EXPLOSION3D);//コンストラクタ
	~Explosion3D() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static Explosion3D* Create(D3DXVECTOR3 Pos);//object生成

	void SizeMagChangebool(bool bChange);//サイズ変動の有無
	void SetSizeMag(D3DXVECTOR3 SizeMag);//倍率
	void SetPos(D3DXVECTOR3 pos);

private:

	DATA m_Data = DataInit();
	D3DXMATRIX m_mtxWorld = {};
	LPD3DXMESH m_pMesh = nullptr;					//Meshポインタ
	LPD3DXBUFFER m_pBuffMat = nullptr;				//マテリアルへのポインタ
	DWORD m_dwNumMat = {};							//マテリアルの数
	D3DXCOLOR m_ChangeCol = {};						//変える色
	D3DXCOLOR m_OriginalColor = {};					//オリジナルカラー格納
	D3DXVECTOR3 m_SetSize = {};						//拡大率用サイズ格納
	D3DXVECTOR3 m_SizeMag = {};						//倍率格納(1.0が平均)
	LPDIRECT3DTEXTURE9	m_ESCpTexture = nullptr;
	bool m_bMagChange = false;						//倍率変動
	bool m_ChangeColorBool = false;					//色変えbool
	bool bFast = false;								//最初の一回のみ
	float m_texOffsetX = 0.0f;						//テクスチャ位置
	float m_texOffsetY = 0.0f;
	int m_nLife = 0;								//寿命
	int m_nCnt = 0;									//カウンター
};

#endif