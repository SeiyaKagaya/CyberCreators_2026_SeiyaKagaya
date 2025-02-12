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

class CLockOnUI : public CObjectBillBoard
{
public:
	const float  PRINTSIZE = 130.0f;//���_�܂ł̋���

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

	void SetPos(D3DXVECTOR3 Pos);//���W�i�[
	
	void SetCol(D3DXCOLOR col) { m_col = col; };//�F�i�[

private:

	D3DXVECTOR3 m_Pos = {};

	D3DXCOLOR m_col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.95f);

	bool m_bDrawOk = false;//�`��\��
};

#endif