#include	"../IEX/iextreme.h"

#include	"Particle.h"

void Particle::Collide(Vector3*pos1, Vector3*move1, float mass1, Vector3*pos2, Vector3*move2, float mass2, float repulsion, float time)
{
	//質量合計
	float totalWeight = mass1 + mass2;

	//反発率
	float repRate = (1 + repulsion*repulsion);

	//衝突軸ベクトル
	Vector3 n = *pos2 - *pos1;
	n.Normalize();

	//内積算出
	float dot = Vector3Dot((*move1 - *move2), n);

	//定数ベクトル
	Vector3 constVec = n * (repRate*dot / totalWeight);

	//衝突後速度ベクトル
	*move1 = constVec * -mass2 + *move1;
	*move2 = constVec * mass1 + *move2;

	//衝突後位置
	*pos1 = *pos1 + *move1*time;
	*pos2 = *pos2 + *move2*time;

}

void Particle::Collide(Vector3*pos, Vector3*move, float mass, float repulsion, float time,Vector3*normal)
{
	// 反射後速度を算出
	normal->Normalize();

	*move = *move - *normal*((1 + repulsion)*Vector3Dot(*normal, *move));

	// 移動位置を計算
	*pos = *pos + *move * time;
}

void Particle::Collide(Vector3*pos, Vector3*move1, Vector3*move2, float mass, float repulsion, float time, Vector3*normal)
{
	// 反射後速度を算出
	normal->Normalize();

	*move1 = *move1 - *normal*((1 + repulsion)*Vector3Dot(*normal, (*move1 - *move2)));

	// 移動位置を計算
	*pos = *pos + *move1 * time;
}

float Particle::WallDistJudg(iexMesh* mesh, Vector3&pos, Vector3&v, float r)
{
	Vector3 out;
	float d = 50.0f;

	Vector3 p = pos;
	Vector3 m = -v;
	int n = mesh->RayPick(&out, &p, &v, &d);
	if (n < 0)return FLT_MAX;

	Vector3 vec = out - pos;
	d = vec.Length();

	return d;
}

Vector3 Particle::MoveWallJudg(iexMesh* mesh, const Vector3&pos, const Vector3&move, float r)
{
	Vector3 p = pos;
	//方向ベクトル補正
	Vector3 m = move;
	float md = m.Length();
	//移動ベクトル正規化
	m.Normalize();

	//壁判定
	Vector3 v = m;

	//壁までの距離
	float d = WallDistJudg(mesh, p, v, r);

	if (d >= 0 && d < md)
	{
		//法線正規化
		v.Normalize();
		float cc = (m.x*v.x + m.z*v.z);

		//めり込み量の計算
		d = md - d;
		//適切な位置の算出(余分に押し戻す)
		m = move - v*cc*d*1.05f;

		//進行方向再チェック
		md = m.Length();
		v = m;
		v.Normalize();
		p = pos;
		d = WallDistJudg(mesh, p, v, r);
		if (d<.0f || d>md)p += m;
	}
	else
	{
		p += move;
	}
	return p;
}