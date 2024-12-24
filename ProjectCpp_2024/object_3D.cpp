//=======================================================
//
// object3Dに関する処理[object3D.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "object3D.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "all_texture.h"

//=============================
// コンストラクタ
//=============================
CObject3D::CObject3D(int nPriority) :CObject(nPriority)
{
    SetObjectType(CObject::OBJECT_OBJECT3D);
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

}
//=============================
// デストラクタ
//=============================
CObject3D::~CObject3D()
{
    Uninit();
}
//=============================
// 初期設定(頂点バッファ生成)
//=============================
HRESULT CObject3D::Init()
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
#if 0

    float fTest = 2400.0f;
    float fTest2 = 3300.0f;

    //頂点座標の設定
    pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, fTest);
    pVtx[1].pos = D3DXVECTOR3(fTest2, 0.0f, fTest);
    pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    pVtx[3].pos = D3DXVECTOR3(fTest2, 0.0f, 0.0f);
#else

    D3DXVECTOR3 POS = D3DXVECTOR3(1700.0f, 0.0f, 1650.0f);




    float fTest = 4300.0f;


    CScene::MODE NowState = CScene::GetNowScene();

    if (NowState == CScene::MODE_GAME || NowState == CScene::MODE_GAME2 )
    {//ゲーム中

        float fTest = 9900.0f;
        float fTest2 = 9900.0f;

        //頂点座標の設定
        pVtx[0].pos = D3DXVECTOR3(0.0f, 30.0f, fTest);
        pVtx[1].pos = D3DXVECTOR3(fTest2, 30.0f, fTest);
        pVtx[2].pos = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
        pVtx[3].pos = D3DXVECTOR3(fTest2, 30.0f, 0.0f);


    }
    else if (NowState == CScene::MODE_TITLE)
    {//タイトル
        fTest = 13300.0f;
        //頂点座標の設定
        pVtx[0].pos = D3DXVECTOR3(POS.x - fTest, 0.0f, POS.z + fTest);
        pVtx[1].pos = D3DXVECTOR3(POS.x + fTest, 0.0f, POS.z + fTest);
        pVtx[2].pos = D3DXVECTOR3(POS.x - fTest, 0.0f, POS.z - fTest);
        pVtx[3].pos = D3DXVECTOR3(POS.x + fTest, 0.0f, POS.z - fTest);
    }
    else if (NowState == CScene::MODE_RESULT)
    {//タイトル mngasd
        fTest = 13300.0f;
        //頂点座標の設定
        pVtx[0].pos = D3DXVECTOR3(POS.x - fTest, 0.0f, POS.z + fTest);
        pVtx[1].pos = D3DXVECTOR3(POS.x + fTest, 0.0f, POS.z + fTest);
        pVtx[2].pos = D3DXVECTOR3(POS.x - fTest, 0.0f, POS.z - fTest);
        pVtx[3].pos = D3DXVECTOR3(POS.x + fTest, 0.0f, POS.z - fTest);
    }


   
