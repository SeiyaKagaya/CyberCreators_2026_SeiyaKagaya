//=======================================================
//
// debugwall�Ɋւ��鏈��[debugwall.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "debugwall.h"
#include "renderer.h"
#include "manager.h"

//=============================
// �R���X�g���N�^
//=============================
CDebugwall::CDebugwall(int nPriority) :CObject3D(nPriority)
{
    SetObjectType(CObject::OBJECT_DEBUGWALL);
}

//=============================
// �f�X�g���N�^
//=============================
CDebugwall::~CDebugwall()
{
    Uninit();
}

//=============================
// �����ݒ�(���_�o�b�t�@����)
//=============================
HRESULT CDebugwall::Init()
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

    //�o�b�t�@�i�[
    BindVtxBuffer(ESCpVtxBuff);

    //�e�N�X�`���ǂݍ���
    LPDIRECT3DTEXTURE9	m_ESCpTexture = nullptr;

    //�e�N�X�`���擾
    CAllTexture* pTexture = pManager->GetTexture();

    int texIndex = pTexture->Regist("DATA\\TEXTURE\\iwaWall.png", EscDevice);//�e�N�X�`���o�^

    m_ESCpTexture = pTexture->GetAddress(texIndex);//�e�N�X�`���̃A�h���X���擾

    BindTexture(m_ESCpTexture);//�ݒ�

    return S_OK;
}

//=============================
// �I������(���_�o�b�t�@�j��)
//=============================
void CDebugwall::Uninit()
{
    CObject3D::Uninit();
}

//=============================
// �X�V(���_���̍X�V)
//=============================
void CDebugwall::Update()
{
    //���_�����X�V
    InputpVtx();

    CObject3D::Update();
}

//=============================
// �`�揈��(POLYGON�`��)
//=============================
void CDebugwall::Draw()
{
    CObject3D::Draw();
}

//=============================
// ���W�ݒ�
//=============================
void CDebugwall::SetPos_Rot(D3DXVECTOR3 Pos, D3DXVECTOR3 rot)
{
    DATA EscData = GetDATA();

    EscData.Pos = Pos;
    EscData.rot = rot;
    
    SetDATA(EscData);
}

//=============================
// ���_���
//=============================
void CDebugwall::InputpVtx()
{
    // �����ݒ�
    VERTEX_3D pVtx[BASE_INDEX];

    //�擾
    DATA EscData = GetDATA();

    //���_���W�̐ݒ�
    pVtx[0].pos = D3DXVECTOR3(-PRINTSIZE, EscData.Pos.y, PRINTSIZE);
    pVtx[1].pos = D3DXVECTOR3(PRINTSIZE, EscData.Pos.y, PRINTSIZE);
    pVtx[2].pos = D3DXVECTOR3(-PRINTSIZE, EscData.Pos.y,-PRINTSIZE);
    pVtx[3].pos = D3DXVECTOR3(PRINTSIZE, EscData.Pos.y, -PRINTSIZE);

    //�@���x�N�g���̐ݒ�
    pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

    //���_�J���[�̐ݒ�
    pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

    //�e�N�X�`�����W��ݒ�
    pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//����
    pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//�E��
    pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//����
    pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//�E��

    SetpVtx(pVtx);//�i�[
}

//=============================
// Object����
//=============================
CDebugwall* CDebugwall::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 rot)
{
    CDebugwall* pObject3D = new CDebugwall;
    pObject3D->SetPos_Rot(Pos, rot);
    pObject3D->Init();
    return pObject3D;
}