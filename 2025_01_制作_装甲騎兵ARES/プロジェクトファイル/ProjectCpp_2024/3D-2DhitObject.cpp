//=========================================================
//
// 2D-3DhitColision[2D-3DhitColision.cpp]
// Author seiya kagaya
//
//=========================================================

#include"3D-2DhitObject.h"
#include "manager.h"
#include "player_motion.h"
#include "enemy_motion_Nomal.h"

//=============================
// コンストラクタ
//=============================
CStageCollisionBox3D2D::CStageCollisionBox3D2D(int nPriority) :CObjectX(nPriority)
{

}

//=============================
// デストラクタ
//=============================
CStageCollisionBox3D2D::‾CStageCollisionBox3D2D()
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

   // LPD3DXMESH pMesh = nullptr;
    LPD3DXBUFFER pBuffMat = nullptr;
    DWORD dwNumMat = 0;

    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();
    
    const char* aData = {};

    switch (m_hitbox)
    {
    case TYPE_RIGHTSLOPE:
        aData = "DATA¥¥MODEL¥¥iwaR.x";
        break;
    case TYPE_LEFTSLOPE:
        aData = "DATA¥¥MODEL¥¥iwaL.x";
        break;
    case TYPE_NOMALBLOCK:
        aData = "DATA¥¥MODEL¥¥iwa.x";
        break;
    case TYPE_3DSTAGE:
        aData = "DATA¥¥MODEL¥¥iwa2.x";
        break;
    }

    // メッシュの読み込み
        D3DXLoadMeshFromX(aData,
            D3DXMESH_SYSTEMMEM,
            EscDevice,
            NULL,
            &pBuffMat,
            NULL,
            &dwNumMat,
            &m_pMesh);

    D3DXMATERIAL* pMat = (D3DXMATERIAL*)pBuffMat->GetBufferPointer();

    // テクスチャ取得
    CAllTexture* pTexture = pManager->GetTexture();
    LPDIRECT3DTEXTURE9 m_ESCpTexture = nullptr;

    for (int nCntMat = 0; nCntMat < (int)dwNumMat; nCntMat++)
    {
        if (pMat[nCntMat].pTextureFilename != NULL)
        {
    //        const char* TexName = "DATA¥¥TEXTURE¥¥iwa.jpg";
            int texIndex = pTexture->Regist(pMat[nCntMat].pTextureFilename, EscDevice);

            m_ESCpTexture = pTexture->GetAddress(texIndex);

            BindTexture(m_ESCpTexture, nCntMat);

            // UVスケールを調整（UVを2倍にすることで600サイズに合わせる例）
            EscDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
            EscDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
        }
    }


    float USize = m_TexSize.x / 150.0f;
    float VSize = m_TexSize.y / 150.0f;

    m_pMesh = ScaleMeshUVs(m_pMesh, USize,VSize);

    SetXfireData(m_pMesh, pBuffMat, dwNumMat);
    SetObjectType(CObject::OBJECT_HITBOX_2D3D);

    return S_OK;
}

//=============================
// 破棄
//=============================
void CStageCollisionBox3D2D::Uninit()
{
    //if (m_pMesh != nullptr)
    //{
    //    delete m_pMesh;
    //    m_pMesh = nullptr;
    //}
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

//#if _DEBUG

    ChengeStageTex(true);
    SizeMagChangebool(true);
 //   SetColorChangeBool(true);
    CObjectX::Draw();
    ChengeStageTex(false);

//#else

//#endif // _D

}

