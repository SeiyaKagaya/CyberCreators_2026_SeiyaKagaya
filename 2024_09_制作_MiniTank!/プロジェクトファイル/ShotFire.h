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

	static const int  PRINTSIZE_X = 200;//�T�C�Y
	static const int  PRINTSIZE_Z = 200;
	static const int START_LIFE = 60;		//����
	static const int DIVISION_NUMBER = 15;	//�e�N�X�`��������

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
};

#endif