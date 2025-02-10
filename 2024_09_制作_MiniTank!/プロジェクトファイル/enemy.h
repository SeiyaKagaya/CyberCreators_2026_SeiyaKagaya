//=========================================================
//
// ballet.cpp�Ŏg���֐�[ballet.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _ENEMY_H
#define _ENEMY_H//��d�C���N���[�h�h�~

#include "object.h"
#include "object2D.h"
#include <Windows.h>
#include "d3dx9.h"//�`�ʏ����Ɏg��

class CEnemy : public CObject2D
{
public:
	static const int ENEMY_SIZE = 40;	//�T�C�Y
	static const int START_LIFE = 120;			//����
	
	CEnemy(int nPriority=CObject::LAYERINDEX_ENEMY);//�R���X�g���N�^
	~CEnemy() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	//���_�i�[
	void InputpVtx()override;
	static CEnemy* Create(DATA data);//�I�u�W�F�N�g����
private:
	int m_nLife = 0;//����
};

#endif