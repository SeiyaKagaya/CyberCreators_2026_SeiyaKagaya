//=========================================================
//
// CShield[CShield.cpp]
// Author seiya kagaya
//
//=========================================================
#include"shield.h"
//#include "renderer.h"
#include "manager.h"
//#include "explosion.h"
//#include <stdio.h>
//#include <cstring>
//#include <iostream> // デバッグ用

//#include <fstream>
//#include <climits> // INT_MAX
//#include <limits.h>





//=============================
// コンストラクタ
//=============================
CShield::CShield(int nPriority) :CObjectX(nPriority)
{

}

//=============================
// デストラクタ
//=============================
CShield::~CShield()
{
}

//=============================
// 初期化
//=============================
HRESULT CShield::Init()
{
    CObjectX::Init();

    CRenderer* pRenderer = nullptr;
    CManager* pManager = CManager::GetInstance();
    pRenderer = pManager->GetRenderer();

    LPD3DXMESH pMesh = nullptr; // Meshポインタ
    LPD3DXBUFFER pBuffMat = nullptr; // マテリアルへのポインタ
    DWORD dwNumMat = 0; // マテリアルの数

    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

    // ファイルの読み込み
    D3DXLoadMeshFromX("DATA\\MODEL\\Shield.x",
        D3DXMESH_SYSTEMMEM,
        EscDevice,
        NULL,
        &pBuffMat,
        NULL,
        &dwNumMat,
        &pMesh);

    D3DXMATERIAL* pMat = (D3DXMATERIAL*)pBuffMat->GetBufferPointer();

    //テクスチャ読み込み
    LPDIRECT3DTEXTURE9	m_ESCpTexture = nullptr;

    //テクスチャ取得
    CAllTexture* pTexture = pManager->GetTexture();




    for (int nCntMat = 0; nCntMat < (int)dwNumMat; nCntMat++)
    {
        if (pMat[nCntMat].pTextureFilename != NULL)
        {
            //LPDIRECT3DTEXTURE9 EscTex = {};

            //テクスチャ読み込み
            //D3DXCreateTextureFromFile(EscDevice, pMat[nCntMat].pTextureFilename, &EscTex);

            int texIndex = pTexture->Regist(pMat[nCntMat].pTextureFilename, EscDevice);//テクスチャ登録

            m_ESCpTexture = pTexture->GetAddress(texIndex);

            BindTexture(m_ESCpTexture, nCntMat);//設定

      //      BindTexture(EscTex, nCntMat);
        }
    }


    SetXfireData(pMesh, pBuffMat, dwNumMat); // データ格納

    SetObjectType(CObject::OBJECT_SHIELD);



    return S_OK;
}

//=============================
// 破棄
//=============================
void CShield::Uninit()
{
    CObjectX::Uninit();
}

//=============================
// 更新
//=============================
void CShield::Update()
{
    DATA EscData = GetDATA();//再取得
  //  EscData.Pos = m_pParent->GetDATA().Pos;

    EscData.rot.x += 0.1f;//これが大事
 
   EscData.rot.y = -D3DX_PI * 0.5f;

    EscData.rot.z += 0.1f;
    SetDATA(EscData);
}

