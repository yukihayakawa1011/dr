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
	static CScene *m_pScene;					//�V�[���Ɋւ���|�C���^
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
	
	static CRenderer *GetRenderer(void);
	static CInputKeyboard *GetInputKeyboard(void);
	static CSound *GetSound(void);
	static CDebugProc *GetDebugProck(void);
	static CInputGamePad *GetGamePad(void);

	//�V�[���Ɋւ���֐�
	static void SetMode(CScene::MODE mode);

private:

	static CRenderer *m_pRenderer;				//�����_���[�̏��
	static CInputKeyboard *m_pInputKeyboard;	//�L�[�{�[�h�̏��
	static CSound *m_pSound;					//�T�E���h���
	static CDebugProc *m_pDebugProc;			//�f�o�b�O���
	static CInputGamePad *m_pInputGamePad;		//�Q�[���p�b�h���

	//�V�[���Ɋւ�����
	static CScene *m_pScene;					//�V�[���Ɋւ���|�C���^
};

#endif



