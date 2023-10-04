//============================
//
//���[�V��������(motion.h)
//Author:���� �F�M
//
//============================
#ifndef _MOTION_H_   //���̃}�N����`������Ă��Ȃ�������
#define _MOTION_H_   //2�d�C���N���[�h�h�~�̃}�N�����`����
//#include "manager.h"
//#include "main.h"
//#include "object.h"

//�}�N����`
#define MAX_PARTS (13)		//�p�[�c�̍ő吔

class CMotion
{
public:

	//���[�V�����̎��
	typedef enum
	{
		MOTIONTYPE_NEUTRAL = 0, //�ҋ@
		MOTIONTYPE_MOVE,		//�ړ�
		MOTIONTYPE_PUNCH,		//�A�N�V����
		MOTIONTYPE_JUMP,		//�W�����v
		MOTIONTYPE_LANDING,		//���n
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
		float m_frotDestX;  //�ڕW�̌���X
		float m_frotDestY;  //�ڕW�̌���Y
		float m_frotDestZ;  //�ڕW�̌���Z
	}KEY;

	// �L�[���̍\����
	typedef struct
	{
		int nFrame;				//�Đ��t���[��
		KEY aKey[MAX_PARTS];	//�e���f���̃L�[�v�f
	}KEY_INFO;

	//���[�V�������̍\����
	typedef struct
	{
		bool bLoop;				//���[�v���邩�ǂ���
		int nNumKey;			//�L�[�̑���
		KEY_INFO aKeyinfo[4];	//�L�[���
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

	INFO m_aInfo[MOTIONTYPE_MAX];		//�p�[�c�̍ő吔
	int m_nNumAll;				//���̍ő吔
	int m_nType;				//���
	bool bLoop;					//�I�����邩�ǂ���
	int m_nKey;					//�L�[�̐�
	int m_nCounter;				//���[�V�����J�E���^�[
	bool m_bFinish;				//�I�����邩�ǂ���

	CModel **m_ppModel;			//���f���ւ̃|�C���^
	int m_nNumModel;			//���f���̑���
};


#endif




