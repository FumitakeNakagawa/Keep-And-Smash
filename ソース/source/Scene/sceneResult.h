#pragma once
#include <memory>

class sceneResult : public Scene
{
public:
	enum
	{
		NON,		//�����{�^���ƃJ�[�\���������Ă��Ȃ�
		RETRY,		//RETRY�{�^��
		TITLE,		//TITLE�{�^��
	};

private:
	std::unique_ptr<iexView>	view;
	std::unique_ptr<UISceneResult> ui;

	POINT	mousePoint;
	BOOL mouseReverse;

	int botton;

	int scorePlayer;
	int scoreEnemy;
public:
	~sceneResult();
	//������
	bool Initialize(int playerScore, int enemyScore);
	//�X�V
	void Update();
	//�`��
	void Render();
};