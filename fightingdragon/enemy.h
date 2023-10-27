//============================
//
//�G����(enemy.h)
//Author:���� �F�M
//
//============================
#ifndef _ENEMY_H_   //���̃}�N����`������Ă��Ȃ�������
#define _ENEMY_H_   //2�d�C���N���[�h�h�~�̃}�N�����`����
#include "main.h"
#include "objectx.h"
#include "model.h"

//�}�N����`
#define MAX_ENEMY (20)				//�G�̍ő吔
#define MAX_MODEL (17)				//���f���̐�

#define ENEMY_MIN_X (-10.0f)		//�G��X���̍���
#define ENEMY_MAX_X (10.0f)			//�G��X���̉E��
	   
#define ENEMY_MIN_Y (0.0f)			//�G��Y���̉�
#define ENEMY_MAX_Y (15.0f)			//�G��Y���̏�
	   
#define ENEMY_MIN_Z (0.0f)			//�G��Z���̉�
#define ENEMY_MAX_Z (15.0f)			//�G��Z���̏�

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

	//���[�V�����̎��
	typedef enum
	{
		MOTIONTYPE_NEUTRAL = 0, //�ҋ@
		MOTIONTYPE_MOVE,		//�ړ�
		MOTIONTYPE_PUNCH,		//�p���`
		MOTIONTYPE_KICK,		//�L�b�N
		MOTIONTYPE_DAMAGE,		//�_���[�W
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

	//���[�V����
	void SetMotionEnemy(MOTIONTYPE nType);

	//CEnemy GetPos(void);
	//void SetPos(D3DXVECTOR3 pos);

private:
	int m_nLife[MAX_ENEMY];											//�̗�	
	int m_EnemyCount;							//�G�̐��𐔂���
	int m_nEnemy;								//�G�̑���
	bool m_bJump;								//�W�����v�����ǂ���
	bool m_bDeath;			//�G�����S�������ǂ�������
	
	D3DXVECTOR3 m_posold;						//�Â��ʒu
	D3DXMATRIX m_mtxWorld;						//���[���h�}�g���b�N�X
	CModel *m_apModel[MAX_PART];				//���f���p�[�c�ւ̃|�C���^
	int m_nNumModel;							//���f���p�[�c�̑���

	//CMotion *m_pMotion;							//���[�V�����̏��

	int m_nldxShadow; //�Ώۂ̉e�̃C���f�b�N�X(�ԍ�)

	EnemyState m_Enemystate;					//�G�̏�Ԃ̏��

	D3DXCOLOR m_ColEnemy;						//�G�̐F

	int m_nCntState;		//�v���C���[��ԃJ�E���g

	int m_nCnt;										//���Ԗڂ̓G���m��

	D3DXVECTOR3 m_InitPartPos[MAX_PART];	//�p�[�c�̏����ʒu
	bool m_bAttack;				//�U����Ԃɓ����Ă��邩�ǂ���
	INFO m_aInfo[MAX_PART];		//�p�[�c�̍ő吔

	int m_nNumAll;				//���̍ő吔
	int m_nType;				//���
	bool bLoop;					//�I�����邩�ǂ���
	int m_nKey;					//�L�[�̐�
	int m_nCounter;				//���[�V�����J�E���^�[
	bool m_bFinish;				//�I�����邩�ǂ���
	int m_nFrameCnt;			//�t���[��������悤
};


#endif




