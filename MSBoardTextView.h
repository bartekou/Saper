#ifndef MSBOARDTEXTVIEW_H
#define MSBOARDTEXTVIEW_H

#include "MinesweeperBoard.h"


class MSBoardTextView
{
    MinesweeperBoard &board_view;

public:
    MSBoardTextView(MinesweeperBoard &gameboard);
    void game_display();

};

#endif // MSBOARDTEXTVIEW_H
