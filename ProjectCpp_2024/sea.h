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

//

class CSea : public CObject3D
{
public:

	static const int  PRINTSIZE = 3300 / 2;
	//	static const int  SETPOS

	static const int ANIMNUM = 1;
	static const int MAX_TEXTURE_XFILE = 50;

	CSea(int nPriority = CObject::LAYERINDEX_SEA);//�R���X�g���N�^
	~CSea() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CSea* Create(D3DXVECTOR3 Pos, D3DXVECTOR3 rot, float rgbA);//object����

	void SetPos_Rot(D3DXVECTOR3 Pos, D3DXVECTOR3 rot);

	//���_�i�[
	void InputpVtx()override;

	//�A���t�@�l���i�[
	void SetrgbA(float rgbA) { m_rgbA = rgbA; };

private:

	float m_texOffsetX = 0.0f;
	float m_texOffsetY = 0.0f;
	float m_rgbA = 0.0f;
///	int m_nCnt = 0;
};

#endif