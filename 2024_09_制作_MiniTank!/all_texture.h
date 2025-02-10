//=========================================================
//
//object�����Ŏg���e�N�X�`���Ǘ��\����[all_texture.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _ALLTEXTURE_H
#define _ALLTEXTURE_H//��d�C���N���[�h�h�~

#include"main.h"
#include <d3d9.h>
#include "object.h"

//�e�N�X�`���Ǘ��N���X
class CAllTexture
{
public:
	CAllTexture();
	~CAllTexture();

	//�v���g�^�C�v�錾
	void Init();
	void Uninit();

	void Unload();//�e�N�X�`���j��
	int Regist(const char* pTextureName, LPDIRECT3DDEVICE9 pDevice);//�e�N�X�`���o�^

	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);//�e�N�X�`��

private:
	static const int m_nMaxTexture = 100;				//�e�N�X�`������
	LPDIRECT3DTEXTURE9 m_pTexture[m_nMaxTexture] = {};	//�e�N�X�`���i�[
	char* m_pFilePass[m_nMaxTexture] = {};				// �t�@�C���p�X
	int m_nNumAll = 0;									//�e�N�X�`����
};

#endif // !_TEXT_H_