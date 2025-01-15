//=======================================================
//
//backgroundに関する処理[background.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "background.h"
#include "renderer.h"
#include "manager.h"
#include "main.h"

//=============================
//コンストラクタ
//=============================
CBG::CBG()
{
	CRenderer* pRenderer = nullptr;
	
	CManager* pManager = CManager::GetInstance();

	pRenderer = pManager->GetRenderer();



	LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

//	data.Pos = D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f);
	m_pVtxBuff = nullptr;
	m_pTexture = nullptr;

	
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(EscDevice, "DATA\\TEXTURE\\title000.png", &m_pTexture);//通常時

}
//=============================
//デストラクタ
//=============================
CBG::~CBG()
{
}
//=============================
//初期設定(頂点バッファ生成)
//=============================
HRESULT CBG::Init()
{
	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	pRenderer = pManager->GetRenderer();


	LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();


	if (FAILED(EscDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		nullptr)))
	{
		return E_FAIL;
	}




	VERTEX_2D* pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定

	float fTest = 1500.0f;

	pVtx[0].pos.x = -fTest;//左上
	pVtx[0].pos.y = 0.0f;//左上
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = fTest;//右上
	pVtx[1].pos.y = 0.0f;//右上
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = -fTest;//左下
	pVtx[2].pos.y = fTest;//左下
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = fTest;//右下
	pVtx[3].pos.y = fTest;//右下
	pVtx[3].pos.z = 0.0f;



	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);



		//テクスチャ座標を更新
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	m_pVtxBuff->Unlock();


	return S_OK;

}
//=============================
//終了処理(頂点バッファ破棄)
//=============================
void CBG::Uninit()
{
	if (m_pTexture)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}
//=============================
//更新(頂点情報の更新)
//=============================
void CBG::Update()
{
	VERTEX_2D* pVtx;

	m_pVtxBuff->Lock(0, 0, reinterpret_cast<void**>(&pVtx), 0);

	

	m_pVtxBuff->Unlock();

}
//=============================
//描画処理(POLYGON描画)
//=============================
void CBG::Draw()
{
	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	pRenderer = pManager->GetRenderer();


	LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();



	EscDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	EscDevice->SetFVF(FVF_VERTEX_2D);

	EscDevice->SetTexture(0, m_pTexture);

	EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);


}


//=============================
//Object生成
//=============================
CBG* CBG::Create()
{
	CBG* pPolygon = new CBG;
	pPolygon->Init();


	return pPolygon;
}





//継承元は2Dのほう？