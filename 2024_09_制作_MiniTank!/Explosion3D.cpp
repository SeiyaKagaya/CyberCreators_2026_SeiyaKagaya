//=======================================================
//
// Explosion3D�Ɋւ��鏈��[Explosion3D.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "Explosion3D.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "all_texture.h"
#include <stdio.h>

//=============================
// �R���X�g���N�^
//=============================
Explosion3D::Explosion3D(int nPriority) :CObject(nPriority)
{
    m_nLife = ANIMNUM;
    m_pMesh = nullptr;
    m_pBuffMat = nullptr;
    m_dwNumMat = 0;
    m_SizeMag = D3DXVECTOR3(1.0f, 1.0f, 1.0f);//�{���i�[(1.0������)
    m_ChangeCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    m_bMagChange = true;//�{���ϓ�
}

//=============================
// �f�X�g���N�^
//=============================
Explosion3D::~Explosion3D()
{
    Uninit();
}

//=============================
// �����ݒ�(���_�o�b�t�@����)
//=============================
HRESULT Explosion3D::Init()
{
    m_Data.Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.OldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.MinLength = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.MaxLength = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.Radius = 0.0f;


    SetObjectType(CObject::OBJECT_EXPLOSION3D);

    CRenderer* pRenderer = nullptr;
    CManager* pManager = CManager::GetInstance();
    pRenderer = pManager->GetRenderer();
    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

    //�t�@�C���̓ǂݍ���
    D3DXLoadMeshFromX("DATA\\MODEL\\Sphere.x",
        D3DXMESH_SYSTEMMEM,
        EscDevice,
        NULL,
        &m_pBuffMat,
        NULL,
        &m_dwNumMat,
        &m_pMesh);

    //�}�e���A���f�[�^�ւ̃|�C���^���擾
    D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

    for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
    {
        // �f�B�t���[�Y�J���[���T�C�Y�Ɋ�Â��ĕύX
        D3DXCOLOR originalColor = pMat[nCntMat].MatD3D.Diffuse;

        pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�F�������Ŏw��
    }

    m_SetSize = D3DXVECTOR3(3.0f, 3.0f, 3.0f);
    
    SetSizeMag(m_SetSize);//�傫���{��
    
    m_Data.MinLength = D3DXVECTOR3(-50.0f, 0.0f, -50.0f);
    m_Data.MaxLength = D3DXVECTOR3(50.0f, 50.0f, 50.0f);

    //�e�N�X�`���擾
    CAllTexture* pTexture = pManager->GetTexture();

    int texIndex = pTexture->Regist("DATA\\TEXTURE\\EXPLOSION3D_2.png", EscDevice);//�e�N�X�`���o�^

    m_ESCpTexture = pTexture->GetAddress(texIndex);

    m_Data.rot.y = 4.5f;
    m_Data.rot.x = 4.5f;

    CSound* pSound = pManager->GetSound();
    pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);

    return S_OK;
}

//=============================
// �I������(���_�o�b�t�@�j��)
//=============================
void Explosion3D::Uninit()
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
}

//=============================
// �X�V(���_���̍X�V)
//=============================
void Explosion3D::Update()
{
    CManager* pManager = CManager::GetInstance();

    if (m_nCnt <= 18)
    {
        pManager->GetCamera()->SetShake(85, 85);

        m_SetSize.x += 2.3f;
        m_SetSize.y += 2.3f;
        m_SetSize.z += 2.3f;
    }
    else if (m_nCnt > 18 || m_nCnt <= 40)
    {
        pManager->GetCamera()->SetShake(55, 55);

        m_SetSize.x += 0.7f;
        m_SetSize.y += 0.7f;
        m_SetSize.z += 0.7f;
    }
    else
    {
        pManager->GetCamera()->SetShake(5, 5);

        m_SetSize.x += 0.3f;
        m_SetSize.y += 0.3f;
        m_SetSize.z += 0.3f;
    }

    SetSizeMag(m_SetSize);//�傫���{��

    m_Data.rot.y += 0.03f;
    m_Data.rot.x += 0.03f;

    m_nCnt++;

    // �e�N�X�`���I�t�Z�b�g�̍X�V (�A�j���[�V�������x)
    m_texOffsetX += (1.0f / (float)ANIMNUM);  // X�����ɏ������ړ�

    if (m_nCnt >= ANIMNUM)
    {
        m_texOffsetX = 0.0f;

        m_nCnt = 0;
    }

   // �c��̒ʏ�̍X�V����
    m_nLife--;

    if (m_nLife <= 0)
    {
        SetDeath(true);
    }
}

