//=======================================================
//
// LockOnUIMainに関する処理[LockOnUIMain.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "LockOnUIMain.h"
#include "renderer.h"
#include "manager.h"
#include "player_motion.h"

//=============================
// コンストラクタ
//=============================
CLockOnUIMain::CLockOnUIMain(int nPriority) :CObjectBillBoard(nPriority)
{
}

//=============================
// デストラクタ
//=============================
CLockOnUIMain::~CLockOnUIMain()
{
    Uninit();
}

//=============================
// 初期設定(頂点バッファ生成)
//=============================
HRESULT CLockOnUIMain::Init()
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

    BindVtxBuffer(ESCpVtxBuff);//バッファ格納

    //テクスチャ読み込み
    LPDIRECT3DTEXTURE9	m_ESCpTexture = nullptr;

    //テクスチャ取得
    CAllTexture* pTexture = pManager->GetTexture();

    int texIndex = pTexture->Regist("DATA\\TEXTURE\\LockOn003.png", EscDevice);//テクスチャ登録

    m_ESCpTexture = pTexture->GetAddress(texIndex);//テクスチャのアドレスを取得

    BindTexture(m_ESCpTexture);//格納

    SetObjectType(CObject::OBJECT_LOCKONUIMAIN);

    return S_OK;
}

//=============================
// 終了処理(頂点バッファ破棄)
//=============================
void CLockOnUIMain::Uninit()
{
    CObjectBillBoard::Uninit();
}

//=============================
// 更新(頂点情報の更新)
//=============================
void CLockOnUIMain::Update()
{
    InputpVtx();

    CObjectBillBoard::Update();
}

//=============================
// 描画処理(POLYGON描画)
//=============================
void CLockOnUIMain::Draw()
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
void CLockOnUIMain::SetPos(D3DXVECTOR3 Pos)
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
void CLockOnUIMain::InputpVtx()
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
CLockOnUIMain* CLockOnUIMain::Create()
{
    CLockOnUIMain* pObject3D = new CLockOnUIMain;

    pObject3D->Init();
 
    return pObject3D;
}