#include "raylib.h"


#include "raylib.h"
#include  "Randum.hpp"
#include "Veczebra.ipp"
#include <string>



class Mover
{
public:
	Mover()
		:coord{ 600.f,450.f }, velocity{ 0.f,0.f }, radius{ 37.f }
	{}

	void update(float dt);
	void show()const;
	void reset();

private:
	void check_edges();
	void bounce_edges();

private:
	Vector2 coord{};
	Vector2 velocity{};
	Vector2 acceleration{};
	
	float radius{};
	const float top_speed = 2000.f;
};

void Mover::update(float dt)
{
	Vector2 mouse = GetMousePosition();

	// Get Direction
	Vector2 direction = mouse - coord;

	direction = normalize(direction);

	// Scale it
	direction *= 7.f;
	
	// Set Acceleration in that direction
	acceleration = direction;

	// Add Acceleration to Velocity
	velocity += acceleration;

	// Limit Velocity
	velocity = limit(velocity, top_speed);

	// Add Velocity to Postion to make Ball Move
	coord += {velocity* dt};


	bounce_edges();
}

void Mover::show()const
{

	// Draw Ball
	DrawCircleGradient(coord.x, coord.y, radius, PINK, RED);
	DrawCircleLinesV(coord, radius, BLACK);
}

void Mover::check_edges()
{
	// Check Y Axis
	if (coord.x > GetScreenWidth())
	{
		coord.x = 0.0f;
	}
	else if (coord.x < 0.0f)
	{
		coord.x = GetScreenWidth();
	}

	// CHECK Y AXIS
	if (coord.y > GetScreenHeight())
	{
		coord.y = 0.f;
	}
	else if (coord.y < 0.0f)
	{
		coord.y = GetScreenHeight();
	}
}

void Mover::bounce_edges()
{

	// Bounce off Edges
	if (coord.x > GetScreenWidth() - radius || coord.x < radius)
	{
		velocity.x = velocity.x * -1.f;
	}

	if (coord.y > GetScreenHeight() - radius || coord.y < radius)
	{
		velocity.y = velocity.y * -1.f;
	}
}

void Mover::reset()
{
	Mover();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
////				CANVAS														///



class Canvas
{
public:
	Canvas()
	{
		InitWindow(1200, 900, "Motion 101(Velocity & Random Acceleration");
		SetTargetFPS(144);
	}

	~Canvas() { CloseWindow(); }
	void run();

private:

	void update(float dt);
	void render()const;

private:
	Mover mover{};

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

	if (IsKeyPressed(KEY_ENTER))
		mover.reset();

	mover.update(dt);
}

void Canvas::render()const
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