//=======================================================
//
// Explosion3Dに関する処理[Explosion3D.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "Explosion3D.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "all_texture.h"
#include <stdio.h>


//あやしいcppのせんとうにこいつを
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

//=============================
// コンストラクタ
//=============================
Explosion3D::Explosion3D(int nPriority) :CObject(nPriority)
{
    for (int i = 0; i < MAXMAT; i++)
    {
        m_bFast[i] = false;

    }

    m_nLife = 60;

    m_pMesh = nullptr;
    m_pBuffMat = nullptr;
    m_dwNumMat = 0;

    m_SizeMag = D3DXVECTOR3(1.0f, 1.0f, 1.0f);//倍率格納(1.0が平均)
    m_ChangeCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

    m_bMagChange = true;//倍率変動


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
   /* for (int nCnt = 0; nCnt < MAX_TEXTURE_XFILE; nCnt++)
    {
        if (m_pTexture[nCnt] != nullptr)
        {
            m_pTexture[nCnt] = nullptr;
        }
    }*/
#endif


}
//=============================
// デストラクタ
//=============================
Explosion3D::~Explosion3D()
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
    //// テクスチャの破棄
    //for (int nCnt = 0; nCnt < MAX_TEXTURE_XFILE; nCnt++)
    //{
    //    if (m_pTexture[nCnt] != nullptr)
    //    {
    //        m_pTexture[nCnt]->Release();
    //        m_pTexture[nCnt] = nullptr; // 解放後に nullptr を設定
    //    }
    //}
#endif
    Uninit();
}
//=============================
// 初期設定(頂点バッファ生成)
//=============================
HRESULT Explosion3D::Init()
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
    D3DXLoadMeshFromX("DATA\\MODEL\\Sphere.x",
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

    m_SetSize = D3DXVECTOR3(3.0f, 3.0f, 3.0f);
    SetSizeMag(m_SetSize);//大きさ倍率
    //仮で大きくする

    //仮
    m_Data.MinLength = D3DXVECTOR3(-50.0f, 0.0f, -50.0f);
    m_Data.MaxLength = D3DXVECTOR3(50.0f, 50.0f, 50.0f);

    //テクスチャ取得
    CAllTexture* pTexture = pManager->GetTexture();

    int texIndex = pTexture->Regist("DATA\\TEXTURE\\EXPLOSION3D_2.png", EscDevice);//テクスチャ登録


    m_ESCpTexture = pTexture->GetAddress(texIndex);

    //////テクスチャ読み込み
    //LPDIRECT3DTEXTURE9	m_ESCpTexture = CAllTexture::GetTexture(CObject::OBJECT_EXPLOSION, EscDevice);

    //BindTexture(m_ESCpTexture);//設定

    m_Data.rot.y = 4.5f;
    m_Data.rot.x = 4.5f;

    CSound* pSound = pManager->GetSound();
  //  pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);


    return S_OK;
}
//=============================
// 終了処理(頂点バッファ破棄)
//=============================
void Explosion3D::Uninit()
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
    //// テクスチャの破棄
    //for (int nCnt = 0; nCnt < MAX_TEXTURE_XFILE; nCnt++)
    //{
    //    if (m_pTexture[nCnt] != nullptr)
    //    {
    //  //      m_pTexture[nCnt]->Release();//texture
    //        m_pTexture[nCnt] = nullptr; // 解放後に nullptr を設定
    //    }
    //}
