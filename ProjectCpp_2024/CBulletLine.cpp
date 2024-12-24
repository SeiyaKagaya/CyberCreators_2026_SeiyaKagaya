//=========================================================
//
// CBulletLine[CBulletLine.cpp]
// Author seiya kagaya
//
//=========================================================
#include"CBulletLine.h"



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

    m_Obb.m_fLength[0] = 160.0f;
    m_Obb.m_fLength[1] = 160.0f;
    m_Obb.m_fLength[2] = 50.0f;

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
}
