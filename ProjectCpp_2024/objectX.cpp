//=======================================================
//
// objectXに関する処理[objectX.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "objectX.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "all_texture.h"
#include <stdio.h>

//=============================
// コンストラクタ
//=============================
CObjectX::CObjectX(int nPriority) :CObject(nPriority)
{
    m_Data.Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.OldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.MinLength = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.MaxLength = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.Radius = 0.0f;


    for (int i = 0; i < MAX_MAT; i++)
    {
        m_bFast[i] = false;

        m_OriginalColor[i] = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
    }

    m_pMesh = nullptr;
    m_pBuffMat = nullptr;
    m_dwNumMat = 0;

    m_SizeMag = D3DXVECTOR3(1.0f, 1.0f, 1.0f);//倍率格納(1.0が平均)
    m_ChangeCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

 //   m_bMagChange = true;//倍率変動
    

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

    m_bModelParts = false;
}
//=============================
// デストラクタ
//=============================
CObjectX::~CObjectX()
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
HRESULT CObjectX::Init()
{



    SetObjectType(CObject::OBJECT_OBJECT3D);

    return S_OK;
}
//=============================
// 終了処理(頂点バッファ破棄)
//=============================
void CObjectX::Uninit()
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

   // CObject::Uninit;
}
//=============================
// 更新(頂点情報の更新)
//=============================
void CObjectX::Update()
{

}
//=============================
// 描画処理(POLYGON描画)
//=============================
void CObjectX::Draw()
{
    CRenderer* pRenderer = nullptr;
    CManager* pManager = CManager::GetInstance();
    pRenderer = pManager->GetRenderer();
    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();
    D3DXMATRIX mtxRot, mtxTrans;


    // ワールドマトリックスの初期化
    D3DXMatrixIdentity(&m_mtxWorld);

    if (m_bModelParts == false)
    {//普通のモデルのとき

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
    }
    else
    {//モデルパーチのとき
        m_mtxWorld = m_ModelmtxWorld;
    }

    D3DMATERIAL9 matDef;
    D3DXMATERIAL* pMat;

    // ワールドマトリックスの設定
    EscDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
    // 頂点フォーマットの設定
    EscDevice->SetFVF(FVF_VERTEX_3D);
    // 現在のマテリアルを取得
    EscDevice->GetMaterial(&matDef);

    if (GetNotLight() == true)
    {
        // ライトを無効にする
        EscDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
    }

    // 通常のオブジェクトの描画
    if (m_pBuffMat != nullptr)
    {
        pMat = reinterpret_cast<D3DXMATERIAL*>(m_pBuffMat->GetBufferPointer());

        for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
        {
            if (m_bFast[nCntMat] == false)
            {
                m_bFast[nCntMat] = true;
                m_OriginalColor[nCntMat]= pMat[nCntMat].MatD3D.Diffuse;
            }

            // マテリアルの設定
            if (m_bMagChange == true)
            {
                D3DXCOLOR originalColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

                if (m_ChangeColorBool == true)
                {
                    originalColor = m_ChangeCol;
                }
                else
                {
                    originalColor = m_OriginalColor[nCntMat];
                }

                if (m_bStageTexChange == true)
                {
                    pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(200.0f, 200.0f, 200.0f, 200.0f);
                }
                else
                {
                    pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(
                        originalColor.r * m_SizeMag.x,
                        originalColor.g * m_SizeMag.y,
                        originalColor.b * m_SizeMag.z,
                        originalColor.a
                    );
                }

                EscDevice->SetMaterial(&pMat[nCntMat].MatD3D);
            }
            else
            {
                D3DXCOLOR originalColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

                if (m_ChangeColorBool == true)
                {
                    originalColor = m_ChangeCol;
                }
                else
                {
                    originalColor = m_OriginalColor[nCntMat];
                }

                pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(
                    originalColor.r,
                    originalColor.g,
                    originalColor.b,
                    originalColor.a);


                // 通常の色設定
                EscDevice->SetMaterial(&pMat[nCntMat].MatD3D);
            }

            // テクスチャの設定
            if (pMat[nCntMat].pTextureFilename != nullptr)
            {
           
                EscDevice->SetTexture(0, m_pTexture[nCntMat]);
//                EscDevice->SetTexture(0, nullptr);
            }
            else
            {
                EscDevice->SetTexture(0, nullptr);
            }

            // メッシュの描画
            m_pMesh->DrawSubset(nCntMat);

            // 保存していたマテリアルを戻す
            EscDevice->SetMaterial(&matDef);

            //リセット
             pMat[nCntMat].MatD3D.Diffuse = m_OriginalColor[nCntMat];
        }
    }

    if (GetNotLight() == true)
    {
        // ライトを有効にする
        EscDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
        SetNotLight(false);
    }
}
//=============================
// Object生成
//=============================
CObjectX* CObjectX::Create()
{
    CObjectX* pObjectX = new CObjectX;
    pObjectX->Init();
    return pObjectX;
}
//=============================
// データ格納
//=============================
void CObjectX::SetXfireData(LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD dwNumMat)
{
    
    m_pMesh = pMesh;//Meshポインタ
     m_pBuffMat = pBuffMat;//マテリア
     m_dwNumMat = dwNumMat;//マテリアルの数

}
//=============================
// サイズ変動の有無
//=============================
void CObjectX::SizeMagChangebool(bool bChange)
{
    m_bMagChange = bChange;
}
//=============================
// 描画処理(POLYGON描画)
//=============================
void CObjectX::SetSizeMag(D3DXVECTOR3 SizeMag)
{
    m_SizeMag = SizeMag;
}

D3DXVECTOR3 CObjectX::GetSizeMag()
{
    return m_SizeMag;
}

//=============================
// 基礎情報取得
//=============================
CObjectX::DATA CObjectX::GetDATA()
{
    return m_Data;
}
//=============================
// テクスチャ格納
//=============================
void CObjectX::BindTexture(LPDIRECT3DTEXTURE9 pTex, int Index)
{
    m_pTexture[Index] = pTex;
}
void CObjectX::ChangeModelPartsbool(bool parts)
{
    m_bModelParts = parts;
}
void CObjectX::SetModelMtxWorld(D3DXMATRIX mtx)
{
    m_ModelmtxWorld = mtx;
}
void CObjectX::SetColorChangeBool(bool ChangeColorBool)
{
    m_ChangeColorBool = ChangeColorBool;
}
void CObjectX::SetChangeColor(D3DXCOLOR ChangeCol)
{
   m_ChangeCol = ChangeCol;
}
void CObjectX::ChengeStageTex(bool Change)
{
    m_bStageTexChange = Change;
}
//=============================
// 基礎情報設定
//=============================
void CObjectX::SetDATA(DATA data)
{
    m_Data = data;
}