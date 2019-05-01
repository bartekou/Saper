#include <iostream>
#include "MinesweeperBoard.h"
#include <string>
#include <stdlib.h>
#include <ctime>

MinesweeperBoard::MinesweeperBoard()
{
    boardWidth=5;
    boardHeight=5;
    setBoard();
}

MinesweeperBoard::MinesweeperBoard(int width, int height, GameMode g_mode)
{
    boardWidth = width;
    boardHeight = height;
    mode = g_mode;
    state=RUNNING;
    mineNumber=0;
    emptyField=0;
    setBoard();
}

void MinesweeperBoard::setField(int x, int y, bool hasMine, bool hasFlag, bool isRevealed)
{
    board[y][x]= {hasMine, hasFlag, isRevealed};
}

int MinesweeperBoard::gameFields(int width, int height)
{
    int area = width*height;
    return area;
}

void MinesweeperBoard::setBoard()
{
    if(mode==DEBUG)
    {
        for (int y=0, x=0; y<boardHeight and x<boardWidth ; y++, x++)
            setField(x,y,true,false,false);
        for (int y=0, x=0; x<boardWidth; x++)
            setField(x,y,true,false,false);
        for (int x=0, y=0; y<boardHeight; y++)
            if(y%2==0)
                setField(x,y,true,false,false);

    }
    if(mode==EASY)
    {
        {
            for (int y = 0; y < boardHeight; y++)
            {
                for (int x = 0; x < boardWidth; x++)
                {
                    setField(x, y, false, false, false);
                }
            }
        }
        int difficulty = 0.1*gameFields(boardWidth,boardHeight);
        for (int counter=1; counter<=difficulty; ++counter)
        {
            int rand_x = (rand() % boardWidth)+ 0;
            int rand_y = (rand() % boardHeight) + 0;
            if (board[rand_y][rand_x].hasMine==0)
            {
                board[rand_y][rand_x].hasMine=true;
                mineNumber++;
            }
            else
                counter--;
        }
        emptyField=gameFields(boardWidth,boardHeight)-mineNumber;
    }

    if(mode==NORMAL)
    {
        {
            for (int y = 0; y < boardHeight; y++)
            {
                for (int x = 0; x < boardWidth; x++)
                {
                    setField(x, y, false, false, false);
                }
            }
        }
        int difficulty = 0.2*gameFields(boardWidth,boardHeight);
        for (int counter=1; counter<=difficulty; ++counter)
        {
            int rand_x = (rand() % boardWidth)+ 0;
            int rand_y = (rand() % boardHeight) + 0;
            if (board[rand_y][rand_x].hasMine==0)
            {
                board[rand_y][rand_x].hasMine=true;
                mineNumber++;
            }
            else
                counter--;
        }
        emptyField=gameFields(boardWidth,boardHeight)-mineNumber;
    }

    if(mode==HARD)
    {
        {
            for (int y = 0; y < boardHeight; y++)
            {
                for (int x = 0; x < boardWidth; x++)
                {
                    setField(x, y, false, false, false);
                }
            }
        }
        int difficulty = 0.3*gameFields(boardWidth,boardHeight);
        for (int counter=1; counter<=difficulty; ++counter)
        {
            int rand_x = (rand() % boardWidth)+ 0;
            int rand_y = (rand() % boardHeight) + 0;
            if (board[rand_y][rand_x].hasMine==0)
            {
                board[rand_y][rand_x].hasMine=true;
                mineNumber++;
            }
            else
                counter--;
        }
        emptyField=gameFields(boardWidth,boardHeight)-mineNumber;
    }
}
/* // funkcja z ktoregos tam etapu
void MinesweeperBoard::debug_display() const
{
    std::string display;
    for (int y = 0; y<boardHeight; y++)
    {
        for (int x = 0; x<boardWidth; x++)
        {
            display+="[";
            if (board[y][x].hasMine)
                display+="M";
            else
                display+=".";
            if (board[y][x].isRevealed)
                display+="o";
            else
                display+=".";
            if (board[y][x].hasFlag)
                display+="f";
            else
                display+=".";
            display+="] ";

        }
        display+= "\n";
    }
    std::cout << display;
}
*/
int MinesweeperBoard::getWidth() const
{
    return boardWidth;
}

int MinesweeperBoard::getHeight() const
{
    return boardHeight;
}

int MinesweeperBoard::getMineNumb() const
{
    return mineNumber;
}

int MinesweeperBoard::countMines(int x, int y)
{
    mineFieldCounter=0;

    if (x >= boardWidth || y >= boardHeight || x<0 || y<0)
        return -1;
    else
    {
        for(int iy=y-1; iy <=y+1; iy++)
        {
            for (int ix=x-1; ix<=x+1 ; ix++)
                if (ix>=0 and ix<boardWidth and iy>=0 and iy<boardHeight)
                {
                    if (iy==y and ix==x)
                        mineFieldCounter+=0;
                    if(board[iy][ix].hasMine and (iy!=y or ix!=x))
                        mineFieldCounter+=1;
                }
        }
    }
    return mineFieldCounter;
}


