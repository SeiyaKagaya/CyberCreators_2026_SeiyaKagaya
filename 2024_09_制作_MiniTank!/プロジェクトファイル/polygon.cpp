//=======================================================
//
//polygonに関する処理[polygon.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "polygon.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"

//=============================
//コンストラクタ
//=============================
CPolygon::CPolygon(int nPriority):CObject2D(nPriority), m_nCounterAnim(0), m_nDirectionMove(0), m_nPatternAnim(0)
{
	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();
	pRenderer = pManager->GetRenderer();
	LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

	//取得
	DATA EscData = GetDATA();
	EscData.Pos = D3DXVECTOR3(SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f, 0.0f);
	EscData.MinLength = D3DXVECTOR3(-POLYGON_SIZE /2, -POLYGON_SIZE /2, 0.0f);//左上
	EscData.MaxLength = D3DXVECTOR3(POLYGON_SIZE /2, POLYGON_SIZE /2, 0.0f);//左上

	//テクスチャ読み込み
	LPDIRECT3DTEXTURE9	m_ESCpTexture = nullptr;

	//テクスチャ取得
	CAllTexture* pTexture = pManager->GetTexture();

	int texIndex = pTexture->Regist("DATA\\TEXTURE\\Block001.jpg", EscDevice);//テクスチャ登録

	m_ESCpTexture = pTexture->GetAddress(texIndex);

	BindTexture(m_ESCpTexture);//設定

	SetDATA(EscData);//格納

	SetObjectType(CObject2D::OBJECT_POLYGON);
}

//=============================
//デストラクタ
//=============================
CPolygon::~CPolygon()
{
}

//=============================
//初期設定(頂点バッファ生成)
//=============================
HRESULT CPolygon::Init()
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
	VERTEX_2D* pVtx;

	ESCpVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	
	//取得
	DATA EscData = GetDATA();

	//頂点座標の設定
	pVtx[0].pos.x = EscData.Pos.x - POLYGON_SIZE / 2;//左上
	pVtx[0].pos.y = EscData.Pos.y - POLYGON_SIZE / 2;//左上
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x =EscData.Pos.x + POLYGON_SIZE / 2;//右上
	pVtx[1].pos.y =EscData.Pos.y - POLYGON_SIZE / 2;//右上
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x =EscData.Pos.x - POLYGON_SIZE / 2;//左下
	pVtx[2].pos.y =EscData.Pos.y + POLYGON_SIZE / 2;//左下
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x =EscData.Pos.x + POLYGON_SIZE / 2;//右下
	pVtx[3].pos.y =EscData.Pos.y + POLYGON_SIZE / 2;//右下
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


	ESCpVtxBuff->Unlock();

	SetDATA(EscData);//格納

	return S_OK;
}

//=============================
//終了処理(頂点バッファ破棄)
//=============================
void CPolygon::Uninit()
{
	CObject2D::Uninit();
}

//=============================
//更新(頂点情報の更新)
//=============================
void CPolygon::Update()
{
}

//=============================
//描画処理(POLYGON描画)
//=============================
void CPolygon::Draw()
{
	CObject2D::Draw();
}

//=============================
//Object生成
//=============================
CPolygon* CPolygon::Create()
{
	CPolygon* pPolygon = new CPolygon;
	pPolygon->Init();
	return pPolygon;
}