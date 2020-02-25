#include "PushableBlockGrid.h"
#include "EBlockSide.h"

PushableBlockGrid::PushableBlockGrid() : Width(9), Height(9)
{
	InitializeCells(9, 9);
}

PushableBlockGrid::PushableBlockGrid(int width, int height)
	: Width(width), Height(height)
{
	InitializeCells(width, height);
}

void PushableBlockGrid::InitializeCells(int width, int height)
{
	Cells = new int* [width];
	for (int i = 0; i < width; i++)
		Cells[i] = new int[height];


	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
		{
			Cells[i][j] = 0;
		}

	GoalCells = std::vector<std::tuple<int, int>>();
}

std::tuple<int, int> PushableBlockGrid::PushBlockInDirection(int x, int y, EBlockSide side)
{
	int xDir = GetXDir(side);
	int yDir = GetYDir(side);
	
	if (!IsValidCell(x, y))
	{
		return std::tuple<int, int>(-1, -1);
	}

	Cells[x][y] = 0;
	while (IsValidMove(x + xDir, y + yDir))
	{
		x += xDir;
		y += yDir;
	}

	Cells[x][y] = 1;

	return std::tuple<int, int>(x, y);
}

int PushableBlockGrid::GetXDir(EBlockSide side)
{
	if (side == EBlockSide::Left)
	{
		return 1;
	}
	if (side == EBlockSide::Right)
	{
		return -1;
	}
	return 0;
}

int PushableBlockGrid::GetYDir(EBlockSide side)
{
	if (side == EBlockSide::Front)
	{
		return 1;
	}
	if (side == EBlockSide::Back)
	{
		return -1;
	}
	return 0;
}

bool PushableBlockGrid::IsValidCell(int x, int y)
{
	return x >= 0 && x < Width && y >= 0 && y < Height;
}

bool PushableBlockGrid::IsValidMove(int x, int y)
{
	return IsValidCell(x, y) && Cells[x][y] <= 0;
}

void PushableBlockGrid::InitializeLocation(int x, int y, int value)
{
	if (IsValidCell(x, y))
	{
		Cells[x][y] = value;
	}
	if (value < 0)
	{
		GoalCells.push_back(std::tuple<int, int>(x, y));
	}
}

bool PushableBlockGrid::PuzzleIsComplete()
{
	for(auto& cell : GoalCells)
	{
		int value = Cells[std::get<0>(cell)][std::get<1>(cell)];
		if (value < 0)
		{
			return false;
		}
	}
	return true;
}





