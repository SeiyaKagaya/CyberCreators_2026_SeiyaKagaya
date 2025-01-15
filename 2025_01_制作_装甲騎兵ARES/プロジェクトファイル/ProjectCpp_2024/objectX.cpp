//=======================================================
//
// objectX�Ɋւ��鏈��[objectX.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "objectX.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "all_texture.h"
#include <stdio.h>

//=============================
// �R���X�g���N�^
//=============================
CObjectX::CObjectX(int nPriority) :CObject(nPriority)
{
    m_Data.Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.OldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.MinLength = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.MaxLength = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.Radius = 0.0f;


    for (int i = 0; i < MAX_MAT; i++)
    {
        m_bFast[i] = false;

        m_OriginalColor[i] = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
    }

    m_pMesh = nullptr;
    m_pBuffMat = nullptr;
    m_dwNumMat = 0;

    m_SizeMag = D3DXVECTOR3(1.0f, 1.0f, 1.0f);//�{���i�[(1.0������)
    m_ChangeCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

 //   m_bMagChange = true;//�{���ϓ�
    

#if 0
    for (int nCnt = 0; nCnt < MAX_TEXTURE_XFILE; nCnt++)
    {
        m_pTexture[nCnt] = new LPDIRECT3DTEXTURE9();

        if (*m_pTexture[nCnt] != nullptr)
        {
            *m_pTexture[nCnt] = nullptr;
        }
    }
#else
    for (int nCnt = 0; nCnt < MAX_TEXTURE_XFILE; nCnt++)
    {
        if (m_pTexture[nCnt] != nullptr)
        {
            m_pTexture[nCnt] = nullptr;
        }
    }
#endif

    m_bModelParts = false;
}
//=============================
// �f�X�g���N�^
//=============================
CObjectX::~CObjectX()
{
#if 0
    // �e�N�X�`���̔j��
    for (int nCnt = 0; nCnt < MAX_TEXTURE_XFILE; nCnt++)
    {
        if (m_pTexture[nCnt] != nullptr)
        {
            delete m_pTexture[nCnt];
            m_pTexture[nCnt] = nullptr;
        }
    }
#else
    // �e�N�X�`���̔j��
    for (int nCnt = 0; nCnt < MAX_TEXTURE_XFILE; nCnt++)
    {
        if (m_pTexture[nCnt] != nullptr)
        {
            m_pTexture[nCnt]->Release();
            m_pTexture[nCnt] = nullptr; // ������ nullptr ��ݒ�
        }
    }
#endif
    Uninit();
}
//=============================
// �����ݒ�(���_�o�b�t�@����)
//=============================
HRESULT CObjectX::Init()
{



    SetObjectType(CObject::OBJECT_OBJECT3D);

    return S_OK;
}
//=============================
// �I������(���_�o�b�t�@�j��)
//=============================
void CObjectX::Uninit()
{
    //���b�V���̔j��
    if (m_pMesh != nullptr)
    {
        m_pMesh->Release();
        m_pMesh = nullptr;
    }
    //�}�e���A���̔j��
    if (m_pBuffMat != nullptr)
    {
        m_pBuffMat->Release();
        m_pBuffMat = nullptr;
    }

#if 1
    // �e�N�X�`���̔j��
    for (int nCnt = 0; nCnt < MAX_TEXTURE_XFILE; nCnt++)
    {
        if (m_pTexture[nCnt] != nullptr)
        {
            m_pTexture[nCnt]->Release();
            m_pTexture[nCnt] = nullptr; // ������ nullptr ��ݒ�
        }
    }
#endif

   // CObject::Uninit;
}
//=============================
// �X�V(���_���̍X�V)
//=============================
void CObjectX::Update()
{

}
//=============================
// �`�揈��(POLYGON�`��)
//=============================
void CObjectX::Draw()
{
    CRenderer* pRenderer = nullptr;
    CManager* pManager = CManager::GetInstance();
    pRenderer = pManager->GetRenderer();
    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();
    D3DXMATRIX mtxRot, mtxTrans;


    // ���[���h�}�g���b�N�X�̏�����
    D3DXMatrixIdentity(&m_mtxWorld);

    if (m_bModelParts == false)
    {//���ʂ̃��f���̂Ƃ�

        if (m_bMagChange == true)
        {
            // ���f���̃T�C�Y��ύX
            D3DXMatrixScaling(&m_mtxWorld, m_SizeMag.x, m_SizeMag.y, m_SizeMag.z);
        }

        // �����𔽉f
        D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Data.rot.y, m_Data.rot.x, m_Data.rot.z);
        D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

        // �ʒu�𔽉f
        D3DXMatrixTranslation(&mtxTrans, m_Data.Pos.x, m_Data.Pos.y, m_Data.Pos.z);
        D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
    }
    else
    {//���f���p�[�`�̂Ƃ�
        m_mtxWorld = m_ModelmtxWorld;
    }

    D3DMATERIAL9 matDef;
    D3DXMATERIAL* pMat;

    // ���[���h�}�g���b�N�X�̐ݒ�
    EscDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
    // ���_�t�H�[�}�b�g�̐ݒ�
    EscDevice->SetFVF(FVF_VERTEX_3D);
    // ���݂̃}�e���A�����擾
    EscDevice->GetMaterial(&matDef);

    if (GetNotLight() == true)
    {
        // ���C�g�𖳌��ɂ���
        EscDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
    }

    // �ʏ�̃I�u�W�F�N�g�̕`��
    if (m_pBuffMat != nullptr)
    {
        pMat = reinterpret_cast<D3DXMATERIAL*>(m_pBuffMat->GetBufferPointer());

        for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
        {
            if (m_bFast[nCntMat] == false)
            {
                m_bFast[nCntMat] = true;
                m_OriginalColor[nCntMat]= pMat[nCntMat].MatD3D.Diffuse;
            }

            // �}�e���A���̐ݒ�
            if (m_bMagChange == true)
            {
                D3DXCOLOR originalColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

                if (m_ChangeColorBool == true)
                {
                    originalColor = m_ChangeCol;
                }
                else
                {
                    originalColor = m_OriginalColor[nCntMat];
                }

                if (m_bStageTexChange == true)
                {
                    pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(200.0f, 200.0f, 200.0f, 200.0f);
                }
                else
                {
                    pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(
                        originalColor.r * m_SizeMag.x,
                        originalColor.g * m_SizeMag.y,
                        originalColor.b * m_SizeMag.z,
                        originalColor.a
                    );
                }

                EscDevice->SetMaterial(&pMat[nCntMat].MatD3D);
            }
            else
            {
                D3DXCOLOR originalColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

                if (m_ChangeColorBool == true)
                {
                    originalColor = m_ChangeCol;
                }
                else
                {
                    originalColor = m_OriginalColor[nCntMat];
                }

                pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(
                    originalColor.r,
                    originalColor.g,
                    originalColor.b,
                    originalColor.a);


                // �ʏ�̐F�ݒ�
                EscDevice->SetMaterial(&pMat[nCntMat].MatD3D);
            }

            // �e�N�X�`���̐ݒ�
            if (pMat[nCntMat].pTextureFilename != nullptr)
            {
           
                EscDevice->SetTexture(0, m_pTexture[nCntMat]);
//                EscDevice->SetTexture(0, nullptr);
            }
            else
            {
                EscDevice->SetTexture(0, nullptr);
            }

            // ���b�V���̕`��
            m_pMesh->DrawSubset(nCntMat);

            // �ۑ����Ă����}�e���A����߂�
            EscDevice->SetMaterial(&matDef);

            //���Z�b�g
             pMat[nCntMat].MatD3D.Diffuse = m_OriginalColor[nCntMat];
        }
    }

    if (GetNotLight() == true)
    {
        // ���C�g��L���ɂ���
        EscDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
        SetNotLight(false);
    }
}
//=============================
// Object����
//=============================
CObjectX* CObjectX::Create()
{
    CObjectX* pObjectX = new CObjectX;
    pObjectX->Init();
    return pObjectX;
}
//=============================
// �f�[�^�i�[
//=============================
void CObjectX::SetXfireData(LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD dwNumMat)
{
    
    m_pMesh = pMesh;//Mesh�|�C���^
     m_pBuffMat = pBuffMat;//�}�e���A
     m_dwNumMat = dwNumMat;//�}�e���A���̐�

}
//=============================
// �T�C�Y�ϓ��̗L��
//=============================
void CObjectX::SizeMagChangebool(bool bChange)
{
    m_bMagChange = bChange;
}
//=============================
// �`�揈��(POLYGON�`��)
//=============================
void CObjectX::SetSizeMag(D3DXVECTOR3 SizeMag)
{
    m_SizeMag = SizeMag;
}

D3DXVECTOR3 CObjectX::GetSizeMag()
{
    return m_SizeMag;
}

//=============================
// ��b���擾
//=============================
CObjectX::DATA CObjectX::GetDATA()
{
    return m_Data;
}
//=============================
// �e�N�X�`���i�[
//=============================
void CObjectX::BindTexture(LPDIRECT3DTEXTURE9 pTex, int Index)
{
    m_pTexture[Index] = pTex;
}
void CObjectX::ChangeModelPartsbool(bool parts)
{
    m_bModelParts = parts;
}
void CObjectX::SetModelMtxWorld(D3DXMATRIX mtx)
{
    m_ModelmtxWorld = mtx;
}
void CObjectX::SetColorChangeBool(bool ChangeColorBool)
{
    m_ChangeColorBool = ChangeColorBool;
}
void CObjectX::SetChangeColor(D3DXCOLOR ChangeCol)
{
   m_ChangeCol = ChangeCol;
}
void CObjectX::ChengeStageTex(bool Change)
{
    m_bStageTexChange = Change;
}
//=============================
// ��b���ݒ�
//=============================
void CObjectX::SetDATA(DATA data)
{
    m_Data = data;
}