#include "../h/system.h"

struct idt_entry {

	unsigned short base_lo;
	unsigned short segment;
	unsigned char always0;
	unsigned char flags;
	unsigned short base_hi;

} __attribute__((packed));

struct idt_ptr {

	unsigned short limit;
	unsigned int base;

} __attribute__ ((packed));

struct idt_entry idt [256];
struct idt_ptr idtp;

extern void idt_load ();

void idt_set_entry (unsigned char num, unsigned long base, unsigned short segment, unsigned char flags) {

	idt [num].base_lo = base & 0xffff;
	idt [num].segment = segment;
	idt [num].always0 = 0;
	idt [num].flags = flags;
	idt [num].base_hi = (base >> 16);
	
	return;

}

void idt_install () {
	
	
	idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
	idtp.base = (unsigned int) &idt;
	
	
	memset ((unsigned char *) &idt, 0, 256 * sizeof (struct idt_entry));
	exc_install ();
	irq_install ();

	idt_load ();
	return;

}
