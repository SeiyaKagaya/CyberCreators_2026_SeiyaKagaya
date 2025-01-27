//=========================================================
//
// newbullet[newbullet.cpp]
// Author seiya kagaya
//
//=========================================================
#include "missile.h"
#include "renderer.h"
#include "manager.h"
//#include "Explosion_Bill.h"
#include "3DParticle.h"
#include "enemy_motion_Nomal.h"
#include "enemy_motion_fast.h"
#include "player_motion.h"
#include "ShotFire.h"
#include "enemy_motion_boss.h"
#include "enemy_motion_guard.h"
//#include "ReflectEffect.h"

// 静的メンバ変数の定義
//CMissile* CMissileALL::m_Missile[CMissileALL::MAXMISSILEALL] = { nullptr };


//=============================
// コンストラクタ
//=============================
CMissileALL::CMissileALL(int nPriority) : CObjectX(nPriority)
{

}
//=============================
// デストラクタ
//=============================
CMissileALL::~CMissileALL()
{
}
//=============================
// 初期化
//=============================
HRESULT CMissileALL::Init()
{
    //初期化
    for (int i = 0; i < MAXMISSILEALL; i++)
    {
        m_Missile[i] = nullptr;
    }

    for (int i = 0; i < MAXMISSILEALL; i++)
    {
        m_Missile[i] = CMissile::Create();
        //   pBlock3D->Init();

        m_Missile[i]->SetID(i);

        //m_Missile[i] = pBlock3D;

    }


    SetObjectType(CObject::OBJECT_MISSILE_MNG);


    return E_NOTIMPL;
}
//=============================
// 終了
//=============================
void CMissileALL::Uninit()
{
    for (int i = 0; i < MAXMISSILEALL; i++)
    {
        m_Missile[i]->SetDeath(true);
    }

}

//=============================
// Release
//=============================
void CMissileALL::ReleaseAllBullet()
{
    Uninit();
    delete this;
}

//=============================
// 生成
//=============================
CMissileALL* CMissileALL::Create()
{
    CMissileALL* pMissileALL = new CMissileALL;
    pMissileALL->Init();
    return pMissileALL;

}
//=============================
// Clean
//=============================
void CMissileALL::AllClean()
{
    for (int i = 0; i < MAXMISSILEALL; i++)
    {
        m_Missile[i]->SetbUse(false);
    }

}
//=============================
// 取得
//=============================
CMissile* CMissileALL::GetBulletData(int nNum)
{
    return m_Missile[nNum];
}
//=============================
// 静的にバレットをセット
//=============================
void CMissileALL::SetMissile(CObject::DATA SetData, int ReflectCnt, D3DXCOLOR col, void* pCaller, CMissileALL::SHOTTYPE ShotType)
{
    for (int i = 0; i < MAXMISSILEALL; i++)
    {
        CMissile* pBullet = GetBulletData(i);

        if (m_Missile[i]->GetbUse() == false)
        {


            m_Missile[i]->SetBulletData(SetData, ReflectCnt, col, pCaller, ShotType);

            CRenderer* pRenderer = nullptr;

            CManager* pManager = CManager::GetInstance();

            CSound* pSound = pManager->GetSound();
               pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOTFIRE);

            break;
        }
    }
}
//=============================
// 追尾対象死亡時処理
//=============================
void CMissileALL::KillMissileTarget(void* pCaller)
{
    for (int i = 0; i < MAXMISSILEALL; i++)
    {
        if (m_Missile[i]->GetCaller() == pCaller)
        {//死んだ追尾対象が同一のとき
            m_Missile[i]->SetCaller(nullptr);
            m_Missile[i]->SetbUse(false);
        }
    }
}





















































