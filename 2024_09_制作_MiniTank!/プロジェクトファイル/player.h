//=========================================================
//
// player.cpp�Ŏg���֐�[player.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _PLAYER_H
#define _PLAYER_H//��d�C���N���[�h�h�~

#include "object.h"
#include "object2D.h"

#include <Windows.h>
#include "d3dx9.h"//�`�ʏ����Ɏg��
#include "MathUtilities.h"

//
class CPlayer : public CObject2D
{
public:

	static const int MAXSHOTDERAY = 7;		//���C�f�B���C�l
	static const int PLAYER_WIDE = 75;		//��
	static const int PLAYER_HEIGHT = 100;	//����
	static const int DISTANCE = 2;					//������

	CPlayer(int nPriority=CObject::LAYERINDEX_PLAYER);//�R���X�g���N�^
	~CPlayer() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CPlayer* Create();//�I�u�W�F�N�g����

	//���_�i�[
	void InputpVtx()override;

private:

	 void Action_Keyboard();	//�����tKeyboard
	 void Action_JoyPad();		//�����t�W���C�p�b�h
	 void HitCollision();		//�����蔻��܂Ƃ�

	 int m_nCounterAnim = 0;	//�A�j��Counter
	int m_nDirectionMove = 0;	//����//0���E����1����
	int m_nPatternAnim = 0;		//�p�^�[���ԍ�
	int m_BulletShotDelay = 0;	//���C�Ԋu�J�E���g
	
	float m_MAG = 0.0f;			//�{��
	float m_fLength = 0.0f;		//����
	float m_fAngle = 0.0f;		//�p�x

	bool m_bLandingNow = false; //���n

	CMathProc::CollisionData m_HitData = {};//�����蔻��f�[�^
};

#endif