//=======================================================
//
// object3D�Ɋւ��鏈��[object3D.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "object3D.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "all_texture.h"

//=============================
// �R���X�g���N�^
//=============================
CObject3D::CObject3D(int nPriority) :CObject(nPriority)
{
    SetObjectType(CObject::OBJECT_OBJECT3D);
    m_pVtxBuff = nullptr;
    m_pTexture = nullptr;

    m_AddDrawMode = false;

    m_Data.Pos = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
    m_Data.OldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_AddDrawMode = false;

    m_Data.MinLength = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.MaxLength = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_Data.Radius = 0.0f;

}
//=============================
// �f�X�g���N�^
//=============================
CObject3D::~CObject3D()
{
    Uninit();
}
//=============================
// �����ݒ�(���_�o�b�t�@����)
//=============================
HRESULT CObject3D::Init()
{
    CRenderer* pRenderer = nullptr;

    CManager* pManager = CManager::GetInstance();

    pRenderer = pManager->GetRenderer();


    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

    if (FAILED(EscDevice->CreateVertexBuffer(
        sizeof(VERTEX_3D) * 4,//�l�p�`�̂���4
        D3DUSAGE_WRITEONLY,
        FVF_VERTEX_3D,
        D3DPOOL_MANAGED,
        &m_pVtxBuff,
        nullptr)))
    {
        return E_FAIL;
    }

    // �����ݒ�
    VERTEX_3D* pVtx;
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
#if 0

    float fTest = 2400.0f;
    float fTest2 = 3300.0f;

    //���_���W�̐ݒ�
    pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, fTest);
    pVtx[1].pos = D3DXVECTOR3(fTest2, 0.0f, fTest);
    pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    pVtx[3].pos = D3DXVECTOR3(fTest2, 0.0f, 0.0f);
#else

    D3DXVECTOR3 POS = D3DXVECTOR3(1700.0f, 0.0f, 1650.0f);




    float fTest = 4300.0f;


    CScene::MODE NowState = CScene::GetNowScene();

    if (NowState == CScene::MODE_GAME || NowState == CScene::MODE_GAME2 )
    {//�Q�[����

        float fTest = 9900.0f;
        float fTest2 = 9900.0f;

        //���_���W�̐ݒ�
        pVtx[0].pos = D3DXVECTOR3(0.0f, 30.0f, fTest);
        pVtx[1].pos = D3DXVECTOR3(fTest2, 30.0f, fTest);
        pVtx[2].pos = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
        pVtx[3].pos = D3DXVECTOR3(fTest2, 30.0f, 0.0f);


    }
    else if (NowState == CScene::MODE_TITLE)
    {//�^�C�g��
        fTest = 13300.0f;
        //���_���W�̐ݒ�
        pVtx[0].pos = D3DXVECTOR3(POS.x - fTest, 0.0f, POS.z + fTest);
        pVtx[1].pos = D3DXVECTOR3(POS.x + fTest, 0.0f, POS.z + fTest);
        pVtx[2].pos = D3DXVECTOR3(POS.x - fTest, 0.0f, POS.z - fTest);
        pVtx[3].pos = D3DXVECTOR3(POS.x + fTest, 0.0f, POS.z - fTest);
    }
    else if (NowState == CScene::MODE_RESULT)
    {//�^�C�g�� mngasd
        fTest = 13300.0f;
        //���_���W�̐ݒ�
        pVtx[0].pos = D3DXVECTOR3(POS.x - fTest, 0.0f, POS.z + fTest);
        pVtx[1].pos = D3DXVECTOR3(POS.x + fTest, 0.0f, POS.z + fTest);
        pVtx[2].pos = D3DXVECTOR3(POS.x - fTest, 0.0f, POS.z - fTest);
        pVtx[3].pos = D3DXVECTOR3(POS.x + fTest, 0.0f, POS.z - fTest);
    }


   
