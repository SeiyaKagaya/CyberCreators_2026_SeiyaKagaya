//=========================================================
//
// enemy.cppで使う関数[enemy.cpp]
// Author seiya kagaya
//
//=========================================================
#include "enemy.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "explosion.h"
#include "particle.h"
#include "all_texture.h"

//=============================
//コンストラクタ
//=============================
CEnemy::CEnemy(int nPriority):CObject2D(nPriority),m_nLife(START_LIFE)
{
}

//=============================
//デストラクタ
//=============================
CEnemy::~CEnemy()
{
}

//=============================
//初期設定(頂点バッファ生成)
//=============================
HRESULT CEnemy::Init()
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

	int texIndex = pTexture->Regist("DATA\\TEXTURE\\player000.png", EscDevice);//テクスチャ登録

	m_ESCpTexture = pTexture->GetAddress(texIndex);

	BindTexture(m_ESCpTexture);//設定

	//取得
	DATA EscData = GetDATA();
	EscData.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	EscData.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	EscData.OldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	EscData.Radius = (ENEMY_SIZE + ENEMY_SIZE) / 4;
 	EscData.MinLength = D3DXVECTOR3(-ENEMY_SIZE, -ENEMY_SIZE, 0.0f);
	EscData.MaxLength = D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f);

	SetDATA(EscData);//格納

	SetObjectType(CObject2D::OBJECT_ENEMY);

	return S_OK;
}

//=============================
//終了処理(頂点バッファ破棄)
//=============================
void CEnemy::Uninit()
{
	CObject2D::Uninit();
}

//=============================
//更新(頂点情報の更新)
//=============================
void CEnemy::Update()
{
	//取得
	DATA EscData = CEnemy::GetDATA();

	if (m_nLife <= 0 || EscData.Pos.x <= 0 || EscData.Pos.x >= SCREEN_WIDTH || EscData.Pos.y <= 0 || EscData.Pos.y >= SCREEN_HEIGHT)
	{
		CExplosion::Create(EscData);
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
void CEnemy::Draw()
{
	CObject2D::Draw();
}

//=============================
//設定格納
//=============================
void CEnemy::InputpVtx()
{
	//取得
	DATA EscData = GetDATA();
	VERTEX_2D EscVtx[BASE_INDEX];

	//頂点座標の更新-----------------------------------
	EscVtx[0].pos.x = EscData.Pos.x - ENEMY_SIZE;//左上
	EscVtx[0].pos.y = EscData.Pos.y - ENEMY_SIZE;//左上
	EscVtx[0].pos.z = 0.0f;

	EscVtx[1].pos.x = EscData.Pos.x + ENEMY_SIZE;//右上
	EscVtx[1].pos.y = EscData.Pos.y - ENEMY_SIZE;//右上
	EscVtx[1].pos.z = 0.0f;

	EscVtx[2].pos.x = EscData.Pos.x - ENEMY_SIZE;//左下
	EscVtx[2].pos.y = EscData.Pos.y + ENEMY_SIZE;//左下
	EscVtx[2].pos.z = 0.0f;

	EscVtx[3].pos.x = EscData.Pos.x + ENEMY_SIZE;//右下
	EscVtx[3].pos.y = EscData.Pos.y + ENEMY_SIZE;//右下
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
CEnemy* CEnemy::Create(DATA data)
{
	CEnemy* pEnemy = new CEnemy;
	pEnemy->Init();

	//取得
	DATA EscData = pEnemy->GetDATA();
	EscData.Pos = data.Pos;

	pEnemy->SetDATA(EscData);//格納
	pEnemy->ChangeRGBA(D3DCOLOR_RGBA(155, 155, 0, 255));

	return pEnemy;
}