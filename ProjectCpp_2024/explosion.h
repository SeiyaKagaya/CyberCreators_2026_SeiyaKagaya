//=========================================================
//
// ballet.cpp�Ŏg���֐�[ballet.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _POLYGON_H

#define _POLYGON_H//��d�C���N���[�h�h�~

#include "object.h"
#include "object2D.h"

#include <Windows.h>
#include "d3dx9.h"//�`�ʏ����Ɏg��
//
class CExplosion : public CObject2D
{
public:

	static const int EX_WIDE = 150;
	static const int EX_HEIGHT = 150;

	const int START_LIFE = 120;
	const int DIVISION_NUMBER = 8;	//�e�N�X�`��������



	CExplosion(int nPriority = CObject::LAYERINDEX_EXPLOSION);//�R���X�g���N�^
	~CExplosion() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	//���_�i�[
	void InputpVtx()override;


	static CExplosion* Create(DATA data);//�I�u�W�F�N�g����
private:
	int m_nLife;
	int m_nPatternAnim;
};

#endif