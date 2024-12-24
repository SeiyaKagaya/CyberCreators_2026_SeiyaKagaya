//=========================================================
//
// CBulletLine[CBulletLine.cpp]
// Author seiya kagaya
//
//=========================================================
#include"CBulletLine.h"



//=============================
// コンストラクタ
//=============================
CBulletLine::CBulletLine(int nPriority) :CObjectX(nPriority)
{

}

//=============================
// デストラクタ
//=============================
CBulletLine::~CBulletLine()
{
}

//=============================
// 初期化
//=============================
HRESULT CBulletLine::Init()
{
    CObjectX::Init();

    CRenderer* pRenderer = nullptr;
    CManager* pManager = CManager::GetInstance();
    pRenderer = pManager->GetRenderer();


    m_pMesh = nullptr; // Meshポインタ
    m_pBuffMat = nullptr; // マテリアルへのポインタ
    m_dwNumMat = 0; // マテリアルの数
    m_ESCpTexture = nullptr;
    m_bFast = false;
    m_OriginalColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();


    // ファイルの読み込み
    D3DXLoadMeshFromX("DATA\\MODEL\\BulletLine.x",
        D3DXMESH_SYSTEMMEM,
        EscDevice,
        NULL,
        &m_pBuffMat,
        NULL,
        &m_dwNumMat,
        &m_pMesh);




    D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

    //テクスチャ取得
    CAllTexture* pTexture = pManager->GetTexture();

    for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
    {
        if (pMat[nCntMat].pTextureFilename != NULL)
        {

            int texIndex = pTexture->Regist(pMat[nCntMat].pTextureFilename, EscDevice);//テクスチャ登録

            m_ESCpTexture = pTexture->GetAddress(texIndex);

            BindTexture(m_ESCpTexture, nCntMat);//設定
        }
    }


    //       SetXfireData(m_pMesh[0], m_pBuffMat[0], m_dwNumMat[0]); // データ格納







    SetObjectType(CObject::OBJECT_BULLETLINE);

    m_Obb.m_fLength[0] = 160.0f;
    m_Obb.m_fLength[1] = 160.0f;
    m_Obb.m_fLength[2] = 50.0f;

    return S_OK;
}

//=============================
// 破棄
//=============================
void CBulletLine::Uninit()
{

        if (m_pMesh != nullptr)
        {
            m_pMesh->Release(); // メッシュ解放
            m_pMesh = nullptr;
        }

        if (m_pBuffMat != nullptr)
        {
            m_pBuffMat->Release(); // マテリアルバッファ解放
            m_pBuffMat = nullptr;
        }

        // テクスチャの解放はCAllTextureクラスの管理方法に従う必要がある
        if (m_ESCpTexture != nullptr)
        {
            // ここでdeleteではなく、CAllTextureの管理クラスで解放するように実装
            // CManager::GetInstance()->GetTexture()->ReleaseTexture(m_ESCpTexture);
            m_ESCpTexture = nullptr;
        }
    


    //  CObjectX::Uninit();
}

//=============================
// 更新
//=============================
void CBulletLine::Update()
{

}


//=============================
// 描画
//=============================
void CBulletLine::Draw()
{
    CRenderer* pRenderer = nullptr;

    CManager* pManager = CManager::GetInstance();

    pRenderer = pManager->GetRenderer();

    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();





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

        SetMag = D3DXVECTOR3(2.0f, 2.0f, 2.0f);


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



        // ワールドマトリックスの設定
        EscDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
        // 頂点フォーマットの設定
        EscDevice->SetFVF(FVF_VERTEX_3D);
        // 現在のマテリアルを取得
        EscDevice->GetMaterial(&matDef);

        // 通常のオブジェクトの描画
  
            pMat = reinterpret_cast<D3DXMATERIAL*>(m_pBuffMat->GetBufferPointer());

            for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
            {
                // ワールド行列を元に戻す
                EscDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

                // マテリアルの設定
                EscDevice->SetMaterial(&pMat[nCntMat].MatD3D);


                pMat[nCntMat].pTextureFilename = NULL;

                EscDevice->SetTexture(0, nullptr);

                if (m_bFast == false)
                {//始めの一回のみ
                    m_OriginalColor = pMat[nCntMat].MatD3D.Diffuse;
                    m_bFast = true;
                }


                // メッシュの描画


                  //  D3DXCOLOR originalColor;


                pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(
                    m_OriginalColor.r * SetMag.x,
                    m_OriginalColor.g * SetMag.y,
                    m_OriginalColor.b * SetMag.z,
                    m_OriginalColor.a
                );

                EscDevice->SetMaterial(&pMat[nCntMat].MatD3D);
                pMat[nCntMat].MatD3D.Diffuse = m_OriginalColor;



                m_pMesh->DrawSubset(nCntMat);

                // 保存していたマテリアルを戻す
                EscDevice->SetMaterial(&matDef);
            }

        


    }

#if _DEBUG
    //char cData2[100] = {};
    //DATA EscData = GetDATA();//再取得
    //snprintf(cData2, sizeof(cData2), "現在のGRID/%d", (int)EscData.rot.x); // 数値を文字列に変換してCDataにコピー
    //CFont::DrawTextSet(D3DXVECTOR3(900.0f, 450.0f, 0.0f), 40, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), cData2);
#else

#endif // _D


}

//=============================
// 生成
//=============================
CBulletLine* CBulletLine::Create(DATA SetData, CObjectMotionPlayer* pMotion)
{
    CBulletLine* pObstacle = new CBulletLine;

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
void CBulletLine::HitCollision()
{
}
