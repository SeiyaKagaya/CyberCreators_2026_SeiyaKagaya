//=========================================================
//
// newbullet[newbullet.cpp]
// Author seiya kagaya
//
//=========================================================
#include "newbullet.h"
#include "renderer.h"
#include "manager.h"
//#include "Explosion_Bill.h"
#include "3DParticle.h"
//#include "ReflectEffect.h"

// 静的メンバ変数の定義
//CNewBullet* CNewBulletALL::m_NewBullet[CNewBulletALL::MAXBULLETALL] = { nullptr };


//=============================
// コンストラクタ
//=============================
CNewBulletALL::CNewBulletALL(int nPriority) : CObjectX(nPriority)
{

}
//=============================
// デストラクタ
//=============================
CNewBulletALL::~CNewBulletALL()
{
}
//=============================
// 初期化
//=============================
HRESULT CNewBulletALL::Init()
{
    //初期化
    for (int i = 0; i < MAXBULLETALL; i++)
    {
        m_NewBullet[i] = nullptr;
    }

    for (int i = 0; i < MAXBULLETALL; i++)
    {
        m_NewBullet[i] = CNewBullet::Create(); 
     //   pBlock3D->Init();

        m_NewBullet[i]->SetID(i);

        //m_NewBullet[i] = pBlock3D;

    }


    SetObjectType(CObject::OBJECT_NEWBULLET_MNG);


    return E_NOTIMPL;
}
//=============================
// 終了
//=============================
void CNewBulletALL::Uninit()
{
    for (int i = 0; i < MAXBULLETALL; i++)
    {
         m_NewBullet[i]->SetDeath(true);
    }

}
void CNewBulletALL::Update()
{
}
void CNewBulletALL::Draw()
{
}
//=============================
// Release
//=============================
void CNewBulletALL::ReleaseAllBullet()
{
    Uninit();
    delete this;
}

//=============================
// 生成
//=============================
CNewBulletALL* CNewBulletALL::Create()
{
    CNewBulletALL* pNewBulletALL = new CNewBulletALL;
    pNewBulletALL->Init();
    return pNewBulletALL;

}
//=============================
// Clean
//=============================
void CNewBulletALL::AllClean()
{
    for (int i = 0; i < MAXBULLETALL; i++)
    {
        m_NewBullet[i]->SetbUse(false);
    }

}
//=============================
// 取得
//=============================
CNewBullet* CNewBulletALL::GetBulletData(int nNum) 
{
    return m_NewBullet[nNum];
}
//=============================
// 静的にバレットをセット
//=============================
void CNewBulletALL::SetBullet(CObject::DATA SetData, int ReflectCnt, D3DXCOLOR col, void* pCaller)
{
    for (int i = 0; i < MAXBULLETALL; i++)
    {
        CNewBullet* pBullet = GetBulletData(i);

        if (m_NewBullet[i]->GetbUse() == false)
        {
  
         
            m_NewBullet[i]->SetBulletData(SetData, ReflectCnt, col, pCaller);

            CRenderer* pRenderer = nullptr;

            CManager* pManager = CManager::GetInstance();

            CSound* pSound = pManager->GetSound();
         //   pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOTFIRE);

            break;
        }
    }
}





















































