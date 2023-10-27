//============================
//
//敵処理(enemy.h)
//Author:早川 友貴
//
//============================
#ifndef _ENEMY_H_   //このマクロ定義がされていなかったら
#define _ENEMY_H_   //2重インクルード防止のマクロを定義する
#include "main.h"
#include "objectx.h"
#include "model.h"

//マクロ定義
#define MAX_ENEMY (20)				//敵の最大数
#define MAX_MODEL (17)				//モデルの数

#define ENEMY_MIN_X (-10.0f)		//敵のX軸の左側
#define ENEMY_MAX_X (10.0f)			//敵のX軸の右側
	   
#define ENEMY_MIN_Y (0.0f)			//敵のY軸の下
#define ENEMY_MAX_Y (15.0f)			//敵のY軸の上
	   
#define ENEMY_MIN_Z (0.0f)			//敵のZ軸の下
#define ENEMY_MAX_Z (15.0f)			//敵のZ軸の上

class CEnemy : public CObjectx
{
public:

	typedef enum 
	{
		ENEMYSTATE_NONE = 0,
		ENEMYSTATE_ATTACK,
		ENEMYSTATE_DAMAGE,
		ENEMYSTATE_GURD,
		ENEMYSTATE_MAX
	}EnemyState;

	//モーションの種類
	typedef enum
	{
		MOTIONTYPE_NEUTRAL = 0, //待機
		MOTIONTYPE_MOVE,		//移動
		MOTIONTYPE_PUNCH,		//パンチ
		MOTIONTYPE_KICK,		//キック
		MOTIONTYPE_DAMAGE,		//ダメージ
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

	CEnemy();
	CEnemy(D3DXVECTOR3 pos);
	~CEnemy();

	static HRESULT Load(void);
	static void Unload(void);
	static CEnemy *Create(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight);

	HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight);

	void Uninit(void);
	void Update(void);
	void Draw(void);

	void AddDamage(int nDamage, int nEnemy);

	bool HitBlock(void);

	void SetLife(int nLife,int nEnemy);

	int GetLife(int nEnemy);

	void SetState(EnemyState state);
	EnemyState GetState(int nEnemy);

	void SetJump(bool jump);
	bool GetJump(void);

	bool GetDeath(void);
	void SetDeath(bool bDeath,int nEnemy);

	int GetCnt(void);
	void SetCnt(int nCnt);

	//モーション
	void SetMotionEnemy(MOTIONTYPE nType);

	//CEnemy GetPos(void);
	//void SetPos(D3DXVECTOR3 pos);

private:
	int m_nLife[MAX_ENEMY];											//体力	
	int m_EnemyCount;							//敵の数を数える
	int m_nEnemy;								//敵の総数
	bool m_bJump;								//ジャンプ中かどうか
	bool m_bDeath;			//敵が死亡したかどうか判定
	
	D3DXVECTOR3 m_posold;						//古い位置
	D3DXMATRIX m_mtxWorld;						//ワールドマトリックス
	CModel *m_apModel[MAX_PART];				//モデルパーツへのポインタ
	int m_nNumModel;							//モデルパーツの総数

	//CMotion *m_pMotion;							//モーションの情報

	int m_nldxShadow; //対象の影のインデックス(番号)

	EnemyState m_Enemystate;					//敵の状態の情報

	D3DXCOLOR m_ColEnemy;						//敵の色

	int m_nCntState;		//プレイヤー状態カウント

	int m_nCnt;										//何番目の敵か知る

	D3DXVECTOR3 m_InitPartPos[MAX_PART];	//パーツの初期位置
	bool m_bAttack;				//攻撃状態に入っているかどうか
	INFO m_aInfo[MAX_PART];		//パーツの最大数

	int m_nNumAll;				//数の最大数
	int m_nType;				//種類
	bool bLoop;					//終了するかどうか
	int m_nKey;					//キーの数
	int m_nCounter;				//モーションカウンター
	bool m_bFinish;				//終了するかどうか
	int m_nFrameCnt;			//フレーム数えるよう
};


#endif




