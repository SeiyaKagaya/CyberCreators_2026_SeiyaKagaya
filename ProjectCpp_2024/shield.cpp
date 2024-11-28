//=========================================================
//
// CShield[CShield.cpp]
// Author seiya kagaya
//
//=========================================================
#include"shield.h"



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

    for (int i = 0; i < 2; i++)
    {
         m_pMesh[i] = nullptr; // Meshポインタ
         m_pBuffMat[i] = nullptr; // マテリアルへのポインタ
         m_dwNumMat[i] = 0; // マテリアルの数
         m_ESCpTexture[i] = nullptr;
         m_bFast[i] = false;
         m_OriginalColor[i] = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
    }
    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

    for (int i = 0; i < 2; i++)
    {

        if (i == 0)
        {
            // ファイルの読み込み
            D3DXLoadMeshFromX("DATA\\MODEL\\Shield.x",
                D3DXMESH_SYSTEMMEM,
                EscDevice,
                NULL,
                &m_pBuffMat[i],
                NULL,
                &m_dwNumMat[i],
                &m_pMesh[i]);
        }
        else
        {
            // ファイルの読み込み
            D3DXLoadMeshFromX("DATA\\MODEL\\Shield2.x",
                D3DXMESH_SYSTEMMEM,
                EscDevice,
                NULL,
                &m_pBuffMat[i],
                NULL,
                &m_dwNumMat[i],
                &m_pMesh[i]);
        }




        D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat[i]->GetBufferPointer();

        //テクスチャ取得
        CAllTexture* pTexture = pManager->GetTexture();

        for (int nCntMat = 0; nCntMat < (int)m_dwNumMat[i]; nCntMat++)
        {
            if (pMat[nCntMat].pTextureFilename != NULL)
            {

                int texIndex = pTexture->Regist(pMat[nCntMat].pTextureFilename, EscDevice);//テクスチャ登録

                m_ESCpTexture[i] = pTexture->GetAddress(texIndex);

                BindTexture(m_ESCpTexture[i], nCntMat);//設定
            }
        }


        SetXfireData(m_pMesh[0], m_pBuffMat[0], m_dwNumMat[0]); // データ格納
    }






    SetObjectType(CObject::OBJECT_SHIELD);

    m_Obb.m_fLength[0] = 160.0f;
    m_Obb.m_fLength[1] = 160.0f;
    m_Obb.m_fLength[2] = 50.0f;

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
    DATA EscData = GetDATA();

    //m_Obb.m_fLength[0] = 30.0f;
    //m_Obb.m_fLength[1] = 160.0f;
    //m_Obb.m_fLength[2] = 30.0f;

    CRenderer* pRenderer = nullptr;
    CManager* pManager = CManager::GetInstance();

    if (pManager->GetbNow3DMode() == false)
    {//2D
        m_Obb.m_fLength[0] = 160.0f;
        m_Obb.m_fLength[1] = 160.0f;
        m_Obb.m_fLength[2] = 50.0f;
    }
    else
    {
        m_Obb.m_fLength[0] = 150.0f;
        m_Obb.m_fLength[1] = 150.0f;
        m_Obb.m_fLength[2] = 150.0f;
    }



    //OBBまわり
    m_Obb.m_Pos = EscData.Pos;
    m_Obb.m_Pos.y -= 160.0f;

    D3DXMATRIX matRot;

    //方向ベクトル取得
    D3DXMatrixRotationYawPitchRoll(&matRot, EscData.rot.y, EscData.rot.x, EscData.rot.z);
    m_Obb.m_Direct[0] = D3DXVECTOR3(matRot._11, matRot._12, matRot._13);
    m_Obb.m_Direct[1] = D3DXVECTOR3(matRot._21, matRot._22, matRot._23);
    m_Obb.m_Direct[2] = D3DXVECTOR3(matRot._31, matRot._32, matRot._33);






    if (m_bDrawOk == true)
    {
        //被弾系
    //----------------------------------------------------------------------------------
        CObject* pObj = nullptr;
        pObj = CObject::GetObjectPoint(CObject::LAYERINDEX_NEWBULLET_MNG, CObject::OBJECT_NEWBULLET_MNG);

        if (pObj != nullptr)
        {
            CNewBulletALL* pBulletMNG = static_cast<CNewBulletALL*>(pObj);

            for (int i = 0; i < CNewBulletALL::MAXBULLETALL; i++)
            {
                CNewBullet* pBullet = pBulletMNG->GetBulletData(i);

                if (pBullet->GetbUse() == true)
                {//弾が機能しているとき
                    if (pBullet->GetHitEscapeTime() <= 0)
                    {//自爆抑制以降の時

                        COBB pObb2 = pBullet->GetOBB();
                        COBB MyObb = m_Obb;

                        D3DXVECTOR3 HitPos;
                        bool btest = CMathProc::ColOBBs(MyObb, pObb2, &HitPos);//当たり判定

                        if (btest == true)
                        {
                            //pBullet->SetDeath(true);
                            pBullet->SetGoodby();

                            m_nLife -= 100;
                        }
                    }
                    else
                    {//抑制期間
                        if (pBullet->GetCaller() != this)
                        {//発射した親が自身じゃないとき
                            COBB pObb2 = pBullet->GetOBB();
                            COBB MyObb = m_Obb;

                            D3DXVECTOR3 HitPos;
                            bool btest = CMathProc::ColOBBs(MyObb, pObb2, &HitPos);//当たり判定

                            if (btest == true)
                            {
                                //pBullet->SetDeath(true);
                                pBullet->SetGoodby();

                                m_nLife -= 100;
                            }
                        }
                    }
                }
            }
        }




        ////被弾系------------------------------------------------------------------------------------------
        //CObject* pObj = nullptr;
        //pObj = CObject::GetObjectPoint(CObject::LAYERINDEX_NEWBULLET, CObject::OBJECT_NEWBULLET);
        //if (pObj != nullptr)
        //{
        //    CNewBullet* pBullet = static_cast<CNewBullet*>(pObj);

        //    CObject::DATA EscData;

        //    if (pBullet->GetHitEscapeTime() <= 0)
        //    {//自爆抑制以降の時

        //        COBB pObb2 = pBullet->GetOBB();
        //        COBB MyObb = m_Obb;

        //        D3DXVECTOR3 HitPos;
        //        bool btest = CMathProc::ColOBBs(MyObb, pObb2, &HitPos);//当たり判定

        //        if (btest == true)
        //        {
        //            pBullet->SetDeath(true);
        //            //pBullet->SetGoodby();

        //            m_nLife -= 100;
        //        }
        //    }
        //    else
        //    {//抑制期間
        //        if (pBullet->GetCaller() != this)
        //        {//発射した親が自身じゃないとき
        //            COBB pObb2 = pBullet->GetOBB();
        //            COBB MyObb = m_Obb;

        //            D3DXVECTOR3 HitPos;
        //            bool btest = CMathProc::ColOBBs(MyObb, pObb2, &HitPos);//当たり判定

        //            if (btest == true)
        //            {
        //                pBullet->SetDeath(true);
        //                //pBullet->SetGoodby();

        //                m_nLife -= 100;
        //            }
        //        }
        //    }
    }
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




