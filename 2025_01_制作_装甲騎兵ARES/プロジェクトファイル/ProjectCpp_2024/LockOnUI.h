//=========================================================
//
// LockOnUI�Ŏg���֐�[LockOnUI.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _LOCKONUI_H

#define _LOCKONUI_H//��d�C���N���[�h�h�~

#include "Object_billboard.h"
#include "d3dx9.h"//�`�ʏ����Ɏg��
#include "main.h"

//

class CLockOnUI : public CObjectBillBoard
{
public:

//	static const int EX_WIDE = 150;
//	static const int EX_HEIGHT = 150;

//	const int START_LIFE = 120;
//	const int DIVISION_NUMBER = 15;	//�e�N�X�`��������


//	static const int STANPLIFE = 2 * 60;
	static const int  PRINTSIZE = 130;
//	static const int  PRINTSIZE_Z = 130;


	CLockOnUI(int nPriority = CObject::LAYERINDEX_LOCKONUI);//�R���X�g���N�^
	~CLockOnUI() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CLockOnUI* Create();//object����



	//���_�i�[
	void InputpVtx()override;

	//�`��\��
	void SetDrawOk(bool bSet) { m_bDrawOk = bSet;};
	bool bGetDrawOk() { return m_bDrawOk; };

	void SetPos(D3DXVECTOR3 Pos);
	void SetCol(D3DXCOLOR col) { m_col = col; };

	void SetfSize(float fSetSize) { fSize = fSetSize; };

private:

	D3DXVECTOR3 m_Pos = {};

	D3DXCOLOR m_col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.95f);

	//int m_nLife = 6;
	bool m_bDrawOk = false;
	float fSize;;
};

#endif