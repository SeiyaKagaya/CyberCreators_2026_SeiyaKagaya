//=======================================================
//
// object_billboardに関する処理[object_billboard.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "object_billboard.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "all_texture.h"

//=============================
// コンストラクタ
//=============================
CObjectBillBoard::CObjectBillBoard(int nPriority) :CObjectX(nPriority)
{
    SetObjectType(CObject::OBJECT_BILLBOARD);
    m_pVtxBuff = nullptr;
    m_pTexture = nullptr;

    m_AddDrawMode = false;

    m_Data.Pos = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
    m_Data.OldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_AddDrawMode = false;

    m_Data.MinLength = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.MaxLength = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.Radius = 0.0f;
    m_ZDethDrawMode = false;
}
//=============================
// デストラクタ
//=============================
CObjectBillBoard::~CObjectBillBoard()
{
    Uninit();
}
//=============================
// 初期設定(頂点バッファ生成)
//=============================
HRESULT CObjectBillBoard::Init()
{
    CRenderer* pRenderer = nullptr;

    CManager* pManager = CManager::GetInstance();

    pRenderer = pManager->GetRenderer();


    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

    if (FAILED(EscDevice->CreateVertexBuffer(
        sizeof(VERTEX_3D) * 4,//四角形のため4
        D3DUSAGE_WRITEONLY,
        FVF_VERTEX_3D,
        D3DPOOL_MANAGED,
        &m_pVtxBuff,
        nullptr)))
    {
        return E_FAIL;
    }

    // 初期設定
    VERTEX_3D* pVtx;
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    float fTest = 2400.0f/2;
    float fTest2 = 3300.0f/2;

    ////頂点座標の設定
    //pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, fTest);
    //pVtx[1].pos = D3DXVECTOR3(fTest2, 0.0f, fTest);
    //pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    //pVtx[3].pos = D3DXVECTOR3(fTest2, 0.0f, 0.0f);

    //頂点座標の設定
    pVtx[0].pos = D3DXVECTOR3(-fTest2, fTest2, 0.0f);
    pVtx[1].pos = D3DXVECTOR3(fTest2, fTest2, 0.0f);
    pVtx[2].pos = D3DXVECTOR3(-fTest2, -fTest2, 0.0f);
    pVtx[3].pos = D3DXVECTOR3(fTest2, -fTest2, 0.0f);



    ////法線ベクトルの設定
    //pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    //pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    //pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    //pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);


        //法線ベクトルの設定
    pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
    pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
    pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
    pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

    //頂点カラーの設定
    pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

    //テクスチャ座標を設定
    pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//左上
    pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//右上
    pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//左下
    pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//右下


    m_pVtxBuff->Unlock();

    //テクスチャ読み込み
    LPDIRECT3DTEXTURE9	m_ESCpTexture = nullptr;

    //テクスチャ取得
    CAllTexture* pTexture = pManager->GetTexture();

    int texIndex = pTexture->Regist("DATA\\TEXTURE\\TestField.png", EscDevice);//テクスチャ登録

    m_ESCpTexture = pTexture->GetAddress(texIndex);

    BindTexture(m_ESCpTexture);//設定


    SetpVtx(pVtx);

    return S_OK;
}
//=============================
// 終了処理(頂点バッファ破棄)
//=============================
void CObjectBillBoard::Uninit()
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
void CObjectBillBoard::Update()
{
    // 更新処理


    VERTEX_3D* pVtx;

    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);



    //頂点座標の更新-----------------------------------

    for (int nCnt = 0; nCnt < BASE_INDEX; nCnt++)
    {
        pVtx[nCnt].pos = m_pVtx[nCnt].pos;//左上
        pVtx[nCnt].tex = m_pVtx[nCnt].tex;
        pVtx[nCnt].nor = m_pVtx[nCnt].nor;
        pVtx[nCnt].col = m_pVtx[nCnt].col;
    }


    m_pVtxBuff->Unlock();
}
//=============================
// 描画処理(POLYGON描画)
//=============================
void CObjectBillBoard::Draw()
{
    CRenderer* pRenderer = nullptr;
    CManager* pManager = CManager::GetInstance();
    pRenderer = pManager->GetRenderer();
    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

    D3DXMATRIX mtxRot, mtxTrans, mtxBillboard, mtxView;

    if (bSetLight == true)
    {
        // ライトを無効にする
        EscDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
    }
    if (m_ZDethDrawMode)
    {
        //Zの比較方法変更
        EscDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

        // Zバッファに書き込まない
        EscDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
    }

    // ワールドマトリックスの初期化
    D3DXMatrixIdentity(&m_mtxWorld);

    // ビューマトリックスを取得
    EscDevice->GetTransform(D3DTS_VIEW, &mtxView);

    // ビュー行列の逆行列を取得
    D3DXMatrixInverse(&mtxBillboard, NULL, &mtxView);

    // 逆行列の位置成分をリセット（回転だけを残す）
    mtxBillboard._41 = 0.0f;
    mtxBillboard._42 = 0.0f;
    mtxBillboard._43 = 0.0f;

    // ビルボード行列をワールド行列に掛け合わせる
    D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxBillboard);

    // 位置を反映
    D3DXMatrixTranslation(&mtxTrans, m_Data.Pos.x, m_Data.Pos.y, m_Data.Pos.z);
    D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

    // ワールドマトリックスの設定
    EscDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

    if (m_AddDrawMode)
    {
        EscDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
        EscDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
        EscDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
        EscDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
    }

    // 頂点バッファをデータストリームに設定
    EscDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

    // 頂点フォーマットの設定
    EscDevice->SetFVF(FVF_VERTEX_3D);

    // テクスチャの設定
    EscDevice->SetTexture(0, m_pTexture);

    for (int i = 0; i < nAddDrawCnt; i++)
    {
        // ポリゴンの描画
        EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
    }

    if (m_AddDrawMode)
    {
        EscDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
        EscDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
        EscDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
        EscDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
    }

    if (bSetLight == true)
    {
        // ライトを有効にする
        EscDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
    }

    if (m_ZDethDrawMode)
    {
        //Zの比較方法変更
        EscDevice->SetRenderState(D3DRS_ZFUNC,D3DCMP_LESSEQUAL);

        // Zバッファへの書き込みを有効にする
        EscDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
    }
}

