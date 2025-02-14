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

	static const int STANPLIFE = 480;	//����
	static const int  PRINTSIZE_X = 85;	//�T�C�Y
	static const int  PRINTSIZE_Y = 10;
	static const int  PRINTSIZE_Z = 40;
	
	const float PRINT_MOVE_X = 13.0f;	//Y�����ɃY
	const float COL_A = 0.55f;			//rgba�J���[A


	CObjectFootPrint(int nPriority = CObject::LAYERINDEX_FOOTPRINT);//�R���X�g���N�^
	~CObjectFootPrint() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectFootPrint* Create(D3DXVECTOR3 Pos, D3DXVECTOR3 rot);//object����

	void SetPos_Rot(D3DXVECTOR3 Pos,D3DXVECTOR3 rot);

	//���_�i�[
	void InputpVtx()override;

private:
	
	int m_nLife = 0;//����
};

#endif