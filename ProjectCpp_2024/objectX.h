//=========================================================
//
// objectX.cpp�Ŏg���֐�[objectX.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _OBJECTX_H

#define _OBJECTX_H//��d�C���N���[�h�h�~

#include "object.h"
#include "d3dx9.h"//�`�ʏ����Ɏg��
#include "main.h"
//
class CObjectX : public CObject
{
public:

	static const int MAX_TEXTURE_XFILE = 50;

	CObjectX(int nPriority = CObject::LAYERINDEX_OBJECTX);//�R���X�g���N�^
	~CObjectX() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;


	static CObjectX* Create();//object����

	void SetXfireData(LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD dwNumMat);//Xfail��ǂ񂾃f�[�^�i�[

	void SizeMagChangebool(bool bChange);//�T�C�Y�ϓ��̗L��
	void SetSizeMag(D3DXVECTOR3 SizeMag);//�{��
	
	DATA GetDATA();//��b���擾
	void SetDATA(DATA data);//��b���ݒ�

	void BindTexture(LPDIRECT3DTEXTURE9 pTex,int Index);//�e�N�X�`���ݒ�

	//���f���p�[�c��
	void ChangeModelPartsbool(bool parts);

	//���f���̂Ƃ��g�p�̃}�g���b�N�X�i�[
	void SetModelMtxWorld(D3DXMATRIX mtx);


	void SetColorChangeBool(bool ChangeColorBool);
	void SetChangeColor(D3DXCOLOR ChangeCol);



	void ChengeStageTex(bool Change);



private:			  

	DATA m_Data;
	D3DXMATRIX m_mtxWorld;
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE_XFILE];//�e�N�X�`��


	LPD3DXMESH m_pMesh;//Mesh�|�C���^
	LPD3DXBUFFER m_pBuffMat;//�}�e���A���ւ̃|�C���^
	DWORD m_dwNumMat;//�}�e���A���̐�

	D3DXVECTOR3 m_SizeMag;//�{���i�[(1.0������)
	bool m_bMagChange;//�{���ϓ�

	bool m_bModelParts;//���f���p�[�c��
	D3DXMATRIX m_ModelmtxWorld;//���f���p�[�c�̂Ƃ��̃}�g���b�N�X

	bool m_ChangeColorBool;//�F�ς�bool
	D3DXCOLOR m_ChangeCol;//�ς���F


	D3DXCOLOR m_OriginalColor;
	bool bFast = false;//�ŏ��̈��̂�

	bool m_bStageTexChange = false;
};

#endif