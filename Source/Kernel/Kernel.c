/*
 * Kernel.c
 */

void KMain()
{
	char *VIDEO_MEMORY = (char*)0xB8000;
	int n = 160;
	VIDEO_MEMORY[n++] = 'R';
	n++;
	VIDEO_MEMORY[n++] = 'F';
}
