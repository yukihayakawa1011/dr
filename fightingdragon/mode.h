//============================
//
//���[�h����(mode.h)
//Author:���� �F�M
//
//============================
#ifndef _MODE_H_   //���̃}�N����`������Ă��Ȃ�������
#define _MODE_H_   //2�d�C���N���[�h�h�~�̃}�N�����`����
#include "manager.h"
#include "main.h"

class CParticle;
class CPlayer;
class CExplosion;
class CEffect;
class CAbg;
class CScore;
//class CTime;
class CEnemy;
class CBlock;
class CCamera;
class CLight;
class CObjectx;
class CModel;
class CInfection;
class CObject3d;
class CPause;

class CTitle : public CScene
{
public:
	CTitle();
	~CTitle();

	static CTitle *Create(D3DXVECTOR3 pos, float fRot, int nTex);
	HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex);
	void Uninit(void);
	void Update(void);
	void Draw(void);

protected:
	LPDIRECT3DTEXTURE9 m_pTexture;				//�e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^

private:
	

};

class CStory : public CScene
{
public:
	CStory();
	~CStory();

	static CStory *Create(D3DXVECTOR3 pos, float fRot, int nTex);
	HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex);
	void Uninit(void);
	void Update(void);
	void Draw(void);

protected:
	LPDIRECT3DTEXTURE9 m_pTexture;				//�e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^

private:


};

class CTutorial : public CScene
{
public:
	CTutorial();
	~CTutorial();

	static CTutorial *Create(D3DXVECTOR3 pos, float fRot, int nTex);
	HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex);
	void Uninit(void);
	void Update(void);
	void Draw(void);

protected:
	LPDIRECT3DTEXTURE9 m_pTexture;				//�e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^

private:


};

class CGame : public CScene
{
public:
	CGame();
	~CGame();

	static CGame *Create(D3DXVECTOR3 pos, float fRot, int nTex);

	HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	
	static CPlayer *GetPlayer(void);
	static CPlayer *GetPlayerMirror(void);
	static CExplosion *GetExplosion(void);
	static CEnemy *GetEnemy(void);
	static CAbg *GetAbg(void);
	static CEffect *GetEffect(void);
	static CScore *GetScore(void);
	static CTime *GetTime(void);
	static CBlock *GetBlock(void);
	static CCamera *GetCamera(void);
	static CLight *GetLight(void);
	static CObjectx *GetObjectx(void);
	static CModel *GetModel(void);
	static CInfection *GetInfection(void);
	static CObject3d *GetObject3d(void);

private:
	static CPlayer *m_pPlayer;					//�v���C���[�̏��
	static CPlayer *m_pPlayerMirror;			//�v���C���[�~���[�̏��
	static CExplosion *m_pExplosion;			//�����̏��
	static CEnemy *m_pEnemy;					//�G���
	static CAbg *m_pAbg;						//���d�w�i���
	static CEffect *m_pEffect;					//�G�t�F�N�g���
	static CScore *m_pScore;					//�X�R�A���
	static CTime *m_pTime;						//�^�C�����
	static CBlock *m_pBlock;					//�u���b�N���
	static CCamera *m_pCamera;					//�J�������
	static CLight *m_pLight;					//���C�g���
	static CObjectx *m_pObjectx[USE_OBJECTX];	//�I�u�W�F�N�g���
	static CModel *m_pModel;					//���f�����
	static CInfection *m_pInfection;			//�������
	static CObject3d *m_pObject3d;				//�I�u�W�F�N�g3d���
	static CPause *m_pPause;					//�|�[�Y�̏��
	bool m_bPause;								//�|�[�Y��Ԃ�ON/OFF
};

class CResult : public CScene
{
public:
	CResult();
	~CResult();

	static CResult *Create(D3DXVECTOR3 pos, float fRot, int nTex);

	HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	LPDIRECT3DTEXTURE9 m_pTexture;				//�e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^
};

class CGameOver : public CScene
{
public:
	CGameOver();
	~CGameOver();

	static CGameOver *Create(D3DXVECTOR3 pos, float fRot, int nTex);

	HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	LPDIRECT3DTEXTURE9 m_pTexture;				//�e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^
};



#endif


