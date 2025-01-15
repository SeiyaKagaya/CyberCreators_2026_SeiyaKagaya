//=========================================================
//
// CBulletLine[CBulletLine.cpp]
// Author seiya kagaya
//
//=========================================================
#include"CBulletLine.h"
#include "enemy_motion_Nomal.h"
#include "enemy_motion_fast.h"
#include "enemy_motion_boss.h"
#include "enemy_motion_guard.h"



//=============================
// �R���X�g���N�^
//=============================
CBulletLine::CBulletLine(int nPriority) :CObjectX(nPriority)
{

}

//=============================
// �f�X�g���N�^
//=============================
CBulletLine::~CBulletLine()
{
}

//=============================
// ������
//=============================
HRESULT CBulletLine::Init()
{
    CObjectX::Init();

    CRenderer* pRenderer = nullptr;
    CManager* pManager = CManager::GetInstance();
    pRenderer = pManager->GetRenderer();


    m_pMesh = nullptr; // Mesh�|�C���^
    m_pBuffMat = nullptr; // �}�e���A���ւ̃|�C���^
    m_dwNumMat = 0; // �}�e���A���̐�
    m_ESCpTexture = nullptr;
    m_bFast = false;
    m_OriginalColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();


    // �t�@�C���̓ǂݍ���
    D3DXLoadMeshFromX("DATA\\MODEL\\BulletLine.x",
        D3DXMESH_SYSTEMMEM,
        EscDevice,
        NULL,
        &m_pBuffMat,
        NULL,
        &m_dwNumMat,
        &m_pMesh);




    D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

    //�e�N�X�`���擾
    CAllTexture* pTexture = pManager->GetTexture();

    for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
    {
        if (pMat[nCntMat].pTextureFilename != NULL)
        {

            int texIndex = pTexture->Regist(pMat[nCntMat].pTextureFilename, EscDevice);//�e�N�X�`���o�^

            m_ESCpTexture = pTexture->GetAddress(texIndex);

            BindTexture(m_ESCpTexture, nCntMat);//�ݒ�
        }
    }


    //       SetXfireData(m_pMesh[0], m_pBuffMat[0], m_dwNumMat[0]); // �f�[�^�i�[







    SetObjectType(CObject::OBJECT_BULLETLINE);

    m_OBB.m_fLength[0] = 80.0f;
    m_OBB.m_fLength[1] = 160.0f;
    m_OBB.m_fLength[2] = 660.0f;

    return S_OK;
}

//=============================
// �j��
//=============================
void CBulletLine::Uninit()
{

        if (m_pMesh != nullptr)
        {
            m_pMesh->Release(); // ���b�V�����
            m_pMesh = nullptr;
        }

        if (m_pBuffMat != nullptr)
        {
            m_pBuffMat->Release(); // �}�e���A���o�b�t�@���
            m_pBuffMat = nullptr;
        }

        // �e�N�X�`���̉����CAllTexture�N���X�̊Ǘ����@�ɏ]���K�v������
        if (m_ESCpTexture != nullptr)
        {
            // ������delete�ł͂Ȃ��ACAllTexture�̊Ǘ��N���X�ŉ������悤�Ɏ���
            // CManager::GetInstance()->GetTexture()->ReleaseTexture(m_ESCpTexture);
            m_ESCpTexture = nullptr;
        }
    


    //  CObjectX::Uninit();
}

