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

//

class CObject3DParticle : public CObjectBillBoard
{
public:

//	static const int EX_WIDE = 150;
//	static const int EX_HEIGHT = 150;

	const int START_LIFE = 15;
//	const int DIVISION_NUMBER = 8;	//テクスチャ分割数


//	static const int STANPLIFE = 2 * 60;
	static const int  PRINTSIZE_X = 40;
	static const int  PRINTSIZE_Z = 20;


	CObject3DParticle(int nPriority = CObject::LAYERINDEX_3DPARTICLE);//コンストラクタ
	~CObject3DParticle() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObject3DParticle* Create(D3DXVECTOR3 Pos, D3DXCOLOR col);//object生成

	void SetPos_Rot(D3DXVECTOR3 Pos);

	//頂点格納
	void InputpVtx()override;

	//色変更
	void SetCOL(D3DXCOLOR col);

private:

	int m_nLife;//寿命で消す

	D3DXCOLOR m_col=D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

//	int m_nPatternAnim;//分割

//	int m_nDelay;
};

#endif