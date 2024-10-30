#include "raylib.h"
#include "Algebra.ipp"



class Canvas
{
public:
	Canvas()
	{
		InitWindow(1200, 900, "Vector Magnitude");
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
	Rectangle mag_bar{5,0,1,15};
	Vector2 mouse{};
	const Vector2 center{ 600.f,450.f };

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

	// Cuz Mouse origin is at (0,0) , now we set it to center
	mag_bar.width = std::hypotf(mouse.x - center.x, mouse.y - center.y);


}

void Canvas::render()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);
	DrawFPS(1200, 5);

	DrawLineEx(center, mouse, 3, GRAY);
	DrawRectangleRec(mag_bar, BLACK);


	EndDrawing();
}


int main()
{
	Canvas canvas{};

	canvas.run();
}