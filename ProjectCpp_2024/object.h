//=========================================================
//
// object.cpp�Ŏg���֐�[object.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _OBJECT_H
#define _OBJECT_H

#include <Windows.h>
#include <d3dx9.h>
#include <memory>

class CObject
{
public:
    typedef struct
    {
        D3DXVECTOR3 Pos;
        D3DXVECTOR3 OldPos;
        D3DXVECTOR3 rot;
        D3DXVECTOR3 move;
        D3DXVECTOR3 MinLength;
        D3DXVECTOR3 MaxLength;
        float Radius;
    } DATA;

    // �`�揇
    typedef enum
    {
     

        //LAYERINDEX_PARTICLE = 0,
        LAYERINDEX_SKY,
        LAYERINDEX_PARTICLE,
        LAYERINDEX_HITBOX,
        LAYERINDEX_HITBOX_2D3D,
        LAYERINDEX_DEBUGWALL,
        LAYERINDEX_SEA,

        LAYERINDEX_BULLET,
        LAYERINDEX_ITEM,
        LAYERINDEX_ENEMY,
        LAYERINDEX_PLAYER,
        LAYERINDEX_EXPLOSION,
        LAYERINDEX_POLYGON  ,
        LAYERINDEX_BLOCK,
        LAYERINDEX_OBJECT,
        LAYERINDEX_OBJECT2D,

        LAYERINDEX_BULLET3D,
        

        LAYERINDEX_BLOCK3D,
        LAYERINDEX_OBSTACLE,
        LAYERINDEX_OBJECT3D,
        LAYERINDEX_OBJECTX,
        LAYERINDEX_PLAYER3D,
        LAYERINDEX_MODELPARTS,

        LAYERINDEX_NEWBULLET_MNG,
        LAYERINDEX_NEWBULLET,
        LAYERINDEX_MISSILE_MNG,
        LAYERINDEX_MISSILE,

        LAYERINDEX_MOTIONMODEL,
        LAYERINDEX_MOTIONPLAYER,
        LAYERINDEX_MOTIONENEMY_BASE,
        LAYERINDEX_MOTIONENEMY_NOMAL,
        LAYERINDEX_MOTIONENEMY_FAST,
        LAYERINDEX_MOTIONB2,

        LAYERINDEX_FADE,
        LAYERINDEX_LINE,
        LAYERINDEX_FOOTPRINT,
        LAYERINDEX_BILLBOARD,
        LAYERINDEX_SMOKE,
        LAYERINDEX_SHOTFIRE,
        LAYERINDEX_ReflectEffect,
        LAYERINDEX_EXPRO_BILL,
        LAYERINDEX_TARGETUI,
        LAYERINDEX_LINEUI,

        LAYERINDEX_HPLATTERUI,
        LAYERINDEX_HPGAUGEUI,
        LAYERINDEX_3DPARTICLE_MNG,
        LAYERINDEX_3DPARTICLE,
        LAYERINDEX_EXPLOSION3D,
        LAYERINDEX_SHIELD,//--
        LAYERINDEX_RESCUE, 
        LAYERINDEX_LOCKONUI,
        LAYERINDEX_LOCKONUIMAIN,
        LAYERINDEX_GAMEUI,
        LAYERINDEX_RESULTUI,
        LAYERINDEX_TIME,
        LAYERINDEX_SCORE,
        LAYERINDEX_TEXTWINDOW,
        LAYERINDEX_MAX,
    } LAYERINDEX;

