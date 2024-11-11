//=========================================================
//
// 2D-3DhitColision[2D-3DhitColision.cpp]
// Author seiya kagaya
//
//=========================================================
#include"3D-2DhitObject.h"
#include "manager.h"





//=============================
// コンストラクタ
//=============================
CStageCollisionBox3D2D::CStageCollisionBox3D2D(int nPriority) :CObjectX(nPriority)
{

}

//=============================
// デストラクタ
//=============================
CStageCollisionBox3D2D::~CStageCollisionBox3D2D()
{
}

//=============================
// 初期化
//=============================
HRESULT CStageCollisionBox3D2D::Init()
{
    CObjectX::Init();

    CRenderer* pRenderer = nullptr;
    CManager* pManager = CManager::GetInstance();
    pRenderer = pManager->GetRenderer();

    LPD3DXMESH pMesh = nullptr;
    LPD3DXBUFFER pBuffMat = nullptr;
    DWORD dwNumMat = 0;

    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

    // メッシュの読み込み
    D3DXLoadMeshFromX("DATA\\MODEL\\iwa.x",
        D3DXMESH_SYSTEMMEM,
        EscDevice,
        NULL,
        &pBuffMat,
        NULL,
        &dwNumMat,
        &pMesh);

    D3DXMATERIAL* pMat = (D3DXMATERIAL*)pBuffMat->GetBufferPointer();

    // テクスチャ取得
    CAllTexture* pTexture = pManager->GetTexture();
    LPDIRECT3DTEXTURE9 m_ESCpTexture = nullptr;

    for (int nCntMat = 0; nCntMat < (int)dwNumMat; nCntMat++)
    {
        if (pMat[nCntMat].pTextureFilename != NULL)
        {
    //        const char* TexName = "DATA\\TEXTURE\\iwa.jpg";
            int texIndex = pTexture->Regist(pMat[nCntMat].pTextureFilename, EscDevice);
            m_ESCpTexture = pTexture->GetAddress(texIndex);

            BindTexture(m_ESCpTexture, nCntMat);

            // UVスケールを調整（UVを2倍にすることで600サイズに合わせる例）
            EscDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
            EscDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
        }
    }


    float USize = m_TexSize.x / 150.0f;
    float VSize = m_TexSize.y / 150.0f;;

    pMesh = ScaleMeshUVs(pMesh, USize,VSize);

    SetXfireData(pMesh, pBuffMat, dwNumMat);
    SetObjectType(CObject::OBJECT_HITBOX);

    return S_OK;
}

//=============================
// 破棄
//=============================
void CStageCollisionBox3D2D::Uninit()
{
    CObjectX::Uninit();
}

//=============================
// 更新
//=============================
void CStageCollisionBox3D2D::Update()
{


}

//=============================
// 描画
//=============================
void CStageCollisionBox3D2D::Draw()
{

#if _DEBUG

    ChengeStageTex(true);
    SizeMagChangebool(true);
 //   SetColorChangeBool(true);
    CObjectX::Draw();
    ChengeStageTex(false);

#else

#endif // _D
}

//=============================
// 生成
//=============================
CStageCollisionBox3D2D* CStageCollisionBox3D2D::Create(DATA SetData)
{
    CStageCollisionBox3D2D* pObstacle = new CStageCollisionBox3D2D;

    pObstacle->SetSIzeTexture(SetData.MaxLength);


    pObstacle->Init();

    // 取得
    DATA EscData = pObstacle->GetDATA();
    EscData = SetData; // 移す

    D3DXVECTOR3 SizeMag;

    //サイズ変動
    SizeMag.x = EscData.MaxLength.x / 10.0f;
    SizeMag.y = EscData.MaxLength.y / 10.0f;
    SizeMag.z = EscData.MaxLength.z / 10.0f;

    pObstacle->SetSizeMag(SizeMag);//倍率変動

    pObstacle->SetChangeColor(D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.1f));

    pObstacle->SetDATA(EscData); // 格納

     

    return pObstacle;
}




//=============================
// 当たり判定まとめ
//=============================
void CStageCollisionBox3D2D::HitCollision()
{

}
// メッシュのUV座標をスケーリングする関数
LPD3DXMESH CStageCollisionBox3D2D::ScaleMeshUVs(LPD3DXMESH pMesh, float uScale, float vScale)
{
    
    struct Vertex
    {
        D3DXVECTOR3 position;
        D3DXVECTOR3 normal;
        float u, v;
    };

    Vertex* pVertices = nullptr;
    pMesh->LockVertexBuffer(0, (void**)&pVertices);

    // メッシュの頂点数を取得
    DWORD numVertices = pMesh->GetNumVertices();

    // 各頂点のUV座標をスケーリング
    for (DWORD i = 0; i < numVertices; ++i)
    {
        pVertices[i].u *= uScale;  // 横方向のスケール
        pVertices[i].v *= vScale;  // 縦方向のスケール
    }

    // バッファをアンロック
    pMesh->UnlockVertexBuffer();

    return pMesh;
}

void CStageCollisionBox3D2D::SetSIzeTexture(D3DXVECTOR3 TexSize)
{
    m_TexSize = TexSize;
}