//=============================
// 描画
//=============================
void CShield::Draw()
{
    CRenderer* pRenderer = nullptr;

    CManager* pManager = CManager::GetInstance();

    pRenderer = pManager->GetRenderer();

    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();


    //DATA EscData = GetDATA();//再取得

    //D3DXMATRIX EscMtxWorld;

    //D3DXMATRIX mtxRot, mtxTrans, mtxParent;//計算用マトリックス

    ////ワールドマトリックスの初期化
    //D3DXMatrixIdentity(&m_mtxWorld);

    ////向きを反映
    //D3DXMatrixRotationYawPitchRoll(&mtxRot, EscData.rot.y, EscData.rot.x, EscData.rot.z);

    //D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

    ////位置を反映
    //D3DXMatrixTranslation(&mtxTrans, EscData.Pos.x, EscData.Pos.y, EscData.Pos.z);

    //D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

    ////親子関係
    //if (m_pParentParts != nullptr)
    //{
    //    //自分の主のマトリックスとかける(player/enemy)など

    //    //
    //    EscDevice->GetTransform(D3DTS_WORLD, &EscMtxWorld);//とりあえず最新のマトリックス取得


    //    D3DXMATRIX EscMat = m_pParentParts->GetMtxWorld();

    //    //始祖とかける
    //    D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &EscMat);
    //}


 ////   ChangeModelPartsbool(true);//パーツ描画じマトリックス変更
 //   SetModelMtxWorld(m_mtxWorld);//マトリックス格納




#if _DEBUG
    if (m_bDrawOk == true)
    {
        SetSizeMag(D3DXVECTOR3 (20.0f,20.0f,20.0f));//倍率
        SizeMagChangebool(true);
      //  SetColorChangeBool(true);
     //   SetNotLight(true);
        CObjectX::Draw();
    }
#else

#endif // _D
}

//=============================
// 生成
//=============================
CShield* CShield::Create(DATA SetData, CObjectMotionPlayer* pMotion)
{
    CShield* pObstacle = new CShield;

    pObstacle->Init();

    // 取得
    DATA EscData = pObstacle->GetDATA();
    EscData = SetData; // 移す

    D3DXVECTOR3 SizeMag;

    //サイズ変動
    SizeMag.x = EscData.MaxLength.x / 10.0f;
    SizeMag.y = EscData.MaxLength.y / 20.0f;
    SizeMag.z = EscData.MaxLength.z / 10.0f;

  //  EscData.rot.y = D3DX_PI * 0.5f;

    pObstacle->SetSizeMag(SizeMag);//倍率変動

 //   pObstacle->SetChangeColor(D3DXCOLOR(1.0f,1.0f,0.0f,0.7f));

    pObstacle->SetDATA(EscData); // 格納
    pObstacle->SetParent(pMotion);
    return pObstacle;
}




//=============================
// 当たり判定まとめ
//=============================
void CShield::HitCollision()
{
    //// 取得
    //DATA EscData = GetDATA();

    //// 当たり判定計算
    //m_HitData = CMathProc::CheckBoxCollision_3D(EscData.Pos, EscData.OldPos, EscData.MinLength, EscData.MaxLength, OBJECT_BLOCK3D,LAYERINDEX_BLOCK3D,EscData.move);

    //if (m_HitData.bHit == true)
    //{
    //    if (m_HitData.HitAngle.x == 1)
    //    {
    //        EscData.Pos.x += m_HitData.ResultDistance.x;
    //        EscData.move.x = 0.0f;
    //    }
    //    else if (m_HitData.HitAngle.x == -1)
    //    {
    //        EscData.Pos.x -= m_HitData.ResultDistance.x;
    //        EscData.move.x = 0.0f;
    //    }
    //    else if (m_HitData.HitAngle.y == 1)
    //    {
    //        EscData.Pos.y += m_HitData.ResultDistance.y;
    //        EscData.move.y = 0.0f;
    //    }
    //    else if (m_HitData.HitAngle.y == -1)
    //    {
    //        EscData.Pos.y -= m_HitData.ResultDistance.y;
    //        EscData.move.y = 0.0f;
    //    }
    //    else if (m_HitData.HitAngle.z == 1)
    //    {
    //        EscData.Pos.z += m_HitData.ResultDistance.z;
    //        EscData.move.z = 0.0f;
    //    }
    //    else if (m_HitData.HitAngle.z == -1)
    //    {
    //        EscData.Pos.z -= m_HitData.ResultDistance.z;
    //        EscData.move.z = 0.0f;
    //    }
    //}

    //SetDATA(EscData); // 格納
}
