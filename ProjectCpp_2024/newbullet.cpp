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

// �ÓI�����o�ϐ��̒�`
CNewBullet* CNewBulletALL::m_NewBullet[CNewBulletALL::MAXBULLETALL] = { nullptr };


//=============================
// �R���X�g���N�^
//=============================
CNewBulletALL::CNewBulletALL()
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
        CNewBullet* pBlock3D = new CNewBullet;
        pBlock3D->Init();

        pBlock3D->SetID(i);

        m_NewBullet[i] = pBlock3D;

    }




    return E_NOTIMPL;
}
//=============================
// �I��
//=============================
void CNewBulletALL::Uninit()
{
  //  for (int i = 0; i < MAXBULLETALL; i++)
  //  {
  ////      delete m_NewBullet[i];
  //  }

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
// �R���X�g���N�^
//=============================
CNewBullet::CNewBullet(int nPriority) :CObjectX(nPriority)
{
  //  m_nNumBulletAll++;

    m_nLife = 200;

    m_bUse = false;

    m_OBB.m_fLength[0] = 15.0f;
    m_OBB.m_fLength[1] = 15.0f;
    m_OBB.m_fLength[2] = 30.0f;
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
    D3DXLoadMeshFromX("DATA\\MODEL\\Bullet.x",
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
    
    EscData.MinLength = D3DXVECTOR3(-30.0f, -30.0f, -30.0f);
    EscData.MaxLength = D3DXVECTOR3(30.0f, 30.0f, 30.0f);
    EscData.Radius = 30.0f;


    SetDATA(EscData);//�i�[


    SetSizeMag(D3DXVECTOR3(5.5f, 5.5f, 5.5f));//�傫���{��

    m_bUse = false;




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
                {//�Q�[����
                 //   CObjectExplosionBill::Create(EscData.Pos);
                }
                //	Uninit();

 //               SetDeath(true);
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

            SetDATA(EscData);//�i�[

            CObjectX::Update();


            CScene::MODE NowState = CScene::GetNowScene();
            if (NowState == CScene::MODE_GAME || NowState == CScene::MODE_GAME2 )
            {//�Q�[����

        //        CObject3DParticle::Create(EscData.Pos, m_col);

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
        {//��L����Ɉ���������Ȃ�


            //�����蔻��v�Z
            m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_NEWBULLET, EscData.Pos, EscData.OldPos, EscData.MinLength, EscData.MaxLength, OBJECT_HITBOX, LAYERINDEX_HITBOX, EscData.move, this);

            if (m_HitData.bHit == false)
            {
                //�����蔻��v�Z
                m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_NEWBULLET, EscData.Pos, EscData.OldPos, EscData.MinLength, EscData.MaxLength, OBJECT_OBSTACLE, LAYERINDEX_OBSTACLE, EscData.move, this);
            }

            if (m_HitData.bHit == true)
            {//�ڐG
                CScene::MODE NowState = CScene::GetNowScene();
                if (NowState == CScene::MODE_GAME || NowState == CScene::MODE_GAME2)
                {//�Q�[����

              //      CObjectReflectEffect::Create(EscData.Pos);
                }
                EscData.move = m_HitData.ReflectionVector;


                //// �i�s�����̌v�Z
                //float Angle = atan2f(EscData.move.x, EscData.move.y) + D3DX_PI;

                ////classData.rot �̍X�V
                //EscData.rot.z = Angle;
             //   float angle = atan2f(EscData.move.y, EscData.move.x); // Y��������
              //  EscData.rot.z = angle; // Z���̉�]���X�V

                m_Reflection--;
            }
        }

        SetDATA(EscData);//�i�[

        m_HitData.bHit = false;
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
void CNewBullet::SetBulletData(DATA SetData, int ReflectCnt, D3DXCOLOR col, void* pCaller)
{
    //�擾
    DATA EscData = GetDATA();






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

    m_nLife = 200;

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
