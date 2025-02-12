//=========================================================
//
// tankfootprint�Ŏg���֐�[tankfootprint.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _TANKFOOTPRINT_H
#define _TANKFOOTPRINT_H//��d�C���N���[�h�h�~

#include "object3D.h"
#include "d3dx9.h"//�`�ʏ����Ɏg��
#include "main.h"

class CObjectFootPrint : public CObject3D
{
public:

	static const int STANPLIFE = 480;//�̗�

	//���_�܂ł̋���
	static const int  PRINTSIZE_X= 85;
	static const int  PRINTSIZE_Z = 40;

	CObjectFootPrint(int nPriority = CObject::LAYERINDEX_FOOTPRINT);//�R���X�g���N�^
	~CObjectFootPrint() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectFootPrint* Create(D3DXVECTOR3 Pos, D3DXVECTOR3 rot);//object����

	void SetPos_Rot(D3DXVECTOR3 Pos,D3DXVECTOR3 rot);//���W�Ɗp�x���i�[

	//���_�i�[
	void InputpVtx()override;

private:
	
	int m_nLife = 0;//�����ŏ���
};

#endif