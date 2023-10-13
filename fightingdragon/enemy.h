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
		ENEMYSTATE_STANBY = 0,
		ENEMYSTATE_ATTACK,
		ENEMYSTATE_DAMAGE,
		ENEMYSTATE_NONE,
		ENEMYSTATE_MAX
	}EnemyState;

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

	//CEnemy GetPos(void);
	//void SetPos(D3DXVECTOR3 pos);

private:
	int m_nLife[MAX_ENEMY];											//体力	
	D3DXVECTOR3 m_posold;						//古い位置
	D3DXMATRIX m_mtxWorld;						//ワールドマトリックス
	CModel *m_apModel[MAX_PART];				//モデルパーツへのポインタ
	int m_nNumModel;							//モデルパーツの総数
	int m_EnemyCount;							//敵の数を数える
	int m_nEnemy;								//敵の総数
	bool m_bJump;								//ジャンプ中かどうか

	//CMotion *m_pMotion;							//モーションの情報

	int m_nldxShadow; //対象の影のインデックス(番号)

	EnemyState m_Enemystate;					//敵の状態の情報

	D3DXCOLOR m_ColEnemy;						//敵の色

	int nCntEnemy;										//何番目の敵か知る

	int m_nCntState;		//プレイヤー状態カウント

	bool m_bDeath;			//敵が死亡したかどうか判定
};


#endif




