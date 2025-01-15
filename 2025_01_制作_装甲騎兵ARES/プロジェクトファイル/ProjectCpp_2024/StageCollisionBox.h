//=========================================================
//
// StageCollisionBox.cpp�Ŏg���֐�[StageCollisionBox.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _STAGECOLLISIONBOXSET_H

#define _STAGECOLLISIONBOXSET_H//��d�C���N���[�h�h�~

//#include "object.h"
#include "objectX.h"

//#include <Windows.h>
//#include "d3dx9.h"//�`�ʏ����Ɏg��
#include "MathUtilities.h"
//#include <vector>
//#include "enemy_motion_base.h"

class StageCollisionBox : public CObjectX
{
public:

	StageCollisionBox(int nPriority = CObject::LAYERINDEX_HITBOX);//�R���X�g���N�^
	~StageCollisionBox() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;


	void HitCollision();//�����蔻��܂Ƃ�



	static StageCollisionBox* Create(DATA SetData);//�I�u�W�F�N�g����

	static void Resize(int count);//�z��̃T�C�Y�ύX

private:

	CMathProc::CollisionData m_HitData;//�����蔻��f�[�^
//	D3DXVECTOR3 m_SizeMag;
	
};

#endif