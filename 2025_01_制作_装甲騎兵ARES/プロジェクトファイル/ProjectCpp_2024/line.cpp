//=========================================================
//
//ラインを表示する処理[line.cpp]
// Author seiya kagaya
//
//=========================================================
#include "line.h"
#include "renderer.h"
#include "manager.h"



//=============================
// コンストラクタ
//=============================
Cline::Cline(int nPriority) :CObject3D(nPriority), m_pVtxBuff(nullptr)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	 m_startPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	 m_endPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	 m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col= D3DXCOLOR(0.0f,0.0f,0.0f,0.0f);
	m_Life = 3;//ここを２にすると線が見える
}
//=============================
//デストラクタ
//=============================
Cline::~Cline()
{
}
//=============================
// 初期化
//=============================
HRESULT Cline::Init()
{
 //   CObject::Init();

    CRenderer* pRenderer = nullptr;

    CManager* pManager = CManager::GetInstance();

    pRenderer = pManager->GetRenderer();


    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();


    // 頂点バッファの生成
    EscDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 2, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

    VERTEX_3D* pVtx;

    // 頂点バッファをロックし、頂点情報へのポインタを取得
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

   
        // 頂点座標の設定
        pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

        // 法線ベクトルの設定
        pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
        pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

        // 頂点カラー
        pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
        pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

        // テクスチャ座標の設定
        pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
        pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);

    
    // 頂点バッファをアンロックする
    
    m_pVtxBuff->Unlock();
    SetObjectType(CObject::OBJECT_LINE);


    return S_OK;
}
//=============================
// 終了処理
//=============================
void Cline::Uninit()
{
    // 頂点バッファの破棄
    if (m_pVtxBuff != NULL)
    {
        m_pVtxBuff->Release();
        m_pVtxBuff = NULL;
    }
}
//=============================
// 更新
//=============================
void Cline::Update()
{
    
    int test = 0;

    m_Life--;

    if (m_Life <= 0)
    {
        SetDeath(true);
    }

}
//=============================
// 描画
//=============================
void Cline::Draw()
{
    CRenderer* pRenderer = nullptr;

    CManager* pManager = CManager::GetInstance();

    pRenderer = pManager->GetRenderer();


    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();


    D3DXMATRIX mtxRot, mtxTrans;                            // 計算用マトリックス

    // ワールドマトリックスの初期化
    D3DXMatrixIdentity(&m_mtxWorld);

    // 向きを反映
    D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

    D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

    // 位置を反映
    D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

    D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

    // ワールドマトリックスの設定
    EscDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

    // 頂点バッファをデータストリームに設定
    EscDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

    // 頂点フォーマットの設定
    EscDevice->SetFVF(FVF_VERTEX_3D);

    // テクスチャの設定
    EscDevice->SetTexture(0, NULL);

    // ポリゴンの描画
    EscDevice->DrawPrimitive(D3DPT_LINELIST, //プリミティブの種類
        0, //描画する最初の頂点インデックス
        1);             //描画するプリミティブ数

    //テクスチャを戻す
    EscDevice->SetTexture(0, NULL);
}
//=============================
// 生成
//=============================
Cline* Cline::Create(D3DXVECTOR3 start, D3DXVECTOR3 end, D3DXCOLOR col)
{
    Cline* pLine = new Cline;
    pLine->Init();
    pLine->SetLineData(start, end, col);

    return pLine;
}
//=============================
// データ格納
//=============================
void Cline::SetLineData(D3DXVECTOR3 start, D3DXVECTOR3 end, D3DXCOLOR col)
{
    
  //  m_pos = D3DXVECTOR3((start.x + end.x) * 0.5f, (start.y + end.y) * 0.5f, (start.z + end.z) * 0.5f);
    m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_startPos = start;
    m_endPos = end;
    m_col = col;

    VERTEX_3D* pVtx;

    // 頂点バッファをロックし、頂点情報へのポインタを取得
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    //// 頂点座標の設定
    //pVtx[0].pos = D3DXVECTOR3(-fabsf(end.x - start.x) * 0.5f, -fabsf(end.y - start.y) * 0.5f, -fabsf(end.z - start.z) * 0.5f);
    //pVtx[1].pos = D3DXVECTOR3(fabsf(end.x - start.x) * 0.5f, fabsf(end.y - start.y) * 0.5f, fabsf(end.z - start.z) * 0.5f);
    pVtx[0].pos = start;
    pVtx[1].pos = end;



    pVtx[0].col = col;
    pVtx[1].col = col;
    // 頂点バッファをアンロックする

    m_pVtxBuff->Unlock();
    
}
