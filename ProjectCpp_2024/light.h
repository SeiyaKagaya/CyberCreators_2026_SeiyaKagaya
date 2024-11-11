//=========================================================
//
//���C�g�֌W�g���錾�Ȃ�[light.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _LIGHT_H_

#define _LIGHT_H_//��d�C���N���[�h�h�~

#include"main.h"



class CLight
{
public:
	CLight();
	~CLight();

	static const int LIGHTNUM = 3;//���C�g�̐�

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	static int GetlightNum();
	D3DXVECTOR3 GetLightVec(int LightNum);


private:

	D3DLIGHT9 m_aLight[LIGHTNUM];//LIGHT�\����
	D3DXVECTOR3 m_VecDir[LIGHTNUM];
};



#endif
