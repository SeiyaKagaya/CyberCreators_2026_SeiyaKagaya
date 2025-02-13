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
	const float TEX_MOVE = 0.0008f;//�e�N�X�`���ړ���
	const float SIZE_1 = 9900.0f;  //�T�C�Y
	const float SIZE_2 = 13300.0f;

	CObject3D(int nPriority = CObject::LAYERINDEX_OBJECT3D);//�R���X�g���N�^
	~CObject3D() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObject3D* Create();//object����

	void BindTexture(LPDIRECT3DTEXTURE9 pTex);//�e�N�X�`���ݒ�
	LPDIRECT3DTEXTURE9 GetTexture();//�e�N�X�`���擾

	void BindVtxBuffer(LPDIRECT3DVERTEXBUFFER9 pVtx);//�o�b�t�@�ݒ�

	LPDIRECT3DVERTEXBUFFER9 GetpVtxBuffer();//�o�b�t�@�擾

	DATA GetDATA();//��b���擾

	void SetDATA(DATA data);//��b���ݒ�

	void ChangeRGBA(D3DCOLOR col);//�F

	void ChengeAddDrawMode(bool bSet);//�`�惂�[�h

	void SetpVtx(VERTEX_3D pVtx[BASE_INDEX]);//���_�i�[

	void SetSubtract(bool bSet) { m_bSubtract = bSet; };//���Y�������ǂ���

	//���_�i�[
	virtual	void InputpVtx();

private:

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = nullptr;//���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture = nullptr;//�e�N�X�`��

	DATA m_Data = CObject::DataInit();

	//�e�N�X�`���Ⓒ�_���W�Ȃǂ̕ێ�
	VERTEX_3D m_pVtx[BASE_INDEX] = {};

	bool m_AddDrawMode = false;//���Z�������[�h

	//�e�N�X�`�����W
	float m_texOffsetX = 0.0f;
	float m_texOffsetY = 0.0f;

	D3DXMATRIX m_mtxWorld = {};

	bool m_bSubtract = false;//���Y�������[�h
};

#endif