//------------------------------------------------------------------------------------------------------------------------------------------------------
//=============================
// コンストラクタ
//=============================
CNewBullet::CNewBullet(int nPriority) :CObjectX(nPriority)
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
CNewBullet::~CNewBullet()
{
 //   m_nNumBulletAll--;
}
//=============================
//初期化
//=============================
HRESULT CNewBullet::Init()
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
    D3DXLoadMeshFromX("DATA\\MODEL\\Bullet2.x",
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

    SetObjectType(CObject::OBJECT_NEWBULLET);


    //取得
    DATA EscData = GetDATA();

    EscData = GetDATA();//再取得

    //仮
    
    EscData.MinLength = D3DXVECTOR3(-6.0f, -6.0f, -6.0f);
    EscData.MaxLength = D3DXVECTOR3(6.0f, 6.0f, 6.0f);
    EscData.Radius = 30.0f;


    SetDATA(EscData);//格納


    SetSizeMag(D3DXVECTOR3(1.5f, 1.5f, 1.5f));//大きさ倍率




    return S_OK;
}
//=============================
//破棄
//=============================
void CNewBullet::Uninit()
{
    CObjectX::Uninit();
}
//=============================
//更新
//=============================
void CNewBullet::Update()
{
    if (m_bUse == true)
    {
        if (m_bGoodbyNow == false)
        {
            DATA EscData = GetDATA();//再取得

            CRenderer* pRenderer = nullptr;

            CManager* pManager = CManager::GetInstance();

            EscData.OldPos = EscData.Pos;
            EscData.Pos += EscData.move;



            SetDATA(EscData);//格納

            HitCollision();

            m_nLife--;

            if (m_ShotByHitEscapeTime >= 0)
            {
                m_ShotByHitEscapeTime--;
            }


            if (m_nLife <= 0 || m_Reflection < 0)
            {
                CScene::MODE NowState = CScene::GetNowScene();
                if (NowState == CScene::MODE_GAME || NowState == CScene::MODE_GAME2)
                {//ゲーム中
                 //   CObjectExplosionBill::Create(EscData.Pos);
                }
                //	Uninit();

 //               SetDeath(true);
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

            SetDATA(EscData);//格納

            CObjectX::Update();


            CScene::MODE NowState = CScene::GetNowScene();
            if (NowState == CScene::MODE_GAME || NowState == CScene::MODE_GAME2 )
            {//ゲーム中

                D3DXCOLOR SetCol = D3DXCOLOR(m_col.r, m_col.g, m_col.b, 0.2f);

                CObject3DParticle::Create(EscData.Pos, SetCol);

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
void CNewBullet::Draw()
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
void CNewBullet::HitCollision()
{
    if (m_bUse == true)
    {
        //取得
        DATA EscData = GetDATA();

        bool btest = false;

     //   m_HitData = CMathProc::CheckCircleCollision(EscData.Pos, EscData.Radius, OBJECT_NEWBULLET, LAYERINDEX_NEWBULLET, this,m_nID);

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
            m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_NEWBULLET, EscData.Pos, EscData.OldPos, EscData.MinLength, EscData.MaxLength, OBJECT_HITBOX, LAYERINDEX_HITBOX, EscData.move, this);

            if (m_HitData.bHit == false)
            {
                //当たり判定計算
                m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_NEWBULLET, EscData.Pos, EscData.OldPos, EscData.MinLength, EscData.MaxLength, OBJECT_OBSTACLE, LAYERINDEX_OBSTACLE, EscData.move, this);
            }

            if (m_HitData.bHit == false)
            {
                //当たり判定計算
                m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_MOTIONPLAYER, EscData.Pos, EscData.OldPos, EscData.MinLength, EscData.MaxLength, OBJECT_HITBOX_2D3D, LAYERINDEX_HITBOX_2D3D, EscData.move, this);
            }



            //if (m_HitData.bHit == false)
            //{
            //    //当たり判定計算
            //    m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_MOTIONPLAYER, EscData.Pos, EscData.OldPos, EscData.MinLength, EscData.MaxLength, OBJECT_HITBOX_2D3D, LAYERINDEX_HITBOX_2D3D, EscData.move, this);

            //}




            if (m_HitData.bHit == true)
            {//接触
                CScene::MODE NowState = CScene::GetNowScene();
                if (NowState == CScene::MODE_GAME || NowState == CScene::MODE_GAME2)
                {//ゲーム中

              //      CObjectReflectEffect::Create(EscData.Pos);
                }
                EscData.move = m_HitData.ReflectionVector;


                //// 進行方向の計算
                //float Angle = atan2f(EscData.move.x, EscData.move.y) + D3DX_PI;

                ////classData.rot の更新
                //EscData.rot.z = Angle;
             //   float angle = atan2f(EscData.move.y, EscData.move.x); // Y成分を先に
              //  EscData.rot.z = angle; // Z軸の回転を更新

                m_Reflection--;
            }
        }

        SetDATA(EscData);//格納

        m_HitData.bHit = false;
    }
}
//=============================
// 反射回数格納
//=============================
void CNewBullet::SetReflect(int nCnt)
{
    m_nReflect = nCnt;
}
//=============================
// 親を格納
//=============================
void CNewBullet::SetCaller(void* pCaller)
{
    m_pCaller = pCaller;
}
//=============================
// 色格納
//=============================
void CNewBullet::SetCOL(D3DXCOLOR col)
{
    m_col = col;
}
//=============================
// たまをクリエイト
//=============================
CNewBullet* CNewBullet::Create()
{
    CNewBullet* pBlock3D = new CNewBullet;
    pBlock3D->Init();
    return pBlock3D;
}

//=============================
// bUseをへんこう
//=============================
void CNewBullet::SetbUse(bool bUse)
{
    m_bUse = bUse;
}
//=============================
// bUseを取得
//=============================
bool CNewBullet::GetbUse()
{
    return m_bUse;
}
//=============================
// セットする
//=============================
void CNewBullet::SetBulletData(DATA SetData, int ReflectCnt, D3DXCOLOR col, void* pCaller)
{
    //取得
    DATA EscData = GetDATA();






    EscData = SetData;//移す

    EscData.MinLength = D3DXVECTOR3(-30.0f, -30.0f, -30.0f);
    EscData.MaxLength = D3DXVECTOR3(30.0f, 30.0f, 30.0f);
    EscData.Radius = 30.0f;

    SetDATA(EscData);//格納
    m_Reflection= ReflectCnt;
    m_pCaller = pCaller;
    m_col = col;

    SetChangeColor(col);//モデルColorも変更
    SetColorChangeBool(true);//色変更をtrueに

    m_nLife = 120;

    m_OBB.m_fLength[0] = 15.0f;
    m_OBB.m_fLength[1] = 15.0f;
    m_OBB.m_fLength[2] = 30.0f;

    m_ShotByHitEscapeTime = 30;//3フレーム当たり判定抑制

    m_bGoodbyNow = false;
    m_bUse = true;

}
//===========================
//当たり判定回避時間を返す
//===========================
int CNewBullet::GetHitEscapeTime()
{
    return m_ShotByHitEscapeTime;
}
//===========================
//OBBを返す
//===========================

COBB CNewBullet::GetOBB()
{
    return m_OBB;
}

//===========================
//親取得
//===========================
void* CNewBullet::GetCaller()
{
    return m_pCaller;
}


//===========================
//バグの回避策 
//===========================
void CNewBullet::SetGoodby()
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

int CNewBullet::GetID()
{
    return m_nID;
}
//===========================
//IDセット
//===========================
void CNewBullet::SetID(int nID)
{
    m_nID = nID;
}

