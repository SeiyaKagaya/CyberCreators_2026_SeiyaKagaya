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
#include "shield.h"

//�����CObjectMotionEnemyBase�̔h���N���X

class CObjectMotionEnemyBoss : public CObjectMotionEnemyBase
{
public:
	const float MOVEROT = 0.065f;				//���񑬓x
	const float MOVESPEED = 3.2f;				//�ړ����x
	static const int LIFE = 1000;				//�̗�
	static const int BULLETMOVESPEED_NOMAL = 25;//�C�e���x
	static const int BULLETSHOTDELAY = 175;		//���C�Ԋu
	static const int  reflectNum = 0;			//���ˉ�
	static const int DAMAGEFRAME = 3;			//��e���t���[����
	static const int LOCKDIFF = 200;			//���b�N�I���p����
	static const int EMNEMY_DROPCOUNT = 300;	//�G�o���J�E���g

	CObjectMotionEnemyBoss(int nPriority = CObject::LAYERINDEX_MOTIONENEMY_BOSS);//�R���X�g���N�^


	~CObjectMotionEnemyBoss() override;//�f�X�g���N�^

	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectMotionEnemyBoss* Create(std::string pfilePass, DATA SetData);//�I�u�W�F�N�g����

	//�X�N���[���|�W�V�������擾
	void SetSCREENPOS(D3DXVECTOR3 pos) { m_ScreenPosition = pos; };
	D3DXVECTOR3 GetScreenPos() { return m_ScreenPosition; };

	//���b�N�I��UI�擾
	CLockOnUI* GetLockOnUI() { return m_LockOnUI; };
	//���C�����b�N�I��UI�擾
	CLockOnUIMain* GetLockOnUIMain() { return m_LockOnUI_Main; };

	//��e
	void SetDamage(int nDamage) { m_nLife -= nDamage; m_bDamageRedNow = true; m_nDamageFrameCnt = DAMAGEFRAME; };

	//�G�����擾
	static int GetEnemyAllNum() { return m_nNumENemyAll; };

private:

	CMathProc::CollisionData m_HitData = {};//�����蔻��f�[�^

	int m_nLife = LIFE;
	int m_nBulletDelay = 0;//���CDelay

	D3DXVECTOR3 m_TargetPos = {};//���݂̖ڕW�n�_
	int m_nOldTargetGRIDNum = -1;//����̉ߋ��̈ʒu�ԍ�
	int m_nOldMyGRIDNum = -1;//�����̉ߋ��̂����ԍ�

	D3DXVECTOR3 m_TargetMove = {};

	//���݂̈ړ���GRID
	int nNowMoveGRIDNum = -1;


	bool bTurretRotationNow = false;//����
	float fRotTurret = 0.0f;//�C���̊p�x

	int m_nMoveCnt = 0;

	//�ȉ�"��{��3D"�̂�
	CLockOnUI* m_LockOnUI = {};
	CLockOnUIMain* m_LockOnUI_Main = {};

	D3DXVECTOR3 m_ScreenPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	bool m_bDamageRedNow = false;
	int m_nDamageFrameCnt = 0;

	int m_nEscCnt = 60;

	CShield* m_pShield;//�V�[���h���i�[

	int m_nMovieCnt = 0;
	static int m_nNumENemyAll;//�G����

	int m_nEnemyCreateCnt = 0;

};

#endif