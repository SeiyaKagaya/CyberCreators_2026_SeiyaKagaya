//=======================================================
//
// pause�Ɋւ��鏈��[pause.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "pause.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "all_texture.h"
#include "font.h"

// �ÓI�����o�[�ϐ��̒�`
//int CPause::m_SelectNum = 0; // �����l��MODE_TITLE�ɐݒ�



//=============================
// �R���X�g���N�^
//=============================
CPause::CPause(/*int nPriority*/)/* :CObject(nPriority)*/
{
    m_SelectNum = 0;

    for (int nCnt = 0; nCnt < TEXNUM; nCnt++)
    {
        m_nTexIdx[nCnt] = 0;
        m_pVtxBuff[nCnt] = nullptr;
        m_pTexture[nCnt] = nullptr;
    }


    m_Pos[0] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
    m_Pos[1] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
    m_Pos[2] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
    m_Pos[3] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
    m_Pos[4] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
    m_Pos[5] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
    m_Pos[6] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
}
//=============================
// �f�X�g���N�^
//=============================
CPause::~CPause()
{
    Uninit();
}
//=============================
// �����ݒ�(���_�o�b�t�@����)
//=============================
HRESULT CPause::Init()
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
            m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

            m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);

            pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 600.0f, m_Pos[nCnt].y - 340.0f, 0.0f);
            pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 600.0f, m_Pos[nCnt].y - 340.0f, 0.0f);
            pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 600.0f, m_Pos[nCnt].y + 340.0f, 0.0f);
            pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 600.0f, m_Pos[nCnt].y + 340.0f, 0.0f);

            pVtx[0].rhw = 1.0f;
            pVtx[1].rhw = 1.0f;
            pVtx[2].rhw = 1.0f;
            pVtx[3].rhw = 1.0f;

            pVtx[0].col = D3DCOLOR_RGBA(25, 25, 25, 225);
            pVtx[1].col = D3DCOLOR_RGBA(25, 25, 25, 225);
            pVtx[2].col = D3DCOLOR_RGBA(25, 25, 25, 225);
            pVtx[3].col = D3DCOLOR_RGBA(25, 25, 25, 225);

            pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
            pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
            pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
            pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

            m_pVtxBuff[nCnt]->Unlock();
            break;

        case 1:
            //�e�N�X�`���̓ǂݍ���
            D3DXCreateTextureFromFile(EscDevice, "DATA\\TEXTURE\\Tutorial1.png", &m_pTexture[nCnt]);//�ʏ펞

            m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

            m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 200.0f, SCREEN_HEIGHT * 0.5f + 100.0f, 0.0f);

            pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 330.0f, m_Pos[nCnt].y - 185.0f, 0.0f);
            pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 330.0f, m_Pos[nCnt].y - 185.0f, 0.0f);
            pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 330.0f, m_Pos[nCnt].y + 185.0f, 0.0f);
            pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 330.0f, m_Pos[nCnt].y + 185.0f, 0.0f);

            pVtx[0].rhw = 1.0f;
            pVtx[1].rhw = 1.0f;
            pVtx[2].rhw = 1.0f;
            pVtx[3].rhw = 1.0f;

            pVtx[0].col = D3DCOLOR_RGBA(255,255,255, 255);
            pVtx[1].col = D3DCOLOR_RGBA(255,255,255, 255);
            pVtx[2].col = D3DCOLOR_RGBA(255,255,255, 255);
            pVtx[3].col = D3DCOLOR_RGBA(255,255,255, 255);

            pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
            pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
            pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
            pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

            m_pVtxBuff[nCnt]->Unlock();
            break;

        case 2:
            //�e�N�X�`���̓ǂݍ���
            D3DXCreateTextureFromFile(EscDevice, "DATA\\TEXTURE\\Tutorial2.png", &m_pTexture[nCnt]);//�ʏ펞

            m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

            m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 200.0f, SCREEN_HEIGHT * 0.5f + 100.0f, 0.0f);

            pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 330.0f, m_Pos[nCnt].y - 185.0f, 0.0f);
            pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 330.0f, m_Pos[nCnt].y - 185.0f, 0.0f);
            pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 330.0f, m_Pos[nCnt].y + 185.0f, 0.0f);
            pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 330.0f, m_Pos[nCnt].y + 185.0f, 0.0f);

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



        case 3:

            //�e�N�X�`���̓ǂݍ���
              D3DXCreateTextureFromFile(EscDevice, "DATA\\TEXTURE\\pngwing.png", &m_pTexture[nCnt]);//�ʏ펞


            m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

            m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f-50.0f, SCREEN_HEIGHT * 0.5f + 312.0f, 0.0f);

            pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 25.0f, m_Pos[nCnt].y - 25.0f, 0.0f);
            pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 25.0f, m_Pos[nCnt].y - 25.0f, 0.0f);
            pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 25.0f, m_Pos[nCnt].y + 25.0f, 0.0f);
            pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 25.0f, m_Pos[nCnt].y + 25.0f, 0.0f);

            pVtx[0].rhw = 1.0f;
            pVtx[1].rhw = 1.0f;
            pVtx[2].rhw = 1.0f;
            pVtx[3].rhw = 1.0f;

            pVtx[0].col = D3DCOLOR_RGBA(255,255,255, 255);
            pVtx[1].col = D3DCOLOR_RGBA(255,255,255, 255);
            pVtx[2].col = D3DCOLOR_RGBA(255,255,255, 255);
            pVtx[3].col = D3DCOLOR_RGBA(255,255,255, 255);

            pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
            pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
            pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
            pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

            m_pVtxBuff[nCnt]->Unlock();
            break;
        case 4:

            //�e�N�X�`���̓ǂݍ���
            D3DXCreateTextureFromFile(EscDevice, "DATA\\TEXTURE\\mouth.png", &m_pTexture[nCnt]);//�ʏ펞


            m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

            m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f + 312.0f, 0.0f);

            pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 40.0f, m_Pos[nCnt].y - 40.0f, 0.0f);
            pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 40.0f, m_Pos[nCnt].y - 40.0f, 0.0f);
            pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 40.0f, m_Pos[nCnt].y + 40.0f, 0.0f);
            pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 40.0f, m_Pos[nCnt].y + 40.0f, 0.0f);

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
        case 5:

            //�e�N�X�`���̓ǂݍ���
            D3DXCreateTextureFromFile(EscDevice, "DATA\\TEXTURE\\mouth_click2.png", &m_pTexture[nCnt]);//�ʏ펞


            m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

            m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5+300.0f, SCREEN_HEIGHT * 0.5f + 312.0f, 0.0f);

            pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 42.0f, m_Pos[nCnt].y - 42.0f, 0.0f);
            pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 42.0f, m_Pos[nCnt].y - 42.0f, 0.0f);
            pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 42.0f, m_Pos[nCnt].y + 42.0f, 0.0f);
            pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 42.0f, m_Pos[nCnt].y + 42.0f, 0.0f);

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

        case 6:

            //�e�N�X�`���̓ǂݍ���
            D3DXCreateTextureFromFile(EscDevice, "DATA\\TEXTURE\\A.png", &m_pTexture[nCnt]);//�ʏ펞


            m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

            m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5 + 250.0f, SCREEN_HEIGHT * 0.5f + 312.0f, 0.0f);

            pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 22.0f, m_Pos[nCnt].y - 22.0f, 0.0f);
            pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 22.0f, m_Pos[nCnt].y - 22.0f, 0.0f);
            pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 22.0f, m_Pos[nCnt].y + 22.0f, 0.0f);
            pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 22.0f, m_Pos[nCnt].y + 22.0f, 0.0f);

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
void CPause::Uninit()
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
            m_pTexture[nCnt]->Release();//-----�e�N�X�`��cpp�ł�邱��
            m_pTexture[nCnt] = nullptr;
        }
    }
}
//=============================
// �X�V(���_���̍X�V)
//=============================
void CPause::Update()
{
    CRenderer* pRenderer = nullptr;

    CManager* pManager = CManager::GetInstance();

    CInputKeyboard* keyboard = pManager->GetKeyboard();

    CInputJoyPad* JoyPad = pManager->GetJoyPad();

    XINPUT_STATE joykeystate;

    //�V���C�p�b�g�̏�Ԃ��擾
    DWORD dwResult = XInputGetState(0, &joykeystate);






    // �}�E�X�J�[�\����\���ɂ���
    int nDrawCnt = ShowCursor(TRUE);

    while (true)
    {
        if (nDrawCnt > 0)
        {//�\����Ԃ̂Ƃ�
            if (nDrawCnt > 1)
            {//2������
                nDrawCnt = ShowCursor(FALSE);
            }

            break;
        }
        else
        {//��\����Ԃ̂Ƃ�
            nDrawCnt = ShowCursor(TRUE);
        }
    }





    if (m_bPhase2 == false)
    {//�����

        if (dwResult == ERROR_SUCCESS)
        {//�L�[�{�[�h/�R���g���[���[���͔��f(�ړ�)

         //   if (m_bSetStick==false)
          //  {
            if (JoyPad->GetTrigger(CInputJoyPad::JOYKEY_UP))
            {
                CSound* pSound = pManager->GetSound();
                //pSound->PlaySound(CSound::SOUND_LABEL_SE_CURSOR);

                AddSelectNum(-1);
                //        m_bSetStick = true;
            }
            else if (JoyPad->GetTrigger(CInputJoyPad::JOYKEY_DOWN) )
            {
                CSound* pSound = pManager->GetSound();
                //pSound->PlaySound(CSound::SOUND_LABEL_SE_CURSOR);


                AddSelectNum(+1);
                //        m_bSetStick = true;
            }
            // }
        }
        //else
        //{//�L�[�{�[�h���͔��f(�ړ�)

        //    if (JoyPad->GetTrigger(CInputJoyPad::JOYKEY_UP))
        //    {
        //        AddSelectNum(-1);
        //    }
        //    else if (JoyPad->GetTrigger(CInputJoyPad::JOYKEY_DOWN))
        //    {
        //        AddSelectNum(+1);
        //    }


        //}

        // �����ŁA�}�E�X�̈ʒu���擾���ĕ\�����鏈�����s��
        POINT mousePos = keyboard->GetMousePosition();

        D3DXVECTOR3 POS = D3DXVECTOR3(0.0f, 0.0f, 0.0f);// keyboard->GetMouseRayIntersection(*pManager->GetCamera());//�}�E�X�ʒu
     //   POINT point= keyboard->GetMousePosition();

        POS.x = (float)mousePos.x;
        POS.y = (float)mousePos.y;


        float MinX[3];
        MinX[0] = 115.0f;
        MinX[1] = 115.0f;
        MinX[2] = 115.0f;

        float MaxX[3];
        MaxX[0] = 385.0f;
        MaxX[1] = 385.0f;
        MaxX[2] = 425.0f;

        float MinY[3];
        MinY[0] = 260.0f;
        MinY[1] = 400.0f;
        MinY[2] = 560.0f;

        float MaxY[3];
        MaxY[0] = 300.0f;
        MaxY[1] = 475.0f;
        MaxY[2] = 640.0f;

        bool bHit = false;

        for (int nCnt = 0; nCnt < 3; nCnt++)
        {
            if ((POS.y) >= MinY[nCnt] &&
                (POS.y) <= MaxY[nCnt])
            {//�㉺
                if ((POS.x) >= MinX[nCnt] &&
                    (POS.x) <= MaxX[nCnt])
                {//���E
                    bHit = true;
                }
            }

            if ((POS.x) >= MinX[nCnt] &&
                (POS.x) <= MaxX[nCnt])
            {//���E
                if ((POS.y) >= MinY[nCnt] &&
                    (POS.y) <= MaxY[nCnt])
                {//�㉺
                    bHit = true;
                }
            }

            if (bHit == true)
            {
                DirectSetNum(nCnt);
                break;
            }
        }


        //-----------------------------------------------------


















        //-------------------------------------------------------------------

        if (dwResult == ERROR_SUCCESS)
        {//�L�[�{�[�h/�R���g���[���[���͔��f(�ړ�)

         //   if (m_bSetStick==false)
          //  {
            JoyPad = pManager->GetJoyPad();

            if (JoyPad->GetTrigger(CInputJoyPad::JOYKEY_A) || JoyPad->GetTrigger(CInputJoyPad::JOYKEY_START) || keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left)|| keyboard->GetTrigger(DIK_SPACE))
            {
                CSound* pSound = pManager->GetSound();
             //   //pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER1);

                StopCnt++;

                switch (GetSelectNum())
                {
                case 0://�Q�[���ɖ߂�

                    pManager->SetPauseState(false);


                    break;

                case 1://��������ύX

                    m_bPhase2 = true;

                    break;

                case 2://�^�C�g���ɖ߂�

                    pManager->SetPauseState(false);

                    
                    CFade* pFade = pManager->GetFade();
                    pFade->SetFade(CScene::MODE_TITLE);

                    break;
                }

            }

        }
        else
        {//�L�[�{�[�h���͔��f(�ړ�)

            if (keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left) || keyboard->GetTrigger(DIK_SPACE))
            {
                CSound* pSound = pManager->GetSound();
            //    //pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER1);

                StopCnt++;

                switch (GetSelectNum())
                {
                case 0://�Q�[���ɖ߂�

                    pManager->SetPauseState(false);

                    break;

                case 1://��������ύX

                    m_bPhase2 = true;

                    break;

                case 2://�^�C�g���ɖ߂�

                    pManager->SetPauseState(false);

                    CFade* pFade = pManager->GetFade();
                    pFade->SetFade(CScene::MODE_TITLE);

                    break;
                }
            }
        }
        
  //      return;

    }
    else
    {//���2�Ԗځi������@�ύX�j


        if (dwResult == ERROR_SUCCESS)
        {//�L�[�{�[�h/�R���g���[���[���͔��f(�ړ�)

            JoyPad = pManager->GetJoyPad();

            if (keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left))
            {
                CSound* pSound = pManager->GetSound();
              //  //pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER1);

                m_bPhase2 = false;
            }
            else if (JoyPad->GetTrigger(CInputJoyPad::JOYKEY_A) || JoyPad->GetTrigger(CInputJoyPad::JOYKEY_START) || JoyPad->GetTrigger(CInputJoyPad::JOYKEY_B) || keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left) || keyboard->GetTrigger(DIK_SPACE))
            {
                CSound* pSound = pManager->GetSound();
               // //pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER1);

                m_bPhase2 = false;
            }
            else if (JoyPad->GetTrigger(CInputJoyPad::JOYKEY_LEFT))
            {
                CSound* pSound = pManager->GetSound();
                //pSound->PlaySound(CSound::SOUND_LABEL_SE_CURSOR);

  
                if (pManager->bGetInputState() == true)
                {//������@--true�ŃR���g���[���[
                    pManager->bSetInputState(false);
                }
                else
                {

                    pManager->bSetInputState(true);
                }

            }
            else if (JoyPad->GetTrigger(CInputJoyPad::JOYKEY_RIGHT))
            {
                CSound* pSound = pManager->GetSound();
                //pSound->PlaySound(CSound::SOUND_LABEL_SE_CURSOR);

                if (pManager->bGetInputState() == true)
                {//������@--true�ŃR���g���[���[
                    pManager->bSetInputState(false);
                }
                else
                {

                    pManager->bSetInputState(true);
                }
            }


            
           
        }
        else
        {//�L�[�{�[�h���͔��f(�ړ�)

            if (keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left) || keyboard->GetTrigger(DIK_SPACE))
            {
                CSound* pSound = pManager->GetSound();
             //   //pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER1);

                m_bPhase2 = false;
            }


          
        }

        // �����ŁA�}�E�X�̈ʒu���擾���ĕ\�����鏈�����s��
        POINT mousePos = keyboard->GetMousePosition();


        D3DXVECTOR3 POS = D3DXVECTOR3(0.0f, 0.0f, 0.0f);// keyboard->GetMouseRayIntersection(*pManager->GetCamera());//�}�E�X�ʒu
     //   POINT point= keyboard->GetMousePosition();

        POS.x = (float)mousePos.x;
        POS.y = (float)mousePos.y;


        float MinX[2];
        MinX[0] = 560.0f;
        MinX[1] = 915.0f;

        float MaxX[2];
        MaxX[0] = 870.0f;
        MaxX[1] = 1180.0f;

        float MinY[2];
        MinY[0] = 230.0f;
        MinY[1] = 230.0f;

        float MaxY[2];
        MaxY[0] = 265.0f;
        MaxY[1] = 265.0f;

        bool bHit = false;

        for (int nCnt = 0; nCnt < 2; nCnt++)
        {
            if ((POS.y) >= MinY[nCnt] &&
                (POS.y) <= MaxY[nCnt])
            {//�㉺
                if ((POS.x) >= MinX[nCnt] &&
                    (POS.x) <= MaxX[nCnt])
                {//���E
                    bHit = true;
                }
            }

            if ((POS.x) >= MinX[nCnt] &&
                (POS.x) <= MaxX[nCnt])
            {//���E
                if ((POS.y) >= MinY[nCnt] &&
                    (POS.y) <= MaxY[nCnt])
                {//�㉺
                    bHit = true;
                }
            }

            if (bHit == true)
            {
                if (nCnt==0)
                {
                    pManager->bSetInputState(false);
                }
                else
                {
                    if (dwResult == ERROR_SUCCESS)
                    {//�L�[�{�[�h/�R���g���[���[���͔��f(�ړ�)
                        pManager->bSetInputState(true);
                    }
                }
               
                break;
            }
        }







       

    }







    if (dwResult == ERROR_SUCCESS)
    {//�p�b�h�ڑ�����
    }
    else
    {
        pManager->bSetInputState(false);
    }
}
//=============================
// �`�揈��(POLYGON�`��)
//=============================
void CPause::Draw()
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

            case 1://�L�[�}�E
                if (pManager->bGetInputState() == false)
                {//������@--true�ŃR���g���[���[
                    hr = EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
                }
                break;

            case 2://�R���g���[���[
                
                if (pManager->bGetInputState() == true)
                {//������@--true�ŃR���g���[���[
                    hr = EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
                }

                break;

            case 3://�R���g���[��UI
                
                if (dwResult == ERROR_SUCCESS)
                {//�p�b�h�ڑ�����

                    hr = EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
                }

                break;

            case 4://�}�E�X
                hr = EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
                break;

            case 5://�}�E�X�N���b�N
                hr = EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
                break;

            case 6://�{�^��A
                
                if (dwResult == ERROR_SUCCESS)
                {//�p�b�h�ڑ�����
                    hr = EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
                }
                
                break;

        }

     


        
        EscDevice->SetTexture(0, nullptr);

    }




    const char* aData = "-PAUSE-";                                                                                                                       
    CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 180.0f, SCREEN_HEIGHT / 2.0f - 310.0f, 0.0f), 103, CFont::FONT_GENKAI, D3DXCOLOR(1.0f,1.0f,1.0f, 1.0f), aData);

    switch (m_SelectNum)
    {
    case 0:
        aData = "�Q�[���ɖ߂�";
        CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 527.0f, SCREEN_HEIGHT / 2.0f - 128.0f, 0.0f), 53, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f), aData);



        aData = "������@�ύX";
        CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 527.0f, SCREEN_HEIGHT / 2.0f + 40.0f, 0.0f), 53, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f), aData);



        aData = "�^�C�g���ɖ߂�";
        CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 527.0f, SCREEN_HEIGHT / 2.0f + 208.0f, 0.0f), 53, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f), aData);


        aData = "+���݂̑�����@+";
        CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 25.0f, SCREEN_HEIGHT / 2.0f - 188.0f, 0.0f), 53, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f), aData);

        break;

    case 1:
        aData = "�Q�[���ɖ߂�";
        CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 527.0f, SCREEN_HEIGHT / 2.0f - 128.0f, 0.0f), 53, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f), aData);

        if (m_bPhase2 == true)
        {//���t�F�[�Y
            aData = "������@�ύX";
            CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 527.0f, SCREEN_HEIGHT / 2.0f + 40.0f, 0.0f), 53, CFont::FONT_GENKAI, D3DXCOLOR(0.2f, 0.2f, 1.0f, 1.0f), aData);
        }
        else
        {
            aData = "������@�ύX";
            CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 527.0f, SCREEN_HEIGHT / 2.0f + 40.0f, 0.0f), 53, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f), aData);
        }

        aData = "�^�C�g���ɖ߂�";
        CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 527.0f, SCREEN_HEIGHT / 2.0f + 208.0f, 0.0f), 53, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f), aData);


        aData = "+���݂̑�����@+";
        CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 25.0f, SCREEN_HEIGHT / 2.0f - 188.0f, 0.0f), 53, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f), aData);


   //     aData = "��������@�ύX";
 //       CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 527.0f, SCREEN_HEIGHT / 2.0f + 40.0f, 0.0f), 53, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f), aData);

        break;

    case 2:
        aData = "�Q�[���ɖ߂�";
        CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 527.0f, SCREEN_HEIGHT / 2.0f - 128.0f, 0.0f), 53, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f), aData);



        aData = "������@�ύX";
        CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 527.0f, SCREEN_HEIGHT / 2.0f + 40.0f, 0.0f), 53, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f), aData);



        aData = "�^�C�g���ɖ߂�";
        CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 527.0f, SCREEN_HEIGHT / 2.0f + 208.0f, 0.0f), 53, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f), aData);
      
        aData = "+���݂̑�����@+";
        CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 25.0f, SCREEN_HEIGHT / 2.0f - 188.0f, 0.0f), 53, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f), aData);
        
        break;

    }
    



    if (m_bPhase2 == true)
    {//�N���b�N��

        XINPUT_STATE joykeystate;
        //�V���C�p�b�g�̏�Ԃ��擾
        DWORD dwResult = XInputGetState(0, &joykeystate);

        if (dwResult == ERROR_SUCCESS)
        {//�p�b�h�ڑ�����

            if (pManager->bGetInputState() == false)
            {//������@--true�ŃR���g���[���[
                aData = "�L�[�{�[�h�E�}�E�X����";
                CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 80.0f, SCREEN_HEIGHT / 2.0f - 125.0f, 0.0f), 33, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f), aData);

                aData = "�R���g���[���[����";
                CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 280.0f, SCREEN_HEIGHT / 2.0f - 125.0f, 0.0f), 33, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), aData);

            }
            else
            {
                aData = "�L�[�{�[�h�E�}�E�X����";
                CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 80.0f, SCREEN_HEIGHT / 2.0f - 125.0f, 0.0f), 33, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), aData);

                aData = "�R���g���[���[����";
                CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 280.0f, SCREEN_HEIGHT / 2.0f - 125.0f, 0.0f), 33, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f), aData);

            }

            aData = "�ړ�";
            CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 30.0f, SCREEN_HEIGHT * 0.5f + 295.0f, 0.0f), 38, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData);

            aData = "�I��";
            CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 330.0f, SCREEN_HEIGHT * 0.5f + 295.0f, 0.0f), 38, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData);


        }
        else
        {
            if (pManager->bGetInputState() == false)
            {//������@--true�ŃR���g���[���[
                aData = "�L�[�{�[�h�E�}�E�X����";
                CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 80.0f, SCREEN_HEIGHT / 2.0f - 125.0f, 0.0f), 33, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f), aData);

                aData = "�R���g���[���[����";
                CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 280.0f, SCREEN_HEIGHT / 2.0f - 125.0f, 0.0f), 33, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), aData);
                aData = "===============";
                CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 280.0f, SCREEN_HEIGHT / 2.0f - 125.0f, 0.0f), 33, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData);

                aData = "�����ڑ�";
                CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 360.0f, SCREEN_HEIGHT / 2.0f - 145.0f, 0.0f), 28, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 0.1f, 0.1f, 0.95f), aData);
     
            }
            else
            {
                aData = "�L�[�{�[�h�E�}�E�X����";
                CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 80.0f, SCREEN_HEIGHT / 2.0f - 125.0f, 0.0f), 33, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), aData);

                aData = "�R���g���[���[����";
                CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 280.0f, SCREEN_HEIGHT / 2.0f - 125.0f, 0.0f), 33, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f), aData);
                aData = "===============";
                CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 280.0f, SCREEN_HEIGHT / 2.0f - 125.0f, 0.0f), 33, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f), aData);

                aData = "�����ڑ�";
                CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 360.0f, SCREEN_HEIGHT / 2.0f - 145.0f, 0.0f), 28, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 0.1f, 0.1f, 0.95f), aData);

            }

            aData = "�ړ�";
            CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 30.0f, SCREEN_HEIGHT * 0.5f + 295.0f, 0.0f), 38, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData);

            aData = "�I��";
            CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 330.0f, SCREEN_HEIGHT * 0.5f + 295.0f, 0.0f), 38, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData);

        }
    }
    else
    {
        XINPUT_STATE joykeystate;
        //�V���C�p�b�g�̏�Ԃ��擾
        DWORD dwResult = XInputGetState(0, &joykeystate);

        if (dwResult == ERROR_SUCCESS)
        {//�p�b�h�ڑ�����

            if (pManager->bGetInputState() == false)
            {//������@--true�ŃR���g���[���[
                aData = "�L�[�{�[�h�E�}�E�X����";
                CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 80.0f, SCREEN_HEIGHT / 2.0f - 125.0f, 0.0f), 33, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData);

                aData = "�R���g���[���[����";
                CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 280.0f, SCREEN_HEIGHT / 2.0f - 125.0f, 0.0f), 33, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), aData);

            }
            else
            {
                aData = "�L�[�{�[�h�E�}�E�X����";
                CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 80.0f, SCREEN_HEIGHT / 2.0f - 125.0f, 0.0f), 33, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), aData);

                aData = "�R���g���[���[����";
                CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 280.0f, SCREEN_HEIGHT / 2.0f - 125.0f, 0.0f), 33, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData);

            }

            aData = "�ړ�";
            CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 30.0f, SCREEN_HEIGHT * 0.5f + 295.0f, 0.0f), 38, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData);

            aData = "�I��";
            CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 330.0f, SCREEN_HEIGHT * 0.5f + 295.0f, 0.0f), 38, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData);

        }
        else
        {
            if (pManager->bGetInputState() == false)
            {//������@--true�ŃR���g���[���[
                aData = "�L�[�{�[�h�E�}�E�X����";
                CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 80.0f, SCREEN_HEIGHT / 2.0f - 125.0f, 0.0f), 33, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData);

                aData = "�R���g���[���[����";
                CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 280.0f, SCREEN_HEIGHT / 2.0f - 125.0f, 0.0f), 33, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), aData);
                aData = "===============";
                CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 280.0f, SCREEN_HEIGHT / 2.0f - 125.0f, 0.0f), 33, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData);

                aData = "�����ڑ�";
                CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 360.0f, SCREEN_HEIGHT / 2.0f - 145.0f, 0.0f), 28, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 0.1f, 0.1f, 0.95f), aData);


            }
            else
            {
                aData = "�L�[�{�[�h�E�}�E�X����";
                CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 80.0f, SCREEN_HEIGHT / 2.0f - 125.0f, 0.0f), 33, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), aData);

                aData = "�R���g���[���[����";
                CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 280.0f, SCREEN_HEIGHT / 2.0f - 125.0f, 0.0f), 33, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData);

                aData = "===============";
                CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 280.0f, SCREEN_HEIGHT / 2.0f - 125.0f, 0.0f), 33, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData);

                aData = "�����ڑ�";
                CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 360.0f, SCREEN_HEIGHT / 2.0f - 145.0f, 0.0f), 28, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 0.1f, 0.1f, 0.95f), aData);
            }

            aData = "�ړ�";
            CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 30.0f, SCREEN_HEIGHT * 0.5f + 295.0f, 0.0f), 38, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData);

            aData = "�I��";
            CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 330.0f, SCREEN_HEIGHT * 0.5f + 295.0f, 0.0f), 38, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData);

        }
    }




    
}

//=============================
// Object����
//=============================
CPause* CPause::Create()
{
    CPause* pObject2D = new CPause;
    pObject2D->Init();
    return pObject2D;
}



void CPause::AddSelectNum(int addnum)
{
    m_SelectNum += addnum;

    if (m_SelectNum<0)
    {
        m_SelectNum = 2;
    }
    else if(m_SelectNum > 2)
    {
        m_SelectNum = 0;
    }
}

void CPause::DirectSetNum(int Num)
{
    m_SelectNum = Num;

    if (m_SelectNum < 0)
    {
        m_SelectNum = 2;
    }
    else if (m_SelectNum > 2)
    {
        m_SelectNum = 0;
    }
}

int CPause::GetSelectNum()
{
    return m_SelectNum;
}