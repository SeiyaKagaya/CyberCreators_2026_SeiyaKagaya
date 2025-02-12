//=======================================================
//
// linerinterUI�Ɋւ��鏈��[linerinterUI.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "linerinterUI.h"
#include "renderer.h"
#include "manager.h"
#include "player_motion.h"

//=============================
// �R���X�g���N�^
//=============================
CObjectLINEUI::CObjectLINEUI(int nPriority) :CObjectBillBoard(nPriority)
{
    SetObjectType(CObject::OBJECT_LINEUI);

    ChengeAddDrawMode(true);//���Z����On��

    m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

    m_col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
    
    m_nLife = LIFE;
}

//=============================
// �f�X�g���N�^
//=============================
CObjectLINEUI::~CObjectLINEUI()
{
    Uninit();
}

//=============================
// �����ݒ�(���_�o�b�t�@����)
//=============================
HRESULT CObjectLINEUI::Init()
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

    int texIndex = pTexture->Regist("DATA\\TEXTURE\\bullet000.png", EscDevice);//�e�N�X�`���o�^

    m_ESCpTexture = pTexture->GetAddress(texIndex);//�e�N�X�`���A�h���X���擾

    BindTexture(m_ESCpTexture);//�e�N�X�`���ݒ�

    return S_OK;
}

//=============================
// �I������(���_�o�b�t�@�j��)
//=============================
void CObjectLINEUI::Uninit()
{
    CObjectBillBoard::Uninit();
}

//=============================
// �X�V(���_���̍X�V)
//=============================
void CObjectLINEUI::Update()
{
    m_nLife--;

    if (m_nLife <= 0)
    {
        SetDeath(true);
    }

    InputpVtx();

    CObjectBillBoard::Update();
}

//=============================
// �`�揈��(POLYGON�`��)
//=============================
void CObjectLINEUI::Draw()
{
    SetZDrawDeth(true);
 
    for (int i = 0; i < 20; i++)
    {//���Z�`��
        CObjectBillBoard::Draw();
    }
    
    SetZDrawDeth(false);
}

//=============================
// ���W�ݒ�
//=============================
void CObjectLINEUI::SetPos(D3DXVECTOR3 Pos)
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
void CObjectLINEUI::InputpVtx()
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
// Object����
//=============================
CObjectLINEUI* CObjectLINEUI::Create(D3DXVECTOR3 Pos)
{
    CObjectLINEUI* pObject3D = new CObjectLINEUI;

    pObject3D->Init();
    pObject3D->SetPos(Pos);
    return pObject3D;
}
