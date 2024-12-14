//=========================================================
//
// enemy_motion_fast.cpp�Ŏg���֐�[enemy_motion_fast.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _MOTIONENEMYFAST_H

#define _MOTIONENEMYFAST_H//��d�C���N���[�h�h�~

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

class CObjectMotionEnemyfast : public CObjectMotionEnemyBase
{
public:
	const float MOVEROT = 0.065f;//���񑬓x
	static const int BULLETMOVESPEED_NOMAL = 15;//�C�e���x
	static const int BULLETSHOTDELAY = 75;
	const float MOVESPEED = 4.8f;
	static const int  reflectNum = 0;


	CObjectMotionEnemyfast(int nPriority = CObject::LAYERINDEX_MOTIONENEMY_FAST);//�R���X�g���N�^


	~CObjectMotionEnemyfast() override;//�f�X�g���N�^

	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectMotionEnemyfast* Create(const char* pfilePass, DATA SetData);//�I�u�W�F�N�g����

//	virtual void LoadRouteTable()override;

	void Attack();
	DATA phase1(D3DXVECTOR3 ShotPos);
	DATA phase2();

	void TurretRotation(D3DXVECTOR3 ShotPos, D3DXVECTOR3 TargetPos, D3DXVECTOR3 BulletMove);
	void ShotBullet(D3DXVECTOR3 ShotPos, D3DXVECTOR3 TargetPos, D3DXVECTOR3 BulletMove);//�C������Ǝˌ��𓝊�


	//�X�N���[���|�W�V�������擾
	void SetSCREENPOS(D3DXVECTOR3 pos) { m_ScreenPosition = pos; };
	D3DXVECTOR3 GetScreenPos() { return m_ScreenPosition; };

	void SetDamage(int nDamage) { m_nLife -= nDamage; };

	////LOCK ON�֌W
	//void SetNormalLockOn(bool bSet) { m_bNormalLockOn = bSet; };
	//bool GetNormalLockOn() { return m_bNormalLockOn; };

	//void SetBulletLockOn(bool bSet) { m_bBulletLockOn = bSet; };
	//bool GetBulletLockOn() { return m_bBulletLockOn; };

	//void SetDiffTrue(bool bSet) { m_DiffTrue = bSet; };
	//bool GetDiffTrue() { return m_DiffTrue; };


	CLockOnUI* GetLockOnUI() { return m_LockOnUI; };
	CLockOnUIMain* GetLockOnUIMain() { return m_LockOnUI_Main;};

private:

	CMathProc::CollisionData m_HitData;//�����蔻��f�[�^

	bool btest = false;

	int m_nLife = 0;
	int m_BulletDelay = 0;

	D3DXVECTOR3 m_TargetPos;//���݂̖ڕW�n�_
	int m_OldTargetGRIDNum = -1;//����̉ߋ��̈ʒu�ԍ�
	int m_OldMyGRIDNum = -1;//�����̉ߋ��̂����ԍ�

	D3DXVECTOR3 m_TargetMove;

	//���݂̈ړ���GRID
	int NowMoveGRIDNum = -1;

	bool bTurretRotationNow;//����
	float fRotTurret;//�C���̊p�x

	int m_nMoveCnt = 0;

	//�ȉ�"��{��3D"�̂�
	CLockOnUI* m_LockOnUI;	       //--���b�N�I��
	CLockOnUIMain* m_LockOnUI_Main;//---�o���b�g���b�N�I��

	D3DXVECTOR3 m_ScreenPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

//	bool m_bNormalLockOn = false;//���ʃ��b�N
//	bool m_bBulletLockOn = false;//�ˌ����b�N
	//bool m_DiffTrue = false;	 //���b�N�n�v�Z�L��
};

#endif