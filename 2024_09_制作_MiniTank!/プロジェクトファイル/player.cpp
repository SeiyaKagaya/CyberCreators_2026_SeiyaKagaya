//=======================================================
//
//polygonに関する処理[polygon.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "player.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "input.h"
#include"ballet.h"
#include <cmath> // 三角関数を使うために必要
#include "all_texture.h"

//=============================
//コンストラクタ
//=============================
CPlayer::CPlayer(int nPriority) :CObject2D(nPriority), m_nCounterAnim(0), m_nDirectionMove(1), m_nPatternAnim(0), m_MAG(0.3f), m_bLandingNow(false)
{
	m_HitData.bHit = false;
	m_HitData.HitAngle = D3DXVECTOR3(0.0f, 0.0f,0.0f);
	m_HitData.ResultDistance = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_HitData.targetIndex = -1;

	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();
	pRenderer = pManager->GetRenderer();
	LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();
	
	//取得
	DATA EscData = GetDATA();
	EscData.Pos = D3DXVECTOR3(SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT / 2.0f, 0.0f);
	SetDATA(EscData);//格納

	SetObjectType(CObject2D::OBJECT_PLAYER);
}

//=============================
//デストラクタ
//=============================
CPlayer::~CPlayer()
{
}

//=============================
//初期設定(頂点バッファ生成)
//=============================
HRESULT CPlayer::Init()
{
	CObject2D::Init();//基本設定
	//取得
	LPDIRECT3DVERTEXBUFFER9 ESCpVtxBuff = GetpVtxBuffer();

	VERTEX_2D* pVtx;
	ESCpVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//対角線の長さを算出
	m_fLength = sqrtf(PLAYER_HEIGHT * PLAYER_HEIGHT * m_MAG + PLAYER_WIDE * PLAYER_WIDE * m_MAG) / 2.0f;//幅*幅+高さ*高さ

	//対角線の角度を算出
	m_fAngle = atan2f(PLAYER_WIDE * m_MAG, PLAYER_HEIGHT * m_MAG);//高さ、幅

	//取得
	DATA EscData = GetDATA();
	EscData.Radius = m_fLength;
	EscData.MinLength = D3DXVECTOR3(-PLAYER_WIDE/2, -PLAYER_HEIGHT/2, 0.0f);//左上
	EscData.MaxLength = D3DXVECTOR3(PLAYER_WIDE/2, PLAYER_HEIGHT/2, 0.0f);//左上

	SetDATA(EscData);//格納

	pVtx[0].pos.x = EscData.Pos.x - PLAYER_WIDE / 2;//左上
	pVtx[0].pos.y = EscData.Pos.y - PLAYER_HEIGHT / 2;//左上
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = EscData.Pos.x + PLAYER_WIDE / 2;//右上
	pVtx[1].pos.y = EscData.Pos.y - PLAYER_HEIGHT / 2;//右上
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = EscData.Pos.x - PLAYER_WIDE / 2;//左下
	pVtx[2].pos.y = EscData.Pos.y + PLAYER_HEIGHT / 2;//左下
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = EscData.Pos.x + PLAYER_WIDE / 2;//右下
	pVtx[3].pos.y = EscData.Pos.y + PLAYER_HEIGHT / 2;//右下
	pVtx[3].pos.z = 0.0f;

	//テクスチャ座標を更新
	pVtx[0].tex = D3DXVECTOR2(((1.0f / 4) * m_nPatternAnim), ((1.0f / 2) * m_nDirectionMove));//左上//ニュートラルの状態
	pVtx[1].tex = D3DXVECTOR2(((1.0f / 4) * (m_nPatternAnim + 1.0f)), ((1.0f / 2) * m_nDirectionMove));//右上
	pVtx[2].tex = D3DXVECTOR2(((1.0f / 4) * m_nPatternAnim), ((1.0f / 2) * (m_nDirectionMove + 1.0f)));//左下
	pVtx[3].tex = D3DXVECTOR2(((1.0f / 4) * (m_nPatternAnim + 1.0f)), ((1.0f / 2) * (m_nDirectionMove + 1.0f)));//右下

	ESCpVtxBuff->Unlock();
		
	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();
	pRenderer = pManager->GetRenderer();
	LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();
	
	//テクスチャ読み込み
	LPDIRECT3DTEXTURE9	m_ESCpTexture = nullptr;

	//テクスチャ取得
	CAllTexture* pTexture = pManager->GetTexture();

	int texIndex = pTexture->Regist("DATA\\TEXTURE\\Player001.png", EscDevice);//テクスチャ登録

	m_ESCpTexture = pTexture->GetAddress(texIndex);
	BindTexture(m_ESCpTexture);//設定

	SetDATA(EscData);//格納

	SetObjectType(CObject2D::OBJECT_PLAYER);

	return S_OK;
}

