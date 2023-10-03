//============================
//
//�I�u�W�F�N�g����(object.h)
//Author:���� �F�M
//
//============================
#ifndef _OBJECT_H_   //���̃}�N����`������Ă��Ȃ�������
#define _OBJECT_H_   //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"
//#include "manager.h"

//�}�N����`
#define MAX_OBJECT	(1280)		//�I�u�W�F�N�g�̍ő吔

class CObject
{
public:
	typedef enum 
	{
		TYPE_NONE = 0,			//�����Ȃ�
		TYPE_PLAYER,			//�v���C���[�^�C�v
		TYPE_ENEMY,				//�G�^�C�v
		TYPE_BULLET,			//�e�^�C�v
		TYPE_EFFECT,			//�G�t�F�N�g�^�C�v
		TYPE_SCORE,				//�X�R�A�^�C�v
		TYPE_TIME,				//�^�C���^�C�v
		TYPE_PARTICLE,			//�p�[�e�B�N��
		TYPE_BLOCK,				//�u���b�N�^�C�v
		TYPE_FLOOR,				//���^�C�v
		TYPE_LONGFLOOR,			//������
		TYPE_BILBOARD,			//�r���{�[�h�^�C�v
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
	static int m_nNumAll;					//�I�u�W�F�N�g����
	int m_nId;								//�������g��ID
	TYPE m_Type;							//���
};

#endif





