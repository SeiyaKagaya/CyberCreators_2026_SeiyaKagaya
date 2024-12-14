//=========================================================
//
// object_motion[object_motion.cpp]
// Author seiya kagaya
//
//=========================================================
#include "object_motion.h"
#include "renderer.h"
#include "manager.h"

//=============================
// �R���X�g���N�^
//=============================
CObjectMotion::CObjectMotion(int nPriority) :CObjectX(nPriority)
{
	m_Obb.m_Direct[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Obb.m_Direct[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Obb.m_Direct[2] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Obb.m_fLength[0] = 0.0f;
	m_Obb.m_fLength[1] = 0.0f;
	m_Obb.m_fLength[2] = 0.0f;

	m_Obb.m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);



    m_FilePass = {};

    m_CrassData = {};//��̂Ƃ��Ẵf�[�^
	m_CrassData.Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_CrassData.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_CrassData.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Model = {};

	m_oldMotionIndex_Parent = MOTIONTYPE_STANDBY;
	m_NowMotionIndex_Parent = MOTIONTYPE_STANDBY;
	m_NowKeyCnt_Parent=0;
	m_NowFrameCnt_Parent=0;
	m_EscapeMotion_Parent=0;
	m_BrendCnt_Parent=0;
	m_MotionLoopStop_Parent = false;
	m_MotionBrend_Parent = false;


	m_oldMotionIndex_Sub = MOTIONTYPE_STANDBY;
	m_NowMotionIndex_Sub = MOTIONTYPE_STANDBY;

	m_NowKeyCnt_Sub = 0;
	m_NowFrameCnt_Sub = 0;
	m_EscapeMotion_Sub = 0;
	m_BrendCnt_Sub = 0;
	m_MotionLoopStop_Sub = false;
	m_MotionBrend_Sub = false;
	m_groundCounter = 0;

    for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
    {
	
        m_pMesh[nCnt] = {};//Mesh�|�C���^
        m_pBuffMat[nCnt] = {};//�}�e���A���ւ̃|�C���^
        m_dwNumMat[nCnt] = {};//�}�e���A���̐�
		m_FilePass = {};
		m_PartfilePass[nCnt] = {};

		for (int i = 0; i < MAX_TEXTURE; i++)
		{
			m_pTexture[nCnt][i] = {};
		}
	}

}

//=============================
// �f�X�g���N�^
//=============================
CObjectMotion::~CObjectMotion()
{
}

//=============================
// ������
//=============================
HRESULT CObjectMotion::Init()
{
    //txt�ǂݍ���
    DataLoad();

    CRenderer* pRenderer = nullptr;
    CManager* pManager = CManager::GetInstance();
    pRenderer = pManager->GetRenderer();

    LPD3DXMESH pMesh = nullptr; // Mesh�|�C���^
    LPD3DXBUFFER pBuffMat = nullptr; // �}�e���A���ւ̃|�C���^
    DWORD dwNumMat = 0; // �}�e���A���̐�
    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();
	SetObjectType(CObject::OBJECT_MOTIONMODEL);

    return S_OK; 
}

//=============================
// �j��
//=============================
void CObjectMotion::Uninit()
{
	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		delete m_PartfilePass[nCnt];
	}

	delete m_FilePass;

    CObjectX::Uninit();
}

//=============================
// �X�V
//=============================
void CObjectMotion::Update()
{
		m_CrassData.OldPos = m_CrassData.Pos;
		m_CrassData.Pos += m_CrassData.move;

		bool bHit = false;

		////�ړ��ʂ��X�V(�^�������Ō���)
		//m_CrassData.move.x += (0.0f - m_CrassData.move.x) * (DAMPING_RATIO_LOAD_XZ);
		//m_CrassData.move.y += (0.0f - m_CrassData.move.y) * (DAMPING_RATIO_Y);
		//m_CrassData.move.z += (0.0f - m_CrassData.move.z) * (DAMPING_RATIO_LOAD_XZ);

		//OBB�܂��
		m_Obb.m_Pos = m_CrassData.Pos;

		D3DXMATRIX matRot;

		//�����x�N�g���擾
		D3DXMatrixRotationYawPitchRoll(&matRot, m_CrassData.rot.y, m_CrassData.rot.x, m_CrassData.rot.z);
		m_Obb.m_Direct[0] = D3DXVECTOR3(matRot._11, matRot._12, matRot._13);
		m_Obb.m_Direct[1] = D3DXVECTOR3(matRot._21, matRot._22, matRot._23);
		m_Obb.m_Direct[2] = D3DXVECTOR3(matRot._31, matRot._32, matRot._33);

		//--------���݂̂���GRID����������
		for (int i = 0; i < CMathProc::GRIDROW; i++)
		{
			for (int M = 0; M < CMathProc::GRIDCOL; M++)
			{
				//�����Ō��݂̈ʒu���v�Z�̂��A����GRID����ɓ����
				if ((float)CMathProc::GRIDLEGTH * i < m_CrassData.Pos.z && (float)CMathProc::GRIDLEGTH * (i + 1) > m_CrassData.Pos.z)
				{
					if ((float)CMathProc::GRIDLEGTH * M < m_CrassData.Pos.x && (float)CMathProc::GRIDLEGTH * (M + 1) > m_CrassData.Pos.x)
					{
						CMathProc::Point EscPoint;
						EscPoint.x = M;
						EscPoint.y = i;

						//�}�X�͈͓̔���GRID����
						m_NowGridNum = CMathProc::GetObjectNumfromPoint(EscPoint);
						break;
					}
				}
			}
		}

		CScene::MODE NowState = CScene::GetNowScene();

		if (NowState == CScene::MODE_GAME || NowState == CScene::MODE_GAME2 )
		{//�Q�[����
			if (m_NowMotionIndex_Sub == 1)
			{//�ړ�

				if (m_RunCnt == 0)
				{
					CManager* pManager = CManager::GetInstance();
					CSound* pSound = pManager->GetSound();
					//pSound->PlaySound(CSound::SOUND_LABEL_SE_RUN);
					m_RunCnt = 15;
				}
				else
				{
					m_RunCnt--;
				}
			}
		}

	Motion_Parent();
	Motion_Sub();


	m_oldMotionIndex_Parent = m_NowMotionIndex_Parent;
	m_oldMotionIndex_Sub = m_NowMotionIndex_Sub;

	//�����ŌÃf�[�^�X�V
	m_OldPosY = m_CrassData.Pos.y;
}