#endif
}
//=============================
// 更新(頂点情報の更新)
//=============================
void Explosion3D::Update()
{
    //m_nCnt++;
    //if (m_nCnt >= 10)
    //{
        
    CManager* pManager = CManager::GetInstance();

    if (m_nCnt<=18)
    {

        pManager->GetCamera()->SetShake(85, 85);
     
        m_SetSize.x += 2.3f;
        m_SetSize.y += 2.3f;
        m_SetSize.z += 2.3f;
    }
    else if(m_nCnt > 18 || m_nCnt <= 40)
    {
        pManager->GetCamera()->SetShake(55, 55);

        m_SetSize.x += 0.7f;
        m_SetSize.y += 0.7f;
        m_SetSize.z += 0.7f;
    }
    else
    {
        pManager->GetCamera()->SetShake(5, 5);

        m_SetSize.x += 0.3f;
        m_SetSize.y += 0.3f;
        m_SetSize.z += 0.3f;
    }

    
    SetSizeMag(m_SetSize);//大きさ倍率
    
    m_Data.rot.y += 0.03f;
    m_Data.rot.x += 0.03f;

    m_nCnt++;
        // テクスチャオフセットの更新 (アニメーション速度)
        m_texOffsetX += (1.0f / (float)ANIMNUM);  // X方向に少しずつ移動
     
                                                  
        if (m_nCnt >= 60)
        {
            m_texOffsetX = 0.0f;

            m_nCnt = 0;
        }
                                                  
                                                  //   m_texOffsetY += 0.01f;  // Y方向に少しずつ移動
 //   }
 
    // 残りの通常の更新処理
    m_nLife--;
    if (m_nLife <= 0)
    {
        SetDeath(true);
    }
}
//=============================
// 描画処理(POLYGON描画)
//=============================
void Explosion3D::Draw()
{
    // デバイスの取得
    CManager* pManager = CManager::GetInstance();
    CRenderer* pRenderer = pManager->GetRenderer();
    LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

    if (!pDevice || !m_pMesh)
    {
        return; // 無効な場合は描画をスキップ
    }

    // 現在のステートのバックアップ
    IDirect3DBaseTexture9* pPrevTexture = nullptr; // 基底型ポインタを使用
    pDevice->GetTexture(0, &pPrevTexture);

    D3DMATERIAL9 prevMaterial;
    pDevice->GetMaterial(&prevMaterial);

    DWORD prevCullMode;
    pDevice->GetRenderState(D3DRS_CULLMODE, &prevCullMode);

    D3DXMATRIX prevWorldMatrix;
    pDevice->GetTransform(D3DTS_WORLD, &prevWorldMatrix);

    D3DXMATRIX prevTexTransform;
    pDevice->GetTransform(D3DTS_TEXTURE0, &prevTexTransform); // テクスチャ変換行列をバックアップ

    DWORD prevTexTransformFlags;
    pDevice->GetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, &prevTexTransformFlags); // テクスチャ変換フラグをバックアップ

    // ワールド行列設定
    D3DXMATRIX matScale, matRot, matTrans, matWorld;
    D3DXMatrixScaling(&matScale, m_SetSize.x, m_SetSize.y, m_SetSize.z);
    D3DXMatrixRotationYawPitchRoll(&matRot, m_Data.rot.y, m_Data.rot.x, m_Data.rot.z);
    D3DXMatrixTranslation(&matTrans, m_Data.Pos.x, m_Data.Pos.y, m_Data.Pos.z);
    matWorld = matScale * matRot * matTrans;
    pDevice->SetTransform(D3DTS_WORLD, &matWorld);

    // カリングモード無効化
    pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

    // マテリアルとテクスチャの設定
    D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
    for (DWORD i = 0; i < m_dwNumMat; ++i)
    {
        if (m_bFast[i] == false)
        {
            m_bFast[i] = true;
            m_OriginalColor[i] = pMat[i].MatD3D.Diffuse;
        }

        pMat[i].MatD3D.Diffuse = D3DXCOLOR(
            m_OriginalColor[i].r * m_SizeMag.x,
            m_OriginalColor[i].g * m_SizeMag.y,
            m_OriginalColor[i].b * m_SizeMag.z,
            m_OriginalColor[i].a
        );

        pDevice->SetMaterial(&pMat[i].MatD3D);
        pMat[i].MatD3D.Diffuse = m_OriginalColor[i];

        // テクスチャ変換行列の設定
        D3DXMATRIX matTexTransform;
        D3DXMatrixScaling(&matTexTransform, (1.0f / (float)ANIMNUM), 1.0f, 1.0f);  // スケーリング
        matTexTransform._31 = m_texOffsetX; // X方向のオフセット設定
        matTexTransform._32 = m_texOffsetY; // Y方向のオフセット設定

        // テクスチャ変換を有効にする
        pDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2); // 2D変換
        pDevice->SetTransform(D3DTS_TEXTURE0, &matTexTransform);  // テクスチャ行列を設定

        if (m_ESCpTexture)
        {
            pDevice->SetTexture(0, m_ESCpTexture);
        }
        else
        {
            pDevice->SetTexture(0, nullptr);
        }

        m_pMesh->DrawSubset(i);
    }

    // ステートの復元
    pDevice->SetTexture(0, pPrevTexture);
    if (pPrevTexture)
    {
        pPrevTexture->Release();
    }

    pDevice->SetMaterial(&prevMaterial);
    pDevice->SetRenderState(D3DRS_CULLMODE, prevCullMode);
    pDevice->SetTransform(D3DTS_WORLD, &prevWorldMatrix);

    // テクスチャ変換行列とフラグの復元
    pDevice->SetTransform(D3DTS_TEXTURE0, &prevTexTransform);
    pDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, prevTexTransformFlags);

}
//=============================
// Object生成
//=============================
Explosion3D* Explosion3D::Create(D3DXVECTOR3 Pos)
{
    Explosion3D* pObjectX = new Explosion3D;
    pObjectX->Init();
    pObjectX->SetPos(Pos);
    return pObjectX;
}

//=============================
// サイズ変動の有無
//=============================
void Explosion3D::SizeMagChangebool(bool bChange)
{
    m_bMagChange = bChange;
}
//=============================
// 描画処理(POLYGON描画)
//=============================
void Explosion3D::SetSizeMag(D3DXVECTOR3 SizeMag)
{
    m_SizeMag = SizeMag;
}
void Explosion3D::SetPos(D3DXVECTOR3 pos)
{
    m_Data.Pos = pos;
}
