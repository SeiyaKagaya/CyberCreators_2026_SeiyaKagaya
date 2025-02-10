//=========================================================
//
// ExplosionBill�Ŏg���֐�[ExplosionBill.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _EXPRO_H
#define _EXPRO_H//��d�C���N���[�h�h�~

#include "Object_billboard.h"
#include "d3dx9.h"//�`�ʏ����Ɏg��
#include "main.h"

class CObjectExplosionBill : public CObjectBillBoard
{
public:

	static const int  PRINTSIZE = 100;		//�T�C�Y
	static const int DIVISION_NUMBER = 30;	//�e�N�X�`��������

	CObjectExplosionBill(int nPriority = CObject::LAYERINDEX_EXPRO_BILL);//�R���X�g���N�^
	~CObjectExplosionBill() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectExplosionBill* Create(D3DXVECTOR3 Pos);//object����

	//���W�i�[
	void SetPos(D3DXVECTOR3 Pos);

	//���_�i�[
	void InputpVtx()override;

private:

	int m_nPatternAnim = 0;//�����J�E���^
};

#endif