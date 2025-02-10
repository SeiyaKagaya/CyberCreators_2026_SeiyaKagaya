//=======================================================
//
// smoke�Ɋւ��鏈��[smoke.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "smoke.h"
#include "renderer.h"
#include "manager.h"

//=============================
// �R���X�g���N�^
//=============================
CObjectSmoke::CObjectSmoke(int nPriority) :CObjectBillBoard(nPriority), m_nPatternAnim(1)
{
    SetObjectType(CObject::OBJECT_SMOKE);

    //���Z����
    ChengeAddDrawMode(true);
}

//=============================
// �f�X�g���N�^
//=============================
CObjectSmoke::~CObjectSmoke()
{
    Uninit();
}

//=============================
// �����ݒ�(���_�o�b�t�@����)
//=============================
HRESULT CObjectSmoke::Init()
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

    int texIndex = pTexture->Regist("DATA\\TEXTURE\\explosion000.png", EscDevice);//�e�N�X�`���o�^

    m_ESCpTexture = pTexture->GetAddress(texIndex);

    BindTexture(m_ESCpTexture);//�ݒ�

    m_nLife = START_LIFE;
    return S_OK;
}

//=============================
// �I������(���_�o�b�t�@�j��)
//=============================
void CObjectSmoke::Uninit()
{
    CObjectBillBoard::Uninit();
}

//=============================
// �X�V(���_���̍X�V)
//=============================
void CObjectSmoke::Update()
{
    InputpVtx();

    m_nPatternAnim++;
    
    if (m_nLife <= 0 || m_nPatternAnim > DIVISION_NUMBER)
    {
        SetDeath(true);
    }
    CObjectBillBoard::Update();
}

//=============================
// �`�揈��(POLYGON�`��)
//=============================
void CObjectSmoke::Draw()
{
    SetZDrawDeth(true);

    CObjectBillBoard::Draw();

    SetZDrawDeth(false);
}

//=============================
// ���W�ݒ�
//=============================
void CObjectSmoke::SetPos(D3DXVECTOR3 Pos)
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
void CObjectSmoke::InputpVtx()
{
    // �����ݒ�
    VERTEX_3D pVtx[BASE_INDEX];

    //�擾
    DATA EscData = GetDATA();

    //���_���W�̐ݒ�
    pVtx[0].pos = D3DXVECTOR3(-PRINTSIZE_X, PRINTSIZE_Z, 0.0f);
    pVtx[1].pos = D3DXVECTOR3(PRINTSIZE_X, PRINTSIZE_Z, 0.0f);
    pVtx[2].pos = D3DXVECTOR3(-PRINTSIZE_X, -PRINTSIZE_Z, 0.0f);
    pVtx[3].pos = D3DXVECTOR3(PRINTSIZE_X, -PRINTSIZE_Z, 0.0f);

    //�@���x�N�g���̐ݒ�
    pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
    pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
    pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
    pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

    //���_�J���[�̐ݒ�
    pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.35f);
    pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.35f);
    pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.35f);
    pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.35f);

    pVtx[0].tex = D3DXVECTOR2((1.0f / DIVISION_NUMBER) * m_nPatternAnim - (1.0f / DIVISION_NUMBER), 0.0f);//�e�N�X�`�����������E���ɍ��W���Y���Ă�
    pVtx[1].tex = D3DXVECTOR2((1.0f / DIVISION_NUMBER) * m_nPatternAnim, 0.0f);
    pVtx[2].tex = D3DXVECTOR2((1.0f / DIVISION_NUMBER) * m_nPatternAnim - (1.0f / DIVISION_NUMBER), 1.0f);//�e�N�X�`�����������E���ɍ��W���Y���Ă�
    pVtx[3].tex = D3DXVECTOR2((1.0f / DIVISION_NUMBER) * m_nPatternAnim, 1.0f);

    SetpVtx(pVtx);
}

//=============================
// Object����
//=============================
CObjectSmoke* CObjectSmoke::Create(D3DXVECTOR3 Pos)
{
    CObjectSmoke* pObject3D = new CObjectSmoke;
    pObject3D->SetPos(Pos);
    pObject3D->Init();
    return pObject3D;
}