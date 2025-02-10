//=======================================================
//
//blockに関する処理[block.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "block.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "explosion.h"

//=============================
//コンストラクタ
//=============================
CBlock::CBlock(int nPriority) :CObject2D(nPriority), m_nCounterAnim(0), m_nDirectionMove(0), m_nPatternAnim(0),m_nLife(STARTLIFE)
{
	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();
	pRenderer = pManager->GetRenderer();
	LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

	//取得
	DATA EscData = GetDATA();

	EscData.Pos = D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f);
	EscData.MinLength = D3DXVECTOR3(-BLOCK_SIZE, -BLOCK_SIZE, 0.0f);//左上
	EscData.MaxLength = D3DXVECTOR3(BLOCK_SIZE, BLOCK_SIZE, 0.0f);//左上

	//テクスチャ読み込み
	LPDIRECT3DTEXTURE9	m_ESCpTexture = nullptr;

	//テクスチャ取得
	CAllTexture* pTexture = pManager->GetTexture();

	int texIndex = pTexture->Regist("DATA\\TEXTURE\\Block004.jpg", EscDevice);//テクスチャ登録

	m_ESCpTexture = pTexture->GetAddress(texIndex);
	
	BindTexture(m_ESCpTexture);//設定

	SetDATA(EscData);//格納

	SetObjectType(CObject2D::OBJECT_BLOCK);
}

//=============================
//デストラクタ
//=============================
CBlock::~CBlock()
{
}

//=============================
//初期設定(頂点バッファ生成)
//=============================
HRESULT CBlock::Init()
{
	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();
	pRenderer = pManager->GetRenderer();
	LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

	//取得
	LPDIRECT3DVERTEXBUFFER9 ESCpVtxBuff = GetpVtxBuffer();

	if (FAILED(EscDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&ESCpVtxBuff,
		nullptr)))
	{
		return E_FAIL;
	}

	//設定
	BindVtxBuffer(ESCpVtxBuff);

	return S_OK;
}

//=============================
//終了処理(頂点バッファ破棄)
//=============================
void CBlock::Uninit()
{
	CObject2D::Uninit();
}

//=============================
//更新(頂点情報の更新)
//=============================
void CBlock::Update()
{
	//取得
	DATA EscData = GetDATA();

	if (m_nLife <= 0)
	{
		CExplosion::Create(EscData);
		Uninit();
		SetDeath(true);
		return;
	}

	InputpVtx();

	CObject2D::Update();
}

//=============================
//描画処理(BLOCK描画)
//=============================
void CBlock::Draw()
{
	CObject2D::Draw();
}

//=============================
//被弾処理
//=============================
void CBlock::Damage(int nDamage)
{
	m_nLife -= nDamage;
}

//=============================
//設定格納
//=============================
void CBlock::InputpVtx()
{
	//取得
	DATA EscData = GetDATA();

	VERTEX_2D EscVtx[BASE_INDEX];

	//頂点座標の更新-----------------------------------
	EscVtx[0].pos.x = EscData.Pos.x - BLOCK_SIZE;//左上
	EscVtx[0].pos.y = EscData.Pos.y - BLOCK_SIZE;//左上
	EscVtx[0].pos.z = 0.0f;

	EscVtx[1].pos.x = EscData.Pos.x + BLOCK_SIZE;//右上
	EscVtx[1].pos.y = EscData.Pos.y - BLOCK_SIZE;//右上
	EscVtx[1].pos.z = 0.0f;

	EscVtx[2].pos.x = EscData.Pos.x - BLOCK_SIZE;//左下
	EscVtx[2].pos.y = EscData.Pos.y + BLOCK_SIZE;//左下
	EscVtx[2].pos.z = 0.0f;

	EscVtx[3].pos.x = EscData.Pos.x + BLOCK_SIZE;//右下
	EscVtx[3].pos.y = EscData.Pos.y + BLOCK_SIZE;//右下
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
CBlock* CBlock::Create(DATA data)
{
	CBlock* pBlock = new CBlock;
	pBlock->Init();

	//取得
	DATA EscData = pBlock->GetDATA();

	EscData.Pos = data.Pos;
	EscData.move = data.move;

	pBlock->SetDATA(EscData);//格納

	pBlock->ChangeRGBA(D3DCOLOR_RGBA(255, 255, 255, 255));

	return pBlock;
}