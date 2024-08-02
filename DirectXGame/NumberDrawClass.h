#pragma once
#include <TextureManager.h>
#include <string.h>
#include <Sprite.h>
#include <Audio.h>
const int numDigits = 5;

class NumberDrawClass {

public:
	NumberDrawClass();
	~NumberDrawClass();
	void Init();
	void Draw(const Vector2& pos, int32_t num);

private:
	uint32_t texHandle;
	std::string texName = "./Resources/addTexture/number-Sheet.png";
	
	Sprite* sprite[5] = {nullptr, nullptr};
	Vector2 initSize;
	Vector2 scale;
	
	float drawNum[numDigits]; // 描画する数字
	float width;

	int currentNum;
	

	

};
