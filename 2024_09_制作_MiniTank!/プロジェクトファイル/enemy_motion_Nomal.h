//=========================================================
//
// enemy_motion_Nomal.cpp�Ŏg���֐�[enemy_motion_Nomal.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _MOTIONENEMYNOMAL_H
#define _MOTIONENEMYNOMAL_H//��d�C���N���[�h�h�~

#include "enemy_motion_base.h"

//�����CObjectMotionEnemyBase�̔h���N���X

class CObjectMotionEnemyNomal : public CObjectMotionEnemyBase
{
public:
	const float MOVEROT = 0.065f;						//���񑬓x
	const float MOVESPEED = 3.2f;						//�C�e���x1
	static const int MOVESPEED2 = 12;					//�C�e���x2
	static const int BULLETSHOTDELAY = 175;				//���C�Ԋu
	static const int LIFE = 100;						//����
	static const int DAMAGE = 100;						//�_���[�W
	static const int RADIUS = 110;						//���a
	const float OBB_LENGTH[3] = { 90.0f,90.0f,120.0f }; //OBB�̒���

	CObjectMotionEnemyNomal(int nPriority = CObject::LAYERINDEX_MOTIONENEMY_NOMAL);//�R���X�g���N�^
	 ~CObjectMotionEnemyNomal() override;//�f�X�g���N�^

	 HRESULT Init()override;
	 void Uninit()override;
	 void Update()override;
	 void Draw()override;

	static CObjectMotionEnemyNomal* Create(const char* pfilePass, DATA SetData);//�I�u�W�F�N�g����

	void Attack();						//�U���֌W
	DATA phase1(D3DXVECTOR3 ShotPos);	//�U���t�F�[�Y1
	DATA phase2();						//�U���t�F�[�Y2

	void TurretRotation(D3DXVECTOR3 ShotPos, D3DXVECTOR3 TargetPos, D3DXVECTOR3 BulletMove);//�C������
	void ShotBullet(D3DXVECTOR3 ShotPos, D3DXVECTOR3 TargetPos, D3DXVECTOR3 BulletMove);	 //�ˌ��n

private:

	CMathProc::CollisionData m_HitData = {};//�����蔻��f�[�^
	D3DXVECTOR3 m_TargetPos = {};			//���݂̖ڕW�n�_
	int m_nLife=0;							//����
	int m_BulletDelay=0;					//���C�Ԋu
	int m_OldTargetGRIDNum = -1;			//����̉ߋ��̈ʒu�ԍ�
	int m_OldMyGRIDNum = -1;				//�����̉ߋ��̂����ԍ�
	int NowMoveGRIDNum = -1;				//���݂̈ړ���GRID
	int m_nMoveCnt = 0;						//�ړ��J�E���^
	bool bTurretRotationNow=false;			//����
	float fRotTurret=false;					//�C���̊p�x
};

#endif