#ifndef MSTEXTCONTROLLER_H
#define MSTEXTCONTROLLER_H

#include "MinesweeperBoard.h"
#include "MSBoardTextView.h"

class MSTextController
{
    MinesweeperBoard &board_action;
    MSBoardTextView &board_view;
    int x;
    int y;
    int choose;
public:
    MSTextController(MinesweeperBoard &board_action, MSBoardTextView &board_view);
    void play();
};

#endif // MSTEXTCONTROLLER_H
