#include "../h/system.h"

extern void exc0 ();
extern void exc1 ();
extern void exc2 ();
extern void exc3 ();
extern void exc4 ();
extern void exc5 ();
extern void exc6 ();
extern void exc7 ();
extern void exc8 ();
extern void exc9 ();
extern void exc10 ();
extern void exc11 ();
extern void exc12 ();
extern void exc13 ();
extern void exc14 ();
extern void exc15 ();
extern void exc16 ();
extern void exc17 ();
extern void exc18 ();
extern void exc19 ();
extern void exc20 ();
extern void exc21 ();
extern void exc22 ();
extern void exc23 ();
extern void exc24 ();
extern void exc25 ();
extern void exc26 ();
extern void exc27 ();
extern void exc28 ();
extern void exc29 ();
extern void exc30 ();
extern void exc31 ();

void exc_install () {

        idt_set_entry (0, (unsigned) exc0, 0x08, 0x8e);
        idt_set_entry (1, (unsigned) exc1, 0x08, 0x8e);
        idt_set_entry (2, (unsigned) exc2, 0x08, 0x8e);
        idt_set_entry (3, (unsigned) exc3, 0x08, 0x8e);
        idt_set_entry (4, (unsigned) exc4, 0x08, 0x8e);
        idt_set_entry (5, (unsigned) exc5, 0x08, 0x8e);
        idt_set_entry (6, (unsigned) exc6, 0x08, 0x8e);
        idt_set_entry (7, (unsigned) exc7, 0x08, 0x8e);
        idt_set_entry (8, (unsigned) exc8, 0x08, 0x8e);
        idt_set_entry (9, (unsigned) exc9, 0x08, 0x8e);
        idt_set_entry (10, (unsigned) exc10, 0x08, 0x8e);
        idt_set_entry (11, (unsigned) exc11, 0x08, 0x8e);
        idt_set_entry (12, (unsigned) exc12, 0x08, 0x8e);
        idt_set_entry (13, (unsigned) exc13, 0x08, 0x8e);
        idt_set_entry (14, (unsigned) exc14, 0x08, 0x8e);
        idt_set_entry (15, (unsigned) exc15, 0x08, 0x8e);
        idt_set_entry (16, (unsigned) exc16, 0x08, 0x8e);
        idt_set_entry (17, (unsigned) exc17, 0x08, 0x8e);
        idt_set_entry (18, (unsigned) exc18, 0x08, 0x8e);
        idt_set_entry (19, (unsigned) exc19, 0x08, 0x8e);
        idt_set_entry (20, (unsigned) exc20, 0x08, 0x8e);
        idt_set_entry (21, (unsigned) exc21, 0x08, 0x8e);
	idt_set_entry (22, (unsigned) exc22, 0x08, 0x8e);
        idt_set_entry (23, (unsigned) exc23, 0x08, 0x8e);
        idt_set_entry (24, (unsigned) exc24, 0x08, 0x8e);
        idt_set_entry (25, (unsigned) exc25, 0x08, 0x8e);
        idt_set_entry (26, (unsigned) exc26, 0x08, 0x8e);
        idt_set_entry (27, (unsigned) exc27, 0x08, 0x8e);
        idt_set_entry (28, (unsigned) exc28, 0x08, 0x8e);
        idt_set_entry (29, (unsigned) exc29, 0x08, 0x8e);
        idt_set_entry (30, (unsigned) exc30, 0x08, 0x8e);
        idt_set_entry (31, (unsigned) exc31, 0x08, 0x8e);

}

