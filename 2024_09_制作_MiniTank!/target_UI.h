//=========================================================
//
// targetui�Ŏg���֐�[targetui.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _TARGETUI_H
#define _TARGETUI_H//��d�C���N���[�h�h�~

#include "Object_billboard.h"
#include "d3dx9.h"//�`�ʏ����Ɏg��
#include "main.h"

class CObjectTargetUI : public CObjectBillBoard
{
public:

	static const int  PRINTSIZE_X = 70;//�T�C�Y
	static const int  PRINTSIZE_Z = 70;
	static const int  START_LIFE = 3;  //����
	static const int ADD_CNT = 20;	   //���Z��

	CObjectTargetUI(int nPriority = CObject::LAYERINDEX_TARGETUI);//�R���X�g���N�^
	~CObjectTargetUI() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectTargetUI* Create(D3DXVECTOR3 Pos);//object����

	//���W�i�[
	void SetPos(D3DXVECTOR3 Pos);

	//���_�i�[
	void InputpVtx()override;

private:

	D3DXVECTOR3 m_Pos = {};
	D3DXCOLOR m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	int m_nLife = START_LIFE;
};

#endif