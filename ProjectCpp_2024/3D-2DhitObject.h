//=========================================================
//
// 2D-3DhitColision.cpp�Ŏg���֐�[2D-3DhitColision.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _STAGECOLLISION_H

#define _STAGECOLLISION_H//��d�C���N���[�h�h�~

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


	CStageCollisionBox3D2D(int nPriority = CObject::LAYERINDEX_HITBOX_2D3D);//�R���X�g���N�^
	~CStageCollisionBox3D2D() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;


//	void HitCollision();//�����蔻��܂Ƃ�

	static CStageCollisionBox3D2D* Create(DATA SetData,HITBOX hitman);//�I�u�W�F�N�g����

	LPD3DXMESH ScaleMeshUVs(LPD3DXMESH pMesh, float uScale, float vScale);
	
	void SetSIzeTexture(D3DXVECTOR3 TexSize);

	void SetType(HITBOX type);
	HITBOX GetHitBoxType();


	static bool bHitColision(D3DXVECTOR3 pos, D3DXVECTOR3 rayDirection, CObject::OBJECTTYPE MyType, void* pCaller);


private:

	CMathProc::CollisionData m_HitData;//�����蔻��f�[�^

	D3DXVECTOR3 m_TexSize;

	HITBOX m_hitbox;


	LPD3DXMESH m_pMesh = nullptr;//�����蔻��ɗ��p



};

#endif