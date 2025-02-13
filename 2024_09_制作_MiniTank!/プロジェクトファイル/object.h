//=========================================================
//
// object.cppで使う関数[object.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _OBJECT_H
#define _OBJECT_H

#include <Windows.h>
#include <d3dx9.h>

class CObject
{
public:

    //よく使う基本セットを作っておく
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

    // 描画順
    typedef enum
    {
        LAYERINDEX_PARTICLE=0,
        LAYERINDEX_HITBOX,
        LAYERINDEX_BULLET,
        LAYERINDEX_ITEM,
        LAYERINDEX_ENEMY,
        LAYERINDEX_PLAYER,
        LAYERINDEX_EXPLOSION,
        LAYERINDEX_POLYGON  ,
        LAYERINDEX_BLOCK,
        LAYERINDEX_OBJECT,
        LAYERINDEX_OBJECT2D,
        LAYERINDEX_BLOCK3D,
        LAYERINDEX_OBSTACLE,
        LAYERINDEX_OBJECT3D,
        LAYERINDEX_OBJECTX,
        //LAYERINDEX_PLAYER3D,
        LAYERINDEX_MODELPARTS,
        LAYERINDEX_NEWBULLET,
        LAYERINDEX_MOTIONMODEL,
        LAYERINDEX_MOTIONPLAYER,
        LAYERINDEX_MOTIONENEMY_BASE,
        LAYERINDEX_MOTIONENEMY_NOMAL,
        LAYERINDEX_MOTIONENEMY_FAST,
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
        LAYERINDEX_3DPARTICLE,
        LAYERINDEX_EXPLOSION3D,
        LAYERINDEX_RESCUE,
        LAYERINDEX_GAMEUI,
        LAYERINDEX_RESULTUI,
        LAYERINDEX_TIME,
        LAYERINDEX_SCORE,
        LAYERINDEX_MAX,
    } LAYERINDEX;

    // オブジェクトタイプ
    typedef enum
    {
        OBJECT_FADE=0,
        OBJECT_HITBOX,
        OBJECT_OBJECT,
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
        OBJECT_EXPLOSION3D,
        OBJECT_RESCUE,
        OBJECT_OBJECT2D,
        OBJECT_OBJECTX,
        //OBJECT_PLAYER3D,
        OBJECT_BLOCK3D,
        OBJECT_MODELPARTS,
        OBJECT_NEWBULLET,
        OBJECT_MOTIONMODEL,
        OBJECT_MOTIONPLAYER,
        OBJECT_MOTIONENEMY_BASE,
        OBJECT_MOTIONENEMY_NOMAL,
        OBJECT_MOTIONENEMY_FAST,
        OBJECT_GAMEUI,
        OBJECT_RESULTUI,
        OBJECT_MAX,
    } OBJECTTYPE;

    static const int MAX_OBJECT = 1000; // OBJECT最大数

    CObject(int nPriority = LAYERINDEX_PARTICLE); // コンストラクタ
    virtual ~CObject(); // デストラクタ
    virtual HRESULT Init() = 0;
    virtual void Uninit() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;

    static void ReleaseAll(); // 全オブジェクト開放
    static void UpdateAll();  // 全オブジェクト更新
    static void DrawAll();    // 全オブジェクト描画
    static void DelayDeath(); //遅らせたリリースをここで

    //新しいReleaseの代わり！！！
    void SetDeath(const bool& bDeath) { m_bDeath = bDeath; };

    //破棄予定か取得
    bool GetDeathNow() { return m_bDeath; };

    //OBJECTの総数取得
    static int GetnNumAll();

    // オブジェクトタイプを設定
    void SetObjectType(OBJECTTYPE ObjectType);

    //オブジェクトタイプを取得
    CObject::OBJECTTYPE GetObjectType();
    
    //対象のobjectのポインタを取得
    static CObject* GetObjectPoint(int nPriority, OBJECTTYPE ObjectType);
    
    //トップ取得
    static CObject* GetpTop(int nPriority);

    //次のポインタの取得
    CObject* GetNext();

    //DATA構造体の初期化用
    static DATA DataInit();

protected:
    void Release(); // 自分自身の開放

private:

    static CObject* m_pTop[LAYERINDEX_MAX];               //先頭のOBJECTのポインタ
    static CObject* m_pCur[LAYERINDEX_MAX];               //現在(最後尾)のポインタ
    static CObject* m_pLastCreatedObject[LAYERINDEX_MAX]; //最後に生成したOBJECTのポインタ
    static int m_nNumAll;                                 // オブジェクト総数
    OBJECTTYPE m_ObjectType;                              // オブジェクトタイプ
    CObject* m_pPrev = nullptr;                           //前のobjectのポインタ
    CObject* m_pNext = nullptr;                           //次のobjectのポインタ
    int m_nID = 0;                                        // 自分自身のID
    int m_nPriority = 0;                                  // 描画順
    bool m_bDeath = false;                                //死亡フラグ
};

#endif // _OBJECT_H