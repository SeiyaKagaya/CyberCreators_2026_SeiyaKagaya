//=========================================================
//
// ModelParts[ModelParts.cpp]
// Author seiya kagaya
//
//=========================================================
#include "ModelParts.h"
#include "renderer.h"
#include "manager.h"
#include "object_motion.h"
#include "3DParticle.h"
#include "player_motion.h"

//=============================
// �R���X�g���N�^
//=============================
CModelParts::CModelParts(int nPriority) :CObjectX(nPriority), m_ChangeDatabool(false)
{
    m_ChangeDATA = {};

    m_CorrectCorrectionPosMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//���[�V�����ł̈ړ���pos
     m_CorrectCorrectionRotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//���[�V�����ł̈ړ���move
     m_calculationExecution=false;//�␳�l�v�Z������bool

     for (int nCnt = 0; nCnt < MAX_TEXTURE_XFILE; nCnt++)
     {
         if (m_pTexture[nCnt] != nullptr)
         {
             m_pTexture[nCnt] = nullptr;
         }
     }
}
//=============================
//�f�X�g���N�^
//=============================
CModelParts::~CModelParts()
{
}
//=============================
//������
//=============================
HRESULT CModelParts::Init()
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
    D3DXLoadMeshFromX(m_PartfilePass,
        D3DXMESH_SYSTEMMEM,
        EscDevice,
        NULL,
        &pBuffMat,
        NULL,
        &dwNumMat,
        &pMesh);

    //�}�e���A���f�[�^�ւ̃|�C���^���擾
    D3DXMATERIAL* pMat = (D3DXMATERIAL*)pBuffMat->GetBufferPointer();

    //�e�N�X�`���ǂݍ���
    LPDIRECT3DTEXTURE9	m_ESCpTexture = nullptr;


    ////�e�N�X�`���擾
    CAllTexture* pTexture = pManager->GetTexture();

    for (int nCntMat = 0; nCntMat < (int)dwNumMat; nCntMat++)
    {
        if (pMat[nCntMat].pTextureFilename != NULL)
        {
            int texIndex = pTexture->Regist(pMat[nCntMat].pTextureFilename, EscDevice);//�e�N�X�`���o�^

            m_ESCpTexture = pTexture->GetAddress(texIndex);

            BindTexture(m_ESCpTexture, nCntMat);//�ݒ�
        }
    }

    SetXfireData(pMesh, pBuffMat, dwNumMat);//�f�[�^�i�[

    //m_pMesh = pMesh;
    //m_pBuffMat = pBuffMat;
    //m_dwNumMat = dwNumMat;

    SetObjectType(CObject::OBJECT_MODELPARTS);

    return S_OK;
}
//=============================
//�j��
//=============================
void CModelParts::Uninit()
{
    delete m_PartfilePass;
    m_PartfilePass = nullptr;

    CObjectX::Uninit();
}
//=============================
//�X�V
//=============================
void CModelParts::Update()
{
    if (typeid(*pMotion) == typeid(CObjectMotionPlayer))
    {


        if (m_nPartNum == 9 || m_nPartNum == 10 || m_nPartNum == 17 || m_nPartNum == 18)
        {
            CRenderer* pRenderer = nullptr;

            CManager* pManager = CManager::GetInstance();

            pRenderer = pManager->GetRenderer();

            LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();


            if (m_ChangeDatabool == true)
            {//�f�[�^�ύX�A���̎�

                //����͐e�̃}�g���b�N�X���l�����Ă��Ȃ�
                m_NowData = m_ChangeDATA;

                m_NowData.Pos = m_offSetData.Pos;

                //�e�̃}�g���b�N�X
                D3DXMATRIX m_mtxWorldParent = m_pParentParts->GetMtxWorld();

                // �e�̌������l�����ĕ␳
                float parentAngle = atan2f(m_mtxWorldParent._31, m_mtxWorldParent._11);
                m_NowData.rot.y -= parentAngle;
            }
            //---------------------------------------------------------------------------------------------------------------------------------------


            DATA EscData = GetDATA();//�Ď擾

            D3DXMATRIX EscMtxWorld;

            D3DXMATRIX mtxRot, mtxTrans, mtxParent;//�v�Z�p�}�g���b�N�X

            //���[���h�}�g���b�N�X�̏�����
            D3DXMatrixIdentity(&m_mtxWorld);

            //�����𔽉f
            D3DXMatrixRotationYawPitchRoll(&mtxRot, m_NowData.rot.y, m_NowData.rot.x, m_NowData.rot.z);

            D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

            //�ʒu�𔽉f
            D3DXMatrixTranslation(&mtxTrans, m_NowData.Pos.x, m_NowData.Pos.y, m_NowData.Pos.z);

            D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

            //�e�q�֌W
            if (m_pParentParts == nullptr)
            {
                //�����̎�̃}�g���b�N�X�Ƃ�����(player/enemy)�Ȃ�

                //
                EscDevice->GetTransform(D3DTS_WORLD, &EscMtxWorld);//�Ƃ肠�����ŐV�̃}�g���b�N�X�擾


                D3DXMATRIX EscMat = pMotion->GetMatrix();

                //�n�c�Ƃ�����
                D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &EscMat);
            }
            else
            {
                D3DXMATRIX m_mtxWorldParent = m_pParentParts->GetMtxWorld();

                //�����̐e�̃}�g���b�N�X�����Ă�
                D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxWorldParent);
            }

            D3DXVECTOR3 BOOSTPos[4] = {};
            D3DXMATRIX m_Boost_mtxWorld[4] = {};

            float BoostMag = 1.0f;

            if (((CObjectMotionPlayer*)pMotion)->GetBoostNow() == true)
            {//
                //�u�[�X�g��
                BoostMag = (float)CObjectMotionPlayer::BOOST_MAG;
                BoostMag /= 10.0f;
            }

       

            switch (m_nPartNum)
            {
            case 9://����
                //��
                BOOSTPos[0] = D3DXVECTOR3(30.0f, 0.0f, 19.0f);	//�ʒu
                BOOSTPos[1] = D3DXVECTOR3(5.0f, -10.0f * BoostMag, 2.0f);	//�ʒu


                BOOSTPos[2] = D3DXVECTOR3(5.0f, -10.0f * BoostMag, 2.0f);	//�ʒu
                BOOSTPos[3] = D3DXVECTOR3(5.0f, -10.0f * BoostMag, 2.0f);	//�ʒu

                break;

            case 10://����
                BOOSTPos[0] = D3DXVECTOR3(-30.0f, 0.0f, 19.0f);	//�ʒu
                BOOSTPos[1] = D3DXVECTOR3(-5.0f, -10.0f * BoostMag, 2.0f);	//�ʒu


                BOOSTPos[2] = D3DXVECTOR3(-5.0f, -10.0f * BoostMag, 2.0f);	//�ʒu
                BOOSTPos[3] = D3DXVECTOR3(-5.0f, -10.0f * BoostMag, 2.0f);	//�ʒu
                break;

            case 17://����
                BOOSTPos[0] = D3DXVECTOR3(10.0f, 0.0f, 19.0f);	//�ʒu
                BOOSTPos[1] = D3DXVECTOR3(5.0f, -10.0f * BoostMag, 2.0f);	//�ʒu


                BOOSTPos[2] = D3DXVECTOR3(5.0f, -10.0f * BoostMag, 2.0f);	//�ʒu
                BOOSTPos[3] = D3DXVECTOR3(5.0f, -10.0f * BoostMag, 2.0f);	//�ʒu
                break;

            case 18://����
                BOOSTPos[0] = D3DXVECTOR3(-10.0f, 0.0f, 19.0f);	//�ʒu
                BOOSTPos[1] = D3DXVECTOR3(-5.0f, -10.0f * BoostMag, 2.0f);	//�ʒu


                BOOSTPos[2] = D3DXVECTOR3(-5.0f, -10.0f * BoostMag, 2.0f);	//�ʒu
                BOOSTPos[3] = D3DXVECTOR3(-5.0f, -10.0f * BoostMag, 2.0f);	//�ʒu
                break;
            }


            for (int i = 0; i < 4; i++)
            {
                if (i == 0)
                {
                    //���[���h�}�g���b�N�X�̏�����
                    D3DXMatrixIdentity(&m_Boost_mtxWorld[i]);

                    //�ʒu�𔽉f
                    D3DXMatrixTranslation(&mtxTrans, BOOSTPos[i].x, BOOSTPos[i].y, BOOSTPos[i].z);

                    D3DXMatrixMultiply(&m_Boost_mtxWorld[i], &m_Boost_mtxWorld[i], &mtxTrans);

                    //�n�c�Ƃ�����
                    D3DXMatrixMultiply(&m_Boost_mtxWorld[i], &m_Boost_mtxWorld[i], &m_mtxWorld);
                }
                else
                {
                    //���[���h�}�g���b�N�X�̏�����
                    D3DXMatrixIdentity(&m_Boost_mtxWorld[i]);

                    //�ʒu�𔽉f
                    D3DXMatrixTranslation(&mtxTrans, BOOSTPos[i].x, BOOSTPos[i].y, BOOSTPos[i].z);

                    D3DXMatrixMultiply(&m_Boost_mtxWorld[i], &m_Boost_mtxWorld[i], &mtxTrans);

                    //�n�c�Ƃ�����
                    D3DXMatrixMultiply(&m_Boost_mtxWorld[i], &m_Boost_mtxWorld[i], &m_Boost_mtxWorld[i - 1]);
                }

                D3DXVECTOR3 SETPOS = D3DXVECTOR3(m_Boost_mtxWorld[i]._41, m_Boost_mtxWorld[i]._42, m_Boost_mtxWorld[i]._43);

                D3DXCOLOR setcol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

                switch (i)
                {
                case 0://���{
                    setcol = D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.1f * BoostMag);
                    break;

                case 1:
                    setcol = D3DXCOLOR(0.25f, 0.0f, 0.75f, 0.1f * BoostMag);
                    break;

                case 2:
                    setcol = D3DXCOLOR(0.5f, 0.0f, 0.5f, 0.1f * BoostMag);
                    break;

                case 3://��[
                    setcol = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.1f * BoostMag);
                    break;
                }

  //              CObject3DParticle::Create(SETPOS, setcol);
            }


        }
    }
}
//=============================
//�`��
//=============================
void CModelParts::Draw()
{
    CRenderer* pRenderer = nullptr;

    CManager* pManager = CManager::GetInstance();

    pRenderer = pManager->GetRenderer();

    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();


    if (m_ChangeDatabool==true)
    {//�f�[�^�ύX�A���̎�

        //����͐e�̃}�g���b�N�X���l�����Ă��Ȃ�
        m_NowData = m_ChangeDATA;

        m_NowData.Pos = m_offSetData.Pos;

        //�e�̃}�g���b�N�X
        D3DXMATRIX m_mtxWorldParent = m_pParentParts->GetMtxWorld();

        // �e�̌������l�����ĕ␳
        float parentAngle = atan2f(m_mtxWorldParent._31, m_mtxWorldParent._11);
        m_NowData.rot.y -= parentAngle;
    }
    //---------------------------------------------------------------------------------------------------------------------------------------


    DATA EscData = GetDATA();//�Ď擾

    D3DXMATRIX EscMtxWorld;

    D3DXMATRIX mtxRot, mtxTrans, mtxParent;//�v�Z�p�}�g���b�N�X

    //���[���h�}�g���b�N�X�̏�����
    D3DXMatrixIdentity(&m_mtxWorld);

    //�����𔽉f
    D3DXMatrixRotationYawPitchRoll(&mtxRot, m_NowData.rot.y, m_NowData.rot.x, m_NowData.rot.z);

    D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

    //�ʒu�𔽉f
    D3DXMatrixTranslation(&mtxTrans, m_NowData.Pos.x, m_NowData.Pos.y, m_NowData.Pos.z);

    D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

    //�e�q�֌W
    if (m_pParentParts == nullptr)
    {
        //�����̎�̃}�g���b�N�X�Ƃ�����(player/enemy)�Ȃ�

        //
        EscDevice->GetTransform(D3DTS_WORLD, &EscMtxWorld);//�Ƃ肠�����ŐV�̃}�g���b�N�X�擾


        D3DXMATRIX EscMat = pMotion->GetMatrix();

        //�n�c�Ƃ�����
        D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &EscMat);
    }
    else
    {
        D3DXMATRIX m_mtxWorldParent = m_pParentParts->GetMtxWorld();

        //�����̐e�̃}�g���b�N�X�����Ă�
        D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxWorldParent);
    }

    ChangeModelPartsbool(true);//�p�[�c�`�悶�}�g���b�N�X�ύX
    SetModelMtxWorld(m_mtxWorld);//�}�g���b�N�X�i�[


    EscData.Pos = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);//�}�g���b�N�X������o��


    // ��]�s��𒊏o���Afloat�ɃL���X�g
    EscData.rot.x = static_cast<float>(atan2(m_mtxWorld._32, m_mtxWorld._33));
    EscData.rot.y = static_cast<float>(atan2(-m_mtxWorld._31, static_cast<double>(sqrt(static_cast<double>(m_mtxWorld._32) * static_cast<double>(m_mtxWorld._32) + static_cast<double>(m_mtxWorld._33) * static_cast<double>(m_mtxWorld._33)))));
    EscData.rot.z = static_cast<float>(atan2(m_mtxWorld._21, m_mtxWorld._11));

    SetDATA(EscData);//�i�[(�`�掞�ɂ��̌v�Z���posRot���g�p����悤�ɂȂ�)




    if (m_bDrawBool == true)
    {




        if (m_bChengeCol==true)
        {
            CObjectX::SetColorChangeBool(true);
            CObjectX::SetChangeColor(m_ChengeCol);
        }


        CObjectX::Draw();
    }



    //D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p(�ꎞ�ޔ�)

    //D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

    //D3DXMATRIX ESCMatrix = m_mtxWorld;

    ////---------------------------------------------------------------------------------------------------���f���̈ʒu
    //DATA ESCNOWDATA = EscData;


    ////���[���h�}�g���b�N�X�̐ݒ�
    //EscDevice->SetTransform(D3DTS_WORLD, &ESCMatrix);

    ////���݂̃}�e���A�����擾
    //EscDevice->GetMaterial(&matDef);

    ////�}�e���A���f�[�^�ւ̃|�C���^���擾
    //pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

    //for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
    //{

    //    bool g_test = false;

    //    //------------------------�J���[�`�F���W
    //    if (g_test == true)
    //    {
    //        // �}�e���A���̐ݒ�
    //        D3DMATERIAL9 matTemp = pMat[nCntMat].MatD3D;
    //        matTemp.Diffuse = D3DXCOLOR(1.0f, 0.1f, 0.1f, 0.8f);
    //        //matTemp.Diffuse.a = 0.5f;  // ���ߓx��ݒ�i0.0f�Ŋ��S�����A1.0f�ŕs�����j
    //        EscDevice->SetMaterial(&matTemp);
    //    }
    //    else
    //    {
    //        //�}�e���A���̐ݒ�
    //        EscDevice->SetMaterial(&pMat[nCntMat].MatD3D);
    //    }

    //    //�e�N�X�`���̐ݒ�
    //    //EscDevice->SetTexture(0, NULL);//����͐ݒ肵�Ȃ�
    //    //�e�N�X�`���̐ݒ�

    //    EscDevice->SetTexture(0, m_pTexture[nCntMat]);
    //    //���f��(�p�[�c)�̕`��
    //    m_pMesh->DrawSubset(nCntMat);

    //}

    ////�ۑ����Ă��}�e���A����߂�
    //EscDevice->SetMaterial(&matDef);

    ////�e�N�X�`����߂�
    //EscDevice->SetTexture(0, NULL);


}
//=============================
//����
//=============================
CModelParts* CModelParts::Create(const char* FilePass, int PartsNum)
{
    CModelParts* pModelParts = new CModelParts;

    pModelParts->SetFilePass(FilePass);
    pModelParts->Init();
    pModelParts->SetPartsNum(PartsNum);
    return pModelParts;
}
//=============================
// �p�X�i�[//init�O�ɂ��
//=============================
void CModelParts::SetFilePass(const char* FilePass)
{
    char* filePass = new char[strlen(FilePass) + 1];//�������m��
    strcpy(filePass, FilePass);//�R�s�[

    m_PartfilePass = filePass;
}
//=============================
// �e���i�[
//=============================
void CModelParts::SetParent(CModelParts* pParentParts)
{
    m_pParentParts = pParentParts;
}
//=============================
// Offset�i�[
//=============================
void CModelParts::SetOffSetData(DATA offSetData)
{
    m_offSetData = offSetData;
}
//=============================
// Offset�擾
//=============================
CModelParts::DATA CModelParts::GetOffSetData()
{
    return m_offSetData;
}
//=============================
// �}�g���b�N�X�擾
//=============================
D3DXMATRIX CModelParts::GetMtxWorld()
{
    return m_mtxWorld;
}
//=============================
// �e���擾
//=============================
CModelParts* CModelParts::GetParent()
{
    return m_pParentParts;
}
//=============================
// �ʏ�f�[�^�i�[
//=============================
void CModelParts::SetNowData(DATA data)
{
    m_NowData=data;
}
//=============================
// �ʏ�f�[�^���擾
//=============================
CModelParts::DATA CModelParts::GetNowData()
{
    return m_NowData;
}
//=============================
// �␳�l�擾POS
//=============================
D3DXVECTOR3 CModelParts::GetCorrectCorrectionPosMove()
{
    return m_CorrectCorrectionPosMove;
}
//=============================
// �␳�l�擾ROT
//=============================
D3DXVECTOR3 CModelParts::GetCorrectCorrectionRotMove()
{
    return m_CorrectCorrectionRotMove;
}
//=============================
// �␳�l�v�Z�ς݂��擾
//=============================
bool CModelParts::GetcalculationExecution()
{
    return m_calculationExecution;
}
//=============================
// �␳�l�i�[POS
//=============================
void CModelParts::SetCorrectCorrectionPosMove(D3DXVECTOR3 pos)
{
    m_CorrectCorrectionPosMove = pos;
}
//=============================
// �␳�l�i�[ROT
//=============================
void CModelParts::SetCorrectCorrectionRotMove(D3DXVECTOR3 Rot)
{
    m_CorrectCorrectionRotMove = Rot;
}
//=============================
// �␳�l�v�Z�ς݂����i�[
//=============================
void CModelParts::SetcalculationExecution(bool calculationExecution)
{
    m_calculationExecution = calculationExecution;
}
//=============================
// motionPos
//=============================
void CModelParts::UpdatePosMotion()
{
    //�e�̂Ƃ��������삵�Ȃ�
    m_NowData.Pos += m_CorrectCorrectionPosMove;
}
//=============================
//MotionRot
//=============================
void CModelParts::UpdateRotMotion()
{
    m_NowData.rot += m_CorrectCorrectionRotMove;
}

void CModelParts::SetMotionPoint(CObjectMotion* Motion)
{
    pMotion = Motion;//���ׂĂ̐e�̃|�C���^

}

D3DXMATRIX CModelParts::GetPartsMtx()
{
    return m_mtxWorld;
}

void CModelParts::SetPartsMtx(D3DXMATRIX mtxWorld)
{
    m_mtxWorld = mtxWorld;
}


//�f�[�^�ύX���f��bool
void CModelParts::m_DataChangeModel(bool changebool)
{
    m_ChangeDatabool = changebool; 
}

//�ύX�f�[�^�i�[
void CModelParts::ChangeDataSet(DATA data)
{
    m_ChangeDATA = data; 
}

void CModelParts::SetMotion_Parent(int Check)
{
    m_MotionParent = Check;
}

int CModelParts::GetMotion_Parent()
{
    return m_MotionParent;
}

void CModelParts::DrawOkBool(bool Draw)
{
    m_bDrawBool = Draw;
}

void CModelParts::ChengeRGBAbool(bool chenge, D3DXCOLOR col)
{
    m_bChengeCol = chenge;
    m_ChengeCol = col;
}
