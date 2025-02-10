//=======================================================
//
// HP_gauge�Ɋւ��鏈��[HP_gauge.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "HP_gauge.h"
#include "renderer.h"
#include "manager.h"
#include "player_motion.h"

//=============================
// �R���X�g���N�^
//=============================
CObjectHPGaugeUI::CObjectHPGaugeUI(int nPriority) :CObjectBillBoard(nPriority)
{
    SetObjectType(CObject::OBJECT_HPGAUGE);

    //���Z����On��
    ChengeAddDrawMode(true);
}

//=============================
// �f�X�g���N�^
//=============================
CObjectHPGaugeUI::~CObjectHPGaugeUI()
{
    Uninit();
}

//=============================
// �����ݒ�(���_�o�b�t�@����)
//=============================
HRESULT CObjectHPGaugeUI::Init()
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

    int texIndex = pTexture->Regist("DATA\\TEXTURE\\HP000.png", EscDevice);//�e�N�X�`���o�^

    m_ESCpTexture = pTexture->GetAddress(texIndex);

    BindTexture(m_ESCpTexture);//�ݒ�

    return S_OK;
}

//=============================
// �I������(���_�o�b�t�@�j��)
//=============================
void CObjectHPGaugeUI::Uninit()
{
    CObjectBillBoard::Uninit();
}

//=============================
// �X�V(���_���̍X�V)
//=============================
void CObjectHPGaugeUI::Update()
{
    InputpVtx();

    CObjectBillBoard::Update();
}

//=============================
// �`�揈��(POLYGON�`��)
//=============================
void CObjectHPGaugeUI::Draw()
{
    ChengeAddDrawMode(false);//���Z�����ł͂Ȃ�
    
    SetZDrawDeth(true);//Z�o�b�t�@�𖳌���

    CObjectBillBoard::Draw();
    
    SetZDrawDeth(false);//�L����
}

//=============================
// ���W�ݒ�
//=============================
void CObjectHPGaugeUI::SetPos(D3DXVECTOR3 Pos)
{
    //�擾
    DATA EscData = GetDATA();

    EscData.Pos = Pos;
    //�擾
    SetDATA(EscData);
}

//=============================
// �T�C�Y�i�[
//=============================
void CObjectHPGaugeUI::SetSize(D3DXVECTOR3 size)
{
    m_SetSize = size;
}

//=============================
// ���_���
//=============================
void CObjectHPGaugeUI::InputpVtx()
{
    // �����ݒ�
    VERTEX_3D pVtx[BASE_INDEX];

    //�擾
    DATA EscData = GetDATA();

     //���_���W�̐ݒ�
    pVtx[0].pos = D3DXVECTOR3(0.0f, m_SetSize.y, 0.0f);
    pVtx[1].pos = D3DXVECTOR3(m_SetSize.x, m_SetSize.y, 0.0f);
    pVtx[2].pos = D3DXVECTOR3(0.0f, -m_SetSize.y, 0.0f);
    pVtx[3].pos = D3DXVECTOR3(m_SetSize.x, -m_SetSize.y, 0.0f);


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
    pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//

    SetpVtx(pVtx);
}

//=============================
// �F�ύX
//=============================
void CObjectHPGaugeUI::SetCol(D3DXCOLOR col)
{
    m_col = col;
}

//=============================
// Object����
//=============================
CObjectHPGaugeUI* CObjectHPGaugeUI::Create(D3DXVECTOR3 Pos)
{
    CObjectHPGaugeUI* pObject3D = new CObjectHPGaugeUI;

    pObject3D->Init();
    pObject3D->SetPos(Pos);
    return pObject3D;
}