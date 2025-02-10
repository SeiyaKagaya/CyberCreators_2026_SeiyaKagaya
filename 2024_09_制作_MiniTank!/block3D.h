//=========================================================
//
// block3D.cpp�Ŏg���֐�[block3D.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _BLOCK3D_H
#define _BLOCK3D_H//��d�C���N���[�h�h�~

#include "object.h"
#include "objectX.h"
#include <Windows.h>
#include "d3dx9.h"//�`�ʏ����Ɏg��

class CBlock3D : public CObjectX
{
public:
	const float SIZE = 50.0f;

	CBlock3D(int nPriority = CObject::LAYERINDEX_OBJECT3D);//�R���X�g���N�^
	~CBlock3D() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CBlock3D* Create();//�I�u�W�F�N�g����
};
#endif