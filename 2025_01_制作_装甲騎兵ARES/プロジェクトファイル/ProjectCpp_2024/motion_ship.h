//=========================================================
//
// player_motion.cpp�Ŏg���֐�[player_motion.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _OBJECT_SHIP_H

#define _OBJECT_SHIP_H//��d�C���N���[�h�h�~

#include "object_motion.h"
#include "newbullet.h"


//class CShield;//�O���錾

class CObjectShip : public CObjectMotion
{
public:
	//static const int START_LIFE = 500;
	static const int START_PLAYER_NUM = 3;		//�c�
	static const int AABB_BOX_PLAYER = 90;		//AABB�T�C�Y
	//static const int RESET_CNT = 90;			//�������x
	//static const int  MOVESPEED = 9;			//�ړ����x
	//static const int GRAVITY = 29;				//�d��
	//const float JoyStickDiff = 0.0004f;			//�X�e�B�b�N�{��
	//static const int BULLETSPEED = 125;			//�C�e���x
	//static const int RANDINGTRIGGER_FARAME = 10;//���n����t���[��
	//static const int BOOST_FARAME = 4;			//Boost�̃t���[��
	//static const int BOOST_RESTFARAME = 5;		//Boost��̗]�C
	//static const int BOOST_MAG = 3;				//�u�[�X�g���A�t�^�[�o�[�i�[�{��

	//static const int MISSILEMAX = 6;			//�~�T�C���̃X�g�b�N�ő�l
	//static const int RECOVERY_MISSILE = 45;		//�L�ڃt���[����1��

	//const float SHIELD_SET_ADDPOS = 130.0f;
	//const float TARGET_SET_ADDPOS = 150.0f;
	//const float SHOTPOS_Y = 70.0f;
	//const float SHOTPOS_Z = -190.0f;



	CObjectShip(int nPriority = CObject::LAYERINDEX_MOTIONB2);//�R���X�g���N�^
	~CObjectShip() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectShip* Create(std::string pfilePass, DATA SetData);//�I�u�W�F�N�g����




private:

	static int m_nNumPlayerAll;//����
//	bool m_bDown;//�_�E��������

	CMathProc::CollisionData m_HitData;//�����蔻��f�[�^

//	bool m_btest = false;

//	int m_nLife;//�̗�


//	int m_nMoveCnt;//����

//	int m_ResetCnt = 0;//Reset�t���[��

//	int m_ShotDelay = 0;//���Cdelay

//	D3DXVECTOR3 m_RESTART_POS;//���X�^�[�g�n�_

//	D3DXVECTOR3 m_TargetPos;//�Ə��ʒu

//	int m_EscCntFootPrint = 0;//���ՃJ�E���^�[(�^�C�g��)

	MOTIONTYPE m_OldInputMotionParent = MOTIONTYPE_STANDBY;//�Â����[�V����

///	bool m_GameStart = false;//�Q�[���X�^�[�g�������ォ
//	int m_RandingCutCnt = 0;//���n�J�E���^�[


//	int m_nBoostCnt = 0;//�u�[�X�g����
	//int m_BoostRestCnt = 0;//�u�[�X�g�I�������

	//GUARD���
//	bool m_guard = false;

//	CShield* m_pShield;//�V�[���h���i�[

//	bool m_bBuletLockOn = false;//





//	int m_nMissileStock = MISSILEMAX;//�~�T�C���X�g�b�N��
//	int m_nMissileRecoveryCnt = 0;	 //�~�T�C���̉񕜃J�E���g
	int m_nCntFrame = 0;
};

#endif