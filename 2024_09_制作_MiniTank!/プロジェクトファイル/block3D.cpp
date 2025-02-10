//=========================================================
//
// block3D[block3D.cpp]
// Author seiya kagaya
//
//=========================================================
#include "block3D.h"
#include "renderer.h"
#include "manager.h"

//=============================
// コンストラクタ
//=============================
CBlock3D::CBlock3D(int nPriority) :CObjectX(nPriority)
{
}

//=============================
//デストラクタ
//=============================
CBlock3D::~CBlock3D()
{
}

//=============================
//初期化
//=============================
HRESULT CBlock3D::Init()
{
    CObjectX::Init();
    CRenderer* pRenderer = nullptr;
    CManager* pManager = CManager::GetInstance();
    pRenderer = pManager->GetRenderer();
    LPD3DXMESH pMesh = nullptr;//Meshポインタ
    LPD3DXBUFFER pBuffMat = nullptr;//マテリアルへのポインタ
    DWORD dwNumMat = 0;//マテリアルの数

    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();
    //ファイルの読み込み
    D3DXLoadMeshFromX("DATA\\MODEL\\baseBlock.x",
        D3DXMESH_SYSTEMMEM,
        EscDevice,
        NULL,
        &pBuffMat,
        NULL,
        &dwNumMat,
        &pMesh);

    //マテリアルデータへのポインタを取得
    D3DXMATERIAL* pMat = (D3DXMATERIAL*)pBuffMat->GetBufferPointer();

    for (int nCntMat = 0; nCntMat < (int)dwNumMat; nCntMat++)
    {
        // ディフューズカラーをサイズに基づいて変更
        D3DXCOLOR originalColor = pMat[nCntMat].MatD3D.Diffuse;

        pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//色をここで指定
    }

    SetXfireData(pMesh, pBuffMat, dwNumMat);//データ格納

    SetObjectType(CObject::OBJECT_BLOCK3D);

    SetSizeMag(D3DXVECTOR3(5.0f, 5.0f, 5.0f));//大きさ倍率

    //取得
    DATA EscData = GetDATA();
    EscData = GetDATA();//再取得
    EscData.MinLength = D3DXVECTOR3(-SIZE, 0.0f, -SIZE);
    EscData.MaxLength = D3DXVECTOR3(SIZE, SIZE, SIZE);
    SetDATA(EscData);//格納

    return S_OK;
}

//=============================
//破棄
//=============================
void CBlock3D::Uninit()
{
    CObjectX::Uninit();
}

//=============================
//更新
//=============================
void CBlock3D::Update()
{   
    CObjectX::Update();
}

//=============================
//描画
//=============================
void CBlock3D::Draw()
{
    //サイズ変更
    SizeMagChangebool(true);

    CObjectX::Draw();
}

//=============================
//生成
//=============================
CBlock3D* CBlock3D::Create()
{
    CBlock3D* pBlock3D = new CBlock3D;
    pBlock3D->Init();
    return pBlock3D;
}