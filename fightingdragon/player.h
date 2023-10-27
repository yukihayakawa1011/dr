//============================
//
//�v���C���[����(player.h)
//Author:���� �F�M
//
//============================
#ifndef _PLAYER_H_   //���̃}�N����`������Ă��Ȃ�������
#define _PLAYER_H_   //2�d�C���N���[�h�h�~�̃}�N�����`����
#include "main.h"
#include "bilboard.h"
#include "objectx.h"
#include "model.h"
//#include "motion.h"
//#include "shadow.h"

//�}�N��
#define PRESS_PLAYER (1.8f)
#define PLAYER_JUNP  (16.5f)
#define PLAYER_HEIGHT (19.0f) 
#define PLAYER_WIDTH (9.0f)
#define PLAYER_HITSPACEX (10.0f)	//�v���C���[�̓����蔻��X
#define PLAYER_HITSPACEY (20.0f)	//�v���C���[�̓����蔻��Y
#define PLAYER_ATTACKSPACE (20.0f) //�v���C���[�̍U������
#define ENEMY_HITSPACE (10.0f)		//�G�̓����蔻��
#define ENEMY_DAMAGESPACE (20.0f)  //�G�̍U�����󂯂�͈�

#define PLAYER_MIN_X (-15.0f)		//�v���C���[��X���̍���
#define PLAYER_MAX_X (15.0f)		//�v���C���[��X���̉E��

#define PLAYER_MIN_Y (0.0f)			//�v���C���[��Y���̉�
#define PLAYER_MAX_Y (50.0f)		//�v���C���[��Y���̉�

#define PLAYER_MIN_Z (0.0f)			//�v���C���[��Z���̉�
#define PLAYER_MAX_Z (15.0f)		//�v���C���[��Z���̉�

#define PLAYER_PUNCH_SPEED (50)		//�v���C���[�̃p���`�Ԋu

class CPlayer : public CObjectx
{
public:
	typedef enum
	{
		PLAYER_PLAYER,			//�v���C���[
		PLAYER_MODE_MAX
	}PLAYER_SELECT;

	typedef enum
	{
		PLAYER_NONE = 0,		//�ʏ���
		PLAYER_DAMAGE,			//�_���[�W���
		PLAYER_INVINCIBLE,		//���G���
		PLAYER_GURD,			//�v���C���[�K�[�h���
		PLAYER_MAX
	}PLAYER_STATE;

	//���[�V�����̎��
	typedef enum
	{
		MOTIONTYPE_NEUTRAL = 0,		//�ҋ@
		MOTIONTYPE_MOVE,			//�ړ�
		MOTIONTYPE_PUNCH0,			//�p���`
		MOTIONTYPE_KICK0,			//�L�b�N
		MOTIONTYPE_UNFAIR_PUNCH,	//unfair�p���`
		MOTIONTYPE_UNFAIR_KICK,		//unfair�L�b�N
		MOTIONTYPE_DAMAGE,			//�_���[�W
		MOTIONTYPE_MAX,
	}MOTIONTYPE;

	//�L�[�̍\����
	typedef struct
	{
		float m_fPosX;		//�ʒuX
		float m_fPosY;		//�ʒuY
		float m_fPosZ;		//�ʒuZ
		float m_fRotX;		//����X
		float m_fRotY;		//����Y
		float m_fRotZ;		//����Z
		//float m_frotDestX;  //�ڕW�̌���X
		//float m_frotDestY;  //�ڕW�̌���Y
		//float m_frotDestZ;  //�ڕW�̌���Z
		//float m_fposDestX;  //�ڕW�̌���X
		//float m_fposDestY;  //�ڕW�̌���Y
		//float m_fposDestZ;  //�ڕW�̌���Z
	}KEY;

	// �L�[���̍\����
	typedef struct
	{
		int nFrame;				//�Đ��t���[��
		KEY aKey[MAX_PART];	//�e���f���̃L�[�v�f
	}KEY_INFO;

	//���[�V�������̍\����
	typedef struct
	{
		bool bLoop;				//���[�v���邩�ǂ���
		int nNumKey;			//�L�[�̑���
		KEY_INFO aKeyinfo[4];	//�L�[���
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

	//���[�V����
	void SetMotionPlayer(MOTIONTYPE nType);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		//���L�e�N�X�`��
	float m_fLength;							//�Ίp���̒���
	float m_movefLength;						//�Ίp���̈ړ���
	float m_fAngle;								//�Ίp���̊p�x
	D3DXVECTOR3 m_posold;						//�Â��ʒu
	bool m_bJump;								//�W�����v�����ǂ���
	float m_fWidth;								//�v���C���[��
	float m_fHeight;							//�v���C���[����

	//D3DXCOLOR m_col;							//�F
	int m_nLife;								//�̗�
	//LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^

	D3DXMATRIX m_mtxWorld;						//���[���h�}�g���b�N�X
	CModel *m_apModel[MAX_PART];				//���f���p�[�c�ւ̃|�C���^
	int m_nNumModel;							//���f���p�[�c�̑���

	int m_nldxShadow; //�Ώۂ̉e�̃C���f�b�N�X(�ԍ�)

	bool m_bDeath;	  //�v���C���[�̐�������

	float m_ShotRot;  //�e�̕��������߂�

	bool m_bRot;	  //�v���C���[�̌�����������

	bool m_bAim;									//�\���Ă��邩�ǂ���

	PLAYER_STATE m_PlayerState;						//�v���C���[�̏��

	D3DXMATERIAL m_NoneMat;  //�}�e���A���ʏ폈��
	D3DXMATERIAL m_RedMat;  //�}�e���A����Ԃ����鏈��
	D3DXMATERIAL m_InvincibleMat;  //�}�e���A����Ԃ����鏈��

	D3DXCOLOR m_stateCol;			//�v���C���[�̏�Ԃɂ��F�̐ݒ�

	LPD3DXBUFFER m_pBuffMat = NULL; //�}�e���A���ւ̃|�C���^

	int m_nCntState;		//�v���C���[��ԃJ�E���g

	INFO m_aInfo[MAX_PART];		//�p�[�c�̍ő吔
	int m_nNumAll;				//���̍ő吔
	int m_nType;				//���
	bool bLoop;					//�I�����邩�ǂ���
	int m_nKey;					//�L�[�̐�
	int m_nCounter;				//���[�V�����J�E���^�[
	bool m_bFinish;				//�I�����邩�ǂ���

	CModel **m_ppModel;			//���f���ւ̃|�C���^

	int m_nFrameCnt;			//�t���[��������悤

	bool m_bAttack;				//�U����Ԃɓ����Ă��邩�ǂ���

	D3DXVECTOR3 m_InitPartPos[MAX_PART];	//�p�[�c�̏����ʒu

	int nPunchSpeed;

	int m_nEnemy;					//���Ԃ߂̓G���m��

	bool m_bSpawn;					//�X�|�[���������ǂ���

	bool m_bUnfare;					//unfair�U�����g�����Ƃ��Ă邩

	int m_nKill;					//���l�|������
};

#endif