//=============================
// �`��
//=============================
void CObjectMotion::Draw()
{
	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();
	pRenderer = pManager->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();


	D3DXMATRIX mtxRot, mtxTrans, mtxParent;//�v�Z�p�}�g���b�N�X


	//�L�����S�̂̊(�e�̐e)
		//---------------------------------------------------------------------------------------------------�v���C���[�̈ʒu�̂�
	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_CrassData.rot.y, m_CrassData.rot.x, m_CrassData.rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_CrassData.Pos.x, m_CrassData.Pos.y, m_CrassData.Pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);


	
#if 1
	/*	for (int nCntPart = 0; nCntPart < m_Model.nMaxLoadPartsCnt; nCntPart++)
		{
			m_pModelParts[nCntPart]->Draw();
		}*/
#else
		D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p(�ꎞ�ޔ�)

	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCnt = 0; nCnt < m_Model.nMaxLoadPartsCnt; nCnt++)
	{
		D3DXMATRIX ESCMatrix = m_pModelParts[nCnt]->GetMtxWorld();

		//---------------------------------------------------------------------------------------------------���f���̈ʒu
		DATA ESCNOWDATA = m_pModelParts[nCnt]->GetNowData();


		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&ESCMatrix);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, ESCNOWDATA.rot.y, ESCNOWDATA.rot.x, ESCNOWDATA.rot.z);

		D3DXMatrixMultiply(&ESCMatrix, &ESCMatrix, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, ESCNOWDATA.Pos.x, ESCNOWDATA.Pos.y, ESCNOWDATA.Pos.z);

		D3DXMatrixMultiply(&ESCMatrix, &ESCMatrix, &mtxTrans);


		//�e�q�֌W
		if (m_pModelParts[nCnt]->GetParent() == nullptr)
		{
			//�v���C���[�Ƃ�����
			D3DXMatrixMultiply(&ESCMatrix, &ESCMatrix, &m_mtxWorld);
		}
		else
		{
			D3DXMATRIX ESCMatrixParent = m_pModelParts[nCnt]->GetParent()->GetMtxWorld();

			//�����̐e�̃}�g���b�N�X�����Ă�
			D3DXMatrixMultiply(&ESCMatrix, &ESCMatrix, &ESCMatrixParent);
		}

		m_pModelParts[nCnt]->SetPartsMtx(ESCMatrix);//�}�g���b�N�X�i�[

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &ESCMatrix);

		//���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)m_pBuffMat[nCnt]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_dwNumMat[nCnt]; nCntMat++)
		{

			bool g_test = false;

			//------------------------�J���[�`�F���W
			if (g_test == true)
			{
				// �}�e���A���̐ݒ�
				D3DMATERIAL9 matTemp = pMat[nCntMat].MatD3D;
				matTemp.Diffuse = D3DXCOLOR(1.0f, 0.1f, 0.1f, 0.8f);
				//matTemp.Diffuse.a = 0.5f;  // ���ߓx��ݒ�i0.0f�Ŋ��S�����A1.0f�ŕs�����j
				pDevice->SetMaterial(&matTemp);
			}
			else
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
			}

			//�e�N�X�`���̐ݒ�
			//pDevice->SetTexture(0, NULL);//����͐ݒ肵�Ȃ�
			//�e�N�X�`���̐ݒ�

			pDevice->SetTexture(0, m_pTexture[nCnt][nCntMat]);
			//���f��(�p�[�c)�̕`��
			m_pMesh[nCnt]->DrawSubset(nCntMat);

		}
	}
	//�ۑ����Ă��}�e���A����߂�
	pDevice->SetMaterial(&matDef);

	//�e�N�X�`����߂�
	pDevice->SetTexture(0, NULL);




#endif // 0

}

//=============================
// ����
//=============================
CObjectMotion* CObjectMotion::Create(const char* pfilePass, DATA SetData)
{
    CObjectMotion* pObstacle = new CObjectMotion;
   
    pObstacle->SetFilePass(pfilePass);//�p�X�i�[
    
    pObstacle->Init();

    // �擾
    DATA EscData = pObstacle->GetClassData();
	pObstacle->SetClassData(SetData);

    return pObstacle;
}


