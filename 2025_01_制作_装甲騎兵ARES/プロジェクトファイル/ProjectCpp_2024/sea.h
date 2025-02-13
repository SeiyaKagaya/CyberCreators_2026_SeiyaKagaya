//=========================================================
//
// tankfootprint�Ŏg���֐�[tankfootprint.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _SEA_H
#define _SEA_H//��d�C���N���[�h�h�~

#include "object3D.h"
#include "d3dx9.h"//�`�ʏ����Ɏg��
#include "main.h"

class CSea : public CObject3D
{
public:
	const float PRINTSIZE = 60000.0f;	//���_�܂ł̒���
	const float TEXMOVE_X1 = 0.00004f;	//�e�N�X�`����move�l
	const float TEXMOVE_Y1 = 0.00002f;
	const float TEXMOVE_X2 = 0.0002f;
	const float TEXMOVE_Y2 = 0.0009f;

	CSea(int nPriority = CObject::LAYERINDEX_SEA);//�R���X�g���N�^
	~CSea() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CSea* Create(D3DXVECTOR3 Pos, D3DXVECTOR3 rot, float rgbA);//object����

	//�ʒu�Ɖ�]���i�[
	void SetPos_Rot(D3DXVECTOR3 Pos, D3DXVECTOR3 rot);

	//���_�i�[
	void InputpVtx()override;

	//�A���t�@�l���i�[
	void SetrgbA(float rgbA) { m_rgbA = rgbA; };

private:

	//�e�N�X�`���̈ʒu�p
	float m_texOffsetX = 0.0f;
	float m_texOffsetY = 0.0f;
	float m_rgbA = 0.0f;//�A���t�@�l�i�[
};

#endif