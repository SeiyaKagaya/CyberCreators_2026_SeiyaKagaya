//=========================================================
//
// StageCollisionBox[StageCollisionBox.cpp]
// Author seiya kagaya
//
//=========================================================
#include"StageCollisionBox.h"
//#include "renderer.h"
#include "manager.h"
//#include "explosion.h"
//#include <stdio.h>
//#include <cstring>
//#include <iostream> // �f�o�b�O�p

//#include <fstream>
//#include <climits> // INT_MAX
//#include <limits.h>





//=============================
// �R���X�g���N�^
//=============================
StageCollisionBox::StageCollisionBox(int nPriority) :CObjectX(nPriority)
{

}

//=============================
// �f�X�g���N�^
//=============================
StageCollisionBox::~StageCollisionBox()
{
}

//=============================
// ������
//=============================
HRESULT StageCollisionBox::Init()
{
    CObjectX::Init();

    CRenderer* pRenderer = nullptr;
    CManager* pManager = CManager::GetInstance();
    pRenderer = pManager->GetRenderer();

    LPD3DXMESH pMesh = nullptr; // Mesh�|�C���^
    LPD3DXBUFFER pBuffMat = nullptr; // �}�e���A���ւ̃|�C���^
    DWORD dwNumMat = 0; // �}�e���A���̐�

    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

    // �t�@�C���̓ǂݍ���
    D3DXLoadMeshFromX("DATA\\MODEL\\DebugModel\\BOX.x",
        D3DXMESH_SYSTEMMEM,
        EscDevice,
        NULL,
        &pBuffMat,
        NULL,
        &dwNumMat,
        &pMesh);

    D3DXMATERIAL* pMat = (D3DXMATERIAL*)pBuffMat->GetBufferPointer();

    //�e�N�X�`���ǂݍ���
    LPDIRECT3DTEXTURE9	m_ESCpTexture = nullptr;

    //�e�N�X�`���擾
    CAllTexture* pTexture = pManager->GetTexture();




    for (int nCntMat = 0; nCntMat < (int)dwNumMat; nCntMat++)
    {
        if (pMat[nCntMat].pTextureFilename != NULL)
        {
            //LPDIRECT3DTEXTURE9 EscTex = {};

            //�e�N�X�`���ǂݍ���
            //D3DXCreateTextureFromFile(EscDevice, pMat[nCntMat].pTextureFilename, &EscTex);

            int texIndex = pTexture->Regist(pMat[nCntMat].pTextureFilename, EscDevice);//�e�N�X�`���o�^

            m_ESCpTexture = pTexture->GetAddress(texIndex);

            BindTexture(m_ESCpTexture, nCntMat);//�ݒ�

      //      BindTexture(EscTex, nCntMat);
        }
    }


    SetXfireData(pMesh, pBuffMat, dwNumMat); // �f�[�^�i�[

    SetObjectType(CObject::OBJECT_HITBOX);


    
    return S_OK;
}

//=============================
// �j��
//=============================
void StageCollisionBox::Uninit()
{
    CObjectX::Uninit();
}

//=============================
// �X�V
//=============================
void StageCollisionBox::Update()
{


}

//=============================
// �`��
//=============================
void StageCollisionBox::Draw()
{
    
#if _DEBUG
    
    SizeMagChangebool(true);
    SetColorChangeBool(true);
    CObjectX::Draw();

#else
   
#endif // _D
}

//=============================
// ����
//=============================
StageCollisionBox* StageCollisionBox::Create(DATA SetData)
{
    StageCollisionBox* pObstacle = new StageCollisionBox;

    pObstacle->Init();

    // �擾
    DATA EscData = pObstacle->GetDATA();
    EscData = SetData; // �ڂ�

    D3DXVECTOR3 SizeMag;

       //�T�C�Y�ϓ�
    SizeMag.x = EscData.MaxLength.x / 10.0f;
    SizeMag.y = EscData.MaxLength.y / 20.0f;
    SizeMag.z = EscData.MaxLength.z / 10.0f;
    
    pObstacle->SetSizeMag(SizeMag);//�{���ϓ�

    pObstacle->SetChangeColor(D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.1f));

    pObstacle->SetDATA(EscData); // �i�[

    return pObstacle;
}




//=============================
// �����蔻��܂Ƃ�
//=============================
void StageCollisionBox::HitCollision()
{
    //// �擾
    //DATA EscData = GetDATA();

    //// �����蔻��v�Z
    //m_HitData = CMathProc::CheckBoxCollision_3D(EscData.Pos, EscData.OldPos, EscData.MinLength, EscData.MaxLength, OBJECT_BLOCK3D,LAYERINDEX_BLOCK3D,EscData.move);

    //if (m_HitData.bHit == true)
    //{
    //    if (m_HitData.HitAngle.x == 1)
    //    {
    //        EscData.Pos.x += m_HitData.ResultDistance.x;
    //        EscData.move.x = 0.0f;
    //    }
    //    else if (m_HitData.HitAngle.x == -1)
    //    {
    //        EscData.Pos.x -= m_HitData.ResultDistance.x;
    //        EscData.move.x = 0.0f;
    //    }
    //    else if (m_HitData.HitAngle.y == 1)
    //    {
    //        EscData.Pos.y += m_HitData.ResultDistance.y;
    //        EscData.move.y = 0.0f;
    //    }
    //    else if (m_HitData.HitAngle.y == -1)
    //    {
    //        EscData.Pos.y -= m_HitData.ResultDistance.y;
    //        EscData.move.y = 0.0f;
    //    }
    //    else if (m_HitData.HitAngle.z == 1)
    //    {
    //        EscData.Pos.z += m_HitData.ResultDistance.z;
    //        EscData.move.z = 0.0f;
    //    }
    //    else if (m_HitData.HitAngle.z == -1)
    //    {
    //        EscData.Pos.z -= m_HitData.ResultDistance.z;
    //        EscData.move.z = 0.0f;
    //    }
    //}

    //SetDATA(EscData); // �i�[
}
