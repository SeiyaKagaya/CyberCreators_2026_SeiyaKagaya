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
//


class CObject3DParticle;

class CObject3DParticleAll : public CObjectX
{
public:

	static const int MAXPARTICLEALL = 640;

	CObject3DParticleAll(int nPriority = CObject::LAYERINDEX_3DPARTICLE_MNG);//�R���X�g���N�^
	~CObject3DParticleAll() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	//void Update()override;
	//void Draw()override;
	static CObject3DParticleAll* Create();//�I�u�W�F�N�g����

	void ReleaseAllParticle();

	
	//�K�萔������������
	void AllClean();

	CObject3DParticle* GetParticleData(int nNum);

	//���łɐ�������Ă�����̂�bUse��true�ɂ��ĉғ�������
	void SetParticle(D3DXVECTOR3 Pos, D3DXCOLOR col,int nLife,float Size);



private:

	//��Ɋm�ۂ��A��
	CObject3DParticle* m_NewParticle[MAXPARTICLEALL];


};



















class CObject3DParticle : public CObjectBillBoard
{
public:

	//	static const int EX_WIDE = 150;
	//	static const int EX_HEIGHT = 150;

	const int START_LIFE = 1;
	//	const int DIVISION_NUMBER = 8;	//�e�N�X�`��������


	//	static const int STANPLIFE = 2 * 60;
	static const int  PRINTSIZE_X = 30;
	static const int  PRINTSIZE_Z = 15;


	CObject3DParticle(int nPriority = CObject::LAYERINDEX_3DPARTICLE);//�R���X�g���N�^
	~CObject3DParticle() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObject3DParticle* Create(/*D3DXVECTOR3 Pos, D3DXCOLOR col*/);//object����

	void SetPos(D3DXVECTOR3 Pos);

	//���_�i�[
	void InputpVtx()override;

	//�F�ύX
	void SetCOL(D3DXCOLOR col);

	void SetbUse(bool bUse) { m_bUse = bUse; if (m_bUse == true) { m_nLife = 3; }; };

	bool GetbUse() { return m_bUse; };

	void SetLife(int nLife) { m_nLife = nLife; };
	void SetUse(bool Set) { m_bUse = Set; };

	void SetSize(float Size) { m_Size = Size; };

private:

	int m_nLife=0;//�����ŏ���

	D3DXCOLOR m_col=D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

//	int m_nPatternAnim;//����

//	int m_nDelay;

	bool m_bUse = false;
	float m_Size = 0.0f;
};

#endif