#endif // 0



    //�@���x�N�g���̐ݒ�
    pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

    //���_�J���[�̐ݒ�
    pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
    pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
    pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
    pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

    //�e�N�X�`�����W��ݒ�
    pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//����
    pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//�E��
    pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//����
    pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//�E��


    m_pVtxBuff->Unlock();

    //�e�N�X�`���ǂݍ���
    LPDIRECT3DTEXTURE9	m_ESCpTexture = nullptr;

    //�e�N�X�`���擾
    CAllTexture* pTexture = pManager->GetTexture();

   int texIndex = pTexture->Regist("DATA\\TEXTURE\\koke.png", EscDevice);//�e�N�X�`���o�^
 //   int texIndex = pTexture->Regist("DATA\\TEXTURE\\umi1.jpg", EscDevice);//�e�N�X�`���o�^


    

    m_ESCpTexture = pTexture->GetAddress(texIndex);

    BindTexture(m_ESCpTexture);//�ݒ�


    SetpVtx(pVtx);

    return S_OK;
}
//=============================
// �I������(���_�o�b�t�@�j��)
//=============================
void CObject3D::Uninit()
{
    m_AddDrawMode = false;

    if (m_pVtxBuff != nullptr)
    {
        m_pVtxBuff->Release();
        m_pVtxBuff = nullptr;
    }
    if (m_pTexture != nullptr)
    {
        //    m_pTexture->Release();//-----�e�N�X�`��cpp�ł�邱��
        m_pTexture = nullptr;
    }
}
//=============================
// �X�V(���_���̍X�V)
//=============================
void CObject3D::Update()
{
    // �X�V����


    VERTEX_3D* pVtx;

    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);



    //���_���W�̍X�V-----------------------------------

    for (int nCnt = 0; nCnt < BASE_INDEX; nCnt++)
    {
        pVtx[nCnt].pos = m_pVtx[nCnt].pos;//����
        pVtx[nCnt].tex = m_pVtx[nCnt].tex;
        pVtx[nCnt].nor = m_pVtx[nCnt].nor;
        pVtx[nCnt].col = m_pVtx[nCnt].col;
    }


    m_pVtxBuff->Unlock();
}
//=============================
// �`�揈��(POLYGON�`��)
//=============================
void CObject3D::Draw()
{
    CRenderer* pRenderer = nullptr;

    CManager* pManager = CManager::GetInstance();

    pRenderer = pManager->GetRenderer();

    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();


    D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

    CScene::MODE NowState = CScene::GetNowScene();

    if (NowState == CScene::MODE_GAME || NowState == CScene::MODE_GAME2 )
    {//�Q�[����

        
    }
    else if (NowState == CScene::MODE_TITLE)
    {//�^�C�g��

        m_texOffsetX -= 0.0008f;
       // m_texOffsetY += 0.01f;

            // �e�N�X�`���ϊ��s��
        D3DXMATRIX matTexTransform;
        D3DXMatrixIdentity(&matTexTransform);
    //    D3DXMatrixScaling(&matTexTransform,1.0f, 1.0f, 1.0f);  // 0.5�{�ɃX�P�[�����O
        matTexTransform._31 = m_texOffsetX; // X�����̃I�t�Z�b�g�ݒ�
        matTexTransform._32 = m_texOffsetY; // Y�����̃I�t�Z�b�g�ݒ�

                                            // �e�N�X�`���s��̃X�P�[�����O��ݒ�i0.5f�Ńe�N�X�`���͈͂𔼕��Ɂj



        // �e�N�X�`���ϊ���L���ɂ���
        EscDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2); // 2D�ϊ�
        EscDevice->SetTransform(D3DTS_TEXTURE0, &matTexTransform);  // �e�N�X�`���s���ݒ�


    }
    else if (NowState == CScene::MODE_RESULT)
    {//�^�C�g��

        if (CScene::GetStageClear() == true)
        {
            m_texOffsetX += 0.0008f;
            // m_texOffsetY += 0.01f;
        }

             // �e�N�X�`���ϊ��s��
        D3DXMATRIX matTexTransform;
        D3DXMatrixIdentity(&matTexTransform);
        //    D3DXMatrixScaling(&matTexTransform,1.0f, 1.0f, 1.0f);  // 0.5�{�ɃX�P�[�����O
        matTexTransform._31 = m_texOffsetX; // X�����̃I�t�Z�b�g�ݒ�
        matTexTransform._32 = m_texOffsetY; // Y�����̃I�t�Z�b�g�ݒ�

                                            // �e�N�X�`���s��̃X�P�[�����O��ݒ�i0.5f�Ńe�N�X�`���͈͂𔼕��Ɂj



        // �e�N�X�`���ϊ���L���ɂ���
        EscDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2); // 2D�ϊ�
        EscDevice->SetTransform(D3DTS_TEXTURE0, &matTexTransform);  // �e�N�X�`���s���ݒ�


    }






    //���[���h�}�g���b�N�X�̏�����
    D3DXMatrixIdentity(&m_mtxWorld);

    //�����𔽉f
    D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Data.rot.y, m_Data.rot.x, m_Data.rot.z);

    D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

    //�ʒu�𔽉f
    D3DXMatrixTranslation(&mtxTrans, m_Data.Pos.x, m_Data.Pos.y, m_Data.Pos.z);

    D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

    //���[���h�}�g���b�N�X�̐ݒ�
    EscDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

    //���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    EscDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

    //���_�t�H�[�}�b�g�̐ݒ�
    EscDevice->SetFVF(FVF_VERTEX_3D);

    //�e�N�X�`���̐ݒ�

    EscDevice->SetTexture(0, m_pTexture);

    //�|���S���̕`��
    EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
        0,//�`�悷��ŏ��̒��_�C���f�b�N�X
        2);//�`�悷��v���~�e�B�u��



    if (NowState == CScene::MODE_GAME || NowState == CScene::MODE_GAME2 )
    {//�Q�[����
    }
    else if (NowState == CScene::MODE_TITLE)
    {//�^�C�g��
        EscDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE); // �e�N�X�`���ϊ��𖳌��ɂ���
    }

}
//=============================
// Object����
//=============================
CObject3D* CObject3D::Create()
{
    CObject3D* pObject3D = new CObject3D;
    pObject3D->Init();
    return pObject3D;
}
//=============================
// �e�N�X�`���ݒ�
//=============================
void CObject3D::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
    m_pTexture = pTex;
}
//=============================
// �e�N�X�`���擾
//=============================
LPDIRECT3DTEXTURE9 CObject3D::GetTexture()
{
    return m_pTexture;
}
//=============================
// �o�b�t�@�ݒ�
//=============================
void CObject3D::BindVtxBuffer(LPDIRECT3DVERTEXBUFFER9 pVtx)
{
    m_pVtxBuff = pVtx;
}
//=============================
// �o�b�t�@�擾
//=============================
LPDIRECT3DVERTEXBUFFER9 CObject3D::GetpVtxBuffer()
{
    return m_pVtxBuff;
}
//=============================
// ��b���擾
//=============================
CObject3D::DATA CObject3D::GetDATA()
{
    return m_Data;
}
//=============================
// ��b���ݒ�
//=============================
void CObject3D::SetDATA(DATA data)
{
    m_Data = data;
}
//=============================
// �F�ύX
//=============================
void CObject3D::ChangeRGBA(D3DCOLOR col)
{
    VERTEX_3D* pVtx;
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    pVtx[0].col = col;
    pVtx[1].col = col;
    pVtx[2].col = col;
    pVtx[3].col = col;

    m_pVtxBuff->Unlock();
}
//=============================
// ���Z�����؂�ւ�
//=============================
void CObject3D::ChengeAddDrawMode(bool bSet)
{
    m_AddDrawMode = bSet;
}
//=============================
// ���_�A�e�N�X�`�����W�؂�ւ�
//=============================
void CObject3D::SetpVtx(VERTEX_3D pVtx[BASE_INDEX])
{
    for (int nCnt = 0; nCnt < BASE_INDEX; nCnt++)
    {
        m_pVtx[nCnt] = pVtx[nCnt];
    }
}
//=============================
// ���_���W����
//=============================
void CObject3D::InputpVtx()
{
}
