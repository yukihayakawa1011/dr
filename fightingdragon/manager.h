//============================
//
//�}�l�[�W���[����(manager.h)
//Author:���� �F�M
//
//============================
#ifndef _MANAGER_H_   //���̃}�N����`������Ă��Ȃ�������
#define _MANAGER_H_   //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"
#include "object.h"

//�}�N����`
#define USE_OBJECTX (4)		//�g���I�u�W�F�N�g�w�̐�

//�O���錾
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
	//�Q�[�����[�h
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
	//�V�[���Ɋւ�����
	MODE m_Mode;
	int m_nMode;
	D3DXVECTOR3 m_pos;							//�ʒu���
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

	//�V�[���Ɋւ���֐�
	void SetMode(CScene::MODE mode);

private:

	//�V���O���g����
	static CManager *pManager;

	CRenderer *m_pRenderer;				//�����_���[�̏��
	CInputKeyboard *m_pInputKeyboard;	//�L�[�{�[�h�̏��
	CSound *m_pSound;					//�T�E���h���
	CDebugProc *m_pDebugProc;			//�f�o�b�O���
	CInputGamePad *m_pInputGamePad;		//�Q�[���p�b�h���

	//�V�[���Ɋւ�����
	CScene *m_pScene;					//�V�[���Ɋւ���|�C���^
};

#endif