//=============================
// �X�V
//=============================
void CBulletLine::Update()
{
    CRenderer* pRenderer = nullptr;

    CManager* pManager = CManager::GetInstance();


    if (pManager->GetbNow3DMode() == false)
    {//2D
      // OBB�܂��
        m_OBB.m_Pos = GetDATA().Pos;

        D3DXMATRIX matRot, EscMtx, mtxTrans;

        // ���[���h�}�g���b�N�X�̏�����
        D3DXMatrixIdentity(&EscMtx);

        // �����x�N�g���擾�i��]�s��̐����j
        D3DXMatrixRotationYawPitchRoll(&matRot, GetDATA().rot.y, GetDATA().rot.x, GetDATA().rot.z);

        // �I�t�Z�b�g��` (���[�J�����)
        D3DXVECTOR3 localOffset(0.0f, -150.0f, -550.0f); // x������+500

        // �I�t�Z�b�g����]�s��ŕϊ��i���[�J�������[���h�j
        D3DXVECTOR3 rotatedOffset;
        D3DXVec3TransformCoord(&rotatedOffset, &localOffset, &matRot);

        // ��]��EscMtx�ɔ��f
        D3DXMatrixMultiply(&EscMtx, &EscMtx, &matRot);

        // �I�t�Z�b�g�𔽉f�����ʒu���v�Z
        D3DXVECTOR3 finalPos = GetDATA().Pos + rotatedOffset;
        D3DXMatrixTranslation(&mtxTrans, finalPos.x, finalPos.y, finalPos.z);

        // �ŏI�s����쐬
        D3DXMatrixMultiply(&EscMtx, &EscMtx, &mtxTrans);

        // OBB�̕����ƈʒu��ݒ�
        m_OBB.m_Direct[0] = D3DXVECTOR3(EscMtx._11, EscMtx._12, EscMtx._13);
        m_OBB.m_Direct[1] = D3DXVECTOR3(EscMtx._21, EscMtx._22, EscMtx._23);
        m_OBB.m_Direct[2] = D3DXVECTOR3(EscMtx._31, EscMtx._32, EscMtx._33);
        m_OBB.m_Pos = D3DXVECTOR3(EscMtx._41, EscMtx._42, EscMtx._43);

        HitCollision();
    }
    else
    {//3D

    }
}


//=============================
// �`��
//=============================
void CBulletLine::Draw()
{
    CRenderer* pRenderer = nullptr;

    CManager* pManager = CManager::GetInstance();

    pRenderer = pManager->GetRenderer();

    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();





    if (m_bDrawOk == true)
    {
        DATA EscData = GetDATA();


        //SetSizeMag(D3DXVECTOR3 (2.0f,2.0f,2.0f));//�{��
        //SizeMagChangebool(true);



       // CObjectX::Draw();

        CRenderer* pRenderer = nullptr;
        CManager* pManager = CManager::GetInstance();
        pRenderer = pManager->GetRenderer();
        LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();


        D3DXMATRIX mtxRot, mtxTrans;


        // ���[���h�}�g���b�N�X�̏�����
        D3DXMatrixIdentity(&m_mtxWorld);


        D3DXVECTOR3 SetMag;

        SetMag = D3DXVECTOR3(2.0f, 2.0f, 2.0f);


        // ���f���̃T�C�Y��ύX

        D3DXMatrixScaling(&m_mtxWorld, SetMag.x, SetMag.y, SetMag.z);

        // �����𔽉f
        D3DXMatrixRotationYawPitchRoll(&mtxRot, EscData.rot.y, EscData.rot.x, EscData.rot.z);
        D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

        // �ʒu�𔽉f
        D3DXMatrixTranslation(&mtxTrans, EscData.Pos.x, EscData.Pos.y, EscData.Pos.z);
        D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

        D3DMATERIAL9 matDef;
        D3DXMATERIAL* pMat;



        // ���[���h�}�g���b�N�X�̐ݒ�
        EscDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
        // ���_�t�H�[�}�b�g�̐ݒ�
        EscDevice->SetFVF(FVF_VERTEX_3D);
        // ���݂̃}�e���A�����擾
        EscDevice->GetMaterial(&matDef);

        // �ʏ�̃I�u�W�F�N�g�̕`��
  
            pMat = reinterpret_cast<D3DXMATERIAL*>(m_pBuffMat->GetBufferPointer());

            for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
            {
                // ���[���h�s������ɖ߂�
                EscDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

                // �}�e���A���̐ݒ�
                EscDevice->SetMaterial(&pMat[nCntMat].MatD3D);


                pMat[nCntMat].pTextureFilename = NULL;

                EscDevice->SetTexture(0, nullptr);

                if (m_bFast == false)
                {//�n�߂̈��̂�
                    m_OriginalColor = pMat[nCntMat].MatD3D.Diffuse;
                    m_bFast = true;
                }


                // ���b�V���̕`��


                  //  D3DXCOLOR originalColor;


                pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(
                    m_OriginalColor.r * SetMag.x,
                    m_OriginalColor.g * SetMag.y,
                    m_OriginalColor.b * SetMag.z,
                    m_OriginalColor.a
                );

                EscDevice->SetMaterial(&pMat[nCntMat].MatD3D);
                pMat[nCntMat].MatD3D.Diffuse = m_OriginalColor;



                m_pMesh->DrawSubset(nCntMat);

                // �ۑ����Ă����}�e���A����߂�
                EscDevice->SetMaterial(&matDef);
            }

        


    }

#if _DEBUG
    //char cData2[100] = {};
    //DATA EscData = GetDATA();//�Ď擾
    //snprintf(cData2, sizeof(cData2), "���݂�GRID/%d", (int)EscData.rot.x); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[
    //CFont::DrawTextSet(D3DXVECTOR3(900.0f, 450.0f, 0.0f), 40, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), cData2);
#else

#endif // _D


}

