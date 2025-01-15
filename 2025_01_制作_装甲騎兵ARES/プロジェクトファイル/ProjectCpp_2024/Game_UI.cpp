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
#include "player_motion.h"



//���₵��cpp�̂���Ƃ��ɂ�����
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

//=============================
// �R���X�g���N�^
//=============================
CGameUI::CGameUI(int nPriority) :CObject(nPriority)
{
    m_MapNum = 0;

    for (int nCnt = 0; nCnt < UI_MAX; nCnt++)
    {
        m_nTexIdx[nCnt] = 0;
        m_pVtxBuff[nCnt] = nullptr;
        m_pTexture[nCnt] = nullptr;

        //m_pVtxBuff[nCnt] = nullptr;//���_�o�b�t�@

        m_nTexIdx[nCnt] = 0;

        //m_pTexture[nCnt] = nullptr;

       
        //�^�C�v�i�[
        m_UiType[nCnt]=(UITYPE)0;

        m_UiState[nCnt]= UISTATE_OFFLINE_NOW;

        m_Pos[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        m_Size[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

        m_nMotionCnt[nCnt] = 0;//���[�V��������

         m_nMotionDelayCnt[nCnt] = 0;//�x��ĒǑ�

         m_nMotionDalay[nCnt] = 0;

         m_fLength[nCnt] = 0;//�Q�[�W�݂̗̂��p

         m_nWeponUIDrawA[nCnt] = 0;
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
    // �}�E�X�J�[�\����\���ɂ���
 //   ShowCursor(TRUE);

    CRenderer* pRenderer = nullptr;

    CManager* pManager = CManager::GetInstance();

    pRenderer = pManager->GetRenderer();


    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

    for (int nCnt = 0; nCnt < UI_MAX; nCnt++)
    {
        m_nMotionCnt[nCnt] = 0;
        m_nMotionDelayCnt[nCnt]=0;//�x��ĒǑ�

        m_nMotionDalay[nCnt]=0;


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

            m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

            pVtx[0].rhw = 1.0f;
            pVtx[1].rhw = 1.0f;
            pVtx[2].rhw = 1.0f;
            pVtx[3].rhw = 1.0f;

            pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 0);
            pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 0);
            pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 0);
            pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 0);

            pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
            pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
            pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
            pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

            switch (nCnt)
            {

            case UI_NOMAL:

                //����
                m_UiType[UI_NOMAL] = UI_NOMAL;

                m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 270.0f, SCREEN_HEIGHT * 0.5f - 340.0f, 0.0f);

                pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 115.0f, m_Pos[nCnt].y - 35.0f, 0.0f);
                pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 115.0f, m_Pos[nCnt].y - 35.0f, 0.0f);
                pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 115.0f, m_Pos[nCnt].y + 35.0f, 0.0f);
                pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 115.0f, m_Pos[nCnt].y + 35.0f, 0.0f);

                break;

            case UI_NOMAL2:

                //score
                m_UiType[UI_NOMAL2] = UI_NOMAL2;

                m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 525.0f, SCREEN_HEIGHT * 0.5f - 340.0f, 0.0f);

                pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 125.0f, m_Pos[nCnt].y - 35.0f, 0.0f);
                pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 125.0f, m_Pos[nCnt].y - 35.0f, 0.0f);
                pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 125.0f, m_Pos[nCnt].y + 35.0f, 0.0f);
                pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 125.0f, m_Pos[nCnt].y + 35.0f, 0.0f);
                break;

            case UI_MAP:
                m_MapNum = UI_MAP;
                //�}�b�v
                m_UiType[UI_MAP] = UI_MAP;

                //�e�N�X�`���̓ǂݍ���
                D3DXCreateTextureFromFile(EscDevice, "DATA\\TEXTURE\\MAP1.png", &m_pTexture[nCnt]);//�ʏ펞

                m_Pos[nCnt] = D3DXVECTOR3(110.0f, 110.0f, 0.0f);

                pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 100.0f, m_Pos[nCnt].y - 100.0f, 0.0f);
                pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 100.0f, m_Pos[nCnt].y - 100.0f, 0.0f);
                pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 100.0f, m_Pos[nCnt].y + 100.0f, 0.0f);
                pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 100.0f, m_Pos[nCnt].y + 100.0f, 0.0f);

                break;

            case UI_MAP_BACK:
                //�}�b�v�w�i
                m_UiType[UI_MAP_BACK] = UI_MAP_BACK;

                m_Pos[nCnt] = D3DXVECTOR3(110.0f, 110.0f, 0.0f);

                pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 105.0f, m_Pos[nCnt].y - 105.0f, 0.0f);
                pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 105.0f, m_Pos[nCnt].y - 105.0f, 0.0f);
                pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 105.0f, m_Pos[nCnt].y + 105.0f, 0.0f);
                pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 105.0f, m_Pos[nCnt].y + 105.0f, 0.0f);
                break;

            case UI_WEPON1_BACK:
                //����UI

                m_UiType[UI_WEPON1_BACK] = UI_WEPON1_BACK;

                m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 570.0f, SCREEN_HEIGHT * 0.5f - 55.0f, 0.0f);

                pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 70.0f, m_Pos[nCnt].y - 50.0f, 0.0f);
                pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 70.0f, m_Pos[nCnt].y - 50.0f, 0.0f);
                pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 70.0f, m_Pos[nCnt].y + 50.0f, 0.0f);
                pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 70.0f, m_Pos[nCnt].y + 50.0f, 0.0f);

                break;

            case UI_WEPON1:
                //����UI�{��

                  //�e�N�X�`���̓ǂݍ���
                D3DXCreateTextureFromFile(EscDevice, "DATA\\TEXTURE\\SHIELD.png", &m_pTexture[nCnt]);//�ʏ펞

                m_UiType[UI_WEPON1] = UI_WEPON1;

                m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 540.0f, SCREEN_HEIGHT * 0.5f - 55.0f, 0.0f);

                pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 45.0f, m_Pos[nCnt].y - 45.0f, 0.0f);
                pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 45.0f, m_Pos[nCnt].y - 45.0f, 0.0f);
                pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 45.0f, m_Pos[nCnt].y + 45.0f, 0.0f);
                pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 45.0f, m_Pos[nCnt].y + 45.0f, 0.0f);

                break;


            case UI_LOAD_GAUGE_BACK_WEPON:
                //����UI

                m_UiType[UI_LOAD_GAUGE_BACK_WEPON] = UI_LOAD_GAUGE_BACK_WEPON;

                m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 570.0f, SCREEN_HEIGHT * 0.5f - 55.0f, 0.0f);

                pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 50.0f, m_Pos[nCnt].y - 5.0f, 0.0f);
                pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 60.0f, m_Pos[nCnt].y - 5.0f, 0.0f);
                pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 50.0f, m_Pos[nCnt].y + 5.0f, 0.0f);
                pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 60.0f, m_Pos[nCnt].y + 5.0f, 0.0f);

                break;
            case UI_LOAD_GAUGE_WEPON:
                //����UI
              
                m_UiType[UI_LOAD_GAUGE_WEPON] = UI_LOAD_GAUGE_WEPON;

                m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 570.0f, SCREEN_HEIGHT * 0.5f - 55.0f, 0.0f);

                m_fLength[nCnt] = 49.5f;

                pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - m_fLength[nCnt], m_Pos[nCnt].y - 4.5f, 0.0f);
                pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + m_fLength[nCnt], m_Pos[nCnt].y - 4.5f, 0.0f);
                pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - m_fLength[nCnt], m_Pos[nCnt].y + 4.5f, 0.0f);
                pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + m_fLength[nCnt], m_Pos[nCnt].y + 4.5f, 0.0f);

                break;

            case UI_WEPON2_BACK://---------------------------------------------------------------------------------
                //����UI

                m_UiType[nCnt] = UI_WEPON2_BACK;

                m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 570.0f, SCREEN_HEIGHT * 0.5f + 55.0f, 0.0f);

                pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 70.0f, m_Pos[nCnt].y - 50.0f, 0.0f);
                pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 70.0f, m_Pos[nCnt].y - 50.0f, 0.0f);
                pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 70.0f, m_Pos[nCnt].y + 50.0f, 0.0f);
                pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 70.0f, m_Pos[nCnt].y + 50.0f, 0.0f);

                break;

            case UI_WEPON2:
                //����UI�{��
               
                //�e�N�X�`���̓ǂݍ���
                D3DXCreateTextureFromFile(EscDevice, "DATA\\TEXTURE\\bullet.png", &m_pTexture[nCnt]);//�ʏ펞

                m_UiType[nCnt] = UI_WEPON2;

                m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 520.0f, SCREEN_HEIGHT * 0.5f + 55.0f, 0.0f);

                pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 15.0f, m_Pos[nCnt].y - 45.0f, 0.0f);
                pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 15.0f, m_Pos[nCnt].y - 45.0f, 0.0f);
                pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 15.0f, m_Pos[nCnt].y + 45.0f, 0.0f);
                pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 15.0f, m_Pos[nCnt].y + 45.0f, 0.0f);

                break;

            case UI_LOAD_GAUGE_BACK_WEPON2:
                //����UI

                m_UiType[nCnt] = UI_LOAD_GAUGE_BACK_WEPON2;

                m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 570.0f, SCREEN_HEIGHT * 0.5f + 55.0f, 0.0f);

                pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 50.0f, m_Pos[nCnt].y - 5.0f, 0.0f);
                pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 60.0f, m_Pos[nCnt].y - 5.0f, 0.0f);
                pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 50.0f, m_Pos[nCnt].y + 5.0f, 0.0f);
                pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 60.0f, m_Pos[nCnt].y + 5.0f, 0.0f);

                break;
            case UI_LOAD_GAUGE_WEPON2:
                //����UI

                m_UiType[nCnt] = UI_LOAD_GAUGE_WEPON2;

                m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 570.0f, SCREEN_HEIGHT * 0.5f + 55.0f, 0.0f);

                m_fLength[nCnt] = 49.5f;

                pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - m_fLength[nCnt], m_Pos[nCnt].y - 4.5f, 0.0f);
                pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + m_fLength[nCnt], m_Pos[nCnt].y - 4.5f, 0.0f);
                pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - m_fLength[nCnt], m_Pos[nCnt].y + 4.5f, 0.0f);
                pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + m_fLength[nCnt], m_Pos[nCnt].y + 4.5f, 0.0f);

                break;

            case UI_WEPON3_BACK://---------------------------------------------------------------------------------
         //����UI

                m_UiType[nCnt] = UI_WEPON3_BACK;

                m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 570.0f,  SCREEN_HEIGHT * 0.5f + 165.0f, 0.0f);

                pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 70.0f, m_Pos[nCnt].y - 50.0f, 0.0f);
                pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 70.0f, m_Pos[nCnt].y - 50.0f, 0.0f);
                pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 70.0f, m_Pos[nCnt].y + 50.0f, 0.0f);
                pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 70.0f, m_Pos[nCnt].y + 50.0f, 0.0f);

                break;

            case UI_WEPON3:
                //����UI�{��

                  //�e�N�X�`���̓ǂݍ���
                D3DXCreateTextureFromFile(EscDevice, "DATA\\TEXTURE\\missile.png", &m_pTexture[nCnt]);//�ʏ펞

                m_UiType[nCnt] = UI_WEPON3;

                m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 520.0f,  SCREEN_HEIGHT * 0.5f + 175.0f, 0.0f);

                pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 7.0f, m_Pos[nCnt].y - 35.0f, 0.0f);
                pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 7.0f, m_Pos[nCnt].y - 35.0f, 0.0f);
                pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 7.0f, m_Pos[nCnt].y + 35.0f, 0.0f);
                pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 7.0f, m_Pos[nCnt].y + 35.0f, 0.0f);

                break;


            case UI_LOAD_GAUGE_BACK_WEPON3:
                //����UI

                m_UiType[nCnt] = UI_LOAD_GAUGE_BACK_WEPON3;

                m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 570.0f,  SCREEN_HEIGHT * 0.5f + 165.0f, 0.0f);

                pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 50.0f, m_Pos[nCnt].y - 5.0f, 0.0f);
                pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 60.0f, m_Pos[nCnt].y - 5.0f, 0.0f);
                pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 50.0f, m_Pos[nCnt].y + 5.0f, 0.0f);
                pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 60.0f, m_Pos[nCnt].y + 5.0f, 0.0f);

                break;
            case UI_LOAD_GAUGE_WEPON3:
                //����UI

                m_UiType[nCnt] = UI_LOAD_GAUGE_WEPON3;

                m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 570.0f,  SCREEN_HEIGHT * 0.5f + 165.0f, 0.0f);

                m_fLength[nCnt] = 49.5f;

                pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - m_fLength[nCnt], m_Pos[nCnt].y - 4.5f, 0.0f);
                pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + m_fLength[nCnt], m_Pos[nCnt].y - 4.5f, 0.0f);
                pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - m_fLength[nCnt], m_Pos[nCnt].y + 4.5f, 0.0f);
                pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + m_fLength[nCnt], m_Pos[nCnt].y + 4.5f, 0.0f);

                break;

            case UI_LOAD_GAUGE_WEPON3_2:
                //����UI

                m_UiType[nCnt] = UI_LOAD_GAUGE_WEPON3_2;

                m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 620.0f, SCREEN_HEIGHT * 0.5f + 170.0f, 0.0f);

                m_fLength[nCnt] = CObjectMotionPlayer::RECOVERY_MISSILE * 2;

                pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x, m_Pos[nCnt].y - 4.5f, 0.0f);
                pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + m_fLength[nCnt], m_Pos[nCnt].y - 4.5f, 0.0f);
                pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x, m_Pos[nCnt].y + 4.5f, 0.0f);
                pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + m_fLength[nCnt], m_Pos[nCnt].y + 4.5f, 0.0f);

                break;

            case UI_ACTION:

                //����UI
                m_UiType[UI_ACTION] = UI_ACTION;

                m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 580.0f, SCREEN_HEIGHT * 0.5f - 100.0f, 0.0f);

                pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 65.0f, m_Pos[nCnt].y - 175.0f, 0.0f);
                pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 65.0f, m_Pos[nCnt].y - 175.0f, 0.0f);
                pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 65.0f, m_Pos[nCnt].y + 175.0f, 0.0f);
                pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 65.0f, m_Pos[nCnt].y + 175.0f, 0.0f);

                break;

            case UI_PLAYERPIN:
                 //�}�b�vplayer
                m_UiType[UI_PLAYERPIN] = UI_PLAYERPIN;

                m_Pos[nCnt] = D3DXVECTOR3(110.0f, 101.0f, 0.0f);

                pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 7.0f, m_Pos[nCnt].y - 14.0f, 0.0f);
                pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 7.0f, m_Pos[nCnt].y - 14.0f, 0.0f);
                pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 7.0f, m_Pos[nCnt].y + 10.0f, 0.0f);
                pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 7.0f, m_Pos[nCnt].y + 10.0f, 0.0f);

                break;

            case UI_TEXTWINDOW:

                //����UI
                m_UiType[UI_TEXTWINDOW] = UI_TEXTWINDOW;

                m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 260.0f, SCREEN_HEIGHT * 0.5f - 305.0f, 0.0f);

                m_fLength[nCnt] = 320.0f;

                pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - m_fLength[nCnt], m_Pos[nCnt].y - 60.0f, 0.0f);
                pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + m_fLength[nCnt], m_Pos[nCnt].y - 60.0f, 0.0f);
                pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - m_fLength[nCnt], m_Pos[nCnt].y + 60.0f, 0.0f);
                pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + m_fLength[nCnt], m_Pos[nCnt].y + 60.0f, 0.0f);

                break;

            case UI_TEXTIMAGE:

                //����UI
                m_UiType[UI_TEXTIMAGE] = UI_TEXTIMAGE;

                //�e�N�X�`���̓ǂݍ���
                D3DXCreateTextureFromFile(EscDevice, "DATA\\TEXTURE\\soundonly.png", &m_pTexture[nCnt]);//�ʏ펞

                m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 375.0f, SCREEN_HEIGHT * 0.5f - 310.0f, 0.0f);

                m_fLength[nCnt] = 70.0f;

                pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - m_fLength[nCnt], m_Pos[nCnt].y - 40.0f, 0.0f);
                pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + m_fLength[nCnt], m_Pos[nCnt].y - 40.0f, 0.0f);
                pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - m_fLength[nCnt], m_Pos[nCnt].y + 40.0f, 0.0f);
                pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + m_fLength[nCnt], m_Pos[nCnt].y + 40.0f, 0.0f);

                break;

            case UI_HP_BACK:
                //�}�b�v�w�i
                m_UiType[UI_HP_BACK] = UI_HP_BACK;

                m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.6f, SCREEN_HEIGHT - 40.0f, 0.0f);

                pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 0.0f, m_Pos[nCnt].y - 13.0f, 0.0f);
                pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + (float)CObjectMotionPlayer::START_LIFE + 5.0f, m_Pos[nCnt].y - 13.0f, 0.0f);
                pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 0.0f, m_Pos[nCnt].y + 13.0f, 0.0f);
                pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + (float)CObjectMotionPlayer::START_LIFE + 5.0f, m_Pos[nCnt].y + 13.0f, 0.0f);
                
                break;

            case UI_HP_MAIN:

                //����UI
                m_UiType[UI_HP_MAIN] = UI_HP_MAIN;

                m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.6f +2.5f, SCREEN_HEIGHT - 40.0f, 0.0f);

                m_fLength[nCnt] = (float)CObjectMotionPlayer::START_LIFE;
                
                pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x , m_Pos[nCnt].y - 10.0f, 0.0f);
                pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + m_fLength[nCnt], m_Pos[nCnt].y - 10.0f, 0.0f);
                pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x , m_Pos[nCnt].y + 10.0f, 0.0f);
                pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + m_fLength[nCnt], m_Pos[nCnt].y + 10.0f, 0.0f);

                break;


            case UI_BOOST_BACK:
                //�}�b�v�w�i
                m_UiType[UI_BOOST_BACK] = UI_BOOST_BACK;

                m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.05f, SCREEN_HEIGHT - 40.0f, 0.0f);

                pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 0.0f, m_Pos[nCnt].y - 13.0f, 0.0f);
                pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + (float)CObjectMotionPlayer::BOOST_LIFE * 2.0f + 5.0f, m_Pos[nCnt].y - 13.0f, 0.0f);
                pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 0.0f, m_Pos[nCnt].y + 13.0f, 0.0f);
                pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + (float)CObjectMotionPlayer::BOOST_LIFE * 2.0f + 5.0f, m_Pos[nCnt].y + 13.0f, 0.0f);

                break;

            case UI_BOOST_MAIN:

                //����UI
                m_UiType[UI_BOOST_MAIN] = UI_BOOST_MAIN;

                m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.05f + 2.5f, SCREEN_HEIGHT - 40.0f, 0.0f);

                m_fLength[nCnt] = (float)CObjectMotionPlayer::BOOST_LIFE * 2.0f;

                pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x, m_Pos[nCnt].y - 10.0f, 0.0f);
                pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + m_fLength[nCnt], m_Pos[nCnt].y - 10.0f, 0.0f);
                pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x, m_Pos[nCnt].y + 10.0f, 0.0f);
                pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + m_fLength[nCnt], m_Pos[nCnt].y + 10.0f, 0.0f);

                break;
            }

      
        m_pVtxBuff[nCnt]->Unlock();

    }
    AllUiRestart();
    return S_OK;
}
//=============================
// �I������(���_�o�b�t�@�j��)
//=============================
void CGameUI::Uninit()
{
    // �}�E�X�J�[�\�����\���ɂ���
//    ShowCursor(FALSE);

    for (int nCnt = 0; nCnt < UI_MAX; nCnt++)
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


  //  delete this;
}
//=============================
// �X�V(���_���̍X�V)
//=============================
void CGameUI::Update()
{
    for (int i = 0; i < UI_MAX; i++)
    {
        if (i== (int)UI_HP_MAIN)
        {
            // �v���C���[�̈ʒu���擾
            CObject* pObj = CObject::GetObjectPoint(CObject::LAYERINDEX_MOTIONPLAYER, CObject::OBJECT_MOTIONPLAYER);

            if (pObj != nullptr)
            {
                CObjectMotionPlayer* pPlayer = static_cast<CObjectMotionPlayer*>(pObj);
                m_fLength[i] = (float)pPlayer->GetLife();
                SetLifeBar(i);
            }
        }
        else if (i == (int)UI_BOOST_MAIN)
        {
            // �v���C���[�̈ʒu���擾
            CObject* pObj = CObject::GetObjectPoint(CObject::LAYERINDEX_MOTIONPLAYER, CObject::OBJECT_MOTIONPLAYER);

            if (pObj != nullptr)
            {
                CObjectMotionPlayer* pPlayer = static_cast<CObjectMotionPlayer*>(pObj);
                m_fLength[i] = (float)pPlayer->GetNowBoostLife()*2;
                SetLifeBar(i);
            }
        }
        else if (i == (int)UI_LOAD_GAUGE_WEPON3_2)
        {
            // �v���C���[�̈ʒu���擾
            CObject* pObj = CObject::GetObjectPoint(CObject::LAYERINDEX_MOTIONPLAYER, CObject::OBJECT_MOTIONPLAYER);

            if (pObj != nullptr)
            {
                CObjectMotionPlayer* pPlayer = static_cast<CObjectMotionPlayer*>(pObj);
                m_fLength[i] = (float)pPlayer->GetNowRecoveryMissileNum()*2;
                SetLifeBar(i);
            }
        }



        if (m_UiState[i]== UISTATE_ONLINE_TRIGGER)
        {//UI��Online�ɂȂ�Œ�
            OnlineTrigger(i);
        }
        else if (m_UiState[i] == UISTATE_OFFLINE_TRIGGER)
        {//UI��Offline�ɂȂ�Œ�
            OfflineTrigger(i);
        }
    }
    
        InputpVtx();//�}�b�v�`��System�̂�
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


        for (int nCnt = 0; nCnt < UI_MAX; nCnt++)
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


            
            








             if (nCnt == UI_MAP)
             {
                 // �z�u���v���C�I���e�B�̐擪���擾
                 CObject* pObject = CObject::GetpTop(CObject::LAYERINDEX_MOTIONPLAYER);

                 if (pObject != nullptr)
                 { // �擪���Ȃ�==�v���C�I���e�B�܂���ƂȂ�

                     if (pObject->GetObjectType() == CObject::OBJECT_MOTIONPLAYER)
                     { // �Ώۂ̃��f���̂Ƃ�
                         CObject::DATA EscData;

                         // �����Ŏg�p���錾
                         CObjectMotionPlayer* pMotionPlayer;

                         pMotionPlayer = (CObjectMotionPlayer*)pObject;

                         D3DXVECTOR3 PlayerPos = pMotionPlayer->GetClassData().Pos;

                         D3DXVECTOR3 GateMin = D3DXVECTOR3(-9900.0f, 0.0f, 0.0f);
                         D3DXVECTOR3 GateMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

                         if (GateMin.x <= PlayerPos.x && GateMax.x >= PlayerPos.x)
                         {
                             hr = EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
                         }
                         else
                         {
                             const char* aDataEsc = "-NoSignal-";

     
                             CFont::DrawTextSet(D3DXVECTOR3(50.0f, 110.0f, 0.0f), 25, CFont::FONT_DIGITAL, D3DXCOLOR(0.0f, 1.0f, 0.0f, (float)m_nWeponUIDrawA[UI_MAP]), aDataEsc);

                         }
                     }
                 }
             }
             else
             {
                 hr = EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
             }
        }

        const char* aData = "�ړ�";
        
        aData = "�V�[���h\n�ϋv:��";
        CFont::DrawTextSet(D3DXVECTOR3(7.0f, SCREEN_HEIGHT / 2.0f - 95.0f, 0.0f), 25, CFont::FONT_SOUKOUMINCHO, D3DXCOLOR(0.0f, 1.0f, 1.0f, (float)m_nWeponUIDrawA[UI_WEPON1]), aData);

        aData = "LB�{�^��";
        CFont::DrawTextSet(D3DXVECTOR3(7.0f, SCREEN_HEIGHT / 2.0f - 25.0f, 0.0f), 25, CFont::FONT_SOUKOUMINCHO, D3DXCOLOR(1.0f, 0.0f, 1.0f, (float)m_nWeponUIDrawA[UI_WEPON1]), aData);




        aData = "�@�֖C\n�c�e:��";
        CFont::DrawTextSet(D3DXVECTOR3(7.0f, SCREEN_HEIGHT / 2.0f + 15.0f, 0.0f), 25, CFont::FONT_SOUKOUMINCHO, D3DXCOLOR(0.0f, 1.0f, 1.0f, (float)m_nWeponUIDrawA[UI_WEPON2]), aData);

        aData = "RT�{�^��";
        CFont::DrawTextSet(D3DXVECTOR3(7.0f, SCREEN_HEIGHT / 2.0f + 80.0f, 0.0f), 25, CFont::FONT_SOUKOUMINCHO, D3DXCOLOR(1.0f, 0.0f, 1.0f, (float)m_nWeponUIDrawA[UI_WEPON2]), aData);



        char cData2[100] = {};
        snprintf(cData2, sizeof(cData2), "�c�@�F%d                           HP", CObjectMotionPlayer::GetPlayerNum()); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[
        // mousePos.x �� mousePos.y ���}�E�X�̈ʒu
        CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH-500.0f, SCREEN_HEIGHT - 80.0f, 0.0f), 30, CFont::FONT_SOUKOUMINCHO, D3DXCOLOR(1.0f, 0.0f, 0.0f, (float)m_nWeponUIDrawA[UI_WEPON1]), cData2);


        snprintf(cData2, sizeof(cData2), "ENERGY"); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[
       // mousePos.x �� mousePos.y ���}�E�X�̈ʒu
        CFont::DrawTextSet(D3DXVECTOR3(70.0f, SCREEN_HEIGHT - 80.0f, 0.0f), 30, CFont::FONT_SOUKOUMINCHO, D3DXCOLOR(1.0f, 0.0f, 1.0f, (float)m_nWeponUIDrawA[UI_WEPON1]), cData2);



        // �z�u���v���C�I���e�B�̐擪���擾
        CObject* pObject = CObject::GetpTop(CObject::LAYERINDEX_MOTIONPLAYER);

        CObject::DATA EscData = CObject::DataInit();

        int nMissileCnt = 0;
        int nMissileRecoveryCnt = 0;

        if (pObject != nullptr)
        { // �擪���Ȃ�==�v���C�I���e�B�܂���ƂȂ�

            int nIndex = 0;

            while (pObject != nullptr)
            {

                if (pObject->GetObjectType() == CObject::OBJECT_MOTIONPLAYER)
                { // �Ώۂ̃��f���̂Ƃ�

                    // �����Ŏg�p���錾
                    CObjectMotionPlayer* pMotionPlayer;

                    pMotionPlayer = (CObjectMotionPlayer*)pObject;

                    EscData = pMotionPlayer->GetClassData();
                    nMissileCnt = pMotionPlayer->GetNowMissileNum();
                    nMissileRecoveryCnt = pMotionPlayer->GetNowRecoveryMissileNum();
                    break;
                }
            }
        }



        if (pManager->GetbNow3DMode() == false)
        {//2D
            char SetWord[1000] = {};
            snprintf(SetWord, sizeof(SetWord), "�~�T�C��\n�c�e�F%d/%d", nMissileCnt, (int)CObjectMotionPlayer::MISSILEMAX); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[

            CFont::DrawTextSet(D3DXVECTOR3(7.0f, SCREEN_HEIGHT / 2.0f + 120.0f, 0.0f), 25, CFont::FONT_SOUKOUMINCHO, D3DXCOLOR(0.0f, 1.0f, 1.0f, (float)m_nWeponUIDrawA[UI_WEPON3]), SetWord);

            aData = "�g�p�s��";
            CFont::DrawTextSet(D3DXVECTOR3(7.0f, SCREEN_HEIGHT / 2.0f + 185.0f, 0.0f), 25, CFont::FONT_SOUKOUMINCHO, D3DXCOLOR(1.0f, 0.0f, 1.0f, (float)m_nWeponUIDrawA[UI_WEPON3]), aData);

        }
        else
        {//3D
            char SetWord[1000] = {};
            snprintf(SetWord, sizeof(SetWord), "�~�T�C��\n�c�e�F%d/%d", nMissileCnt, (int)CObjectMotionPlayer::MISSILEMAX); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[

            CFont::DrawTextSet(D3DXVECTOR3(7.0f, SCREEN_HEIGHT / 2.0f + 120.0f, 0.0f), 25, CFont::FONT_SOUKOUMINCHO, D3DXCOLOR(0.0f, 1.0f, 1.0f, (float)m_nWeponUIDrawA[UI_WEPON3]), SetWord);

            aData = "RB�{�^��";
            CFont::DrawTextSet(D3DXVECTOR3(7.0f, SCREEN_HEIGHT / 2.0f + 185.0f, 0.0f), 25, CFont::FONT_SOUKOUMINCHO, D3DXCOLOR(1.0f, 0.0f, 1.0f, (float)m_nWeponUIDrawA[UI_WEPON3]), aData);

        }







        //aData = "�e�X�g�}�b�v";
        //CFont::DrawTextSet(D3DXVECTOR3(10.0f, SCREEN_HEIGHT / 2.0f - 280.0f, 0.0f), 35, CFont::FONT_SOUKOUMINCHO, D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.55f), aData);

      //  aData = "��{\n����UI\n����";
     //   CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH-110.0f, SCREEN_HEIGHT / 2.0f - 160.0f, 0.0f), 35, CFont::FONT_SOUKOUMINCHO, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), aData);
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
//=============================
// ���_���
//=============================
void CGameUI::InputpVtx()
{
    // �z�u���v���C�I���e�B�̐擪���擾
    CObject* pObject = CObject::GetpTop(CObject::LAYERINDEX_MOTIONPLAYER);

    CObject::DATA EscData=CObject::DataInit();

    if (pObject != nullptr)
    { // �擪���Ȃ�==�v���C�I���e�B�܂���ƂȂ�

        int nIndex = 0;

        while (pObject != nullptr)
        {
            
            if (pObject->GetObjectType() == CObject::OBJECT_MOTIONPLAYER)
            { // �Ώۂ̃��f���̂Ƃ�

                // �����Ŏg�p���錾
                CObjectMotionPlayer* pMotionPlayer;

                pMotionPlayer = (CObjectMotionPlayer*)pObject;

                EscData = pMotionPlayer->GetClassData();
                break;
            }
        }
    }

    // �����ݒ�
    VERTEX_2D* pVtx;

    m_pVtxBuff[m_MapNum]->Lock(0, 0, (void**)&pVtx, 0);

    //pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 195);
    //pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 195);
    //pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 195);
    //pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 195);

    D3DXVECTOR3 MapPlayerPos = D3DXVECTOR3(EscData.Pos.x + 9900.0f, EscData.Pos.y, EscData.Pos.z);

    D3DXVECTOR3 MapPlayerPos2 = D3DXVECTOR3(MapPlayerPos.x / 9900.0f, -MapPlayerPos.y / 3300.0f, MapPlayerPos.z);

    float Diff = 0.11f;
    float Diff2 = 0.33f;

    pVtx[0].tex = D3DXVECTOR2(MapPlayerPos2.x - Diff, MapPlayerPos2.y - Diff2);
    pVtx[1].tex = D3DXVECTOR2(MapPlayerPos2.x + Diff, MapPlayerPos2.y - Diff2);
    pVtx[2].tex = D3DXVECTOR2(MapPlayerPos2.x - Diff, MapPlayerPos2.y + Diff2);
    pVtx[3].tex = D3DXVECTOR2(MapPlayerPos2.x + Diff, MapPlayerPos2.y + Diff2);

    m_pVtxBuff[m_MapNum]->Unlock();     
}


//=============================
// ��ԑJ��
//=============================
void CGameUI::SetStateChangeUi(bool bSet, UITYPE Uitype)
{
   
    if (bSet)
    {//Online�ɂ��鎞
        m_UiState[Uitype] = UISTATE_ONLINE_TRIGGER;
        m_nMotionDalay[Uitype] = DELAYRAME1;
    }
    else
    {//Offline�ɂ���Ƃ�
        m_UiState[Uitype] = UISTATE_OFFLINE_TRIGGER;
    }


}
//=============================
// Online���̓���
//=============================
void CGameUI::OnlineTrigger(int nCnt)
{
    if (m_bFirst[nCnt] == true)
    {
        m_bFirst[nCnt] = false;
        m_nMotionCnt[nCnt] = 0;
    }

    //��{��RGB�@�ύX�͌��
    int DrawR = 15;
    int DrawG = 35;
    int DrawB = 15;

    int nDrawA[4] = {};
 
    int divisionFrame = 0;//�����t���[��

    float EscLength = 0.0f;//�Q�[�W�̂ݎg�p

    // �����ݒ�
    VERTEX_2D* pVtx;

    m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);


    m_nMotionCnt[nCnt]++;


    if (m_nMotionDalay[nCnt] <= 0)
    {
        m_nMotionDelayCnt[nCnt]++;
    }
    else
    {
        m_nMotionDalay[nCnt]--;
    }



    if (nCnt == UI_WEPON1_BACK|| nCnt == UI_WEPON2_BACK || nCnt == UI_WEPON3_BACK 
        || nCnt == UI_MAP_BACK || nCnt == UI_NOMAL || nCnt == UI_NOMAL2 ||nCnt == UI_HP_BACK|| nCnt == UI_BOOST_BACK)
    {
        if (nCnt == UI_HP_BACK)
        {
            DrawR = 155;
            DrawG = 155;
            DrawB = 155;
        }


        m_nWeponUIDrawA[nCnt] = 0;

        divisionFrame = PHASE1RAME;

        if (m_nMotionCnt[nCnt] <= divisionFrame)
        {
            nDrawA[0] = static_cast<int>((float)BACKGROUND_A * m_nMotionCnt[nCnt] / divisionFrame);
            nDrawA[1] = nDrawA[0];
        }
        else
        {
            nDrawA[0] = BACKGROUND_A;
            nDrawA[1] = nDrawA[0];
        }

        if (m_nMotionDelayCnt[nCnt] <= divisionFrame)
        {
            nDrawA[2] = static_cast<int>((float)BACKGROUND_A * m_nMotionDelayCnt[nCnt] / divisionFrame);
            nDrawA[3] = nDrawA[2];
        }
        else
        {
            nDrawA[2] = BACKGROUND_A;
            nDrawA[3] = nDrawA[2];
        }
    }
    else  if (nCnt == UI_WEPON1|| nCnt == UI_WEPON2 || nCnt == UI_WEPON3 || nCnt == UI_MAP|| nCnt == UI_PLAYERPIN)
    {
         //����UI�{��

        if (nCnt == UI_WEPON1 || nCnt == UI_WEPON2 || nCnt == UI_WEPON3)
        {
            DrawR = 140;
            DrawG = 180;
            DrawB = 180;
            divisionFrame = PHASE1RAME;
        }
        else if ( nCnt == UI_MAP)
        {
            DrawR = 255;
            DrawG = 255;
            DrawB = 255;
            divisionFrame = PHASE3RAME;
        }

        else if (nCnt == UI_PLAYERPIN)
        {
            DrawR = 255;
            DrawG = 15;
            DrawB = 15;
            divisionFrame = PHASE1RAME;

        }

        if (m_nMotionCnt[nCnt] <= divisionFrame)
        {
            nDrawA[0] = static_cast<int>((float)BACKGROUND_A * m_nMotionCnt[nCnt] / divisionFrame);
            nDrawA[1] = nDrawA[0];
        }
        else
        {
            nDrawA[0] = BACKGROUND_A;
            nDrawA[1] = nDrawA[0];
        }

        if (m_nMotionDelayCnt[nCnt] <= divisionFrame)
        {
            nDrawA[2] = static_cast<int>((float)BACKGROUND_A * m_nMotionDelayCnt[nCnt] / divisionFrame);
            nDrawA[3] = nDrawA[2];
        }
        else
        {
            nDrawA[2] = BACKGROUND_A;
            nDrawA[3] = nDrawA[2];
        }
        //UI�p�`��A�l
        m_nWeponUIDrawA[nCnt] = nDrawA[3];

    }
    else  if (nCnt == UI_LOAD_GAUGE_BACK_WEPON|| nCnt == UI_LOAD_GAUGE_BACK_WEPON2 || nCnt == UI_LOAD_GAUGE_BACK_WEPON3)
    {
        divisionFrame = PHASE1RAME;

        DrawR = 200;
        DrawG = 200;
        DrawB = 200;

        if (m_nMotionCnt[nCnt] <= divisionFrame)
        {
            nDrawA[0] = static_cast<int>((float)BACKGROUND_B * m_nMotionCnt[nCnt] / divisionFrame);
            nDrawA[1] = nDrawA[0];
        }
        else
        {
            nDrawA[0] = BACKGROUND_B;
            nDrawA[1] = nDrawA[0];
        }

        if (m_nMotionDelayCnt[nCnt] <= divisionFrame)
        {
            nDrawA[2] = static_cast<int>((float)BACKGROUND_B * m_nMotionDelayCnt[nCnt] / divisionFrame);
            nDrawA[3] = nDrawA[2];
        }
        else
        {
            nDrawA[2] = BACKGROUND_B;
            nDrawA[3] = nDrawA[2];
        }
    }
    else  if (nCnt == UI_LOAD_GAUGE_WEPON|| nCnt == UI_LOAD_GAUGE_WEPON2 || nCnt == UI_LOAD_GAUGE_WEPON3)
    {
        divisionFrame = PHASE2RAME;

        DrawR = 200;
        DrawG = 35;
        DrawB = 35;
        nDrawA[0] = BACKGROUND_B;
        nDrawA[1] = BACKGROUND_B;
        nDrawA[2] = BACKGROUND_B;
        nDrawA[3] = BACKGROUND_B;



        if (m_nMotionCnt[nCnt] <= divisionFrame)
        {
            EscLength = (m_fLength[nCnt] * 2.0f * m_nMotionCnt[nCnt] / divisionFrame);
        }
        else
        {
            EscLength = m_fLength[nCnt];
        }


        pVtx[0].pos.x = (m_Pos[nCnt].x - m_fLength[nCnt]);
        pVtx[1].pos.x = (m_Pos[nCnt].x - m_fLength[nCnt] + EscLength);
        pVtx[2].pos.x = (m_Pos[nCnt].x - m_fLength[nCnt]);
        pVtx[3].pos.x = (m_Pos[nCnt].x - m_fLength[nCnt] + EscLength);

    }
    else  if (nCnt == UI_TEXTWINDOW|| nCnt == UI_TEXTIMAGE || nCnt== UI_HP_MAIN || nCnt == UI_LOAD_GAUGE_WEPON3_2 || nCnt == UI_BOOST_MAIN)
    {
        divisionFrame = PHASE4RAME;

        if (nCnt == UI_TEXTWINDOW)
        {
            DrawR = 15;
            DrawG = 15;
            DrawB = 70;
        }
        else if (nCnt == UI_TEXTIMAGE)
        {
            DrawR = 255;
            DrawG = 255;
            DrawB = 255;
        }
        else if (nCnt == UI_HP_MAIN || nCnt == UI_LOAD_GAUGE_WEPON3_2)
        {
            DrawR = 155;
            DrawG = 0;
            DrawB = 0;
        }
        else if (nCnt == UI_BOOST_MAIN)
        {
            DrawR = 255;
            DrawG = 0;
            DrawB = 255;
        }
        

        nDrawA[0] =230;
        nDrawA[1] =230;
        nDrawA[2] =230;
        nDrawA[3] =230;



        if (m_nMotionCnt[nCnt] <= divisionFrame)
        {
            EscLength = (m_fLength[nCnt] * m_nMotionCnt[nCnt] / divisionFrame);
        }
        else
        {
            EscLength = m_fLength[nCnt];
        }


        if (nCnt == UI_TEXTWINDOW || nCnt == UI_TEXTIMAGE)
        {
            pVtx[0].pos.x = (m_Pos[nCnt].x - EscLength * 0.5f);
            pVtx[1].pos.x = (m_Pos[nCnt].x + EscLength * 0.5f);
            pVtx[2].pos.x = (m_Pos[nCnt].x - EscLength * 0.5f);
            pVtx[3].pos.x = (m_Pos[nCnt].x + EscLength * 0.5f);
        }
        else if (nCnt == UI_HP_MAIN || nCnt == UI_BOOST_MAIN || nCnt == UI_LOAD_GAUGE_WEPON3_2)
        {
         //   pVtx[0].pos.x = (m_Pos[nCnt].x - EscLength * 0.5f);
            pVtx[1].pos.x = (m_Pos[nCnt].x + EscLength);
          //  pVtx[2].pos.x = (m_Pos[nCnt].x - EscLength * 0.5f);
            pVtx[3].pos.x = (m_Pos[nCnt].x + EscLength);
        }

        else if (nCnt == UI_LOAD_GAUGE_WEPON3_2)
        {
            //   pVtx[0].pos.x = (m_Pos[nCnt].x - EscLength * 0.5f);
            pVtx[1].pos.x = (m_Pos[nCnt].x + EscLength);
            //  pVtx[2].pos.x = (m_Pos[nCnt].x - EscLength * 0.5f);
            pVtx[3].pos.x = (m_Pos[nCnt].x + EscLength);
        }
        

    }

    pVtx[0].col = D3DCOLOR_RGBA(DrawR, DrawG, DrawB, nDrawA[0]);
    pVtx[1].col = D3DCOLOR_RGBA(DrawR, DrawG, DrawB, nDrawA[1]);
    pVtx[2].col = D3DCOLOR_RGBA(DrawR, DrawG, DrawB, nDrawA[2]);
    pVtx[3].col = D3DCOLOR_RGBA(DrawR, DrawG, DrawB, nDrawA[3]);

    if (m_nMotionCnt[nCnt] >= divisionFrame)
    {//���[�V�������ő�l
      

        if (m_nMotionDelayCnt[nCnt] >= divisionFrame)
        {
            m_UiState[nCnt] = UISTATE_ONLINE_NOW;

          //  m_nMotionCnt[nCnt] = 0;
            m_nMotionDelayCnt[nCnt] = 0;

            pVtx[0].col = D3DCOLOR_RGBA(DrawR, DrawG, DrawB, nDrawA[0]);
            pVtx[1].col = D3DCOLOR_RGBA(DrawR, DrawG, DrawB, nDrawA[1]);
            pVtx[2].col = D3DCOLOR_RGBA(DrawR, DrawG, DrawB, nDrawA[2]);
            pVtx[3].col = D3DCOLOR_RGBA(DrawR, DrawG, DrawB, nDrawA[3]);


            switch (nCnt)
            {
            case UI_MAP_BACK:

                m_UiState[UI_MAP] = UISTATE_ONLINE_TRIGGER;
           
                

                break;

            case  UI_MAP:
                   m_UiState[UI_PLAYERPIN] = UISTATE_ONLINE_TRIGGER;
                break;




            case UI_WEPON1_BACK://UI_WEPON1

                //�Q�[�W�o�b�Non
                m_UiState[UI_LOAD_GAUGE_BACK_WEPON] = UISTATE_ONLINE_TRIGGER;

                break;
            case UI_WEPON1:
                //����UI�{��
                
                break;

            case UI_LOAD_GAUGE_BACK_WEPON://UI_WEPON�Q�[�W���
                //�Q�[�W�o�b�Non
                m_UiState[UI_LOAD_GAUGE_WEPON] = UISTATE_ONLINE_TRIGGER;

                break;

            case UI_LOAD_GAUGE_WEPON://UI_WEPON�Q�[�W�O

                //�Q�[�W�o�b�Non
                m_UiState[UI_WEPON1] = UISTATE_ONLINE_TRIGGER;

                UIDrawReset(CGameUI::UI_LOAD_GAUGE_BACK_WEPON);
                UIDrawReset(CGameUI::UI_LOAD_GAUGE_WEPON);

                break;
            //---------------------------------------------------------------------
            case UI_WEPON2_BACK://UI_WEPON1

                //�Q�[�W�o�b�Non
                m_UiState[UI_LOAD_GAUGE_BACK_WEPON2] = UISTATE_ONLINE_TRIGGER;

                break;
            case UI_WEPON2:
                //����UI�{��

                break;

            case UI_LOAD_GAUGE_BACK_WEPON2://UI_WEPON�Q�[�W���
                //�Q�[�W�o�b�Non
                m_UiState[UI_LOAD_GAUGE_WEPON2] = UISTATE_ONLINE_TRIGGER;

                break;

            case UI_LOAD_GAUGE_WEPON2://UI_WEPON�Q�[�W�O

                //�Q�[�W�o�b�Non
                m_UiState[UI_WEPON2] = UISTATE_ONLINE_TRIGGER;

                UIDrawReset(CGameUI::UI_LOAD_GAUGE_BACK_WEPON2);
                UIDrawReset(CGameUI::UI_LOAD_GAUGE_WEPON2);

                break;

                //---------------------------------------------------------------------
            case UI_WEPON3_BACK://UI_WEPON1

                //�Q�[�W�o�b�Non
                m_UiState[UI_LOAD_GAUGE_BACK_WEPON3] = UISTATE_ONLINE_TRIGGER;

                break;
            case UI_WEPON3:
                //����UI�{��

                break;

            case UI_LOAD_GAUGE_BACK_WEPON3://UI_WEPON�Q�[�W���
                //�Q�[�W�o�b�Non
                m_UiState[UI_LOAD_GAUGE_WEPON3] = UISTATE_ONLINE_TRIGGER;

                break;

            case UI_LOAD_GAUGE_WEPON3://UI_WEPON�Q�[�W�O

                //�Q�[�W�o�b�Non
                m_UiState[UI_WEPON3] = UISTATE_ONLINE_TRIGGER;
                m_UiState[UI_LOAD_GAUGE_WEPON3_2] = UISTATE_ONLINE_TRIGGER;

                UIDrawReset(CGameUI::UI_LOAD_GAUGE_BACK_WEPON3);
                UIDrawReset(CGameUI::UI_LOAD_GAUGE_WEPON3);

                break;

            case UI_PLAYERPIN://PLAYERPIN//playerpin
                break;

            case UI_TEXTWINDOW:
                 //�Q�[�W�o�b�Non
                m_UiState[UI_TEXTIMAGE] = UISTATE_ONLINE_TRIGGER;
                break;
            case UI_TEXTIMAGE:
                break;

            case UI_HP_BACK:

                m_UiState[UI_HP_MAIN] = UISTATE_ONLINE_TRIGGER;
                break;

            case UI_HP_MAIN:

               // m_UiState[UI_HP_MAIN] = UISTATE_ONLINE_TRIGGER;
                break;

            case UI_BOOST_BACK:

                m_UiState[UI_BOOST_MAIN] = UISTATE_ONLINE_TRIGGER;
                break;
            case UI_BOOST_MAIN:

                //m_UiState[UI_BOOST_MAIN] = UISTATE_ONLINE_TRIGGER;
                break;

               }
        }

    }

    m_pVtxBuff[nCnt]->Unlock();
}
//=============================
// Offline���̓���
//=============================
void CGameUI::OfflineTrigger(int nCnt)
{

    int divisionFrame = 0;//�����t���[��

    float EscLength = 0.0f;//�Q�[�W�̂ݎg�p

    // �����ݒ�
    VERTEX_2D* pVtx;

    m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

    m_nMotionCnt[nCnt]--;

    if (nCnt == UI_WEPON1_BACK || nCnt == UI_WEPON2_BACK || nCnt == UI_WEPON3_BACK || nCnt == UI_MAP_BACK 
        || nCnt == UI_NOMAL || nCnt == UI_NOMAL2 || nCnt== UI_HP_BACK|| nCnt == UI_BOOST_BACK)
    {

        divisionFrame = PHASE1RAME;


    }
    else  if (nCnt == UI_WEPON1 || nCnt == UI_WEPON2 || nCnt == UI_WEPON3 || nCnt == UI_MAP || nCnt == UI_PLAYERPIN)
    {
        //����UI�{��

        if (nCnt == UI_WEPON1 || nCnt == UI_WEPON2 || nCnt == UI_WEPON3)
        {
            divisionFrame = PHASE1RAME;
        }
        else if (nCnt == UI_MAP)
        {
            divisionFrame = PHASE3RAME;
        }

        else if (nCnt == UI_PLAYERPIN)
        {
            divisionFrame = PHASE1RAME;

        }



    }
    else  if (nCnt == UI_LOAD_GAUGE_BACK_WEPON || nCnt == UI_LOAD_GAUGE_BACK_WEPON2 || nCnt == UI_LOAD_GAUGE_BACK_WEPON3)
    {
        divisionFrame = PHASE1RAME;


    }
    else  if (nCnt == UI_LOAD_GAUGE_WEPON || nCnt == UI_LOAD_GAUGE_WEPON2 || nCnt == UI_LOAD_GAUGE_WEPON3)
    {
        divisionFrame = PHASE2RAME;




        if (m_nMotionCnt[nCnt] <= divisionFrame)
        {
            EscLength = (m_fLength[nCnt] * 2.0f * m_nMotionCnt[nCnt] / divisionFrame);
        }
        else
        {
            EscLength = m_fLength[nCnt];
        }


        pVtx[0].pos.x = (m_Pos[nCnt].x - m_fLength[nCnt]);
        pVtx[1].pos.x = (m_Pos[nCnt].x - m_fLength[nCnt] + EscLength);
        pVtx[2].pos.x = (m_Pos[nCnt].x - m_fLength[nCnt]);
        pVtx[3].pos.x = (m_Pos[nCnt].x - m_fLength[nCnt] + EscLength);

    }
    else  if (nCnt == UI_TEXTWINDOW || nCnt == UI_TEXTIMAGE || nCnt == UI_HP_MAIN)
    {
        divisionFrame = PHASE4RAME;





        if (m_nMotionCnt[nCnt] <= divisionFrame)
        {
            EscLength = (m_fLength[nCnt] * m_nMotionCnt[nCnt] / divisionFrame);
        }
        else
        {
            EscLength = m_fLength[nCnt];
        }

        if (nCnt == UI_TEXTWINDOW || nCnt == UI_TEXTIMAGE)
        {
            pVtx[0].pos.x = (m_Pos[nCnt].x - EscLength * 0.5f);
            pVtx[1].pos.x = (m_Pos[nCnt].x + EscLength * 0.5f);
            pVtx[2].pos.x = (m_Pos[nCnt].x - EscLength * 0.5f);
            pVtx[3].pos.x = (m_Pos[nCnt].x + EscLength * 0.5f);

        }
        else if ( nCnt == UI_HP_MAIN)
        {
            //   pVtx[0].pos.x = (m_Pos[nCnt].x - EscLength * 0.5f);
            pVtx[1].pos.x = (m_Pos[nCnt].x + EscLength);
            //  pVtx[2].pos.x = (m_Pos[nCnt].x - EscLength * 0.5f);
            pVtx[3].pos.x = (m_Pos[nCnt].x + EscLength);
        }
        
    }

    if (m_nMotionCnt[nCnt] < 0)
    {//���[�V�������ŏ��l

        pVtx[0].pos.x = 0.0f;
        pVtx[1].pos.x = 0.0f;
        pVtx[2].pos.x = 0.0f;
        pVtx[3].pos.x = 0.0f;

        m_nMotionCnt[nCnt] = 0;

        m_UiState[nCnt] = UISTATE_OFFLINE_NOW;

        switch (nCnt)
        {
        case UI_MAP_BACK:

            break;

        case  UI_MAP:

            break;

        case UI_WEPON1_BACK://UI_WEPON1

            break;

        case UI_WEPON1:
            //����UI�{��

            break;

        case UI_LOAD_GAUGE_BACK_WEPON://UI_WEPON�Q�[�W���

            break;

        case UI_LOAD_GAUGE_WEPON://UI_WEPON�Q�[�W�O

            break;
            //---------------------------------------------------------------------
        case UI_WEPON2_BACK://UI_WEPON1

            break;
        case UI_WEPON2:
            //����UI�{��

            break;

        case UI_LOAD_GAUGE_BACK_WEPON2://UI_WEPON�Q�[�W���

            break;

        case UI_LOAD_GAUGE_WEPON2://UI_WEPON�Q�[�W�O

            break;

            //---------------------------------------------------------------------
        case UI_WEPON3_BACK://UI_WEPON1

            break;
        case UI_WEPON3:
            //����UI�{��

            break;

        case UI_LOAD_GAUGE_BACK_WEPON3://UI_WEPON�Q�[�W���

            break;

        case UI_LOAD_GAUGE_WEPON3://UI_WEPON�Q�[�W�O

            break;

        case UI_PLAYERPIN://PLAYERPIN//playerpin
            break;

        case UI_TEXTWINDOW:

            break;
        case UI_TEXTIMAGE:
            m_UiState[UI_TEXTWINDOW] = UISTATE_OFFLINE_TRIGGER;
            break;

        case UI_HP_BACK:
       //     UI_HP_MAIN
            break;

        case UI_HP_MAIN:
            break;
        }
    }



    m_pVtxBuff[nCnt]->Unlock();
}
//=============================
// �`��lReset
//=============================
void CGameUI::UIDrawReset(int nCnt)
{

    // �����ݒ�
    VERTEX_2D* pVtx;

    m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

    pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 0);
    pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 0);
    pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 0);
    pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 0);

    m_pVtxBuff[nCnt]->Unlock();
}
//=============================
// �`��lRestart
//=============================
void CGameUI::AllUiRestart()
{
    if (m_bNowRestart==false)
    {//����N����
        for (int nCnt = 0; nCnt < UI_MAX; nCnt++)
        {
            m_bFirst[nCnt] = true;
        }


        m_bNowRestart = true;
        m_NowUiCount = 0;
        m_NowUiFrameCnt = 0;

        m_nWeponUIDrawA[UI_WEPON1] = 0;
        m_nWeponUIDrawA[UI_WEPON2] = 0;
        m_nWeponUIDrawA[UI_WEPON3] = 0;

        //Reset
        UIDrawReset(CGameUI::UI_MAP_BACK);
        m_nMotionCnt[(int)CGameUI::UI_MAP_BACK] = 0;

        UIDrawReset(CGameUI::UI_MAP);
        m_nMotionCnt[(int)CGameUI::UI_MAP] = 0;
        
        UIDrawReset(CGameUI::UI_NOMAL);
        m_nMotionCnt[(int)CGameUI::UI_NOMAL] = 0;
        
        UIDrawReset(CGameUI::UI_NOMAL2);
        m_nMotionCnt[(int)CGameUI::UI_NOMAL2] = 0;
        
        UIDrawReset(CGameUI::UI_WEPON1_BACK);
        m_nMotionCnt[(int)CGameUI::UI_WEPON1_BACK] = 0;
        
        UIDrawReset(CGameUI::UI_WEPON1);
        m_nMotionCnt[(int)CGameUI::UI_WEPON1] = 0;
        
        UIDrawReset(CGameUI::UI_LOAD_GAUGE_BACK_WEPON);
        m_nMotionCnt[(int)CGameUI::UI_LOAD_GAUGE_BACK_WEPON] = 0;
        
        UIDrawReset(CGameUI::UI_LOAD_GAUGE_WEPON);
        m_nMotionCnt[(int)CGameUI::UI_LOAD_GAUGE_WEPON] = 0;

        UIDrawReset(CGameUI::UI_WEPON2_BACK);
        m_nMotionCnt[(int)CGameUI::UI_WEPON2_BACK] = 0;
        
        UIDrawReset(CGameUI::UI_WEPON2);
        m_nMotionCnt[(int)CGameUI::UI_WEPON2] = 0;
        
        UIDrawReset(CGameUI::UI_LOAD_GAUGE_BACK_WEPON2);
        m_nMotionCnt[(int)CGameUI::UI_LOAD_GAUGE_BACK_WEPON2] = 0;

        UIDrawReset(CGameUI::UI_LOAD_GAUGE_WEPON2);
        m_nMotionCnt[(int)CGameUI::UI_LOAD_GAUGE_WEPON2] = 0;

        UIDrawReset(CGameUI::UI_WEPON3_BACK);
        m_nMotionCnt[(int)CGameUI::UI_WEPON3_BACK] = 0;

        UIDrawReset(CGameUI::UI_WEPON3);
        m_nMotionCnt[(int)CGameUI::UI_WEPON3] = 0;

        UIDrawReset(CGameUI::UI_LOAD_GAUGE_BACK_WEPON3);
        m_nMotionCnt[(int)CGameUI::UI_LOAD_GAUGE_BACK_WEPON3] = 0;

        UIDrawReset(CGameUI::UI_LOAD_GAUGE_WEPON3);
        m_nMotionCnt[(int)CGameUI::UI_LOAD_GAUGE_WEPON3] = 0;

        UIDrawReset(CGameUI::UI_PLAYERPIN);
        m_nMotionCnt[(int)CGameUI::UI_PLAYERPIN] = 0;

        UIDrawReset(CGameUI::UI_TEXTWINDOW);
        m_nMotionCnt[(int)CGameUI::UI_TEXTWINDOW] = 0;

        UIDrawReset(CGameUI::UI_TEXTIMAGE);
        m_nMotionCnt[(int)CGameUI::UI_TEXTIMAGE] = 0;

        UIDrawReset(CGameUI::UI_HP_BACK);
        m_nMotionCnt[(int)CGameUI::UI_HP_BACK] = 0;

        UIDrawReset(CGameUI::UI_HP_MAIN);
        m_nMotionCnt[(int)CGameUI::UI_HP_MAIN] = 0;

        UIDrawReset(CGameUI::UI_LOAD_GAUGE_WEPON3_2);
        m_nMotionCnt[(int)CGameUI::UI_LOAD_GAUGE_WEPON3_2] = 0;


        UIDrawReset(CGameUI::UI_BOOST_BACK);
        m_nMotionCnt[(int)CGameUI::UI_BOOST_BACK] = 0;


       
    }
    else
    {//�N���ς�
        m_NowUiFrameCnt++;
        
        if (m_NowUiFrameCnt >= DELAY_UI_TO_UI)
        {//���O���i��
            m_NowUiFrameCnt = 0;//�J�E���gReset

            switch (m_NowUiCount)
            {
                case 0:
                    SetStateChangeUi(true, CGameUI::UI_MAP_BACK);
                   // SetStateChangeUi(true, CGameUI::UI_TEXTWINDOW);
                    SetStateChangeUi(true, CGameUI::UI_HP_BACK);
                    SetStateChangeUi(true, CGameUI::UI_BOOST_BACK);
                  
                    
                    break;
                case 1:
                    SetStateChangeUi(true, CGameUI::UI_WEPON1_BACK);
               
                    SetStateChangeUi(true, CGameUI::UI_NOMAL);
                    break;
                case 2:
                    SetStateChangeUi(true, CGameUI::UI_WEPON2_BACK);
                    
                    SetStateChangeUi(true, CGameUI::UI_NOMAL2);
                    break;
                case 3:
                    SetStateChangeUi(true, CGameUI::UI_WEPON3_BACK);
                    break;
                case 4: 
                    m_bNowRestart = false;//�I��
                    break;
            }
            m_NowUiCount++;//�K�w�X�V
        }
    }
}

//=============================
// Restart����(debug)
//=============================
bool CGameUI::GetAllUiRestartNow()
{
    return m_bNowRestart;
}
//=============================
// �̗̓o�[�ϓ�
//=============================
void CGameUI::SetLifeBar(int nCnt)
{
    // �����ݒ�
    VERTEX_2D* pVtx;

    m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

    //   pVtx[0].pos.x = (m_Pos[nCnt].x - EscLength * 0.5f);
    pVtx[1].pos.x = (m_Pos[nCnt].x + m_fLength[nCnt]);

    //  pVtx[2].pos.x = (m_Pos[nCnt].x - EscLength * 0.5f);

    pVtx[3].pos.x = (m_Pos[nCnt].x + m_fLength[nCnt]);

    m_pVtxBuff[nCnt]->Unlock();
}

