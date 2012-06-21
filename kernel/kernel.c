#include "h/system.h"

int main () {
	
	screen_setup ();
	idt_install ();
	__asm__ __volatile__ ("sti");
	
	sleep (5);
	cls ();
	puts ("> ");
	putsbar ("\t\t\t\tchat with CPU...", -1);
	
	while (1);
	return 0;

}
