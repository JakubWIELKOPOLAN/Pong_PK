#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;
class Ball : public Drawable
{
public:
	Ball(float t_x, float t_y);
	Ball() = delete;
	~Ball() = default;
	void update();

	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();

	Vector2f getPosition(); 

	float left();
	float right();
	float top();
	float bottom();


private:
	CircleShape shape;
	const float ballRadius{ 10.0f };
	float ballVelocity{ 6.0f };
	Vector2f velocity{ ballVelocity, ballVelocity };
	void draw(RenderTarget& target, RenderStates state) const override;
	float x, y;


};

