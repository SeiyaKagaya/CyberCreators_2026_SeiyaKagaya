//=========================================================
//
// ReflectEffect�Ŏg���֐�[ReflectEffect.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _REFLECTEFFECT_H
#define _REFLECTEFFECT_H//��d�C���N���[�h�h�~

#include "Object_billboard.h"
#include "d3dx9.h"//�`�ʏ����Ɏg��
#include "main.h"



class CObjectReflectEffect : public CObjectBillBoard
{
public:
	static const int  PRINTSIZE_X = 120;//�T�C�Y
	static const int  PRINTSIZE_Z = 120;
	static const int DIVISION_NUMBER = 30;		//�e�N�X�`��������

	CObjectReflectEffect(int nPriority = CObject::LAYERINDEX_ReflectEffect);//�R���X�g���N�^
	~CObjectReflectEffect() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectReflectEffect* Create(D3DXVECTOR3 Pos);//object����

	//POS�i�[
	void SetPos(D3DXVECTOR3 Pos);

	//���_�i�[
	void InputpVtx()override;

private:

	int m_nPatternAnim = 0;//����
};

#endif