//------------------------------------------------------------------------------------------------------------------------------------------------------
//=============================
// コンストラクタ
//=============================
CMissile::CMissile(int nPriority) :CObjectX(nPriority)
{
    //  m_nNumBulletAll++;

    m_nLife = 200;

    m_bUse = false;

    m_OBB.m_fLength[0] = 6.0f;
    m_OBB.m_fLength[1] = 6.0f;
    m_OBB.m_fLength[2] = 6.0f;

    m_Reflection = NEWMAXREFLECTION;
    m_ShotByHitEscapeTime = 30;//3フレーム当たり判定抑制
    m_pCaller = nullptr;
}
//=============================
//デストラクタ
//=============================
CMissile::~CMissile()
{
    //   m_nNumBulletAll--;
}
//=============================
//初期化
//=============================
HRESULT CMissile::Init()
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
    D3DXLoadMeshFromX("DATA\\MODEL\\Missile.x",
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

    SetObjectType(CObject::OBJECT_MISSILE);


    //取得
    DATA EscData = GetDATA();

    EscData = GetDATA();//再取得

    //仮

    EscData.MinLength = D3DXVECTOR3(-6.0f, -6.0f, -6.0f);
    EscData.MaxLength = D3DXVECTOR3(6.0f, 6.0f, 6.0f);
    EscData.Radius = 30.0f;


    SetDATA(EscData);//格納


    SetSizeMag(D3DXVECTOR3(0.5f, 0.5f, 0.5f));//大きさ倍率




    return S_OK;
}
//=============================
//破棄
//=============================
void CMissile::Uninit()
{
    CObjectX::Uninit();
}
//=============================
//更新
//=============================
void CMissile::Update()
{
    if (m_bUse == true)
    {
        if (m_bGoodbyNow == false)
        {
            DATA EscData = GetDATA();//再取得

            CRenderer* pRenderer = nullptr;

            CManager* pManager = CManager::GetInstance();


            if (m_DelayCnt > 0)
            {
                m_DelayCnt--;

                EscData.move.x = 0.0f;
                EscData.move.y = 9.0f;
                EscData.move.z = 0.0f;

                // 位置を更新
                EscData.OldPos = EscData.Pos;
                EscData.Pos += EscData.move;
         
                SetDATA(EscData);
            }
            else
            {
                Homing();
            }

    
            m_nLife--;

            if (m_ShotByHitEscapeTime >= 0)
            {
                m_ShotByHitEscapeTime--;
            }


            if (m_nLife <= 0 || m_Reflection < 0)
            {
                CScene::MODE NowState = CScene::GetNowScene();
       
                m_bUse = false;
                return;
            }

            EscData = GetDATA();//再取得

        //OBBまわり
            m_OBB.m_Pos = EscData.Pos;




            D3DXMATRIX matRot;

            //方向ベクトル取得
            D3DXMatrixRotationYawPitchRoll(&matRot, EscData.rot.y, EscData.rot.x, EscData.rot.z);

            m_OBB.m_Direct[0] = D3DXVECTOR3(matRot._11, matRot._12, matRot._13);
            m_OBB.m_Direct[1] = D3DXVECTOR3(matRot._21, matRot._22, matRot._23);
            m_OBB.m_Direct[2] = D3DXVECTOR3(matRot._31, matRot._32, matRot._33);


            HitCollision();

            
          //  EscData.move;//の移動方向にrotをX軸+方向を向ける
            
          //  EscData.rot;

            //--------------------------------------------------------------------------------------------------------------------------------------------------

            DATA ChangeData = DataInit();
       //     DATA classData = GetClassData();


            // 目標方向を計算
            D3DXVECTOR3 enemyDirection = EscData.move;

            // XZ平面上の目標角度を計算
            float targetAngleXZ = atan2f(enemyDirection.z, -enemyDirection.x) + (D3DX_PI * 0.5f);

            // 現在の砲塔のXZ平面上の角度
          //  float currentAngleXZ = fRotTurret;


            // 角度を範囲内に収める
            targetAngleXZ = fmodf(targetAngleXZ + D3DX_PI, 2 * D3DX_PI) - D3DX_PI;

            // 角度の差分
          //  float rotDiff = targetAngleXZ - currentAngleXZ;

            //// 差分が範囲外なら補正---------------------------------------------------------------近いうちちゃんと内容調べる
            //if (fabsf(rotDiff) > D3DX_PI)
            //{
            //    rotDiff = (rotDiff < 0) ? (rotDiff + 2 * D3DX_PI) : (rotDiff - 2 * D3DX_PI);
            //}

            //currentAngleXZ += rotDiff * MOVEROT;

   /*         if (currentAngleXZ > D3DX_PI)
            {
                currentAngleXZ -= (2.0f * D3DX_PI);
            }
            else if (currentAngleXZ < -D3DX_PI)
            {
                currentAngleXZ += (2.0f * D3DX_PI);
            }*/


            ChangeData.rot.y = targetAngleXZ;

            EscData.rot.y = targetAngleXZ;


            float minYAngle = -1.1f; // 下側の角度の限界
            float maxYAngle = 1.1f;  // 上側の角度の限界


            D3DXVECTOR3 SETVEC = EscData.Pos + EscData.move;


            //方向
            enemyDirection = D3DXVECTOR3(SETVEC.x, SETVEC.y, SETVEC.z) - D3DXVECTOR3(GetDATA().Pos.x, GetDATA().Pos.y, GetDATA().Pos.z);

            // XZ平面上の角度
            float angleXZ = atan2f(enemyDirection.z, enemyDirection.x);

          //  ChangeData.rot.x = 0.0f; // よじりを防ぐために必要な調整
            EscData.rot.y = -(angleXZ + 1.57f); // 腰を向ける
          //  ChangeData.rot.z = 0.0f;

            //		 Y軸の角度
            float angleY = (atan2f(enemyDirection.y, sqrtf(enemyDirection.x * enemyDirection.x + enemyDirection.z * enemyDirection.z)));

            //// Y軸角度をクランプ
            //if (angleY < minYAngle)
            //{
            //    angleY = minYAngle;
            //}
            //else if (angleY > maxYAngle)
            //{
            //    angleY = maxYAngle;
            //}

            EscData.rot.x = angleY; // Y方向を向ける


                // 変更データを反映
            //SetChangeDataInObjectMotion(ChangeData);
            //--------------------------------------------------------------------------------------------------------------------------------------------------






















            SetDATA(EscData);//格納

            CObjectX::Update();


            CScene::MODE NowState = CScene::GetNowScene();
            if (NowState == CScene::MODE_GAME || NowState == CScene::MODE_GAME2 || NowState == CScene::MODE_GAME3)
            {//ゲーム中

                D3DXCOLOR SetCol = D3DXCOLOR(m_col.r, m_col.g, m_col.b, 0.4f);

                //       CObject3DParticle::Create(EscData.Pos, SetCol);
                CObject* pObj = nullptr;
                pObj = CObject::GetObjectPoint(CObject::LAYERINDEX_3DPARTICLE_MNG, CObject::OBJECT_3DPARTICLE_MNG);

                if (pObj != nullptr)
                {
                    CObject3DParticleAll* pParticleMNG = static_cast<CObject3DParticleAll*>(pObj);
                    pParticleMNG->SetParticle(EscData.Pos, m_col, 30,60.0f);
                }
            }
        }
        else
        {
            m_nLife--;

            if (m_ShotByHitEscapeTime >= 0)
            {
                m_ShotByHitEscapeTime--;
            }

            if (m_nLife <= 0 || m_Reflection < 0)
            {
                //               SetDeath(true);
                m_bUse = false;
                return;
            }
        }
    }
}
//=============================
//描画
//=============================
void CMissile::Draw()
{
    if (m_bUse == true)
    {
        SizeMagChangebool(true);
        CObjectX::Draw();
    }
}
//=============================
// 当たり判定
//=============================
void CMissile::HitCollision()
{
    if (m_bUse == true)
    {
        //取得
        DATA EscData = GetDATA();

        bool btest = false;

        if (m_HitData.bHit == true)
        {
            m_HitData.bHit = false;
            btest = true;

            int test = m_nID;
            SetGoodby();

            return;
        }


        if (btest == false)
        {//上記判定に引っかからない

            //当たり判定計算
            m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_MISSILE, EscData.Pos, EscData.OldPos, EscData.MinLength, EscData.MaxLength, OBJECT_HITBOX, LAYERINDEX_HITBOX, EscData.move, this);

            if (m_HitData.bHit == false)
            {
                //当たり判定計算
                m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_MISSILE, EscData.Pos, EscData.OldPos, EscData.MinLength, EscData.MaxLength, OBJECT_OBSTACLE, LAYERINDEX_OBSTACLE, EscData.move, this);
            }

            if (m_HitData.bHit == false)
            {
                //当たり判定計算
                m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_MISSILE, EscData.Pos, EscData.OldPos, EscData.MinLength, EscData.MaxLength, OBJECT_HITBOX_2D3D, LAYERINDEX_HITBOX_2D3D, EscData.move, this);
            }

            if (m_HitData.bHit == true)
            {
                CObjectShotFire::Create(EscData.Pos);
                m_bUse = false;
            }


            bool bHit = false;

            if (m_ShotType == CNewBulletALL::SHOTTYPE_PLAYER)
            {//射手がplayer


                // 配置物プライオリティの先頭を取得
                CObject* pObject = CObject::GetpTop(CObject::LAYERINDEX_MOTIONENEMY_NOMAL);

                if (pObject != nullptr)
                { // 先頭がない==プライオリティまるっとない

                    int nIndex = 0;

                    while (pObject != nullptr)
                    {
                        CObjectMotionEnemyNomal* pEnemyNomal = static_cast<CObjectMotionEnemyNomal*>(pObject);

                        COBB pObb2 = pEnemyNomal->GetOBB();


                        D3DXVECTOR3 HitPos;
                        bHit = CMathProc::ColOBBs(m_OBB, pObb2, &HitPos);//当たり判定

                        if (bHit == true)
                        {
                            pEnemyNomal->SetDamage(100);
                            CObjectShotFire::Create(EscData.Pos);
                            m_bUse = false;
                            break;

                        }
                        else
                        {
                            CObject* pNext = pObject->GetNext();
                            pObject = pNext;
                            nIndex++;
                        }
                    }
                }

                if (bHit == false)
                {//接触無し

                    // 配置物プライオリティの先頭を取得
                    CObject* pObject = CObject::GetpTop(CObject::LAYERINDEX_MOTIONENEMY_FAST);

                    if (pObject != nullptr)
                    { // 先頭がない==プライオリティまるっとない

                        int nIndex = 0;

                        while (pObject != nullptr)
                        {
                            CObjectMotionEnemyfast* pEnemyFast = static_cast<CObjectMotionEnemyfast*>(pObject);

                            COBB pObb2 = pEnemyFast->GetOBB();


                            D3DXVECTOR3 HitPos;
                            bHit = CMathProc::ColOBBs(m_OBB, pObb2, &HitPos);//当たり判定

                            if (bHit == true)
                            {
                                pEnemyFast->SetDamage(100);
                                CObjectShotFire::Create(EscData.Pos);
                                m_bUse = false;
                                break;
                            }
                            else
                            {
                                CObject* pNext = pObject->GetNext();
                                pObject = pNext;
                                nIndex++;
                            }
                        }
                    }
                }


                if (bHit == false)
                {//接触無し

                    // 配置物プライオリティの先頭を取得
                    CObject* pObject = CObject::GetpTop(CObject::LAYERINDEX_MOTIONENEMY_BOSS);

                    if (pObject != nullptr)
                    { // 先頭がない==プライオリティまるっとない

                        int nIndex = 0;

                        while (pObject != nullptr)
                        {
                            CObjectMotionEnemyBoss* pEnemyBoss = static_cast<CObjectMotionEnemyBoss*>(pObject);

                            COBB pObb2 = pEnemyBoss->GetOBB();


                            D3DXVECTOR3 HitPos;
                            bHit = CMathProc::ColOBBs(m_OBB, pObb2, &HitPos);//当たり判定

                            if (bHit == true)
                            {
                                pEnemyBoss->SetDamage(35);
                                CObjectShotFire::Create(EscData.Pos);
                                m_bUse = false;
                                break;
                            }
                            else
                            {
                                CObject* pNext = pObject->GetNext();
                                pObject = pNext;
                                nIndex++;
                            }
                        }
                    }
                }


                if (bHit == false)
                {//接触無し

                    // 配置物プライオリティの先頭を取得
                    CObject* pObject = CObject::GetpTop(CObject::LAYERINDEX_MOTIONENEMY_BOSS_GUARD);

                    if (pObject != nullptr)
                    { // 先頭がない==プライオリティまるっとない

                        int nIndex = 0;

                        while (pObject != nullptr)
                        {
                            CObjectMotionEnemyGuard* pEnemyBoss = static_cast<CObjectMotionEnemyGuard*>(pObject);

                            COBB pObb2 = pEnemyBoss->GetOBB();


                            D3DXVECTOR3 HitPos;
                            bHit = CMathProc::ColOBBs(m_OBB, pObb2, &HitPos);//当たり判定

                            if (bHit == true)
                            {
                                pEnemyBoss->SetDamage(35);
                                CObjectShotFire::Create(EscData.Pos);
                                m_bUse = false;
                                break;
                            }
                            else
                            {
                                CObject* pNext = pObject->GetNext();
                                pObject = pNext;
                                nIndex++;
                            }
                        }
                    }
                }









            }
            else if (m_ShotType == CNewBulletALL::SHOTTYPE_ENEMY)
            {//射手がenemy
                   // 配置物プライオリティの先頭を取得
                CObject* pObject = CObject::GetpTop(CObject::LAYERINDEX_MOTIONPLAYER);

                if (pObject != nullptr)
                { // 先頭がない==プライオリティまるっとない

                    int nIndex = 0;

                    while (pObject != nullptr)
                    {
                        CObjectMotionPlayer* pPlayer = static_cast<CObjectMotionPlayer*>(pObject);

                        COBB pObb2 = pPlayer->GetOBB();


                        D3DXVECTOR3 HitPos;
                        bHit = CMathProc::ColOBBs(m_OBB, pObb2, &HitPos);//当たり判定

                        if (bHit == true)
                        {
                            pPlayer->SetDamage(85);
                            CObjectShotFire::Create(EscData.Pos);
                            m_bUse = false;
                            break;
                        }
                        else
                        {
                            CObject* pNext = pObject->GetNext();
                            pObject = pNext;
                            nIndex++;
                        }
                    }
                }
            }
        }
    }
}
//=============================
// 反射回数格納
//=============================
void CMissile::SetReflect(int nCnt)
{
    m_nReflect = nCnt;
}
//=============================
// 親を格納
//=============================
void CMissile::SetCaller(void* pCaller)
{
    m_pCaller = pCaller;
}
//=============================
// 色格納
//=============================
void CMissile::SetCOL(D3DXCOLOR col)
{
    m_col = col;
}
//=============================
// たまをクリエイト
//=============================
CMissile* CMissile::Create()
{
    CMissile* pBlock3D = new CMissile;
    pBlock3D->Init();
    return pBlock3D;
}

