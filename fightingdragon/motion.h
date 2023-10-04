//============================
//
//モーション処理(motion.h)
//Author:早川 友貴
//
//============================
#ifndef _MOTION_H_   //このマクロ定義がされていなかったら
#define _MOTION_H_   //2重インクルード防止のマクロを定義する
//#include "manager.h"
//#include "main.h"
//#include "object.h"

//マクロ定義
#define MAX_PARTS (13)		//パーツの最大数

class CMotion
{
public:

	//モーションの種類
	typedef enum
	{
		MOTIONTYPE_NEUTRAL = 0, //待機
		MOTIONTYPE_MOVE,		//移動
		MOTIONTYPE_PUNCH,		//アクション
		MOTIONTYPE_JUMP,		//ジャンプ
		MOTIONTYPE_LANDING,		//着地
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
		float m_frotDestX;  //目標の向きX
		float m_frotDestY;  //目標の向きY
		float m_frotDestZ;  //目標の向きZ
	}KEY;

	// キー情報の構造体
	typedef struct
	{
		int nFrame;				//再生フレーム
		KEY aKey[MAX_PARTS];	//各モデルのキー要素
	}KEY_INFO;

	//モーション情報の構造体
	typedef struct
	{
		bool bLoop;				//ループするかどうか
		int nNumKey;			//キーの総数
		KEY_INFO aKeyinfo[4];	//キー情報
	}INFO;

	CMotion();
	~CMotion();

	static CMotion *Create(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight);
	HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight);
	void Set(int nType);
	void Uninit(void);
	void Update(void);
	
	int GetType(void);
	bool IsFinish(void);

	void SetInfo(INFO info);

	void SetModel(CModel **ppModel, int nNumModel);

private:

	INFO m_aInfo[MOTIONTYPE_MAX];		//パーツの最大数
	int m_nNumAll;				//数の最大数
	int m_nType;				//種類
	bool bLoop;					//終了するかどうか
	int m_nKey;					//キーの数
	int m_nCounter;				//モーションカウンター
	bool m_bFinish;				//終了するかどうか

	CModel **m_ppModel;			//モデルへのポインタ
	int m_nNumModel;			//モデルの総数
};


#endif