//=============================
// �f�[�^���[�h
//=============================
void CObjectMotion::DataLoad()
{

	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();
	pRenderer = pManager->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	FILE* pFile;//�t�@�C���|�C���^��錾


	char aString[MAX_WORD] = {};	//�ǂݍ��ލő啶����

	int nEscapeCntModel=0;//���f����

	int nfirstEscapePartsCnt=0;//�͂��߂Ɏg���p�[�c�J�E���g


	int nMotionCnt=0;//���[�V�����J�E���g
	
	int KeyCnt=0;//�L�[�J�E���g

	int nKeyPartsCnt=0;//�e�L�[�̒��ł̃p�[�c�J�E���g


	int EscapeIndex = 0;//��
	int EscapeParentIndex = 0;//�e�ԍ�

	DATA EscOffSetData;//
	DATA EscNowData;//

	int SetMotionCheck = 1;

	pFile = fopen(m_FilePass, "r");
	
	if (pFile != NULL)
	{//�t�@�C�����J������
		while (1)
		{
			fscanf(pFile, "%s", &aString[0]);

			if (strcmp(&aString[0], "END_SCRIPT") == 0)
			{//�Ō�ɂ�����
				fclose(pFile);
				break;
			}
			else if (strcmp(&aString[0], "NUM_MODEL") == 0)
			{//���f������������
				fscanf(pFile, "%s", &aString[0]);
				fscanf(pFile, "%d", &m_Model.nMaxLoadPartsCnt);//���f�����i�[

			}
			else if (strcmp(&aString[0], "MODEL_FILENAME") == 0)
			{//�e���f���̃p�[�c�̃p�X��������
				fscanf(pFile, "%s", &aString[0]);
				fscanf(pFile, "%s", &aString[0]);//�t�@�C���p�X


				char* filePass = new char[strlen(aString) + 1];//�������m��
				strcpy(filePass, aString);//�R�s�[

				m_PartfilePass[nEscapeCntModel] = filePass;

				nEscapeCntModel++;//���f���i�[��C���N��
			}
			else if (strcmp(&aString[0], "CHARACTERSET") == 0)
			{//�L�����Z�b�g��������
				while (1)
				{
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "END_CHARACTERSET") == 0)
					{
						//nCnt++;
						break;
					}
					else if (strcmp(&aString[0], "NUM_PARTS") == 0)
					{//Parts����������
						fscanf(pFile, "%s", &aString[0]);
						fscanf(pFile, "%d", &m_Model.nMaxPartsCnt);
					}
					else if (strcmp(&aString[0], "CHANGE_MODEL_INDEX") == 0)
					{//���f���f�[�^�ύX�̂��郂�f���̃C���f�b�N�X
						int nChangeIndex = 0;
						fscanf(pFile, "%s", &aString[0]);

						fscanf(pFile, "%d", &nChangeIndex);

						//Changebool��true��
						m_pModelParts[nChangeIndex]->m_DataChangeModel(true);
						m_ChangeDataModelIndex = nChangeIndex;
					}
					else if (strcmp(&aString[0], "PARTSSET") == 0)
					{//Parts�ݒ肪������
						while (1)
						{
							fscanf(pFile, "%s", &aString[0]);

							if (strcmp(&aString[0], "END_PARTSSET") == 0)
							{//Parts���G���h��������
								//�N���G�C�g
								m_pModelParts[nfirstEscapePartsCnt] = CModelParts::Create(m_PartfilePass[nfirstEscapePartsCnt],nfirstEscapePartsCnt);
								//�e�ݒ�
								m_pModelParts[nfirstEscapePartsCnt]->SetParent(m_pModelParts[EscapeParentIndex]);
								//�I�t�Z�b�g�i�[
								m_pModelParts[nfirstEscapePartsCnt]->SetOffSetData(EscOffSetData);
								//���s�f�[�^�i�[ 
								m_pModelParts[nfirstEscapePartsCnt]->SetNowData(EscNowData);
								m_pModelParts[nfirstEscapePartsCnt]->SetMotionPoint(this);
								m_pModelParts[nfirstEscapePartsCnt]->SetMotion_Parent(SetMotionCheck);
								nfirstEscapePartsCnt++;
								break;
							}
							else if (strcmp(&aString[0], "INDEX") == 0)
							{//�C���f�b�N�X��������
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%d", &EscapeIndex);

							}
							else if (strcmp(&aString[0], "PARENT") == 0)
							{//�e��������
								fscanf(pFile, "%s", &aString[0]);
								//fscanf(pFile, "%d", &m_Model.ModelParts[nfirstEscapePartsCnt].PEARENT);
								fscanf(pFile, "%d", &EscapeParentIndex);
								
							}
							else if (strcmp(&aString[0], "POS") == 0)
							{//POS��������
								fscanf(pFile, "%s", &aString[0]);

								//fscanf(pFile, "%f %f %f", &m_Model.ModelParts[nfirstEscapePartsCnt].Pos.x, &m_Model.ModelParts[nfirstEscapePartsCnt].Pos.y, &m_Model.ModelParts[nfirstEscapePartsCnt].Pos.z);

								////�ۑ�
								//m_Model.ModelParts[nfirstEscapePartsCnt].StartPos = m_Model.ModelParts[nfirstEscapePartsCnt].Pos;

								fscanf(pFile, "%f %f %f", &EscNowData.Pos.x, &EscNowData.Pos.y, &EscNowData.Pos.z);

								//�ۑ�
								EscOffSetData.Pos = EscNowData.Pos;

							}
							else if (strcmp(&aString[0], "ROT") == 0)
							{//ROT��������
								fscanf(pFile, "%s", &aString[0]);

								//fscanf(pFile, "%f %f %f", &m_Model.ModelParts[nfirstEscapePartsCnt].Rot.x, &m_Model.ModelParts[nfirstEscapePartsCnt].Rot.y, &m_Model.ModelParts[nfirstEscapePartsCnt].Rot.z);

								////�ۑ�
								//m_Model.ModelParts[nfirstEscapePartsCnt].StartRot = m_Model.ModelParts[nfirstEscapePartsCnt].Rot;
							
								fscanf(pFile, "%f %f %f", &EscNowData.rot.x, &EscNowData.rot.y, &EscNowData.rot.z);

								//�ۑ�
								EscOffSetData.rot = EscNowData.rot;
							}
							else if (strcmp(&aString[0], "MOTIONPARENT") == 0)
							{//ROT��������
								fscanf(pFile, "%s", &aString[0]);

								fscanf(pFile, "%d", &SetMotionCheck);

								//�ۑ�
								EscOffSetData.rot = EscNowData.rot;
							}
							
						}

					}					
					else if (strcmp(&aString[0], "CHANGE_MODEL_INDEX") == 0)
					{//���f���f�[�^�ύX�̂��郂�f���̃C���f�b�N�X
						int nChangeIndex = 0;
						fscanf(pFile, "%s", &aString[0]);

						fscanf(pFile, "%d", &nChangeIndex);

						//Changebool��true��
						m_pModelParts[nChangeIndex]->m_DataChangeModel(true);
						m_ChangeDataModelIndex = nChangeIndex;
					}

				}
			}
			else if (strcmp(&aString[0], "MOTIONSET") == 0)
			{//MOTION�Z�b�g��������
				while (1)
				{
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "END_MOTIONSET") == 0)
					{//�G���hMOTION�Z�b�g

						m_Model.Motion[nMotionCnt].Motiontype = nMotionCnt;
						nMotionCnt++;//���[�V�����C���N�������g

						if (m_Model.nMaxMotionCnt <= nMotionCnt)
						{
							m_Model.nMaxMotionCnt = nMotionCnt;//���[�V�������͍ő�̂�
						}

						KeyCnt = 0;//�L�[�ԍ����Z�b�g

						break;
					}
					else if (strcmp(&aString[0], "LOOP") == 0)
					{//���[�v����������
						fscanf(pFile, "%s", &aString[0]);
						fscanf(pFile, "%d", &m_Model.Motion[nMotionCnt].nLoop);
					}
					else if (strcmp(&aString[0], "NUM_KEY") == 0)//----------------�ő�L�[���ɉ��p
					{//�L�[�̐���������
						fscanf(pFile, "%s", &aString[0]);
						fscanf(pFile, "%d", &m_Model.Motion[nMotionCnt].nNumKey);
					}
					else if (strcmp(&aString[0], "KEYSET") == 0)
					{//KEY�Z�b�g��������
						while (1)
						{
							fscanf(pFile, "%s", &aString[0]);

							if (strcmp(&aString[0], "END_KEYSET") == 0)
							{//�G���hKEY�Z�b�g

								KeyCnt++;//�L�[�C���N�������g
								nKeyPartsCnt = 0;//�p�[�c�ԍ������Z�b�g
								break;

							}
							else if (strcmp(&aString[0], "FRAME") == 0)
							{//�t���[���̐���������
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%d", &m_Model.Motion[nMotionCnt].KeyData[KeyCnt].nSplitFrame);//-----------------------------------���L�Ɠ���//�킯�Ȃ��ƁA��΂��ꂽ�Ƃ��ɔF���ł��Ȃ�

							}
							else if (strcmp(&aString[0], "KEY") == 0)
							{//KEY��������

								while (1)
								{
									fscanf(pFile, "%s", &aString[0]);

									if (strcmp(&aString[0], "FRAME") == 0)
									{//�t���[���̐���������
										fscanf(pFile, "%s", &aString[0]);
										fscanf(pFile, "%d", &m_Model.Motion[nMotionCnt].KeyData[KeyCnt].nSplitFrame);///------------------------��L�Ɠ���

									}

									else if (strcmp(&aString[0], "END_KEY") == 0)
									{//�G���hKEY

										nKeyPartsCnt++;//�p�[�c�C���N�������g
										break;
									}
									else if (strcmp(&aString[0], "POS") == 0)
									{//POS����������
										fscanf(pFile, "%s", &aString[0]);
										fscanf(pFile, "%f %f %f", &m_Model.Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionPos.x, &m_Model.Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionPos.y, &m_Model.Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionPos.z);///------------------------Key���Ƃ��p�[�c���Ƃŕϓ�

									}
									else if (strcmp(&aString[0], "ROT") == 0)
									{//ROT����������
										fscanf(pFile, "%s", &aString[0]);
										fscanf(pFile, "%f %f %f", &m_Model.Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionRot.x, &m_Model.Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionRot.y, &m_Model.Motion[nMotionCnt].KeyData[KeyCnt].PartsData[nKeyPartsCnt].CorrectionRot.z);///------------------------Key���Ƃ��p�[�c���Ƃŕϓ�
									}
								}
							}
						}
					}
				}
			}
			else if(strcmp(&aString[0], "CHANGE_MODEL_INDEX") == 0)
			{//���f���f�[�^�ύX�̂��郂�f���̃C���f�b�N�X
			int nChangeIndex = 0;
			fscanf(pFile, "%s", &aString[0]);

			fscanf(pFile, "%d", &nChangeIndex);

			//Changebool��true��
			m_pModelParts[nChangeIndex]->m_DataChangeModel(true);
			m_ChangeDataModelIndex = nChangeIndex;
			}
		}
	}

}



