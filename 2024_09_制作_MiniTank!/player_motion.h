//=========================================================
//
// player_motion.cpp�Ŏg���֐�[player_motion.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _MOTIONPLAYER_H
#define _MOTIONPLAYER_H//��d�C���N���[�h�h�~

#include "object_motion.h"
#include "HpLatter.h"
#include "HP_gauge.h"
#include "resuscitation.h"

class CObjectMotionPlayer : public CObjectMotion
{
public:
	static const int START_PLAYER_NUM = 3;				//�c�@
	static const int AABB_BOX_PLAYER = 75;				//AABB�p�T�C�Y
	static const int RESET_CNT = 90;					//���X�^�[�g�J�E���^
	static const int DAMAGE = 100;						//�_���[�W
	static const int LIFE = 300;						//����
	const float OBB_LENGTH[3] = { 90.0f,90.0f,120.0f };	//OBB�̒���

	CObjectMotionPlayer(int nPriority = CObject::LAYERINDEX_MOTIONPLAYER);//�R���X�g���N�^
	~CObjectMotionPlayer() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectMotionPlayer* Create(const char* pfilePass, DATA SetData);//�I�u�W�F�N�g����

	void Input();						  //���͌n(static)
	void ControllerInput();				  //�R���g���[������

	static void SetPlayerNum(int SetNum); //�c�@�i�[
	static int GetPlayerNum();			  //�c�@�擾

	void SetStartPos(D3DXVECTOR3 pos);	  //�X�^�[�g�n�_�i�[
	D3DXVECTOR3 GetTARGETPOS();			  //�ڕW�n�_�擾

	void SetLinearInterpolation();		  //���`��Ԓn�_�`��

private:

	static int m_nNumPlayerAll;					//����
	 bool m_bDown=false;						//�_�E��������

	 CMathProc::CollisionData m_HitData = {};	//�����蔻��f�[�^

	int m_nLife=0;								//����
	int m_nMoveCnt=0;							//�ړ��J�E���^
	int m_ResetCnt = 0;							//���Z�b�g�J�E���^
	int ShotDelay = 0;							//���Cdelay
	int EscCntFootPrint=0;						//���ՃJ�E���^

	D3DXVECTOR3 m_RESTART_POS = {};				//���X�^�[�g�n�_
	D3DXVECTOR3 m_TargetPos = {};				//�Ə��ʒu
	D3DXVECTOR3 m_BulletPosMove = {};			//�Ə��ʒu�pmove�l
	CObjectHPLatterUI* m_pHPUI = nullptr;		//HP�pUI
	CObjectHPGaugeUI* m_pHPGauge[2] = {};		//HP�Q�[�W�pUI
	CRescue* m_Resue = nullptr;					//�h���pUI
};

#endif