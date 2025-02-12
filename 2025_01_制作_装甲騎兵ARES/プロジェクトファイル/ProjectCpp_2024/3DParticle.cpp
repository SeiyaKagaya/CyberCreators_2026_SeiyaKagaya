//=======================================================
//
// 3DParticle�Ɋւ��鏈��[3DParticle.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "3DParticle.h"
#include "renderer.h"
#include "manager.h"

//=============================
// �R���X�g���N�^
//=============================
CObject3DParticleAll::CObject3DParticleAll(int nPriority) : CObjectX(nPriority)
{
}

//=============================
// �f�X�g���N�^
//=============================
CObject3DParticleAll::~CObject3DParticleAll()
{
}

//=============================
// ������
//=============================
HRESULT CObject3DParticleAll::Init()
{
    //������
    for (int i = 0; i < MAXPARTICLEALL; i++)
    {
        m_NewParticle[i] = nullptr;
    }

    for (int i = 0; i < MAXPARTICLEALL; i++)
    {
        m_NewParticle[i] = CObject3DParticle::Create();
    }

    SetObjectType(CObject::OBJECT_3DPARTICLE_MNG);

    return E_NOTIMPL;
}

//=============================
// �I��
//=============================
void CObject3DParticleAll::Uninit()
{
    for (int i = 0; i < MAXPARTICLEALL; i++)
    {
        m_NewParticle[i]->SetDeath(true);
    }
}

//=============================
// Create
//=============================
CObject3DParticleAll* CObject3DParticleAll::Create()
{
    CObject3DParticleAll* pNewBulletALL = new CObject3DParticleAll;
    pNewBulletALL->Init();
    return pNewBulletALL;
}

//=============================
// Release
//=============================
void CObject3DParticleAll::ReleaseAllParticle()
{
    Uninit();
    delete this;
}

//=============================
// Clean
//=============================
void CObject3DParticleAll::AllClean()
{
    for (int i = 0; i < MAXPARTICLEALL; i++)
    {
        m_NewParticle[i]->SetUse(false);
    }
}

//=============================
// �擾
//=============================
CObject3DParticle* CObject3DParticleAll::GetParticleData(int nNum)
{
    return m_NewParticle[nNum];
}

//=============================
// �ÓI�Ƀo���b�g���Z�b�g
//=============================
void CObject3DParticleAll::SetParticle(D3DXVECTOR3 Pos, D3DXCOLOR col, int nLife, float Size)
{
    for (int i = 0; i < MAXPARTICLEALL; i++)
    {
        CObject3DParticle* pBullet = GetParticleData(i);

        if (m_NewParticle[i]->GetbUse() == false)
        {
            m_NewParticle[i]->SetCOL(col);
            m_NewParticle[i]->SetPos(Pos);
            m_NewParticle[i]->SetLife(nLife);
            m_NewParticle[i]->SetSize(Size);
            m_NewParticle[i]->SetUse(true);

            CRenderer* pRenderer = nullptr;
            CManager* pManager = CManager::GetInstance();

            break;
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------

//=============================
// �R���X�g���N�^
//=============================
CObject3DParticle::CObject3DParticle(int nPriority) :CObjectBillBoard(nPriority)
{
    SetObjectType(CObject::OBJECT_3DPARTICLE);

    ChengeAddDrawMode(true);//���Z����On
    SetAddDrawCnt(4);//���Z��
}

//=============================
// �f�X�g���N�^
//=============================
CObject3DParticle::~CObject3DParticle()
{
    Uninit();
}

//=============================
// �����ݒ�(���_�o�b�t�@����)
//=============================
HRESULT CObject3DParticle::Init()
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

    int texIndex = pTexture->Regist("DATA\\TEXTURE\\effect000.jpg", EscDevice);//�e�N�X�`���o�^
    
    m_ESCpTexture = pTexture->GetAddress(texIndex);

    BindTexture(m_ESCpTexture);//�ݒ�

    return S_OK;
}

//=============================
// �I������(���_�o�b�t�@�j��)
//=============================
void CObject3DParticle::Uninit()
{
    CObjectBillBoard::Uninit();
}

//=============================
// �X�V(���_���̍X�V)
//=============================
void CObject3DParticle::Update()
{
    if (m_bUse == true)
    {
        InputpVtx();

        if (m_nLife <= 0)
        {
            m_bUse = false;
        }

        CObjectBillBoard::Update();

        m_nLife--;
    }
}

//=============================
// �`�揈��(POLYGON�`��)
//=============================
void CObject3DParticle::Draw()
{
    if (m_bUse == true)
    {
        SetLight(true);
        CObjectBillBoard::Draw();
    }
}

//=============================
// ���W�ݒ�
//=============================
void CObject3DParticle::SetPos(D3DXVECTOR3 Pos)
{
    //�擾
    DATA EscData = GetDATA();

    EscData.Pos = Pos;
    //�擾
    SetDATA(EscData);

}

//=============================
// ���_���
//=============================
void CObject3DParticle::InputpVtx()
{
    // �����ݒ�
    VERTEX_3D pVtx[BASE_INDEX];

    //�擾
    DATA EscData = GetDATA();

    //���_���W�̐ݒ�
    pVtx[0].pos = D3DXVECTOR3(-m_Size, m_Size, 0.0f);
    pVtx[1].pos = D3DXVECTOR3(m_Size, m_Size, 0.0f);
    pVtx[2].pos = D3DXVECTOR3(-m_Size, -m_Size, 0.0f);
    pVtx[3].pos = D3DXVECTOR3(m_Size, -m_Size, 0.0f);
    
    //�@���x�N�g���̐ݒ�
    pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
    pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
    pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
    pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

    //���_�J���[�̐ݒ�
    pVtx[0].col = m_col;
    pVtx[1].col = m_col;
    pVtx[2].col = m_col;
    pVtx[3].col = m_col;

    //�e�N�X�`�����W��ݒ�
    pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//����
    pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//�E��
    pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//����
    pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//�E��

    SetpVtx(pVtx);
}

//=============================
// �F�ύX
//=============================
void CObject3DParticle::SetCOL(D3DXCOLOR col)
{
    m_col = col;
}

//=============================
// Object����
//=============================
CObject3DParticle* CObject3DParticle::Create()
{
    CObject3DParticle* pObject3D = new CObject3DParticle;

    pObject3D->Init();

    return pObject3D;
}