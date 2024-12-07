#pragma once
#include <vector>
#include <raylib.h>

class Grid
{
    public:
        Grid();
        void Initialize();
        void Draw();
        void Print();
        bool IsCellOutside(int row, int col);
        bool IsCellEmpty(int row, int col);
        int ClearFullRow();
        int grid[20][10];

    private:
        bool IsRowFull(int row);
        void ClearRow(int row);
        void MoveRowDown(int row, int numRows);
        int numRows;
        int numCols;
        int cellSize;
        std::vector<Color> colors;
        
};