//=========================================================
//
// enemy_motion_base.cpp�Ŏg���֐�[enemy_motion_base.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _MOTIONENEMYBASE_H

#define _MOTIONENEMYBASE_H//��d�C���N���[�h�h�~

#include "object.h"
#include "objectX.h"

#include <Windows.h>
#include "d3dx9.h"//�`�ʏ����Ɏg��
#include "MathUtilities.h"
#include <vector>
#include "object_motion.h"


//���N���X
class CObjectMotionEnemyBase : public CObjectMotion
{
public:
	static const int ROUTE_TABLE_ROW = 11;//����8�܂�
	static const int ROUTE_TABLE_SHIELDROW = 8;//�c��11�܂�
	static const int AABB_BOX = 58;

	typedef enum
	{
		ENEMYTYPE_NOMAL=0,
		ENEMYTYPE_MAX
	}ENEMYTYPE;


	CObjectMotionEnemyBase(int nPriority = CObject::LAYERINDEX_MOTIONENEMY_BASE);//�R���X�g���N�^

	CObjectMotionEnemyBase(ENEMYTYPE Enemytype,int nPriority = CObject::LAYERINDEX_MOTIONENEMY_BASE);//�I�[�o�[���[�h
	virtual ~CObjectMotionEnemyBase() override;//�f�X�g���N�^

	virtual HRESULT Init()override;
	virtual void Uninit()override;
	virtual void Update()override;
	virtual void Draw()override;

	static CObjectMotionEnemyBase* Create(const char* pfilePass, DATA SetData);//�I�u�W�F�N�g����

	static int GetEnemyAllNum();

private:

	CMathProc::CollisionData m_HitData;//�����蔻��f�[�^

	bool btest = false;

	int m_nLife;

	static int m_nNumENemyAll;//�G����
};

#endif