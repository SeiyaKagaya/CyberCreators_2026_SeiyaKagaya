//=======================================================
//
// Tutorial�Ɋւ��鏈��[Tutorial.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "Tutorial.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "all_texture.h"
#include "font.h"

// �ÓI�����o�[�ϐ��̒�`
//int CTutorialUI::m_SelectNum = 0; // �����l��MODE_TITLE�ɐݒ�



//=============================
// �R���X�g���N�^
//=============================
CTutorialUI::CTutorialUI(/*int nPriority*/)/* :CObject(nPriority)*/
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
}
//=============================
// �f�X�g���N�^
//=============================
CTutorialUI::~CTutorialUI()
{
    Uninit();
}
//=============================
// �����ݒ�(���_�o�b�t�@����)
//=============================
HRESULT CTutorialUI::Init()
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
            D3DXCreateTextureFromFile(EscDevice, "DATA\\TEXTURE\\yuka.jpg", &m_pTexture[nCnt]);//�ʏ펞


            m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

            m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);

            pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - (float)(SCREEN_WIDTH *0.5f), m_Pos[nCnt].y - (float)(SCREEN_HEIGHT * 0.5f), 0.0f);
            pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + (float)(SCREEN_WIDTH * 0.5f), m_Pos[nCnt].y - (float)(SCREEN_HEIGHT * 0.5f), 0.0f);
            pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - (float)(SCREEN_WIDTH * 0.5f), m_Pos[nCnt].y + (float)(SCREEN_HEIGHT * 0.5f), 0.0f);
            pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + (float)(SCREEN_WIDTH * 0.5f), m_Pos[nCnt].y + (float)(SCREEN_HEIGHT * 0.5f), 0.0f);

            pVtx[0].rhw = 1.0f;
            pVtx[1].rhw = 1.0f;
            pVtx[2].rhw = 1.0f;
            pVtx[3].rhw = 1.0f;

            pVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
            pVtx[1].col = D3DCOLOR_RGBA(255,255,255,255);
            pVtx[2].col = D3DCOLOR_RGBA(255,255,255,255);
            pVtx[3].col = D3DCOLOR_RGBA(255,255,255,255);

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

            m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 000.0f, SCREEN_HEIGHT * 0.5f - 90.0f , 0.0f);

            pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 600.0f, m_Pos[nCnt].y - 130.0f, 0.0f);
            pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 600.0f, m_Pos[nCnt].y - 130.0f, 0.0f);
            pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 600.0f, m_Pos[nCnt].y + 130.0f, 0.0f);
            pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 600.0f, m_Pos[nCnt].y + 130.0f, 0.0f);

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

        case 2:
            //�e�N�X�`���̓ǂݍ���
            D3DXCreateTextureFromFile(EscDevice, "DATA\\TEXTURE\\Tutorial2.png", &m_pTexture[nCnt]);//�ʏ펞

            m_pVtxBuff[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

            m_Pos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 280.0f, SCREEN_HEIGHT * 0.5f +180.0f, 0.0f);
            
            pVtx[0].pos = D3DXVECTOR3(m_Pos[nCnt].x - 300.0f, m_Pos[nCnt].y - 130.0f, 0.0f);
            pVtx[1].pos = D3DXVECTOR3(m_Pos[nCnt].x + 300.0f, m_Pos[nCnt].y - 130.0f, 0.0f);
            pVtx[2].pos = D3DXVECTOR3(m_Pos[nCnt].x - 300.0f, m_Pos[nCnt].y + 130.0f, 0.0f);
            pVtx[3].pos = D3DXVECTOR3(m_Pos[nCnt].x + 300.0f, m_Pos[nCnt].y + 130.0f, 0.0f);

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
void CTutorialUI::Uninit()
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
void CTutorialUI::Update()
{

    CRenderer* pRenderer = nullptr;

    CManager* pManager = CManager::GetInstance();

    CInputKeyboard* keyboard = pManager->GetKeyboard();

    CInputJoyPad* JoyPad = pManager->GetJoyPad();

    XINPUT_STATE joykeystate;

    //�V���C�p�b�g�̏�Ԃ��擾
    DWORD dwResult = XInputGetState(0, &joykeystate);


        if (dwResult == ERROR_SUCCESS)
        {//�L�[�{�[�h/�R���g���[���[���͔��f(�ړ�)

         //   if (m_bSetStick==false)
          //  {
            if (JoyPad->GetTrigger(CInputJoyPad::JOYKEY_UP))
            {
                CSound* pSound = pManager->GetSound();
                pSound->PlaySound(CSound::SOUND_LABEL_SE_CURSOR);

                AddSelectNum(-1);
                //        m_bSetStick = true;
            }
            else if (JoyPad->GetTrigger(CInputJoyPad::JOYKEY_DOWN))
            {
                CSound* pSound = pManager->GetSound();
                pSound->PlaySound(CSound::SOUND_LABEL_SE_CURSOR);


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
            if (JoyPad->GetTrigger(CInputJoyPad::JOYKEY_A) || keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left))
            {
                CSound* pSound = pManager->GetSound();
                pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER1);


                CFade* pFade = {};

                switch (GetSelectNum())
                {
                case 0://�^�C�g���ɖ߂�

                    pFade = pManager->GetFade();
                 //   pFade->SetFade(CScene::MODE_GAME);
                    pFade->SetFade(CScene::MODE_OP);

                    break;

                case 1:

                    pFade = pManager->GetFade();
                    pFade->SetFade(CScene::MODE_TITLE);

                    break;

                case 2:

                 //   m_bStopNow = false;

                    /*pFade = pManager->GetFade();
                    pFade->SetFade(CScene::MODE_TITLE);*/


                    break;
                }

            }

        }
        else
        {//�L�[�{�[�h���͔��f(�ړ�)
//
//            if (keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left))
//            {
//                CSound* pSound = pManager->GetSound();
//           
//
//                CFade* pFade;
//
//                switch (GetSelectNum())
//                {
//                case 0://�^�C�g���ɖ߂�
//
//                    pFade = pManager->GetFade();
////                    pFade->SetFade(CScene::MODE_GAME);
//                    pFade->SetFade(CScene::MODE_OP);
//
//                    break;
//
//                case 1://��������ύX
//
//             
//
//                    break;
//
//                case 2://���ɐi��
//
//                 //   m_bStopNow = false;
//
//                    pFade = pManager->GetFade();
//                    pFade->SetFade(CScene::MODE_TITLE);
//
//
//                    break;
//                }
//            }
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
void CTutorialUI::Draw()
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

        EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

        //switch (nCnt)
        //{
        //case 0://�w�i
        //    hr = EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
        //    break;

        //case 1://�L�[�}�E

        //    if (pManager->bGetInputState() == false)
        //    {//������@--true�ŃR���g���[���[
        //        hr = EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
        //    }
        //    else
        //    {//�}�E�X

        //    }

        //    break;

        //case 2://�R���g���[���[

        //    if (pManager->bGetInputState() == true)
        //    {//������@--true�ŃR���g���[���[
        //        hr = EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
        //    }

        //    break;
        //}





        EscDevice->SetTexture(0, nullptr);

    }




    const char* aData = "-TUTORIAL-";
   // CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 600.0f, SCREEN_HEIGHT / 2.0f - 340.0f, 0.0f), 80, CFont::FONT_GENKAI, D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f), aData);



    aData = "����̔C���́A-�V�^�g����-�̕ߔ����̗z���ł���B�P�Ɛ�����A�������Ԉȓ���\n�n�㕔�������j���G��n�����ɂđҋ@�B�g���͂̕ߔ��������������퐬���ł���B\n�ߔ����̂͊C�R�݂̂ōs���̂ŊȒP�ȔC���ɂȂ邾�낤�B";
    CFont::DrawTextSet(D3DXVECTOR3(100.0f, 28.0f, 0.0f), 30, CFont::FONT_SOUKOUMINCHO, D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f), aData);

    aData = "�z����� �}��";
    CFont::DrawTextSet(D3DXVECTOR3(100.0f, 150.0f, 0.0f), 30, CFont::FONT_SOUKOUMINCHO, D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f), aData);


    aData = "������@      A�őI��";
    CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH - 400.0f, SCREEN_HEIGHT - 45.0f, 0.0f), 40, CFont::FONT_SOUKOUMINCHO, D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f), aData);


    XINPUT_STATE joykeystate;
    //�V���C�p�b�g�̏�Ԃ��擾
    DWORD dwResult = XInputGetState(0, &joykeystate);

    switch (m_SelectNum)
    {
    case 0:
        aData = "�Q�[���ɐi��";
        CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 527.0f, SCREEN_HEIGHT / 2.0f + 128.0f, 0.0f), 53, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f), aData);



     


        aData = "�^�C�g���ɖ߂�";
        CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 527.0f, SCREEN_HEIGHT / 2.0f + 208.0f, 0.0f), 53, CFont::FONT_GENKAI, D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.8f), aData);


        break;

    case 1:

        aData = "�Q�[���ɐi��";

        CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 527.0f, SCREEN_HEIGHT / 2.0f + 128.0f, 0.0f), 53, CFont::FONT_GENKAI, D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.8f), aData);



 

        aData = "�^�C�g���ɖ߂�";
        CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 527.0f, SCREEN_HEIGHT / 2.0f + 208.0f, 0.0f), 53, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f), aData);


        break;

   
    }



}
//=============================
// Object����
//=============================
CTutorialUI* CTutorialUI::Create()
{
    CTutorialUI* pObject2D = new CTutorialUI;
    pObject2D->Init();
    return pObject2D;
}


void CTutorialUI::AddSelectNum(int addnum)
{
    m_SelectNum += addnum;

    if (m_SelectNum < 0)
    {
        m_SelectNum = 1;
    }
    else if (m_SelectNum > 1)
    {
        m_SelectNum = 0;
    }
}

void CTutorialUI::DirectSetNum(int Num)
{
    m_SelectNum = Num;

    if (m_SelectNum < 0)
    {
        m_SelectNum = 1;
    }
    else if (m_SelectNum > 1)
    {
        m_SelectNum = 0;
    }
}

int CTutorialUI::GetSelectNum()
{
    return m_SelectNum;
}
