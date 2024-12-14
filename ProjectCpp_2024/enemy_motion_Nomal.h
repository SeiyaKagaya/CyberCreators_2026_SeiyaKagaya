//=========================================================
//
// enemy_motion_Nomal.cpp�Ŏg���֐�[enemy_motion_Nomal.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _MOTIONENEMYNOMAL_H

#define _MOTIONENEMYNOMAL_H//��d�C���N���[�h�h�~

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

class CObjectMotionEnemyNomal : public CObjectMotionEnemyBase
{
public:
	 const float MOVEROT = 0.065f;//���񑬓x
	 static const int BULLETMOVESPEED_NOMAL = 12;//�C�e���x
	 static const int BULLETSHOTDELAY = 175;
	 const float MOVESPEED = 3.2f;
	 static const int  reflectNum = 0;


	CObjectMotionEnemyNomal(int nPriority = CObject::LAYERINDEX_MOTIONENEMY_NOMAL);//�R���X�g���N�^


	 ~CObjectMotionEnemyNomal() override;//�f�X�g���N�^

	 HRESULT Init()override;
	 void Uninit()override;
	 void Update()override;
	 void Draw()override;

	static CObjectMotionEnemyNomal* Create(const char* pfilePass, DATA SetData);//�I�u�W�F�N�g����

//	virtual void LoadRouteTable()override;

	void Attack();
	DATA phase1(D3DXVECTOR3 ShotPos);
	DATA phase2();

	void TurretRotation(D3DXVECTOR3 ShotPos, D3DXVECTOR3 TargetPos, D3DXVECTOR3 BulletMove);
	void ShotBullet(D3DXVECTOR3 ShotPos, D3DXVECTOR3 TargetPos, D3DXVECTOR3 BulletMove);//�C������Ǝˌ��𓝊�



	//�X�N���[���|�W�V�������擾
	void SetSCREENPOS(D3DXVECTOR3 pos) { m_ScreenPosition = pos; };
	D3DXVECTOR3 GetScreenPos() { return m_ScreenPosition; };

	////LOCK ON�֌W
	//void SetNormalLockOn(bool bSet) { m_bNormalLockOn = bSet; };
	//bool GetNormalLockOn() { return m_bNormalLockOn; };

	//void SetBulletLockOn(bool bSet) { m_bBulletLockOn = bSet; };
	//bool GetBulletLockOn() { return m_bBulletLockOn; };
	CLockOnUI* GetLockOnUI() { return m_LockOnUI; };
	CLockOnUIMain* GetLockOnUIMain() { return m_LockOnUI_Main; };

	void SetDamage(int nDamage) { m_nLife -= nDamage; };

private:

	CMathProc::CollisionData m_HitData;//�����蔻��f�[�^

//	COBB m_Obb;
	
	bool btest = false;

	int m_nLife;
	int m_BulletDelay;


	D3DXVECTOR3 m_TargetPos;//���݂̖ڕW�n�_
	int m_OldTargetGRIDNum = -1;//����̉ߋ��̈ʒu�ԍ�
	int m_OldMyGRIDNum = -1;//�����̉ߋ��̂����ԍ�

	D3DXVECTOR3 m_TargetMove;

	//���݂̈ړ���GRID
	int NowMoveGRIDNum = -1;



	bool bTurretRotationNow;//����
	float fRotTurret;//�C���̊p�x

//	int nTurretRotationCnt;//�ڕW�p�܂ł̕����t���[����//������̍����܂Ŋp�x�̍��ق��k�߂Ύˌ��J�n
	int m_nMoveCnt;

	//�ȉ�"��{��3D"�̂�
	CLockOnUI* m_LockOnUI;
	CLockOnUIMain* m_LockOnUI_Main;

//	bool m_bNormalLockOn = false;//���ʃ��b�N
//	bool m_bBulletLockOn = false;//�ˌ����b�N
	D3DXVECTOR3 m_ScreenPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
};

#endif