//=============================
// bUseをへんこう
//=============================
void CMissile::SetbUse(bool bUse)
{
    m_bUse = bUse;
}
//=============================
// bUseを取得
//=============================
bool CMissile::GetbUse()
{
    return m_bUse;
}
//=============================
// セットする
//=============================
void CMissile::SetBulletData(DATA SetData, int ReflectCnt, D3DXCOLOR col, void* pCaller, CMissileALL::SHOTTYPE ShotType)
{
    //取得
    DATA EscData = GetDATA();

    m_ShotType = ShotType;



    EscData = SetData;//移す

    EscData.MinLength = D3DXVECTOR3(-30.0f, -30.0f, -30.0f);
    EscData.MaxLength = D3DXVECTOR3(30.0f, 30.0f, 30.0f);
    EscData.Radius = 30.0f;

    SetDATA(EscData);//格納
    m_Reflection = ReflectCnt;
    m_pCaller = pCaller;
    m_col = col;

    SetChangeColor(col);//モデルColorも変更
    SetColorChangeBool(true);//色変更をtrueに

    m_nLife = 500;

    m_OBB.m_fLength[0] = 15.0f;
    m_OBB.m_fLength[1] = 15.0f;
    m_OBB.m_fLength[2] = 30.0f;

    m_ShotByHitEscapeTime = 30;//3フレーム当たり判定抑制

    m_bGoodbyNow = false;
    m_bUse = true;
    m_DelayCnt = 30;
}
//===========================
//当たり判定回避時間を返す
//===========================
int CMissile::GetHitEscapeTime()
{
    return m_ShotByHitEscapeTime;
}
//===========================
//OBBを返す
//===========================

