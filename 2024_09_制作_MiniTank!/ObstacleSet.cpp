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

    // �擾
    DATA EscData = GetDATA();
    EscData = GetDATA(); // �Ď擾


    SetDATA(EscData); // �i�[

    return S_OK;
}

//=============================
// �j��
//=============================
void CObstacleSet::Uninit()
{
    CObjectX::Uninit();
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
       

//�ȉ���MAPPING�p
#if 0
    if (m_bPreview == true)
    {
        DATA EscData = GetDATA();//�擾

        //Mouse�ŉ�ʂɎw���Ă�3D��ԍ��W�擾
        EscData.Pos = keyboard->GetMouseRayIntersection(*pManager->GetCamera());
        
        EscData.rot = m_SetRot;

        SetDATA(EscData); // �i�[
   
    }
    else
    {
        //������邩����
        if (keyboard->GetTrigger(DIK_F1) == true)
        {//�폜
               //Mouse�ŉ�ʂɎw���Ă�3D��ԍ��W�擾
            DATA EscData2;
            EscData2.Pos = keyboard->GetMouseRayIntersection(*pManager->GetCamera());

            //�͈͐���
            D3DXVECTOR3 HitMin = D3DXVECTOR3(EscData2.Pos.x - 200.0f, 0.0f, EscData2.Pos.z - 200.0f);
            D3DXVECTOR3 HitMax = D3DXVECTOR3(EscData2.Pos.x + 200.0f, 0.0f, EscData2.Pos.z + 200.0f);

            if (HitMin.x <= EscData.Pos.x && HitMax.x >= EscData.Pos.x)
            {
                if (HitMin.z <= EscData.Pos.z && HitMax.z >= EscData.Pos.z)
                {//�����
                    SetDeath(true);
                }
            }
        }
    }
#else
#endif // 0
}

//=============================
// �`��
//=============================
void CObstacleSet::Draw()
{
    SizeMagChangebool(true);
    CObjectX::Draw();
}

//=============================
// ����
//=============================
CObstacleSet* CObstacleSet::Create(DATA SetData, int SetType, bool bBreak, bool bPreview)
{
    CObstacleSet* pObstacle = new CObstacleSet;

    pObstacle->m_nType = SetType;
    pObstacle->Init();

    // �擾
    DATA EscData = pObstacle->GetDATA();
    EscData = SetData; // �ڂ�

    pObstacle->m_bBreak = bBreak;
    pObstacle->m_bPreview = bPreview;

    if (pObstacle->m_nType == (m_ObstacleCount - 1))
    {//�ő�l�̃��f���^�C�v�̂Ƃ�
        pObstacle->m_StageBlock = true;//�X�e�[�Wblock����

        EscData.MinLength = D3DXVECTOR3(-150.0f, 0.0f, -150.0f);
        EscData.MaxLength = D3DXVECTOR3(150.0f, 300.0f, 150.0f);
    }
    else
    {
        EscData.MinLength = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        EscData.MaxLength = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    }

    pObstacle->SetDATA(EscData); // �i�[

    return pObstacle;
}

//=============================
// �z��T�C�Y�ύX
//=============================
void CObstacleSet::Resize(int count)
{
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
                        pObstacleSet->SetDeath(true);
                        
                        break;
                    }
                }
                pObj = pNext;
            }
        }
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
    snprintf(cData2, sizeof(cData2), "[F1]�Ń}�E�X���W�̃��f���폜�I\n[F3]��model�����o���I���݂�Index[%d]�p�x[y=%.2f]", m_NowSetModelIndex, m_SetRot.y); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[
    // mousePos.x �� mousePos.y ���}�E�X�̈ʒu
    CFont::DrawTextSet(D3DXVECTOR3(100.0f, 600.0f, 0.0f), 20, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), cData2);

}

//=============================
//��Q���̌��m�Ƃ���𓥂܂����}�b�s���O
//=============================
void CObstacleSet::ObstacleScanMapping()
{
    //�}CObstacleSet�X�ڗp�f�[�^
    CMathProc::Cell GridData[CMathProc::GRIDROW][CMathProc::GRIDCOL] = {};

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
                                break;
                            }
                        }
                    }
                    CObject* pNext = pObj->GetNext();
                    pObj = pNext;
                }
            }
        }
    }

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

                    //�Z���i�[
                    CMathProc::SetCell(GridData);

                    // ���D��T�������s
                    CMathProc::bfs(start, goal);

                    //�ŒZ�����ƌo�H�e�[�u���̍쐬
                    CMathProc::RouteTableSet(start, goal);
                }
            }
        }
    }

    //CSV�ɏ����o��
    CMathProc::DRAWCSV("DATA\\ForDevelopment\\RouteResult.csv");
}

//=============================
// �����蔻��܂Ƃ�
//=============================
void CObstacleSet::HitCollision()
{
}

//=============================
// �X�e�[�W�z�u�����擾
//=============================
bool CObstacleSet::GetStageBlockbool()
{
    return m_StageBlock;
}