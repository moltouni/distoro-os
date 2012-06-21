#ifndef __SYSTEM_H
#define __SYSTEM_H

extern unsigned char *memcpy (unsigned char *dest, const unsigned char *src, int count);
extern unsigned char *memset (unsigned char *dest, unsigned char val, int count);
extern unsigned short *memsetw (unsigned short *dest, unsigned short val, int count);
extern int strlen (const char *str);
extern unsigned char iport (unsigned short _port);
extern void oport (unsigned short _port, unsigned char _data);
struct regs { unsigned int gs, fs, es, ds; unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax; unsigned int int_no, err_code; unsigned int eip, cs, eflags, useresp, ss; };
extern int min (const int, const int);
extern int max (const int, const int);
extern void scroll ();
extern void move_csr ();
extern void cls ();
extern void putc (char, char);
extern void puts (char *);
extern void putsa (char *, char);
extern void set_vga (int, int, char);
extern void putsbar (char *, int);
extern void screen_setup ();
extern void puti (int);
extern void putclock ();
extern void idt_set_entry (unsigned char, unsigned long, unsigned short, unsigned char);
extern void idt_install ();
extern void isr_manager (struct regs *);
extern void exc_install ();
extern void irq_install ();
extern void irq_add_func (int, void (*handler) (struct regs *r));
extern void irq_del_func (int);
extern void irq_handler (struct regs *);
extern void configure_timer ();
extern void isr_timer ();
extern void configure_kb ();
extern void isr_kb ();
void sleep (int);

#endif
