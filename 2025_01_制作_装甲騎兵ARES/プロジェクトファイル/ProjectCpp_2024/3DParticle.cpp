//=======================================================
//
// 3DParticleに関する処理[3DParticle.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "3DParticle.h"
#include "renderer.h"
#include "manager.h"

//=============================
// コンストラクタ
//=============================
CObject3DParticleAll::CObject3DParticleAll(int nPriority) : CObjectX(nPriority)
{
}

//=============================
// デストラクタ
//=============================
CObject3DParticleAll::~CObject3DParticleAll()
{
}

//=============================
// 初期化
//=============================
HRESULT CObject3DParticleAll::Init()
{
    //初期化
    for (int i = 0; i < MAXPARTICLEALL; i++)
    {
        m_NewParticle[i] = nullptr;
    }

    for (int i = 0; i < MAXPARTICLEALL; i++)
    {
        m_NewParticle[i] = CObject3DParticle::Create();
    }

    SetObjectType(CObject::OBJECT_3DPARTICLE_MNG);

    return E_NOTIMPL;
}

//=============================
// 終了
//=============================
void CObject3DParticleAll::Uninit()
{
    for (int i = 0; i < MAXPARTICLEALL; i++)
    {
        m_NewParticle[i]->SetDeath(true);
    }
}

//=============================
// Create
//=============================
CObject3DParticleAll* CObject3DParticleAll::Create()
{
    CObject3DParticleAll* pNewBulletALL = new CObject3DParticleAll;
    pNewBulletALL->Init();
    return pNewBulletALL;
}

//=============================
// Release
//=============================
void CObject3DParticleAll::ReleaseAllParticle()
{
    Uninit();
    delete this;
}

//=============================
// Clean
//=============================
void CObject3DParticleAll::AllClean()
{
    for (int i = 0; i < MAXPARTICLEALL; i++)
    {
        m_NewParticle[i]->SetUse(false);
    }
}

//=============================
// 取得
//=============================
CObject3DParticle* CObject3DParticleAll::GetParticleData(int nNum)
{
    return m_NewParticle[nNum];
}

//=============================
// 静的にバレットをセット
//=============================
void CObject3DParticleAll::SetParticle(D3DXVECTOR3 Pos, D3DXCOLOR col, int nLife, float Size)
{
    for (int i = 0; i < MAXPARTICLEALL; i++)
    {
        CObject3DParticle* pBullet = GetParticleData(i);

        if (m_NewParticle[i]->GetbUse() == false)
        {
            m_NewParticle[i]->SetCOL(col);
            m_NewParticle[i]->SetPos(Pos);
            m_NewParticle[i]->SetLife(nLife);
            m_NewParticle[i]->SetSize(Size);
            m_NewParticle[i]->SetUse(true);

            CRenderer* pRenderer = nullptr;
            CManager* pManager = CManager::GetInstance();

            break;
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------

//=============================
// コンストラクタ
//=============================
CObject3DParticle::CObject3DParticle(int nPriority) :CObjectBillBoard(nPriority)
{
    SetObjectType(CObject::OBJECT_3DPARTICLE);

    ChengeAddDrawMode(true);//加算合成On
    SetAddDrawCnt(4);//加算回数
}

//=============================
// デストラクタ
//=============================
CObject3DParticle::~CObject3DParticle()
{
    Uninit();
}

//=============================
// 初期設定(頂点バッファ生成)
//=============================
HRESULT CObject3DParticle::Init()
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

    int texIndex = pTexture->Regist("DATA\\TEXTURE\\effect000.jpg", EscDevice);//テクスチャ登録
    
    m_ESCpTexture = pTexture->GetAddress(texIndex);

    BindTexture(m_ESCpTexture);//設定

    return S_OK;
}

//=============================
// 終了処理(頂点バッファ破棄)
//=============================
void CObject3DParticle::Uninit()
{
    CObjectBillBoard::Uninit();
}

//=============================
// 更新(頂点情報の更新)
//=============================
void CObject3DParticle::Update()
{
    if (m_bUse == true)
    {
        InputpVtx();

        if (m_nLife <= 0)
        {
            m_bUse = false;
        }

        CObjectBillBoard::Update();

        m_nLife--;
    }
}

//=============================
// 描画処理(POLYGON描画)
//=============================
void CObject3DParticle::Draw()
{
    if (m_bUse == true)
    {
        SetLight(true);
        CObjectBillBoard::Draw();
    }
}

//=============================
// 座標設定
//=============================
void CObject3DParticle::SetPos(D3DXVECTOR3 Pos)
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
void CObject3DParticle::InputpVtx()
{
    // 初期設定
    VERTEX_3D pVtx[BASE_INDEX];

    //取得
    DATA EscData = GetDATA();

    //頂点座標の設定
    pVtx[0].pos = D3DXVECTOR3(-m_Size, m_Size, 0.0f);
    pVtx[1].pos = D3DXVECTOR3(m_Size, m_Size, 0.0f);
    pVtx[2].pos = D3DXVECTOR3(-m_Size, -m_Size, 0.0f);
    pVtx[3].pos = D3DXVECTOR3(m_Size, -m_Size, 0.0f);
    
    //法線ベクトルの設定
    pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
    pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
    pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
    pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

    //頂点カラーの設定
    pVtx[0].col = m_col;
    pVtx[1].col = m_col;
    pVtx[2].col = m_col;
    pVtx[3].col = m_col;

    //テクスチャ座標を設定
    pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//左上
    pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//右上
    pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//左下
    pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//右下

    SetpVtx(pVtx);
}

//=============================
// 色変更
//=============================
void CObject3DParticle::SetCOL(D3DXCOLOR col)
{
    m_col = col;
}

//=============================
// Object生成
//=============================
CObject3DParticle* CObject3DParticle::Create()
{
    CObject3DParticle* pObject3D = new CObject3DParticle;

    pObject3D->Init();

    return pObject3D;
}