//=============================
// pass�i�[
//=============================
void CObjectMotion::SetFilePass(const char* FilePass)
{
    char* filePass = new char[strlen(FilePass) + 1];//�������m��
    strcpy(filePass, FilePass);//�R�s�[

    m_FilePass = filePass;
}
//=============================
// MOTION�I�I�I�I
//=============================
void CObjectMotion::Motion_Parent()
{
	if (m_NowMotionIndex_Parent == 10)
	{
		int test = 0;
	}

	if (m_NowMotionIndex_Parent != m_oldMotionIndex_Parent)
	{//�O��̃��[�V�����ƈႤ��
	//-------------------------------���Z�b�g����
		m_NowKeyCnt_Parent = 0;
		m_NowFrameCnt_Parent = 0;
		m_EscapeMotion_Parent = m_NowMotionIndex_Parent;
		m_BrendCnt_Parent = 0;
		for (int i = 0; i < m_Model.nMaxLoadPartsCnt; i++)
		{//���Z�b�g

			if (m_pModelParts[i]->GetMotion_Parent() == 1)
			{//parent���̎�
				m_pModelParts[i]->SetcalculationExecution(false);
				m_pModelParts[i]->SetCorrectCorrectionPosMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_pModelParts[i]->SetCorrectCorrectionRotMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_MotionLoopStop_Parent = false;
			}
		}
		if (m_NowMotionIndex_Parent == MOTIONTYPE_ATTACK|| m_NowMotionIndex_Parent == MOTIONTYPE_OP0 || m_NowMotionIndex_Parent == MOTIONTYPE_OP1 || m_NowMotionIndex_Parent == MOTIONTYPE_OP2 || m_NowMotionIndex_Parent == MOTIONTYPE_OP3)
		{

		}
		else
		{
			m_MotionBrend_Parent = true;
		}
	}


#if 0
	

#else // 1
	if (m_MotionBrend_Parent == true)
	{//���[�V�����u�����h

		if (m_BrendCnt_Parent < BRENDFLAME)
		{
			for (int nCnt = 0; nCnt < m_Model.nMaxLoadPartsCnt; nCnt++)
			{//�p�[�c�����
				
				if (m_pModelParts[nCnt]->GetMotion_Parent() == 1)
				{//parent���̎�

					DATA EscOffSetDATA = m_pModelParts[nCnt]->GetOffSetData();//�I�t�Z�b�g�擾
					DATA EscNowDATA = m_pModelParts[nCnt]->GetNowData();//���s�擾

						//ROT�n
					if (m_pModelParts[nCnt]->GetcalculationExecution() == false)
					{
						//CorrectionPos,CorrectionRot�͂����܂ŁAOFFSET��Start�n�_�Ƃ����␳�ʂȂ̂ŁA
						D3DXVECTOR3 TargetRot;
						TargetRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


						TargetRot = EscOffSetDATA.rot + m_Model.Motion[m_NowMotionIndex_Parent].KeyData[1].PartsData[nCnt].CorrectionRot;

						m_pModelParts[nCnt]->SetCorrectCorrectionRotMove(CMathProc::ConversionXfireRot3(TargetRot - EscNowDATA.rot) / BRENDFLAME);

						m_pModelParts[nCnt]->SetcalculationExecution(true);
					}
					m_pModelParts[nCnt]->UpdateRotMotion();


					//POS�n
					//--------------------------------------------------------------------------------
					if (m_pModelParts[nCnt]->GetParent() == nullptr)
					{//���������ׂĂ̐e�̎�
						D3DXVECTOR3 TargetPos;
						TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

						//�����ʒu���猩���n�_��␳�����A�ڕW�n�_�̎Z�o
						TargetPos = EscOffSetDATA.Pos + m_Model.Motion[m_NowMotionIndex_Parent].KeyData[1].PartsData[nCnt].CorrectionPos;

						//���݂̈ʒu����A��ŎZ�o�����ڕW�n�_�܂ł̍����v�Z
						m_pModelParts[nCnt]->SetCorrectCorrectionPosMove((TargetPos - EscNowDATA.Pos) / BRENDFLAME);

						//POS�̍X�V
						m_pModelParts[nCnt]->UpdatePosMotion();
						//------------------------------------------------------------------------------------
					}
				}
			}

		}
		m_BrendCnt_Parent++;

		if (m_BrendCnt_Parent >= BRENDFLAME)
		{
			m_BrendCnt_Parent = 0;

			m_MotionBrend_Parent = false;

			m_NowKeyCnt_Parent++;//�L�[��i�߂�

			for (int nCnt = 0; nCnt < m_Model.nMaxLoadPartsCnt; nCnt++)
			{//�p�[�c�����
				if (m_pModelParts[nCnt]->GetMotion_Parent() == 1)
				{//parent���̎�
					m_pModelParts[nCnt]->SetcalculationExecution(false);
					m_pModelParts[nCnt]->SetCorrectCorrectionPosMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					m_pModelParts[nCnt]->SetCorrectCorrectionRotMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}
			}
		}

	}
	else
	{

		if (m_NowMotionIndex_Parent == 2)
		{
			int test = 0;
		}

		// �{����------------------------------------------------------------------------------------------------------------------
		if (m_MotionLoopStop_Parent == false)
		{
			if (m_NowFrameCnt_Parent < m_Model.Motion[m_NowMotionIndex_Parent].KeyData[m_NowKeyCnt_Parent /*- 1*/].nSplitFrame)
			{//�����t���[���̕����
				if (m_NowKeyCnt_Parent < m_Model.Motion[m_NowMotionIndex_Parent].nNumKey)
				{//�L�[�̕����

					for (int nCnt = 0; nCnt < m_Model.nMaxLoadPartsCnt; nCnt++)
					{//�p�[�c�����
						if (m_pModelParts[nCnt]->GetMotion_Parent() == 1)
						{//parent���̎�
							DATA EscOffSetDATA = m_pModelParts[nCnt]->GetOffSetData();//�I�t�Z�b�g�擾
							DATA EscNowDATA = m_pModelParts[nCnt]->GetNowData();//���s�擾

								//ROT�n
							if (m_pModelParts[nCnt]->GetcalculationExecution() == false)
							{
								//CorrectionPos,CorrectionRot�͂����܂ŁAOFFSET��Start�n�_�Ƃ����␳�ʂȂ̂ŁA
								D3DXVECTOR3 TargetRot;
								TargetRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

								if (m_NowKeyCnt_Parent != m_Model.Motion[m_NowMotionIndex_Parent].nNumKey - 1)
								{//�Ō�L�[����Ȃ�
									TargetRot = EscOffSetDATA.rot + m_Model.Motion[m_NowMotionIndex_Parent].KeyData[m_NowKeyCnt_Parent + 1].PartsData[nCnt].CorrectionRot;
								}
								else if (m_NowKeyCnt_Parent == m_Model.Motion[m_NowMotionIndex_Parent].nNumKey - 1)
								{//�Ō�L�[�̂Ƃ�
									TargetRot = EscOffSetDATA.rot + m_Model.Motion[m_NowMotionIndex_Parent].KeyData[0].PartsData[nCnt].CorrectionRot;
								}
								m_pModelParts[nCnt]->SetCorrectCorrectionRotMove((CMathProc::ConversionXfireRot3(TargetRot - EscNowDATA.rot)) / (float)m_Model.Motion[m_NowMotionIndex_Parent].KeyData[m_NowKeyCnt_Parent].nSplitFrame);

								m_pModelParts[nCnt]->SetcalculationExecution(true);
							}
							m_pModelParts[nCnt]->UpdateRotMotion();

							//POS�n
							//--------------------------------------------------------------------------------
							if (m_pModelParts[nCnt]->GetParent() == nullptr)
							{//���������ׂĂ̐e�̎�
								D3DXVECTOR3 TargetPos;
								TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
								if (m_NowKeyCnt_Parent != m_Model.Motion[m_NowMotionIndex_Parent].nNumKey - 1)
								{//�Ō�L�[����Ȃ�
								//�����ʒu���猩���n�_��␳�����A�ڕW�n�_�̎Z�o
									TargetPos = EscOffSetDATA.Pos + m_Model.Motion[m_NowMotionIndex_Parent].KeyData[m_NowKeyCnt_Parent + 1].PartsData[nCnt].CorrectionPos;
								}
								else if (m_NowKeyCnt_Parent == m_Model.Motion[m_NowMotionIndex_Parent].nNumKey - 1)
								{//�Ō�L�[�̂Ƃ�
								//�����ʒu���猩���n�_��␳�����A�ڕW�n�_�̎Z�o
									TargetPos = EscOffSetDATA.Pos + m_Model.Motion[m_NowMotionIndex_Parent].KeyData[0].PartsData[nCnt].CorrectionPos;
								}
								//���݂̈ʒu����A��ŎZ�o�����ڕW�n�_�܂ł̍����v�Z
								m_pModelParts[nCnt]->SetCorrectCorrectionPosMove((TargetPos - EscNowDATA.Pos) / (float)m_Model.Motion[m_NowMotionIndex_Parent].KeyData[m_NowKeyCnt_Parent].nSplitFrame);

								//POS�̍X�V
								m_pModelParts[nCnt]->UpdatePosMotion();
								//------------------------------------------------------------------------------------
							}
						}
					}
				}
				m_NowFrameCnt_Parent++;//�t���[���i�߂�
			}
			else
			{//�t���[����������
				m_NowFrameCnt_Parent = 0;//�t���[�����Z�b�g

				m_NowKeyCnt_Parent++;//�L�[��i�߂�

				for (int i = 0; i < m_Model.nMaxLoadPartsCnt; i++)
				{//���Z�b�g
					if (m_pModelParts[i]->GetMotion_Parent() == 1)
					{//parent���̎�
						m_pModelParts[i]->SetcalculationExecution(false);
					}
				}

				if (m_NowKeyCnt_Parent == m_Model.Motion[m_NowMotionIndex_Parent].nNumKey)
				{//�L�[���A�ő�L�[�𒴂�����

					m_NowFrameCnt_Parent = 0;//�t���[�����Z�b�g
					m_NowKeyCnt_Parent = 0;//�L�[���Z�b�g

					if (m_Model.Motion[m_NowMotionIndex_Parent].nLoop == 0)
					{//���[�v���Ȃ�
						if (m_NowMotionIndex_Parent == 3)
						{
							m_MotionLoopStop_Parent = true;
						}
						else
						{//���ĈȊO
							//�ҋ@�ɂ���
							m_NowMotionIndex_Parent = MOTIONTYPE_STANDBY;//�ҋ@��Ԃɖ߂�
							//�u�����h����
							if (m_MotionBrend_Parent == false)
							{
								m_NowKeyCnt_Parent = 0;
								m_NowFrameCnt_Parent = 0;
								m_EscapeMotion_Parent = m_NowMotionIndex_Parent;
								m_BrendCnt_Parent = 0;
								for (int i = 0; i < m_Model.nMaxLoadPartsCnt; i++)
								{//���Z�b�g
									if (m_pModelParts[i]->GetMotion_Parent() == 1)
									{//parent���̎�
										m_pModelParts[i]->SetcalculationExecution(false);
										m_pModelParts[i]->SetCorrectCorrectionPosMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
										m_pModelParts[i]->SetCorrectCorrectionRotMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
										m_MotionLoopStop_Parent = false;

										m_MotionBrend_Parent = true;
									}
								}
							}
						}
					}
					else
					{//���[�v

					}

				}
			}
		}

	}
#endif
	
}


