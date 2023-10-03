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
	static CScene *m_pScene;					//シーンに関するポインタ
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
	
	static CRenderer *GetRenderer(void);
	static CInputKeyboard *GetInputKeyboard(void);
	static CSound *GetSound(void);
	static CDebugProc *GetDebugProck(void);
	static CInputGamePad *GetGamePad(void);

	//シーンに関する関数
	static void SetMode(CScene::MODE mode);

private:

	static CRenderer *m_pRenderer;				//レンダラーの情報
	static CInputKeyboard *m_pInputKeyboard;	//キーボードの情報
	static CSound *m_pSound;					//サウンド情報
	static CDebugProc *m_pDebugProc;			//デバッグ情報
	static CInputGamePad *m_pInputGamePad;		//ゲームパッド情報

	//シーンに関する情報
	static CScene *m_pScene;					//シーンに関するポインタ
};

#endif



