#pragma once
#include "..\\UI\UI.h"
#include <memory>

class sceneTitle : public Scene
{
private:
	std::unique_ptr<iexView>	view;
	std::unique_ptr<UISceneTitle> ui;
	bool pushBotton;

	POINT	mousePoint;
	BOOL mouseReverse;
public:
	~sceneTitle();
	//初期化
	bool Initialize();
	//更新
	void Update();
	//描画
	void Render();
};