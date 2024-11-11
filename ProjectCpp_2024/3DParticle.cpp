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
CObject3DParticle::CObject3DParticle(int nPriority) :CObjectBillBoard(nPriority)
{
    SetObjectType(CObject::OBJECT_3DPARTICLE);
    ChengeAddDrawMode(true);
    // m_pVtxBuff = nullptr;
    // m_pTexture = nullptr;

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
    //int texIndex = pTexture->Regist("DATA\\TEXTURE\\explosion000.png", EscDevice);//�e�N�X�`���o�^

    m_ESCpTexture = pTexture->GetAddress(texIndex);

    BindTexture(m_ESCpTexture);//�ݒ�


 //   SetpVtx(pVtx);

  //  InputpVtx();
    m_nLife = START_LIFE;
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
    InputpVtx();

      m_nLife--;






    if (m_nLife <= 0 )
    {
        SetDeath(true);
    }



    CObjectBillBoard::Update();
}
//=============================
// �`�揈��(POLYGON�`��)
//=============================
void CObject3DParticle::Draw()
{
    CObjectBillBoard::Draw();
}
//=============================
// ���W�ݒ�
//=============================
void CObject3DParticle::SetPos_Rot(D3DXVECTOR3 Pos)
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
    //pVtx[0].pos = D3DXVECTOR3((float)-PRINTSIZE_X, 10.0f, (float)PRINTSIZE_Z);
    //pVtx[1].pos = D3DXVECTOR3((float)PRINTSIZE_X, 10.0f, (float)PRINTSIZE_Z);
    //pVtx[2].pos = D3DXVECTOR3((float)-PRINTSIZE_X, 10.0f, (float)-PRINTSIZE_Z);
    //pVtx[3].pos = D3DXVECTOR3((float)PRINTSIZE_X, 10.0f, (float)-PRINTSIZE_Z);

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

    ////�@���x�N�g���̐ݒ�
    //pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    //pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    //pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    //pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    
    //�e�N�X�`�����W��ݒ�
    //pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//����
    //pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//�E��
    //pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//����
    //pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//�E��
    
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



    //   ESCpVtxBuff->Unlock();

   //    BindVtxBuffer(ESCpVtxBuff);

    SetpVtx(pVtx);
}
void CObject3DParticle::SetCOL(D3DXCOLOR col)
{
    m_col = col;
}
//=============================
// Object����
//=============================
CObject3DParticle* CObject3DParticle::Create(D3DXVECTOR3 Pos,D3DXCOLOR col)
{
    CObject3DParticle* pObject3D = new CObject3DParticle;
    pObject3D->SetPos_Rot(Pos);
    pObject3D->Init();
    pObject3D->SetCOL(col);
    return pObject3D;
}
