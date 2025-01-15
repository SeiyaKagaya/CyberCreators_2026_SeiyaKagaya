//=========================================================
//
// object2D.cpp�Ŏg���֐�[object2D.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _OBJECT2D_H

#define _OBJECT2D_H//��d�C���N���[�h�h�~

#include "object.h"
#include "d3dx9.h"//�`�ʏ����Ɏg��
#include "main.h"
//
class CObject2D: public CObject
{
public:
	
	CObject2D(int nPriority=CObject::LAYERINDEX_OBJECT2D);//�R���X�g���N�^
	 ~CObject2D() override ;//�f�X�g���N�^
	 HRESULT Init()override;
	 void Uninit()override;
	 void Update()override;
	 void Draw()override;

	static CObject2D *Create();//object����

	void BindTexture(LPDIRECT3DTEXTURE9 pTex);//�e�N�X�`���ݒ�
	LPDIRECT3DTEXTURE9 GetTexture();//�e�N�X�`���擾
	
	void BindVtxBuffer(LPDIRECT3DVERTEXBUFFER9 pVtx);//�o�b�t�@�ݒ�

	LPDIRECT3DVERTEXBUFFER9 GetpVtxBuffer();//�o�b�t�@�擾

	DATA GetDATA();//��b���擾
	void SetDATA(DATA data);//��b���ݒ�


	void ChangeRGBA(D3DCOLOR col);

	void ChengeAddDrawMode(bool bSet);

	//���_�Ȃ�
	void SetpVtx(VERTEX_2D pVtx[BASE_INDEX]);

	//���_�i�[
	virtual	void InputpVtx();

	//�e�N�X�`��id�i�[
	void SetTexIndex(int TexIdx);

private:
//protected:

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;//���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture;//�e�N�X�`��

	int m_nTexIdx;

	DATA m_Data;

	//�e�N�X�`���Ⓒ�_���W�Ȃǂ̕ێ�
	VERTEX_2D m_pVtx[BASE_INDEX];

	bool m_AddDrawMode;//���Z�������[�h

};

#endif