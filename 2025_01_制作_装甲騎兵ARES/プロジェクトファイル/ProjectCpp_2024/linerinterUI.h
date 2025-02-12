//=========================================================
//
// linerinterUI�Ŏg���֐�[linerinterUI.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _LINEUI_H
#define _LINEUI_H//��d�C���N���[�h�h�~

#include "Object_billboard.h"
#include "d3dx9.h"//�`�ʏ����Ɏg��
#include "main.h"

class CObjectLINEUI : public CObjectBillBoard
{
public:

	const float  PRINTSIZE = 20.0f;
	static const int LIFE = 6;

	CObjectLINEUI(int nPriority = CObject::LAYERINDEX_LINEUI);//�R���X�g���N�^
	~CObjectLINEUI() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectLINEUI* Create(D3DXVECTOR3 Pos);//object����

	void SetPos(D3DXVECTOR3 Pos);//���W�i�[

	//���_�i�[
	void InputpVtx()override;

private:

	D3DXVECTOR3 m_Pos;

	D3DXCOLOR m_col;

	int m_nLife = 0;
};

#endif