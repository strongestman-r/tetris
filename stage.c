#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "stage.h"
#include "block.h"

struct Stage s;
extern struct Block b;
extern struct Block nb;
extern struct BlockPattern bp[7];

static void updateBoard(int x, int y, int p)
{
  s.board[x][y] = p;
}

static void setStr()
{
  char *point;

  glColor3d(0.0, 0.0, 0.0);

  glRasterPos3d(3.0 / 12.0, 3.0 / 12.0, 0.0);
  for(point = s.strShapes; *point; point++){
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *point);
  }

  glRasterPos3d(3.0 / 12.0, 2.0 / 12.0, 0.0);
  for(point = s.strRows; *point; point++){
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *point);
  }

  glRasterPos3d(3.0 / 12.0, 1.0 / 12.0, 0.0);
  for(point = s.strScore; *point; point++){
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *point);
  }

  glRasterPos3d(3.0 / 12.0, 0.0 / 12.0, 0.0);
  for(point = s.strLevel; *point; point++){
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *point);
  }

  if (isGameEnd()) {
	  glRasterPos3d(3.0 / 12.0, -2.0 / 12.0, 0.0);
	  for (point = s.strGameEnd; *point; point++) {
		  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *point);
	  }
  }
}

static void setBoard()
{
  glColor3d(0.0, 0.0, 0.2);

  // Game Board

  glBegin(GL_QUADS);
  glVertex2f(-10.0 / 12.0, -10.0 / 12.0);
  glVertex2f(-10.0 / 12.0, -11.0 / 12.0);
  glVertex2f(  2.0 / 12.0, -11.0 / 12.0);
  glVertex2f(  2.0 / 12.0, -10.0 / 12.0);
  glEnd();

  glBegin(GL_QUADS);
  glVertex2f(-10.0 / 12.0,  10.0 / 12.0);
  glVertex2f(-10.0 / 12.0,  11.0 / 12.0);
  glVertex2f(  2.0 / 12.0,  11.0 / 12.0);
  glVertex2f(  2.0 / 12.0,  10.0 / 12.0);
  glEnd();

  glBegin(GL_QUADS);
  glVertex2f(-10.0 / 12.0,  10.0 / 12.0);
  glVertex2f(-10.0 / 12.0, -10.0 / 12.0);
  glVertex2f(- 9.0 / 12.0, -10.0 / 12.0);
  glVertex2f(- 9.0 / 12.0,  10.0 / 12.0);
  glEnd();

  glBegin(GL_QUADS);
  glVertex2f(  1.0 / 12.0,  10.0 / 12.0);
  glVertex2f(  1.0 / 12.0, -10.0 / 12.0);
  glVertex2f(  2.0 / 12.0, -10.0 / 12.0);
  glVertex2f(  2.0 / 12.0,  10.0 / 12.0);
  glEnd();

  // Next Window

  glBegin(GL_QUADS);
  glVertex2f(  3.0 / 12.0,   5.0 / 12.0);
  glVertex2f(  3.0 / 12.0,   4.0 / 12.0);
  glVertex2f( 10.0 / 12.0,   4.0 / 12.0);
  glVertex2f( 10.0 / 12.0,   5.0 / 12.0);
  glEnd();

  glBegin(GL_QUADS);
  glVertex2f(  3.0 / 12.0,  11.0 / 12.0);
  glVertex2f(  3.0 / 12.0,  10.0 / 12.0);
  glVertex2f( 10.0 / 12.0,  10.0 / 12.0);
  glVertex2f( 10.0 / 12.0,  11.0 / 12.0);
  glEnd();

  glBegin(GL_QUADS);
  glVertex2f(  3.0 / 12.0,  10.0 / 12.0);
  glVertex2f(  3.0 / 12.0,   5.0 / 12.0);
  glVertex2f(  4.0 / 12.0,   5.0 / 12.0);
  glVertex2f(  4.0 / 12.0,  10.0 / 12.0);
  glEnd();

  glBegin(GL_QUADS);
  glVertex2f(  9.0 / 12.0,  10.0 / 12.0);
  glVertex2f(  9.0 / 12.0,   5.0 / 12.0);
  glVertex2f( 10.0 / 12.0,   5.0 / 12.0);
  glVertex2f( 10.0 / 12.0,  10.0 / 12.0);
  glEnd();

  glFlush();
}

static void showPiece(float x, float y, float r, float g, float b)
{
  glColor3d(r, g, b);
  glBegin(GL_QUADS);

  glVertex2f(x       / 12.0 / W * 10.0, y       / 12.0 / H * 20.0);
  glVertex2f((x + 1) / 12.0 / W * 10.0, y       / 12.0 / H * 20.0);
  glVertex2f((x + 1) / 12.0 / W * 10.0, (y + 1) / 12.0 / H * 20.0);
  glVertex2f(x       / 12.0 / W * 10.0, (y + 1) / 12.0 / H * 20.0);

  glEnd();

  glFlush();
}

