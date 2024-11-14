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
	typedef enum
	{
		TYPE_RIGHTSLOPE=0,
		TYPE_LEFTSLOPE,
		TYPE_NOMALBLOCK,
	}HITBOX;


	CStageCollisionBox3D2D(int nPriority = CObject::LAYERINDEX_HITBOX_2D3D);//コンストラクタ
	~CStageCollisionBox3D2D() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;


//	void HitCollision();//当たり判定まとめ

	static CStageCollisionBox3D2D* Create(DATA SetData,HITBOX hitman);//オブジェクト生成

	LPD3DXMESH ScaleMeshUVs(LPD3DXMESH pMesh, float uScale, float vScale);
	
	void SetSIzeTexture(D3DXVECTOR3 TexSize);

	void SetType(HITBOX type);
	HITBOX GetHitBoxType();


	static bool bHitColision(D3DXVECTOR3 pos, D3DXVECTOR3 rayDirection, CObject::OBJECTTYPE MyType, void* pCaller);


private:

	CMathProc::CollisionData m_HitData;//当たり判定データ

	D3DXVECTOR3 m_TexSize;

	HITBOX m_hitbox;


	LPD3DXMESH m_pMesh = nullptr;//当たり判定に利用



};

#endif