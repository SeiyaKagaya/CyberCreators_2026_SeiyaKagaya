//=========================================================
//
// ObstacleSet[ObstacleSet.cpp]
// Author seiya kagaya
//
//=========================================================
#include "ObstacleSet.h"
#include "manager.h"

// �ÓI�����o�ϐ��̏�����
std::vector<CObstacleSet::OBSTACLEINFO> CObstacleSet::m_ObstacleInfo = {}; // xfile�ƃC���f�b�N�X�̊i�[
int CObstacleSet::m_ObstacleCount = 10; // ��̍\���̂̃T�C�Y

bool CObstacleSet::m_bRelease = false;//�J��������

int CObstacleSet::m_NowSetModelIndex = 0;//���݂̃��f���^�C�v
int CObstacleSet::m_MAXModelIndex = 0;//�ő僂�f����
D3DXVECTOR3 CObstacleSet::m_SetRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//���݂̃��f���^�C�v


//=============================
// �R���X�g���N�^
//=============================
CObstacleSet::CObstacleSet(int nPriority) :CObjectX(nPriority)
{
    m_bBreak = false;
    m_bPreview = false;
    m_nType = 0;
    m_StageBlock = false;
}

//=============================
// �f�X�g���N�^
//=============================
CObstacleSet::~CObstacleSet()
{
}

//=============================
// ������
//=============================
HRESULT CObstacleSet::Init()
{
    CObjectX::Init();

    CRenderer* pRenderer = nullptr;
    CManager* pManager = CManager::GetInstance();
    pRenderer = pManager->GetRenderer();

    LPD3DXMESH pMesh = nullptr; // Mesh�|�C���^
    LPD3DXBUFFER pBuffMat = nullptr; // �}�e���A���ւ̃|�C���^
    DWORD dwNumMat = 0; // �}�e���A���̐�

    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

    // �t�@�C���̓ǂݍ���
    D3DXLoadMeshFromX(m_ObstacleInfo[m_nType].pFilePass,
        D3DXMESH_SYSTEMMEM,
        EscDevice,
        NULL,
        &pBuffMat,
        NULL,
        &dwNumMat,
        &pMesh);
    





    //// �o�E���f�B���O�{�b�N�X���i�[���邽�߂̕ϐ�
    //D3DXVECTOR3 vMin, vMax;

    //// ���_�o�b�t�@���擾
    //LPDIRECT3DVERTEXBUFFER9 pVertexBuffer = NULL;
    //pMesh->GetVertexBuffer(&pVertexBuffer);
    //
    //// ���_�f�[�^���������Ƀ��b�N����
    //void* pVertices = NULL;
    //pVertexBuffer->Lock(0, 0, &pVertices, 0);
    //
    //// ���_�t�H�[�}�b�g���擾���A���_�̈ʒu��񂪊i�[����Ă���I�t�Z�b�g�����߂�
    //DWORD vertexSize = pMesh->GetNumVertices();
    //DWORD fvf = pMesh->GetFVF();
    //DWORD vertexPosOffset = (fvf & D3DFVF_XYZRHW) ? sizeof(D3DXVECTOR3) : 0;

    //// �o�E���f�B���O�{�b�N�X���v�Z
    //D3DXComputeBoundingBox(
    //    (const D3DXVECTOR3*)pVertices,  // ���_�f�[�^�i�ʒu���j
    //    vertexSize,                     // ���_�̐�
    //    vertexPosOffset,                // ���_�t�H�[�}�b�g�Ɋ�Â��I�t�Z�b�g�i�ʒu���̃I�t�Z�b�g�j
    //    &vMin,                          // �ŏ��_
    //    &vMax                           // �ő�_
    //);

   // // ���_�o�b�t�@�̃��b�N������
   // pVertexBuffer->Unlock();


    // �擾
    DATA EscData = GetDATA();

    EscData.MinLength = D3DXVECTOR3(100000.0f, 1000000.0f, 100000.0f); //���f���̍ŏ��ʒu
    EscData.MaxLength = D3DXVECTOR3(-10000.0f, -1000000.0f, -100000.0f); //���f���̍ő�ʒu

    int nNumVtx; //���_��
    DWORD sizeFVF; //���_�t�H�[�}�b�g�̃T�C�Y
    BYTE* pVtxBuff; //���_�o�b�t�@�̃|�C���^

    //���_���̎擾
    nNumVtx = pMesh->GetNumVertices();
    //���_�t�H�[�}�b�g�̃T�C�Y���擾
    sizeFVF = D3DXGetFVFVertexSize(pMesh->GetFVF());

    //���_�o�b�t�@�̃��b�N
    pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
    for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
    {
        //���_���W�̑��
        D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

        // ���W�ϊ��s����쐬
        D3DXMATRIXA16 matRotation;
        D3DXMatrixRotationYawPitchRoll(&matRotation, EscData.rot.y, EscData.rot.x, EscData.rot.z);

        // ���_���W����]
        D3DXVec3TransformCoord(&vtx, &vtx, &matRotation);


        if (vtx.x > EscData.MaxLength.x)
        {
            EscData.MaxLength.x = vtx.x;
        }
        if (vtx.x < EscData.MinLength.x)
        {
            EscData.MinLength.x = vtx.x;
        }

        if (vtx.y > EscData.MaxLength.y)
        {
            EscData.MaxLength.y = vtx.y;
        }
        if (vtx.y < EscData.MinLength.y)
        {
            EscData.MinLength.y = vtx.y;
        }

        if (vtx.z > EscData.MaxLength.z)
        {
            EscData.MaxLength.z = vtx.z;
        }
        if (vtx.z < EscData.MinLength.z)
        {
            EscData.MinLength.z = vtx.z;
        }

        // ���̒��_�ɐi��
        pVtxBuff += sizeFVF;
    }


    if (m_nType == 5)
    {//stagemodel
        EscData.MinLength = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        EscData.MaxLength = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    }


    SetDATA(EscData); // �i�[



   





    D3DXMATERIAL* pMat = (D3DXMATERIAL*)pBuffMat->GetBufferPointer();

    //�e�N�X�`���ǂݍ���
    LPDIRECT3DTEXTURE9	m_ESCpTexture = nullptr;

    //�e�N�X�`���擾
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


    SetXfireData(pMesh, pBuffMat, dwNumMat); // �f�[�^�i�[

    SetObjectType(CObject::OBJECT_OBSTACLE);

    SetSizeMag(D3DXVECTOR3(1.0f,1.0f,1.0f)); // �傫���{��

 

    return S_OK;
}

