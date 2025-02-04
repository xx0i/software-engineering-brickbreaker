#include "stdafx.h"
#include "Game.h"

Game::Game()
{
	Reset();
}

void Game::Reset()
{
	Console::SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	Console::CursorVisible(false);
	paddle.width = 12;
	paddle.height = 2;
	paddle.x_position = 32;
	paddle.y_position = 30;

	ball.visage = 'O';
	ball.color = ConsoleColor::Cyan;
	ResetBall();

	// TODO #2 - Add this brick and 4 more bricks to the vector
	int pos = static_cast<int>(Console::WindowWidth());
	pos = pos / 5;
	//brick1
	brick1.width = 10;
	brick1.height = 2;
	brick1.x_position = 2;
	brick1.y_position = 5;
	brick1.doubleThick = true;
	brick1.color = ConsoleColor::Red;
	bricks.push_back(brick1);

	//brick2
	brick2.width = 10;
	brick2.height = 2;
	brick2.x_position = pos+2;
	brick2.y_position = 5;
	brick2.doubleThick = true;
	brick2.color = ConsoleColor::Yellow;
	bricks.push_back(brick2);

	//brick3
	brick3.width = 10;
	brick3.height = 2;
	brick3.x_position = pos*2+2;
	brick3.y_position = 5;
	brick3.doubleThick = true;
	brick3.color = ConsoleColor::Green;
	bricks.push_back(brick3);

	//brick4
	brick4.width = 10;
	brick4.height = 2;
	brick4.x_position = pos*3+2;
	brick4.y_position = 5;
	brick4.doubleThick = true;
	brick4.color = ConsoleColor::Blue;
	bricks.push_back(brick4);
	
	//brick5
	brick5.width = 10;
	brick5.height = 2;
	brick5.x_position = pos*4+2;
	brick5.y_position = 5;
	brick5.doubleThick = true;
	brick5.color = ConsoleColor::Magenta;
	bricks.push_back(brick5);
}

void Game::ResetBall()
{
	ball.x_position = paddle.x_position + paddle.width / 2;
	ball.y_position = paddle.y_position - 1;
	ball.x_velocity = rand() % 2 ? 1 : -1;
	ball.y_velocity = -1;
	ball.moving = false;
}

bool Game::Update()
{
	if (GetAsyncKeyState(VK_ESCAPE) & 0x1)
		return false;

	if (GetAsyncKeyState(VK_RIGHT) && paddle.x_position < WINDOW_WIDTH - paddle.width)
		paddle.x_position += 2;

	if (GetAsyncKeyState(VK_LEFT) && paddle.x_position > 0)
		paddle.x_position -= 2;

	if (GetAsyncKeyState(VK_SPACE) & 0x1)
		ball.moving = !ball.moving;

	if (GetAsyncKeyState('R') & 0x1) {
		bricks.clear(); // clears the bricks vector before continuing -> fixes the functionality error that was happening after resetting
		Reset();
	}

	ball.Update();
	CheckCollision();
	return true;
}

//  All rendering should be done between the locks in this function
void Game::Render()const
{
	Console::Lock(true);
	Console::Clear();
	
	paddle.Draw();
	ball.Draw();

	// TODO #3 - Update render to render all bricks
	for (int i = 0; i < bricks.size(); i++) {
		bricks[i].Draw();
	}
	if (bricks.size() == 0) {
		Console::SetCursorPosition(30, paddle.y_position - 10);
		std::cout << "!_~. YOU WIN .~_!";
	}
	if (ball.y_position == Console::WindowHeight()) {
		Console::SetCursorPosition(30, paddle.y_position - 10);
		std::cout << "T_T YOU LOSE T_T";
	}
	Console::Lock(false);
}

void Game::CheckCollision()
{
	// TODO #4 - Update collision to check all bricks
	for (int i = 0; i < bricks.size(); i++) {
		if (bricks[i].Contains(ball.x_position + ball.x_velocity, ball.y_position + ball.y_velocity))
		{
			bricks[i].color = ConsoleColor(bricks[i].color - 1);
			ball.y_velocity *= -1;
			bricks[i].count++;

			// TODO #5 - If the ball hits the same brick 3 times (color == black), remove it from the vector
			if (bricks[i].count == 3) {
				bricks.erase(bricks.begin() + i);
				i--;
			}
		}
	}

	// TODO #6 - If no bricks remain, pause ball and display victory text with R to reset
	if (bricks.size() == 0) {
		ball.moving = false;
		Render();
		bricks.clear();
		if (GetAsyncKeyState('R') & 0x1)
			Reset();
	}

	if (paddle.Contains(ball.x_position + ball.x_velocity, ball.y_velocity + ball.y_position))
	{
		ball.y_velocity *= -1;
	}

	// TODO #7 - If ball touches bottom of window, pause ball and display defeat text with R to reset
	if (ball.y_position == Console::WindowHeight()) {
		ball.moving = false;
		Render();
		bricks.clear();
		if (GetAsyncKeyState('R') & 0x1)
			Reset();
	}
}
