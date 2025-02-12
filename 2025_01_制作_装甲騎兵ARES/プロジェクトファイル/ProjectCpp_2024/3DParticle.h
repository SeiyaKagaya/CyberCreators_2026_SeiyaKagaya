//=========================================================
//
// 3DParticleで使う関数[3DParticle.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _3DPARTICLE_H
#define _3DPARTICLE_H//二重インクルード防止

#include "Object_billboard.h"
#include "d3dx9.h"//描写処理に使う
#include "main.h"
#include "object.h"

class CObject3DParticle;

class CObject3DParticleAll : public CObjectX
{
public:

	static const int MAXPARTICLEALL = 640;//パーティクルの総数

	CObject3DParticleAll(int nPriority = CObject::LAYERINDEX_3DPARTICLE_MNG);//コンストラクタ
	~CObject3DParticleAll() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	//void Update()override;
	//void Draw()override;
	static CObject3DParticleAll* Create();//オブジェクト生成

	void ReleaseAllParticle();//すべてをリリース

	//規定数を初期化する
	void AllClean();

	CObject3DParticle* GetParticleData(int nNum);//配列番号のパーティクルのポインタ取得

	//すでに生成されているもののbUseをtrueにして稼働させる
	void SetParticle(D3DXVECTOR3 Pos, D3DXCOLOR col,int nLife,float Size);

private:

	//先に確保し、回す
	CObject3DParticle* m_NewParticle[MAXPARTICLEALL];
};

//--------------------------------------------------------------------------------------------------------------------------------------------------

class CObject3DParticle : public CObjectBillBoard
{
public:

	CObject3DParticle(int nPriority = CObject::LAYERINDEX_3DPARTICLE);//コンストラクタ
	~CObject3DParticle() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObject3DParticle* Create();//object生成

	void SetPos(D3DXVECTOR3 Pos);//座標格納

	//頂点格納
	void InputpVtx()override;

	//色変更
	void SetCOL(D3DXCOLOR col);

	bool GetbUse() { return m_bUse; };//使用中か取得

	void SetLife(int nLife) { m_nLife = nLife; };//体力設定

	void SetUse(bool Set) { m_bUse = Set; };//使用状態か格納

	void SetSize(float Size) { m_Size = Size; };//サイズ格納

private:

	int m_nLife=0;//寿命で消す

	D3DXCOLOR m_col=D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

	bool m_bUse = false;

	float m_Size = 0.0f;
};

#endif