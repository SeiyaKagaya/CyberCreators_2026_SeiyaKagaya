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

//

class CObjectShotFire : public CObjectBillBoard
{
public:

	static const int EX_WIDE = 150;
	static const int EX_HEIGHT = 150;

	const int START_LIFE = 120;
	const int DIVISION_NUMBER = 15;	//�e�N�X�`��������


//	static const int STANPLIFE = 2 * 60;
	static const int  PRINTSIZE_X = 200;
	static const int  PRINTSIZE_Z = 200;


	CObjectShotFire(int nPriority = CObject::LAYERINDEX_SHOTFIRE);//�R���X�g���N�^
	~CObjectShotFire() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectShotFire* Create(D3DXVECTOR3 Pos);//object����

	void SetPos_Rot(D3DXVECTOR3 Pos);

	//���_�i�[
	void InputpVtx()override;


private:

	int m_nLife;//�����ŏ���

	int m_nPatternAnim;//����

	int m_nDelay;
};

#endif