//=======================================================
//
// debugwallに関する処理[debugwall.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "debugwall.h"
#include "renderer.h"
#include "manager.h"

//=============================
// コンストラクタ
//=============================
CDebugwall::CDebugwall(int nPriority) :CObject3D(nPriority)
{
    SetObjectType(CObject::OBJECT_DEBUGWALL);
}

//=============================
// デストラクタ
//=============================
CDebugwall::~CDebugwall()
{
    Uninit();
}

//=============================
// 初期設定(頂点バッファ生成)
//=============================
HRESULT CDebugwall::Init()
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

    //バッファ格納
    BindVtxBuffer(ESCpVtxBuff);

    //テクスチャ読み込み
    LPDIRECT3DTEXTURE9	m_ESCpTexture = nullptr;

    //テクスチャ取得
    CAllTexture* pTexture = pManager->GetTexture();

    int texIndex = pTexture->Regist("DATA\\TEXTURE\\iwaWall.png", EscDevice);//テクスチャ登録

    m_ESCpTexture = pTexture->GetAddress(texIndex);//テクスチャのアドレスを取得

    BindTexture(m_ESCpTexture);//設定

    return S_OK;
}

//=============================
// 終了処理(頂点バッファ破棄)
//=============================
void CDebugwall::Uninit()
{
    CObject3D::Uninit();
}

//=============================
// 更新(頂点情報の更新)
//=============================
void CDebugwall::Update()
{
    //頂点情報を更新
    InputpVtx();

    CObject3D::Update();
}

//=============================
// 描画処理(POLYGON描画)
//=============================
void CDebugwall::Draw()
{
    CObject3D::Draw();
}

//=============================
// 座標設定
//=============================
void CDebugwall::SetPos_Rot(D3DXVECTOR3 Pos, D3DXVECTOR3 rot)
{
    DATA EscData = GetDATA();

    EscData.Pos = Pos;
    EscData.rot = rot;
    
    SetDATA(EscData);
}

//=============================
// 頂点情報
//=============================
void CDebugwall::InputpVtx()
{
    // 初期設定
    VERTEX_3D pVtx[BASE_INDEX];

    //取得
    DATA EscData = GetDATA();

    //頂点座標の設定
    pVtx[0].pos = D3DXVECTOR3(-PRINTSIZE, EscData.Pos.y, PRINTSIZE);
    pVtx[1].pos = D3DXVECTOR3(PRINTSIZE, EscData.Pos.y, PRINTSIZE);
    pVtx[2].pos = D3DXVECTOR3(-PRINTSIZE, EscData.Pos.y,-PRINTSIZE);
    pVtx[3].pos = D3DXVECTOR3(PRINTSIZE, EscData.Pos.y, -PRINTSIZE);

    //法線ベクトルの設定
    pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

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

    SetpVtx(pVtx);//格納
}

//=============================
// Object生成
//=============================
CDebugwall* CDebugwall::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 rot)
{
    CDebugwall* pObject3D = new CDebugwall;
    pObject3D->SetPos_Rot(Pos, rot);
    pObject3D->Init();
    return pObject3D;
}