//=========================================================
//
// LockOnUIMain�Ŏg���֐�[LockOnUIMain.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _LOCKONUIMAIN_H
#define _LOCKONUIMAIN_H//��d�C���N���[�h�h�~

#include "Object_billboard.h"
#include "d3dx9.h"//�`�ʏ����Ɏg��
#include "main.h"

class CLockOnUIMain : public CObjectBillBoard
{
public:
	const float  PRINTSIZE = 80.0f;
	
	CLockOnUIMain(int nPriority = CObject::LAYERINDEX_LOCKONUIMAIN);//�R���X�g���N�^
	~CLockOnUIMain() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CLockOnUIMain* Create();//object����

	//���_�i�[
	void InputpVtx()override;

	//�`��\��
	void SetDrawOk(bool bSet) { m_bDrawOk = bSet; };
	bool bGetDrawOk() { return m_bDrawOk; };

	void SetPos(D3DXVECTOR3 Pos);//���W�i�[

	void SetCol(D3DXCOLOR col) { m_col = col; };//�F�i�[

private:

	D3DXVECTOR3 m_Pos = {};

	D3DXCOLOR m_col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 0.95f);

	bool m_bDrawOk = false;//�`��\��
};

#endif