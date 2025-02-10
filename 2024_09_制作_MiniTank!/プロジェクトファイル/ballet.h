//=========================================================
//
// ballet.cpp�Ŏg���֐�[ballet.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _BULLET_H
#define _BULLET_H//��d�C���N���[�h�h�~

#include "object.h"
#include "object2D.h"

#include <Windows.h>
#include "d3dx9.h"//�`�ʏ����Ɏg��

class CBullet : public CObject2D
{
public:

	static const int BULLET_SIZE = 10;	//�T�C�Y

	const int START_LIFE = 120;			//����
	const int START_SPEED = 10;			//���x

	CBullet(int nPriority=CObject::LAYERINDEX_BULLET);//�R���X�g���N�^
	~CBullet() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void HitCollision();//�����蔻��܂Ƃ�
	//���_�i�[
	void InputpVtx()override;
	static CBullet* Create(DATA data);//�I�u�W�F�N�g����
private:
	int m_nLife = 0;		//����
	float m_speed = 0.0f;	//���x
};

#endif