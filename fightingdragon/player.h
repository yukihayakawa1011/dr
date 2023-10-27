//============================
//
//プレイヤー処理(player.h)
//Author:早川 友貴
//
//============================
#ifndef _PLAYER_H_   //このマクロ定義がされていなかったら
#define _PLAYER_H_   //2重インクルード防止のマクロを定義する
#include "main.h"
#include "bilboard.h"
#include "objectx.h"
#include "model.h"
//#include "motion.h"
//#include "shadow.h"

//マクロ
#define PRESS_PLAYER (1.8f)
#define PLAYER_JUNP  (16.5f)
#define PLAYER_HEIGHT (19.0f) 
#define PLAYER_WIDTH (9.0f)
#define PLAYER_HITSPACEX (10.0f)	//プレイヤーの当たり判定X
#define PLAYER_HITSPACEY (20.0f)	//プレイヤーの当たり判定Y
#define PLAYER_ATTACKSPACE (20.0f) //プレイヤーの攻撃判定
#define ENEMY_HITSPACE (10.0f)		//敵の当たり判定
#define ENEMY_DAMAGESPACE (20.0f)  //敵の攻撃を受ける範囲

#define PLAYER_MIN_X (-15.0f)		//プレイヤーのX軸の左側
#define PLAYER_MAX_X (15.0f)		//プレイヤーのX軸の右側

#define PLAYER_MIN_Y (0.0f)			//プレイヤーのY軸の下
#define PLAYER_MAX_Y (50.0f)		//プレイヤーのY軸の下

#define PLAYER_MIN_Z (0.0f)			//プレイヤーのZ軸の下
#define PLAYER_MAX_Z (15.0f)		//プレイヤーのZ軸の下

#define PLAYER_PUNCH_SPEED (50)		//プレイヤーのパンチ間隔

class CPlayer : public CObjectx
{
public:
	typedef enum
	{
		PLAYER_PLAYER,			//プレイヤー
		PLAYER_MODE_MAX
	}PLAYER_SELECT;

	typedef enum
	{
		PLAYER_NONE = 0,		//通常状態
		PLAYER_DAMAGE,			//ダメージ状態
		PLAYER_INVINCIBLE,		//無敵状態
		PLAYER_GURD,			//プレイヤーガード状態
		PLAYER_MAX
	}PLAYER_STATE;

	//モーションの種類
	typedef enum
	{
		MOTIONTYPE_NEUTRAL = 0,		//待機
		MOTIONTYPE_MOVE,			//移動
		MOTIONTYPE_PUNCH0,			//パンチ
		MOTIONTYPE_KICK0,			//キック
		MOTIONTYPE_UNFAIR_PUNCH,	//unfairパンチ
		MOTIONTYPE_UNFAIR_KICK,		//unfairキック
		MOTIONTYPE_DAMAGE,			//ダメージ
		MOTIONTYPE_MAX,
	}MOTIONTYPE;

	//キーの構造体
	typedef struct
	{
		float m_fPosX;		//位置X
		float m_fPosY;		//位置Y
		float m_fPosZ;		//位置Z
		float m_fRotX;		//向きX
		float m_fRotY;		//向きY
		float m_fRotZ;		//向きZ
		//float m_frotDestX;  //目標の向きX
		//float m_frotDestY;  //目標の向きY
		//float m_frotDestZ;  //目標の向きZ
		//float m_fposDestX;  //目標の向きX
		//float m_fposDestY;  //目標の向きY
		//float m_fposDestZ;  //目標の向きZ
	}KEY;

	// キー情報の構造体
	typedef struct
	{
		int nFrame;				//再生フレーム
		KEY aKey[MAX_PART];	//各モデルのキー要素
	}KEY_INFO;

	//モーション情報の構造体
	typedef struct
	{
		bool bLoop;				//ループするかどうか
		int nNumKey;			//キーの総数
		KEY_INFO aKeyinfo[4];	//キー情報
	}INFO;

	CPlayer();
	~CPlayer();

	
	static CPlayer *Create(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight);
	HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight);

	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetJump(bool jump);
	bool GetJump(void);

	void HitBlock(bool bJump);
	bool HitEnemyPunch0(bool bDeath);
	bool HitEnemyKick0(bool bDeath);
	bool HitEnemyUnfarePunch(bool bDeath);
	bool HitEnemyUnfareKick(bool bDeath);


	bool HitPlayer(bool bDeath);

	void SetDeath(bool bDeath);
	bool GetDeath(void);

	void SetPlayerRot(bool bRot);
	bool GetPlayerRot(void);

	void SetPlayerAim(bool bAim);
	bool GetPlayerAim(void);
	void SetLife(int nLife);
	void SetState(PLAYER_STATE state);

	int GetLife(void);
	PLAYER_STATE GetState(void);

	void AddDamage(int nDamage);

	//モーション
	void SetMotionPlayer(MOTIONTYPE nType);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		//共有テクスチャ
	float m_fLength;							//対角線の長さ
	float m_movefLength;						//対角線の移動量
	float m_fAngle;								//対角線の角度
	D3DXVECTOR3 m_posold;						//古い位置
	bool m_bJump;								//ジャンプ中かどうか
	float m_fWidth;								//プレイヤー幅
	float m_fHeight;							//プレイヤー高さ

	//D3DXCOLOR m_col;							//色
	int m_nLife;								//体力
	//LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//頂点バッファへのポインタ

	D3DXMATRIX m_mtxWorld;						//ワールドマトリックス
	CModel *m_apModel[MAX_PART];				//モデルパーツへのポインタ
	int m_nNumModel;							//モデルパーツの総数

	int m_nldxShadow; //対象の影のインデックス(番号)

	bool m_bDeath;	  //プレイヤーの生死判定

	float m_ShotRot;  //弾の方向を決める

	bool m_bRot;	  //プレイヤーの向きを教える

	bool m_bAim;									//構えているかどうか

	PLAYER_STATE m_PlayerState;						//プレイヤーの状態

	D3DXMATERIAL m_NoneMat;  //マテリアル通常処理
	D3DXMATERIAL m_RedMat;  //マテリアルを赤くする処理
	D3DXMATERIAL m_InvincibleMat;  //マテリアルを赤くする処理

	D3DXCOLOR m_stateCol;			//プレイヤーの状態による色の設定

	LPD3DXBUFFER m_pBuffMat = NULL; //マテリアルへのポインタ

	int m_nCntState;		//プレイヤー状態カウント

	INFO m_aInfo[MAX_PART];		//パーツの最大数
	int m_nNumAll;				//数の最大数
	int m_nType;				//種類
	bool bLoop;					//終了するかどうか
	int m_nKey;					//キーの数
	int m_nCounter;				//モーションカウンター
	bool m_bFinish;				//終了するかどうか

	CModel **m_ppModel;			//モデルへのポインタ

	int m_nFrameCnt;			//フレーム数えるよう

	bool m_bAttack;				//攻撃状態に入っているかどうか

	D3DXVECTOR3 m_InitPartPos[MAX_PART];	//パーツの初期位置

	int nPunchSpeed;

	int m_nEnemy;					//何番めの敵か知る

	bool m_bSpawn;					//スポーンしたかどうか

	bool m_bUnfare;					//unfair攻撃を使おうとしてるか

	int m_nKill;					//何人倒したか
};

#endif


