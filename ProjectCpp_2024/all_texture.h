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

	////objectPass�Ǘ��\����
	//typedef struct
	//{
	//	LPDIRECT3DTEXTURE9 m_pTexture;//�e�N�X�`���i�[
	//	const char* pFilePass;	// �t�@�C���p�X
	//	CObject::OBJECTTYPE objectType;	// object�l�[��
	//} TEXTUREINFO;

	//�v���g�^�C�v�錾
	void Init();
	void Uninit();

	void Unload();//�e�N�X�`���j��
	int Regist(const char* pTextureName, LPDIRECT3DDEVICE9 pDevice);//�e�N�X�`���o�^

	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);//�e�N�X�`��

//	static LPDIRECT3DTEXTURE9 GetTexture(CObject::OBJECTTYPE ObjectType, LPDIRECT3DDEVICE9 pDevice);//�e�N�X�`��

private:
	static const int m_nMaxTexture = 150;//�e�N�X�`������
	LPDIRECT3DTEXTURE9 m_pTexture[m_nMaxTexture];//�e�N�X�`���i�[
	char* m_pFilePass[m_nMaxTexture];	// �t�@�C���p�X
	int m_nNumAll;//�e�N�X�`����

	//�p�X�Ǘ��\����
//	static 	TEXTUREINFO m_TextureInfo[CObject::OBJECT_MAX];
};

#endif // !_TEXT_H_