//=========================================================
//
// item.cppで使う関数[item.cpp]
// Author seiya kagaya
//
//=========================================================
#include "item.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "explosion.h"
#include "particle.h"
#include "all_texture.h"
#include "MathUtilities.h"

//=============================
//コンストラクタ
//=============================
CItem::CItem(int nPriority) :CObject2D(nPriority)
{
}

//=============================
//デストラクタ
//=============================
CItem::~CItem()
{
}

//=============================
//初期設定(頂点バッファ生成)
//=============================
HRESULT CItem::Init()
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

	int texIndex = pTexture->Regist("DATA\\TEXTURE\\item001.png", EscDevice);//テクスチャ登録

	m_ESCpTexture = pTexture->GetAddress(texIndex);
	BindTexture(m_ESCpTexture);//設定

	DATA EscData = GetDATA();
	EscData.Radius = (ITEM_SIZE + ITEM_SIZE) / 4;
	EscData.MinLength = D3DXVECTOR3(-ITEM_SIZE, -ITEM_SIZE, 0.0f);
	EscData.MaxLength = D3DXVECTOR3(ITEM_SIZE, ITEM_SIZE, 0.0f);

	SetDATA(EscData);//格納

	SetObjectType(CObject2D::OBJECT_ITEM);

	return S_OK;
}

//=============================
//終了処理(頂点バッファ破棄)
//=============================
void CItem::Uninit()
{
	CObject2D::Uninit();
}

//=============================
//更新(頂点情報の更新)
//=============================
void CItem::Update()
{
	InputpVtx();
	CObject2D::Update();
}

//=============================
//描画処理(POLYGON描画)
//=============================
void CItem::Draw()
{
	CObject2D::Draw();
}

//=============================
//設定格納
//=============================
void CItem::InputpVtx()
{
	//取得
	DATA EscData = GetDATA();
	VERTEX_2D EscVtx[BASE_INDEX];

	//頂点座標の更新-----------------------------------
	EscVtx[0].pos.x = EscData.Pos.x - ITEM_SIZE;//左上
	EscVtx[0].pos.y = EscData.Pos.y - ITEM_SIZE;//左上
	EscVtx[0].pos.z = 0.0f;

	EscVtx[1].pos.x = EscData.Pos.x + ITEM_SIZE;//右上
	EscVtx[1].pos.y = EscData.Pos.y - ITEM_SIZE;//右上
	EscVtx[1].pos.z = 0.0f;

	EscVtx[2].pos.x = EscData.Pos.x - ITEM_SIZE;//左下
	EscVtx[2].pos.y = EscData.Pos.y + ITEM_SIZE;//左下
	EscVtx[2].pos.z = 0.0f;

	EscVtx[3].pos.x = EscData.Pos.x + ITEM_SIZE;//右下
	EscVtx[3].pos.y = EscData.Pos.y + ITEM_SIZE;//右下
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
CItem* CItem::Create(DATA data)
{
	CItem* pItem = new CItem;
	pItem->Init();

	//取得
	DATA EscData = pItem->GetDATA();
	EscData.Pos = data.Pos;
	EscData.move = data.move;
	pItem->SetDATA(EscData);//格納
	pItem->ChangeRGBA(D3DCOLOR_RGBA(255, 255, 255, 255));

	return pItem;
}