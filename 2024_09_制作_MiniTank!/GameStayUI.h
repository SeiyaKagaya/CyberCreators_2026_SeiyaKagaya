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

class CStayUI 
{
public:
	static const int TEXNUM = 2;
	CStayUI();//�R���X�g���N�^
	~CStayUI() ;//�f�X�g���N�^
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	static CStayUI* Create();//object����

private:

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff[TEXNUM] = {};//���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture[TEXNUM] = {};		//�e�N�X�`��
	int m_nTexIdx[TEXNUM] = {};					  	//�e�N�X�`��ID
	D3DXVECTOR3 m_Pos[TEXNUM] = {};			    	//���W
};

#endif