//=============================
// MOTION�I�I�I�ISub
//=============================
void CObjectMotion::Motion_Sub()
{
	if (m_NowMotionIndex_Sub == MOTIONTYPE_ATTACK)
	{
		m_MotionBrend_Sub = false;
	}

	if (m_NowMotionIndex_Sub == 2)
	{
		int test = 0;
	}

	if (m_NowMotionIndex_Sub != m_oldMotionIndex_Sub)
	{//�O��̃��[�V�����ƈႤ��
	//-------------------------------���Z�b�g����
		m_NowKeyCnt_Sub = 0;
		m_NowFrameCnt_Sub = 0;
		m_EscapeMotion_Sub = m_NowMotionIndex_Sub;
		m_BrendCnt_Sub = 0;
		for (int i = 0; i < m_Model.nMaxLoadPartsCnt; i++)
		{//���Z�b�g
			if (m_pModelParts[i]->GetMotion_Parent() == 0)
			{//Sub���̎�
				m_pModelParts[i]->SetcalculationExecution(false);
				m_pModelParts[i]->SetCorrectCorrectionPosMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_pModelParts[i]->SetCorrectCorrectionRotMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_MotionLoopStop_Sub = false;
			}
		}
		
		if (m_NowMotionIndex_Sub == MOTIONTYPE_ATTACK)
		{

		}
		else
		{
			m_MotionBrend_Sub = true;
		}
	}


#if 0


#else // 1
	if (m_MotionBrend_Sub == true)
	{//���[�V�����u�����h

		if (m_BrendCnt_Sub < BRENDFLAME)
		{
			for (int nCnt = 0; nCnt < m_Model.nMaxLoadPartsCnt; nCnt++)
			{//�p�[�c�����
				if (m_pModelParts[nCnt]->GetMotion_Parent() == 0)
				{//Sub���̎�
					DATA EscOffSetDATA = m_pModelParts[nCnt]->GetOffSetData();//�I�t�Z�b�g�擾
					DATA EscNowDATA = m_pModelParts[nCnt]->GetNowData();//���s�擾

						//ROT�n
					if (m_pModelParts[nCnt]->GetcalculationExecution() == false)
					{
						D3DXVECTOR3 TargetRot;
						TargetRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

						TargetRot = EscOffSetDATA.rot + m_Model.Motion[m_NowMotionIndex_Sub].KeyData[1].PartsData[nCnt].CorrectionRot;

						m_pModelParts[nCnt]->SetCorrectCorrectionRotMove(CMathProc::ConversionXfireRot3(TargetRot - EscNowDATA.rot) / BRENDFLAME);

						m_pModelParts[nCnt]->SetcalculationExecution(true);
					}
					m_pModelParts[nCnt]->UpdateRotMotion();


					//POS�n
					//--------------------------------------------------------------------------------
					if (m_pModelParts[nCnt]->GetParent() == nullptr)
					{//���������ׂĂ̐e�̎�
						D3DXVECTOR3 TargetPos;
						TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

						//�����ʒu���猩���n�_��␳�����A�ڕW�n�_�̎Z�o
						TargetPos = EscOffSetDATA.Pos + m_Model.Motion[m_NowMotionIndex_Sub].KeyData[1].PartsData[nCnt].CorrectionPos;

						//���݂̈ʒu����A��ŎZ�o�����ڕW�n�_�܂ł̍����v�Z
						m_pModelParts[nCnt]->SetCorrectCorrectionPosMove((TargetPos - EscNowDATA.Pos) / BRENDFLAME);

						//POS�̍X�V
						m_pModelParts[nCnt]->UpdatePosMotion();
						//------------------------------------------------------------------------------------
					}
				}
			}

		}
		m_BrendCnt_Sub++;

		if (m_BrendCnt_Sub >= BRENDFLAME)
		{
			m_BrendCnt_Sub = 0;

			m_MotionBrend_Sub = false;

			m_NowKeyCnt_Sub++;//�L�[��i�߂�

			for (int nCnt = 0; nCnt < m_Model.nMaxLoadPartsCnt; nCnt++)
			{//�p�[�c�����
				if (m_pModelParts[nCnt]->GetMotion_Parent() == 0)
				{//Sub���̎�
					m_pModelParts[nCnt]->SetcalculationExecution(false);
					m_pModelParts[nCnt]->SetCorrectCorrectionPosMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					m_pModelParts[nCnt]->SetCorrectCorrectionRotMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}
			}
		}
	}
	else
	{

		if (m_NowMotionIndex_Sub == 2)
		{
			int test = 0;
		}

		// �{����------------------------------------------------------------------------------------------------------------------
		if (m_MotionLoopStop_Sub == false)
		{
			if (m_NowFrameCnt_Sub < m_Model.Motion[m_NowMotionIndex_Sub].KeyData[m_NowKeyCnt_Sub /*- 1*/].nSplitFrame)
			{//�����t���[���̕����
				if (m_NowKeyCnt_Sub < m_Model.Motion[m_NowMotionIndex_Sub].nNumKey)
				{//�L�[�̕����
					for (int nCnt = 0; nCnt < m_Model.nMaxLoadPartsCnt; nCnt++)
					{//�p�[�c�����
						if (m_pModelParts[nCnt]->GetMotion_Parent() == 0)
						{//Sub���̎�
							DATA EscOffSetDATA = m_pModelParts[nCnt]->GetOffSetData();//�I�t�Z�b�g�擾
							DATA EscNowDATA = m_pModelParts[nCnt]->GetNowData();//���s�擾

								//ROT�n
							if (m_pModelParts[nCnt]->GetcalculationExecution() == false)
							{
								//CorrectionPos,CorrectionRot�͂����܂ŁAOFFSET��Start�n�_�Ƃ����␳�ʂȂ̂ŁA
								D3DXVECTOR3 TargetRot;
								TargetRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

								if (m_NowKeyCnt_Sub != m_Model.Motion[m_NowMotionIndex_Sub].nNumKey - 1)
								{//�Ō�L�[����Ȃ�
									TargetRot = EscOffSetDATA.rot + m_Model.Motion[m_NowMotionIndex_Sub].KeyData[m_NowKeyCnt_Sub + 1].PartsData[nCnt].CorrectionRot;
								}
								else if (m_NowKeyCnt_Sub == m_Model.Motion[m_NowMotionIndex_Sub].nNumKey - 1)
								{//�Ō�L�[�̂Ƃ�
									TargetRot = EscOffSetDATA.rot + m_Model.Motion[m_NowMotionIndex_Sub].KeyData[0].PartsData[nCnt].CorrectionRot;
								}
								m_pModelParts[nCnt]->SetCorrectCorrectionRotMove((CMathProc::ConversionXfireRot3(TargetRot - EscNowDATA.rot)) / (float)m_Model.Motion[m_NowMotionIndex_Sub].KeyData[m_NowKeyCnt_Sub].nSplitFrame);

								m_pModelParts[nCnt]->SetcalculationExecution(true);
							}
							m_pModelParts[nCnt]->UpdateRotMotion();

							//POS�n
							//--------------------------------------------------------------------------------
							if (m_pModelParts[nCnt]->GetParent() == nullptr)
							{//���������ׂĂ̐e�̎�
								D3DXVECTOR3 TargetPos;
								TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
								if (m_NowKeyCnt_Sub != m_Model.Motion[m_NowMotionIndex_Sub].nNumKey - 1)
								{//�Ō�L�[����Ȃ�
								//�����ʒu���猩���n�_��␳�����A�ڕW�n�_�̎Z�o
									TargetPos = EscOffSetDATA.Pos + m_Model.Motion[m_NowMotionIndex_Sub].KeyData[m_NowKeyCnt_Sub + 1].PartsData[nCnt].CorrectionPos;
								}
								else if (m_NowKeyCnt_Sub == m_Model.Motion[m_NowMotionIndex_Sub].nNumKey - 1)
								{//�Ō�L�[�̂Ƃ�
								//�����ʒu���猩���n�_��␳�����A�ڕW�n�_�̎Z�o
									TargetPos = EscOffSetDATA.Pos + m_Model.Motion[m_NowMotionIndex_Sub].KeyData[0].PartsData[nCnt].CorrectionPos;
								}
								//���݂̈ʒu����A��ŎZ�o�����ڕW�n�_�܂ł̍����v�Z
								m_pModelParts[nCnt]->SetCorrectCorrectionPosMove((TargetPos - EscNowDATA.Pos) / (float)m_Model.Motion[m_NowMotionIndex_Sub].KeyData[m_NowKeyCnt_Sub].nSplitFrame);

								//POS�̍X�V
								m_pModelParts[nCnt]->UpdatePosMotion();
								//------------------------------------------------------------------------------------
							}
						}
					}
				}
				m_NowFrameCnt_Sub++;//�t���[���i�߂�
			}
			else
			{//�t���[����������
				m_NowFrameCnt_Sub = 0;//�t���[�����Z�b�g


				m_NowKeyCnt_Sub++;//�L�[��i�߂�

				for (int i = 0; i < m_Model.nMaxLoadPartsCnt; i++)
				{//���Z�b�g
					if (m_pModelParts[i]->GetMotion_Parent() == 0)
					{//Sub���̎�
						m_pModelParts[i]->SetcalculationExecution(false);
					}
				}

				if (m_NowKeyCnt_Sub == m_Model.Motion[m_NowMotionIndex_Sub].nNumKey)
				{//�L�[���A�ő�L�[�𒴂�����

					m_NowFrameCnt_Sub = 0;//�t���[�����Z�b�g
					m_NowKeyCnt_Sub = 0;//�L�[���Z�b�g

					if (m_Model.Motion[m_NowMotionIndex_Sub].nLoop == 0)
					{//���[�v���Ȃ�
						if (m_NowMotionIndex_Sub == 3)
						{
							m_MotionLoopStop_Sub = true;
						}
						else
						{//���ĈȊO
							//�ҋ@�ɂ���
							m_NowMotionIndex_Sub = MOTIONTYPE_STANDBY;//�ҋ@��Ԃɖ߂�
							//�u�����h����
							if (m_MotionBrend_Sub == false)
							{
								m_NowKeyCnt_Sub = 0;
								m_NowFrameCnt_Sub = 0;
								m_EscapeMotion_Sub = m_NowMotionIndex_Sub;
								m_BrendCnt_Sub = 0;
								for (int i = 0; i < m_Model.nMaxLoadPartsCnt; i++)
								{//���Z�b�g
									if (m_pModelParts[i]->GetMotion_Parent() == 0)
									{//Sub���̎�
										m_pModelParts[i]->SetcalculationExecution(false);
										m_pModelParts[i]->SetCorrectCorrectionPosMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
										m_pModelParts[i]->SetCorrectCorrectionRotMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
										m_MotionLoopStop_Sub = false;

										m_MotionBrend_Sub = true;
									}

								}
							}
						}
					}
					else
					{//���[�v

					}

				}
			}
		}

	}
#endif

}



