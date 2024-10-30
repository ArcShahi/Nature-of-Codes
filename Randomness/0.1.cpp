// Example 0.1: A Traditional Random Walk

#include "raylib.h"
#include <vector>
#include <string>


class Walker
{
public:
	Walker()
		:coord{ 500.f,550.f }
	{}

	void show()const;
	void step();

private:
	Vector2 coord{};
	std::vector<Vector2> trail{};
	size_t steps{ 0 };
};


void Walker::show() const 
{
	// Draw the trail with fading effect
	for (size_t i = 0; i < trail.size(); i++) {
		float alpha = (float)i / trail.size();
		Color trail_color = { 0, 0, 0, (unsigned char)(alpha * 255) };
		DrawPixelV(trail[i], trail_color);
	}

	// Draw current position
	DrawPixelV(coord,BLACK);
	
	std::string text = "Steps Taken: " + std::to_string(steps);
	DrawText(text.c_str(), 5, 25, 20, BLACK);


}

void Walker::step()
{
	trail.emplace_back(coord.x,coord.y);
	steps++;

	// Limit trail length to prevent excessive memory usage
	if (trail.size() > 10'000)
	{
		trail.erase(trail.begin());
	}

	int x= GetRandomValue(0, 3);

	if (x == 0) coord.x++;
	else if (x == 1) coord.x--;
	else if (x == 2) coord.y++;
	else coord.y--;


	// Bounce off screen edges
	if (coord.x < 0) coord.x = 0;
	if (coord.x > GetScreenWidth()) coord.x = GetScreenWidth();
	if (coord.y < 0) coord.y = 0;
	if (coord.y > GetScreenHeight()) coord.y = GetScreenHeight();

	
}


///////////////////////////////////////////////////////////////////////////////////////////////
////							CANVAS CLASS						               ////	
/////////////////////////////////////////////////////////////////////////////////////////////


class Canvas
{
public:
	Canvas()
	{
		InitWindow(1200, 900, "Random Walker");
	}

	~Canvas()
	{
		CloseWindow();
	}

	void run();
	
private:
	void update(float dt);
	void render();
	
private:
	Walker walker{};

};


void Canvas::run()
{
	SetTargetFPS(144);

	while (!WindowShouldClose())
	{  

		float dt = GetFrameTime();
		update(dt);
		render();
	}
}

void Canvas::update(float dt)
{
	// Resets the Walker
	if (IsKeyPressed(KEY_ENTER))
	{
		walker = Walker();
	}

	walker.step();
}

void Canvas::render()
{
	

	BeginDrawing();
	ClearBackground(RAYWHITE);
	DrawFPS(5, 5);

	walker.show();

	EndDrawing();

}

/////////////////////////////////////////////////////////////////////////////////////////////////////



int main()
{
	Canvas canvas{};

	canvas.run();

}