//=======================================================
//
// object_billboard�Ɋւ��鏈��[object_billboard.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "object_billboard.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "all_texture.h"

//=============================
// �R���X�g���N�^
//=============================
CObjectBillBoard::CObjectBillBoard(int nPriority) :CObjectX(nPriority)
{
    SetObjectType(CObject::OBJECT_BILLBOARD);
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
    m_ZDethDrawMode = false;
}
//=============================
// �f�X�g���N�^
//=============================
CObjectBillBoard::~CObjectBillBoard()
{
    Uninit();
}
//=============================
// �����ݒ�(���_�o�b�t�@����)
//=============================
HRESULT CObjectBillBoard::Init()
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

    float fTest = 2400.0f/2;
    float fTest2 = 3300.0f/2;

    ////���_���W�̐ݒ�
    //pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, fTest);
    //pVtx[1].pos = D3DXVECTOR3(fTest2, 0.0f, fTest);
    //pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    //pVtx[3].pos = D3DXVECTOR3(fTest2, 0.0f, 0.0f);

    //���_���W�̐ݒ�
    pVtx[0].pos = D3DXVECTOR3(-fTest2, fTest2, 0.0f);
    pVtx[1].pos = D3DXVECTOR3(fTest2, fTest2, 0.0f);
    pVtx[2].pos = D3DXVECTOR3(-fTest2, -fTest2, 0.0f);
    pVtx[3].pos = D3DXVECTOR3(fTest2, -fTest2, 0.0f);



    ////�@���x�N�g���̐ݒ�
    //pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    //pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    //pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    //pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);


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

    int texIndex = pTexture->Regist("DATA\\TEXTURE\\TestField.png", EscDevice);//�e�N�X�`���o�^

    m_ESCpTexture = pTexture->GetAddress(texIndex);

    BindTexture(m_ESCpTexture);//�ݒ�


    SetpVtx(pVtx);

    return S_OK;
}
//=============================
// �I������(���_�o�b�t�@�j��)
//=============================
void CObjectBillBoard::Uninit()
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
void CObjectBillBoard::Update()
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
void CObjectBillBoard::Draw()
{
    CRenderer* pRenderer = nullptr;
    CManager* pManager = CManager::GetInstance();
    pRenderer = pManager->GetRenderer();
    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

    D3DXMATRIX mtxRot, mtxTrans, mtxBillboard, mtxView;

    if (bSetLight == true)
    {
        // ���C�g�𖳌��ɂ���
        EscDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
    }
    if (m_ZDethDrawMode)
    {
        //Z�̔�r���@�ύX
        EscDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

        // Z�o�b�t�@�ɏ������܂Ȃ�
        EscDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
    }

    // ���[���h�}�g���b�N�X�̏�����
    D3DXMatrixIdentity(&m_mtxWorld);

    // �r���[�}�g���b�N�X���擾
    EscDevice->GetTransform(D3DTS_VIEW, &mtxView);

    // �r���[�s��̋t�s����擾
    D3DXMatrixInverse(&mtxBillboard, NULL, &mtxView);

    // �t�s��̈ʒu���������Z�b�g�i��]�������c���j
    mtxBillboard._41 = 0.0f;
    mtxBillboard._42 = 0.0f;
    mtxBillboard._43 = 0.0f;

    // �r���{�[�h�s������[���h�s��Ɋ|�����킹��
    D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxBillboard);

    // �ʒu�𔽉f
    D3DXMatrixTranslation(&mtxTrans, m_Data.Pos.x, m_Data.Pos.y, m_Data.Pos.z);
    D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

    // ���[���h�}�g���b�N�X�̐ݒ�
    EscDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

    if (m_AddDrawMode)
    {
        EscDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
        EscDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
        EscDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
        EscDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
    }

    // ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    EscDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

    // ���_�t�H�[�}�b�g�̐ݒ�
    EscDevice->SetFVF(FVF_VERTEX_3D);

    // �e�N�X�`���̐ݒ�
    EscDevice->SetTexture(0, m_pTexture);

    for (int i = 0; i < nAddDrawCnt; i++)
    {
        // �|���S���̕`��
        EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
    }

    if (m_AddDrawMode)
    {
        EscDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
        EscDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
        EscDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
        EscDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
    }

    if (bSetLight == true)
    {
        // ���C�g��L���ɂ���
        EscDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
    }

    if (m_ZDethDrawMode)
    {
        //Z�̔�r���@�ύX
        EscDevice->SetRenderState(D3DRS_ZFUNC,D3DCMP_LESSEQUAL);

        // Z�o�b�t�@�ւ̏������݂�L���ɂ���
        EscDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
    }
}

//=============================
// Object����
//=============================
CObjectBillBoard* CObjectBillBoard::Create()
{
    CObjectBillBoard* pObject3D = new CObjectBillBoard;
    pObject3D->Init();
    return pObject3D;
}
//=============================
// �e�N�X�`���ݒ�
//=============================
void CObjectBillBoard::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
    m_pTexture = pTex;
}
//=============================
// �e�N�X�`���擾
//=============================
LPDIRECT3DTEXTURE9 CObjectBillBoard::GetTexture()
{
    return m_pTexture;
}
//=============================
// �o�b�t�@�ݒ�
//=============================
void CObjectBillBoard::BindVtxBuffer(LPDIRECT3DVERTEXBUFFER9 pVtx)
{
    m_pVtxBuff = pVtx;
}
//=============================
// �o�b�t�@�擾
//=============================
LPDIRECT3DVERTEXBUFFER9 CObjectBillBoard::GetpVtxBuffer()
{
    return m_pVtxBuff;
}
//=============================
// ��b���擾
//=============================
CObjectBillBoard::DATA CObjectBillBoard::GetDATA()
{
    return m_Data;
}
//=============================
// ��b���ݒ�
//=============================
void CObjectBillBoard::SetDATA(DATA data)
{
    m_Data = data;
}
//=============================
// �F�ύX
//=============================
void CObjectBillBoard::ChangeRGBA(D3DCOLOR col)
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
void CObjectBillBoard::ChengeAddDrawMode(bool bSet)
{
    m_AddDrawMode = bSet;
}
//=============================
// ���_�A�e�N�X�`�����W�؂�ւ�
//=============================
void CObjectBillBoard::SetpVtx(VERTEX_3D pVtx[BASE_INDEX])
{
    for (int nCnt = 0; nCnt < BASE_INDEX; nCnt++)
    {
        m_pVtx[nCnt] = pVtx[nCnt];
    }
}
//=============================
// ���_���W����
//=============================
void CObjectBillBoard::InputpVtx()
{
}

void CObjectBillBoard::SetZDrawDeth(bool bDraw)
{
    m_ZDethDrawMode = bDraw;
}