//=============================
// ���[�V�����ԍ��Z�b�g
//=============================
void CObjectMotion::SetNowMotion_Parent(MOTIONTYPE nMotionNum)
{
	m_NowMotionIndex_Parent = nMotionNum;
}
//=============================
// ���[�V�����ԍ��Z�b�g�T�u
//=============================
void CObjectMotion::SetNowMotion_Sub(MOTIONTYPE nMotionNum)
{
	m_NowMotionIndex_Sub = nMotionNum;
}


//=============================
// �S�̂Ƃ��Ẵf�[�^�ݒ�
//=============================
void CObjectMotion::SetClassData(DATA data)
{
	m_CrassData = data;
}
//=============================
// �S�̂Ƃ��Ẵf�[�^�擾
//=============================
CObjectMotion::DATA CObjectMotion::GetClassData()
{
	return m_CrassData;//�Ȃ��������Ŏ~�܂�
}
//=============================
//�}�g���b�N�X�擾
//=============================
D3DXMATRIX CObjectMotion::GetMatrix()
{
	return m_mtxWorld;
}
//=============================
// �}�g���b�N�X�ݒ�
//=============================
void CObjectMotion::SetMatrix(D3DXMATRIX mtx)
{
	m_mtxWorld = mtx;
}
//=============================
// �f�[�^�ύX���胂�f���ւ̕ύX�f�[�^�i�[
//=============================
void CObjectMotion::SetChangeDataInObjectMotion(DATA ChangeData)
{
	
	m_pModelParts[m_ChangeDataModelIndex]->ChangeDataSet(ChangeData);

}
//=============================
// �p�[�c�擾
//=============================
CModelParts* CObjectMotion::GetModelParts(int index)
{
	return m_pModelParts[index];
}
//=============================
// �p�[�c���擾
//=============================
int CObjectMotion::GetMaxLoadPartsNum()
{
	return m_Model.nMaxLoadPartsCnt;
}

