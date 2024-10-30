#include "raylib.h"
#include  "Randum.hpp"
#include "Veczebra.ipp"

class Mover
{
public:
	Mover()
		:coord{xe::randomf(0.0f,1200.f),xe::randomf(0.0f,900.f)}
		,velocity{xe::randomf(-200.f,200.f),xe::randomf(-200.f,200.f)}
		,radius{37.f}
	{}

	void update(float dt);
	void show();

private:
	void check_edges();

private:
	Vector2 coord{};
	Vector2 velocity{};
	float radius{};
};

void Mover::update(float dt)
{
	// Add Velocity to Postion to make Ball Move
	coord += {velocity*dt};

	check_edges();
}

void Mover::show()
{

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
	else if (coord.x <0.0f)
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


class Canvas
{
public:
	Canvas()
	{
		InitWindow(1200, 900, "Motion 101 (Velocity)");
		SetTargetFPS(144);
	}

	~Canvas(){ CloseWindow(); }
	void run();

private:

	void update(float dt);
	void render();

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
	mover.update(dt);
}

void Canvas::render()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);
	DrawFPS(5, 5);

	DrawRectangleLines(5, 5, 1200, 900, BLACK);

	mover.show();

	EndDrawing();
}


int main()
{

	Canvas canvas{};

	canvas.run();
}