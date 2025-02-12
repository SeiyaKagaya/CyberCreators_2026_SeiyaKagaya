//=========================================================
//
// shotfire�Ŏg���֐�[shorfire.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _SHOTFIRE_H
#define _SHOTFIRE_H//��d�C���N���[�h�h�~

#include "Object_billboard.h"
#include "d3dx9.h"//�`�ʏ����Ɏg��
#include "main.h"

class CObjectShotFire : public CObjectBillBoard
{
public:

	const int START_LIFE = 30;
	const int DIVISION_NUMBER = 15;	//�e�N�X�`��������
	const float  PRINTSIZE = 200.0f;

	CObjectShotFire(int nPriority = CObject::LAYERINDEX_SHOTFIRE);//�R���X�g���N�^
	~CObjectShotFire() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectShotFire* Create(D3DXVECTOR3 Pos);//object����

	void SetPos(D3DXVECTOR3 Pos);

	//���_�i�[
	void InputpVtx()override;

private:

	int m_nLife = 0;//�����ŏ���

	int m_nPatternAnim = 0;//����

	int m_nDelay = 0;
};

#endif