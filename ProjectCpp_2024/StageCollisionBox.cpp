//=========================================================
//
// StageCollisionBox[StageCollisionBox.cpp]
// Author seiya kagaya
//
//=========================================================
#include"StageCollisionBox.h"
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
StageCollisionBox::StageCollisionBox(int nPriority) :CObjectX(nPriority)
{

}

//=============================
// デストラクタ
//=============================
StageCollisionBox::~StageCollisionBox()
{
}

//=============================
// 初期化
//=============================
HRESULT StageCollisionBox::Init()
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
    D3DXLoadMeshFromX("DATA\\MODEL\\DebugModel\\BOX.x",
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

    SetObjectType(CObject::OBJECT_HITBOX);


    
    return S_OK;
}

//=============================
// 破棄
//=============================
void StageCollisionBox::Uninit()
{
    CObjectX::Uninit();
}

//=============================
// 更新
//=============================
void StageCollisionBox::Update()
{


}

//=============================
// 描画
//=============================
void StageCollisionBox::Draw()
{
    
#if _DEBUG
    
    SizeMagChangebool(true);
    SetColorChangeBool(true);
    CObjectX::Draw();

#else
   
#endif // _D
}

//=============================
// 生成
//=============================
StageCollisionBox* StageCollisionBox::Create(DATA SetData)
{
    StageCollisionBox* pObstacle = new StageCollisionBox;

    pObstacle->Init();

    // 取得
    DATA EscData = pObstacle->GetDATA();
    EscData = SetData; // 移す

    D3DXVECTOR3 SizeMag;

       //サイズ変動
    SizeMag.x = EscData.MaxLength.x / 10.0f;
    SizeMag.y = EscData.MaxLength.y / 20.0f;
    SizeMag.z = EscData.MaxLength.z / 10.0f;
    
    pObstacle->SetSizeMag(SizeMag);//倍率変動

    pObstacle->SetChangeColor(D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.1f));

    pObstacle->SetDATA(EscData); // 格納

    return pObstacle;
}




//=============================
// 当たり判定まとめ
//=============================
void StageCollisionBox::HitCollision()
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
