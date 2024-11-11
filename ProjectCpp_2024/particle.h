//=========================================================
//
// particle.cppで使う関数[particle.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _PARTICLE_H

#define _PARTICLE_H//二重インクルード防止

#include "object.h"
#include "object2D.h"

#include <Windows.h>
#include "d3dx9.h"//描写処理に使う
//
class CParticle : public CObject2D
{
public:

	const int START_LIFE = 110;
	const int START_RADiUS = 11;

	CParticle(int nPriority=CObject::LAYERINDEX_PARTICLE);//コンストラクタ
	~CParticle() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	//頂点格納
	void InputpVtx()override;

	static CParticle* Create(DATA data);//オブジェクト生成
private:
	int m_nLife;
	float m_Radius;

};


#endif