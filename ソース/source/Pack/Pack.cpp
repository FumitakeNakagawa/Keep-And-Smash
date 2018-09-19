#include	"Pack.h"
#include	<assert.h>

#include	"../Particle/Particle.h"

#include	"../Sound/Sound.h"

#define GRAVITY -0.05f

std::vector<std::unique_ptr<iexMesh>>	Pack::mesh;


void Pack::Initialize()
{
	pos = Vector3(0.0f, 6.0f, 0.0f);
	rot = Vector3(0.0f, 0.0f, 0.0f);
	scale = Vector3(1.0f, 1.0f, 1.0f);
	move = Vector3(0.0f, 0.0f, 0.0f);
	velocity = Vector3(0.0f, 0.0f, 0.0f);

	level = 1;

	sphere.center = pos;
	sphere.radius = scale.x;
	step = 0;
}


void Pack::Initialize(Vector3 p, Vector3 m)
{
	pos = p;
	scale = Vector3(1.0f, 1.0f, 1.0f);
	rot = Vector3(0.0f, 0.0f, 0.0f);
	move = m;
	velocity = Vector3(0.0f, 0.0f, 0.0f);

	level = 1;

	sphere.center = pos;
	sphere.radius = 1.0f;
	step = 0;

}

void Pack::Initialize(Vector3 pos, Vector3 move, int level)
{
	this->pos = pos;
	scale = Vector3(1.0f, 1.0f, 1.0f);
	rot = Vector3(0.0f, 0.0f, 0.0f);
	this->move = move;
	velocity = Vector3(0.0f, 0.0f, 0.0f);

	this->level = level + 1;

	sphere.center = pos;
	sphere.radius = 1.0f;
	step = 0;

}


void Pack::Collide(Vector3*pos, Vector3*move, float mass, float repulsion, float time, Vector3*normal)
{
	// 反射後速度を算出
	normal->Normalize();

	*move = *move - *normal*((1 + repulsion)*Vector3Dot(*normal, *move));

	// 移動位置を計算
	*pos = *pos + *move * time;
}

void Pack::Gather(Sphere& s1, Pack& pack)
{
	float dist = 5.0f;

	if (step == 0)
	{
		Vector3 v = s1.center - sphere.center;
		v.Normalize();
		Vector3 near1 = sphere.center + v*sphere.radius;//最接近点


		Vector3 v2 = sphere.center - s1.center;
		v2.Normalize();
		Vector3 near2 = s1.center + v2*s1.radius;


		Vector3 v3 = near2 - near1;




		float length = v3.Length();
		if (.0f < length&&length < dist)
			step++;
	}
	else
	{
		Vector3 v = s1.center - sphere.center;
		v.Normalize();

		pos = pos + v*(dist*(sphere.radius + 5.0f)*0.05f);
		step = 0;

		if (!sound->StateWAV(SE_CATCH))sound->PlayWAV(SE_CATCH);

	}


}

bool Pack::Update(iexMesh* mesh)
{
	Vector3 out;
	float dist = 5.0f;
	float dist2 = 1.0f;
	Vector3 v = move;
	v.Normalize();
	Vector3 v2 = v;

	//壁とPackの当たり判定
	if ((mesh->RayPick(&out, &pos, &v, &dist)) > -1)
	{
		if (move.Length() >= dist)
		{
			Collide(&pos, &move, 1.0f, 0.9f, 1.0f, &v);
		}
		else if (ColWall(mesh))
		{
			Collide(&pos, &move, 1.0f, 0.9f, 1.0f, &v);
		}
	}

	
	float d = 1.0f;

	if (move.x > d)move.x = d;
	if (move.x < -d)move.x = -d;
	if (move.z > d)move.z = d;
	if (move.z < -d)move.z = -d;

	pos = Particle::MoveWallJudg(mesh, pos, move, sphere.radius);
	pos.y = 6.0f;

		dist = 5.0f;

		int index = mesh->RayPick(&out, &pos, &Vector3(0.0f, -1.0f, 0.0f), &dist);
		sphere.center = pos;

		if (index > -1)
		{
			DWORD* attr;
			mesh->GetMesh()->LockAttributeBuffer(D3DLOCK_READONLY, &attr);
			DWORD mat = attr[index];
			mesh->GetMesh()->UnlockAttributeBuffer();
			if (mat == 1)
				return true;
		}

	sphere.center = pos;

	return false;
}

void Pack::Render()
{
	mesh[level - 1]->SetPos(pos);
	mesh[level - 1]->SetAngle(rot);
	mesh[level - 1]->SetScale(scale);

	mesh[level - 1]->Update();
	mesh[level - 1]->Render();

#ifdef _DEBUG

	char str[256];

	sprintf(str, "x:%.1f\ny:%.1f\nz:%.1f", move.x, move.y, move.z);
	IEX_DrawText(str, 100, 400, 100, 100, 0xFFFFFFFF);

#endif
}

bool Pack::ColWall(iexMesh*mesh)
{
	Vector3 p = pos;
	//方向ベクトル補正
	Vector3 v1 = Vector3(move.x, 0, move.z);
	v1.Normalize();
	float d1 = 1.0f;
	Vector3 out1;

	p += v1*sphere.radius;
	int n1 = mesh->RayPick2(out1, p, v1, d1);//レイピック
	Vector3 vec1 = p - out1;
	p -= v1*sphere.radius;
	d1 = vec1.Length();  //壁までの距離

	p += move;//先に足しておいて

	if (d1 < 1.0f)
	{
		p -= Vector3(move.x, 0, move.z);

		pos = p;
		return true;
	}
	return false;
}