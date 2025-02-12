//=======================================================
//
// sea�Ɋւ��鏈��[sea.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "sea.h"
#include "renderer.h"
#include "manager.h"

//=============================
// �R���X�g���N�^
//=============================
CSea::CSea(int nPriority) :CObject3D(nPriority)
{
    SetObjectType(CObject::OBJECT_SEA);
}

//=============================
// �f�X�g���N�^
//=============================
CSea::~CSea()
{
    Uninit();
}

//=============================
// �����ݒ�(���_�o�b�t�@����)
//=============================
HRESULT CSea::Init()
{
    CRenderer* pRenderer = nullptr;
    CManager* pManager = CManager::GetInstance();
    pRenderer = pManager->GetRenderer();
    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

    LPDIRECT3DVERTEXBUFFER9 ESCpVtxBuff;//���_�o�b�t�@

    if (FAILED(EscDevice->CreateVertexBuffer(
        sizeof(VERTEX_3D) * 4,//�l�p�`�̂���4
        D3DUSAGE_WRITEONLY,
        FVF_VERTEX_3D,
        D3DPOOL_MANAGED,
        &ESCpVtxBuff,
        nullptr)))
    {
        return E_FAIL;
    }

    BindVtxBuffer(ESCpVtxBuff);

    //�e�N�X�`���ǂݍ���
    LPDIRECT3DTEXTURE9	m_ESCpTexture = nullptr;

    //�e�N�X�`���擾
    CAllTexture* pTexture = pManager->GetTexture();

    int texIndex = pTexture->Regist("DATA\\TEXTURE\\umi1.jpg", EscDevice);//�e�N�X�`���o�^

    m_ESCpTexture = pTexture->GetAddress(texIndex);//�e�N�X�`���̃A�h���X���i�[

    BindTexture(m_ESCpTexture);//�ݒ�

    return S_OK;
}

//=============================
// �I������(���_�o�b�t�@�j��)
//=============================
void CSea::Uninit()
{ 
    CObject3D::Uninit();
}

//=============================
// �X�V(���_���̍X�V)
//=============================
void CSea::Update()
{
    InputpVtx();//���_�����X�V���i�[

    CScene::MODE NowState = CScene::GetNowScene();

    if (NowState == CScene::MODE_GAME || NowState == CScene::MODE_GAME2 || NowState == CScene::MODE_GAME3 || NowState == CScene::MODE_MOVIE || NowState == CScene::MODE_MOVIE2)
    {//�Q�[����

     // �e�N�X�`���I�t�Z�b�g�̍X�V (�A�j���[�V�������x)
        m_texOffsetX += 0.00004f;  // X�����ɏ������ړ�
        m_texOffsetY += 0.00002f;  // X�����ɏ������ړ�

    }
    else if (NowState == CScene::MODE_OP)
    {//�o���O���o
        // �e�N�X�`���I�t�Z�b�g�̍X�V (�A�j���[�V�������x)
        m_texOffsetX += 0.0002f;  // X�����ɏ������ړ�
        m_texOffsetY += 0.0009f;  // X�����ɏ������ړ�
    }

    CObject3D::Update();
}

//=============================
// �`�揈��(POLYGON�`��)
//=============================
void CSea::Draw()
{
    CRenderer* pRenderer = nullptr;
    CManager* pManager = CManager::GetInstance();
    pRenderer = pManager->GetRenderer();
    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

    D3DXMATRIX mtxRot, mtxTrans;

    // �e�N�X�`���ϊ��s��
    D3DXMATRIX matTexTransform;

    D3DXMatrixScaling(&matTexTransform, 1.0f, 1.0f, 1.0f);  // 0.5�{�ɃX�P�[�����O
    matTexTransform._31 = m_texOffsetX; // X�����̃I�t�Z�b�g�ݒ�
    matTexTransform._32 = m_texOffsetY; // Y�����̃I�t�Z�b�g�ݒ�

    // �e�N�X�`���ϊ���L���ɂ���
    EscDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2); // 2D�ϊ�
    EscDevice->SetTransform(D3DTS_TEXTURE0, &matTexTransform);  // �e�N�X�`���s���ݒ�

    CObject3D::Draw();

    EscDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE); // �e�N�X�`���ϊ��𖳌��ɂ���
}

//=============================
// ���W�ݒ�
//=============================
void CSea::SetPos_Rot(D3DXVECTOR3 Pos, D3DXVECTOR3 rot)
{
    //�擾
    DATA EscData = GetDATA();

    EscData.Pos = Pos;
    EscData.rot = rot;

    //�擾
    SetDATA(EscData);
}

//=============================
// ���_���
//=============================
void CSea::InputpVtx()
{
    // �����ݒ�
    VERTEX_3D pVtx[BASE_INDEX];

    //�擾
    DATA EscData = GetDATA();

    //���_���W�̐ݒ�
    pVtx[0].pos = D3DXVECTOR3((float)-PRINTSIZE, 0.0f, (float)PRINTSIZE);
    pVtx[1].pos = D3DXVECTOR3((float)PRINTSIZE, 0.0f, (float)PRINTSIZE);
    pVtx[2].pos = D3DXVECTOR3((float)-PRINTSIZE, 0.0f, (float)-PRINTSIZE);
    pVtx[3].pos = D3DXVECTOR3((float)PRINTSIZE, 0.0f, (float)-PRINTSIZE);

    //�@���x�N�g���̐ݒ�
    pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

    //���_�J���[�̐ݒ�
    pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_rgbA);
    pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_rgbA);
    pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_rgbA);
    pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_rgbA);

    //�e�N�X�`�����W��ݒ�
    pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//����
    pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//�E��
    pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//����
    pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//�E��

    SetpVtx(pVtx);//���_���i�[
}

//=============================
// Object����
//=============================
CSea* CSea::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 rot, float rgbA)
{
    CSea* pObject3D = new CSea;
    pObject3D->SetPos_Rot(Pos, rot);
    pObject3D->Init();
    pObject3D->SetrgbA(rgbA);
    return pObject3D;
}