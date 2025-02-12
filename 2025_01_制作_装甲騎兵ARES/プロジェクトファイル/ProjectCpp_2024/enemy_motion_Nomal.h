//=========================================================
//
// enemy_motion_Nomal.cpp�Ŏg���֐�[enemy_motion_Nomal.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _MOTIONENEMYNOMAL_H
#define _MOTIONENEMYNOMAL_H//��d�C���N���[�h�h�~

#include "enemy_motion_base.h"
#include "LockOnUI.h"
#include "LockOnUIMain.h"

//�����CObjectMotionEnemyBase�̔h���N���X
class CObjectMotionEnemyNomal : public CObjectMotionEnemyBase
{
public:
	 const float MOVEROT = 0.065f;//���񑬓x
	 static const int BULLETMOVESPEED_NOMAL = 25;//�C�e���x
	 static const int BULLETSHOTDELAY = 175;	//���C�Ԋu
	 static const int NORMAL_LIFE = 100;

	 const float MOVESPEED = 3.2f;
	 static const int  reflectNum = 0;
	 static const int DAMAGEFRAME = 3;
	 static const int LOCKDIFF = 40;
	 static const int AIRMOVESPEED = 10;
	 static const int MAXMOVECNT = 85;
	 static const int GRAVITY = 3;				//�d��

	CObjectMotionEnemyNomal(int nPriority = CObject::LAYERINDEX_MOTIONENEMY_NOMAL);//�R���X�g���N�^


	 ~CObjectMotionEnemyNomal() override;//�f�X�g���N�^

	 HRESULT Init()override;
	 void Uninit()override;
	 void Update()override;
	 void Draw()override;

	static CObjectMotionEnemyNomal* Create(std::string pfilePass, DATA SetData);//�I�u�W�F�N�g����

	//�U������
	void Attack();

	void TurretRotation(D3DXVECTOR3 ShotPos, D3DXVECTOR3 TargetPos, D3DXVECTOR3 BulletMove);
	void ShotBullet(D3DXVECTOR3 ShotPos, D3DXVECTOR3 TargetPos, D3DXVECTOR3 BulletMove);//�C������Ǝˌ��𓝊�

	//�X�N���[���|�W�V�������擾
	void SetSCREENPOS(D3DXVECTOR3 pos) { m_ScreenPosition = pos; };
	D3DXVECTOR3 GetScreenPos() { return m_ScreenPosition; };

	//���b�N�I��UI���擾
	CLockOnUI* GetLockOnUI() { return m_LockOnUI; };
	CLockOnUIMain* GetLockOnUIMain() { return m_LockOnUI_Main; };

	//�_���[�W����
	void SetDamage(int nDamage) { m_nLife -= nDamage; m_bDamageRedNow = true; m_nDamageFrameCnt = DAMAGEFRAME; };

private:

	CMathProc::CollisionData m_HitData;//�����蔻��f�[�^

	int m_nLife=0;
	int m_nBulletDelay=0;

	int m_nOldTargetGRIDNum = -1;//����̉ߋ��̈ʒu�ԍ�
	int m_nOldMyGRIDNum = -1;//�����̉ߋ��̂����ԍ�

	D3DXVECTOR3 m_TargetPos;//���݂̖ڕW�n�_
	D3DXVECTOR3 m_TargetMove;

	//���݂̈ړ���GRID
	int m_nNowMoveGRIDNum = -1;

	bool m_bTurretRotationNow=false;//����

	float m_fRotTurret=0.0f;//�C���̊p�x

	int m_nMoveCnt=0;

	//�ȉ�"��{��3D"�̂�
	CLockOnUI* m_LockOnUI;
	CLockOnUIMain* m_LockOnUI_Main;

	D3DXVECTOR3 m_ScreenPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	bool m_bDamageRedNow = false;
	int m_nDamageFrameCnt = 0;
	int nMoveCnt = 0;
};

#endif