//=============================
// �j��
//=============================
void CObstacleSet::Uninit()
{
    int test = 0;

    if (m_bRelease == false)
    {
        m_bRelease = true;
        for (int i = 0; i < m_ObstacleCount; i++)
        {
            delete m_ObstacleInfo[i].pFilePass;
        }
    }
 
    
    CObjectX::Uninit();

   // delete this;
}

//=============================
// �X�V
//=============================
void CObstacleSet::Update()
{

    // �擾
   DATA EscData = GetDATA();

    SetDATA(EscData); // �i�[

    CRenderer* pRenderer = nullptr;

    CManager* pManager = CManager::GetInstance();
    CInputKeyboard* keyboard = pManager->GetKeyboard();
       
    if (m_StageBlock == true)
    {

    }

}

//=============================
// �`��
//=============================
void CObstacleSet::Draw()
{
  //  SizeMagChangebool(true);
    CObjectX::Draw();
}

//=============================
// ����
//=============================
CObstacleSet* CObstacleSet::Create(DATA SetData, int SetType, bool bBreak, bool bPreview)
{
    CObstacleSet* pObstacle = new CObstacleSet;

    pObstacle->m_nType = SetType;


    // �擾
    DATA EscData = pObstacle->GetDATA();
    EscData = SetData; // �ڂ�

    pObstacle->m_bBreak = bBreak;
    pObstacle->m_bPreview = bPreview;

    pObstacle->SetDATA(EscData); // �i�[

    pObstacle->Init();

    return pObstacle;
}

