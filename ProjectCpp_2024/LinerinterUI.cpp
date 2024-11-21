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

    ChengeAddDrawMode(true);

    // m_pVtxBuff = nullptr;
    // m_pTexture = nullptr;

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

    m_ESCpTexture = pTexture->GetAddress(texIndex);

    BindTexture(m_ESCpTexture);//�ݒ�


 //   SetpVtx(pVtx);

  //  InputpVtx();

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

    //CRenderer* pRenderer = nullptr;

    //CManager* pManager = CManager::GetInstance();

    //CInputKeyboard* keyboard = pManager->GetKeyboard();

    //CInputJoyPad* JoyPad = pManager->GetJoyPad();

    //XINPUT_STATE joykeystate;

    ////�V���C�p�b�g�̏�Ԃ��擾
    //DWORD dwResult = XInputGetState(0, &joykeystate);

    ////Mouse�ŉ�ʂɎw���Ă�3D��ԍ��W�擾
    //D3DXVECTOR3 TargetPos = keyboard->GetMouseRayIntersection(*pManager->GetCamera());




    //// �z�u���v���C�I���e�B�̐擪���擾
    //CObject* pObject = CObject::GetpTop(CObject::LAYERINDEX_MOTIONPLAYER);

    //if (pObject != nullptr)
    //{ // �擪���Ȃ�==�v���C�I���e�B�܂���ƂȂ�

    //    if (pObject->GetObjectType() == CObject::OBJECT_MOTIONPLAYER)
    //    { // �Ώۂ̃��f���̂Ƃ�

    //        D3DXVECTOR3 TarGet_Collision_Min_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    //        D3DXVECTOR3 TarGet_Collision_Max_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

    //        // �����Ŏg�p���錾
    //        CObjectMotionPlayer* pMotionPlayer;

    //        pMotionPlayer = (CObjectMotionPlayer*)pObject;


    //        m_Pos = pMotionPlayer->GetTARGETPOS();


    //    }
    //}

    ////�擾
    //DATA EscData = GetDATA();

    //EscData.Pos = m_Pos;
    ////�擾
    //SetDATA(EscData);



    m_nLife--;






    if (m_nLife <= 0)
    {
        SetDeath(true);
    }


    InputpVtx();

    //  m_nLife--;

    //m_nDelay++;

    //if (m_nDelay >= 0)
    //{
    //    m_nDelay = 0;
    //    m_nPatternAnim++;
    //}




    //if (m_nLife <= 0 || m_nPatternAnim > DIVISION_NUMBER)
    //{
    //    SetDeath(true);
    //}



    CObjectBillBoard::Update();
}
//=============================
// �`�揈��(POLYGON�`��)
//=============================
void CObjectLINEUI::Draw()
{
    //    ChengeAddDrawMode(true);
    SetZDrawDeth(true);
    for (int i = 0; i < 20; i++)
    {
        CObjectBillBoard::Draw();
    }
    SetZDrawDeth(false);
}
//=============================
// ���W�ݒ�
//=============================
void CObjectLINEUI::SetPos_Rot(D3DXVECTOR3 Pos)
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
CObjectLINEUI* CObjectLINEUI::Create(D3DXVECTOR3 Pos)
{
    CObjectLINEUI* pObject3D = new CObjectLINEUI;

    pObject3D->Init();
    pObject3D->SetPos_Rot(Pos);
    return pObject3D;
}
