//============================
//
//マネージャー処理(manager.h)
//Author:早川 友貴
//
//============================
#ifndef _MANAGER_H_   //このマクロ定義がされていなかったら
#define _MANAGER_H_   //2重インクルード防止のマクロを定義する

#include "main.h"
#include "object.h"

//マクロ定義
#define USE_OBJECTX (4)		//使うオブジェクトＸの数

//前方宣言
class CSound;
class CParticle;
class CRenderer;
class CInputKeyboard;
class CPlayer;
class CExplosion;
class CEffect;
class CAbg;
class CScore;
class CTime;
class CEnemy;
class CBlock;
class CCamera;
class CLight;
class CDebugProc;
class CObjectx;
class CModel;
class CInfection;
class CInputGamePad;

class CScene : public CObject
{
public:
	//ゲームモード
	enum MODE
	{
		MODE_TITLE = 0,
		MODE_STORY,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_RESULT,
		MODE_GAMEOVER,
		MODE_MAX
	};

	CScene();
	~CScene();

	static CScene *Create(MODE mode);

	HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight);

	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetMove(void);

	CScene::MODE GetMode(void);

private:
	//シーンに関する情報
	MODE m_Mode;
	int m_nMode;
	D3DXVECTOR3 m_pos;							//位置情報
};

class CManager
{
public:
	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hinstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	static CManager *GetInstance();	
	static void Release(void);

	CRenderer *GetRenderer(void);
	CInputKeyboard *GetInputKeyboard(void);
	CSound *GetSound(void);
	CDebugProc *GetDebugProck(void);
	CInputGamePad *GetGamePad(void);

	//シーンに関する関数
	void SetMode(CScene::MODE mode);

private:

	//シングルトン化
	static CManager *pManager;

	CRenderer *m_pRenderer;				//レンダラーの情報
	CInputKeyboard *m_pInputKeyboard;	//キーボードの情報
	CSound *m_pSound;					//サウンド情報
	CDebugProc *m_pDebugProc;			//デバッグ情報
	CInputGamePad *m_pInputGamePad;		//ゲームパッド情報

	//シーンに関する情報
	CScene *m_pScene;					//シーンに関するポインタ
};

#endif



