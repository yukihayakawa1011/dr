//============================
//
//オブジェクト処理(object.h)
//Author:早川 友貴
//
//============================
#ifndef _OBJECT_H_   //このマクロ定義がされていなかったら
#define _OBJECT_H_   //2重インクルード防止のマクロを定義する

#include "main.h"
//#include "manager.h"

//マクロ定義
#define MAX_OBJECT	(1280)		//オブジェクトの最大数

class CObject
{
public:
	typedef enum 
	{
		TYPE_NONE = 0,			//何もない
		TYPE_PLAYER,			//プレイヤータイプ
		TYPE_ENEMY,				//敵タイプ
		TYPE_BULLET,			//弾タイプ
		TYPE_EFFECT,			//エフェクトタイプ
		TYPE_SCORE,				//スコアタイプ
		TYPE_TIME,				//タイムタイプ
		TYPE_PARTICLE,			//パーティクル
		TYPE_BLOCK,				//ブロックタイプ
		TYPE_FLOOR,				//床タイプ
		TYPE_LONGFLOOR,			//長い床
		TYPE_BILBOARD,			//ビルボードタイプ
		TYPE_MAX
	}TYPE;

	CObject();
	CObject(TYPE type);
	virtual	~CObject();

	virtual HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex,float fWidth,float fHeight) = 0;

	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);

	void SetType(TYPE type);
	TYPE GetType(void);
	static CObject *GetObject(int nIdx);

	virtual void SetPosition(D3DXVECTOR3 pos) = 0;
	virtual D3DXVECTOR3 GetPosition(void) = 0;
	virtual D3DXVECTOR3 GetMove(void) = 0;

protected:
	void Release(void);

private:
	static CObject *m_apObject[MAX_OBJECT];
	static int m_nNumAll;					//オブジェクト総数
	int m_nId;								//自分自身のID
	TYPE m_Type;							//種類
};

#endif





