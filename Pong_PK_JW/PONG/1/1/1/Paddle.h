#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
class Paddle : public Drawable
{
public:
	Paddle(float t_x, float t_y, Keyboard::Key klawisz_lewo, Keyboard::Key klawisz_prawo);
	Paddle() = delete;
	~Paddle() = default;

	Vector2f getPosition();
	void update();
	float left();
	float right();
	float top();
	float bottom();

private:
	void draw(RenderTarget& target, RenderStates state) const override;
	RectangleShape shape;
	const float paddleWidth{ 80.0f };
	const float paddleHeight{ 20.0f };
	const float paddleVelocity{ 12.0f };
	Keyboard::Key lewo, prawo;
	Vector2f velocity{ paddleVelocity, 0 };


};

