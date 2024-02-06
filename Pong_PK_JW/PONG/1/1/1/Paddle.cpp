#include "Paddle.h"

Paddle::Paddle(float t_x, float t_y, Keyboard::Key klawisz_lewo, Keyboard::Key klawisz_prawo) : lewo(klawisz_lewo), prawo(klawisz_prawo)
{
	shape.setPosition(t_x, t_y);
	shape.setSize({ paddleWidth, paddleHeight });
	shape.setFillColor(Color::Green);
	shape.setOrigin(paddleWidth / 2.f, paddleHeight / 2.f);
}
void Paddle::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(shape, state);
}

void Paddle::update()
{
	shape.move(velocity);

	if (Keyboard::isKeyPressed(lewo) && left() > 0)
	{
		velocity.x = -paddleVelocity;
	}
	else if (Keyboard::isKeyPressed(prawo) && right() < 800)
	{
		velocity.x = paddleVelocity;
	}
	else velocity.x = 0;

}





float Paddle::left()
{
	return shape.getPosition().x - shape.getSize().x/2.f;
}
float Paddle::right()
{
	return shape.getPosition().x + shape.getSize().x / 2.f;
}
float Paddle::top()
{
	return shape.getPosition().y - shape.getSize().y / 2.f;
}
float Paddle::bottom()
{
	return shape.getPosition().y + shape.getSize().y / 2.f;
}

Vector2f Paddle::getPosition()
{
	return shape.getPosition();
}