//=========================================================
//
// Game_UI.cpp�Ŏg���֐�[Game_UI.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _GAMEUI_H
#define _GAMEUI_H//��d�C���N���[�h�h�~

#include "object.h"
#include "d3dx9.h"//�`�ʏ����Ɏg��
#include "main.h"
//
class CGameUI : public CObject
{
public:
	static const int TEXNUM = 15;
	CGameUI(int nPriority = CObject::LAYERINDEX_GAMEUI);//�R���X�g���N�^
	~CGameUI() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CGameUI* Create();//object����

private:

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff[TEXNUM] = {};	//���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture[TEXNUM] = {};			//�e�N�X�`��
	int m_nTexIdx[TEXNUM] = {};							//�e�N�X�`��ID
	D3DXVECTOR3 m_Pos[TEXNUM] = {};						//���W
};

#endif