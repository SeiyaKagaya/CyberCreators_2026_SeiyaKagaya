//=======================================================
//
// seaに関する処理[sea.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "sea.h"
#include "renderer.h"
#include "manager.h"

//=============================
// コンストラクタ
//=============================
CSea::CSea(int nPriority) :CObject3D(nPriority)
{
    SetObjectType(CObject::OBJECT_SEA);
}

//=============================
// デストラクタ
//=============================
CSea::~CSea()
{
    Uninit();
}

//=============================
// 初期設定(頂点バッファ生成)
//=============================
HRESULT CSea::Init()
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

    int texIndex = pTexture->Regist("DATA\\TEXTURE\\umi1.jpg", EscDevice);//テクスチャ登録

    m_ESCpTexture = pTexture->GetAddress(texIndex);//テクスチャのアドレスを格納

    BindTexture(m_ESCpTexture);//設定

    return S_OK;
}

//=============================
// 終了処理(頂点バッファ破棄)
//=============================
void CSea::Uninit()
{ 
    CObject3D::Uninit();
}

//=============================
// 更新(頂点情報の更新)
//=============================
void CSea::Update()
{
    InputpVtx();//頂点情報を更新し格納

    CScene::MODE NowState = CScene::GetNowScene();

    if (NowState == CScene::MODE_GAME || NowState == CScene::MODE_GAME2 || NowState == CScene::MODE_GAME3 || NowState == CScene::MODE_MOVIE || NowState == CScene::MODE_MOVIE2)
    {//ゲーム中

     // テクスチャオフセットの更新 (アニメーション速度)
        m_texOffsetX += TEXMOVE_X1;  // X方向に少しずつ移動
        m_texOffsetY += TEXMOVE_Y1;  // X方向に少しずつ移動

    }
    else if (NowState == CScene::MODE_OP)
    {//出撃前演出
        // テクスチャオフセットの更新 (アニメーション速度)
        m_texOffsetX += TEXMOVE_X2;  // X方向に少しずつ移動
        m_texOffsetY += TEXMOVE_Y2;  // X方向に少しずつ移動
    }

    CObject3D::Update();
}

//=============================
// 描画処理(POLYGON描画)
//=============================
void CSea::Draw()
{
    CRenderer* pRenderer = nullptr;
    CManager* pManager = CManager::GetInstance();
    pRenderer = pManager->GetRenderer();
    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

    D3DXMATRIX mtxRot, mtxTrans;

    // テクスチャ変換行列
    D3DXMATRIX matTexTransform;

    D3DXMatrixScaling(&matTexTransform, 1.0f, 1.0f, 1.0f);  // 0.5倍にスケーリング
    matTexTransform._31 = m_texOffsetX; // X方向のオフセット設定
    matTexTransform._32 = m_texOffsetY; // Y方向のオフセット設定

    // テクスチャ変換を有効にする
    EscDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2); // 2D変換
    EscDevice->SetTransform(D3DTS_TEXTURE0, &matTexTransform);  // テクスチャ行列を設定

    CObject3D::Draw();

    EscDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE); // テクスチャ変換を無効にする
}

//=============================
// 座標設定
//=============================
void CSea::SetPos_Rot(D3DXVECTOR3 Pos, D3DXVECTOR3 rot)
{
    //取得
    DATA EscData = GetDATA();

    EscData.Pos = Pos;
    EscData.rot = rot;

    //取得
    SetDATA(EscData);
}

//=============================
// 頂点情報
//=============================
void CSea::InputpVtx()
{
    // 初期設定
    VERTEX_3D pVtx[BASE_INDEX];

    //取得
    DATA EscData = GetDATA();

    //頂点座標の設定
    pVtx[0].pos = D3DXVECTOR3(-PRINTSIZE, 0.0f, PRINTSIZE);
    pVtx[1].pos = D3DXVECTOR3(PRINTSIZE, 0.0f, PRINTSIZE);
    pVtx[2].pos = D3DXVECTOR3(-PRINTSIZE, 0.0f, -PRINTSIZE);
    pVtx[3].pos = D3DXVECTOR3(PRINTSIZE, 0.0f, -PRINTSIZE);

    //法線ベクトルの設定
    pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

    //頂点カラーの設定
    pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_rgbA);
    pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_rgbA);
    pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_rgbA);
    pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_rgbA);

    //テクスチャ座標を設定
    pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//左上
    pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//右上
    pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//左下
    pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//右下

    SetpVtx(pVtx);//頂点情報格納
}

//=============================
// Object生成
//=============================
CSea* CSea::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 rot, float rgbA)
{
    CSea* pObject3D = new CSea;
    pObject3D->SetPos_Rot(Pos, rot);
    pObject3D->Init();
    pObject3D->SetrgbA(rgbA);
    return pObject3D;
}