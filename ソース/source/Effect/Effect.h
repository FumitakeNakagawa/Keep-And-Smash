#pragma once

class Effect
{
public:

	void Initialize();		//初期化（画像読み込み）
	void Update();			//更新
	void Render();			//描画

	/*☆*/
	static void Smash(const Vector3& pos, const Vector3& move);

};