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

	CStageCollisionBox3D2D(int nPriority = CObject::LAYERINDEX_HITBOX);//�R���X�g���N�^
	~CStageCollisionBox3D2D() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;


	void HitCollision();//�����蔻��܂Ƃ�



	static CStageCollisionBox3D2D* Create(DATA SetData);//�I�u�W�F�N�g����

	static void Resize(int count);//�z��̃T�C�Y�ύX

	LPD3DXMESH ScaleMeshUVs(LPD3DXMESH pMesh, float uScale, float vScale);
	
	void SetSIzeTexture(D3DXVECTOR3 TexSize);

private:

	CMathProc::CollisionData m_HitData;//�����蔻��f�[�^

	D3DXVECTOR3 m_TexSize;
};

#endif