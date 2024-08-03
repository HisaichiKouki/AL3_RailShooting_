#pragma once
#include "TextureManager.h"
#include "WorldTransform.h"
#include <Easing.h>
#include <Model.h>
#include <ObjectColor.h>
#include <stdlib.h>
class Enemy;

class HPbar {
public:
	HPbar();
	~HPbar();
	void Init();
	void Update();
	void Draw(const ViewProjection& viewprojection);
	void SetEnemy(Enemy* set);
	bool GetIsDead() { return isDead; }

	private:
	Enemy* enemy = nullptr;
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_;
	ObjectColor* objColor = nullptr;
	bool isDead;
	float initHp;
	float raito;
};
