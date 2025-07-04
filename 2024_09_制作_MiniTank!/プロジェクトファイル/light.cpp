//============================================================================================
//
//ライトを管理する処理[light.cpp]
// Author seiya kagaya
//
//============================================================================================
#include "light.h"
#include "renderer.h"
#include "manager.h"

//=============================
//コンストラクタ
//=============================
CLight::CLight()
{
	for (int nCntLIght = 0; nCntLIght < LIGHTNUM; nCntLIght++)
	{
		//ライト情報をクリアする
		ZeroMemory(&m_aLight[nCntLIght], sizeof(D3DLIGHT9));
	}
}

//=============================
//デストラクタ
//=============================
CLight::~CLight()
{
}

//=============================
//ライト初期化処理
//=============================
HRESULT CLight::Init(void)
{
	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	pRenderer = pManager->GetRenderer();

	LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();


	for (int nCntLIght = 0; nCntLIght < LIGHTNUM; nCntLIght++)
	{
		//ライト情報をクリアする
		ZeroMemory(&m_aLight[nCntLIght], sizeof(D3DLIGHT9));

		//ライトの種類を設定
		m_aLight[nCntLIght].Type = D3DLIGHT_DIRECTIONAL;

		//ライトの拡散光を設定
		m_aLight[nCntLIght].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);


		if (nCntLIght == 0)
		{
			//ライトの方向を設定
			m_VecDir[nCntLIght] = LIGHT_POS[0];
		}
		else if (nCntLIght == 1)
		{
			//ライトの方向を設定
			m_VecDir[nCntLIght] = LIGHT_POS[1];
		}
		else if (nCntLIght == 2)
		{
			//ライトの方向を設定
			m_VecDir[nCntLIght] = LIGHT_POS[2];
		}

		D3DXVec3Normalize(&m_VecDir[nCntLIght], &m_VecDir[nCntLIght]);//ベクトルを正規化する

		m_aLight[nCntLIght].Direction = m_VecDir[nCntLIght];


		//ライトの設定をする
		EscDevice->SetLight(nCntLIght, &m_aLight[nCntLIght]);

		//ライトを有効化する
		EscDevice->LightEnable(nCntLIght, TRUE);
	}
	return S_OK;
}

//=============================
//ライト終了処理
//=============================
void CLight::Uninit(void)
{
}

//=============================
//ライト更新処理
//=============================
void CLight::Update(void)
{
}

//=============================
// ライトの数取得
//=============================
int CLight::GetlightNum()
{
	return LIGHTNUM;
}

//=============================
// 特定のライトのベクトルを取得
//=============================
D3DXVECTOR3 CLight::GetLightVec(int LightNum)
{
	return m_VecDir[LightNum];
}