//=========================================================
//
// 3DParticle�Ŏg���֐�[3DParticle.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _3DPARTICLE_H
#define _3DPARTICLE_H//��d�C���N���[�h�h�~

#include "Object_billboard.h"
#include "d3dx9.h"//�`�ʏ����Ɏg��
#include "main.h"
#include "object.h"

class CObject3DParticle;

class CObject3DParticleAll : public CObjectX
{
public:

	static const int MAXPARTICLEALL = 640;//�p�[�e�B�N���̑���

	CObject3DParticleAll(int nPriority = CObject::LAYERINDEX_3DPARTICLE_MNG);//�R���X�g���N�^
	~CObject3DParticleAll() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	//void Update()override;
	//void Draw()override;
	static CObject3DParticleAll* Create();//�I�u�W�F�N�g����

	void ReleaseAllParticle();//���ׂĂ������[�X

	//�K�萔������������
	void AllClean();

	CObject3DParticle* GetParticleData(int nNum);//�z��ԍ��̃p�[�e�B�N���̃|�C���^�擾

	//���łɐ�������Ă�����̂�bUse��true�ɂ��ĉғ�������
	void SetParticle(D3DXVECTOR3 Pos, D3DXCOLOR col,int nLife,float Size);

private:

	//��Ɋm�ۂ��A��
	CObject3DParticle* m_NewParticle[MAXPARTICLEALL];
};

//--------------------------------------------------------------------------------------------------------------------------------------------------

class CObject3DParticle : public CObjectBillBoard
{
public:

	CObject3DParticle(int nPriority = CObject::LAYERINDEX_3DPARTICLE);//�R���X�g���N�^
	~CObject3DParticle() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObject3DParticle* Create();//object����

	void SetPos(D3DXVECTOR3 Pos);//���W�i�[

	//���_�i�[
	void InputpVtx()override;

	//�F�ύX
	void SetCOL(D3DXCOLOR col);

	bool GetbUse() { return m_bUse; };//�g�p�����擾

	void SetLife(int nLife) { m_nLife = nLife; };//�̗͐ݒ�

	void SetUse(bool Set) { m_bUse = Set; };//�g�p��Ԃ��i�[

	void SetSize(float Size) { m_Size = Size; };//�T�C�Y�i�[

private:

	int m_nLife=0;//�����ŏ���

	D3DXCOLOR m_col=D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

	bool m_bUse = false;

	float m_Size = 0.0f;
};

#endif