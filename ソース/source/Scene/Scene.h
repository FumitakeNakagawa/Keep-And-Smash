#ifndef __SCENE_H__
#define __SCENE_H__

//*****************************************************************************
//
//		シーン基底クラス
//
//*****************************************************************************

class Scene {
protected:
	Scene* pStack;			//スタック用ポインタ

public:
	//	生成・解放
	Scene() :pStack(NULL) {}
	virtual ~Scene() { if (pStack) delete pStack; }
	//	初期化
	virtual bool Initialize() { return true; }
	//	更新・描画
	virtual void Update() {}
	virtual void Render() {}

	Scene* getStackScene() { return pStack; }
	void setStackScene(Scene* s) { pStack = s; }
};

//*****************************************************************************
#endif
