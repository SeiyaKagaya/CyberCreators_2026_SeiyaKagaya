//=========================================================
//
// player_motion.cpp�Ŏg���֐�[player_motion.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _MOTIONPLAYER_H

#define _MOTIONPLAYER_H//��d�C���N���[�h�h�~

#include "object_motion.h"



class CShield;//�O���錾

class CObjectMotionPlayer : public CObjectMotion
{
public:
	static const int START_PLAYER_NUM = 3;		//�c�
	static const int AABB_BOX_PLAYER = 90;		//AABB�T�C�Y
	static const int RESET_CNT = 90;			//�������x
	static const int  MOVESPEED = 9;			//�ړ����x
	static const int GRAVITY = 29;				//�d��
	const float JoyStickDiff = 0.0004f;			//�X�e�B�b�N�{��
	static const int BULLETSPEED = 35;			//�C�e���x
	static const int RANDINGTRIGGER_FARAME = 10;//���n����t���[��
	static const int BOOST_FARAME = 4;			//Boost�̃t���[��
	static const int BOOST_RESTFARAME = 5;		//Boost��̗]�C
	static const int BOOST_MAG = 3;				//�u�[�X�g���A�t�^�[�o�[�i�[�{��

	CObjectMotionPlayer(int nPriority = CObject::LAYERINDEX_MOTIONPLAYER);//�R���X�g���N�^
	~CObjectMotionPlayer() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectMotionPlayer* Create(const char* pfilePass, DATA SetData);//�I�u�W�F�N�g����

	void Input();//���͌n(static)
	void ControllerInput();//�R���g���[������

	static void SetPlayerNum(int SetNum);//�c�@�i�[
	static int GetPlayerNum();//�c�@�擾

	void SetStartPos(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetTARGETPOS();

	void SetLinearInterpolation();

	void SetbGuard(bool bSet) { m_guard = bSet; };
	bool GetbGuard() { return m_guard; };

private:

	static int m_nNumPlayerAll;//����
	 bool m_bDown;//�_�E��������

	CMathProc::CollisionData m_HitData;//�����蔻��f�[�^

	bool m_btest = false;

	int m_nLife;//�̗�
	int m_nMoveCnt;//����

	int m_ResetCnt = 0;//Reset�t���[��

	int m_ShotDelay = 0;//���Cdelay

	D3DXVECTOR3 m_RESTART_POS;//���X�^�[�g�n�_

	D3DXVECTOR3 m_TargetPos;//�Ə��ʒu

	int m_EscCntFootPrint=0;//���ՃJ�E���^�[(�^�C�g��)

	MOTIONTYPE m_OldInputMotionParent = MOTIONTYPE_STANDBY;//�Â����[�V����

	bool m_GameStart = false;//�Q�[���X�^�[�g�������ォ
	int m_RandingCutCnt = 0;//���n�J�E���^�[


	int m_nBoostCnt = 0;//�u�[�X�g����
	int m_BoostRestCnt = 0;//�u�[�X�g�I�������

	//GUARD���
	bool m_guard = false;
	

	CShield* m_pShield;//�V�[���h���i�[
};

#endif