COBB CMissile::GetOBB()
{
    return m_OBB;
}

//===========================
//親取得
//===========================
void* CMissile::GetCaller()
{
    return m_pCaller;
}


//===========================
//バグの回避策 
//===========================
void CMissile::SetGoodby()
{ //取得

    int Test = m_nID;

    DATA EscData = GetDATA();

    EscData.Pos = D3DXVECTOR3(-3000.0, -3000.0f, -3000.0f);
    EscData.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    EscData.Radius = 30.0f;
    EscData.MinLength = D3DXVECTOR3(-30.0f, -30.0f, -30.0f);
    EscData.MaxLength = D3DXVECTOR3(30.0f, 30.0f, 30.0f);

    SetDATA(EscData);//格納
    m_bUse = false;
    m_bGoodbyNow = true;

}
//===========================
//ID取得
//===========================

int CMissile::GetID()
{
    return m_nID;
}
//===========================
//IDセット
//===========================
void CMissile::SetID(int nID)
{
    m_nID = nID;
}
//===========================
//誘導処理
//===========================
void CMissile::Homing()
{


    if (m_ShotType == CMissileALL::SHOTTYPE_PLAYER)
    {//プレイヤー弾
        
                CObjectMotion* pObj = static_cast<CObjectMotion*>(m_pCaller);

                DATA ESCDATA = pObj->GetClassData();

           
                D3DXVECTOR3 targetDirection = D3DXVECTOR3(pObj->GetClassData().Pos.x, pObj->GetClassData().Pos.y + 50.0f, pObj->GetClassData().Pos.z) - GetDATA().Pos;
                D3DXVec3Normalize(&targetDirection, &targetDirection);

                D3DXVECTOR3 SetMove = GetDATA().move;

                // ミサイルの移動方向を変更
                ChangeVectorDirection(SetMove, targetDirection, D3DX_PI / 180.0f * MISSILEROT); // 適切な値に変更してください

                // ミサイルの速さを調整するための倍率
               // float missileSpeedMultiplier = MISSILEMOVESPEED; // 適切な値に変更してください

                DATA SetData = GetDATA();

                SetData.move = SetMove;

                // 位置を更新
                SetData.OldPos = SetData.Pos;
                SetData.Pos += SetData.move * MISSILEMOVESPEED * 1.2f;
             
               SetDATA(SetData);
    }
    else  if (m_ShotType == CMissileALL::SHOTTYPE_ENEMY)
    {//敵弾

            //playerの位置を取得
        CObject* pObj = nullptr;
        pObj = CObject::GetObjectPoint(CObject::LAYERINDEX_MOTIONPLAYER, CObject::OBJECT_MOTIONPLAYER);

        D3DXVECTOR3 TargetPos = {};

        CObject::DATA EscData;

        if (pObj != nullptr)
        {
            CObjectMotionPlayer* pPlayer = static_cast<CObjectMotionPlayer*>(pObj);

            EscData = pPlayer->GetClassData();
            EscData.Pos.y += 130.0f;
        }

        ///CObjectMotionPlayer* pObj = static_cast<CObjectMotionPlayer*>(m_pCaller);

 //       D3DXVECTOR3 targetDirection = pObj->GetDATA().Pos - GetDATA().Pos;
//        D3DXVec3Normalize(&targetDirection, &targetDirection);

         // 目標への方向ベクトル
        D3DXVECTOR3 targetDirection = EscData.Pos - GetDATA().Pos;

        D3DXVec3Normalize(&targetDirection, &targetDirection);//正規化

        D3DXVECTOR3 SetMove = GetDATA().move;

        // ミサイルの移動方向を変更
        ChangeVectorDirection(SetMove, targetDirection, D3DX_PI / 180.0f * MISSILEROT * 0.15f); // 適切な値に変更してください

        // ミサイルの速さを調整するための倍率
       // float missileSpeedMultiplier = MISSILEMOVESPEED; // 適切な値に変更してください

        DATA SetData = GetDATA();

        SetData.move = SetMove;

         // 位置を更新
        SetData.OldPos = SetData.Pos;
        SetData.Pos += SetData.move * MISSILEMOVESPEED * 0.3f;
    

        SetDATA(SetData);
    }
}
//===========================
// ベクトルの大きさを保ちつつ角度を変更する関数
//===========================
void CMissile::ChangeVectorDirection(D3DXVECTOR3& vector, const D3DXVECTOR3& newDirection, float maxAngleChange)
{
    D3DXVECTOR3 currentDirection = vector;
    D3DXVECTOR3 targetDirection = newDirection;

    D3DXVec3Normalize(&currentDirection, &currentDirection);
    D3DXVec3Normalize(&targetDirection, &targetDirection);

    float dotProduct = D3DXVec3Dot(&currentDirection, &targetDirection);

    if (dotProduct < cos(maxAngleChange))
    {
        // 角度変更が制限を越える場合は、角度を制限内に収めつつ方向を変更
        D3DXVECTOR3 rotatedDirection;
        D3DXVec3Cross(&rotatedDirection, &currentDirection, &targetDirection);
        D3DXVec3Normalize(&rotatedDirection, &rotatedDirection);

        D3DXMATRIX rotationMatrix;
        D3DXMatrixRotationAxis(&rotationMatrix, &rotatedDirection, maxAngleChange);

        D3DXVec3TransformNormal(&currentDirection, &currentDirection, &rotationMatrix);
        vector = currentDirection;
    }
    else
    {
        // 制限内の場合は、直接方向を変更
        vector = targetDirection;
    }
}


