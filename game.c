#include <stdlib.h>
#include <GL/glut.h>
#include "game.h"
#include "stage.h"
#include "block.h"

extern struct Block b;
extern struct BlockPattern bp[7];

int isEnd = 0;

int shapes = 0;
int rows = 0;
int score = 0;
int level = 0;

int k = 0;

void doKeyEvent(unsigned char key, int x, int y)
{
  switch(key){
  case 'j': // left
    if(isMovableLeft())  { moveLeft(); }
    break;
  case 'k': // turn
    if(isRotatable())    { rotate(); }
    break;
  case 'l': // right
    if(isMovableRight()) { moveRight(); }
    break;
  case 'm': // falling
    if(isDescendible())  { descend(); }
    break;
  default:
    ; // do nothing
  }
}

void incrementShapesNum() // step10 ‚Å’Ç‰Á
{
	setStrShapes(++shapes);
}
void incrementRowsNum() // step10 ‚Å’Ç‰Á
{
	setStrRows(++rows);
}
void incrementScore(int delta) // step10 ‚Å’Ç‰Á
{
	score += delta;
	setStrScore(score);
}

void setLevel() // step10 ‚Å’Ç‰Á
{
	if (score >= 0 && score <= 300) { level = 1; }
	else if (score >= 300) { level = 2; }
	else if (score >= 1000) { level = 3; }
	else if (score >= 2000) { level = 4; }

	setStrLevel(level);
}

void updateStage()
{
	int j, n = 0;

	for (j = b.rpy; j < b.rpy + 5; j++) {
		if (isCompleteLine(j - n)) {
			eraseLine(j - n);
			n++;
			incrementRowsNum();
			incrementScore(100);
		}
	}
	incrementShapesNum();
	incrementScore(10);
	setLevel();
}

void setGameEnd()
{
	isEnd = 1;
}

int isMovableLeft()
{
	int i, x_, y_;
	for (i = 0; i < 4; i++) {
		x_ = b.rpx + bp[b.pattern].x[b.mode][i] - 1;
		y_ = b.rpy + bp[b.pattern].y[b.mode][i];
		if (x_ < 0) { return 0; }
		if (isPiece(x_, y_)) { return 0; }
	}
	return 1;
}

int isMovableRight()
{
	int i, x_, y_;
	for (i = 0; i < 4; i++) {
		x_ = b.rpx + bp[b.pattern].x[b.mode][i] + 1;
		y_ = b.rpy + bp[b.pattern].y[b.mode][i];
		if (x_ > 9) { return 0; }
		if (isPiece(x_, y_)) { return 0; }
	}
	return 1;
}

int isRotatable()
{
	int i, x_, y_, mode_;
	mode_ = (b.mode + 1) % 4;
	for (i = 0; i < 4; i++) {
		y_ = b.rpy + bp[b.pattern].y[mode_][i];
		if (y_ < 0) { return 0; }
	}
	for (i = 0; i < 4; i++) {
		x_ = b.rpx + bp[b.pattern].x[mode_][i];
		if (x_ > 9) { return 0; }
	}
	for (i = 0; i < 4; i++) {
		x_ = b.rpx + bp[b.pattern].x[mode_][i];
		if (x_ < 0) { return 0; }
		if (isPiece(x_, y_)) { return 0; }
	}
	return 1;
}

int isDescendible()
{
	int i, x_, y_;
	for (i = 0; i < 4; i++) {
		x_ = b.rpx + bp[b.pattern].x[b.mode][i];
		y_ = b.rpy + bp[b.pattern].y[b.mode][i] - 1;
		if (y_ < 0) { return 0; }
		if (isPiece(x_, y_)) { return 0; }
	}
	return 1;
}

int isGameEnd()
{
	return isEnd;
}

int isOverlapped()
{
	int i, x_, y_;

	for (i = 0; i < 4; i++) {
		x_ = b.rpx + bp[b.pattern].x[b.mode][i];
		y_ = b.rpy + bp[b.pattern].y[b.mode][i];
		if (isPiece(x_, y_)) { return 1; }
	}

	return 0;
}

int getLevel() // step10 ‚Å’Ç‰Á
{
	return level;
}

void moveLeft()
{
	b.rpx--;
}

void moveRight()
{
	b.rpx++; // ì‚è‚Ü‚µ‚å‚¤
}

void rotate()
{
	b.mode = k % 4;
	k++;// ì‚è‚Ü‚µ‚å‚¤
}

void descend()
{
	b.rpy--; // ì‚è‚Ü‚µ‚å‚¤
}

///// End of file /////
