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

class CObjectLINEUI : public CObjectBillBoard
{
public:
	static const int  PRINTSIZE_X = 20;//�T�C�Y
	static const int  PRINTSIZE_Z = 20;
	static const int LIFE = 3;		   //����
	static const int ADD_CNT = 20;	   //���Z��
	
	CObjectLINEUI(int nPriority = CObject::LAYERINDEX_LINEUI);//�R���X�g���N�^
	~CObjectLINEUI() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectLINEUI* Create(D3DXVECTOR3 Pos);//object����

	//Pos�i�[
	void SetPos(D3DXVECTOR3 Pos);

	//���_�i�[
	void InputpVtx()override;
private:

	D3DXVECTOR3 m_Pos = {};

	D3DXCOLOR m_col = D3DXCOLOR(0.0f,0.0f, 1.0f, 1.0f);

	int m_nLife = LIFE;
};

#endif