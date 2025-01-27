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

// �ÓI�����o�ϐ��̒�`
//CMissile* CMissileALL::m_Missile[CMissileALL::MAXMISSILEALL] = { nullptr };


//=============================
// �R���X�g���N�^
//=============================
CMissileALL::CMissileALL(int nPriority) : CObjectX(nPriority)
{

}
//=============================
// �f�X�g���N�^
//=============================
CMissileALL::~CMissileALL()
{
}
//=============================
// ������
//=============================
HRESULT CMissileALL::Init()
{
    //������
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
// �I��
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
// ����
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
// �擾
//=============================
CMissile* CMissileALL::GetBulletData(int nNum)
{
    return m_Missile[nNum];
}
//=============================
// �ÓI�Ƀo���b�g���Z�b�g
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
// �ǔ��Ώێ��S������
//=============================
void CMissileALL::KillMissileTarget(void* pCaller)
{
    for (int i = 0; i < MAXMISSILEALL; i++)
    {
        if (m_Missile[i]->GetCaller() == pCaller)
        {//���񂾒ǔ��Ώۂ�����̂Ƃ�
            m_Missile[i]->SetCaller(nullptr);
            m_Missile[i]->SetbUse(false);
        }
    }
}





















































//------------------------------------------------------------------------------------------------------------------------------------------------------
//=============================
// �R���X�g���N�^
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
    m_ShotByHitEscapeTime = 30;//3�t���[�������蔻��}��
    m_pCaller = nullptr;
}
//=============================
//�f�X�g���N�^
//=============================
CMissile::~CMissile()
{
    //   m_nNumBulletAll--;
}
//=============================
//������
//=============================
HRESULT CMissile::Init()
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
    D3DXLoadMeshFromX("DATA\\MODEL\\Missile.x",
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

    SetObjectType(CObject::OBJECT_MISSILE);


    //�擾
    DATA EscData = GetDATA();

    EscData = GetDATA();//�Ď擾

    //��

    EscData.MinLength = D3DXVECTOR3(-6.0f, -6.0f, -6.0f);
    EscData.MaxLength = D3DXVECTOR3(6.0f, 6.0f, 6.0f);
    EscData.Radius = 30.0f;


    SetDATA(EscData);//�i�[


    SetSizeMag(D3DXVECTOR3(0.5f, 0.5f, 0.5f));//�傫���{��




    return S_OK;
}
//=============================
//�j��
//=============================
void CMissile::Uninit()
{
    CObjectX::Uninit();
}
//=============================
//�X�V
//=============================
void CMissile::Update()
{
    if (m_bUse == true)
    {
        if (m_bGoodbyNow == false)
        {
            DATA EscData = GetDATA();//�Ď擾

            CRenderer* pRenderer = nullptr;

            CManager* pManager = CManager::GetInstance();


            if (m_DelayCnt > 0)
            {
                m_DelayCnt--;

                EscData.move.x = 0.0f;
                EscData.move.y = 9.0f;
                EscData.move.z = 0.0f;

                // �ʒu���X�V
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

            EscData = GetDATA();//�Ď擾

        //OBB�܂��
            m_OBB.m_Pos = EscData.Pos;




            D3DXMATRIX matRot;

            //�����x�N�g���擾
            D3DXMatrixRotationYawPitchRoll(&matRot, EscData.rot.y, EscData.rot.x, EscData.rot.z);

            m_OBB.m_Direct[0] = D3DXVECTOR3(matRot._11, matRot._12, matRot._13);
            m_OBB.m_Direct[1] = D3DXVECTOR3(matRot._21, matRot._22, matRot._23);
            m_OBB.m_Direct[2] = D3DXVECTOR3(matRot._31, matRot._32, matRot._33);


            HitCollision();

            
          //  EscData.move;//�̈ړ�������rot��X��+������������
            
          //  EscData.rot;

            //--------------------------------------------------------------------------------------------------------------------------------------------------

            DATA ChangeData = DataInit();
       //     DATA classData = GetClassData();


            // �ڕW�������v�Z
            D3DXVECTOR3 enemyDirection = EscData.move;

            // XZ���ʏ�̖ڕW�p�x���v�Z
            float targetAngleXZ = atan2f(enemyDirection.z, -enemyDirection.x) + (D3DX_PI * 0.5f);

            // ���݂̖C����XZ���ʏ�̊p�x
          //  float currentAngleXZ = fRotTurret;


            // �p�x��͈͓��Ɏ��߂�
            targetAngleXZ = fmodf(targetAngleXZ + D3DX_PI, 2 * D3DX_PI) - D3DX_PI;

            // �p�x�̍���
          //  float rotDiff = targetAngleXZ - currentAngleXZ;

            //// �������͈͊O�Ȃ�␳---------------------------------------------------------------�߂����������Ɠ��e���ׂ�
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


            float minYAngle = -1.1f; // �����̊p�x�̌��E
            float maxYAngle = 1.1f;  // �㑤�̊p�x�̌��E


            D3DXVECTOR3 SETVEC = EscData.Pos + EscData.move;


            //����
            enemyDirection = D3DXVECTOR3(SETVEC.x, SETVEC.y, SETVEC.z) - D3DXVECTOR3(GetDATA().Pos.x, GetDATA().Pos.y, GetDATA().Pos.z);

            // XZ���ʏ�̊p�x
            float angleXZ = atan2f(enemyDirection.z, enemyDirection.x);

          //  ChangeData.rot.x = 0.0f; // �悶���h�����߂ɕK�v�Ȓ���
            EscData.rot.y = -(angleXZ + 1.57f); // ����������
          //  ChangeData.rot.z = 0.0f;

            //		 Y���̊p�x
            float angleY = (atan2f(enemyDirection.y, sqrtf(enemyDirection.x * enemyDirection.x + enemyDirection.z * enemyDirection.z)));

            //// Y���p�x���N�����v
            //if (angleY < minYAngle)
            //{
            //    angleY = minYAngle;
            //}
            //else if (angleY > maxYAngle)
            //{
            //    angleY = maxYAngle;
            //}

            EscData.rot.x = angleY; // Y������������


                // �ύX�f�[�^�𔽉f
            //SetChangeDataInObjectMotion(ChangeData);
            //--------------------------------------------------------------------------------------------------------------------------------------------------






















            SetDATA(EscData);//�i�[

            CObjectX::Update();


            CScene::MODE NowState = CScene::GetNowScene();
            if (NowState == CScene::MODE_GAME || NowState == CScene::MODE_GAME2 || NowState == CScene::MODE_GAME3)
            {//�Q�[����

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
//�`��
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
// �����蔻��
//=============================
void CMissile::HitCollision()
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
            m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_MISSILE, EscData.Pos, EscData.OldPos, EscData.MinLength, EscData.MaxLength, OBJECT_HITBOX, LAYERINDEX_HITBOX, EscData.move, this);

            if (m_HitData.bHit == false)
            {
                //�����蔻��v�Z
                m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_MISSILE, EscData.Pos, EscData.OldPos, EscData.MinLength, EscData.MaxLength, OBJECT_OBSTACLE, LAYERINDEX_OBSTACLE, EscData.move, this);
            }

            if (m_HitData.bHit == false)
            {
                //�����蔻��v�Z
                m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_MISSILE, EscData.Pos, EscData.OldPos, EscData.MinLength, EscData.MaxLength, OBJECT_HITBOX_2D3D, LAYERINDEX_HITBOX_2D3D, EscData.move, this);
            }

            if (m_HitData.bHit == true)
            {
                CObjectShotFire::Create(EscData.Pos);
                m_bUse = false;
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
                            bHit = CMathProc::ColOBBs(m_OBB, pObb2, &HitPos);//�����蔻��

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
                            bHit = CMathProc::ColOBBs(m_OBB, pObb2, &HitPos);//�����蔻��

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
                            bHit = CMathProc::ColOBBs(m_OBB, pObb2, &HitPos);//�����蔻��

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
                        bHit = CMathProc::ColOBBs(m_OBB, pObb2, &HitPos);//�����蔻��

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
// ���ˉ񐔊i�[
//=============================
void CMissile::SetReflect(int nCnt)
{
    m_nReflect = nCnt;
}
//=============================
// �e���i�[
//=============================
void CMissile::SetCaller(void* pCaller)
{
    m_pCaller = pCaller;
}
//=============================
// �F�i�[
//=============================
void CMissile::SetCOL(D3DXCOLOR col)
{
    m_col = col;
}
//=============================
// ���܂��N���G�C�g
//=============================
CMissile* CMissile::Create()
{
    CMissile* pBlock3D = new CMissile;
    pBlock3D->Init();
    return pBlock3D;
}

//=============================
// bUse���ւ񂱂�
//=============================
void CMissile::SetbUse(bool bUse)
{
    m_bUse = bUse;
}
//=============================
// bUse���擾
//=============================
bool CMissile::GetbUse()
{
    return m_bUse;
}
//=============================
// �Z�b�g����
//=============================
void CMissile::SetBulletData(DATA SetData, int ReflectCnt, D3DXCOLOR col, void* pCaller, CMissileALL::SHOTTYPE ShotType)
{
    //�擾
    DATA EscData = GetDATA();

    m_ShotType = ShotType;



    EscData = SetData;//�ڂ�

    EscData.MinLength = D3DXVECTOR3(-30.0f, -30.0f, -30.0f);
    EscData.MaxLength = D3DXVECTOR3(30.0f, 30.0f, 30.0f);
    EscData.Radius = 30.0f;

    SetDATA(EscData);//�i�[
    m_Reflection = ReflectCnt;
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
    m_DelayCnt = 30;
}
//===========================
//�����蔻�������Ԃ�Ԃ�
//===========================
int CMissile::GetHitEscapeTime()
{
    return m_ShotByHitEscapeTime;
}
//===========================
//OBB��Ԃ�
//===========================

COBB CMissile::GetOBB()
{
    return m_OBB;
}

//===========================
//�e�擾
//===========================
void* CMissile::GetCaller()
{
    return m_pCaller;
}


//===========================
//�o�O�̉���� 
//===========================
void CMissile::SetGoodby()
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

int CMissile::GetID()
{
    return m_nID;
}
//===========================
//ID�Z�b�g
//===========================
void CMissile::SetID(int nID)
{
    m_nID = nID;
}
//===========================
//�U������
//===========================
void CMissile::Homing()
{


    if (m_ShotType == CMissileALL::SHOTTYPE_PLAYER)
    {//�v���C���[�e
        
                CObjectMotion* pObj = static_cast<CObjectMotion*>(m_pCaller);

                DATA ESCDATA = pObj->GetClassData();

           
                D3DXVECTOR3 targetDirection = D3DXVECTOR3(pObj->GetClassData().Pos.x, pObj->GetClassData().Pos.y + 50.0f, pObj->GetClassData().Pos.z) - GetDATA().Pos;
                D3DXVec3Normalize(&targetDirection, &targetDirection);

                D3DXVECTOR3 SetMove = GetDATA().move;

                // �~�T�C���̈ړ�������ύX
                ChangeVectorDirection(SetMove, targetDirection, D3DX_PI / 180.0f * MISSILEROT); // �K�؂Ȓl�ɕύX���Ă�������

                // �~�T�C���̑����𒲐����邽�߂̔{��
               // float missileSpeedMultiplier = MISSILEMOVESPEED; // �K�؂Ȓl�ɕύX���Ă�������

                DATA SetData = GetDATA();

                SetData.move = SetMove;

                // �ʒu���X�V
                SetData.OldPos = SetData.Pos;
                SetData.Pos += SetData.move * MISSILEMOVESPEED * 1.2f;
             
               SetDATA(SetData);
    }
    else  if (m_ShotType == CMissileALL::SHOTTYPE_ENEMY)
    {//�G�e

            //player�̈ʒu���擾
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

         // �ڕW�ւ̕����x�N�g��
        D3DXVECTOR3 targetDirection = EscData.Pos - GetDATA().Pos;

        D3DXVec3Normalize(&targetDirection, &targetDirection);//���K��

        D3DXVECTOR3 SetMove = GetDATA().move;

        // �~�T�C���̈ړ�������ύX
        ChangeVectorDirection(SetMove, targetDirection, D3DX_PI / 180.0f * MISSILEROT * 0.15f); // �K�؂Ȓl�ɕύX���Ă�������

        // �~�T�C���̑����𒲐����邽�߂̔{��
       // float missileSpeedMultiplier = MISSILEMOVESPEED; // �K�؂Ȓl�ɕύX���Ă�������

        DATA SetData = GetDATA();

        SetData.move = SetMove;

         // �ʒu���X�V
        SetData.OldPos = SetData.Pos;
        SetData.Pos += SetData.move * MISSILEMOVESPEED * 0.3f;
    

        SetDATA(SetData);
    }
}
//===========================
// �x�N�g���̑傫����ۂ��p�x��ύX����֐�
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
        // �p�x�ύX���������z����ꍇ�́A�p�x�𐧌����Ɏ��߂�����ύX
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
        // �������̏ꍇ�́A���ڕ�����ύX
        vector = targetDirection;
    }
}


