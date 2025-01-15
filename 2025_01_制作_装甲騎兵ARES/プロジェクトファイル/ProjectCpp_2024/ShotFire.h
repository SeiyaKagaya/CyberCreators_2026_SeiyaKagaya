//=========================================================
//
// shotfireで使う関数[shorfire.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _SHOTFIRE_H

#define _SHOTFIRE_H//二重インクルード防止

#include "Object_billboard.h"
#include "d3dx9.h"//描写処理に使う
#include "main.h"

//

class CObjectShotFire : public CObjectBillBoard
{
public:

	static const int EX_WIDE = 150;
	static const int EX_HEIGHT = 150;

	const int START_LIFE = 120;
	const int DIVISION_NUMBER = 15;	//テクスチャ分割数


//	static const int STANPLIFE = 2 * 60;
	static const int  PRINTSIZE_X = 200;
	static const int  PRINTSIZE_Z = 200;


	CObjectShotFire(int nPriority = CObject::LAYERINDEX_SHOTFIRE);//コンストラクタ
	~CObjectShotFire() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectShotFire* Create(D3DXVECTOR3 Pos);//object生成

	void SetPos_Rot(D3DXVECTOR3 Pos);

	//頂点格納
	void InputpVtx()override;


private:

	int m_nLife;//寿命で消す

	int m_nPatternAnim;//分割

	int m_nDelay;
};

#endif