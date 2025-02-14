//=========================================================
//
// object3D.cpp�Ŏg���֐�[object3D.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _OBJECT3D_H
#define _OBJECT3D_H//��d�C���N���[�h�h�~

#include "object.h"
#include "d3dx9.h"//�`�ʏ����Ɏg��
#include "main.h"

class CObject3D : public CObject
{
public:

	CObject3D(int nPriority = CObject::LAYERINDEX_OBJECT3D);//�R���X�g���N�^
	~CObject3D() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObject3D* Create();//object����

	void BindTexture(LPDIRECT3DTEXTURE9 pTex);		 //�e�N�X�`���ݒ�
	LPDIRECT3DTEXTURE9 GetTexture();				 //�e�N�X�`���擾

	void BindVtxBuffer(LPDIRECT3DVERTEXBUFFER9 pVtx);//�o�b�t�@�ݒ�
	LPDIRECT3DVERTEXBUFFER9 GetpVtxBuffer();		 //�o�b�t�@�擾

	DATA GetDATA();									//��b���擾
	void SetDATA(DATA data);						//��b���ݒ�

	void ChangeRGBA(D3DCOLOR col);					//�F

	void ChengeAddDrawMode(bool bSet);				//�`�惂�[�h
	
	void SetpVtx(VERTEX_3D pVtx[BASE_INDEX]);		//���_�i�[

	virtual	void InputpVtx();						//���_�Z�b�g

private:

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = nullptr;//���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture = nullptr;	 //�e�N�X�`��
	DATA m_Data = DataInit();

	//�e�N�X�`���Ⓒ�_���W�Ȃǂ̕ێ�
	VERTEX_3D m_pVtx[BASE_INDEX] = {};

	bool m_AddDrawMode = false;//���Z�������[�h
	float m_texOffsetX = 0.0f; //�e�N�X�`���ʒu
	float m_texOffsetY = 0.0f;

	D3DXMATRIX m_mtxWorld = {};
};

#endif