//=============================
// �z��T�C�Y�ύX
//=============================
void CObstacleSet::Resize(int count)
{

    //// �����̓��I�����������
    //for (size_t i = 0; i < m_ObstacleInfo.size(); ++i)
    //{
    //    delete[] m_ObstacleInfo[i].pFilePass; // ���I�Ɋm�ۂ��������������
    //    m_ObstacleInfo[i].pFilePass = nullptr; // �|�C���^�𖳌���
    //}

    m_ObstacleInfo.resize(count);
}

//=============================
// �f�[�^���[�h
//=============================
void CObstacleSet::DataLoad(const char* filename)
{
    int ModelPassCnt = 0; // pass�J�E���g�A�b�v�p
    DATA EscData = {}; // �N���G�C�g�p�̃f�[�^�ꎞ�i�[
    int SetTypeIndex = 0; // �Z�b�g����^�C�v���ꎞ�i�[

    FILE* pFile = nullptr; // �t�@�C���|�C���^��錾
    char aString[2000]; // �ǂݍ��ލő啶����
    
    pFile = fopen(filename, "r");

    if (pFile != nullptr)
    {
        while (1)
        {
            fscanf(pFile, "%s", aString);

            if (strcmp(aString, "END_SCRIPT") == 0)
            {
                fclose(pFile);//����
                break;
            }
            else if (strcmp(aString, "NUM_MODEL") == 0)
            {
                fscanf(pFile, "%s", aString); // '='���z��
                fscanf(pFile, "%d", &m_ObstacleCount); // �z�񐔂������

                CObstacleSet::Resize(m_ObstacleCount); // �z��̃T�C�Y��ύX
            }
            else if (strcmp(aString, "MODEL_FILENAME") == 0)
            {
                fscanf(pFile, "%s", aString); // '='���z��
                fscanf(pFile, "%s", aString); // �{��

                char* filePass = new char[strlen(aString) + 1];//�������m��
                strcpy(filePass, aString);//�R�s�[

                m_ObstacleInfo[ModelPassCnt].ModelIndex = ModelPassCnt;
                m_ObstacleInfo[ModelPassCnt].pFilePass = filePass;

                ModelPassCnt++;

            }
            else if (strcmp(aString, "MODELSET") == 0)
            {
                while (1)
                {
                    fscanf(pFile, "%s", aString);

                    if (strcmp(aString, "END_MODELSET") == 0)
                    {
                        Create(EscData, SetTypeIndex, false, false);
                        break;
                    }
                    else if (strcmp(aString, "TYPE") == 0)
                    {
                        fscanf(pFile, "%s", aString); // '='���z��
                        fscanf(pFile, "%d", &SetTypeIndex); // type���i�[
                    }
                    else if (strcmp(aString, "POS") == 0)
                    {
                        fscanf(pFile, "%s", aString);
                        fscanf(pFile, "%f %f %f", &EscData.Pos.x, &EscData.Pos.y, &EscData.Pos.z);
                    }
                    else if (strcmp(aString, "ROT") == 0)
                    {
                        fscanf(pFile, "%s", aString);
                        fscanf(pFile, "%f %f %f", &EscData.rot.x, &EscData.rot.y, &EscData.rot.z);
                    }
                }
            }
        }
    }
    //�ő吔��ۑ�
    m_MAXModelIndex = ModelPassCnt-1;
}



