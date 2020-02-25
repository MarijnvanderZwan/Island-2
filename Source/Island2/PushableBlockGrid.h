#pragma once
#include <tuple>
#include <vector>

enum class EBlockSide : unsigned char;

class PushableBlockGrid
{
public:
	PushableBlockGrid();
	PushableBlockGrid(int width, int height);

	int** Cells;
	int Width;
	int Height;
	std::vector<std::tuple<int, int>> GoalCells;
	
	void InitializeCells(int width, int height);
	std::tuple<int, int> PushBlockInDirection(int x, int y, EBlockSide side);
	int GetXDir(EBlockSide side);
	int GetYDir(EBlockSide side);
	bool IsValidCell(int x, int y);
	bool IsValidMove(int x, int y);
	void InitializeLocation(int x, int y, int value);
	bool PuzzleIsComplete();
};
