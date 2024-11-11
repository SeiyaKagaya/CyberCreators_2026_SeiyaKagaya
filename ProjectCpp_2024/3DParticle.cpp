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
CObject3DParticle::CObject3DParticle(int nPriority) :CObjectBillBoard(nPriority)
{
    SetObjectType(CObject::OBJECT_3DPARTICLE);
    ChengeAddDrawMode(true);
    // m_pVtxBuff = nullptr;
    // m_pTexture = nullptr;

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
    //int texIndex = pTexture->Regist("DATA\\TEXTURE\\explosion000.png", EscDevice);//テクスチャ登録

    m_ESCpTexture = pTexture->GetAddress(texIndex);

    BindTexture(m_ESCpTexture);//設定


 //   SetpVtx(pVtx);

  //  InputpVtx();
    m_nLife = START_LIFE;
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
    InputpVtx();

      m_nLife--;






    if (m_nLife <= 0 )
    {
        SetDeath(true);
    }



    CObjectBillBoard::Update();
}
//=============================
// 描画処理(POLYGON描画)
//=============================
void CObject3DParticle::Draw()
{
    CObjectBillBoard::Draw();
}
//=============================
// 座標設定
//=============================
void CObject3DParticle::SetPos_Rot(D3DXVECTOR3 Pos)
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
    //pVtx[0].pos = D3DXVECTOR3((float)-PRINTSIZE_X, 10.0f, (float)PRINTSIZE_Z);
    //pVtx[1].pos = D3DXVECTOR3((float)PRINTSIZE_X, 10.0f, (float)PRINTSIZE_Z);
    //pVtx[2].pos = D3DXVECTOR3((float)-PRINTSIZE_X, 10.0f, (float)-PRINTSIZE_Z);
    //pVtx[3].pos = D3DXVECTOR3((float)PRINTSIZE_X, 10.0f, (float)-PRINTSIZE_Z);

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

    ////法線ベクトルの設定
    //pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    //pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    //pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    //pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    
    //テクスチャ座標を設定
    //pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//左上
    //pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//右上
    //pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//左下
    //pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//右下
    
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



    //   ESCpVtxBuff->Unlock();

   //    BindVtxBuffer(ESCpVtxBuff);

    SetpVtx(pVtx);
}
void CObject3DParticle::SetCOL(D3DXCOLOR col)
{
    m_col = col;
}
//=============================
// Object生成
//=============================
CObject3DParticle* CObject3DParticle::Create(D3DXVECTOR3 Pos,D3DXCOLOR col)
{
    CObject3DParticle* pObject3D = new CObject3DParticle;
    pObject3D->SetPos_Rot(Pos);
    pObject3D->Init();
    pObject3D->SetCOL(col);
    return pObject3D;
}