//=============================
//���f���Z�b�g��Ԃ��Z�[�u
//=============================
void CObstacleSet::Model_DebugSave(void)
{
    FILE* pFile;//�t�@�C���|�C���^��錾

    //�t�@�C�����J��
    pFile = fopen("DATA\\ForDevelopment\\Setinfo.txt", "w");

    if (pFile != NULL)
    {
        fprintf(pFile, "#------------------------------------------------------------------------------\n");
        fprintf(pFile, "  # ���f���z�u���\n");
        fprintf(pFile, "#------------------------------------------------------------------------------\n");


      
     //   for (int nCnt = 0; nCnt < LAYERINDEX_MAX; nCnt++)
      //  {
        int nCnt = (int)LAYERINDEX_OBSTACLE;

            CObject* pObj = CObject::GetpTop(nCnt);//�擪�擾

            if (pObj != nullptr)
            {//�擪���Ȃ�==�v���C�I���e�B�܂���ƂȂ�

             //�ő吔�s���̂���while
                while (pObj != nullptr)
                {
                    CObject* pNext = pObj->GetNext();
                    
                    //�ϊ�
                    CObstacleSet* pObstacleSet;

                    pObstacleSet = (CObstacleSet*)pObj;

                    if (pObstacleSet->GetPreviewBool() == true)
                    {//�v���r���[���f���������Ƃ�
                    }
                    else
                    {
                        int EscType = pObstacleSet->GetModelType();
                        CObject::DATA EscData = pObstacleSet->GetDATA();

                        fprintf(pFile, "MODELSET\nTYPE = %d\nPOS = %.2f %.2f %.2f\nROT = %.2f %.2f %.2f\nEND_MODELSET\n\n"
                            , EscType
                            , EscData.Pos.x, EscData.Pos.y, EscData.Pos.z
                            , EscData.rot.x, EscData.rot.y, EscData.rot.z
                        );
                    }

                    pObj = pNext;

                }
            }
      //  }


        //
        // //�v���r���[���f���ȊO������
        //for (int nPriority = 0; nPriority < CObject::LAYERINDEX_MAX; nPriority++)
        //{
    
        //    for (int nCnt = 0; nCnt < CObject::GetnNumAll(); nCnt++)
        //    {//�Sobject����

        //        CObject* pObject = CObject::GetObjectData(nCnt, (CObject::LAYERINDEX)nPriority);//�I�u�W�F�N�g�f�[�^�擾

        //        if (pObject != nullptr)
        //        {
        //            CObject::OBJECTTYPE type = pObject->GetObjectType();//�^�C�v�擾

        //            if (type == CObject::OBJECT_OBSTACLE)
        //            {//�T���Ă���^�C�v�ƈ�v

        //                //�ϊ�
        //                CObstacleSet* pObstacleSet;

        //                pObstacleSet = (CObstacleSet*)pObject;

        //                if (pObstacleSet->GetPreviewBool() == true)
        //                {//�v���r���[���f���������Ƃ�
        //                }
        //                else
        //                {
        //                    int EscType = pObstacleSet->GetModelType();
        //                    CObject::DATA EscData = pObstacleSet->GetDATA();

        //                    fprintf(pFile, "MODELSET\nTYPE = %d\nPOS = %.2f %.2f %.2f\nROT = %.2f %.2f %.2f\nEND_MODELSET\n\n"
        //                        , EscType
        //                        , EscData.Pos.x, EscData.Pos.y, EscData.Pos.z
        //                        , EscData.rot.x, EscData.rot.y, EscData.rot.z
        //                        );
        //                }
        //            }
        //        }
        //    }

        //}
        
        fprintf(pFile, "\nEND_SCRIPT");

        //�t�@�C������
        fclose(pFile);
    }
    else
    {
    }

}


