//=========================================================
//
// tankfootprintで使う関数[tankfootprint.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _TANKFOOTPRINT_H
#define _TANKFOOTPRINT_H//二重インクルード防止

#include "object3D.h"
#include "d3dx9.h"//描写処理に使う
#include "main.h"

class CObjectFootPrint : public CObject3D
{
public:

	static const int STANPLIFE = 480;	//寿命
	static const int  PRINTSIZE_X = 85;	//サイズ
	static const int  PRINTSIZE_Y = 10;
	static const int  PRINTSIZE_Z = 40;
	
	const float PRINT_MOVE_X = 13.0f;	//Y方向にズ
	const float COL_A = 0.55f;			//rgbaカラーA


	CObjectFootPrint(int nPriority = CObject::LAYERINDEX_FOOTPRINT);//コンストラクタ
	~CObjectFootPrint() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectFootPrint* Create(D3DXVECTOR3 Pos, D3DXVECTOR3 rot);//object生成

	void SetPos_Rot(D3DXVECTOR3 Pos,D3DXVECTOR3 rot);

	//頂点格納
	void InputpVtx()override;

private:
	
	int m_nLife = 0;//寿命
};

#endif