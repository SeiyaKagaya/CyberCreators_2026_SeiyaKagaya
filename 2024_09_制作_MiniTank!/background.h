//=========================================================
//
// background.cpp�Ŏg���֐�[background.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _BACKGROUND_H
#define _BACKGROUND_H//��d�C���N���[�h�h�~

#include "object.h"
#include "object2D.h"

#include <Windows.h>
#include "d3dx9.h"//�`�ʏ����Ɏg��
//
class CBG : public CObject
{
public:

	CBG();//�R���X�g���N�^
	~CBG() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CBG* Create();//�I�u�W�F�N�g����
private:

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = nullptr;//���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture = nullptr;//�e�N�X�`��
};

#endif