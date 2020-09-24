#include <stdio.h>
#define VS_SYSTEM_IMPLEMENTATION
#include "../src/VSSystem.h"

void quit()
{
	vsWindowClose();
}

void click(int btn)
{
	printf("Mouse btn pressed: %d\n", btn);
}

void keypress(int key)
{
	printf("Key pressed: %d\n", key);
}

int main()
{
	vsSystemInit("Test", 800, 600, 1, 0);	
	
	vsSystemBindEventQuit(quit);
	vsSystemBindEventMouseClick(click);
	vsSystemBindEventKeyPress(keypress);

	int k = 0;

	while(vsWindowIsOpen()) {
	
		if (k++ > 60) {
			printf("TimeFromStart: %f TimePerFrame: %f\n", vsTimeGetFromStart(), vsTimeGetElapsed());
			k = 0;
		}
		
		/*
		if (vsMouseGetState(VS_BTN_LEFT)) 
			printf("Hello World\n");
		
		if (vsKeyGetState(VS_KEY_H))
			printf("Hello World\n");
		*/

		vsWindowSwapBuffers();
		vsSystemPollEvents();
	}

	vsSystemDestroy();
	return 0;
}
