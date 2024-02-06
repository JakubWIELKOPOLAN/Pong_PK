#include "Ball.h"
extern Text score;
extern int wynik1, wynik2;
Ball::Ball(float t_x, float t_y) : x(t_x),y(t_y)
{
	shape.setPosition(t_x, t_y);
	shape.setRadius(ballRadius);
	shape.setFillColor(Color::Red);
	shape.setOrigin(ballRadius, ballRadius);




}

void Ball::draw(RenderTarget& target, RenderStates state) const 
{
	target.draw(shape, state);
}

void Ball :: update()
{
	shape.move(velocity);

	if (left() < 0)
		velocity.x = ballVelocity;

	if (right() > 800)
		velocity.x = -ballVelocity;

	if (top() < 0)
	{
		shape.setPosition(x, y);
		wynik1++;
	}
	if (bottom() > 600)
	{
		shape.setPosition(x, y);
		wynik2++;
	}

}


float Ball::left()
{
	return shape.getPosition().x - shape.getRadius();
}
float Ball::right()
{
	return shape.getPosition().x + shape.getRadius();
}
float Ball::top()
{
	return shape.getPosition().y - shape.getRadius();
}
float Ball::bottom()
{
	return shape.getPosition().y + shape.getRadius();
}

void Ball::moveDown()
{
	velocity.y = ballVelocity;
}

void Ball::moveUp()
{
	velocity.y = -ballVelocity;
}

void Ball::moveLeft()
{
	velocity.x = -ballVelocity;
}

void Ball::moveRight()
{
	velocity.x = ballVelocity;
}

Vector2f Ball::getPosition()
{
	return shape.getPosition();
}