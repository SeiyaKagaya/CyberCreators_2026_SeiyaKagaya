//=========================================================
//
// HpLatter�Ŏg���֐�[HpLatter.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _HPLATTERUI_H
#define _HPLATTERUI_H//��d�C���N���[�h�h�~

#include "Object_billboard.h"
#include "d3dx9.h"//�`�ʏ����Ɏg��
#include "main.h"

class CObjectHPLatterUI : public CObjectBillBoard
{
public:

	static const int  PRINTSIZE_X = 45;//�T�C�Y
	static const int  PRINTSIZE_Z = 45;

	CObjectHPLatterUI(int nPriority = CObject::LAYERINDEX_HPLATTERUI);//�R���X�g���N�^
	~CObjectHPLatterUI() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectHPLatterUI* Create(D3DXVECTOR3 Pos);//object����

	//���W�i�[
	void SetPos(D3DXVECTOR3 Pos);

	//���_�i�[
	void InputpVtx()override;

private:

	D3DXVECTOR3 m_Pos = {};

	D3DXCOLOR m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
};

#endif