//=============================
// �v���r���[���f������
//=============================
void CObstacleSet::previewModelLoad()
{
    bool bSet = false;//�Z�b�g����Ă��邩

    int nCnt = (int)LAYERINDEX_OBSTACLE;

   // for (int nCnt = 0; nCnt < LAYERINDEX_MAX; nCnt++)
   // {
        CObject* pObj = CObject::GetpTop(nCnt);//�擪�擾

        if (pObj != nullptr)
        {//�擪���Ȃ�==�v���C�I���e�B�܂���ƂȂ�

         //�ő吔�s���̂���while
            while (pObj != nullptr)
            {
                CObject* pNext = pObj->GetNext();

                //�ϊ�
                CObstacleSet* pObstacleSet;

                pObstacleSet = (CObstacleSet*)pObj;

                if (pObstacleSet->GetPreviewBool() == true)
                {//�v���r���[���f���������Ƃ�

                    if (pObstacleSet->GetModelType() == m_NowSetModelIndex)
                    {//���݂̃��f���^�C�v�Ɠ����Ƃ�
                        bSet = true;//�Z�b�g�ς݂ɂ���B
                        break;
                    }
                    else
                    {//�Ⴄ�Ƃ�

//                        pObstacleSet->Release();//�Ώۂ������[�X
                        pObstacleSet->SetDeath(true);
                        
                        break;

                    }
                }
                //if (pObstacleSet->GetPreviewBool() == true)
                //{//�v���r���[���f���������Ƃ�
                //}
                //else
                //{
                //    int EscType = pObstacleSet->GetModelType();
                //    CObject::DATA EscData = pObstacleSet->GetDATA();

                //    fprintf(pFile, "MODELSET\nTYPE = %d\nPOS = %.2f %.2f %.2f\nROT = %.2f %.2f %.2f\nEND_MODELSET\n\n"
                //        , EscType
                //        , EscData.Pos.x, EscData.Pos.y, EscData.Pos.z
                //        , EscData.rot.x, EscData.rot.y, EscData.rot.z
                //    );
                //}

                pObj = pNext;

            }
        }
  //  }



    ////�v���r���[���f������
    //for (int nPriority = 0; nPriority < CObject::LAYERINDEX_MAX; nPriority++)
    //{
    //    for (int nCnt = 0; nCnt < CObject::GetnNumAll(); nCnt++)
    //    {//�Sobject����

    //        CObject* pObject = CObject::GetObjectData(nCnt, (CObject::LAYERINDEX)nPriority);//�I�u�W�F�N�g�f�[�^�擾

    //        if (pObject != nullptr)
    //        {
    //            CObject::OBJECTTYPE type = pObject->GetObjectType();//�^�C�v�擾

    //            if (type == CObject::OBJECT_OBSTACLE)
    //            {//�T���Ă���^�C�v�ƈ�v
    //                
    //                //�ϊ�
    //                CObstacleSet* pObstacleSet;

    //                pObstacleSet = (CObstacleSet*)pObject;
    //                if (pObstacleSet->GetPreviewBool()==true)
    //                {//�v���r���[���f���������Ƃ�
    //    
    //                    if (pObstacleSet->GetModelType()== m_NowSetModelIndex)
    //                    {//���݂̃��f���^�C�v�Ɠ����Ƃ�
    //                        bSet = true;//�Z�b�g�ς݂ɂ���B
    //                        break;
    //                    }
    //                    else
    //                    {//�Ⴄ�Ƃ�
    //                        pObstacleSet->Release();//�Ώۂ������[�X
    //                        break;
    //                      
    //                    }
    //                }
    //            }
    //        }
    //    }
    //}













    if (bSet==false)
    {//�Z�b�g���Ă��Ȃ��A�������̓^�C�v���Ⴄ
        CRenderer* pRenderer = nullptr;

        CManager* pManager = CManager::GetInstance();

        CInputKeyboard* keyboard = pManager->GetKeyboard();


        DATA SetData;
        //Mouse�ŉ�ʂɎw���Ă�3D��ԍ��W�擾
        SetData.Pos = keyboard->GetMouseRayIntersection(*pManager->GetCamera());

        // SetData.rot.y ���^�[�Q�b�g�̕����ɍ��킹��
        SetData.rot = m_SetRot;
        //----------------------------------------------------------------------------------

        //���݂̃��f���^�C�v�ōč\��
        Create(SetData, m_NowSetModelIndex, false, true);
    }


}
//=============================
// �v���r���[���f�����擾
//=============================
bool CObstacleSet::GetPreviewBool()
{
    return m_bPreview;
}
//=============================
// ���f���^�C�v�擾
//=============================
int CObstacleSet::GetModelType()
{
    return m_nType;
}
//=============================
// �ݒu�p�Ɨ�����
//=============================
void CObstacleSet::Input()
{
    CRenderer* pRenderer = nullptr;

    CManager* pManager = CManager::GetInstance();

    CInputKeyboard* keyboard = pManager->GetKeyboard();

    //---------------------------------------------------------�ړ��n
    if (keyboard->GetTrigger(DIK_8) == true)
    {
        if (0 >= m_NowSetModelIndex)
        {
            m_NowSetModelIndex = m_MAXModelIndex;
        }
        else
        {
            m_NowSetModelIndex -= 1;
        }
    }
    if (keyboard->GetTrigger(DIK_9) == true)
    {
        if (m_NowSetModelIndex >= m_MAXModelIndex)
        {
            m_NowSetModelIndex = 0;
        }
        else
        {
            m_NowSetModelIndex += 1;
        }
    }



    if (keyboard->GetTrigger(DIK_UP) == true)
    {
      
        m_SetRot.y += (D3DX_PI / 6);

        if (D3DX_PI - 0.1f >= m_SetRot.y)
        {
            
        }
        else
        {
            m_SetRot.y = 0.0f;
        }
    }
    if (keyboard->GetTrigger(DIK_DOWN) == true)
    {
      
        m_SetRot.y -= (D3DX_PI / 6);

        if (0.0f + 0.1f <= m_SetRot.y)
        {
           
        }
        else
        {
            m_SetRot.y = D3DX_PI;
        }
    }


    //if (keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left))
    //{//���{�^���������ꂽ

    //    //Mouse�̕�����ballet���΂�
    //    //----------------------------------------------------------------------------------
    //    DATA SetData;
    //    //Mouse�ŉ�ʂɎw���Ă�3D��ԍ��W�擾
    //    SetData.Pos = keyboard->GetMouseRayIntersection(*pManager->GetCamera());

    //    // SetData.rot.y ���^�[�Q�b�g�̕����ɍ��킹��
    //    SetData.rot = m_SetRot;
    //    //----------------------------------------------------------------------------------

    //    Create(SetData, m_NowSetModelIndex, false, false);
    //}

    if (keyboard->GetTrigger(DIK_F3) == true)
    {//�Z�[�u
        Model_DebugSave();
    }
    //if (keyboard->GetTrigger(DIK_F1) == true)
    //{//�폜
    //    DestroyCircle();
    //}
   
    if (keyboard->GetTrigger(DIK_F6) == true)
    {
        ObstacleScanMapping();//�}�b�s���O
    }
}
//=============================
// �ݒu�p�e�X�g�`��
//=============================
void CObstacleSet::DebugSetDataDraw()
{
    char cData2[100] = {};
    snprintf(cData2, sizeof(cData2), "[F1]�Ń}�E�X���W�̃��f���폜�I\n[F3]�ŏ����o���I���݂�Index[%d]�p�x[y=%.2f]", m_NowSetModelIndex, m_SetRot.y); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[
    // mousePos.x �� mousePos.y ���}�E�X�̈ʒu
    CFont::DrawTextSet(D3DXVECTOR3(100.0f, 600.0f, 0.0f), 20, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), cData2);

}




