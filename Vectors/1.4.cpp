#include "raylib.h"
#include <cmath>



class Canvas
{
public:
	Canvas()
	{
		InitWindow(1200, 900, "Multiplyling a Vector");
		SetTargetFPS(144);
	}

	~Canvas()
	{
		CloseWindow();
	}

	void run();
private:
	void update();
	void render();

private:
	Vector2 mouse{};
	Vector2 darker{};
	const Vector2 origin{500.f,500.f};
};

void Canvas::run()
{
	while (!WindowShouldClose())
	{
		update();
		render();
	}
}

void Canvas::update()
{
	mouse = GetMousePosition();
	//vector from origin to mouse
	darker = { mouse.x - origin.x, mouse.y - origin.y };  

	// Scale it to half length
	darker = { darker.x * 0.5f, darker.y * 0.5f };     

	// Origin back to get final position
	darker = { darker.x + origin.x, darker.y + origin.y }; 

} 



void Canvas::render()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);
	DrawFPS(5, 5);

	DrawLineEx(origin, mouse, 3, GRAY);
	DrawLineEx(origin, darker, 6, BLACK);


	EndDrawing();
}


int main()
{
	Canvas canvas{};
	canvas.run();
}


/*
To scale something relative to a point, we need to:

-First treat that point as (0,0)
-Do your scaling
-Then put it back where it belongs

If we didn't do this and just scaled the raw mouse position, it would scale relative to (0,0) of the window
 not our desired origin point of (500,500).

*/