//=============================
// ����
//=============================
CBulletLine* CBulletLine::Create(DATA SetData, CObjectMotionPlayer* pMotion)
{
    CBulletLine* pObstacle = new CBulletLine;

    pObstacle->Init();

    // �擾
    DATA EscData = pObstacle->GetDATA();
    EscData = SetData; // �ڂ�

    D3DXVECTOR3 SizeMag;

    //�T�C�Y�ϓ�
    SizeMag.x = EscData.MaxLength.x / 10.0f;
    SizeMag.y = EscData.MaxLength.y / 20.0f;
    SizeMag.z = EscData.MaxLength.z / 10.0f;

    //  EscData.rot.y = D3DX_PI * 0.5f;

    pObstacle->SetSizeMag(SizeMag);//�{���ϓ�

 //   pObstacle->SetChangeColor(D3DXCOLOR(1.0f,1.0f,0.0f,0.7f));

    pObstacle->SetDATA(EscData); // �i�[
    pObstacle->SetParent(pMotion);
    return pObstacle;
}




//=============================
// �����蔻��܂Ƃ�
//=============================
void CBulletLine::HitCollision()
{
    m_bHit = false;

    //�擾
    DATA EscData = GetDATA();



    bool bHit = false;

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

                        //���Z�b�g
            pEnemyNomal->GetLockOnUI()->SetDrawOk(false);
            pEnemyNomal->GetLockOnUIMain()->SetDrawOk(false);

            if (bHit == true)
            {
                //�����Ńo���b�g���b�N
                pEnemyNomal->GetLockOnUIMain()->SetDrawOk(true);
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

                            //���Z�b�g
                pEnemyFast->GetLockOnUI()->SetDrawOk(false);
                pEnemyFast->GetLockOnUIMain()->SetDrawOk(false);

                if (bHit == true)
                {
                    //�����Ńo���b�g���b�N
                    pEnemyFast->GetLockOnUIMain()->SetDrawOk(true);
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

                            //���Z�b�g
                pEnemyBoss->GetLockOnUI()->SetDrawOk(false);
                pEnemyBoss->GetLockOnUIMain()->SetDrawOk(false);

                if (bHit == true)
                {
                    //�����Ńo���b�g���b�N
                    pEnemyBoss->GetLockOnUIMain()->SetDrawOk(true);
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

                            //���Z�b�g
                pEnemyBoss->GetLockOnUI()->SetDrawOk(false);
                pEnemyBoss->GetLockOnUIMain()->SetDrawOk(false);

                if (bHit == true)
                {
                    //�����Ńo���b�g���b�N
                    pEnemyBoss->GetLockOnUIMain()->SetDrawOk(true);
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

    if (bHit == true)
    {
        m_bHit = true;
    }
}