#if _DEBUG
    if (m_bDrawOk == true)
    {
        DATA EscData = GetDATA();

        //SetSizeMag(D3DXVECTOR3 (2.0f,2.0f,2.0f));//倍率
        //SizeMagChangebool(true);

     

       // CObjectX::Draw();
   
        CRenderer* pRenderer = nullptr;
        CManager* pManager = CManager::GetInstance();
        pRenderer = pManager->GetRenderer();
        LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();


        D3DXMATRIX mtxRot, mtxTrans;


        // ワールドマトリックスの初期化
        D3DXMatrixIdentity(&m_mtxWorld);
        
        
        D3DXVECTOR3 SetMag;

        if (pManager->GetbNow3DMode() == false)
        {//2D
             SetMag = D3DXVECTOR3(2.0f, 2.0f, 2.0f);
        }
        else
        {
             SetMag = D3DXVECTOR3(1.5f, 1.5f, 1.5f);
        }

        // モデルのサイズを変更

        D3DXMatrixScaling(&m_mtxWorld, SetMag.x, SetMag.y, SetMag.z);
        
        // 向きを反映
        D3DXMatrixRotationYawPitchRoll(&mtxRot, EscData.rot.y, EscData.rot.x, EscData.rot.z);
        D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

        // 位置を反映
        D3DXMatrixTranslation(&mtxTrans, EscData.Pos.x, EscData.Pos.y, EscData.Pos.z);
        D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

        D3DMATERIAL9 matDef;
        D3DXMATERIAL* pMat;


        int nCnt = 0;

        if (pManager->GetbNow3DMode() == false)
        {//2D
            nCnt = 0;
        }
        else
        {
            nCnt = 1;
        }


        // ワールドマトリックスの設定
        EscDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
        // 頂点フォーマットの設定
        EscDevice->SetFVF(FVF_VERTEX_3D);
        // 現在のマテリアルを取得
        EscDevice->GetMaterial(&matDef);

        // 通常のオブジェクトの描画
        if (m_pBuffMat[nCnt] != nullptr)
        {
            pMat = reinterpret_cast<D3DXMATERIAL*>(m_pBuffMat[nCnt]->GetBufferPointer());

            for (int nCntMat = 0; nCntMat < (int)m_dwNumMat[nCnt]; nCntMat++)
            {
                // ワールド行列を元に戻す
                EscDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

                // マテリアルの設定
                EscDevice->SetMaterial(&pMat[nCntMat].MatD3D);


                pMat[nCntMat].pTextureFilename = NULL;

                EscDevice->SetTexture(0, nullptr);

                if (m_bFast[nCnt] == false)
                {//始めの一回のみ
                    m_OriginalColor[nCnt] = pMat[nCntMat].MatD3D.Diffuse;
                    m_bFast[nCnt] = true;
                }


                // メッシュの描画
            

                  //  D3DXCOLOR originalColor;

                  
                    pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(
                        m_OriginalColor[nCnt].r * SetMag.x,
                        m_OriginalColor[nCnt].g * SetMag.y,
                        m_OriginalColor[nCnt].b * SetMag.z,
                        m_OriginalColor[nCnt].a
                    );

                    EscDevice->SetMaterial(&pMat[nCntMat].MatD3D);
                    pMat[nCntMat].MatD3D.Diffuse = m_OriginalColor[nCnt];

                

                m_pMesh[nCnt]->DrawSubset(nCntMat);

                // 保存していたマテリアルを戻す
                EscDevice->SetMaterial(&matDef);
            }

        }

        
    }
#else

#endif // _D

    char cData2[100] = {};
    DATA EscData = GetDATA();//再取得
    snprintf(cData2, sizeof(cData2), "現在のGRID/%d", (int)EscData.rot.x); // 数値を文字列に変換してCDataにコピー
    CFont::DrawTextSet(D3DXVECTOR3(900.0f, 450.0f, 0.0f), 40, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), cData2);

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
