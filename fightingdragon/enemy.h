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
	int m_nLife[MAX_ENEMY];											//�̗�	
	D3DXVECTOR3 m_posold;						//�Â��ʒu
	D3DXMATRIX m_mtxWorld;						//���[���h�}�g���b�N�X
	CModel *m_apModel[MAX_PART];				//���f���p�[�c�ւ̃|�C���^
	int m_nNumModel;							//���f���p�[�c�̑���
	int m_EnemyCount;							//�G�̐��𐔂���
	int m_nEnemy;								//�G�̑���
	bool m_bJump;								//�W�����v�����ǂ���

	//CMotion *m_pMotion;							//���[�V�����̏��

	int m_nldxShadow; //�Ώۂ̉e�̃C���f�b�N�X(�ԍ�)

	EnemyState m_Enemystate;					//�G�̏�Ԃ̏��

	D3DXCOLOR m_ColEnemy;						//�G�̐F

	int nCntEnemy;										//���Ԗڂ̓G���m��

	int m_nCntState;		//�v���C���[��ԃJ�E���g

	bool m_bDeath;			//�G�����S�������ǂ�������
};


#endif




