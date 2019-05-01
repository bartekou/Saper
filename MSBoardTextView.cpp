#include "MSBoardTextView.h"
#include <iostream>

MSBoardTextView::MSBoardTextView(MinesweeperBoard &gameboard) : board_view(gameboard)
{
}

void MSBoardTextView::game_display()
{
    std::string display;
    int boardHeight=board_view.getHeight();
    int boardWidth=board_view.getWidth();
    for (int y = 0; y<boardHeight; y++)
    {
        for (int x = 0; x<boardWidth; x++)
        {
            display+="[";
            display+=board_view.getFieldInfo(x,y);
            display+="]";
        }
        display+= "\n";
    }
    std::cout << display;
}
