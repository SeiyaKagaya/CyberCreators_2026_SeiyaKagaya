//=======================================================
//
// Game_UI�Ɋւ��鏈��[Game_UI.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "Game_UI.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "all_texture.h"
#include "font.h"


//=============================
// �R���X�g���N�^
//=============================
CGameUI::CGameUI(int nPriority) :CObject(nPriority)
{
    for (int nCnt = 0; nCnt < TEXNUM; nCnt++)
    {
        m_nTexIdx[nCnt] = 0;
        m_pVtxBuff[nCnt] = nullptr;
        m_pTexture[nCnt] = nullptr;
    }

    m_Pos[0] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
    m_Pos[1] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
    m_Pos[2] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);

    SetObjectType(OBJECT_GAMEUI);
}

//=============================
// �f�X�g���N�^
//=============================
CGameUI::~CGameUI()
{
    Uninit();
}

//=============================
// �����ݒ�(���_�o�b�t�@����)
//=============================
HRESULT CGameUI::Init()
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

        m_pTexture[nCnt] = nullptr;

        // �����ݒ�
        VERTEX_2D* pVtx;

        switch (nCnt)
        {
        case 0:
            m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

            m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 40.0f, SCREEN_HEIGHT * 0.5f + 330.0f, 0.0f);

            pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 125.0f, m_Pos[nCnt].y - 30.0f, 0.0f);
            pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 125.0f, m_Pos[nCnt].y - 30.0f, 0.0f);
            pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 125.0f, m_Pos[nCnt].y + 30.0f, 0.0f);
            pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 125.0f, m_Pos[nCnt].y + 30.0f, 0.0f);

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

        case 1:

            m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

            m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 490.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f);

            pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 130.0f, m_Pos[nCnt].y - 35.0f, 0.0f);
            pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 130.0f, m_Pos[nCnt].y - 35.0f, 0.0f);
            pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 130.0f, m_Pos[nCnt].y + 35.0f, 0.0f);
            pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 130.0f, m_Pos[nCnt].y + 35.0f, 0.0f);

            pVtx[0].rhw = 1.0f;
            pVtx[1].rhw = 1.0f;
            pVtx[2].rhw = 1.0f;
            pVtx[3].rhw = 1.0f;

            pVtx[0].col = D3DCOLOR_RGBA(55, 55, 55, 155);
            pVtx[1].col = D3DCOLOR_RGBA(55, 55, 55, 155);
            pVtx[2].col = D3DCOLOR_RGBA(55, 55, 55, 155);
            pVtx[3].col = D3DCOLOR_RGBA(55, 55, 55, 155);

            pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
            pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
            pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
            pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

            m_pVtxBuff[nCnt]->Unlock();

            break;

        case 2:

            m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

            m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f - 340.0f, 0.0f);

            pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 115.0f, m_Pos[nCnt].y - 35.0f, 0.0f);
            pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 115.0f, m_Pos[nCnt].y - 35.0f, 0.0f);
            pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 115.0f, m_Pos[nCnt].y + 35.0f, 0.0f);
            pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 115.0f, m_Pos[nCnt].y + 35.0f, 0.0f);

            pVtx[0].rhw = 1.0f;
            pVtx[1].rhw = 1.0f;
            pVtx[2].rhw = 1.0f;
            pVtx[3].rhw = 1.0f;

            pVtx[0].col = D3DCOLOR_RGBA(55, 55, 55, 155);
            pVtx[1].col = D3DCOLOR_RGBA(55, 55, 55, 155);
            pVtx[2].col = D3DCOLOR_RGBA(55, 55, 55, 155);
            pVtx[3].col = D3DCOLOR_RGBA(55, 55, 55, 155);

            pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
            pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
            pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
            pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

            m_pVtxBuff[nCnt]->Unlock();
            break;

        case 3:

            m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

            m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 525.0f, SCREEN_HEIGHT * 0.5f - 340.0f, 0.0f);

            pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 125.0f, m_Pos[nCnt].y - 35.0f, 0.0f);
            pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 125.0f, m_Pos[nCnt].y - 35.0f, 0.0f);
            pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 125.0f, m_Pos[nCnt].y + 35.0f, 0.0f);
            pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 125.0f, m_Pos[nCnt].y + 35.0f, 0.0f);

            pVtx[0].rhw = 1.0f;
            pVtx[1].rhw = 1.0f;
            pVtx[2].rhw = 1.0f;
            pVtx[3].rhw = 1.0f;

            pVtx[0].col = D3DCOLOR_RGBA(55, 55, 55, 155);
            pVtx[1].col = D3DCOLOR_RGBA(55, 55, 55, 155);
            pVtx[2].col = D3DCOLOR_RGBA(55, 55, 55, 155);
            pVtx[3].col = D3DCOLOR_RGBA(55, 55, 55, 155);

            pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
            pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
            pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
            pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

            m_pVtxBuff[nCnt]->Unlock();
            break;

        case 4:
            
            m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

            m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 225.0f, SCREEN_HEIGHT * 0.5f + 320.0f, 0.0f);

            pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 100.0f, m_Pos[nCnt].y - 40.0f, 0.0f);
            pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 100.0f, m_Pos[nCnt].y - 40.0f, 0.0f);
            pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 100.0f, m_Pos[nCnt].y + 40.0f, 0.0f);
            pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 100.0f, m_Pos[nCnt].y + 40.0f, 0.0f);

            pVtx[0].rhw = 1.0f;
            pVtx[1].rhw = 1.0f;
            pVtx[2].rhw = 1.0f;
            pVtx[3].rhw = 1.0f;

            pVtx[0].col = D3DCOLOR_RGBA(55, 55, 55, 155);
            pVtx[1].col = D3DCOLOR_RGBA(55, 55, 55, 155);
            pVtx[2].col = D3DCOLOR_RGBA(55, 55, 55, 155);
            pVtx[3].col = D3DCOLOR_RGBA(55, 55, 55, 155);

            pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
            pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
            pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
            pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

            m_pVtxBuff[nCnt]->Unlock();
            break;


        case 5:
            m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

            m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 350.0f, SCREEN_HEIGHT * 0.5f + 320.0f, 0.0f);

            pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 150.0f, m_Pos[nCnt].y - 40.0f, 0.0f);
            pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 300.0f, m_Pos[nCnt].y - 40.0f, 0.0f);
            pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 150.0f, m_Pos[nCnt].y + 40.0f, 0.0f);
            pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 300.0f, m_Pos[nCnt].y + 40.0f, 0.0f);

            pVtx[0].rhw = 1.0f;
            pVtx[1].rhw = 1.0f;
            pVtx[2].rhw = 1.0f;
            pVtx[3].rhw = 1.0f;

            pVtx[0].col = D3DCOLOR_RGBA(55, 55, 55, 155);
            pVtx[1].col = D3DCOLOR_RGBA(55, 55, 55, 155);
            pVtx[2].col = D3DCOLOR_RGBA(55, 55, 55, 155);
            pVtx[3].col = D3DCOLOR_RGBA(55, 55, 55, 155);

            pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
            pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
            pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
            pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

            m_pVtxBuff[nCnt]->Unlock();
            break;

        case 6:
            //�e�N�X�`���̓ǂݍ���
            D3DXCreateTextureFromFile(EscDevice, "DATA\\TEXTURE\\WASD.png", &m_pTexture[nCnt]);//�ʏ펞

            m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

            m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 275.0f, SCREEN_HEIGHT * 0.5f + 325.0f, 0.0f);

            pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 60.0f, m_Pos[nCnt].y - 55.0f, 0.0f);
            pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 60.0f, m_Pos[nCnt].y - 55.0f, 0.0f);
            pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 60.0f, m_Pos[nCnt].y + 55.0f, 0.0f);
            pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 60.0f, m_Pos[nCnt].y + 55.0f, 0.0f);

            pVtx[0].rhw = 1.0f;
            pVtx[1].rhw = 1.0f;
            pVtx[2].rhw = 1.0f;
            pVtx[3].rhw = 1.0f;

            pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
            pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
            pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
            pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

            pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
            pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
            pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
            pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

            m_pVtxBuff[nCnt]->Unlock();
            break;

        case 7:
            //�e�N�X�`���̓ǂݍ���
            D3DXCreateTextureFromFile(EscDevice, "DATA\\TEXTURE\\mouth.png", &m_pTexture[nCnt]);//�ʏ펞

            m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

            m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 280.0f, SCREEN_HEIGHT * 0.5f + 325.0f, 0.0f);

            pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 60.0f, m_Pos[nCnt].y - 55.0f, 0.0f);
            pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 60.0f, m_Pos[nCnt].y - 55.0f, 0.0f);
            pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 60.0f, m_Pos[nCnt].y + 55.0f, 0.0f);
            pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 60.0f, m_Pos[nCnt].y + 55.0f, 0.0f);


            pVtx[0].rhw = 1.0f;
            pVtx[1].rhw = 1.0f;
            pVtx[2].rhw = 1.0f;
            pVtx[3].rhw = 1.0f;

            pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
            pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
            pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
            pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

            pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
            pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
            pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
            pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

            m_pVtxBuff[nCnt]->Unlock();
            break;

        case 8:
            //�e�N�X�`���̓ǂݍ���
            D3DXCreateTextureFromFile(EscDevice, "DATA\\TEXTURE\\mouth_click2.png", &m_pTexture[nCnt]);//�ʏ펞

            m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

            m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 500.0f, SCREEN_HEIGHT * 0.5f + 325.0f, 0.0f);

            pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 60.0f, m_Pos[nCnt].y - 55.0f, 0.0f);
            pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 60.0f, m_Pos[nCnt].y - 55.0f, 0.0f);
            pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 60.0f, m_Pos[nCnt].y + 55.0f, 0.0f);
            pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 60.0f, m_Pos[nCnt].y + 55.0f, 0.0f);

            pVtx[0].rhw = 1.0f;
            pVtx[1].rhw = 1.0f;
            pVtx[2].rhw = 1.0f;
            pVtx[3].rhw = 1.0f;

            pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
            pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
            pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
            pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

            pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
            pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
            pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
            pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

            m_pVtxBuff[nCnt]->Unlock();
            break;

        case 9:
            //�e�N�X�`���̓ǂݍ���
            D3DXCreateTextureFromFile(EscDevice, "DATA\\TEXTURE\\ComLeft.png", &m_pTexture[nCnt]);//�ʏ펞

            m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

            m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 275.0f, SCREEN_HEIGHT * 0.5f + 315.0f, 0.0f);

            pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 48.0f, m_Pos[nCnt].y - 45.0f, 0.0f);
            pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 48.0f, m_Pos[nCnt].y - 45.0f, 0.0f);
            pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 48.0f, m_Pos[nCnt].y + 45.0f, 0.0f);
            pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 48.0f, m_Pos[nCnt].y + 45.0f, 0.0f);

            pVtx[0].rhw = 1.0f;
            pVtx[1].rhw = 1.0f;
            pVtx[2].rhw = 1.0f;
            pVtx[3].rhw = 1.0f;

            pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
            pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
            pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
            pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

            pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
            pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
            pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
            pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

            m_pVtxBuff[nCnt]->Unlock();
            break;

        case 10:
            //�e�N�X�`���̓ǂݍ���
            D3DXCreateTextureFromFile(EscDevice, "DATA\\TEXTURE\\ComRight.png", &m_pTexture[nCnt]);//�ʏ펞

            m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

            m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 250.0f, SCREEN_HEIGHT * 0.5f + 315.0f, 0.0f);

            pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 48.0f, m_Pos[nCnt].y - 40.0f, 0.0f);
            pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 48.0f, m_Pos[nCnt].y - 40.0f, 0.0f);
            pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 48.0f, m_Pos[nCnt].y + 40.0f, 0.0f);
            pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 48.0f, m_Pos[nCnt].y + 40.0f, 0.0f);


            pVtx[0].rhw = 1.0f;
            pVtx[1].rhw = 1.0f;
            pVtx[2].rhw = 1.0f;
            pVtx[3].rhw = 1.0f;

            pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
            pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
            pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
            pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

            pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
            pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
            pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
            pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

            m_pVtxBuff[nCnt]->Unlock();
            break;
        case 11:
            //�e�N�X�`���̓ǂݍ���
            D3DXCreateTextureFromFile(EscDevice, "DATA\\TEXTURE\\ComTriger.png", &m_pTexture[nCnt]);//�ʏ펞

            m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

            m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 480.0f, SCREEN_HEIGHT * 0.5f + 328.0f, 0.0f);

            pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 60.0f, m_Pos[nCnt].y - 60.0f, 0.0f);
            pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 60.0f, m_Pos[nCnt].y - 60.0f, 0.0f);
            pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 60.0f, m_Pos[nCnt].y + 60.0f, 0.0f);
            pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 60.0f, m_Pos[nCnt].y + 60.0f, 0.0f);


            pVtx[0].rhw = 1.0f;
            pVtx[1].rhw = 1.0f;
            pVtx[2].rhw = 1.0f;
            pVtx[3].rhw = 1.0f;

            pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
            pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
            pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
            pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

            pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
            pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
            pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
            pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

            m_pVtxBuff[nCnt]->Unlock();
            break;


        case 12:

            m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

            m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 480.0f, SCREEN_HEIGHT * 0.5f + 328.0f, 0.0f);

            pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 110.0f, m_Pos[nCnt].y - 40.0f, 0.0f);
            pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 110.0f, m_Pos[nCnt].y - 40.0f, 0.0f);
            pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 110.0f, m_Pos[nCnt].y + 40.0f, 0.0f);
            pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 110.0f, m_Pos[nCnt].y + 40.0f, 0.0f);


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


        case 13:
            //�e�N�X�`���̓ǂݍ���
            D3DXCreateTextureFromFile(EscDevice, "DATA\\TEXTURE\\SPACE.png", &m_pTexture[nCnt]);//�ʏ펞

            m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

            m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 530.0f, SCREEN_HEIGHT * 0.5f + 325.0f, 0.0f);

            pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 60.0f, m_Pos[nCnt].y - 25.0f, 0.0f);
            pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 60.0f, m_Pos[nCnt].y - 25.0f, 0.0f);
            pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 60.0f, m_Pos[nCnt].y + 25.0f, 0.0f);
            pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 60.0f, m_Pos[nCnt].y + 25.0f, 0.0f);


            pVtx[0].rhw = 1.0f;
            pVtx[1].rhw = 1.0f;
            pVtx[2].rhw = 1.0f;
            pVtx[3].rhw = 1.0f;

            pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
            pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
            pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
            pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

            pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
            pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
            pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
            pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

            m_pVtxBuff[nCnt]->Unlock();
            break;


        case 14:
            //�e�N�X�`���̓ǂݍ���
            D3DXCreateTextureFromFile(EscDevice, "DATA\\TEXTURE\\start.png", &m_pTexture[nCnt]);//�ʏ펞

            m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

            m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 530.0f, SCREEN_HEIGHT * 0.5f + 325.0f, 0.0f);

            pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 30.0f, m_Pos[nCnt].y - 25.0f, 0.0f);
            pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 30.0f, m_Pos[nCnt].y - 25.0f, 0.0f);
            pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 30.0f, m_Pos[nCnt].y + 25.0f, 0.0f);
            pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 30.0f, m_Pos[nCnt].y + 25.0f, 0.0f);


            pVtx[0].rhw = 1.0f;
            pVtx[1].rhw = 1.0f;
            pVtx[2].rhw = 1.0f;
            pVtx[3].rhw = 1.0f;

            pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
            pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
            pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
            pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

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
void CGameUI::Uninit()
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
void CGameUI::Update()
{  
}

