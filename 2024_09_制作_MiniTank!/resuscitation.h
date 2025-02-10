//=========================================================
//
// resuscitation�Ŏg���֐�[resuscitation.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _RESCUE_H

#define _RESCUE_H//��d�C���N���[�h�h�~

#include "Object_billboard.h"
#include "d3dx9.h"//�`�ʏ����Ɏg��
#include "main.h"

class CRescue : public CObjectBillBoard
{
public:

	static const int  PRINTSIZE_X = 300;	//�T�C�Y
	static const int  PRINTSIZE_Z = 150;
	static const int START_LIFE = 120;		//����
	static const int DIVISION_NUMBER = 15;	//�e�N�X�`��������

	CRescue(int nPriority = CObject::LAYERINDEX_RESCUE);//�R���X�g���N�^
	~CRescue() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CRescue* Create(D3DXVECTOR3 Pos);//object����

	//���W�i�[
	void SetPos(D3DXVECTOR3 Pos);

	//���_�i�[
	void InputpVtx()override;

private:

	D3DXVECTOR3 m_Pos = {};

	D3DXCOLOR m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
};

#endif