#pragma once

/// <summary>
/// 2次元ベクトル
/// </summary>
struct Vector2 final {
	float x;
	float y;
	Vector2 operator*(Vector2 scalar) const { return {x * scalar.x, y * scalar.y}; }
};
