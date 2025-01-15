//=======================================================
//
// result�Ɋւ��鏈��[result.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "result.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "all_texture.h"
#include "font.h"


//=============================
// �R���X�g���N�^
//=============================
CResultUI::CResultUI(int nPriority) :CObject(nPriority)
{

    for (int nCnt = 0; nCnt < TEXNUM; nCnt++)
    {
        m_nTexIdx[nCnt] = 0;
        m_pVtxBuff[nCnt] = nullptr;
        m_pTexture[nCnt] = nullptr;
    }


    
    SetObjectType(OBJECT_GAMEUI);

}
//=============================
// �f�X�g���N�^
//=============================
CResultUI::~CResultUI()
{
    Uninit();
}
//=============================
// �����ݒ�(���_�o�b�t�@����)
//=============================
HRESULT CResultUI::Init()
{
    // �}�E�X�J�[�\����\���ɂ���
 //   ShowCursor(TRUE);

    CRenderer* pRenderer = nullptr;

    CManager* pManager = CManager::GetInstance();

    pRenderer = pManager->GetRenderer();


    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

    for (int nCnt = 0; nCnt < TEXNUM; nCnt++)
    {
        if (FAILED(EscDevice->CreateVertexBuffer(
            sizeof(VERTEX_2D) * 4,
            D3DUSAGE_WRITEONLY,
            FVF_VERTEX_2D,
            D3DPOOL_MANAGED,
            &m_pVtxBuff[nCnt],
            nullptr)))
        {
            return E_FAIL;
        }


        // �����ݒ�
        VERTEX_2D* pVtx;


        switch (nCnt)
        {
        case 0:
            //�e�N�X�`���̓ǂݍ���
        //    D3DXCreateTextureFromFile(EscDevice, "DATA\\TEXTURE\\yuka.jpg", &m_pTexture[nCnt]);//�ʏ펞


            m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

            m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f , SCREEN_HEIGHT * 0.5f, 0.0f);

            pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - (SCREEN_WIDTH * 0.5f - 50.0f), m_Pos[nCnt].y - (SCREEN_HEIGHT * 0.5f - 25.0f), 0.0f);
            pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + (SCREEN_WIDTH * 0.5f - 50.0f), m_Pos[nCnt].y - (SCREEN_HEIGHT * 0.5f - 25.0f), 0.0f);
            pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - (SCREEN_WIDTH * 0.5f - 50.0f), m_Pos[nCnt].y + (SCREEN_HEIGHT * 0.5f - 25.0f), 0.0f);
            pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + (SCREEN_WIDTH * 0.5f - 50.0f), m_Pos[nCnt].y + (SCREEN_HEIGHT * 0.5f - 25.0f), 0.0f);

            pVtx[0].rhw = 1.0f;
            pVtx[1].rhw = 1.0f;
            pVtx[2].rhw = 1.0f;
            pVtx[3].rhw = 1.0f;

            pVtx[0].col = D3DCOLOR_RGBA(25, 25, 25, 155);
            pVtx[1].col = D3DCOLOR_RGBA(25, 25, 25, 155);
            pVtx[2].col = D3DCOLOR_RGBA(25, 25, 25, 155);
            pVtx[3].col = D3DCOLOR_RGBA(25, 25, 25, 155);

            pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
            pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
            pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
            pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

            m_pVtxBuff[nCnt]->Unlock();
            break;

    

        }





    }
    return S_OK;
}
//=============================
// �I������(���_�o�b�t�@�j��)
//=============================
void CResultUI::Uninit()
{
    // �}�E�X�J�[�\�����\���ɂ���
//    ShowCursor(FALSE);

    for (int nCnt = 0; nCnt < TEXNUM; nCnt++)
    {
        if (m_pVtxBuff[nCnt] != nullptr)
        {
            m_pVtxBuff[nCnt]->Release();
            m_pVtxBuff[nCnt] = nullptr;
        }
        if (m_pTexture[nCnt] != nullptr)
        {
            m_pTexture[nCnt]->Release();//-----�e�N�X�`��cpp�ł�邱��
            m_pTexture[nCnt] = nullptr;
        }
    }
}
//=============================
// �X�V(���_���̍X�V)
//=============================
void CResultUI::Update()
{


}
//=============================
// �`�揈��(POLYGON�`��)
//=============================
void CResultUI::Draw()
{
    CRenderer* pRenderer = nullptr;

    CManager* pManager = CManager::GetInstance();

    pRenderer = pManager->GetRenderer();


    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();


    for (int nCnt = 0; nCnt < TEXNUM; nCnt++)
    {
        EscDevice->SetStreamSource(0, m_pVtxBuff[nCnt], 0, sizeof(VERTEX_2D));
        EscDevice->SetFVF(FVF_VERTEX_2D);

        if (m_pTexture != nullptr)
        {
            EscDevice->SetTexture(0, m_pTexture[nCnt]);
        }
        else
        {
            EscDevice->SetTexture(0, nullptr);
        }

        HRESULT hr = {};


        XINPUT_STATE joykeystate;
        //�V���C�p�b�g�̏�Ԃ��擾
        DWORD dwResult = XInputGetState(0, &joykeystate);


        switch (nCnt)
        {
        case 0://�w�i
            hr = EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
            break;

    
        }





        EscDevice->SetTexture(0, nullptr);

    }



}
//=============================
// Object����
//=============================
CResultUI* CResultUI::Create()
{
    CResultUI* pObject = new CResultUI;
    pObject->Init();
    return pObject;
}
