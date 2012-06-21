#include "../h/system.h"

char* isr_message [] = {
	"E: Division by zero",
	"E: Debug",
	"E: Non Maskable Interrupt",
	"E: Breakpoint",
	"E: Into Detected Overflow",
	"E: Out of Bounds",
	"E: Invalid Opcode",
	"E: No Coprocessor",
	"E: Double Fault",
	"E: Coprocesor Segment Overrun",
	"E: Bad TSS",
	"E: Segment Not Present",
	"E: Stack Fault",
	"E: General Protection Fault",
	"E: Page Fault",
	"E: Unknown Interrupt",
	"E: Coprocessor Fault",
	"E: Alignment Check",
	"E: Machine Check",
	"E: Reserved",
	"E: Reserved",
	"E: Reserved",
	"E: Reserved",
	"E: Reserved",
	"E: Reserved",
	"E: Reserved",
	"E: Reserved",
	"E: Reserved",
	"E: Reserved",
	"E: Reserved",
	"E: Reserved",
	"E: Reserved"
};

void isr_manager (struct regs *r)  {

	if (r->int_no < 32) {
		
		cls ();
		puts ("\t\t\t\t\tSystem failure\n\r\n");
		puts ("\tError: ");
		puts (isr_message[r -> int_no]);
		puts ("\n\r\tSystem Halted!");
		putsbar ("\t\t\t\t\tOh crap!", -1);
		while (1);

	}
	
	else { irq_handler (r); }
	
	return;

}