//=============================
//終了処理(頂点バッファ破棄)
//=============================
void CPlayer::Uninit()
{
	CObject2D::Uninit();
}

//=============================
//更新(頂点情報の更新)
//=============================
void CPlayer::Update()
{
	bool HitData = false;
	
	//取得
	DATA EscData = GetDATA();

	Action_Keyboard();//Keyboard操作
	
	EscData = GetDATA();//再取得

	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	CInputJoyPad* JoyPad = pManager->GetJoyPad();

	if (JoyPad->IsJoyPadConnected())//接続時
	{
		Action_JoyPad(); // ジョイパッド操作
	}

	EscData = GetDATA();//再取得
	EscData.OldPos = EscData.Pos;
	EscData.Pos += EscData.move;

	m_nPatternAnim++;

	if (m_bLandingNow == false)
	{
		EscData.move.y += 0.9f;//試験重力
	}
	
	m_bLandingNow = false;//着地Reset

	SetDATA(EscData);//格納

	HitCollision();

	EscData = GetDATA();//再取得

	bool bHit = false;

	if (EscData.Pos.x+ PLAYER_WIDE/2 >=SCREEN_WIDTH)
	{//右
		EscData.Pos.x = SCREEN_WIDTH - (PLAYER_WIDE / 2.0f  - DISTANCE);
		bHit = true;
	}
	else if (EscData.Pos.x - PLAYER_WIDE / 2.0f <= 0)
	{//左
		EscData.Pos.x =(PLAYER_WIDE / 2.0f + DISTANCE);
		bHit = true;
	}
	if (EscData.Pos.y +DISTANCE>= SCREEN_HEIGHT)
	{//下
		EscData.Pos.y = SCREEN_HEIGHT - (DISTANCE* 2.0f);

		bHit = true;
		m_bLandingNow = true;
	}
	else if (EscData.Pos.y - PLAYER_HEIGHT/ 2.0f <= 0)
	{//上
		EscData.Pos.y = (PLAYER_HEIGHT/ 2.0f + DISTANCE);
		bHit = true;
	}

	//移動量を更新(疑似慣性で減衰)
	EscData.move.x += (0.0f - EscData.move.x) * 0.1f;

	SetDATA(EscData);//格納
	InputpVtx();//ポリゴン更新
	CObject2D::Update();
}

//=============================
//描画処理(POLYGON描画)
//=============================
void CPlayer::Draw()
{
	CObject2D::Draw();
}

//=============================
//Object生成
//=============================
CPlayer* CPlayer::Create()
{
	CPlayer* pPlayer = new CPlayer;
	pPlayer->Init();

	return pPlayer;
}

//=============================
//設定格納
//=============================
void CPlayer::InputpVtx()
{
	//取得
	DATA EscData = GetDATA();
	VERTEX_2D EscVtx[BASE_INDEX];

	EscVtx[0].pos.x = EscData.Pos.x - PLAYER_WIDE / 2;//左上
	EscVtx[0].pos.y = EscData.Pos.y - PLAYER_HEIGHT / 2;//左上
	EscVtx[0].pos.z = 0.0f;

	EscVtx[1].pos.x = EscData.Pos.x + PLAYER_WIDE / 2;//右上
	EscVtx[1].pos.y = EscData.Pos.y - PLAYER_HEIGHT / 2;//右上
	EscVtx[1].pos.z = 0.0f;

	EscVtx[2].pos.x = EscData.Pos.x - PLAYER_WIDE / 2;//左下
	EscVtx[2].pos.y = EscData.Pos.y + PLAYER_HEIGHT / 2;//左下
	EscVtx[2].pos.z = 0.0f;

	EscVtx[3].pos.x = EscData.Pos.x + PLAYER_WIDE / 2;//右下
	EscVtx[3].pos.y = EscData.Pos.y + PLAYER_HEIGHT / 2;//右下
	EscVtx[3].pos.z = 0.0f;

	//テクスチャ座標を更新
	EscVtx[0].tex = D3DXVECTOR2(((1.0f / 4) * m_nPatternAnim), ((1.0f / 2) * m_nDirectionMove));//左上//ニュートラルの状態
	EscVtx[1].tex = D3DXVECTOR2(((1.0f / 4) * (m_nPatternAnim + 1.0f)), ((1.0f / 2) * m_nDirectionMove));//右上
	EscVtx[2].tex = D3DXVECTOR2(((1.0f / 4) * m_nPatternAnim), ((1.0f / 2) * (m_nDirectionMove + 1.0f)));//左下
	EscVtx[3].tex = D3DXVECTOR2(((1.0f / 4) * (m_nPatternAnim + 1.0f)), ((1.0f / 2) * (m_nDirectionMove + 1.0f)));//右下

	SetpVtx(EscVtx);
}

