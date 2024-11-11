//============================================================================================
//
//���C�g���Ǘ����鏈��[light.cpp]
// Author seiya kagaya
//
//============================================================================================
#include "light.h"
#include "renderer.h"
#include "manager.h"


//=============================
//�R���X�g���N�^
//=============================
CLight::CLight()
{
	for (int nCntLIght = 0; nCntLIght < LIGHTNUM; nCntLIght++)
	{
		//���C�g�����N���A����
		ZeroMemory(&m_aLight[nCntLIght], sizeof(D3DLIGHT9));
	}
}
//=============================
//�f�X�g���N�^
//=============================
CLight::~CLight()
{
}
//=============================
//���C�g����������
//=============================
HRESULT CLight::Init(void)
{
	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	pRenderer = pManager->GetRenderer();

	LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

//	D3DXVECTOR3 vecDir;	//�ݒ�p�����x�N�g��

	for (int nCntLIght = 0; nCntLIght < LIGHTNUM; nCntLIght++)
	{
		//���C�g�����N���A����
		ZeroMemory(&m_aLight[nCntLIght], sizeof(D3DLIGHT9));

		//���C�g�̎�ނ�ݒ�
		m_aLight[nCntLIght].Type = D3DLIGHT_DIRECTIONAL;

		//���C�g�̊g�U����ݒ�
		m_aLight[nCntLIght].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);


		if (nCntLIght == 0)
		{
			//���C�g�̕�����ݒ�
			m_VecDir[nCntLIght] = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
		}
		else if (nCntLIght == 1)
		{
			//���C�g�̕�����ݒ�
			m_VecDir[nCntLIght] = D3DXVECTOR3(0.4f, 0.8f, 0.4f);
		}
		else if (nCntLIght == 2)
		{
			//���C�g�̕�����ݒ�
			m_VecDir[nCntLIght] = D3DXVECTOR3(-0.2f, -0.8f, -0.4f);
		}

		D3DXVec3Normalize(&m_VecDir[nCntLIght], &m_VecDir[nCntLIght]);//�x�N�g���𐳋K������

		m_aLight[nCntLIght].Direction = m_VecDir[nCntLIght];


		//���C�g�̐ݒ������
		EscDevice->SetLight(nCntLIght, &m_aLight[nCntLIght]);

		//���C�g��L��������
		EscDevice->LightEnable(nCntLIght, TRUE);
	}


	return S_OK;
}
//=============================
//���C�g�I������
//=============================
void CLight::Uninit(void)
{
}
//=============================
//���C�g�X�V����
//=============================
void CLight::Update(void)
{
}

int CLight::GetlightNum()
{
	return LIGHTNUM;
}

D3DXVECTOR3 CLight::GetLightVec(int LightNum)
{
	return m_VecDir[LightNum];
}
