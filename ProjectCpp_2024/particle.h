//=========================================================
//
// particle.cpp�Ŏg���֐�[particle.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _PARTICLE_H

#define _PARTICLE_H//��d�C���N���[�h�h�~

#include "object.h"
#include "object2D.h"

#include <Windows.h>
#include "d3dx9.h"//�`�ʏ����Ɏg��
//
class CParticle : public CObject2D
{
public:

	const int START_LIFE = 110;
	const int START_RADiUS = 11;

	CParticle(int nPriority=CObject::LAYERINDEX_PARTICLE);//�R���X�g���N�^
	~CParticle() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	//���_�i�[
	void InputpVtx()override;

	static CParticle* Create(DATA data);//�I�u�W�F�N�g����
private:
	int m_nLife;
	float m_Radius;

};


#endif