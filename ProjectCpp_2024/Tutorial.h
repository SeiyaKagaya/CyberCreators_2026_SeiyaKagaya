//=========================================================
//
// Tutorial.cpp�Ŏg���֐�[Tutorial.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _TUTORIAL_H

#define _TUTORIAL_H//��d�C���N���[�h�h�~

#include "object.h"
#include "d3dx9.h"//�`�ʏ����Ɏg��
#include "main.h"
//
class CTutorialUI //: public CObject
{
public:
	static const int TEXNUM = 3;
	CTutorialUI(/*int nPriority = CObject::LAYERINDEX_OBJECT2D*/);//�R���X�g���N�^
	~CTutorialUI() /*override*/;//�f�X�g���N�^
	HRESULT Init()/*override*/;
	void Uninit()/*override*/;
	void Update()/*override*/;
	void Draw()/*override*/;

	static CTutorialUI* Create();//object����

	void AddSelectNum(int addnum);
	void DirectSetNum(int Num);

	int GetSelectNum();

private:

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff[TEXNUM];//���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture[TEXNUM];//�e�N�X�`��
	int m_nTexIdx[TEXNUM];

	D3DXVECTOR3 m_Pos[TEXNUM];

	//�e�N�X�`���Ⓒ�_���W�Ȃǂ̕ێ�
//	VERTEX_2D m_pVtx[BASE_INDEX];

//	bool m_AddDrawMode;//���Z�������[�h

	int m_SelectNum = 0;

	bool m_bPhase2 = false;
};

#endif