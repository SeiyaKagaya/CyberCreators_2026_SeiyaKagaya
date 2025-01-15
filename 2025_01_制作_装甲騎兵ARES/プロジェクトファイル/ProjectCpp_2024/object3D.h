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
//
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

	void BindTexture(LPDIRECT3DTEXTURE9 pTex);//�e�N�X�`���ݒ�
	LPDIRECT3DTEXTURE9 GetTexture();//�e�N�X�`���擾

	void BindVtxBuffer(LPDIRECT3DVERTEXBUFFER9 pVtx);//�o�b�t�@�ݒ�

	LPDIRECT3DVERTEXBUFFER9 GetpVtxBuffer();//�o�b�t�@�擾

	DATA GetDATA();//��b���擾
	void SetDATA(DATA data);//��b���ݒ�


	void ChangeRGBA(D3DCOLOR col);//�F

	void ChengeAddDrawMode(bool bSet);//�`�惂�[�h

	//���_�Ȃ�
	void SetpVtx(VERTEX_3D pVtx[BASE_INDEX]);

	//���_�i�[
	virtual	void InputpVtx();




//	static HRESULT Load();
//	static void UnLoad();;

private:
	//protected:

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;//���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture;//�e�N�X�`��

	DATA m_Data;



	//�e�N�X�`���Ⓒ�_���W�Ȃǂ̕ێ�
	VERTEX_3D m_pVtx[BASE_INDEX];

	bool m_AddDrawMode;//���Z�������[�h
	float m_texOffsetX = 0.0f;
	float m_texOffsetY = 0.0f;


	D3DXMATRIX m_mtxWorld;
};

#endif