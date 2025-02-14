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
	static const int FOOTPRINT = 10;					//���ь�̃X�^���v
	static const int BULLETSHOTDELAY = 20;							 //���C�Ԋu
	static const int POINTER_NUM = 7;					//���`��ԃ|�C���^�[�̐�

	const float BULLETSIZE = 10.0f;						//�C�e�\���T�C�Y
	const float TANKFIRE_OFFSETPOS_Z = -190.0f;			//�C���̐�[�ʒu�܂ł�offset
	const float OBB_LENGTH[3] = { 90.0f,90.0f,120.0f };	//OBB�̒���
	const float STICK_RADIUS = 500.0f;					//�Ə����a
	const float MOVESPEED = 8.1f;						//�ړ����x
	const float BULLETMOVE = 14.0f;						//�e�ۑ��x
	const float STICK_MAG = 0.0015f;					//�X�e�B�b�N�{��
	const float STICK_SUB = 6000.0f;					//�f�b�h�]�[������
	const float MIN_ANGLE_Y = -0.1f;					//�C�����񎞂̏㉺�̌��E�A���O��
	const float MAX_ANGLE_Y = 0.1f;
	const float POSY = 4.0f;							//�Œ�̍���

	const D3DXCOLOR BULLET_COLOR = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);//�e�̐F

	const D3DXVECTOR3 UI_POS[4] = {						//UI�p���W
		D3DXVECTOR3(-150.0f,400.0f,100.0f),
		D3DXVECTOR3(-100.0f,400.0f,100.0f) ,
		D3DXVECTOR3(-95.0f,400.0f,100.0f),
		D3DXVECTOR3(-70.0f,400.0f,100.0f)
	};

	const D3DXVECTOR3 UI_SIZE[2] = {					//HPUI�p�T�C�Y
	D3DXVECTOR3(320.0f, 18.0f, 0.0f),
	D3DXVECTOR3(-9999.9f, 14.0f, 0.0f) ,
	};

	const D3DXCOLOR HP_UI_COLOR[2] = {					//HPUI�p�J���[
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f),
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.9f)
	}; //�G�̐F


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