void initDrawEnv(int* argc, char** argv)
{
  glutInit(argc, argv);  // OpenGL 環境の初期化

  // 表示モードの設定
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

  glutInitWindowSize(600, 600);  // ウィンドウサイズの指定
  glutInitWindowPosition(0, 0);  // ウィンドウ位置の指定
  glutCreateWindow(argv[0]);  // ウィンドウの生成
  glClearColor(0.8, 0.8, 0.8, 1.0);  // 塗りつぶし色の指定
}

void initStage()
{
  int i, j;

  for(i = 0; i < W; i++){
    for(j = 0; j < H; j++){
      s.board[i][j] = -1;
    }
  }

  setStrShapes(0);
  setStrRows(0);
  setStrScore(0);
  setStrLevel(0);
  sprintf(s.strGameEnd, "GAME OVER");
}

void absorbBlock()
{
	int i;
	for (i = 0; i < 4; i++) {
		updateBoard(b.rpx + bp[b.pattern].x[b.mode][i], // 以下で修正します
			b.rpy + bp[b.pattern].y[b.mode][i], // 以下で修正します
			b.pattern);
	}
}

void showPieceRandomly()
{
	int x, y;
	float r, g, b;
	// rand 関数を用いて…
	x = rand() % 10; // 0 <= x < 10 となるようなint をランダムに
	y = rand() % 20; // 0 <= y < 20 となるようなint をランダムに
	r = rand() % 11 / 10; // 0.0 <= r <= 1.0 となるfloat をランダムに
	g = rand() % 11 / 10; // 0.0 <= g <= 1.0 となるfloat をランダムに
	b = rand() % 11 / 10; // 0.0 <= b <= 1.0 となるfloat をランダムに
	showPieceInBoard(x, y, r, g, b);
}

int isCompleteLine(int y)
{
	int i;
	for (i = 0; i < W; i++) {
		if (s.board[i][y] < 0) { return 0; }
	}
	return 1;
}

int isPiece(int x, int y)
{
	if (x > 9 || x < 0 || y < 0) { return 1; }
	if (y < H && s.board[x][y] >= 0) { return 1; }
	else { return 0; }
}

void eraseLine(int y)
{
	int i, j;

	for (i = 0; i < W; i++) {
		for (j = y + 1; j < H; j++){
			s.board[i][j - 1] = s.board[i][j];
		}
	}
}

void showBlock()
{
	int i;
	for (i = 0; i < 4; i++) {
		showPieceInBoard(
			b.rpx + bp[b.pattern].x[b.mode][i],
			b.rpy + bp[b.pattern].y[b.mode][i],
			bp[b.pattern].rgb[0],
			bp[b.pattern].rgb[1],
			bp[b.pattern].rgb[2]
		);
		showPieceInNextWindow(
			nb.rpx + bp[nb.pattern].x[nb.mode][i],
			nb.rpy + bp[nb.pattern].y[nb.mode][i],
			bp[nb.pattern].rgb[0],
			bp[nb.pattern].rgb[1],
			bp[nb.pattern].rgb[2]
		);
	}
}



void showBoard()
{
	int i, j, k;
	for (i = 0; i < W; i++) {
		for (j = 0; j < H; j++) {
			k = s.board[i][j];
			if (k >= 0) {
				showPieceInBoard(i, j, // 以下で修正します
					bp[k].rgb[0],
					bp[k].rgb[1],
					bp[k].rgb[2]);
			}
		}
	}
}

void myDisplay()
{
  // ウィンドウを塗りつぶす設定
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  setStr();
  setBoard();

  showBlock();
  showBoard();

  glutSwapBuffers();  // 描画する
}


void showPieceInBoard(int x, int y, float r, float g, float b)
{
  float x_ = -9  * (W / 10.0) + x;
  float y_ = -10 * (H / 20.0) + y;

  if(x < 0 || x >= W || y < 0 || y >= H) { return; }

  showPiece(x_, y_, r, g, b);
}

void showPieceInNextWindow(int x, int y, float r, float g, float b)
{
  float x_ = 4 * (W / 10.0) + x;
  float y_ = 5 * (H / 20.0) + y;

  if(x < 0 || x >= 5 || y < 0 || y >= 5) { return; }

  showPiece(x_, y_, r, g, b);
}

void setStrShapes(int shapes)
{
  sprintf(s.strShapes, "Shapes: %05d", shapes);
}

void setStrRows(int rows)
{
  sprintf(s.strRows, "Rows  : %05d", rows);
}

void setStrScore(int score)
{
  sprintf(s.strScore, "Score : %05d", score);
}

void setStrLevel(int level)
{
  sprintf(s.strLevel, "Level : %05d", level);
}

///// End of file /////
