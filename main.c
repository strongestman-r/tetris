#include <GL/glut.h>
#include "stage.h"
#include "timer.h"
#include "block.h"
#include "game.h"

int main(int argc, char** argv)
{
  initDrawEnv(&argc, argv); // �`����̏�����
  initStage();      // �X�e�[�W�̏�����

  initBlockPattern();
  initBlock();
  glutKeyboardFunc(doKeyEvent);

  glutDisplayFunc(myDisplay);       // �i�āj�`�掞�ɌĂяo���֐�
  glutTimerFunc(CLOCK, myTimer, 0); // CLOCK�i�~���b�j ���� myTimer �����s
  glutMainLoop();                   // �C�x���g�҂���Ԃɂ���

  return 0;
}

///// End of file /////