bool MinesweeperBoard::hasMine(int x, int y) const
{
    if (x<0 or x>=boardWidth or y<0 or y>=boardHeight)
        return false;
    if (board[y][x].hasMine==1)
        return true;
    else
        return false;
}

bool MinesweeperBoard::hasFlag(int x, int y) const
{
    if (x<0 or x>=boardWidth or y<0 or y>=boardHeight)
        return false;
    if (board[y][x].isRevealed==1)
        return false;
    if (board[y][x].hasFlag==0)
        return false;
    if (board[y][x].hasFlag==1)
        return true;
}

bool MinesweeperBoard::isRevealed(int x, int y) const
{


    if (x<0 or x>=boardWidth or y<0 or y>=boardHeight)
        return false;
    if (board[y][x].isRevealed==1)
        return true;
    else
        return false;
}

void MinesweeperBoard::toggleFlag(int x, int y)
{

    ++moves;
    if (board[y][x].isRevealed==1)
        return;
    if (x<0 or x>=boardWidth or y<0 or y>=boardHeight)
        return;
    if (state==FINISHED_WIN or state==FINISHED_LOSS)
        return;
    if (board[y][x].isRevealed==0 and board[y][x].hasMine==1)
    {
        board[y][x].hasFlag=true;
        mineNumber--;
    }
    else
        board[y][x].hasFlag=true;
    if (mineNumber==0)
        state=FINISHED_WIN;
}

void MinesweeperBoard::revealField(int x, int y)
{


    if (x<0 or x>=boardWidth or y<0 or y>=boardHeight)
        return;
    if (state==FINISHED_WIN or state==FINISHED_LOSS)
        return;
    if (board[y][x].hasFlag==1)
        return;


    if (moves!=0 and board[y][x].hasFlag==0 and board[y][x].hasMine==0)
    {

        if (board[y][x].isRevealed==0)
        {
            board[y][x].isRevealed=true;
            moves++;
            emptyField--;
        }
        recursionReveal(x,y);
    }
    if (emptyField==0)
        state=FINISHED_WIN;
    if (moves!=0 and board[y][x].hasMine==1 and mode!=DEBUG)
    {
        board[y][x].isRevealed=true;
        moves++;
        state=FINISHED_LOSS;
    }

    if (board[y][x].isRevealed==0 and moves==0)
    {
        if (board[y][x].hasMine==1 and mode==DEBUG)
        {
            board[y][x].isRevealed=true;
            moves++;
        }
        if (board[y][x].hasMine==1 and mode!=DEBUG)
        {
            for (int counter=1; counter<=1; ++counter)
            {
                int rand_x = (rand() % boardWidth)+ 0;
                int rand_y = (rand() % boardHeight) + 0;
                if (board[rand_y][rand_x].hasMine==0)
                {
                    board[y][x].hasMine=false;
                    board[rand_y][rand_x].hasMine=true;
                }
                else
                    counter--;
            }
            board[y][x].isRevealed=true;
            emptyField--;
        }
        if (board[y][x].hasMine==0 and mode!=DEBUG)
        {
            board[y][x].isRevealed=true;
            moves++;
            emptyField--;
        }
        recursionReveal(x,y);
    }
    if (emptyField==0)
        state=FINISHED_WIN;
}

GameState MinesweeperBoard::getGameState() const
{
    return state;

}

char MinesweeperBoard::getFieldInfo(int x, int y)
{
    char info;
    if (getGameState()==FINISHED_LOSS and board[y][x].hasMine==1)
    {
        info='X';
        return info;
    }
    if (x<0 or x>=boardWidth or y<0 or y>=boardHeight)
    {
        info='#';
        return info;
    }
    if (board[y][x].isRevealed==0 and board[y][x].hasFlag==1)
    {
        info='F';
        return info;
    }
    if (board[y][x].isRevealed==0 and board[y][x].hasFlag==0)
    {
        info='_';
        return info;
    }
    if (board[y][x].isRevealed==1 and board[y][x].hasMine==1)
    {
        info='x';
        return info;
    }
    if (board[y][x].isRevealed==1 and countMines(x,y)==0)
    {
        info=' ';
        return info;
    }
    if (board[y][x].isRevealed==1 and countMines(x,y)!=0)
    {
        int number = countMines(x,y);
        info='0'+number;
        return info;
    }
}

void MinesweeperBoard::recursionReveal(int x, int y)
{
    if (countMines(x,y) == 0)
    {
        for (int i = y - 1; i <= y + 1; i++)
        {
            for (int j = x - 1; j <= x + 1; j++)
            {
                if (j>=0 and j<boardWidth and i>=0 and i<boardHeight and !board[i][j].isRevealed)
                {
                    if (countMines(j, i) == 0)
                    {
                        if (board[i][j].isRevealed==false)
                        {
                            board[i][j].isRevealed = true;
                            emptyField--;
                            revealField(j, i);
                        }

                    }

                    if (countMines(j, i) > 0)
                    {
                        if (board[i][j].isRevealed==false)
                        {
                            board[i][j].isRevealed = true;
                            emptyField--;
                        }
                    }
                }
            }
        }
    }
}
