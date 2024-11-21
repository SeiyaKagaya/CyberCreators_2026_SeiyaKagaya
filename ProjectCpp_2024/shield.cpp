//=========================================================
//
// CShield[CShield.cpp]
// Author seiya kagaya
//
//=========================================================
#include"shield.h"
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
CShield::CShield(int nPriority) :CObjectX(nPriority)
{

}

//=============================
// �f�X�g���N�^
//=============================
CShield::~CShield()
{
}

//=============================
// ������
//=============================
HRESULT CShield::Init()
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
    D3DXLoadMeshFromX("DATA\\MODEL\\Shield.x",
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

    SetObjectType(CObject::OBJECT_SHIELD);



    return S_OK;
}

//=============================
// �j��
//=============================
void CShield::Uninit()
{
    CObjectX::Uninit();
}

//=============================
// �X�V
//=============================
void CShield::Update()
{
    DATA EscData = GetDATA();//�Ď擾
  //  EscData.Pos = m_pParent->GetDATA().Pos;

    EscData.rot.x += 0.1f;//���ꂪ�厖
 
   EscData.rot.y = -D3DX_PI * 0.5f;

    EscData.rot.z += 0.1f;
    SetDATA(EscData);
}

//=============================
// �`��
//=============================
void CShield::Draw()
{
    CRenderer* pRenderer = nullptr;

    CManager* pManager = CManager::GetInstance();

    pRenderer = pManager->GetRenderer();

    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();


    //DATA EscData = GetDATA();//�Ď擾

    //D3DXMATRIX EscMtxWorld;

    //D3DXMATRIX mtxRot, mtxTrans, mtxParent;//�v�Z�p�}�g���b�N�X

    ////���[���h�}�g���b�N�X�̏�����
    //D3DXMatrixIdentity(&m_mtxWorld);

    ////�����𔽉f
    //D3DXMatrixRotationYawPitchRoll(&mtxRot, EscData.rot.y, EscData.rot.x, EscData.rot.z);

    //D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

    ////�ʒu�𔽉f
    //D3DXMatrixTranslation(&mtxTrans, EscData.Pos.x, EscData.Pos.y, EscData.Pos.z);

    //D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

    ////�e�q�֌W
    //if (m_pParentParts != nullptr)
    //{
    //    //�����̎�̃}�g���b�N�X�Ƃ�����(player/enemy)�Ȃ�

    //    //
    //    EscDevice->GetTransform(D3DTS_WORLD, &EscMtxWorld);//�Ƃ肠�����ŐV�̃}�g���b�N�X�擾


    //    D3DXMATRIX EscMat = m_pParentParts->GetMtxWorld();

    //    //�n�c�Ƃ�����
    //    D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &EscMat);
    //}


 ////   ChangeModelPartsbool(true);//�p�[�c�`�悶�}�g���b�N�X�ύX
 //   SetModelMtxWorld(m_mtxWorld);//�}�g���b�N�X�i�[




#if _DEBUG
    if (m_bDrawOk == true)
    {
        SetSizeMag(D3DXVECTOR3 (20.0f,20.0f,20.0f));//�{��
        SizeMagChangebool(true);
      //  SetColorChangeBool(true);
     //   SetNotLight(true);
        CObjectX::Draw();
    }
#else

#endif // _D
}

//=============================
// ����
//=============================
CShield* CShield::Create(DATA SetData, CObjectMotionPlayer* pMotion)
{
    CShield* pObstacle = new CShield;

    pObstacle->Init();

    // �擾
    DATA EscData = pObstacle->GetDATA();
    EscData = SetData; // �ڂ�

    D3DXVECTOR3 SizeMag;

    //�T�C�Y�ϓ�
    SizeMag.x = EscData.MaxLength.x / 10.0f;
    SizeMag.y = EscData.MaxLength.y / 20.0f;
    SizeMag.z = EscData.MaxLength.z / 10.0f;

  //  EscData.rot.y = D3DX_PI * 0.5f;

    pObstacle->SetSizeMag(SizeMag);//�{���ϓ�

 //   pObstacle->SetChangeColor(D3DXCOLOR(1.0f,1.0f,0.0f,0.7f));

    pObstacle->SetDATA(EscData); // �i�[
    pObstacle->SetParent(pMotion);
    return pObstacle;
}




//=============================
// �����蔻��܂Ƃ�
//=============================
void CShield::HitCollision()
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
