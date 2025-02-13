//=======================================================
//
// smokeに関する処理[smoke.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "smoke.h"
#include "renderer.h"
#include "manager.h"

//=============================
// コンストラクタ
//=============================
CObjectSmoke::CObjectSmoke(int nPriority) :CObjectBillBoard(nPriority), m_nPatternAnim(1)
{
    SetObjectType(CObject::OBJECT_SMOKE);

    //加算合成
    ChengeAddDrawMode(true);
}

//=============================
// デストラクタ
//=============================
CObjectSmoke::~CObjectSmoke()
{
    Uninit();
}

//=============================
// 初期設定(頂点バッファ生成)
//=============================
HRESULT CObjectSmoke::Init()
{
    CRenderer* pRenderer = nullptr;
    CManager* pManager = CManager::GetInstance();
    pRenderer = pManager->GetRenderer();
    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();
    LPDIRECT3DVERTEXBUFFER9 ESCpVtxBuff;//頂点バッファ

    if (FAILED(EscDevice->CreateVertexBuffer(
        sizeof(VERTEX_3D) * 4,//四角形のため4
        D3DUSAGE_WRITEONLY,
        FVF_VERTEX_3D,
        D3DPOOL_MANAGED,
        &ESCpVtxBuff,
        nullptr)))
    {
        return E_FAIL;
    }

    BindVtxBuffer(ESCpVtxBuff);

    //テクスチャ読み込み
    LPDIRECT3DTEXTURE9	m_ESCpTexture = nullptr;

    //テクスチャ取得
    CAllTexture* pTexture = pManager->GetTexture();

    int texIndex = pTexture->Regist("DATA\\TEXTURE\\explosion000.png", EscDevice);//テクスチャ登録

    m_ESCpTexture = pTexture->GetAddress(texIndex);

    BindTexture(m_ESCpTexture);//設定

    m_nLife = START_LIFE;
    return S_OK;
}

//=============================
// 終了処理(頂点バッファ破棄)
//=============================
void CObjectSmoke::Uninit()
{
    CObjectBillBoard::Uninit();
}

//=============================
// 更新(頂点情報の更新)
//=============================
void CObjectSmoke::Update()
{
    InputpVtx();

    m_nPatternAnim++;
    
    if (m_nLife <= 0 || m_nPatternAnim > DIVISION_NUMBER)
    {
        SetDeath(true);
    }
    CObjectBillBoard::Update();
}

//=============================
// 描画処理(POLYGON描画)
//=============================
void CObjectSmoke::Draw()
{
    SetZDrawDeth(true);

    CObjectBillBoard::Draw();

    SetZDrawDeth(false);
}

//=============================
// 座標設定
//=============================
void CObjectSmoke::SetPos(D3DXVECTOR3 Pos)
{
    //取得
    DATA EscData = GetDATA();

    EscData.Pos = Pos;
    //取得
    SetDATA(EscData);
}

//=============================
// 頂点情報
//=============================
void CObjectSmoke::InputpVtx()
{
    // 初期設定
    VERTEX_3D pVtx[BASE_INDEX];

    //取得
    DATA EscData = GetDATA();

    //頂点座標の設定
    pVtx[0].pos = D3DXVECTOR3(-PRINTSIZE_X, PRINTSIZE_Z, 0.0f);
    pVtx[1].pos = D3DXVECTOR3(PRINTSIZE_X, PRINTSIZE_Z, 0.0f);
    pVtx[2].pos = D3DXVECTOR3(-PRINTSIZE_X, -PRINTSIZE_Z, 0.0f);
    pVtx[3].pos = D3DXVECTOR3(PRINTSIZE_X, -PRINTSIZE_Z, 0.0f);

    //法線ベクトルの設定
    pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
    pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
    pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
    pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

    //頂点カラーの設定
    pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, RGB_A);
    pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, RGB_A);
    pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, RGB_A);
    pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, RGB_A);

    pVtx[0].tex = D3DXVECTOR2((1.0f / DIVISION_NUMBER) * m_nPatternAnim - (1.0f / DIVISION_NUMBER), 0.0f);//テクスチャ分割数分右側に座標がズレてる
    pVtx[1].tex = D3DXVECTOR2((1.0f / DIVISION_NUMBER) * m_nPatternAnim, 0.0f);
    pVtx[2].tex = D3DXVECTOR2((1.0f / DIVISION_NUMBER) * m_nPatternAnim - (1.0f / DIVISION_NUMBER), 1.0f);//テクスチャ分割数分右側に座標がズレてる
    pVtx[3].tex = D3DXVECTOR2((1.0f / DIVISION_NUMBER) * m_nPatternAnim, 1.0f);

    SetpVtx(pVtx);
}

//=============================
// Object生成
//=============================
CObjectSmoke* CObjectSmoke::Create(D3DXVECTOR3 Pos)
{
    CObjectSmoke* pObject3D = new CObjectSmoke;
    pObject3D->SetPos(Pos);
    pObject3D->Init();
    return pObject3D;
}