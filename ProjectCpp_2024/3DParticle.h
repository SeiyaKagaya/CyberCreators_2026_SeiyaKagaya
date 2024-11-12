//=========================================================
//
// 3DParticle�Ŏg���֐�[3DParticle.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _3DPARTICLE_H

#define _3DPARTICLE_H//��d�C���N���[�h�h�~

#include "Object_billboard.h"
#include "d3dx9.h"//�`�ʏ����Ɏg��
#include "main.h"

//

class CObject3DParticle : public CObjectBillBoard
{
public:

//	static const int EX_WIDE = 150;
//	static const int EX_HEIGHT = 150;

	const int START_LIFE = 15;
//	const int DIVISION_NUMBER = 8;	//�e�N�X�`��������


//	static const int STANPLIFE = 2 * 60;
	static const int  PRINTSIZE_X = 40;
	static const int  PRINTSIZE_Z = 20;


	CObject3DParticle(int nPriority = CObject::LAYERINDEX_3DPARTICLE);//�R���X�g���N�^
	~CObject3DParticle() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObject3DParticle* Create(D3DXVECTOR3 Pos, D3DXCOLOR col);//object����

	void SetPos_Rot(D3DXVECTOR3 Pos);

	//���_�i�[
	void InputpVtx()override;

	//�F�ύX
	void SetCOL(D3DXCOLOR col);

private:

	int m_nLife;//�����ŏ���

	D3DXCOLOR m_col=D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

//	int m_nPatternAnim;//����

//	int m_nDelay;
};

#endif