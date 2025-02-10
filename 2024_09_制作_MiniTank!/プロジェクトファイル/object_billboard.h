//=========================================================
//
// object_billboard.cpp�Ŏg���֐�[object_billboard.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _OBJECTBILL_H
#define _OBJECTBILL_H//��d�C���N���[�h�h�~

#include "object.h"
#include "d3dx9.h"//�`�ʏ����Ɏg��
#include "main.h"

class CObjectBillBoard : public CObject
{
public:
	static const int SIZE = 1650;//�T�C�Y

	CObjectBillBoard(int nPriority = CObject::LAYERINDEX_BILLBOARD);//�R���X�g���N�^
	~CObjectBillBoard() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectBillBoard* Create();//object����

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

	//Z�o�b�t�@
	void SetZDrawDeth(bool bDraw);

private:

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = nullptr;//���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture = nullptr;//�e�N�X�`��
	DATA m_Data = DataInit();

	//�e�N�X�`���Ⓒ�_���W�Ȃǂ̕ێ�
	VERTEX_3D m_pVtx[BASE_INDEX] = {};

	bool m_AddDrawMode = false;//���Z�������[�h
	bool m_ZDethDrawMode = false;//Z�o�b�t�@�𖳌���

	D3DXMATRIX m_mtxWorld = {};
};
#endif