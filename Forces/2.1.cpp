#include "raylib.h"
#include "Randum.hpp"
#include "Veczebra.ipp"


class Mover
{
public:
	Mover()
		:position{ xe::randomf(0.f,1200),xe::randomf(0.f,900) }
		, mass{ 2.1f }, radius{ 16.f }
	{}

	

	void apply_force(Vector2);
	void update(float dt);
	void show()const;

private:
	void bounce_edges();

private:
	Vector2 position{};
	Vector2 velocity{};
	Vector2 acceleration{};;
	float mass{};
	float radius{};
};


// Don't Modify the actual Force being Applied
void Mover::apply_force(Vector2 force)
{
	force /= mass;

	acceleration += force;
}

void Mover::update(float dt)
{

	velocity += acceleration;
	position += velocity*dt;
	// Reset Acceleration Each Time
	acceleration = { 0 };

	bounce_edges();
}

void Mover::show()const
{

	DrawCircleGradient(position.x, position.y, mass * radius,GRAY,BLACK);
	DrawCircleLinesV(position, mass *radius,RED);
}

void Mover::bounce_edges()
{
	// Right Edge
	if (position.x > GetScreenWidth()) 
	{
		position.x = GetScreenWidth();
		velocity.x *= -1.f;
	}
	else if (position.x < 0.f) 
	{ // Left Edge
		position.x = 0.f;
		velocity.x *= -1.f;
	}

	// Bottom Edge
	if (position.y > GetScreenHeight()) 
	{
		position.y = GetScreenHeight()-radius;
		velocity.y *= -1.f;	
	}
}


class Canvas
{
public:
	Canvas()
	{
		InitWindow(1200, 900, "Forces");
		SetTargetFPS(144);
	}
	~Canvas() { CloseWindow(); }

	void run();

private:

	void update(float dt);
	void render()const;


private:
	Mover mover{};
	Vector2 gravity{ 0.f,98.f };
	Vector2 wind = { 10.f,0.f };
   
};

void Canvas::run()
{
	while (!WindowShouldClose())
	{
		float dt = GetFrameTime();
		update(dt);
		render();
	}
}

void Canvas::update(float dt)
{
	

	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
	{
		mover.apply_force(wind);
	}

	mover.apply_force(gravity);
	mover.update(dt);
}

void Canvas::render() const
{
	BeginDrawing();
	ClearBackground(RAYWHITE);
	DrawFPS(5, 5);

	mover.show();

	EndDrawing();
}


int main()
{

	Canvas canvas{};
	canvas.run();
}