#endif // 0



    //法線ベクトルの設定
    pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

    //頂点カラーの設定
    pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
    pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
    pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
    pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

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

   int texIndex = pTexture->Regist("DATA\\TEXTURE\\koke.png", EscDevice);//テクスチャ登録
 //   int texIndex = pTexture->Regist("DATA\\TEXTURE\\umi1.jpg", EscDevice);//テクスチャ登録


    

    m_ESCpTexture = pTexture->GetAddress(texIndex);

    BindTexture(m_ESCpTexture);//設定


    SetpVtx(pVtx);

    return S_OK;
}
//=============================
// 終了処理(頂点バッファ破棄)
//=============================
void CObject3D::Uninit()
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
void CObject3D::Update()
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
void CObject3D::Draw()
{
    CRenderer* pRenderer = nullptr;

    CManager* pManager = CManager::GetInstance();

    pRenderer = pManager->GetRenderer();

    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();


    D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス

    CScene::MODE NowState = CScene::GetNowScene();

    if (NowState == CScene::MODE_GAME || NowState == CScene::MODE_GAME2 )
    {//ゲーム中

        
    }
    else if (NowState == CScene::MODE_TITLE)
    {//タイトル

        m_texOffsetX -= 0.0008f;
       // m_texOffsetY += 0.01f;

            // テクスチャ変換行列
        D3DXMATRIX matTexTransform;
        D3DXMatrixIdentity(&matTexTransform);
    //    D3DXMatrixScaling(&matTexTransform,1.0f, 1.0f, 1.0f);  // 0.5倍にスケーリング
        matTexTransform._31 = m_texOffsetX; // X方向のオフセット設定
        matTexTransform._32 = m_texOffsetY; // Y方向のオフセット設定

                                            // テクスチャ行列のスケーリングを設定（0.5fでテクスチャ範囲を半分に）



        // テクスチャ変換を有効にする
        EscDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2); // 2D変換
        EscDevice->SetTransform(D3DTS_TEXTURE0, &matTexTransform);  // テクスチャ行列を設定


    }
    else if (NowState == CScene::MODE_RESULT)
    {//タイトル

        if (CScene::GetStageClear() == true)
        {
            m_texOffsetX += 0.0008f;
            // m_texOffsetY += 0.01f;
        }

             // テクスチャ変換行列
        D3DXMATRIX matTexTransform;
        D3DXMatrixIdentity(&matTexTransform);
        //    D3DXMatrixScaling(&matTexTransform,1.0f, 1.0f, 1.0f);  // 0.5倍にスケーリング
        matTexTransform._31 = m_texOffsetX; // X方向のオフセット設定
        matTexTransform._32 = m_texOffsetY; // Y方向のオフセット設定

                                            // テクスチャ行列のスケーリングを設定（0.5fでテクスチャ範囲を半分に）



        // テクスチャ変換を有効にする
        EscDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2); // 2D変換
        EscDevice->SetTransform(D3DTS_TEXTURE0, &matTexTransform);  // テクスチャ行列を設定


    }






    //ワールドマトリックスの初期化
    D3DXMatrixIdentity(&m_mtxWorld);

    //向きを反映
    D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Data.rot.y, m_Data.rot.x, m_Data.rot.z);

    D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

    //位置を反映
    D3DXMatrixTranslation(&mtxTrans, m_Data.Pos.x, m_Data.Pos.y, m_Data.Pos.z);

    D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

    //ワールドマトリックスの設定
    EscDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

    //頂点バッファをデータストリームに設定
    EscDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

    //頂点フォーマットの設定
    EscDevice->SetFVF(FVF_VERTEX_3D);

    //テクスチャの設定

    EscDevice->SetTexture(0, m_pTexture);

    //ポリゴンの描画
    EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
        0,//描画する最初の頂点インデックス
        2);//描画するプリミティブ数



    if (NowState == CScene::MODE_GAME || NowState == CScene::MODE_GAME2 )
    {//ゲーム中
    }
    else if (NowState == CScene::MODE_TITLE)
    {//タイトル
        EscDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE); // テクスチャ変換を無効にする
    }

}
//=============================
// Object生成
//=============================
CObject3D* CObject3D::Create()
{
    CObject3D* pObject3D = new CObject3D;
    pObject3D->Init();
    return pObject3D;
}
//=============================
// テクスチャ設定
//=============================
void CObject3D::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
    m_pTexture = pTex;
}
//=============================
// テクスチャ取得
//=============================
LPDIRECT3DTEXTURE9 CObject3D::GetTexture()
{
    return m_pTexture;
}
//=============================
// バッファ設定
//=============================
void CObject3D::BindVtxBuffer(LPDIRECT3DVERTEXBUFFER9 pVtx)
{
    m_pVtxBuff = pVtx;
}
//=============================
// バッファ取得
//=============================
LPDIRECT3DVERTEXBUFFER9 CObject3D::GetpVtxBuffer()
{
    return m_pVtxBuff;
}
//=============================
// 基礎情報取得
//=============================
CObject3D::DATA CObject3D::GetDATA()
{
    return m_Data;
}
//=============================
// 基礎情報設定
//=============================
void CObject3D::SetDATA(DATA data)
{
    m_Data = data;
}
//=============================
// 色変更
//=============================
void CObject3D::ChangeRGBA(D3DCOLOR col)
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
void CObject3D::ChengeAddDrawMode(bool bSet)
{
    m_AddDrawMode = bSet;
}
//=============================
// 頂点、テクスチャ座標切り替え
//=============================
void CObject3D::SetpVtx(VERTEX_3D pVtx[BASE_INDEX])
{
    for (int nCnt = 0; nCnt < BASE_INDEX; nCnt++)
    {
        m_pVtx[nCnt] = pVtx[nCnt];
    }
}
//=============================
// 頂点座標入れ
//=============================
void CObject3D::InputpVtx()
{
}