//=============================
// �`�揈��(POLYGON�`��)
//=============================
void Explosion3D::Draw()
{
    CRenderer* pRenderer = nullptr;
    CManager* pManager = CManager::GetInstance();
    pRenderer = pManager->GetRenderer();
    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();
    D3DXMATRIX mtxRot, mtxTrans;

    // �e�N�X�`���ϊ��s��
    D3DXMATRIX matTexTransform;

    // �J�����O�i���ʂ̔�\���j��ݒ�i�I�v�V�����j
    EscDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

    D3DXMatrixScaling(&matTexTransform, (1.0f/ (float)ANIMNUM), 1.0f, 1.0f);  // 0.5�{�ɃX�P�[�����O
    matTexTransform._31 = m_texOffsetX; // X�����̃I�t�Z�b�g�ݒ�
    matTexTransform._32 = m_texOffsetY; // Y�����̃I�t�Z�b�g�ݒ�
                                    
    // �e�N�X�`���ϊ���L���ɂ���
    EscDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2); // 2D�ϊ�
    EscDevice->SetTransform(D3DTS_TEXTURE0, &matTexTransform);  // �e�N�X�`���s���ݒ�

    // ���[���h�}�g���b�N�X�̏�����
    D3DXMatrixIdentity(&m_mtxWorld);

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

    D3DMATERIAL9 matDef;
    D3DXMATERIAL* pMat;

    // ���[���h�}�g���b�N�X�̐ݒ�
    EscDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
    // ���_�t�H�[�}�b�g�̐ݒ�
    EscDevice->SetFVF(FVF_VERTEX_3D);
    // ���݂̃}�e���A�����擾
    EscDevice->GetMaterial(&matDef);

    // �ʏ�̃I�u�W�F�N�g�̕`��
    if (m_pBuffMat != nullptr)
    {
        pMat = reinterpret_cast<D3DXMATERIAL*>(m_pBuffMat->GetBufferPointer());

        for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
        {
            // ���[���h�s������ɖ߂�
            EscDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

            // �}�e���A���̐ݒ�
            EscDevice->SetMaterial(&pMat[nCntMat].MatD3D);


            pMat[nCntMat].pTextureFilename = NULL;

            EscDevice->SetTexture(0, m_ESCpTexture);

            if (bFast == false)
            {//�n�߂̈��̂�
                m_OriginalColor = pMat[nCntMat].MatD3D.Diffuse;
                bFast = true;
            }

            // ���b�V���̕`��
            if (m_bMagChange == true)
            {
                D3DXCOLOR originalColor;

                if (m_ChangeColorBool == true)
                {
                    originalColor = m_ChangeCol;
                }
                else
                {
                    originalColor = m_OriginalColor;
                }

                if (m_nCnt >= 40)
                {//���ߗ�
                    originalColor.a = ((float)ANIMNUM - m_nCnt) * 0.5f;
                }

                pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(
                    originalColor.r * m_SizeMag.x,
                    originalColor.g * m_SizeMag.y,
                    originalColor.b * m_SizeMag.z,
                    originalColor.a
                );

                EscDevice->SetMaterial(&pMat[nCntMat].MatD3D);
                pMat[nCntMat].MatD3D.Diffuse = originalColor;

            }
            m_pMesh->DrawSubset(nCntMat);

            // �ۑ����Ă����}�e���A����߂�
            EscDevice->SetMaterial(&matDef);
        }
    }

    EscDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE); // �e�N�X�`���ϊ��𖳌��ɂ���

    // �J�����O�𖳌����i�I�v�V�����j
    EscDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
}

//=============================
// Object����
//=============================
Explosion3D* Explosion3D::Create(D3DXVECTOR3 Pos)
{
    Explosion3D* pObjectX = new Explosion3D;
    pObjectX->Init();
    pObjectX->SetPos(Pos);
    return pObjectX;
}

//=============================
// �T�C�Y�ϓ��̗L��
//=============================
void Explosion3D::SizeMagChangebool(bool bChange)
{
    m_bMagChange = bChange;
}

//=============================
// �T�C�Y�{���i�[
//=============================
void Explosion3D::SetSizeMag(D3DXVECTOR3 SizeMag)
{
    m_SizeMag = SizeMag;
}

//=============================
// ���W�i�[
//=============================
void Explosion3D::SetPos(D3DXVECTOR3 pos)
{
    m_Data.Pos = pos;
}
