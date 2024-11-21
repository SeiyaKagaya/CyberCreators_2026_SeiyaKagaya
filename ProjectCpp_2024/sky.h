//=========================================================
//
// objectX.cpp�Ŏg���֐�[objectX.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _SKY3D_H

#define _SKY3D_H//��d�C���N���[�h�h�~

#include "object.h"
#include "d3dx9.h"//�`�ʏ����Ɏg��
#include "main.h"
//
class Sky3D : public CObject
{
public:

	static const int ANIMNUM = 36000;
	static const int MAX_TEXTURE_XFILE = 50;

	Sky3D(int nPriority = CObject::LAYERINDEX_SKY);//�R���X�g���N�^
	~Sky3D() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;


	static Sky3D* Create(D3DXVECTOR3 Pos);//object����

	void SizeMagChangebool(bool bChange);//�T�C�Y�ϓ��̗L��
	void SetSizeMag(D3DXVECTOR3 SizeMag);//�{��
	void SetPos(D3DXVECTOR3 pos);



private:

	DATA m_Data;
	D3DXMATRIX m_mtxWorld;
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE_XFILE];//�e�N�X�`��


	LPD3DXMESH m_pMesh;//Mesh�|�C���^
	LPD3DXBUFFER m_pBuffMat;//�}�e���A���ւ̃|�C���^
	DWORD m_dwNumMat;//�}�e���A���̐�





	D3DXVECTOR3 m_SizeMag;//�{���i�[(1.0������)
	bool m_bMagChange;//�{���ϓ�


	bool m_ChangeColorBool;//�F�ς�bool
	D3DXCOLOR m_ChangeCol;//�ς���F


	D3DXCOLOR m_OriginalColor;
	bool bFast = false;//�ŏ��̈��̂�


//	int m_nLife;


	//�e�N�X�`���ǂݍ���
	LPDIRECT3DTEXTURE9	m_ESCpTexture=nullptr;

	float m_texOffsetX = 0.0f;
	float m_texOffsetY = 0.0f;

	int m_nCnt=0;

	D3DXVECTOR3 m_SetSize;
};

#endif