//=========================================================
//
// explosion.cppで使う関数[explosion.cpp]
// Author seiya kagaya
//
//=========================================================
#include "explosion.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "explosion.h"
#include "all_texture.h"

//=============================
//コンストラクタ
//=============================
CExplosion::CExplosion(int nPriority):CObject2D(nPriority),m_nLife(START_LIFE), m_nPatternAnim(1)
{
}

//=============================
//デストラクタ
//=============================
CExplosion::~CExplosion()
{
}

//=============================
//初期設定(頂点バッファ生成)
//=============================
HRESULT CExplosion::Init()
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

	int texIndex = pTexture->Regist("DATA\\TEXTURE\\explosion000.png", EscDevice);//テクスチャ登録

	m_ESCpTexture = pTexture->GetAddress(texIndex);

	BindTexture(m_ESCpTexture);//設定

	SetObjectType(CObject2D::OBJECT_EXPLOSION);

	return S_OK;
}

//=============================
//終了処理(頂点バッファ破棄)
//=============================
void CExplosion::Uninit()
{
	CObject2D::Uninit();
}

//=============================
//更新(頂点情報の更新)
//=============================
void CExplosion::Update()
{
	//取得
	DATA EscData = GetDATA();

	m_nLife--;

	m_nPatternAnim++;
	
	SetDATA(EscData);//格納

	if (m_nLife <= 0 || m_nPatternAnim > DIVISION_NUMBER)
	{
		Uninit();
		Release();

		return;
	}
	
	InputpVtx();//ポリゴン更新

	CObject2D::Update();
}

//=============================
//描画処理(POLYGON描画)
//=============================
void CExplosion::Draw()
{
	CObject2D::Draw();
}

//=============================
//設定格納
//=============================
void CExplosion::InputpVtx()
{
	//取得
	DATA EscData = GetDATA();

	VERTEX_2D EscVtx[BASE_INDEX];

	//頂点座標の更新-----------------------------------
	EscVtx[0].pos.x = EscData.Pos.x - SIZE;//左上
	EscVtx[0].pos.y = EscData.Pos.y - SIZE;//左上
	EscVtx[0].pos.z = 0.0f;

	EscVtx[1].pos.x = EscData.Pos.x + SIZE;//右上
	EscVtx[1].pos.y = EscData.Pos.y - SIZE;//右上
	EscVtx[1].pos.z = 0.0f;

	EscVtx[2].pos.x = EscData.Pos.x - SIZE;//左下
	EscVtx[2].pos.y = EscData.Pos.y + SIZE;//左下
	EscVtx[2].pos.z = 0.0f;

	EscVtx[3].pos.x = EscData.Pos.x + SIZE;//右下
	EscVtx[3].pos.y = EscData.Pos.y + SIZE;//右下
	EscVtx[3].pos.z = 0.0f;

	EscVtx[0].tex = D3DXVECTOR2((1.0f / DIVISION_NUMBER) * m_nPatternAnim - (1.0f / DIVISION_NUMBER), 0.0f);//テクスチャ分割数分右側に座標がズレてる
	EscVtx[1].tex = D3DXVECTOR2((1.0f / DIVISION_NUMBER) * m_nPatternAnim, 0.0f);
	EscVtx[2].tex = D3DXVECTOR2((1.0f / DIVISION_NUMBER) * m_nPatternAnim - (1.0f / DIVISION_NUMBER), 1.0f);//テクスチャ分割数分右側に座標がズレてる
	EscVtx[3].tex = D3DXVECTOR2((1.0f / DIVISION_NUMBER) * m_nPatternAnim, 1.0f);

	SetpVtx(EscVtx);
}

//=============================
//Object生成
//=============================
CExplosion* CExplosion::Create(DATA data)
{
	CExplosion* pExplosion = new CExplosion;

	pExplosion->Init();

	//取得
	DATA EscData = pExplosion->GetDATA();
	EscData.Pos = data.Pos;

	pExplosion->SetDATA(EscData);//格納
	
	return pExplosion;
}