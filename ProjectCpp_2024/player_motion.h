//=========================================================
//
// player_motion.cpp�Ŏg���֐�[player_motion.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _MOTIONPLAYER_H

#define _MOTIONPLAYER_H//��d�C���N���[�h�h�~

#include "object_motion.h"

class CObjectMotionPlayer : public CObjectMotion
{
public:
	static const int START_PLAYER_NUM = 3;
	static const int AABB_BOX_PLAYER = 90;
	static const int RESET_CNT = 90;
	static const int  MOVESPEED = 9;
	static const int GRAVITY = 99;//�d��

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

private:

	static int m_nNumPlayerAll;//����
	 bool m_bDown;//�_�E��������

	CMathProc::CollisionData m_HitData;//�����蔻��f�[�^

	bool btest = false;

	int m_nLife;
	int m_nMoveCnt;

	int m_ResetCnt = 0;

	int ShotDelay = 0;//���Cdelay

	D3DXVECTOR3 m_RESTART_POS;//���X�^�[�g�n�_

	D3DXVECTOR3 m_TargetPos;//�Ə��ʒu

	int EscCntFootPrint=0;

	D3DXVECTOR3 m_BulletPosMove=D3DXVECTOR3(0.0f,0.0f,0.0f);

	MOTIONTYPE m_OldInputMotionParent = MOTIONTYPE_STANDBY;


	bool m_GameStart = false;
};

#endif