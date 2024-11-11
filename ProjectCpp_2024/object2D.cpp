//=======================================================
//
// object2Dに関する処理[object2D.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "object2D.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "all_texture.h"

//=============================
// コンストラクタ
//=============================
CObject2D::CObject2D(int nPriority):CObject(nPriority)
{
    m_nTexIdx = 0;
    m_pVtxBuff = nullptr;
    m_pTexture = nullptr;

    m_AddDrawMode = false;

    m_Data.Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.OldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_AddDrawMode = false;
    
    m_Data.MinLength = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.MaxLength = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.Radius = 0.0f;

}
//=============================
// デストラクタ
//=============================
CObject2D::~CObject2D()
{
    Uninit();
}
//=============================
// 初期設定(頂点バッファ生成)
//=============================
HRESULT CObject2D::Init()
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

    // 初期設定
    VERTEX_2D* pVtx;
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

    pVtx[0].rhw = 1.0f;
    pVtx[1].rhw = 1.0f;
    pVtx[2].rhw = 1.0f;
    pVtx[3].rhw = 1.0f;

    pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

    pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
    pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
    pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
    pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

    m_pVtxBuff->Unlock();

    return S_OK;
}
//=============================
// 終了処理(頂点バッファ破棄)
//=============================
void CObject2D::Uninit()
{
    m_AddDrawMode = false;

    if (m_pVtxBuff != nullptr)
    {
        m_pVtxBuff->Release();
        m_pVtxBuff = nullptr;
    }
    if (m_pTexture != nullptr)
    {
    //    m_pTexture->Release();//-----テクスチャcppでやること
        m_pTexture = nullptr;
    }
}
//=============================
// 更新(頂点情報の更新)
//=============================
void CObject2D::Update()
{
    // 更新処理


    VERTEX_2D* pVtx;

    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


  
        //頂点座標の更新-----------------------------------

    for (int nCnt = 0; nCnt < BASE_INDEX; nCnt++)
    {
        pVtx[nCnt].pos = m_pVtx[nCnt].pos;//左上
        pVtx[nCnt].tex = m_pVtx[nCnt].tex;

    }
    
    
    m_pVtxBuff->Unlock();
}
//=============================
// 描画処理(POLYGON描画)
//=============================
void CObject2D::Draw()
{
    CRenderer* pRenderer = nullptr;

    CManager* pManager = CManager::GetInstance();

    pRenderer = pManager->GetRenderer();


    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

    if (m_AddDrawMode)
    {
        EscDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
        EscDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
        EscDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
        EscDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
    }

    EscDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
    EscDevice->SetFVF(FVF_VERTEX_2D);

    if (m_pTexture!=nullptr)
    {
        EscDevice->SetTexture(0, m_pTexture);
    }
    else
    {
        EscDevice->SetTexture(0, nullptr);
    }

    HRESULT hr = EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

    if (FAILED(hr))
    {
   
    }

    if (m_AddDrawMode)
    {
        EscDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
        EscDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
        EscDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
        EscDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
    }

    EscDevice->SetTexture(0, nullptr);



}
//
//void CObject2D::TestDraw()
//{
//    CRenderer* pRenderer = nullptr;
//
//    CManager* pManager = CManager::GetInstance();
//
//    pRenderer = pManager->GetRenderer();
//
//
//    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();
//
//
//    EscDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
//    EscDevice->SetFVF(FVF_VERTEX_2D);
//
//    if (m_pTexture != nullptr)
//    {
//        EscDevice->SetTexture(0, m_pTexture);
//    }
//    else
//    {
//        EscDevice->SetTexture(0, nullptr);
//    }
//
//    HRESULT hr = EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
//}

//=============================
// Object生成
//=============================
CObject2D* CObject2D::Create()
{
    CObject2D* pObject2D = new CObject2D;
    pObject2D->Init();
    return pObject2D;
}
//=============================
// テクスチャ設定
//=============================
void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
    m_pTexture = pTex;
}
//=============================
// テクスチャ取得
//=============================
LPDIRECT3DTEXTURE9 CObject2D::GetTexture()
{
    return m_pTexture;
}
//=============================
// バッファ設定
//=============================
void CObject2D::BindVtxBuffer(LPDIRECT3DVERTEXBUFFER9 pVtx)
{
    m_pVtxBuff = pVtx;
}
//=============================
// バッファ取得
//=============================
LPDIRECT3DVERTEXBUFFER9 CObject2D::GetpVtxBuffer()
{
    return m_pVtxBuff;
}
//=============================
// 基礎情報取得
//=============================
CObject2D::DATA CObject2D::GetDATA()
{
    return m_Data;
}
//=============================
// 基礎情報設定
//=============================
void CObject2D::SetDATA(DATA data)
{
    m_Data = data;
}
//=============================
// 色変更
//=============================
void CObject2D::ChangeRGBA(D3DCOLOR col)
{
    VERTEX_2D* pVtx;
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    pVtx[0].col = col;
    pVtx[1].col = col;
    pVtx[2].col = col;
    pVtx[3].col = col;

    m_pVtxBuff->Unlock();
}
//=============================
// 加算合成切り替え
//=============================
void CObject2D::ChengeAddDrawMode(bool bSet)
{
    m_AddDrawMode = bSet;
}
//=============================
// 頂点、テクスチャ座標切り替え
//=============================
void CObject2D::SetpVtx(VERTEX_2D pVtx[BASE_INDEX])
{
    for (int nCnt = 0; nCnt < BASE_INDEX; nCnt++)
    {
        m_pVtx[nCnt] = pVtx[nCnt];
    }
}
//=============================
// 頂点座標入れ
//=============================
void CObject2D::InputpVtx()
{
}
//=============================
// テクスチャindex格納
//=============================
void CObject2D::SetTexIndex(int TexIdx)
{
    m_nTexIdx = TexIdx;
}