//=============================
// Object生成
//=============================
CObjectBillBoard* CObjectBillBoard::Create()
{
    CObjectBillBoard* pObject3D = new CObjectBillBoard;
    pObject3D->Init();
    return pObject3D;
}
//=============================
// テクスチャ設定
//=============================
void CObjectBillBoard::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
    m_pTexture = pTex;
}
//=============================
// テクスチャ取得
//=============================
LPDIRECT3DTEXTURE9 CObjectBillBoard::GetTexture()
{
    return m_pTexture;
}
//=============================
// バッファ設定
//=============================
void CObjectBillBoard::BindVtxBuffer(LPDIRECT3DVERTEXBUFFER9 pVtx)
{
    m_pVtxBuff = pVtx;
}
//=============================
// バッファ取得
//=============================
LPDIRECT3DVERTEXBUFFER9 CObjectBillBoard::GetpVtxBuffer()
{
    return m_pVtxBuff;
}
//=============================
// 基礎情報取得
//=============================
CObjectBillBoard::DATA CObjectBillBoard::GetDATA()
{
    return m_Data;
}
//=============================
// 基礎情報設定
//=============================
void CObjectBillBoard::SetDATA(DATA data)
{
    m_Data = data;
}
//=============================
// 色変更
//=============================
void CObjectBillBoard::ChangeRGBA(D3DCOLOR col)
{
    VERTEX_3D* pVtx;
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
void CObjectBillBoard::ChengeAddDrawMode(bool bSet)
{
    m_AddDrawMode = bSet;
}
//=============================
// 頂点、テクスチャ座標切り替え
//=============================
void CObjectBillBoard::SetpVtx(VERTEX_3D pVtx[BASE_INDEX])
{
    for (int nCnt = 0; nCnt < BASE_INDEX; nCnt++)
    {
        m_pVtx[nCnt] = pVtx[nCnt];
    }
}
//=============================
// 頂点座標入れ
//=============================
void CObjectBillBoard::InputpVtx()
{
}

void CObjectBillBoard::SetZDrawDeth(bool bDraw)
{
    m_ZDethDrawMode = bDraw;
}
