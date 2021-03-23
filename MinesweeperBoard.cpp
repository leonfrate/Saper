#include <iostream>
#include "MinesweeperBoard.h"

MinesweeperBoard::MinesweeperBoard(int width, int height, GameMode mode) : width(width), height(height)
{
    width = width;
    height = height;
    mode = mode;

    int minecount = 0;

    for (int wier = 0; wier < height; wier++)
    {

        if (mode == DEBUG)
        {
            for (int kol = 0; kol < width; kol++)
            {
                if (wier == kol)
                    Board[wier][kol].hasMine = true;

                if (wier == 0)
                    Board[wier][kol].hasMine = true;

                if (kol == 0 and wier % 2 == 0)
                    Board[wier][kol].hasMine = true;

                Board[wier][kol].isRevealed = true;
                Board[wier][kol].hasFlag = false;
            }
        }

        if (mode == EASY)
        {
            int mines = 0.1 * width * height;
            
            while (minecount != mines + 1)
            {
                Board[rand() % height][rand() % width].hasMine = true;
                minecount++;
            }
        }

        if (mode == NORMAL)
        {
            int mines = 0.2 * width * height;

            while (minecount != mines + 1)
            {
                Board[rand() % height][rand() % width].hasMine = true;
                minecount++;
            }
        }

        if (mode == HARD)
        {
            int mines = 0.3 * width * height;

            while (minecount != mines + 1)
            {
                Board[rand() % height][rand() % width].hasMine = true;
                minecount++;
            }

        }

    }

}


void MinesweeperBoard::debug_display() const
{
    for (int wier = 0; wier < height; wier++)
    {
        for (int kol = 0; kol < width; kol++)
        {
            if (Board[wier][kol].hasMine == true)
                std::cout << "[M";
            else
                std::cout << "[.";

            if (Board[wier][kol].isRevealed == true)
                std::cout << "o";
            else
                std::cout << ".";

            if (Board[wier][kol].hasFlag == true)
                std::cout << "f]";
            else
                std::cout << ".]";
        }

        std::cout << std::endl;
    }

}


int MinesweeperBoard::getBoardWidth() const
{
    return width;
}


int MinesweeperBoard::getBoardHeight() const
{
    return height;
}


int MinesweeperBoard::getMineCount() const
{
    int minecount = 0;

    for (int wier = 0; wier < height; wier++)
    {
        for (int kol = 0; kol < width; kol++)
        {
            if (Board[wier][kol].hasMine == true)
                minecount++;
        }
    }

    return minecount;
}


int MinesweeperBoard::countMines(int wier, int kol) const
{
    int minecount = 0;

    if (Board[wier][kol].isRevealed == false)
        return -1;

    if (wier > height or kol > width)
        return -1;

    if (Board[wier - 1][kol - 1].hasMine == true)
        minecount += 1;

    if (Board[wier][kol - 1].hasMine == true)
        minecount += 1;

    if (Board[wier + 1][kol - 1].hasMine == true)
        minecount += 1;

    if (Board[wier + 1][kol].hasMine == true)
        minecount += 1;

    if (Board[wier - 1][kol].hasMine == true)
        minecount += 1;

    if (Board[wier + 1][kol + 1].hasMine == true)
        minecount += 1;

    if (Board[wier][kol + 1].hasMine == true)
        minecount += 1;

    if (Board[wier - 1][kol + 1].hasMine == true)
        minecount += 1;

    return minecount;
}


bool MinesweeperBoard::hasFlag(int wier, int kol) const
{
    if (wier > height or kol > width)
        return false;

    if (Board[wier][kol].hasFlag == false)
        return false;

    if (Board[wier][kol].isRevealed == true)
        return false;

    if (Board[wier][kol].hasFlag == true)
        return true;
}


void MinesweeperBoard::toggleFlag(int wier, int kol)
{
    if (Board[wier][kol].isRevealed == false)
        Board[wier][kol].hasFlag = true;

    if (Board[wier][kol].isRevealed == true)
        return;

    if (wier > height or kol > width)
        return;

    if (FINISHED_LOSS or FINISHED_WIN)
        return;
}


bool MinesweeperBoard::isRevealed(int wier, int kol) const
{
    if (Board[wier][kol].isRevealed == true)
        return true;
}


void MinesweeperBoard::revealField(int wier, int kol)
{
    bool notTouchedBoard = true;

    if (Board[wier][kol].isRevealed == true)
        return;

    if (wier > height or kol > width)
        return;

    if (FINISHED_LOSS or FINISHED_WIN)
        return;

    if (Board[wier][kol].hasFlag == true)
        return;

    if (Board[wier][kol].isRevealed == false and Board[wier][kol].hasMine == false)
        Board[wier][kol].isRevealed = true;

    if (Board[wier][kol].isRevealed == false and Board[wier][kol].hasMine == true)
    {
        
        for (int i = 0; i < wier; i++)
        {
            for (int j = 0; j < kol; j++)
            {
                if (Board[i][j].isRevealed == true)
                {
                    notTouchedBoard = false;
                }
            }
        }

        if (notTouchedBoard == true)
        {
            Board[wier][kol].isRevealed = true;
            Board[wier][kol].hasMine = false;
            Board[rand() % wier - 1][rand() % kol - 1].hasMine = true;
        }

        else
        {
            Board[wier][kol].isRevealed = true;
            FINISHED_LOSS;
        }

    }

}


char MinesweeperBoard::getFieldInfo(int wier, int kol) const
{
    if (wier > height or kol > width)
        return '#';

    if (Board[wier][kol].isRevealed == false and Board[wier][kol].hasFlag == true)
        return 'F';

    if (Board[wier][kol].isRevealed == false and Board[wier][kol].hasFlag == false)
        return '_';

    if (Board[wier][kol].isRevealed == true and Board[wier][kol].hasMine == true)
        return 'x';

    if (Board[wier][kol].isRevealed == true and countMines(wier, kol) == 0)
        return ' ';

    if (Board[wier][kol].isRevealed == true and countMines(wier, kol) != 0)
        return countMines(wier, kol);
}

GameState MinesweeperBoard::getGameState() const
{
    if (FINISHED_LOSS)
        return FINISHED_LOSS;

    if (FINISHED_WIN)
        return FINISHED_WIN;

    if (RUNNING)
        return RUNNING;
}