//=============================
//操作受付Keyboard
//=============================
void CPlayer::Action_Keyboard()
{
	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();
	CInputKeyboard* keyboard = pManager->GetKeyboard();

	//---------------------------------------------------------移動系
	//取得
	DATA EscData = GetDATA();

	float MoveSpeed = 1.0f;

	if (keyboard->GetPress(DIK_W) == true)
	{
		EscData.move.y += -MoveSpeed;
	
	}
	if (keyboard->GetPress(DIK_A) == true)
	{
		EscData.move.x += -MoveSpeed;
		m_nDirectionMove = 1;
	}
	if (keyboard->GetPress(DIK_S) == true)
	{
		EscData.move.y += MoveSpeed;
	}
	if (keyboard->GetPress(DIK_D) == true)
	{
		EscData.move.x += MoveSpeed;
		m_nDirectionMove = 0;
	}

	if (keyboard->GetTrigger(DIK_SPACE) == true)
	{
		EscData.move.y = cosf(-0.75f * D3DX_PI) * (2.0f * 15.0f);
	}

	if (keyboard->GetPress(DIK_LEFT) == true)
	{
		EscData.rot.z += 0.03f;

	}
	if (keyboard->GetPress(DIK_RIGHT) == true)
	{
		EscData.rot.z -= 0.03f;
	}

	SetDATA(EscData);//格納

	//---------------------------------------------------------移動系ここまで
	if (keyboard->GetPress(DIK_N) == true)
	{
		if (MAXSHOTDERAY <= m_BulletShotDelay)
		{
			DATA SetData;
			SetData.Pos = EscData.Pos + D3DXVECTOR3(0.0f, -35.0f, 0.0f);

			SetData.move = D3DXVECTOR3(cos(-EscData.rot.z * D3DX_PI), sin(-EscData.rot.z * D3DX_PI), 0.0f);//角度制定
			CBullet::Create(SetData);

			m_BulletShotDelay = 0;
		}
		else
		{
			m_BulletShotDelay++;
		}
	}

	if (keyboard->GetTrigger(DIK_DOWN) == true)
	{
		DATA SetData;
		SetData.Pos = EscData.Pos;
		SetData.move = D3DXVECTOR3(cos(-EscData.rot.z * D3DX_PI), sin(-EscData.rot.z * D3DX_PI), 0.0f);//角度制定

		CBullet::Create(SetData);
	}

	SetDATA(EscData);//格納
}

