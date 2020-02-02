#include <GL/glut.h>
#include "timer.h"
#include "stage.h"



void myTimer()
{
	static int counter = 0;
	if (++counter == 30 - 5 * (getLevel() - 1)) {
		counter = 0;
		if (!isGameEnd()) {
			if (isDescendible()) {
				descend();
			}
			else {
				absorbBlock();
				updateStage();
				updateBlock();
				if (isOverlapped()) { setGameEnd(); }
			}
		}
	}
  glutTimerFunc(CLOCK, myTimer, 0);
  glutPostRedisplay();
}

///// End of file /////
