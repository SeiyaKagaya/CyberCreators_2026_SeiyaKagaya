//=======================================================
//
// ExplosionBill�Ɋւ��鏈��[ExplosionBill.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "Explosion_Bill.h"
#include "renderer.h"
#include "manager.h"

//=============================
// �R���X�g���N�^
//=============================
CObjectExplosionBill::CObjectExplosionBill(int nPriority) :CObjectBillBoard(nPriority), m_nPatternAnim(1)
{
    SetObjectType(CObject::OBJECT_EXPRO_BILL);

    //���Z����On��
    ChengeAddDrawMode(true);
}

//=============================
// �f�X�g���N�^
//=============================
CObjectExplosionBill::~CObjectExplosionBill()
{
    Uninit();
}

//=============================
// �����ݒ�(���_�o�b�t�@����)
//=============================
HRESULT CObjectExplosionBill::Init()
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

    int texIndex = pTexture->Regist("DATA\\TEXTURE\\ExplosionBill.png", EscDevice);//�e�N�X�`���o�^

    m_ESCpTexture = pTexture->GetAddress(texIndex);

    BindTexture(m_ESCpTexture);//�ݒ�

    return S_OK;
}

//=============================
// �I������(���_�o�b�t�@�j��)
//=============================
void CObjectExplosionBill::Uninit()
{
    CObjectBillBoard::Uninit();
}

//=============================
// �X�V(���_���̍X�V)
//=============================
void CObjectExplosionBill::Update()
{
    InputpVtx();

   
    m_nPatternAnim++;

    if (m_nPatternAnim > DIVISION_NUMBER)
    {
        SetDeath(true);
    }

    CObjectBillBoard::Update();
}

//=============================
// �`�揈��(POLYGON�`��)
//=============================
void CObjectExplosionBill::Draw()
{
    CObjectBillBoard::Draw();
}

//=============================
// ���W�ݒ�
//=============================
void CObjectExplosionBill::SetPos(D3DXVECTOR3 Pos)
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
void CObjectExplosionBill::InputpVtx()
{
    // �����ݒ�
    VERTEX_3D pVtx[BASE_INDEX];

    //�擾
    DATA EscData = GetDATA();

     //���_���W�̐ݒ�
    pVtx[0].pos = D3DXVECTOR3(-PRINTSIZE, PRINTSIZE, 0.0f);
    pVtx[1].pos = D3DXVECTOR3(PRINTSIZE, PRINTSIZE, 0.0f);
    pVtx[2].pos = D3DXVECTOR3(-PRINTSIZE, -PRINTSIZE, 0.0f);
    pVtx[3].pos = D3DXVECTOR3(PRINTSIZE, -PRINTSIZE, 0.0f);


    //�@���x�N�g���̐ݒ�
    pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
    pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
    pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
    pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

    //���_�J���[�̐ݒ�
    pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

    pVtx[0].tex = D3DXVECTOR2((1.0f / DIVISION_NUMBER) * m_nPatternAnim - (1.0f / DIVISION_NUMBER), 0.0f);//�e�N�X�`�����������E���ɍ��W���Y���Ă�
    pVtx[1].tex = D3DXVECTOR2((1.0f / DIVISION_NUMBER) * m_nPatternAnim, 0.0f);
    pVtx[2].tex = D3DXVECTOR2((1.0f / DIVISION_NUMBER) * m_nPatternAnim - (1.0f / DIVISION_NUMBER), 1.0f);//�e�N�X�`�����������E���ɍ��W���Y���Ă�
    pVtx[3].tex = D3DXVECTOR2((1.0f / DIVISION_NUMBER) * m_nPatternAnim, 1.0f);

    SetpVtx(pVtx);
}

//=============================
// Object����
//=============================
CObjectExplosionBill* CObjectExplosionBill::Create(D3DXVECTOR3 Pos)
{
    CObjectExplosionBill* pObject3D = new CObjectExplosionBill;
    pObject3D->SetPos(Pos);
    pObject3D->Init();
    return pObject3D;
}
