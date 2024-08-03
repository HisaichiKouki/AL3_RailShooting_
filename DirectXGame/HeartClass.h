#pragma once
#include "Easing.h"
#include <Sprite.h>
#include <TextureManager.h>

class HeartClass {
public:
	HeartClass();
	~HeartClass();
	void Init();
	void Updaet();
	void Draw(Vector2 pos);

private:
	Sprite* sprite=nullptr;
	Sprite* frontSprite=nullptr;
	uint32_t texHandle;

	float color;
	Vector2 initSize;
	float scale;
	float currentT;
};
