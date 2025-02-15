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

	static const int LIGHTNUM = 3;//���C�g�̐�
	const D3DXVECTOR3 LIGHT_POS[LIGHTNUM] =
	{
		D3DXVECTOR3(0.2f,-0.8f,0.4f),
		D3DXVECTOR3(0.4f,0.8f,0.4f),
		D3DXVECTOR3(-0.2f,-0.8f,-0.4f),
	};

	CLight();
	~CLight();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	static int GetlightNum();				//���C�g�̐��擾
	D3DXVECTOR3 GetLightVec(int LightNum);  //���C�g�̃x�N�g�����擾
private:

	D3DLIGHT9 m_aLight[LIGHTNUM] = {};		//LIGHT�\����
	D3DXVECTOR3 m_VecDir[LIGHTNUM] = {};	//�x�N�g��
};

#endif
