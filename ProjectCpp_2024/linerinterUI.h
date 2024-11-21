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

//

class CObjectLINEUI : public CObjectBillBoard
{
public:

	static const int EX_WIDE = 150;
	static const int EX_HEIGHT = 150;

	const int START_LIFE = 120;
	const int DIVISION_NUMBER = 15;	//�e�N�X�`��������


//	static const int STANPLIFE = 2 * 60;
	static const int  PRINTSIZE_X = 20;
	static const int  PRINTSIZE_Z = 20;


	CObjectLINEUI(int nPriority = CObject::LAYERINDEX_LINEUI);//�R���X�g���N�^
	~CObjectLINEUI() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectLINEUI* Create(D3DXVECTOR3 Pos);//object����

	void SetPos_Rot(D3DXVECTOR3 Pos);

	//���_�i�[
	void InputpVtx()override;


private:

	D3DXVECTOR3 m_Pos = {};

	D3DXCOLOR m_col = D3DXCOLOR(0.0f,1.0f, 1.0f, 1.0f);

	int m_nLife = 3;
};

#endif