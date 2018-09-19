#ifndef __SCENE_H__
#define __SCENE_H__

//*****************************************************************************
//
//		�V�[�����N���X
//
//*****************************************************************************

class Scene {
protected:
	Scene* pStack;			//�X�^�b�N�p�|�C���^

public:
	//	�����E���
	Scene() :pStack(NULL) {}
	virtual ~Scene() { if (pStack) delete pStack; }
	//	������
	virtual bool Initialize() { return true; }
	//	�X�V�E�`��
	virtual void Update() {}
	virtual void Render() {}

	Scene* getStackScene() { return pStack; }
	void setStackScene(Scene* s) { pStack = s; }
};

//*****************************************************************************
#endif
