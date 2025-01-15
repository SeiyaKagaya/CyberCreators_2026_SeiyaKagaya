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

//

class CSea : public CObject3D
{
public:

	static const int  PRINTSIZE = 3300 / 2;
	//	static const int  SETPOS

	static const int ANIMNUM = 1;
	static const int MAX_TEXTURE_XFILE = 50;

	CSea(int nPriority = CObject::LAYERINDEX_SEA);//コンストラクタ
	~CSea() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CSea* Create(D3DXVECTOR3 Pos, D3DXVECTOR3 rot, float rgbA);//object生成

	void SetPos_Rot(D3DXVECTOR3 Pos, D3DXVECTOR3 rot);

	//頂点格納
	void InputpVtx()override;

	//アルファ値を格納
	void SetrgbA(float rgbA) { m_rgbA = rgbA; };

private:

	float m_texOffsetX = 0.0f;
	float m_texOffsetY = 0.0f;
	float m_rgbA = 0.0f;
///	int m_nCnt = 0;
};

#endif