//=============================
// �f�[�^�ύX���胂�f���̃C���f�b�N�X
//=============================
int CObjectMotion::GetChangeDataPartsIndex()
{
	return m_ChangeDataModelIndex;
}
//=============================
//OBB�T�C�Y�����̂�
//=============================
void CObjectMotion::SetOBBLength(float fLength[3])
{
	m_Obb.m_fLength[0] = fLength[0];
	m_Obb.m_fLength[1] = fLength[1];
	m_Obb.m_fLength[2] = fLength[2];
}
//=============================
// OBB�擾
//=============================
COBB CObjectMotion::GetOBB()
{
	return m_Obb;
}
//=============================
// GRID�ԍ��擾
//=============================
int CObjectMotion::GetNowGRIDNum()
{
	return m_NowGridNum;
}
//=============================
// ���@�����Q���Ȃǂւ̓����蔻��(player/enemy����)
//=============================
void CObjectMotion::HitCollisionToStageBlock()
{

	//�擾
	DATA EscData = GetClassData();
	
	////�����蔻��v�Z
	//m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_MOTIONMODEL, EscData.Pos, EscData.OldPos, EscData.MinLength, EscData.MaxLength, OBJECT_HITBOX, LAYERINDEX_HITBOX, EscData.move);


	//if (m_HitData.bHit == true)
	//{//�ڐG
	//	
	//	if (m_HitData.HitAngle.x == 1)
	//	{//+x
	//		EscData.Pos.x += m_HitData.ResultDistance.x;

	//		EscData.move.x = 0.0f;
	//	}
	//	else if (m_HitData.HitAngle.x == -1)
	//	{//-x

	//		EscData.Pos.x -= m_HitData.ResultDistance.x;
	//		EscData.move.x = 0.0f;
	//	}
	//	else if (m_HitData.HitAngle.y == 1)
	//	{//+y
	//		EscData.Pos.y += m_HitData.ResultDistance.y;

	//		EscData.move.y = 0.0f;
	//	}
	//	else if (m_HitData.HitAngle.y == -1)
	//	{//-y
	//		EscData.Pos.y -= m_HitData.ResultDistance.y;
	//		EscData.move.y = 0.0f;
	//	}
	//	else if (m_HitData.HitAngle.z == 1)
	//	{//+z
	//		EscData.Pos.z += m_HitData.ResultDistance.z;

	//		EscData.move.z = 0.0f;
	//	}
	//	else if (m_HitData.HitAngle.z == -1)
	//	{//-z
	//		EscData.Pos.z -= m_HitData.ResultDistance.z;
	//		EscData.move.z = 0.0f;
	//	}
	//}


	SetClassData(EscData);//�i�[
}



////=============================
////
////=============================
//
//int CObjectMotion::GetGroundFrame()
//{
//	return m_groundCounter;
//}
////=============================
//
////=============================
//
//void CObjectMotion::SetGroundFrame(int cnt)
//{
//	m_groundCounter += cnt;
//}