//=============================
// �`�揈��(POLYGON�`��)
//=============================
void CGameUI::Draw()
{
    CScene::MODE NowState = CScene::GetNowScene();

    if (NowState != CScene::MODE_TITLE && NowState != CScene::MODE_RESULT)
    {//�^�C�g��
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

            case 1:
                hr = EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

                break;

            case 2:
                hr = EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

                break;

            case 3:
                hr = EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

                break;

            case 4:
                hr = EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

                break;

            case 5:

                hr = EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

                break;

            case 6://WASD

                if (pManager->bGetInputState() == false)
                {//������@--true�ŃR���g���[���[
                    hr = EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
                }
                break;
            case 7://�}�E�X
                if (pManager->bGetInputState() == false)
                {//������@--true�ŃR���g���[���[
                    hr = EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
                }
                break;
            case 8://�}�E�X
                if (pManager->bGetInputState() == false)
                {//������@--true�ŃR���g���[���[
                    hr = EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
                }
                break;

            case 9://�R���g���[����

                if (pManager->bGetInputState() == true)
                {//������@--true�ŃR���g���[���[

                    hr = EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
                }
                break;
            case 10://�R���g���[���E

                if (pManager->bGetInputState() == true)
                {//������@--true�ŃR���g���[���[

                    hr = EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
                }
                break;
            case 11://�R���g���[�����C

                if (pManager->bGetInputState() == true)
                {//������@--true�ŃR���g���[���[


                    hr = EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
                }
                break;

            case 12://�R���g���[�����C


                hr = EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

                break;


            case 13://�R���g���[�����C

                if (pManager->bGetInputState() == false)
                {//������@--true�ŃR���g���[���[
                    hr = EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
                }
                break;


            case 14://�R���g���[�����C

                if (pManager->bGetInputState() == true)
                {//������@--true�ŃR���g���[���[
                    hr = EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
                }
                break;
            }

            EscDevice->SetTexture(0, nullptr);

        }

        const char* aData = "�ړ�";
        CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 220.0f, SCREEN_HEIGHT / 2.0f + 300.0f, 0.0f), 50, CFont::FONT_SOUKOUMINCHO, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData);

        aData = "�Ə�";
        CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 310.0f, SCREEN_HEIGHT / 2.0f + 300.0f, 0.0f), 50, CFont::FONT_SOUKOUMINCHO, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData);

        aData = "���C";
        CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 547.0f, SCREEN_HEIGHT / 2.0f + 300.0f, 0.0f), 50, CFont::FONT_SOUKOUMINCHO, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData);

        aData = "PAUSE";
        CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 467.0f, SCREEN_HEIGHT / 2.0f + 310.0f, 0.0f), 30, CFont::FONT_SOUKOUMINCHO, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData);

    }
}

//=============================
// Object����
//=============================
CGameUI* CGameUI::Create()
{
    CGameUI* pObject = new CGameUI;
    pObject->Init();
    return pObject;
}