//=======================================================
//
// GameStayUI�Ɋւ��鏈��[GameStayUI.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "GameStayUI.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "all_texture.h"
#include "font.h"

//=============================
// �R���X�g���N�^
//=============================
CStayUI::CStayUI()
{
    for (int nCnt = 0; nCnt < TEXNUM; nCnt++)
    {
        m_nTexIdx[nCnt] = 0;
        m_pVtxBuff[nCnt] = nullptr;
        m_pTexture[nCnt] = nullptr;
    }
}

//=============================
// �f�X�g���N�^
//=============================
CStayUI::~CStayUI()
{
    Uninit();
}

//=============================
// �����ݒ�(���_�o�b�t�@����)
//=============================
HRESULT CStayUI::Init()
{
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
            D3DXCreateTextureFromFile(EscDevice, "DATA\\TEXTURE\\Green.png", &m_pTexture[nCnt]);//�ʏ펞

            m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

            m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);

            pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - (SCREEN_WIDTH * 0.5f), m_Pos[nCnt].y - (SCREEN_HEIGHT * 0.5f), 0.0f);
            pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + (SCREEN_WIDTH * 0.5f), m_Pos[nCnt].y - (SCREEN_HEIGHT * 0.5f), 0.0f);
            pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - (SCREEN_WIDTH * 0.5f), m_Pos[nCnt].y + (SCREEN_HEIGHT * 0.5f), 0.0f);
            pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + (SCREEN_WIDTH * 0.5f), m_Pos[nCnt].y + (SCREEN_HEIGHT * 0.5f), 0.0f);

            pVtx[0].rhw = 1.0f;
            pVtx[1].rhw = 1.0f;
            pVtx[2].rhw = 1.0f;
            pVtx[3].rhw = 1.0f;

            pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 155);
            pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 155);
            pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 155);
            pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 155);

            pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
            pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
            pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
            pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

            m_pVtxBuff[nCnt]->Unlock();
            break;

        case 1:
            //�e�N�X�`���̓ǂݍ���
            D3DXCreateTextureFromFile(EscDevice, "DATA\\TEXTURE\\Yellow.png", &m_pTexture[nCnt]);//�ʏ펞


            m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

            m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);

            pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - (SCREEN_WIDTH * 0.5f), m_Pos[nCnt].y - (SCREEN_HEIGHT * 0.5f), 0.0f);
            pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + (SCREEN_WIDTH * 0.5f), m_Pos[nCnt].y - (SCREEN_HEIGHT * 0.5f), 0.0f);
            pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - (SCREEN_WIDTH * 0.5f), m_Pos[nCnt].y + (SCREEN_HEIGHT * 0.5f), 0.0f);
            pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + (SCREEN_WIDTH * 0.5f), m_Pos[nCnt].y + (SCREEN_HEIGHT * 0.5f), 0.0f);

            pVtx[0].rhw = 1.0f;
            pVtx[1].rhw = 1.0f;
            pVtx[2].rhw = 1.0f;
            pVtx[3].rhw = 1.0f;

            pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 155);
            pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 155);
            pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 155);
            pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 155);

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
void CStayUI::Uninit()
{
    for (int nCnt = 0; nCnt < TEXNUM; nCnt++)
    {
        if (m_pVtxBuff[nCnt] != nullptr)
        {
            m_pVtxBuff[nCnt]->Release();
            m_pVtxBuff[nCnt] = nullptr;
        }
        if (m_pTexture[nCnt] != nullptr)
        {
                m_pTexture[nCnt]->Release();
            m_pTexture[nCnt] = nullptr;
        }
    }
}

//=============================
// �X�V(���_���̍X�V)
//=============================
void CStayUI::Update()
{
}

//=============================
// �`�揈��(POLYGON�`��)
//=============================
void CStayUI::Draw()
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
        
        if (pManager->GetEndStatusState() == true)
        {//�N���ARoute
            switch (nCnt)
            {
            case 0://�w�i
                hr = EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
                break;
            case 1://�w�i

                break;
            }

            char aData2[100];

            snprintf(aData2, sizeof(aData2), "�X�e�[�W�N���A�I�I"); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[

            CFont::DrawTextSet(SETPOS[0], 100, CFont::FONT_KEIFONT, D3DXCOLOR(0.2f, 1.0f, 0.2f, 1.0f), aData2);
        }
        else
        {
            switch (nCnt)
            {
            case 0://�w�i
      
                break;
            case 1://�w�i
                hr = EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
                break;
            }
            char aData2[100];

            snprintf(aData2, sizeof(aData2), "�s�k�I�I"); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[

            CFont::DrawTextSet(SETPOS[1], 100, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f), aData2);
        }

        EscDevice->SetTexture(0, nullptr);
    }
}

//=============================
// Object����
//=============================
CStayUI* CStayUI::Create()
{
    CStayUI* pObject = new CStayUI;
    pObject->Init();
    return pObject;
}