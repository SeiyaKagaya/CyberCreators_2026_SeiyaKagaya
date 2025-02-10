//=========================================================
//
// StageCollisionBox.cpp�Ŏg���֐�[StageCollisionBox.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _STAGECOLLISIONBOXSET_H
#define _STAGECOLLISIONBOXSET_H//��d�C���N���[�h�h�~

#include "objectX.h"
#include "MathUtilities.h"

class StageCollisionBox : public CObjectX
{
public:

	StageCollisionBox(int nPriority = CObject::LAYERINDEX_HITBOX);//�R���X�g���N�^
	~StageCollisionBox() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void HitCollision();								//�����蔻��܂Ƃ�

	static StageCollisionBox* Create(DATA SetData);		//�I�u�W�F�N�g����

private:
	CMathProc::CollisionData m_HitData;					//�����蔻��f�[�^
};

#endif