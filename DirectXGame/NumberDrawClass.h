#pragma once
#include <TextureManager.h>
#include <string.h>
#include <Sprite.h>
class NumberDrawClass {
public:
	NumberDrawClass();
	~NumberDrawClass();
	void Init();
	void Draw(const Vector2& pos);

private:
	uint32_t texHandle;
	std::string texName = "./Resources/addTexture/number-Sheet.png";
	
	Sprite* sprite = nullptr;
	Vector2 initSize;
	Vector2 scale;
	float drawNum;//描画する数字
	float width;

};
