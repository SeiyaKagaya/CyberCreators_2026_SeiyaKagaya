//=========================================================
//
// HP_gauge�Ŏg���֐�[HP_gauge.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _HPGAUGEUI_H
#define _HPGAUGEUI_H//��d�C���N���[�h�h�~

#include "Object_billboard.h"
#include "d3dx9.h"//�`�ʏ����Ɏg��
#include "main.h"

class CObjectHPGaugeUI : public CObjectBillBoard
{
public:

	CObjectHPGaugeUI(int nPriority = CObject::LAYERINDEX_HPGAUGEUI);//�R���X�g���N�^
	~CObjectHPGaugeUI() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectHPGaugeUI* Create(D3DXVECTOR3 Pos);//object����

	void SetPos(D3DXVECTOR3 Pos);//�T�C�Y�i�[

	void SetSize(D3DXVECTOR3 size);//�T�C�Y�i�[

	void InputpVtx()override;//���_�Z�b�g

	void SetCol(D3DXCOLOR col);//�F�i�[

private:

	D3DXVECTOR3 m_Pos = {};									//���W
	D3DXCOLOR m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//�F
	D3DXVECTOR3 m_SetSize = {};								//�T�C�Y
};

#endif