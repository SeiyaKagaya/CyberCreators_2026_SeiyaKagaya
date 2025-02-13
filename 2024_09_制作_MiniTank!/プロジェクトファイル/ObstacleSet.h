//=========================================================
//
// ObstacleSet.cppで使う関数[ObstacleSet.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _OBSTACLESET_H
#define _OBSTACLESET_H//二重インクルード防止

#include "objectX.h"
#include "MathUtilities.h"

class CObstacleSet : public CObjectX
{
public:

	static const int STAGE_HITSIZE = 150;//ステージ配置物のサイズ

	//objectPass管理構造体
	typedef struct
	{
		int ModelIndex;			//モデル番号
		const char* pFilePass;	// ファイルパス
	} OBSTACLEINFO;

	typedef struct
	{
		bool bObstacleBool;  // 障害物フラグ
		int distance;        // スタート地点からの距離
		bool visited;        // 探索済みフラグ
		int parentX;         // 経路保存用の親ノードX
		int parentY;         // 経路保存用の親ノードY

		//最後しか使用せず
		int MoveNumX;
		int MoveNumZ;

	}GRIDDATA;

	CObstacleSet(int nPriority = CObject::LAYERINDEX_OBSTACLE);//コンストラクタ
	~CObstacleSet() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;


	//void HitCollision();																//当たり判定まとめ

	bool GetStageBlockbool();															//状態取得

	static CObstacleSet* Create(DATA SetData, int SetType, bool bBreak, bool _bPreview);//オブジェクト生成

	static void Resize(int count);														//配列のサイズ変更
	static void DataLoad(const char* filename);											//ステージデータの読み込みとクリエイトを行う
	static void previewModelLoad();														//設置予定モデル仮描画--同時に過去のプレビューモデルを検索後削除
	static void Model_DebugSave();														//セット状態セーブ

	bool GetPreviewBool();																//プレビューモデルか取得
	int GetModelType();																	//モデルタイプ取得

	static void Input();																//入力系(static)
	static void DebugSetDataDraw();														//セット用情報描画

	static void ObstacleScanMapping();													//障害物の検知とそれを踏まえたマッピング


private:

	CMathProc::CollisionData m_HitData = {};											//当たり判定データ
	static std::vector<OBSTACLEINFO> m_ObstacleInfo;									//ファイルパス格納
	static int m_ObstacleCount;															//モデル数(配列サイズ)

	bool m_bBreak = false;																//破壊可能か
	bool m_StageBlock = false;															//ステージblockか
	bool m_bPreview = false;															//プレビューか

	int m_nType = 0;																	//種別(x.file用

	static int m_NowSetModelIndex;														//設置するタイプ
	static int m_MAXModelIndex;															//モデル最大数
	static D3DXVECTOR3 m_SetRot;														//設置時角度	
};

#endif