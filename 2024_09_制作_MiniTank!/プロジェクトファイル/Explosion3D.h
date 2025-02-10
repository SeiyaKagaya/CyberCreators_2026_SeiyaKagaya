//=========================================================
//
// objectX.cpp�Ŏg���֐�[objectX.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _EXPLOSION3D_H
#define _EXPLOSION3D_H//��d�C���N���[�h�h�~

#include "object.h"
#include "d3dx9.h"//�`�ʏ����Ɏg��
#include "main.h"
//
class Explosion3D : public CObject
{
public:

	static const int ANIMNUM = 60;//�A�j���[�V����������

	Explosion3D(int nPriority = CObject::LAYERINDEX_EXPLOSION3D);//�R���X�g���N�^
	~Explosion3D() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static Explosion3D* Create(D3DXVECTOR3 Pos);//object����

	void SizeMagChangebool(bool bChange);//�T�C�Y�ϓ��̗L��
	void SetSizeMag(D3DXVECTOR3 SizeMag);//�{��
	void SetPos(D3DXVECTOR3 pos);

private:

	DATA m_Data = DataInit();
	D3DXMATRIX m_mtxWorld = {};
	LPD3DXMESH m_pMesh = nullptr;					//Mesh�|�C���^
	LPD3DXBUFFER m_pBuffMat = nullptr;				//�}�e���A���ւ̃|�C���^
	DWORD m_dwNumMat = {};							//�}�e���A���̐�
	D3DXCOLOR m_ChangeCol = {};						//�ς���F
	D3DXCOLOR m_OriginalColor = {};					//�I���W�i���J���[�i�[
	D3DXVECTOR3 m_SetSize = {};						//�g�嗦�p�T�C�Y�i�[
	D3DXVECTOR3 m_SizeMag = {};						//�{���i�[(1.0������)
	LPDIRECT3DTEXTURE9	m_ESCpTexture = nullptr;
	bool m_bMagChange = false;						//�{���ϓ�
	bool m_ChangeColorBool = false;					//�F�ς�bool
	bool bFast = false;								//�ŏ��̈��̂�
	float m_texOffsetX = 0.0f;						//�e�N�X�`���ʒu
	float m_texOffsetY = 0.0f;
	int m_nLife = 0;								//����
	int m_nCnt = 0;									//�J�E���^�[
};

#endif