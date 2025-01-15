//=======================================================
//
// LockOnUI�Ɋւ��鏈��[LockOnUI.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "LockOnUI.h"
#include "renderer.h"
#include "manager.h"
#include "player_motion.h"

//=============================
// �R���X�g���N�^
//=============================
CLockOnUI::CLockOnUI(int nPriority) :CObjectBillBoard(nPriority)
{
  

  //  ChengeAddDrawMode(true);

    // m_pVtxBuff = nullptr;
    // m_pTexture = nullptr;

}
//=============================
// �f�X�g���N�^
//=============================
CLockOnUI::~CLockOnUI()
{
    Uninit();
}
//=============================
// �����ݒ�(���_�o�b�t�@����)
//=============================
HRESULT CLockOnUI::Init()
{
    SetObjectType(CObject::OBJECT_LOCKONUI);

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

    int texIndex = pTexture->Regist("DATA\\TEXTURE\\LockOn000.png", EscDevice);//�e�N�X�`���o�^

    m_ESCpTexture = pTexture->GetAddress(texIndex);

    BindTexture(m_ESCpTexture);//�ݒ�

    fSize = PRINTSIZE;

 //   SetpVtx(pVtx);

  //  InputpVtx();

    SetObjectType(CObject::OBJECT_LOCKONUI);

    return S_OK;
}
//=============================
// �I������(���_�o�b�t�@�j��)
//=============================
void CLockOnUI::Uninit()
{
    CObjectBillBoard::Uninit();
}
//=============================
// �X�V(���_���̍X�V)
//=============================
void CLockOnUI::Update()
{


    InputpVtx();

  

    CObjectBillBoard::Update();
}
//=============================
// �`�揈��(POLYGON�`��)
//=============================
void CLockOnUI::Draw()
{
    //    ChengeAddDrawMode(true);
    //SetZDrawDeth(true);
    //for (int i = 0; i < 20; i++)
    //{

    if (m_bDrawOk == true)
    {
        SetZDrawDeth(true);
        SetLight(true);
        CObjectBillBoard::Draw();
        SetZDrawDeth(false);
    }
    
    /*   }
    SetZDrawDeth(false);*/
}
//=============================
// ���W�ݒ�
//=============================
void CLockOnUI::SetPos(D3DXVECTOR3 Pos)
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
void CLockOnUI::InputpVtx()
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
    pVtx[0].pos = D3DXVECTOR3(-fSize, fSize, 0.0f);
    pVtx[1].pos = D3DXVECTOR3(fSize, fSize, 0.0f);
    pVtx[2].pos = D3DXVECTOR3(-fSize, -fSize, 0.0f);
    pVtx[3].pos = D3DXVECTOR3(fSize, -fSize, 0.0f);


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
    //pVtx[0].tex = D3DXVECTOR2((1.0f / DIVISION_NUMBER) * m_nPatternAnim - (1.0f / DIVISION_NUMBER), 0.0f);//�e�N�X�`�����������E���ɍ��W���Y���Ă�
    //pVtx[1].tex = D3DXVECTOR2((1.0f / DIVISION_NUMBER) * m_nPatternAnim, 0.0f);
    //pVtx[2].tex = D3DXVECTOR2((1.0f / DIVISION_NUMBER) * m_nPatternAnim - (1.0f / DIVISION_NUMBER), 1.0f);//�e�N�X�`�����������E���ɍ��W���Y���Ă�
    //pVtx[3].tex = D3DXVECTOR2((1.0f / DIVISION_NUMBER) * m_nPatternAnim, 1.0f);



    //   ESCpVtxBuff->Unlock();

   //    BindVtxBuffer(ESCpVtxBuff);

    SetpVtx(pVtx);

}
//=============================
// Object����
//=============================
CLockOnUI* CLockOnUI::Create()
{
    CLockOnUI* pObject3D = new CLockOnUI;

    pObject3D->Init();
   // pObject3D->SetPos(Pos);
    return pObject3D;
}
