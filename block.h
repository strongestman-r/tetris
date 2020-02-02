struct Block{
  int pattern;
  int mode;
  int rpx;
  int rpy;
};

struct BlockPattern{
  float rgb[3];
  int max_y; // mode 0 Ç≈ÇÃ y ÇÃç≈ëÂíl
  int x[4][4];
  int y[4][4];
};

void initBlock();
void initBlockPattern();
void genNextBlock();
void updateBlock();

///// End of file /////
