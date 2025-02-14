//=========================================================
//
// smoke�Ŏg���֐�[smoke.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _SMOKE_H
#define _SMOKE_H//��d�C���N���[�h�h�~

#include "Object_billboard.h"
#include "d3dx9.h"//�`�ʏ����Ɏg��
#include "main.h"

class CObjectSmoke: public CObjectBillBoard
{
public:

	static const int  PRINTSIZE_X = 30;		//�T�C�Y
	static const int  PRINTSIZE_Z = 15;
	static const int START_LIFE = 60;		//����
	static const int DIVISION_NUMBER = 8;	//�e�N�X�`��������
	const float RGB_A = 0.35f;				//�A���t�@�l

	CObjectSmoke(int nPriority = CObject::LAYERINDEX_SMOKE);//�R���X�g���N�^
	~CObjectSmoke() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectSmoke* Create(D3DXVECTOR3 Pos);//object����

	void SetPos(D3DXVECTOR3 Pos);

	//���_�i�[
	void InputpVtx()override;

private:

	int m_nLife=0;		 //�����ŏ���
	int m_nPatternAnim=0;//����
};

#endif