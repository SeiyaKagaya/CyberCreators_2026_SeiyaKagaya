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
    m_Data.Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.OldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.MinLength = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.MaxLength = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.Radius = 0.0f;


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

    //---------------------------------------
    //D3DXMATRIX mtxShadow; //影行列
    //D3DXPLANE plane; //平面情報
    //D3DXVECTOR4 vecLight; //ライト逆方向
    //D3DXVECTOR3 pos, nor; //平面上の一点と法線

    //// マトリックスの初期化
    //D3DXMatrixIdentity(&mtxShadow);

    //// ライトの逆方向ベクトルを設定
    //CLight* pLight = pManager->GetLight();
    //D3DXVECTOR3 EscVecLight = pLight->GetLightVec(0); //各ライトのベクトル
    //EscVecLight = EscVecLight * -1; //逆方向に
    //D3DXVec3Normalize(&EscVecLight, &EscVecLight); //ベクトルを正規化する

    //// ライトの逆方向ベクトル
    //vecLight = D3DXVECTOR4(EscVecLight.x, EscVecLight.y, EscVecLight.z, 0.0f);
    //pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    //nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f); // 平面の法線ベクトルが正しいか確認

    //// 法線と平面上の一点から平面情報を作成
    //D3DXPlaneFromPointNormal(&plane, &pos, &nor);
    //// ライトの平面情報から影行列を作成
    //D3DXMatrixShadow(&mtxShadow, &vecLight, &plane);

    //// ワールドマトリックスとかける
    //D3DXMatrixMultiply(&mtxShadow, &mtxShadow, &m_mtxWorld);




    // ワールドマトリックスの設定
    EscDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
    // 頂点フォーマットの設定
    EscDevice->SetFVF(FVF_VERTEX_3D);
    // 現在のマテリアルを取得
    EscDevice->GetMaterial(&matDef);




    //// 影の描画
    //if (m_pBuffMat != nullptr)
    //{
    //    // アルファブレンディングを加算合成に設定
    //    EscDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    //    EscDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
    //    EscDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    //    EscDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

    //    pMat = reinterpret_cast<D3DXMATERIAL*>(m_pBuffMat->GetBufferPointer());

    //    // 影の色を設定
    //    D3DMATERIAL9 shadowMaterial;
    //    ZeroMemory(&shadowMaterial, sizeof(D3DMATERIAL9));
    //    shadowMaterial.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.3f); // 半透明の黒




    //    for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
    //    {
    //        // ワールド行列を影行列に設定
    //        EscDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

    //        // 影のマテリアルを設定
    //        EscDevice->SetMaterial(&shadowMaterial);

    //        // テクスチャを無効にする
    //        EscDevice->SetTexture(0, nullptr);

    //        // メッシュの描画
    //        m_pMesh->DrawSubset(nCntMat);
    //    }


    //EscDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
    //EscDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    //EscDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    //EscDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
    //}

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
            // ワールド行列を元に戻す
            EscDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

            // マテリアルの設定
            EscDevice->SetMaterial(&pMat[nCntMat].MatD3D);

            // テクスチャの設定
            if (pMat[nCntMat].pTextureFilename != nullptr)
            {
                EscDevice->SetTexture(0, m_pTexture[nCntMat]);
            }
            else
            {
                EscDevice->SetTexture(0, nullptr);
            }

            if (bFast==false)
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
 
                if (m_bStageTexChange==true)
                {
                    pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(200.0f,200.0f,200.0f,200.0f);
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
                pMat[nCntMat].MatD3D.Diffuse = originalColor;

            }
         



            m_pMesh->DrawSubset(nCntMat);

            // 保存していたマテリアルを戻す
            EscDevice->SetMaterial(&matDef);
        }
    
    }


    if (GetNotLight() == true)
    {
        // ライトを有効にする
        EscDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
        SetNotLight(false);
        
    }

       //// アルファブレンディングを加算合成に設定
       //EscDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
       //EscDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
       //EscDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
       //EscDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

    ///----------------------------------------------------------------------

       //// アルファブレンディングを元に戻す
       //EscDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
       //EscDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
       //EscDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
       //EscDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

    /*   EscDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
       EscDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
       EscDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
       EscDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);*/















    ////アルファブレンディングをもとに戻す
    //EscDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
    //EscDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    //EscDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

    
    //// アルファブレンドを無効にする
    //EscDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);


   


    //----------------------------------------

    //        // ワールドマトリックスの設定
    //    EscDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
    //    // 頂点フォーマットの設定
    //    EscDevice->SetFVF(FVF_VERTEX_3D);

    //    // 現在のマテリアルを取得
    //    EscDevice->GetMaterial(&matDef);


   

    //if (m_pBuffMat != nullptr)
    //{
    //    pMat = reinterpret_cast<D3DXMATERIAL*>(m_pBuffMat->GetBufferPointer());

    //    for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
    //    {
    //        // マテリアルの設定
    //        EscDevice->SetMaterial(&pMat[nCntMat].MatD3D);

    //        // テクスチャの設定
    //        if (pMat[nCntMat].pTextureFilename != nullptr)
    //        {
    //            // テクスチャの設定
    //            EscDevice->SetTexture(0, m_pTexture[nCntMat]);
    //        }
    //        else
    //        {
    //            // テクスチャの設定
    //            EscDevice->SetTexture(0, nullptr);
    //        }

    //        // メッシュの描画
    //        if (m_bMagChange == true)
    //        {
    //            D3DXCOLOR originalColor = pMat[nCntMat].MatD3D.Diffuse;
    //            pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(
    //                originalColor.r * m_SizeMag.x,
    //                originalColor.g * m_SizeMag.y,
    //                originalColor.b * m_SizeMag.z,
    //                originalColor.a
    //            );

    //            EscDevice->SetMaterial(&pMat[nCntMat].MatD3D);
    //            pMat[nCntMat].MatD3D.Diffuse = originalColor;

    //            m_bMagChange = false;
    //        }

    //        m_pMesh->DrawSubset(nCntMat);

    //        // 保存していたマテリアルを戻す
    //        EscDevice->SetMaterial(&matDef);
    //    }
    //}
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