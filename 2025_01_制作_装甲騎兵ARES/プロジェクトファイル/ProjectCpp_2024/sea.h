//=========================================================
//
// tankfootprintで使う関数[tankfootprint.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _SEA_H
#define _SEA_H//二重インクルード防止

#include "object3D.h"
#include "d3dx9.h"//描写処理に使う
#include "main.h"

class CSea : public CObject3D
{
public:
	const float PRINTSIZE = 60000.0f;	//頂点までの長さ
	const float TEXMOVE_X1 = 0.00004f;	//テクスチャのmove値
	const float TEXMOVE_Y1 = 0.00002f;
	const float TEXMOVE_X2 = 0.0002f;
	const float TEXMOVE_Y2 = 0.0009f;

	CSea(int nPriority = CObject::LAYERINDEX_SEA);//コンストラクタ
	~CSea() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CSea* Create(D3DXVECTOR3 Pos, D3DXVECTOR3 rot, float rgbA);//object生成

	//位置と回転を格納
	void SetPos_Rot(D3DXVECTOR3 Pos, D3DXVECTOR3 rot);

	//頂点格納
	void InputpVtx()override;

	//アルファ値を格納
	void SetrgbA(float rgbA) { m_rgbA = rgbA; };

private:

	//テクスチャの位置用
	float m_texOffsetX = 0.0f;
	float m_texOffsetY = 0.0f;
	float m_rgbA = 0.0f;//アルファ値格納
};

#endif