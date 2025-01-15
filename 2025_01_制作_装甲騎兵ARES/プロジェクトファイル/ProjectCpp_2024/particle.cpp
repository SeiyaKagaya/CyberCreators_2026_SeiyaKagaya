//=========================================================
//
// particle.cppで使う関数[particle.cpp]
// Author seiya kagaya
//
//=========================================================
#include "particle.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "explosion.h"
#include "all_texture.h"

//=============================
//コンストラクタ
//=============================
CParticle::CParticle(int nPriority):CObject2D(nPriority), m_nLife(START_LIFE),m_Radius((float)START_RADiUS)
{


}
//=============================
//デストラクタ
//=============================
CParticle::~CParticle()
{
}
//=============================
//初期設定(頂点バッファ生成)
//=============================
HRESULT CParticle::Init()
{

	CObject2D::Init();//基本設定

	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	pRenderer = pManager->GetRenderer();


	LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

	//テクスチャ読み込み
	LPDIRECT3DTEXTURE9	m_ESCpTexture = nullptr;

	//テクスチャ取得
	CAllTexture* pTexture = pManager->GetTexture();

	int texIndex = pTexture->Regist("DATA\\TEXTURE\\effect000.jpg", EscDevice);//テクスチャ登録

	m_ESCpTexture = pTexture->GetAddress(texIndex);

	BindTexture(m_ESCpTexture);//設定

	SetObjectType(CObject2D::OBJECT_PARTICLE);
	return S_OK;
}
//=============================
//終了処理(頂点バッファ破棄)
//=============================
void CParticle::Uninit()
{
	CObject2D::Uninit();
}
//=============================
//更新(頂点情報の更新)
//=============================
void CParticle::Update()
{	
	//取得
	DATA EscData = GetDATA();



	m_nLife--;
	m_Radius -= 0.1f;



	if (m_nLife <= 0 || EscData.Pos.x <= 0 || EscData.Pos.x >= SCREEN_WIDTH || EscData.Pos.y <= 0 || EscData.Pos.y >= SCREEN_HEIGHT)
	{
		Uninit();
		Release();
		return;
	}


	SetDATA(EscData);//格納


	InputpVtx();//ポリゴン更新
	CObject2D::Update();
}
//=============================
//描画処理(POLYGON描画)
//=============================
void CParticle::Draw()
{
	ChengeAddDrawMode(true);

	CObject2D::Draw();

	ChengeAddDrawMode(false);

}
//=============================
//設定格納
//=============================
void CParticle::InputpVtx()
{
	//取得
	DATA EscData = GetDATA();


	VERTEX_2D EscVtx[BASE_INDEX];

	//頂点座標の更新-----------------------------------
	EscVtx[0].pos.x = EscData.Pos.x - m_Radius;//左上
	EscVtx[0].pos.y = EscData.Pos.y - m_Radius;//左上
	EscVtx[0].pos.z = 0.0f;

	EscVtx[1].pos.x = EscData.Pos.x + m_Radius;//右上
	EscVtx[1].pos.y = EscData.Pos.y - m_Radius;//右上
	EscVtx[1].pos.z = 0.0f;

	EscVtx[2].pos.x = EscData.Pos.x - m_Radius;//左下
	EscVtx[2].pos.y = EscData.Pos.y + m_Radius;//左下
	EscVtx[2].pos.z = 0.0f;

	EscVtx[3].pos.x = EscData.Pos.x + m_Radius;//右下
	EscVtx[3].pos.y = EscData.Pos.y + m_Radius;//右下
	EscVtx[3].pos.z = 0.0f;

	EscVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	EscVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	EscVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	EscVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	SetpVtx(EscVtx);
}
//=============================
//Object生成
//=============================
CParticle* CParticle::Create(DATA data)
{
	CParticle* pParticle = new CParticle;
	pParticle->Init();


	//取得
	DATA EscData = pParticle->GetDATA();

	EscData.Pos = data.Pos;

	pParticle->SetDATA(EscData);//格納


	pParticle->ChangeRGBA(D3DCOLOR_RGBA(255, 0, 0, 255));

	return pParticle;
}




