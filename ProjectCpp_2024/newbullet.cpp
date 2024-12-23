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
#include "enemy_motion_Nomal.h"
#include "enemy_motion_fast.h"
#include "player_motion.h"
#include "ShotFire.h"
#include "enemy_motion_boss.h"
#include "enemy_motion_guard.h"
//#include "ReflectEffect.h"

// �ÓI�����o�ϐ��̒�`
//CNewBullet* CNewBulletALL::m_NewBullet[CNewBulletALL::MAXBULLETALL] = { nullptr };


//=============================
// �R���X�g���N�^
//=============================
CNewBulletALL::CNewBulletALL(int nPriority) : CObjectX(nPriority)
{

}
//=============================
// �f�X�g���N�^
//=============================
CNewBulletALL::~CNewBulletALL()
{
}
//=============================
// ������
//=============================
HRESULT CNewBulletALL::Init()
{
    //������
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
// �I��
//=============================
void CNewBulletALL::Uninit()
{
    for (int i = 0; i < MAXBULLETALL; i++)
    {
         m_NewBullet[i]->SetDeath(true);
    }

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
// ����
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
// �擾
//=============================
CNewBullet* CNewBulletALL::GetBulletData(int nNum) 
{
    return m_NewBullet[nNum];
}
//=============================
// �ÓI�Ƀo���b�g���Z�b�g
//=============================
void CNewBulletALL::SetBullet(CObject::DATA SetData, int ReflectCnt, D3DXCOLOR col, void* pCaller, CNewBulletALL::SHOTTYPE ShotType)
{
    D3DXVECTOR3 ESCTargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

    for (int i = 0; i < MAXBULLETALL; i++)
    {
        if (m_NewBullet[i]->GetbUse() == false)
        {
            CManager* pManager = CManager::GetInstance();

            CInputKeyboard* keyboard = pManager->GetKeyboard();

            CInputJoyPad* JoyPad = pManager->GetJoyPad();

            XINPUT_STATE joykeystate;

            //�V���C�p�b�g�̏�Ԃ��擾
            DWORD dwResult = XInputGetState(0, &joykeystate);

            if (pManager->GetbNow3DMode() == false)
            {//2D
            }
            else
            {//3D

                if (ShotType == CNewBulletALL::SHOTTYPE_PLAYER)
                {//�ˎ肪player
                    CNewBullet* pBullet = GetBulletData(i);



                    bool bChange = false;

                    // �z�u���v���C�I���e�B�̐擪���擾
                    CObject* pObject = CObject::GetpTop(LAYERINDEX_MOTIONENEMY_FAST);

                    if (pObject != nullptr)
                    { // �擪���Ȃ�==�v���C�I���e�B�܂���ƂȂ�

                        CObjectMotionEnemyfast* pEnemyFast;
                        pEnemyFast = (CObjectMotionEnemyfast*)pObject;

                        while (pObject != nullptr)
                        {
                            CObject::DATA EscEnemyData = pEnemyFast->GetClassData();

                            if (pEnemyFast->GetLockOnUIMain()->bGetDrawOk() == true)
                            {//�o���b�g���b�N�I�����`����

                                D3DXVECTOR3 EscPos= D3DXVECTOR3(pEnemyFast->GetClassData().Pos.x, pEnemyFast->GetClassData().Pos.y + CObjectMotionEnemyfast::LOCKDIFF, pEnemyFast->GetClassData().Pos.z);

                                   // TargetPos ���� SetData.Pos �ւ̕����x�N�g�����v�Z
                                D3DXVECTOR3 direction2 = EscPos - SetData.Pos;


                                float speed = (int)CObjectMotionPlayer::BULLETSPEED;//���x(��X�ύX)
                                SetData.move = direction2;//���x��������


                                ESCTargetPos = CMathProc::SetPositionldPredictedImpactPoint(SetData.Pos, SetData.move, EscPos, pEnemyFast->GetClassData().move, (float)CObjectMotionPlayer::BULLETSPEED);

                                D3DXVECTOR3 POSPOS = pEnemyFast->GetClassData().Pos;

                                bChange = true;
                                break;
                            }
                            else
                            {
                                CObject* pNext = pObject->GetNext();
                                pObject = pNext;
                                pEnemyFast = (CObjectMotionEnemyfast*)pObject;
                            }
                        }
                    }


                    if (bChange == false)
                    {
                        // �z�u���v���C�I���e�B�̐擪���擾
                        pObject = CObject::GetpTop(LAYERINDEX_MOTIONENEMY_NOMAL);

                        if (pObject != nullptr)
                        { // �擪���Ȃ�==�v���C�I���e�B�܂���ƂȂ�

                            CObjectMotionEnemyNomal* pEnemyNomal;
                            pEnemyNomal = (CObjectMotionEnemyNomal*)pObject;

                            while (pObject != nullptr)
                            {
                                CObject::DATA EscEnemyData = pEnemyNomal->GetClassData();

                                if (pEnemyNomal->GetLockOnUIMain()->bGetDrawOk() == true)
                                {//�o���b�g���b�N�I�����`����

                                    D3DXVECTOR3 EscPos = D3DXVECTOR3(pEnemyNomal->GetClassData().Pos.x, pEnemyNomal->GetClassData().Pos.y + CObjectMotionEnemyNomal::LOCKDIFF, pEnemyNomal->GetClassData().Pos.z);

                                    // TargetPos ���� SetData.Pos �ւ̕����x�N�g�����v�Z
                                    D3DXVECTOR3 direction2 = EscPos - SetData.Pos;

                                    float speed = (int)CObjectMotionPlayer::BULLETSPEED;//���x(��X�ύX)
                                    SetData.move = direction2;//���x��������

                                    ESCTargetPos = CMathProc::SetPositionldPredictedImpactPoint(SetData.Pos, SetData.move, EscPos, pEnemyNomal->GetClassData().move, (float)CObjectMotionPlayer::BULLETSPEED);
                                    bChange = true;
                                    break;
                                }
                                else
                                {
                                    CObject* pNext = pObject->GetNext();
                                    pObject = pNext;
                                    pEnemyNomal = (CObjectMotionEnemyNomal*)pObject;


                                }
                            }
                        }
                    }






                    if (bChange == false)
                    {
                        // �z�u���v���C�I���e�B�̐擪���擾
                        pObject = CObject::GetpTop(LAYERINDEX_MOTIONENEMY_BOSS);

                        if (pObject != nullptr)
                        { // �擪���Ȃ�==�v���C�I���e�B�܂���ƂȂ�

                            CObjectMotionEnemyBoss* pEnemyBoss;
                            pEnemyBoss = (CObjectMotionEnemyBoss*)pObject;

                            while (pObject != nullptr)
                            {
                                CObject::DATA EscEnemyData = pEnemyBoss->GetClassData();

                                if (pEnemyBoss->GetLockOnUIMain()->bGetDrawOk() == true)
                                {//�o���b�g���b�N�I�����`����

                                    D3DXVECTOR3 EscPos = D3DXVECTOR3(pEnemyBoss->GetClassData().Pos.x, pEnemyBoss->GetClassData().Pos.y + CObjectMotionEnemyBoss::LOCKDIFF, pEnemyBoss->GetClassData().Pos.z);

                                    // TargetPos ���� SetData.Pos �ւ̕����x�N�g�����v�Z
                                    D3DXVECTOR3 direction2 = EscPos - SetData.Pos;

                                    float speed = (int)CObjectMotionPlayer::BULLETSPEED;//���x(��X�ύX)
                                    SetData.move = direction2;//���x��������

                                    ESCTargetPos = CMathProc::SetPositionldPredictedImpactPoint(SetData.Pos, SetData.move, EscPos, pEnemyBoss->GetClassData().move, (float)CObjectMotionPlayer::BULLETSPEED);
                                    bChange = true;
                                    break;
                                }
                                else
                                {
                                    CObject* pNext = pObject->GetNext();
                                    pObject = pNext;
                                    pEnemyBoss = (CObjectMotionEnemyBoss*)pObject;


                                }
                            }
                        }
                    }




                    if (bChange == false)
                    {
                        // �z�u���v���C�I���e�B�̐擪���擾
                        pObject = CObject::GetpTop(LAYERINDEX_MOTIONENEMY_BOSS_GUARD);

                        if (pObject != nullptr)
                        { // �擪���Ȃ�==�v���C�I���e�B�܂���ƂȂ�

                            CObjectMotionEnemyGuard* pEnemyGuard;
                            pEnemyGuard = (CObjectMotionEnemyGuard*)pObject;

                            while (pObject != nullptr)
                            {
                                CObject::DATA EscEnemyData = pEnemyGuard->GetClassData();

                                if (pEnemyGuard->GetLockOnUIMain()->bGetDrawOk() == true)
                                {//�o���b�g���b�N�I�����`����

                                    D3DXVECTOR3 EscPos = D3DXVECTOR3(pEnemyGuard->GetClassData().Pos.x, pEnemyGuard->GetClassData().Pos.y + CObjectMotionEnemyGuard::LOCKDIFF, pEnemyGuard->GetClassData().Pos.z);

                                    // TargetPos ���� SetData.Pos �ւ̕����x�N�g�����v�Z
                                    D3DXVECTOR3 direction2 = EscPos - SetData.Pos;

                                    float speed = (int)CObjectMotionPlayer::BULLETSPEED;//���x(��X�ύX)
                                    SetData.move = direction2;//���x��������

                                    ESCTargetPos = CMathProc::SetPositionldPredictedImpactPoint(SetData.Pos, SetData.move, EscPos, pEnemyGuard->GetClassData().move, (float)CObjectMotionPlayer::BULLETSPEED);
                                    bChange = true;
                                    break;
                                }
                                else
                                {
                                    CObject* pNext = pObject->GetNext();
                                    pObject = pNext;
                                    pEnemyGuard = (CObjectMotionEnemyGuard*)pObject;


                                }
                            }
                        }
                    }


















                    if (bChange == true)
                    {
                        // TargetPos ���� SetData.Pos �ւ̕����x�N�g�����v�Z
                        D3DXVECTOR3 direction = ESCTargetPos - SetData.Pos;

                        D3DXVec3Normalize(&direction, &direction);

                        float speed = (float)CObjectMotionPlayer::BULLETSPEED;//���x(��X�ύX)
                        SetData.move = direction * speed;//���x��������
                    }

                }
            }












            m_NewBullet[i]->SetBulletData(SetData, ReflectCnt, col, pCaller, ShotType);


            CSound* pSound = pManager->GetSound();
            //   pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOTFIRE);

            break;
        }
    }
}





















































//------------------------------------------------------------------------------------------------------------------------------------------------------
//=============================
// �R���X�g���N�^
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
    m_ShotByHitEscapeTime = 30;//3�t���[�������蔻��}��
    m_pCaller = nullptr;
}
//=============================
//�f�X�g���N�^
//=============================
CNewBullet::~CNewBullet()
{
 //   m_nNumBulletAll--;
}
//=============================
//������
//=============================
HRESULT CNewBullet::Init()
{

    CObjectX::Init();

    CRenderer* pRenderer = nullptr;

    CManager* pManager = CManager::GetInstance();

    pRenderer = pManager->GetRenderer();

    LPD3DXMESH pMesh = nullptr;//Mesh�|�C���^
    LPD3DXBUFFER pBuffMat = nullptr;//�}�e���A���ւ̃|�C���^
    DWORD dwNumMat = 0;//�}�e���A���̐�

    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();
    //�t�@�C���̓ǂݍ���
    D3DXLoadMeshFromX("DATA\\MODEL\\Bullet2.x",
        D3DXMESH_SYSTEMMEM,
        EscDevice,
        NULL,
        &pBuffMat,
        NULL,
        &dwNumMat,
        &pMesh);

    //�}�e���A���f�[�^�ւ̃|�C���^���擾
    D3DXMATERIAL* pMat = (D3DXMATERIAL*)pBuffMat->GetBufferPointer();

    for (int nCntMat = 0; nCntMat < (int)dwNumMat; nCntMat++)
    {
        // �f�B�t���[�Y�J���[���T�C�Y�Ɋ�Â��ĕύX
        D3DXCOLOR originalColor = pMat[nCntMat].MatD3D.Diffuse;

        pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//�F�������Ŏw��
    }

    SetXfireData(pMesh, pBuffMat, dwNumMat);//�f�[�^�i�[

    SetObjectType(CObject::OBJECT_NEWBULLET);


    //�擾
    DATA EscData = GetDATA();

    EscData = GetDATA();//�Ď擾

    //��
    
    EscData.MinLength = D3DXVECTOR3(-6.0f, -6.0f, -6.0f);
    EscData.MaxLength = D3DXVECTOR3(6.0f, 6.0f, 6.0f);
    EscData.Radius = 30.0f;


    SetDATA(EscData);//�i�[


    SetSizeMag(D3DXVECTOR3(1.5f, 1.5f, 1.5f));//�傫���{��




    return S_OK;
}
//=============================
//�j��
//=============================
void CNewBullet::Uninit()
{
    CObjectX::Uninit();
}
//=============================
//�X�V
//=============================
void CNewBullet::Update()
{
    if (m_bUse == true)
    {
        if (m_bGoodbyNow == false)
        {
            DATA EscData = GetDATA();//�Ď擾

            CRenderer* pRenderer = nullptr;

            CManager* pManager = CManager::GetInstance();

            EscData.OldPos = EscData.Pos;
            EscData.Pos += EscData.move;



            SetDATA(EscData);//�i�[



            m_nLife--;

            if (m_ShotByHitEscapeTime >= 0)
            {
                m_ShotByHitEscapeTime--;
            }


            if (m_nLife <= 0 || m_Reflection < 0)
            {
                CScene::MODE NowState = CScene::GetNowScene();
                if (NowState == CScene::MODE_GAME || NowState == CScene::MODE_GAME2)
                {//�Q�[����
                 //   CObjectExplosionBill::Create(EscData.Pos);
                }
                //	Uninit();

 //               SetDeath(true);
                m_bUse = false;

                DATA EscData = GetDATA();//�Ď擾

                EscData.OldPos = D3DXVECTOR3(0.0f,-100000.0f,0.0f);
                EscData.Pos = D3DXVECTOR3(0.0f, -100000.0f, 0.0f);

                SetDATA(EscData);//�i�[

                return;
            }

            EscData = GetDATA();//�Ď擾

           
          


        //OBB�܂��
            m_OBB.m_Pos = EscData.Pos;

            D3DXMATRIX matRot;

            //�����x�N�g���擾
            D3DXMatrixRotationYawPitchRoll(&matRot, EscData.rot.y, EscData.rot.x, EscData.rot.z);

            m_OBB.m_Direct[0] = D3DXVECTOR3(matRot._11, matRot._12, matRot._13);
            m_OBB.m_Direct[1] = D3DXVECTOR3(matRot._21, matRot._22, matRot._23);
            m_OBB.m_Direct[2] = D3DXVECTOR3(matRot._31, matRot._32, matRot._33);

            SetDATA(EscData);//�i�[

            CObjectX::Update();



            HitCollision();



            CScene::MODE NowState = CScene::GetNowScene();
            if (NowState == CScene::MODE_GAME || NowState == CScene::MODE_GAME2 )
            {//�Q�[����

                D3DXCOLOR SetCol = D3DXCOLOR(m_col.r, m_col.g, m_col.b, 0.2f);

         //       CObject3DParticle::Create(EscData.Pos, SetCol);
                CObject* pObj = nullptr;
                pObj = CObject::GetObjectPoint(CObject::LAYERINDEX_3DPARTICLE_MNG, CObject::OBJECT_3DPARTICLE_MNG);

                if (pObj != nullptr)
                {
                    CObject3DParticleAll* pParticleMNG = static_cast<CObject3DParticleAll*>(pObj);
                    pParticleMNG->SetParticle(EscData.Pos, m_col,4,30.0f);
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
//�`��
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
// �����蔻��
//=============================
void CNewBullet::HitCollision()
{
    if (m_bUse == true)
    {
        //�擾
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
        {//��L����Ɉ���������Ȃ�

            //�����蔻��v�Z
            m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_NEWBULLET, EscData.Pos, EscData.OldPos, EscData.MinLength, EscData.MaxLength, OBJECT_HITBOX, LAYERINDEX_HITBOX, EscData.move, this);

            if (m_HitData.bHit == false)
            {
                //�����蔻��v�Z
                m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_NEWBULLET, EscData.Pos, EscData.OldPos, EscData.MinLength, EscData.MaxLength, OBJECT_OBSTACLE, LAYERINDEX_OBSTACLE, EscData.move, this);
            }

            if (m_HitData.bHit == false)
            {
                //�����蔻��v�Z
                m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_NEWBULLET, EscData.Pos, EscData.OldPos, EscData.MinLength, EscData.MaxLength, OBJECT_HITBOX_2D3D, LAYERINDEX_HITBOX_2D3D, EscData.move, this);
            }

            if (m_HitData.bHit == true)
            {
                CObjectShotFire::Create(EscData.Pos);
            }


            bool bHit = false;

            if (m_ShotType == CNewBulletALL::SHOTTYPE_PLAYER)
            {//�ˎ肪player


                // �z�u���v���C�I���e�B�̐擪���擾
                CObject* pObject = CObject::GetpTop(CObject::LAYERINDEX_MOTIONENEMY_NOMAL);

                if (pObject != nullptr)
                { // �擪���Ȃ�==�v���C�I���e�B�܂���ƂȂ�

                    int nIndex = 0;

                    while (pObject != nullptr)
                    {
                        CObjectMotionEnemyNomal* pEnemyNomal = static_cast<CObjectMotionEnemyNomal*>(pObject);

                        COBB pObb2 = pEnemyNomal->GetOBB();


                        D3DXVECTOR3 HitPos;
                        bHit = CMathProc::ColOBBs(m_OBB, pObb2, &HitPos);//�����蔻��

                        if (bHit == true)
                        {
                            pEnemyNomal->SetDamage(25);
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
                {//�ڐG����

                    // �z�u���v���C�I���e�B�̐擪���擾
                    CObject* pObject = CObject::GetpTop(CObject::LAYERINDEX_MOTIONENEMY_FAST);

                    if (pObject != nullptr)
                    { // �擪���Ȃ�==�v���C�I���e�B�܂���ƂȂ�

                        int nIndex = 0;

                        while (pObject != nullptr)
                        {
                            CObjectMotionEnemyfast* pEnemyFast = static_cast<CObjectMotionEnemyfast*>(pObject);

                            COBB pObb2 = pEnemyFast->GetOBB();


                            D3DXVECTOR3 HitPos;
                            bool btest = CMathProc::ColOBBs(m_OBB, pObb2, &HitPos);//�����蔻��

                            if (btest == true)
                            {
                                pEnemyFast->SetDamage(25);
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
                {//�ڐG����

                    // �z�u���v���C�I���e�B�̐擪���擾
                    CObject* pObject = CObject::GetpTop(CObject::LAYERINDEX_MOTIONENEMY_BOSS);

                    if (pObject != nullptr)
                    { // �擪���Ȃ�==�v���C�I���e�B�܂���ƂȂ�

                        int nIndex = 0;

                        while (pObject != nullptr)
                        {
                            CObjectMotionEnemyBoss* pEnemyBoss = static_cast<CObjectMotionEnemyBoss*>(pObject);

                            COBB pObb2 = pEnemyBoss->GetOBB();


                            D3DXVECTOR3 HitPos;
                            bool btest = CMathProc::ColOBBs(m_OBB, pObb2, &HitPos);//�����蔻��

                            if (btest == true)
                            {
                                pEnemyBoss->SetDamage(25);
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
                {//�ڐG����

                    // �z�u���v���C�I���e�B�̐擪���擾
                    CObject* pObject = CObject::GetpTop(CObject::LAYERINDEX_MOTIONENEMY_BOSS_GUARD);

                    if (pObject != nullptr)
                    { // �擪���Ȃ�==�v���C�I���e�B�܂���ƂȂ�

                        int nIndex = 0;

                        while (pObject != nullptr)
                        {
                            CObjectMotionEnemyGuard* pEnemyBoss = static_cast<CObjectMotionEnemyGuard*>(pObject);

                            COBB pObb2 = pEnemyBoss->GetOBB();


                            D3DXVECTOR3 HitPos;
                            bool btest = CMathProc::ColOBBs(m_OBB, pObb2, &HitPos);//�����蔻��

                            if (btest == true)
                            {
                                pEnemyBoss->SetDamage(25);
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
            {//�ˎ肪enemy
                   // �z�u���v���C�I���e�B�̐擪���擾
                CObject* pObject = CObject::GetpTop(CObject::LAYERINDEX_MOTIONPLAYER);

                if (pObject != nullptr)
                { // �擪���Ȃ�==�v���C�I���e�B�܂���ƂȂ�

                    int nIndex = 0;

                    while (pObject != nullptr)
                    {
                        CObjectMotionPlayer* pPlayer = static_cast<CObjectMotionPlayer*>(pObject);

                        COBB pObb2 = pPlayer->GetOBB();


                        D3DXVECTOR3 HitPos;
                        bool btest = CMathProc::ColOBBs(m_OBB, pObb2, &HitPos);//�����蔻��

                        if (btest == true)
                        {
                            pPlayer->SetDamage(5);
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
// ���ˉ񐔊i�[
//=============================
void CNewBullet::SetReflect(int nCnt)
{
    m_nReflect = nCnt;
}
//=============================
// �e���i�[
//=============================
void CNewBullet::SetCaller(void* pCaller)
{
    m_pCaller = pCaller;
}
//=============================
// �F�i�[
//=============================
void CNewBullet::SetCOL(D3DXCOLOR col)
{
    m_col = col;
}
//=============================
// ���܂��N���G�C�g
//=============================
CNewBullet* CNewBullet::Create()
{
    CNewBullet* pBlock3D = new CNewBullet;
    pBlock3D->Init();
    return pBlock3D;
}

//=============================
// bUse���ւ񂱂�
//=============================
void CNewBullet::SetbUse(bool bUse)
{
    m_bUse = bUse;
}
//=============================
// bUse���擾
//=============================
bool CNewBullet::GetbUse()
{
    return m_bUse;
}
//=============================
// �Z�b�g����
//=============================
void CNewBullet::SetBulletData(DATA SetData, int ReflectCnt, D3DXCOLOR col, void* pCaller, CNewBulletALL::SHOTTYPE ShotType)
{
    //�擾
    DATA EscData = GetDATA();



    m_ShotType = ShotType;


    EscData = SetData;//�ڂ�

    EscData.MinLength = D3DXVECTOR3(-30.0f, -30.0f, -30.0f);
    EscData.MaxLength = D3DXVECTOR3(30.0f, 30.0f, 30.0f);
    EscData.Radius = 30.0f;

    SetDATA(EscData);//�i�[
    m_Reflection= ReflectCnt;
    m_pCaller = pCaller;
    m_col = col;

    SetChangeColor(col);//���f��Color���ύX
    SetColorChangeBool(true);//�F�ύX��true��

    m_nLife = 500;
    
    m_OBB.m_fLength[0] = 15.0f;
    m_OBB.m_fLength[1] = 15.0f;
    m_OBB.m_fLength[2] = 30.0f;

    m_ShotByHitEscapeTime = 30;//3�t���[�������蔻��}��

    m_bGoodbyNow = false;
    m_bUse = true;

}
//===========================
//�����蔻�������Ԃ�Ԃ�
//===========================
int CNewBullet::GetHitEscapeTime()
{
    return m_ShotByHitEscapeTime;
}
//===========================
//OBB��Ԃ�
//===========================

COBB CNewBullet::GetOBB()
{
    return m_OBB;
}

//===========================
//�e�擾
//===========================
void* CNewBullet::GetCaller()
{
    return m_pCaller;
}


//===========================
//�o�O�̉���� 
//===========================
void CNewBullet::SetGoodby()
{ //�擾

    int Test = m_nID;

    DATA EscData = GetDATA();

    EscData.Pos = D3DXVECTOR3(-3000.0, -3000.0f, -3000.0f);
    EscData.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    EscData.Radius = 30.0f;
    EscData.MinLength = D3DXVECTOR3(-30.0f, -30.0f, -30.0f);
    EscData.MaxLength = D3DXVECTOR3(30.0f, 30.0f, 30.0f);

    SetDATA(EscData);//�i�[
    m_bUse = false;
    m_bGoodbyNow = true;

}
//===========================
//ID�擾
//===========================

int CNewBullet::GetID()
{
    return m_nID;
}
//===========================
//ID�Z�b�g
//===========================
void CNewBullet::SetID(int nID)
{
    m_nID = nID;
}