//=============================
// 生成
//=============================
CStageCollisionBox3D2D* CStageCollisionBox3D2D::Create(DATA SetData, HITBOX hitman)
{
    CStageCollisionBox3D2D* pObstacle = new CStageCollisionBox3D2D;

    pObstacle->SetSIzeTexture(SetData.MaxLength);

    pObstacle->SetType(hitman);
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

////=============================
//// 当たり判定まとめ
////=============================
//void CStageCollisionBox3D2D::HitCollision()
//{
//
//}
//=============================
// メッシュのUV座標をスケーリングする関数
//=============================
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
//=============================
// テクスチャサイズ
//=============================
void CStageCollisionBox3D2D::SetSIzeTexture(D3DXVECTOR3 TexSize)
{
    m_TexSize = TexSize;
}
//=============================
// タイプ格納
//=============================
void CStageCollisionBox3D2D::SetType(HITBOX type)
{
    m_hitbox = type;
}
//=============================
// タイプ取得
//=============================
CStageCollisionBox3D2D::HITBOX CStageCollisionBox3D2D::GetHitBoxType()
{
    return m_hitbox;
}
LPD3DXMESH CStageCollisionBox3D2D::GetMesh()
{
	return m_pMesh;
}

//=============================
// タイプ取得
//=============================
CMathProc::CollisionData CStageCollisionBox3D2D::bHitColision(D3DXVECTOR3 pos, D3DXVECTOR3 rayDirection, CObject::OBJECTTYPE MyType, void* pCaller)
{
    CRenderer* pRenderer = nullptr;
    CManager* pManager = CManager::GetInstance();
    pRenderer = pManager->GetRenderer();
    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

    bool EscHit = false;
    CMathProc::CollisionData HitData;
    HitData.bHit = false;
    HitData.HitAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    HitData.ResultDistance = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    HitData.targetIndex = -1;

    bool bLandingHit = false;

    CObject* pObject = CObject::GetpTop(LAYERINDEX_HITBOX_2D3D);
    int nIndex = 0;

    while (pObject != nullptr)
    {
        bool bSkip = false;

        // オブジェクトタイプの確認
        if (pObject->GetObjectType() == LAYERINDEX_HITBOX_2D3D)
        {
            CStageCollisionBox3D2D* pStageHitBox_2D3D = (CStageCollisionBox3D2D*)pObject;
            CObject::DATA EscData = pStageHitBox_2D3D->GetDATA();

            // スロープ以外のオブジェクトをスキップ
            if (pStageHitBox_2D3D->GetHitBoxType() != CStageCollisionBox3D2D::TYPE_LEFTSLOPE)
            {
                bSkip = true;
            }

            if (!bSkip)
            {
                D3DXMATRIX matWorld;
                D3DXMatrixIdentity(&matWorld);

                // メッシュのスケーリングと回転・位置を適用
                D3DXMatrixScaling(&matWorld, pStageHitBox_2D3D->GetSizeMag().x, pStageHitBox_2D3D->GetSizeMag().y, pStageHitBox_2D3D->GetSizeMag().z);
                D3DXMatrixRotationYawPitchRoll(&matWorld, pStageHitBox_2D3D->GetDATA().rot.y, pStageHitBox_2D3D->GetDATA().rot.x, pStageHitBox_2D3D->GetDATA().rot.z);
                D3DXMatrixTranslation(&matWorld, pStageHitBox_2D3D->GetDATA().Pos.x, pStageHitBox_2D3D->GetDATA().Pos.y, pStageHitBox_2D3D->GetDATA().Pos.z);

                LPD3DXMESH pMesh;
                pStageHitBox_2D3D->GetMesh()->CloneMeshFVF(
                    D3DXMESH_MANAGED,
                    D3DFVF_XYZ | D3DFVF_NORMAL,
                    EscDevice,
                    &pMesh);

                // 衝突検出用の最短距離と交差情報の初期化
                float nearestDist = FLT_MAX;
                D3DXVECTOR3 hitPoint, hitNormal;
                BOOL hit = FALSE;
                DWORD faceIndex;
                FLOAT u, v, dist;

                if (SUCCEEDED(D3DXIntersect(pMesh, &pos, &rayDirection, &hit, &faceIndex, &u, &v, &dist, NULL, NULL)))
                {
                    if (hit && dist < nearestDist)
                    {
                        nearestDist = dist;
                        EscHit = true;
                        bLandingHit = true;

                        // ワールド行列の設定
                        D3DXMATRIX matScale, matRot, matTrans, matWorld;
                        D3DXMatrixScaling(&matScale, pStageHitBox_2D3D->GetSizeMag().x, pStageHitBox_2D3D->GetSizeMag().y, pStageHitBox_2D3D->GetSizeMag().z);
                        D3DXMatrixRotationYawPitchRoll(&matRot, pStageHitBox_2D3D->GetDATA().rot.y, pStageHitBox_2D3D->GetDATA().rot.x, pStageHitBox_2D3D->GetDATA().rot.z);
                        D3DXMatrixTranslation(&matTrans, pStageHitBox_2D3D->GetDATA().Pos.x, pStageHitBox_2D3D->GetDATA().Pos.y, pStageHitBox_2D3D->GetDATA().Pos.z);
                        matWorld = matScale * matRot * matTrans;

                        // インデックスバッファと頂点バッファから交差面の頂点座標を取得
                        LPDIRECT3DVERTEXBUFFER9 pVertexBuffer = nullptr;
                        LPDIRECT3DINDEXBUFFER9 pIndexBuffer = nullptr;
                        pMesh->GetVertexBuffer(&pVertexBuffer);
                        pMesh->GetIndexBuffer(&pIndexBuffer);

                        // 三角形の頂点インデックスを取得
                        WORD* pIndices = nullptr;
                        pIndexBuffer->Lock(0, 0, (void**)&pIndices, D3DLOCK_READONLY);
                        WORD i0 = pIndices[faceIndex * 3 + 0];
                        WORD i1 = pIndices[faceIndex * 3 + 1];
                        WORD i2 = pIndices[faceIndex * 3 + 2];
                        pIndexBuffer->Unlock();

                        // 三角形の頂点座標を取得
                        D3DXVECTOR3* pVertices = nullptr;
                        pVertexBuffer->Lock(0, 0, (void**)&pVertices, D3DLOCK_READONLY);
                        D3DXVECTOR3 v0 = pVertices[i0];
                        D3DXVECTOR3 v1 = pVertices[i1];
                        D3DXVECTOR3 v2 = pVertices[i2];
                        pVertexBuffer->Unlock();

                        // 頂点座標をワールド行列で変換
                        D3DXVec3TransformCoord(&v0, &v0, &matWorld);
                        D3DXVec3TransformCoord(&v1, &v1, &matWorld);
                        D3DXVec3TransformCoord(&v2, &v2, &matWorld);

                        // バリュエーション補間で接触点を計算
                        D3DXVECTOR3 hitPoint = (1 - u - v) * v0 + u * v1 + v * v2;

                        // 法線ベクトルを計算（クロス積を用いる）
                        D3DXVECTOR3 edge1 = v1 - v0;
                        D3DXVECTOR3 edge2 = v2 - v0;
                        D3DXVECTOR3 hitNormal;
                        D3DXVec3Cross(&hitNormal, &edge1, &edge2);
                        D3DXVec3Normalize(&hitNormal, &hitNormal);

                        // ヒットデータに情報を反映
                        HitData.bHit = true;
                        HitData.HitAngle = hitNormal;  // ヒット角度として法線を設定
                        HitData.ResultDistance = hitPoint - pos;  // 接触点までのベクトル
                        HitData.targetIndex = nIndex;

                        // 後処理
                        pVertexBuffer->Release();
                        pIndexBuffer->Release();
                    }
                }

                pMesh->Release();
            }
        }

        pObject = pObject->GetNext();
        nIndex++;
    }

    HitData.bHit = EscHit;
    if (bLandingHit)
    {
        HitData.HitAngle.y = 1;  // 必要に応じてY軸の角度を修正
    }

    return HitData;
}
