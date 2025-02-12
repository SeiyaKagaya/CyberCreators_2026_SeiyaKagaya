//=======================================================
//
// LockOnUIに関する処理[LockOnUI.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "LockOnUI.h"
#include "renderer.h"
#include "manager.h"
#include "player_motion.h"

//=============================
// コンストラクタ
//=============================
CLockOnUI::CLockOnUI(int nPriority) :CObjectBillBoard(nPriority)
{
}

//=============================
// デストラクタ
//=============================
CLockOnUI::~CLockOnUI()
{
    Uninit();
}

//=============================
// 初期設定(頂点バッファ生成)
//=============================
HRESULT CLockOnUI::Init()
{
    SetObjectType(CObject::OBJECT_LOCKONUI);

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

    int texIndex = pTexture->Regist("DATA\\TEXTURE\\LockOn000.png", EscDevice);//テクスチャ登録

    m_ESCpTexture = pTexture->GetAddress(texIndex);

    BindTexture(m_ESCpTexture);//設定

    SetObjectType(CObject::OBJECT_LOCKONUI);

    return S_OK;
}

//=============================
// 終了処理(頂点バッファ破棄)
//=============================
void CLockOnUI::Uninit()
{
    CObjectBillBoard::Uninit();
}

//=============================
// 更新(頂点情報の更新)
//=============================
void CLockOnUI::Update()
{
    InputpVtx();

    CObjectBillBoard::Update();
}

//=============================
// 描画処理(POLYGON描画)
//=============================
void CLockOnUI::Draw()
{
    if (m_bDrawOk == true)
    {
        SetZDrawDeth(true);
        SetLight(true);
        CObjectBillBoard::Draw();
        SetZDrawDeth(false);
    }
}

//=============================
// 座標設定
//=============================
void CLockOnUI::SetPos(D3DXVECTOR3 Pos)
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
void CLockOnUI::InputpVtx()
{
    // 初期設定
    VERTEX_3D pVtx[BASE_INDEX];

    //取得
    DATA EscData = GetDATA();

     //頂点座標の設定
    pVtx[0].pos = D3DXVECTOR3(-PRINTSIZE, PRINTSIZE, 0.0f);
    pVtx[1].pos = D3DXVECTOR3(PRINTSIZE, PRINTSIZE, 0.0f);
    pVtx[2].pos = D3DXVECTOR3(-PRINTSIZE, -PRINTSIZE, 0.0f);
    pVtx[3].pos = D3DXVECTOR3(PRINTSIZE, -PRINTSIZE, 0.0f);


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
    pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//
    
    SetpVtx(pVtx);
}

//=============================
// Object生成
//=============================
CLockOnUI* CLockOnUI::Create()
{
    CLockOnUI* pObject3D = new CLockOnUI;

    pObject3D->Init();
    return pObject3D;
}
