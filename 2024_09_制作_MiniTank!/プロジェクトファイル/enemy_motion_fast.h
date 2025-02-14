//=========================================================
//
// enemy_motion_fast.cpp�Ŏg���֐�[enemy_motion_fast.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _MOTIONENEMYFAST_H
#define _MOTIONENEMYFAST_H//��d�C���N���[�h�h�~

#include "enemy_motion_base.h"


//�����CObjectMotionEnemyBase�̔h���N���X

class CObjectMotionEnemyfast : public CObjectMotionEnemyBase
{
public:
	const float POSY = 4.0f;										 //�Œ�̍���
	const float MOVEROT = 0.065f;									 //���񑬓x
	const float MOVESPEED = 4.8f;									 //�C�e���x1
	const float TARGETSPEED = 1500.0f;								 //����̗\�����x
	const float TANKFIRE_OFFSETPOS_Z = -190.0f;						 //�C���̐�[�ʒu�܂ł�offset
	const float BULLETSIZE = 30.0f;									 //�C�e�\���T�C�Y
	const float OBB_LENGTH[3] = { 90.0f,90.0f,120.0f };				 //OBB�̒���
	static const int MOVESPEED2 = 15;								 //�C�e���x2
	static const int BULLETSHOTDELAY = 155;							 //���C�Ԋu
	static const int LIFE = 100;									 //����
	static const int DAMAGE = 100;									 //�_���[�W
	static const int RADIUS = 110;									 //���a
	static const int BULLET_LINE_LENGTH = 80;						 //�ː��̒���
	static const int STAMPCNT = 30;									 //���ь�J�E���g
	const D3DXCOLOR ENEMY_COLOR = D3DXCOLOR(0.3f, 0.1f, 0.3f, 1.0f); //�G�̐F
	const D3DXCOLOR BULLET_COLOR = D3DXCOLOR(0.7f, 0.3f, 0.3f, 1.0f);//�e�̐F

	
	
	CObjectMotionEnemyfast(int nPriority = CObject::LAYERINDEX_MOTIONENEMY_FAST);//�R���X�g���N�^

	~CObjectMotionEnemyfast() override;//�f�X�g���N�^

	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectMotionEnemyfast* Create(const char* pfilePass, DATA SetData);//�I�u�W�F�N�g����

	void Attack();						//�U���֌W
	DATA phase1(D3DXVECTOR3 ShotPos);	//�U���t�F�[�Y1
	DATA phase2();						//�U���t�F�[�Y2

	void TurretRotation(D3DXVECTOR3 ShotPos, D3DXVECTOR3 TargetPos, D3DXVECTOR3 BulletMove);//�C������
	void ShotBullet(D3DXVECTOR3 ShotPos, D3DXVECTOR3 TargetPos, D3DXVECTOR3 BulletMove);	//�ˌ��n

private:

	CMathProc::CollisionData m_HitData = {}; //�����蔻��f�[�^
	D3DXVECTOR3 m_TargetPos = {};		  	 //���݂̖ڕW�n�_
	int m_nLife=0;							 //����
	int m_BulletDelay=0;					 //���C�Ԋu
	int m_nMoveCnt = 0;						 //�ړ��J�E���^
	int m_OldTargetGRIDNum = -1;			 //����̉ߋ��̈ʒu�ԍ�
	int m_OldMyGRIDNum = -1;				 //�����̉ߋ��̂����ԍ�
	int NowMoveGRIDNum = -1;				 //���݂̈ړ���GRID
	bool bTurretRotationNow=false;			 //����
	float fRotTurret=0.0f;					 //�C���̊p�x
};
#endif