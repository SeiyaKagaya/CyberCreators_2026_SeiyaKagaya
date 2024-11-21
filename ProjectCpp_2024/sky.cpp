//=======================================================
//
// Sky3Dに関する処理[Sky3D.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "sky.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "all_texture.h"
#include <stdio.h>

//=============================
// コンストラクタ
//=============================
Sky3D::Sky3D(int nPriority) :CObject(nPriority)
{
 //   m_nLife = 60;

    m_pMesh = nullptr;
    m_pBuffMat = nullptr;
    m_dwNumMat = 0;

    m_SizeMag = D3DXVECTOR3(1.0f, 1.0f, 1.0f);//倍率格納(1.0が平均)
    m_ChangeCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

    m_bMagChange = true;//倍率変動
    m_Data.rot.x = 0.0f;


#if 0
    for (int nCnt = 0; nCnt < MAX_TEXTURE_XFILE; nCnt++)
    {
        m_pTexture[nCnt] = new LPDIRECT3DTEXTURE9();

        if (*m_pTexture[nCnt] != nullptr)
        {
            *m_pTexture[nCnt] = nullptr;
        }
    }
#else
    for (int nCnt = 0; nCnt < MAX_TEXTURE_XFILE; nCnt++)
    {
        if (m_pTexture[nCnt] != nullptr)
        {
            m_pTexture[nCnt] = nullptr;
        }
    }
#endif

    //  m_bModelParts = false;
}
//=============================
// デストラクタ
//=============================
Sky3D::~Sky3D()
{
#if 0
    // テクスチャの破棄
    for (int nCnt = 0; nCnt < MAX_TEXTURE_XFILE; nCnt++)
    {
        if (m_pTexture[nCnt] != nullptr)
        {
            delete m_pTexture[nCnt];
            m_pTexture[nCnt] = nullptr;
        }
    }
#else
    // テクスチャの破棄
    for (int nCnt = 0; nCnt < MAX_TEXTURE_XFILE; nCnt++)
    {
        if (m_pTexture[nCnt] != nullptr)
        {
            m_pTexture[nCnt]->Release();
            m_pTexture[nCnt] = nullptr; // 解放後に nullptr を設定
        }
    }
#endif
    Uninit();
}
//=============================
// 初期設定(頂点バッファ生成)
//=============================
HRESULT Sky3D::Init()
{
    m_Data.Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.OldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.MinLength = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.MaxLength = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.Radius = 0.0f;


    SetObjectType(CObject::OBJECT_EXPLOSION3D);


    CRenderer* pRenderer = nullptr;

    CManager* pManager = CManager::GetInstance();

    pRenderer = pManager->GetRenderer();

    //    LPD3DXMESH pMesh = nullptr;//Meshポインタ
    //    LPD3DXBUFFER pBuffMat = nullptr;//マテリアルへのポインタ
      //  DWORD dwNumMat = 0;//マテリアルの数

    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();
    //ファイルの読み込み
    D3DXLoadMeshFromX("DATA\\MODEL\\SKY.x",
        D3DXMESH_SYSTEMMEM,
        EscDevice,
        NULL,
        &m_pBuffMat,
        NULL,
        &m_dwNumMat,
        &m_pMesh);

    //マテリアルデータへのポインタを取得
    D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

    for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
    {
        // ディフューズカラーをサイズに基づいて変更
        D3DXCOLOR originalColor = pMat[nCntMat].MatD3D.Diffuse;

        pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//色をここで指定
    }

    //   SetXfireData(m_pMesh, m_pBuffMat, m_dwNumMat);//データ格納

       //// SetXfireDataの直後での確認
       //if (pBuffMat == nullptr)
       //{
       //    MessageBox(NULL, "m_pBuffMat is nullptr after SetXfireData in Init", "Error", MB_OK);
       //}
       //else 
       //{
       //    MessageBox(NULL, "m_pBuffMat is valid after SetXfireData in Init", "Info", MB_OK);
       //}


     //  SetObjectType(CObject::OBJECT_BLOCK3D);

    m_SetSize = D3DXVECTOR3(5.0f, 5.0f, 5.0f);
    SetSizeMag(m_SetSize);//大きさ倍率
    //仮で大きくする

    //仮
    m_Data.MinLength = D3DXVECTOR3(-50.0f, 0.0f, -50.0f);
    m_Data.MaxLength = D3DXVECTOR3(50.0f, 50.0f, 50.0f);

    //テクスチャ取得
    CAllTexture* pTexture = pManager->GetTexture();

    int texIndex = pTexture->Regist("DATA\\TEXTURE\\title000.png", EscDevice);//テクスチャ登録


    m_ESCpTexture = pTexture->GetAddress(texIndex);

    //////テクスチャ読み込み
    //LPDIRECT3DTEXTURE9	m_ESCpTexture = CAllTexture::GetTexture(CObject::OBJECT_EXPLOSION, EscDevice);

    //BindTexture(m_ESCpTexture);//設定
    m_Data.rot.x = D3DX_PI;
    m_Data.rot.y = D3DX_PI*0.2f;


    CSound* pSound = pManager->GetSound();
    //  pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);


    return S_OK;
}
//=============================
// 終了処理(頂点バッファ破棄)
//=============================
void Sky3D::Uninit()
{
    //メッシュの破棄
    if (m_pMesh != nullptr)
    {
        m_pMesh->Release();
        m_pMesh = nullptr;
    }
    //マテリアルの破棄
    if (m_pBuffMat != nullptr)
    {
        m_pBuffMat->Release();
        m_pBuffMat = nullptr;
    }

#if 1
    // テクスチャの破棄
    for (int nCnt = 0; nCnt < MAX_TEXTURE_XFILE; nCnt++)
    {
        if (m_pTexture[nCnt] != nullptr)
        {
            m_pTexture[nCnt]->Release();
            m_pTexture[nCnt] = nullptr; // 解放後に nullptr を設定
        }
    }
#endif
}
//=============================
// 更新(頂点情報の更新)
//=============================
void Sky3D::Update()
{
    m_Data.Pos = CCamera::GetCameraPos();

    
    CManager* pManager = CManager::GetInstance();

  

    //SetSizeMag(m_SetSize);//大きさ倍率

    m_Data.rot.y += 0.0001f;


    //m_nCnt++;
    //// テクスチャオフセットの更新 (アニメーション速度)
    //m_texOffsetX += (1.0f / (float)ANIMNUM);  // X方向に少しずつ移動

    /*if (m_nCnt >= ANIMNUM)
    {
        m_texOffsetX = 0.0f;

        m_nCnt = 0;
    }*/
}
//=============================
// 描画処理(POLYGON描画)
//=============================
void Sky3D::Draw()
{
    CRenderer* pRenderer = nullptr;
    CManager* pManager = CManager::GetInstance();
    pRenderer = pManager->GetRenderer();
    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();


    D3DXMATRIX mtxRot, mtxTrans;

    // テクスチャ変換行列
    D3DXMATRIX matTexTransform;




    // Zバッファを有効化
//    EscDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);

    // Zバッファへの書き込みを有効化
 //   EscDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

    // カリング（裏面の非表示）を設定（オプション）
 //   EscDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);









    //D3DXMatrixScaling(&matTexTransform, (1.0f / (float)ANIMNUM), 1.0f, 1.0f);  // 0.5倍にスケーリング
    //matTexTransform._31 = m_texOffsetX; // X方向のオフセット設定
    //matTexTransform._32 = m_texOffsetY; // Y方向のオフセット設定

    //// テクスチャ変換を有効にする
    //EscDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2); // 2D変換
    //EscDevice->SetTransform(D3DTS_TEXTURE0, &matTexTransform);  // テクスチャ行列を設定


    // ワールドマトリックスの初期化
    D3DXMatrixIdentity(&m_mtxWorld);


    if (m_bMagChange == true)
    {
        // モデルのサイズを変更

        D3DXMatrixScaling(&m_mtxWorld, m_SizeMag.x, m_SizeMag.y, m_SizeMag.z);
    }

    // 向きを反映
    D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Data.rot.y, m_Data.rot.x, m_Data.rot.z);
    D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

    // 位置を反映
    D3DXMatrixTranslation(&mtxTrans, m_Data.Pos.x, m_Data.Pos.y, m_Data.Pos.z);
    D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

    D3DMATERIAL9 matDef;
    D3DXMATERIAL* pMat;

    // ワールドマトリックスの設定
    EscDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
    // 頂点フォーマットの設定
    EscDevice->SetFVF(FVF_VERTEX_3D);
    // 現在のマテリアルを取得
    EscDevice->GetMaterial(&matDef);

    // 通常のオブジェクトの描画
    if (m_pBuffMat != nullptr)
    {
        pMat = reinterpret_cast<D3DXMATERIAL*>(m_pBuffMat->GetBufferPointer());

        for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
        {
            // ワールド行列を元に戻す
            EscDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

            // マテリアルの設定
            EscDevice->SetMaterial(&pMat[nCntMat].MatD3D);


            pMat[nCntMat].pTextureFilename = NULL;

            EscDevice->SetTexture(0, m_ESCpTexture);

            if (bFast == false)
            {//始めの一回のみ
                m_OriginalColor = pMat[nCntMat].MatD3D.Diffuse;
                bFast = true;
            }


            // メッシュの描画
            if (m_bMagChange == true)
            {
                D3DXCOLOR originalColor;

                if (m_ChangeColorBool == true)
                {
                    originalColor = m_ChangeCol;
                }
                else
                {
                    originalColor = m_OriginalColor;
                }

                //if (m_nCnt >= 40)
                //{//透過率
                //    originalColor.a = ((float)60 - m_nCnt) * 0.5f;
                //}

                pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(
                    originalColor.r * m_SizeMag.x,
                    originalColor.g * m_SizeMag.y,
                    originalColor.b * m_SizeMag.z,
                    originalColor.a
                );

                EscDevice->SetMaterial(&pMat[nCntMat].MatD3D);
                pMat[nCntMat].MatD3D.Diffuse = originalColor;

            }
            else
            {
            }

            m_pMesh->DrawSubset(nCntMat);

            // 保存していたマテリアルを戻す
            EscDevice->SetMaterial(&matDef);
        }

    }

    EscDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE); // テクスチャ変換を無効にする


    // Zバッファを無効化
  //  EscDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);

    // Zバッファへの書き込みを無効化
 //   EscDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

    // カリングを無効化（オプション）
 //   EscDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

}
//=============================
// Object生成
//=============================
Sky3D* Sky3D::Create(D3DXVECTOR3 Pos)
{
    Sky3D* pObjectX = new Sky3D;
    pObjectX->Init();
    pObjectX->SetPos(Pos);
    return pObjectX;
}

//=============================
// サイズ変動の有無
//=============================
void Sky3D::SizeMagChangebool(bool bChange)
{
    m_bMagChange = bChange;
}
//=============================
// 描画処理(POLYGON描画)
//=============================
void Sky3D::SetSizeMag(D3DXVECTOR3 SizeMag)
{
    m_SizeMag = SizeMag;
}
//=============================
// 座標格納
//=============================
void Sky3D::SetPos(D3DXVECTOR3 pos)
{
    m_Data.Pos = pos;
}
