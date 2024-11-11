//=========================================================
//
// 2D-3DhitColision.cppで使う関数[2D-3DhitColision.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _STAGECOLLISION_H

#define _STAGECOLLISION_H//二重インクルード防止

#include "objectX.h"

#include "MathUtilities.h"

class CStageCollisionBox3D2D : public CObjectX
{
public:

	CStageCollisionBox3D2D(int nPriority = CObject::LAYERINDEX_HITBOX);//コンストラクタ
	~CStageCollisionBox3D2D() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;


	void HitCollision();//当たり判定まとめ



	static CStageCollisionBox3D2D* Create(DATA SetData);//オブジェクト生成

	static void Resize(int count);//配列のサイズ変更

	LPD3DXMESH ScaleMeshUVs(LPD3DXMESH pMesh, float uScale, float vScale);
	
	void SetSIzeTexture(D3DXVECTOR3 TexSize);

private:

	CMathProc::CollisionData m_HitData;//当たり判定データ

	D3DXVECTOR3 m_TexSize;
};

#endif