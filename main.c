#include <GL/glut.h>
#include "stage.h"
#include "timer.h"
#include "block.h"
#include "game.h"

int main(int argc, char** argv)
{
  initDrawEnv(&argc, argv); // 描画環境の初期化
  initStage();      // ステージの初期化

  initBlockPattern();
  initBlock();
  glutKeyboardFunc(doKeyEvent);

  glutDisplayFunc(myDisplay);       // （再）描画時に呼び出す関数
  glutTimerFunc(CLOCK, myTimer, 0); // CLOCK（ミリ秒） 毎に myTimer を実行
  glutMainLoop();                   // イベント待ち状態にする

  return 0;
}

///// End of file /////
