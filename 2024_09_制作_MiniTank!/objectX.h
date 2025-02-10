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

	void ChangeModelPartsbool(bool parts);	//���f���p�[�c��

	void SetModelMtxWorld(D3DXMATRIX mtx);	//���f���̂Ƃ��g�p�̃}�g���b�N�X�i�[

	void SetColorChangeBool(bool ChangeColorBool);	//�F�ύX���邩

	void SetChangeColor(D3DXCOLOR ChangeCol);	//�F�ύX�J���[

private:			  

	DATA m_Data = DataInit();
	D3DXMATRIX m_mtxWorld = {};							//�}�g���b�N�X
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE_XFILE];	//�e�N�X�`��
	LPD3DXMESH m_pMesh = nullptr;						//Mesh�|�C���^
	LPD3DXBUFFER m_pBuffMat = nullptr;					//�}�e���A���ւ̃|�C���^
	DWORD m_dwNumMat = {};								//�}�e���A���̐�
	D3DXVECTOR3 m_SizeMag = {};							//�{���i�[(1.0������)
	D3DXMATRIX m_ModelmtxWorld = {};					//���f���p�[�c�̂Ƃ��̃}�g���b�N�X
	D3DXCOLOR m_ChangeCol = {};							//�ς���F
	D3DXCOLOR m_OriginalColor = {};						//�I���W�i���J���[
	bool m_bMagChange = false;							//�{���ϓ�
	bool m_ChangeColorBool = false;						//�F�ς�bool
	bool m_bModelParts = false;							//���f���p�[�c��
	bool bFast = false;									//�ŏ��̈��̂�
};

#endif