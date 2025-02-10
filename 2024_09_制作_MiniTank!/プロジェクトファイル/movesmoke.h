//=========================================================
//
// movesmoke�Ŏg���֐�[movesmoke.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _MOVESMOKE_H
#define _MOVESMOKE_H//��d�C���N���[�h�h�~

#include "Object_billboard.h"
#include "d3dx9.h"//�`�ʏ����Ɏg��
#include "main.h"

class CMoveSmoke : public CObjectBillBoard
{
public:

	static const int  PRINTSIZE_X = 120;	//�T�C�Y
	static const int  PRINTSIZE_Z = 120;
	static const int START_LIFE = 60;		//����
	static const int DIVISION_NUMBER = 8;	//�e�N�X�`��������

	CMoveSmoke(int nPriority = CObject::LAYERINDEX_ReflectEffect);//�R���X�g���N�^
	~CMoveSmoke() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CMoveSmoke* Create(D3DXVECTOR3 Pos);//object����

	//POS�i�[
	void SetPos(D3DXVECTOR3 Pos);

	//���_�i�[
	void InputpVtx()override;

private:

	int m_nLife = 0;//�����ŏ���

	int m_nPatternAnim = 0;//�����J�E���g

	D3DXCOLOR m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�J���[

	int m_nACnt = 100;//�J���[�̃A���t�@�l
};

#endif