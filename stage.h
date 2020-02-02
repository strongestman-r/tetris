#define W 10
#define H 20
#define STRLEN 256

struct Stage{
  int board[W][H];
  char strShapes [STRLEN];
  char strRows   [STRLEN];
  char strScore  [STRLEN];
  char strLevel  [STRLEN];
  char strGameEnd[STRLEN];
};

void showBlock();

void initDrawEnv(int* argc, char** argv);
void initStage();
void myDisplay();

void showPieceInBoard(int x, int y, float r, float g, float b);
void showPieceInNextWindow(int x, int y, float r, float g, float b);
void showBoard();

void setStrShapes(int shapes);
void setStrRows(int rows);
void setStrScore(int score);
void setStrLevel(int level);
void eraseLine(int y);

int isPiece(int x, int y);
int isCompleteLine(int y);



///// End of file /////
