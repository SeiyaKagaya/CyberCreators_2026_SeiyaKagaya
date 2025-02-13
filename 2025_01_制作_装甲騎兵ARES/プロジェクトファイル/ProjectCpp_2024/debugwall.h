//=========================================================
//
// debugwall�Ŏg���֐�[debugwall.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _DEBUGWALL_H
#define _DEBUGWALL_H//��d�C���N���[�h�h�~

#include "object3D.h"
#include "d3dx9.h"//�`�ʏ����Ɏg��
#include "main.h"

class CDebugwall : public CObject3D
{
public:

	const float  PRINTSIZE = 1650;//���_�̒���

	CDebugwall(int nPriority = CObject::LAYERINDEX_DEBUGWALL);//�R���X�g���N�^
	~CDebugwall() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CDebugwall* Create(D3DXVECTOR3 Pos, D3DXVECTOR3 rot);//object����

	void SetPos_Rot(D3DXVECTOR3 Pos, D3DXVECTOR3 rot);//���W�Ɗp�x���i�[

	void InputpVtx()override;//���_�i�[
};

#endif