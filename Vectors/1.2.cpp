/// EXAMPLE 1.2 : BOUCING BALL WITH VECTORS

#include "raylib.h"
#include "raymath.h"

class Mover
{
public:
	Mover()
		:coord{ 500.f,500.f }, radius{ 45.f },velocity{250.f,200.f}
	{}

	Vector2 coord{};

	void update(float dt);
	void show()const;
	void boune_edge();


private:
	Vector2 velocity{ };
	float radius{};
};

void Mover::update(float dt)
{

	coord.x += velocity.x * dt;
	coord.y += velocity.y * dt;

	// Bounce off Edges
	boune_edge();
	
}

void Mover::show()const
{
	
	DrawCircleGradient(coord.x, coord.y, radius, PINK,RED);
	DrawCircleLinesV(coord, radius, BLACK);

}

void Mover::boune_edge()
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


class Canvas
{
public:
	Canvas()
	{
		InitWindow(1200, 900, "Boucing Ball");
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

void Canvas::update(float dt)
{
	mover.update(dt);
}

void Canvas::render()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);
	DrawFPS(5, 5);

	mover.show();

	EndDrawing();
}

void Canvas::run()
{
	while (!WindowShouldClose())
	{
		float dt = GetFrameTime();

		update(dt);
		render();
	}
}


int main()
{

	Canvas canvas{};
	canvas.run();
}


