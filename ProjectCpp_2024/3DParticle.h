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
//


class CObject3DParticle;

class CObject3DParticleAll : public CObjectX
{
public:

	static const int MAXPARTICLEALL = 640;

	CObject3DParticleAll(int nPriority = CObject::LAYERINDEX_3DPARTICLE_MNG);//コンストラクタ
	~CObject3DParticleAll() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	//void Update()override;
	//void Draw()override;
	static CObject3DParticleAll* Create();//オブジェクト生成

	void ReleaseAllParticle();

	
	//規定数を初期化する
	void AllClean();

	CObject3DParticle* GetParticleData(int nNum);

	//すでに生成されているもののbUseをtrueにして稼働させる
	void SetParticle(D3DXVECTOR3 Pos, D3DXCOLOR col,int nLife,float Size);



private:

	//先に確保し、回す
	CObject3DParticle* m_NewParticle[MAXPARTICLEALL];


};



















class CObject3DParticle : public CObjectBillBoard
{
public:

	//	static const int EX_WIDE = 150;
	//	static const int EX_HEIGHT = 150;

	const int START_LIFE = 1;
	//	const int DIVISION_NUMBER = 8;	//テクスチャ分割数


	//	static const int STANPLIFE = 2 * 60;
	static const int  PRINTSIZE_X = 30;
	static const int  PRINTSIZE_Z = 15;


	CObject3DParticle(int nPriority = CObject::LAYERINDEX_3DPARTICLE);//コンストラクタ
	~CObject3DParticle() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObject3DParticle* Create(/*D3DXVECTOR3 Pos, D3DXCOLOR col*/);//object生成

	void SetPos(D3DXVECTOR3 Pos);

	//頂点格納
	void InputpVtx()override;

	//色変更
	void SetCOL(D3DXCOLOR col);

	void SetbUse(bool bUse) { m_bUse = bUse; if (m_bUse == true) { m_nLife = 3; }; };

	bool GetbUse() { return m_bUse; };

	void SetLife(int nLife) { m_nLife = nLife; };
	void SetUse(bool Set) { m_bUse = Set; };

	void SetSize(float Size) { m_Size = Size; };

private:

	int m_nLife=0;//寿命で消す

	D3DXCOLOR m_col=D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

//	int m_nPatternAnim;//分割

//	int m_nDelay;

	bool m_bUse = false;
	float m_Size = 0.0f;
};

#endif