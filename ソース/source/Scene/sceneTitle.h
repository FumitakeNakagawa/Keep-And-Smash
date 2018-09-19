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
	//������
	bool Initialize();
	//�X�V
	void Update();
	//�`��
	void Render();
};