    // �I�u�W�F�N�g�^�C�v
    typedef enum
    {
        OBJECT_FADE,
        OBJECT_SKY,
        OBJECT_HITBOX,
        OBJECT_HITBOX_2D3D,
        OBJECT_OBJECT,
        OBJECT_SEA,
        OBJECT_DEBUGWALL,
        OBJECT_LINE,
        OBJECT_TIME,
        OBJECT_SCORE,
        OBJECT_OBSTACLE,
        OBJECT_PLAYER,
        OBJECT_BULLET,
        OBJECT_PARTICLE,
        OBJECT_EXPLOSION,
        OBJECT_ENEMY,
        OBJECT_POLYGON,
        OBJECT_BLOCK,
        OBJECT_ITEM,
        OBJECT_OBJECT3D,
        OBJECT_FOOTPRINT,
        OBJECT_BILLBOARD,
        OBJECT_SMOKE,
        OBJECT_SHOTFIRE,
        OBJECT_ReflectEffect,
        OBJECT_EXPRO_BILL,
        OBJECT_TARGETUI,
        OBJECT_LINEUI,
     
        OBJECT_HPLATTER,
        OBJECT_HPGAUGE,
        OBJECT_3DPARTICLE,
        OBJECT_3DPARTICLE_MNG,
        OBJECT_EXPLOSION3D,
        OBJECT_RESCUE,

        
        OBJECT_OBJECT2D,
        OBJECT_OBJECTX,
        OBJECT_BULLET3D,
       
        OBJECT_PLAYER3D,
        OBJECT_BLOCK3D,

        OBJECT_NEWBULLET_MNG,
        OBJECT_NEWBULLET,
        OBJECT_MISSILE_MNG,
        OBJECT_MISSILE,
        OBJECT_MOTIONMODEL,
        OBJECT_MOTIONPLAYER,
        OBJECT_MOTIONENEMY_BASE,
        OBJECT_MOTIONENEMY_NOMAL,
        OBJECT_MOTIONENEMY_FAST,
        OBJECT_MOTIONB2,

        OBJECT_LOCKONUI,
        OBJECT_LOCKONUIMAIN,
        OBJECT_MODELPARTS,
        OBJECT_SHIELD,
        OBJECT_TEXTWINDOW,
        OBJECT_GAMEUI,
        OBJECT_RESULTUI,

        OBJECT_MAX,
    } OBJECTTYPE;

    static const int MAX_OBJECT = 1000; // OBJECT�ő吔

    CObject(int nPriority = LAYERINDEX_PARTICLE); // �R���X�g���N�^
    virtual ~CObject(); // �f�X�g���N�^
    virtual HRESULT Init() = 0;
    virtual void Uninit() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;

    static void ReleaseAll(); // �S�I�u�W�F�N�g�J��
    static void UpdateAll(); // �S�I�u�W�F�N�g�X�V
    static void DrawAll(); // �S�I�u�W�F�N�g�`��
    static void DelayDeath();//�x�点�������[�X��������

    //�V����Release�̑���I�I�I
    void SetDeath(const bool& bDeath) { m_bDeath = bDeath; };

    bool GetDeathNow() { return m_bDeath; };

    static int GetnNumAll();

    // �I�u�W�F�N�g�^�C�v��ݒ�
    void SetObjectType(OBJECTTYPE ObjectType);
    CObject::OBJECTTYPE GetObjectType();
    
    //�Ώۂ�object�̃|�C���^���擾
    static CObject* GetObjectPoint(int nPriority, OBJECTTYPE ObjectType);
    
    //�g�b�v�擾
    static CObject* GetpTop(int nPriority);

    //���̃|�C���^�̎擾
    CObject* GetNext();


    //DATA�\���̂̏������p
    static DATA DataInit();

    int GetNum();


protected:
    void Release(); // �������g�̊J��

private:

    static CObject* m_pTop[LAYERINDEX_MAX];//�擪��OBJECT�̃|�C���^
    static CObject* m_pCur[LAYERINDEX_MAX];//����(�Ō��)�̃|�C���^
    static CObject* m_pLastCreatedObject[LAYERINDEX_MAX];//�Ō�ɐ�������OBJECT�̃|�C���^

    CObject* m_pPrev;//�O��object�̃|�C���^
    CObject* m_pNext;//����object�̃|�C���^

    static int m_nNumAll; // �I�u�W�F�N�g����
    int m_nID; // �������g��ID
    int m_nPriority; // �`�揇
    OBJECTTYPE m_ObjectType;


    bool m_bDeath=false;//���S�t���O


};

#endif // _OBJECT_H