//=============================
//操作受付ジョイパッド
//=============================
void CPlayer::Action_JoyPad()
{
	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();
	CInputJoyPad* JoyPad = pManager->GetJoyPad();
	XINPUT_STATE joykeystate;

	//ショイパットの状態を取得
	DWORD dwResult = XInputGetState(0, &joykeystate);

	//取得
	DATA EscData = GetDATA();

	float MoveSpeed = 1.0f;

	bool bMove = false;

	if (joykeystate.Gamepad.sThumbLX <= -(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000))
	{//Aがおされた(左)
		m_nDirectionMove = 1;

		bMove = true;
	}
	else if (joykeystate.Gamepad.sThumbLX >= (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000))
	{//Dがおされた(右)
		m_nDirectionMove = 0;
		bMove = true;
	}
	else if (joykeystate.Gamepad.sThumbLY >= (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000))
	{//Wがおされた(上)
		bMove = true;
	}
	else if (joykeystate.Gamepad.sThumbLY <= -(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000))
	{//Sがおされた(下)
		bMove = true;
	}

	if (JoyPad->GetPress(CInputJoyPad::JOYKEY_UP) == true)
	{
		EscData.move.y += -MoveSpeed;
	}
	if (JoyPad->GetPress(CInputJoyPad::JOYKEY_LEFT) == true)
	{
		EscData.move.x += -MoveSpeed;
		m_nDirectionMove = 1;
	}
	if (JoyPad->GetPress(CInputJoyPad::JOYKEY_DOWN) == true)
	{
		EscData.move.y += MoveSpeed;
	}
	if (JoyPad->GetPress(CInputJoyPad::JOYKEY_RIGHT) == true)
	{
		EscData.move.x += MoveSpeed;
		m_nDirectionMove = 0;
	}

	if (bMove == true)
	{
		float Angle2 = atan2f((float)-joykeystate.Gamepad.sThumbLX, (float)-joykeystate.Gamepad.sThumbLY);//これが方角

		EscData.move.x = sinf(Angle2 - (1.0f * D3DX_PI)) * MoveSpeed * 10.0f;//三角関数利用して移動の長さを代入
		EscData.move.y = -cosf(Angle2 - (1.0f * D3DX_PI)) * MoveSpeed * 10.0f;//三角関数利用して移動の長さを代入
	
	}

	bool bMove2= false;

	if (joykeystate.Gamepad.sThumbRX <= -(XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 6000))
	{//Aがおされた(左)
		bMove = true;
	}
	else if (joykeystate.Gamepad.sThumbRX >= (XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 6000))
	{//Dがおされた(右)
		bMove = true;
	}
	else if (joykeystate.Gamepad.sThumbRY >= (XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 6000))
	{//Wがおされた(上)
		bMove = true;
	}
	else if (joykeystate.Gamepad.sThumbRY <= -(XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 6000))
	{//Sがおされた(下)
		bMove = true;
	}

	if (bMove == true)
	{
		float Angle2 = atan2f((float)joykeystate.Gamepad.sThumbRX, (float)-joykeystate.Gamepad.sThumbRY);//これが方角
		EscData.rot.z = (Angle2/D3DX_PI)+ 1.5f;
	}

	if (JoyPad->GetTrigger(CInputJoyPad::JOYKEY_A)== true)
	{
		EscData.move.y = cosf(-0.75f * D3DX_PI) * (2.0f * 15.0f);
	}

	//入力の有無を確認して分岐
	if (joykeystate.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD || joykeystate.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)//トリガー
	{//L2キー
	
		if (MAXSHOTDERAY <= m_BulletShotDelay)
		{
			DATA SetData;
			SetData.Pos = EscData.Pos + D3DXVECTOR3(0.0f, -35.0f, 0.0f);

			SetData.move = D3DXVECTOR3(cos(-EscData.rot.z * D3DX_PI), sin(-EscData.rot.z * D3DX_PI), 0.0f);//角度制定
			CBullet::Create(SetData);

			m_BulletShotDelay = 0;
		}
		else
		{
			m_BulletShotDelay++;
		}
	}
	SetDATA(EscData);//格納
}
//=============================
//当たり判定まとめ
//=============================
void CPlayer::HitCollision()
{
	//取得
	DATA EscData = GetDATA();

	//当たり判定計算
	m_HitData = CMathProc::CheckBoxCollision_2D(EscData.Pos, EscData.OldPos, EscData.MinLength, EscData.MaxLength, CObject2D::OBJECT_BLOCK);

	if (m_HitData.bHit == true)
	{//接触
		if (m_HitData.HitAngle.x == 1)
		{//右
			EscData.Pos.x += m_HitData.ResultDistance.x;

			EscData.move.x = 0.0f;
		}
		else if (m_HitData.HitAngle.x == -1)
		{//左
			EscData.Pos.x -= m_HitData.ResultDistance.x;
			EscData.move.x = 0.0f;
		}
		else if (m_HitData.HitAngle.y == 1)
		{//下
 			EscData.Pos.y += m_HitData.ResultDistance.y;

			EscData.move.y = 0.0f;
		}
		else if (m_HitData.HitAngle.y == -1)
		{//上
			EscData.Pos.y -= m_HitData.ResultDistance.y;
			EscData.move.y = 0.0f;
		}
	}

	SetDATA(EscData);//格納

	//判定Reset
	m_HitData.bHit = false;

	//当たり判定計算
	m_HitData = CMathProc::CheckBoxCollision_2D(EscData.Pos, EscData.OldPos, EscData.MinLength, EscData.MaxLength, CObject2D::OBJECT_ITEM);

}