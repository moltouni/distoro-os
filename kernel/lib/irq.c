#include "../h/system.h"

extern void irq0 ();
extern void irq1 ();
extern void irq2 ();
extern void irq3 ();
extern void irq4 ();
extern void irq5 ();
extern void irq6 ();
extern void irq7 ();
extern void irq8 ();
extern void irq9 ();
extern void irq10 ();
extern void irq11 ();
extern void irq12 ();
extern void irq13 ();
extern void irq14 ();
extern void irq15 ();

int uptime_h = 0, uptime_m = 0, uptime_s = 0, uptime_ms = 0;

void *irq_func [16] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0
};

int keystatus [4] = {0, 0, 0, 0};
unsigned char keymapUS [128] =
{
	0,  27, '1', '2', '3', '4', '5', '6', '7', '8',
	'9', '0', '-', '=', '\b', '\t', 'q', 'w', 'e', 'r',
	't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
	'\'', '`',   0, '\\', 'z', 'x', 'c', 'v', 'b', 'n',
	'm', ',', '.', '/',   0, '*', 0, ' ', 0, 0,
	0,   0,   0,   0,   0,   0,   0,   0,
	0, 0, 0, 0, 0, 0, '-', 0, 0, 0, '+', 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0,
};

void irq_add_func (int irq, void (*handler) (struct regs *r)) {

	irq_func [irq] = handler;

}

void irq_del_func (int irq) {

	irq_func [irq] = 0;

}

void irq_remap (void) {

	oport (0x20, 0x11);
	oport (0xa0, 0x11);
	
	oport (0x21, 0x20);
	oport (0xa1, 0x28);
	
	oport (0x21, 0x04);
	oport (0xa1, 0x02);
	
	oport (0x21, 0x01);
	oport (0xa1, 0x01);
	
	oport (0x21, 0x0);
	oport (0xa1, 0x0);
	

}

void irq_install () {

	irq_remap ();
	
	idt_set_entry (32, (unsigned) irq0, 0x08, 0x8e);
	idt_set_entry (33, (unsigned) irq1, 0x08, 0x8e);
	idt_set_entry (34, (unsigned) irq2, 0x08, 0x8e);
	idt_set_entry (35, (unsigned) irq3, 0x08, 0x8e);
	idt_set_entry (36, (unsigned) irq4, 0x08, 0x8e);
	idt_set_entry (37, (unsigned) irq5, 0x08, 0x8e);
	idt_set_entry (38, (unsigned) irq6, 0x08, 0x8e);
	idt_set_entry (39, (unsigned) irq7, 0x08, 0x8e);
	idt_set_entry (40, (unsigned) irq8, 0x08, 0x8e);
	idt_set_entry (41, (unsigned) irq9, 0x08, 0x8e);
	idt_set_entry (42, (unsigned) irq10, 0x08, 0x8e);
	idt_set_entry (43, (unsigned) irq11, 0x08, 0x8e);
	idt_set_entry (44, (unsigned) irq12, 0x08, 0x8e);
	idt_set_entry (45, (unsigned) irq13, 0x08, 0x8e);
	idt_set_entry (46, (unsigned) irq14, 0x08, 0x8e);
	idt_set_entry (47, (unsigned) irq15, 0x08, 0x8e);
	
	irq_func [0] = irq_func [1] = irq_func [2] = irq_func [3] = irq_func [4] = irq_func [5] = irq_func [6] = irq_func [7] = 0;
	irq_func [8] = irq_func [9] = irq_func [10] = irq_func [11] = irq_func [12] = irq_func [13] = irq_func [14] = irq_func [15] = 0;
	
	configure_timer (100);
	configure_kb ();


}

void irq_handler (struct regs *r) {

	void (*handler) (struct regs *r);
	handler = irq_func [r-> int_no - 32];
	if (handler) { handler (r); }
	else { puts ("I've lost that ISR!"); while (1); }
	
	if (r->int_no >= 40) oport (0xa0, 0x20);
	oport (0x20, 0x20);


}

void configure_kb () {

	irq_add_func (1, isr_kb);

}

void isr_kb (struct regs *r) {
	
	char *tipka;
	unsigned char scancode = iport (0x60);
	
	if (scancode & 0x80) {
		
		scancode = scancode & 127;
		if (scancode == 58) { keystatus [1] = ~keystatus [1]; }
		else if (scancode == 69) { keystatus [0] = ~keystatus [0]; }
			else if (scancode == 70) { keystatus [2] = ~keystatus [2]; }
				else if (scancode == 54 || scancode == 42) { keystatus [3] = ~keystatus [3];  }

	}
	else {
	
	if (scancode == 54 || scancode == 42) { keystatus [3] = ~keystatus [3];  }
	*tipka = keymapUS [scancode];
	if ((keystatus [1] || keystatus [3]) && (*tipka >= 'a' && *tipka <= 'z')) *tipka -= 32;
	else if (scancode == 28) puts ("\r");
	puts (tipka);
	
	}
	
	return;

}

void configure_timer (int hz) {
	
	oport (0x43, 0x36);
	
	int koliko = 1193180 / hz;
	oport (0x40, koliko & 0xff);
	oport (0x40, koliko >> 8);
	
	irq_add_func (0, isr_timer);
	uptime_h = uptime_m = uptime_s = uptime_ms = 0;
	
	return;

}

void isr_timer (struct regs *r) {
	
	uptime_ms = uptime_ms + 10;
	int promjenaclk = 0;
	if (uptime_ms == 1000) { uptime_ms = 0; uptime_s = uptime_s + 1; promjenaclk = 1; }
	if (uptime_s == 60)  { uptime_s = 0; uptime_m = uptime_m + 1; }
	if (uptime_m == 60) ++uptime_h;
	if (promjenaclk) putclock ();
	
	return;

}
