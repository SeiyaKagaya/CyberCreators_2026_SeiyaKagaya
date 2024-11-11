//=========================================================
//
// GameStayUI.cpp�Ŏg���֐�[GameStayUI.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _stayUI_H

#define _stayUI_H//��d�C���N���[�h�h�~

#include "object.h"
#include "d3dx9.h"//�`�ʏ����Ɏg��
#include "main.h"
//
class CStayUI //: public CObject
{
public:
	static const int TEXNUM = 2;
	CStayUI(/*int nPriority = CObject::LAYERINDEX_RESULTUI*/);//�R���X�g���N�^
	~CStayUI() /*override*/;//�f�X�g���N�^
	HRESULT Init()/*override*/;
	void Uninit()/*override*/;
	void Update()/*override*/;
	void Draw()/*override*/;

	static CStayUI* Create();//object����


private:

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff[TEXNUM];//���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture[TEXNUM];//�e�N�X�`��
	int m_nTexIdx[TEXNUM];

	D3DXVECTOR3 m_Pos[TEXNUM];


};

#endif