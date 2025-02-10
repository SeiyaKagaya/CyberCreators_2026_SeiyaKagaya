//=========================================================
//
// ballet.cppで使う関数[ballet.cpp]
// Author seiya kagaya
//
//=========================================================
#include "ballet.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "explosion.h"
#include "particle.h"
#include "all_texture.h"
#include "MathUtilities.h"
#include "block.h"

//=============================
//コンストラクタ
//=============================
CBullet::CBullet(int nPriority):CObject2D(nPriority),m_nLife(START_LIFE),m_speed((float)START_SPEED)
{
}

//=============================
//デストラクタ
//=============================
CBullet::~CBullet()
{
}

//=============================
//初期設定(頂点バッファ生成)
//=============================
HRESULT CBullet::Init()
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

	int texIndex = pTexture->Regist("DATA\\TEXTURE\\bullet000.png", EscDevice);//テクスチャ登録

	m_ESCpTexture = pTexture->GetAddress(texIndex);

	BindTexture(m_ESCpTexture);//設定
							   
	//取得
	DATA EscData = GetDATA();

	EscData.Radius = (BULLET_SIZE + BULLET_SIZE) / 4;
	EscData.MinLength = D3DXVECTOR3(-BULLET_SIZE, -BULLET_SIZE, 0.0f);
	EscData.MaxLength = D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE, 0.0f);

	SetDATA(EscData);//格納

	SetObjectType(CObject2D::OBJECT_BULLET);

	return S_OK;
}

//=============================
//終了処理(頂点バッファ破棄)
//=============================
void CBullet::Uninit()
{
	CObject2D::Uninit();
}

//=============================
//更新(頂点情報の更新)
//=============================
void CBullet::Update()
{
	//取得
	DATA EscData = GetDATA();
	EscData.OldPos = EscData.Pos;
	EscData.Pos += EscData.move*m_speed;

	m_nLife--;

	CParticle::Create(EscData);

	SetDATA(EscData);//格納
	
	HitCollision();//当たり判定

	//再度取得
	EscData = GetDATA();

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
void CBullet::Draw()
{
	CObject2D::Draw();
}

//=============================
//あたり判定格納
//=============================
void CBullet::HitCollision()
{
	//取得
	DATA EscData = GetDATA();

	CMathProc::CollisionData HitData;//当たり判定データ

	//当たり判定計算--敵
	HitData = CMathProc::CheckBoxCollision_2D(EscData.Pos, EscData.OldPos, EscData.MinLength, EscData.MaxLength, CObject2D::OBJECT_ENEMY);//敵

	if (HitData.bHit ==false)
	{
		//当たり判定計算--BLOCK
		HitData = CMathProc::CheckBoxCollision_2D(EscData.Pos, EscData.OldPos, EscData.MinLength, EscData.MaxLength, CObject2D::OBJECT_POLYGON);//ポリゴン

		if (HitData.bHit == false)
		{
			//当たり判定計算--敵
			HitData = CMathProc::CheckBoxCollision_2D(EscData.Pos, EscData.OldPos, EscData.MinLength, EscData.MaxLength, CObject2D::OBJECT_BLOCK);//block
		}
	}

	if (HitData.bHit == true)
	{
		m_nLife = 0;
	}

	SetDATA(EscData);//格納
}

//=============================
//設定格納
//=============================
void CBullet::InputpVtx()
{
	//取得
	DATA EscData = GetDATA();


	VERTEX_2D EscVtx[BASE_INDEX];

	//頂点座標の更新-----------------------------------
	EscVtx[0].pos.x = EscData.Pos.x - BULLET_SIZE;//左上
	EscVtx[0].pos.y = EscData.Pos.y - BULLET_SIZE;//左上
	EscVtx[0].pos.z = 0.0f;

	EscVtx[1].pos.x = EscData.Pos.x + BULLET_SIZE;//右上
	EscVtx[1].pos.y = EscData.Pos.y - BULLET_SIZE;//右上
	EscVtx[1].pos.z = 0.0f;

	EscVtx[2].pos.x = EscData.Pos.x - BULLET_SIZE;//左下
	EscVtx[2].pos.y = EscData.Pos.y + BULLET_SIZE;//左下
	EscVtx[2].pos.z = 0.0f;

	EscVtx[3].pos.x = EscData.Pos.x + BULLET_SIZE;//右下
	EscVtx[3].pos.y = EscData.Pos.y + BULLET_SIZE;//右下
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
CBullet* CBullet::Create(DATA data)
{
	CBullet* pBullet = new CBullet;
	pBullet->Init();

	//取得
	DATA EscData = pBullet->GetDATA();
	EscData.Pos = data.Pos;
	EscData.move = data.move;

	pBullet->SetDATA(EscData);//格納	
	pBullet->ChangeRGBA(D3DCOLOR_RGBA(155, 155, 0, 255));

	return pBullet;
}