//=========================================================
//
// player3D.cpp�Ŏg���֐�[player3D.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _PLAYER3D_H
#define _PLAYER3D_H//��d�C���N���[�h�h�~

#include "object.h"
#include "objectX.h"
#include <Windows.h>
#include "d3dx9.h"//�`�ʏ����Ɏg��
#include "MathUtilities.h"

class CPlayer3D : public CObjectX
{
public:	
	const  float DAMPING_RATIO = 0.5f;
	
	CPlayer3D(int nPriority = CObject::LAYERINDEX_PLAYER3D);//�R���X�g���N�^
	~CPlayer3D() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void Action_Keyboard();//�����tKeyboard
	void Action_JoyPad();//�����t�W���C�p�b�h
	void HitCollision();//�����蔻��܂Ƃ�

	CObject::DATA GetPlayerData();//�f�[�^�擾(player���͂悭�g�p���邽��)

	static CPlayer3D* Create();//�I�u�W�F�N�g����
private:
	CMathProc::CollisionData m_HitData;//�����蔻��f�[�^
};

#endif