//=========================================================
//
// StageCollisionBox[StageCollisionBox.cpp]
// Author seiya kagaya
//
//=========================================================
#include"StageCollisionBox.h"
#include "manager.h"

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
            int texIndex = pTexture->Regist(pMat[nCntMat].pTextureFilename, EscDevice);//テクスチャ登録

            m_ESCpTexture = pTexture->GetAddress(texIndex);

            BindTexture(m_ESCpTexture, nCntMat);//設定
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
    //debug時のみ描画
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
    SizeMag.x = EscData.MaxLength.x / (float)SIZE;
    SizeMag.y = EscData.MaxLength.y / (float)SIZE*2.0f;
    SizeMag.z = EscData.MaxLength.z / (float)SIZE;
    
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

}