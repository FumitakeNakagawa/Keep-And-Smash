#pragma once

class Effect
{
public:

	void Initialize();		//�������i�摜�ǂݍ��݁j
	void Update();			//�X�V
	void Render();			//�`��

	/*��*/
	static void Smash(const Vector3& pos, const Vector3& move);

};