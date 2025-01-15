//=========================================================
//
// enemy_motion_Nomal.cpp�Ŏg���֐�[enemy_motion_Nomal.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _MOTIONENEMYBOSS_H

#define _MOTIONENEMYBOSS_H//��d�C���N���[�h�h�~

//#include "object.h"
//#include "objectX.h"
//
//#include <Windows.h>
//#include "d3dx9.h"//�`�ʏ����Ɏg��
//#include "MathUtilities.h"
//#include <vector>
//#include "object_motion.h"

#include "enemy_motion_base.h"
#include "LockOnUI.h"
#include "LockOnUIMain.h"


//�����CObjectMotionEnemyBase�̔h���N���X

class CObjectMotionEnemyBoss : public CObjectMotionEnemyBase
{
public:
	const float MOVEROT = 0.065f;//���񑬓x
	static const int BULLETMOVESPEED_NOMAL = 25;//�C�e���x
	static const int BULLETSHOTDELAY = 175;
	const float MOVESPEED = 3.2f;
	static const int  reflectNum = 0;
	static const int DAMAGEFRAME = 3;
	static const int LOCKDIFF = 200;

	CObjectMotionEnemyBoss(int nPriority = CObject::LAYERINDEX_MOTIONENEMY_BOSS);//�R���X�g���N�^


	~CObjectMotionEnemyBoss() override;//�f�X�g���N�^

	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectMotionEnemyBoss* Create(std::string pfilePass, DATA SetData);//�I�u�W�F�N�g����

	void Attack();
	DATA phase1(D3DXVECTOR3 ShotPos);
	DATA phase2();

	void TurretRotation(D3DXVECTOR3 ShotPos, D3DXVECTOR3 TargetPos, D3DXVECTOR3 BulletMove);
	void ShotBullet(D3DXVECTOR3 ShotPos, D3DXVECTOR3 TargetPos, D3DXVECTOR3 BulletMove);//�C������Ǝˌ��𓝊�


	//�X�N���[���|�W�V�������擾
	void SetSCREENPOS(D3DXVECTOR3 pos) { m_ScreenPosition = pos; };
	D3DXVECTOR3 GetScreenPos() { return m_ScreenPosition; };

	CLockOnUI* GetLockOnUI() { return m_LockOnUI; };
	CLockOnUIMain* GetLockOnUIMain() { return m_LockOnUI_Main; };

	void SetDamage(int nDamage) { m_nLife -= nDamage; m_bDamageRedNow = true; m_nDamageFrameCnt = DAMAGEFRAME; };

private:

	CMathProc::CollisionData m_HitData;//�����蔻��f�[�^

	bool btest = false;

	int m_nLife=0;
	int m_nBulletDelay=0;

	D3DXVECTOR3 m_TargetPos;//���݂̖ڕW�n�_
	int m_nOldTargetGRIDNum = -1;//����̉ߋ��̈ʒu�ԍ�
	int m_nOldMyGRIDNum = -1;//�����̉ߋ��̂����ԍ�

	D3DXVECTOR3 m_TargetMove;

	//���݂̈ړ���GRID
	int nNowMoveGRIDNum = -1;


	bool bTurretRotationNow=false;//����
	float fRotTurret=0.0f;//�C���̊p�x

	int m_nMoveCnt=0;

	//�ȉ�"��{��3D"�̂�
	CLockOnUI* m_LockOnUI;
	CLockOnUIMain* m_LockOnUI_Main;

	D3DXVECTOR3 m_ScreenPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	bool m_bDamageRedNow = false;
	int m_nDamageFrameCnt = 0;

	int m_nEscCnt = 60;
};

#endif