#ifndef MinesweeperBoard_H_
#define MinesweeperBoar_H_

enum GameMode { DEBUG, EASY, NORMAL, HARD} ;
enum GameState { RUNNING, FINISHED_WIN, FINISHED_LOSS };

struct Field
{
    bool hasMine;
    bool hasFlag;
    bool isRevealed;
};

class MinesweeperBoard
{
    Field Board[100][100];
    int width;
    int height;
    
    

public:
    static int minecount;

    MinesweeperBoard(int width, int height, GameMode mode);
    void debug_display() const;
    int getBoardWidth() const;
    int getBoardHeight() const;
    int getMineCount() const;
    int countMines(int wier, int kol) const;
    bool hasFlag(int wier, int kol);
    void toggleFlag(int wier, int kol);
    void revealField(int wier, int kol) const;
    bool isRevealed(int wier, int kol) const;
    GameState getGameState() const;
    char getFieldInfo(int row, int col) const;
};

#endif


/*

enum GameMode { DEBUG, EASY, NORMAL, HARD };
enum GameState { RUNNING, FINISHED_WIN, FINISHED_LOSS };

struct Field
{
  bool hasMine;
  bool hasFlag;
  bool isRevealed;
};

class MinesweeperBoard
{
  Field Board[100][100];
  int width;
  int height;

public:
  MinesweeperBoard(int width, int height, GameMode mode);
  void debug_display() const;
};

*/