//=============================
//��Q���̌��m�Ƃ���𓥂܂����}�b�s���O
//=============================
void CObstacleSet::ObstacleScanMapping()
{
    

  //  float fMapBlockLength = 300.0f;


    //�}�X�ڗp�f�[�^
    CMathProc::Cell GridData[CMathProc::GRIDROW][CMathProc::GRIDCOL] = {};


    //typedef struct
    //{
    //    int GridDistance[CMathProc::GRIDROW][CMathProc::GRIDCOL];//�O���b�h�ɔz�u���ꂽ����
    //}ROUTEDATA;



    //������
    for (int i = 0; i < CMathProc::GRIDROW; i++)
    {
        for (int M = 0; M < CMathProc::GRIDCOL; M++)
        {
            GridData[i][M].bBlock = false;
            GridData[i][M].Num = 0;
        }
    }




    //�܂���Q�������m�E����}�X��true��
    //----------------------------------------------------------------------------------------------------
    for (int i = 0; i < CMathProc::GRIDROW; i++)
    {
        for (int M = 0; M < CMathProc::GRIDCOL; M++)
        {
            //�z�u���v���C�I���e�B�̐擪���擾
            CObject* pObj = GetpTop(LAYERINDEX_OBSTACLE);

            if (pObj != nullptr)
            {//�擪���Ȃ�==�v���C�I���e�B�܂���ƂȂ�
                while (pObj != nullptr)
                {
                    if (pObj->GetObjectType() == OBJECT_OBSTACLE)
                    {//�ݒu���f���̂Ƃ�

                        CObstacleSet* pObstacleObject = static_cast<CObstacleSet*>(pObj);//�L���X�g

                        DATA ObjectData = pObstacleObject->GetDATA();//�f�[�^�擾

                        if ((float)CMathProc::GRIDLEGTH * i < ObjectData.Pos.z && (float)CMathProc::GRIDLEGTH * (i + 1) > ObjectData.Pos.z)
                        {
                            if ((float)CMathProc::GRIDLEGTH * M < ObjectData.Pos.x && (float)CMathProc::GRIDLEGTH * (M + 1) > ObjectData.Pos.x)
                            {
                                //�}�X�͈͓̔�����Q������

                                GridData[i][M].bBlock = true;

                                //for�܂Ŗ߂��Ď��̃}�X�ɐi��
                                break;
                            }
                        }

                    }

                    CObject* pNext = pObj->GetNext();
                    pObj = pNext;
                }
            }
        }
    }//----------------------------------------------------------------------------------------------------

//    //��Q���ɋC�����Ȃ���"���D��T��"������
//    //--------------------------------------------------------------------------------------------------------------
    // �X�^�[�g�ʒu�ƃS�[���ʒu
     

#if 1
    for (int A = 0; A < CMathProc::GRIDROW; A++)
    {
        for (int B = 0; B < CMathProc::GRIDCOL; B++)
        {
            for (int C = 0; C < CMathProc::GRIDROW; C++)
            {
                for (int D = 0; D < CMathProc::GRIDCOL; D++)
                {

   //-------------------------X---Y
                    CMathProc::Point start = { B, A };
                    CMathProc::Point goal = { D,C };
#else
                    CMathProc::Point start = { 0, 0 };
                    CMathProc::Point goal = { 10,7 };
#endif



                 


                    //�Z���i�[
                    CMathProc::SetCell(GridData);

                    // ���D��T�������s
                    CMathProc::bfs(start, goal);

                    // ���ʂ�CSV�ɏ����o��
           //         CMathProc::writeToCSV("DATA\\ForDevelopment\\DepthResult.csv");

                    //�ŒZ�����ƌo�H�e�[�u���̍쐬
                    CMathProc::RouteTableSet(start, goal);

#if 1


                }
            }
        }
    }
#else
#endif // 0
    CMathProc::DRAWCSV("DATA\\ForDevelopment\\RouteResult.csv");


    
}



