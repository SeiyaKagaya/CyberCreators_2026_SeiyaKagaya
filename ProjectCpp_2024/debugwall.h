//=========================================================
//
// tankfootprint�Ŏg���֐�[tankfootprint.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _DEBUGWALL_H

#define _DEBUGWALL_H//��d�C���N���[�h�h�~

#include "object3D.h"
#include "d3dx9.h"//�`�ʏ����Ɏg��
#include "main.h"

//

class CDebugwall : public CObject3D
{
public:

	static const int  PRINTSIZE = 3300/2;
//	static const int  SETPOS

	CDebugwall(int nPriority = CObject::LAYERINDEX_DEBUGWALL);//�R���X�g���N�^
	~CDebugwall() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CDebugwall* Create(D3DXVECTOR3 Pos, D3DXVECTOR3 rot);//object����

	void SetPos_Rot(D3DXVECTOR3 Pos, D3DXVECTOR3 rot);

	//���_�i�[
	void InputpVtx()override;


private:

	
};

#endif