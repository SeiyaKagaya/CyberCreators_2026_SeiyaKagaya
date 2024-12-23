//=========================================================
//
//���C����\�����鏈��[line.cpp]
// Author seiya kagaya
//
//=========================================================
#include "line.h"
#include "renderer.h"
#include "manager.h"



//=============================
// �R���X�g���N�^
//=============================
Cline::Cline(int nPriority) :CObject3D(nPriority), m_pVtxBuff(nullptr)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	 m_startPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	 m_endPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	 m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col= D3DXCOLOR(0.0f,0.0f,0.0f,0.0f);
	m_Life = 3;//�������Q�ɂ���Ɛ���������
}
//=============================
//�f�X�g���N�^
//=============================
Cline::~Cline()
{
}
//=============================
// ������
//=============================
HRESULT Cline::Init()
{
 //   CObject::Init();

    CRenderer* pRenderer = nullptr;

    CManager* pManager = CManager::GetInstance();

    pRenderer = pManager->GetRenderer();


    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();


    // ���_�o�b�t�@�̐���
    EscDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 2, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

    VERTEX_3D* pVtx;

    // ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

   
        // ���_���W�̐ݒ�
        pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

        // �@���x�N�g���̐ݒ�
        pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
        pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

        // ���_�J���[
        pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
        pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

        // �e�N�X�`�����W�̐ݒ�
        pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
        pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);

    
    // ���_�o�b�t�@���A�����b�N����
    
    m_pVtxBuff->Unlock();
    SetObjectType(CObject::OBJECT_LINE);


    return S_OK;
}
//=============================
// �I������
//=============================
void Cline::Uninit()
{
    // ���_�o�b�t�@�̔j��
    if (m_pVtxBuff != NULL)
    {
        m_pVtxBuff->Release();
        m_pVtxBuff = NULL;
    }
}
//=============================
// �X�V
//=============================
void Cline::Update()
{
    
    int test = 0;

    m_Life--;

    if (m_Life <= 0)
    {
        SetDeath(true);
    }

}
//=============================
// �`��
//=============================
void Cline::Draw()
{
    CRenderer* pRenderer = nullptr;

    CManager* pManager = CManager::GetInstance();

    pRenderer = pManager->GetRenderer();


    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();


    D3DXMATRIX mtxRot, mtxTrans;                            // �v�Z�p�}�g���b�N�X

    // ���[���h�}�g���b�N�X�̏�����
    D3DXMatrixIdentity(&m_mtxWorld);

    // �����𔽉f
    D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

    D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

    // �ʒu�𔽉f
    D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

    D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

    // ���[���h�}�g���b�N�X�̐ݒ�
    EscDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

    // ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    EscDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

    // ���_�t�H�[�}�b�g�̐ݒ�
    EscDevice->SetFVF(FVF_VERTEX_3D);

    // �e�N�X�`���̐ݒ�
    EscDevice->SetTexture(0, NULL);

    // �|���S���̕`��
    EscDevice->DrawPrimitive(D3DPT_LINELIST, //�v���~�e�B�u�̎��
        0, //�`�悷��ŏ��̒��_�C���f�b�N�X
        1);             //�`�悷��v���~�e�B�u��

    //�e�N�X�`����߂�
    EscDevice->SetTexture(0, NULL);
}
//=============================
// ����
//=============================
Cline* Cline::Create(D3DXVECTOR3 start, D3DXVECTOR3 end, D3DXCOLOR col)
{
    Cline* pLine = new Cline;
    pLine->Init();
    pLine->SetLineData(start, end, col);

    return pLine;
}
//=============================
// �f�[�^�i�[
//=============================
void Cline::SetLineData(D3DXVECTOR3 start, D3DXVECTOR3 end, D3DXCOLOR col)
{
    
  //  m_pos = D3DXVECTOR3((start.x + end.x) * 0.5f, (start.y + end.y) * 0.5f, (start.z + end.z) * 0.5f);
    m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_startPos = start;
    m_endPos = end;
    m_col = col;

    VERTEX_3D* pVtx;

    // ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    //// ���_���W�̐ݒ�
    //pVtx[0].pos = D3DXVECTOR3(-fabsf(end.x - start.x) * 0.5f, -fabsf(end.y - start.y) * 0.5f, -fabsf(end.z - start.z) * 0.5f);
    //pVtx[1].pos = D3DXVECTOR3(fabsf(end.x - start.x) * 0.5f, fabsf(end.y - start.y) * 0.5f, fabsf(end.z - start.z) * 0.5f);
    pVtx[0].pos = start;
    pVtx[1].pos = end;



    pVtx[0].col = col;
    pVtx[1].col = col;
    // ���_�o�b�t�@���A�����b�N����

    m_pVtxBuff->Unlock();
    
}