//=============================
// �����蔻��܂Ƃ�
//=============================
void CObstacleSet::HitCollision()
{
    //// �擾
    //DATA EscData = GetDATA();

    //// �����蔻��v�Z
    //m_HitData = CMathProc::CheckBoxCollision_3D(EscData.Pos, EscData.OldPos, EscData.MinLength, EscData.MaxLength, OBJECT_BLOCK3D,LAYERINDEX_BLOCK3D,EscData.move);

    //if (m_HitData.bHit == true)
    //{
    //    if (m_HitData.HitAngle.x == 1)
    //    {
    //        EscData.Pos.x += m_HitData.ResultDistance.x;
    //        EscData.move.x = 0.0f;
    //    }
    //    else if (m_HitData.HitAngle.x == -1)
    //    {
    //        EscData.Pos.x -= m_HitData.ResultDistance.x;
    //        EscData.move.x = 0.0f;
    //    }
    //    else if (m_HitData.HitAngle.y == 1)
    //    {
    //        EscData.Pos.y += m_HitData.ResultDistance.y;
    //        EscData.move.y = 0.0f;
    //    }
    //    else if (m_HitData.HitAngle.y == -1)
    //    {
    //        EscData.Pos.y -= m_HitData.ResultDistance.y;
    //        EscData.move.y = 0.0f;
    //    }
    //    else if (m_HitData.HitAngle.z == 1)
    //    {
    //        EscData.Pos.z += m_HitData.ResultDistance.z;
    //        EscData.move.z = 0.0f;
    //    }
    //    else if (m_HitData.HitAngle.z == -1)
    //    {
    //        EscData.Pos.z -= m_HitData.ResultDistance.z;
    //        EscData.move.z = 0.0f;
    //    }
    //}

    //SetDATA(EscData); // �i�[
}
//=============================
// �X�e�[�W�z�u�����擾
//=============================
bool CObstacleSet::GetStageBlockbool()
{
    return m_StageBlock;
}
