#include "../h/system.h"

char attrib = 0x7;
int tx = 0, ty = 0;
char baractive = 0;

void scroll (int cnt) {
	
	if ((cnt == -1 && ty < 24) || baractive) return;
	int kol = ty - 23;
	
	int rety = 23;
	if (cnt > 0)  { kol = min (cnt, ty + 1); rety = (ty - kol); }
	else  { rety = 23; }

	while (kol--) {
		
		unsigned char* dest = (unsigned char *) 0xb8000;
		const unsigned char* src = (const unsigned char *) 0xb8000;
		int i = 78;
		while (i--) {
		
			src += 80 * 2;
			memcpy (dest, src, 160);
			dest += 80 * 2;
			
		}
	
	}
	
	ty = rety;
	move_csr ();
	return;

}

void move_csr (void) {
	
	int loc = ty * 80 + tx;
	oport (0x3d4, 14);
	oport (0x3d5, loc >> 8);
	oport (0x3d4, 15);
	oport (0x3d5, loc);

}

void cls (void) {
	
	unsigned short* dest = (unsigned short *) 0xb8000;
	for (int i = 0 ; i < 24 ; ++i) {
	
		memsetw (dest, (unsigned short) ' ' | (attrib << 8), 80);
		dest += 80;

	}

	tx = ty = 0;
	move_csr ();

	return;

}

void set_vga (int nx, int ny, char atr) {
	
	if (nx != -1) tx = nx;
	if (ny != -1) ty = ny;
	if (atr != -1) attrib = atr;
	move_csr ();
	
	return;

}

void putc (char c, char atr) {
	
	if (ty >= 24) scroll (-1);
	if (c == '\n') { ++ty; move_csr (); scroll (-1);  return; }
	if (c == '\t') { tx += 6; tx %= 80; if (!tx) ++ty; move_csr (); return; }
	if (c == '\r') { tx = 0; move_csr (); return; }
	if (c == 0x8) { if (tx > 0) --tx; move_csr (); return; }
	
	char *loc = (char *) 0xb8000;
	loc += (ty * 80 + tx) * 2;
	*loc++ = c;
	*loc = atr;
	++tx; tx %= 80;
	if (!tx) ++ty;
	scroll (-1);
	move_csr ();
	return;
	
}

void puts (char* str) {
	
	for (int i = 0 ; i < strlen (str) ; ++i) { putc (str [i], attrib); }
	return;

}

void putsa (char* str, char atr) {

	for (int i = 0 ; i < strlen (str) ; ) putc (str [i++], atr);
	return;

}

void putsbar (char *str, int nx) {
	
	baractive = 1;
	int ox = tx, oy = ty;
	int posx = 0;
	if (nx > 0) posx = nx;
	set_vga (posx, 24, -1);
	for (int i = 0 ; i < 80 ; ++i) { putc (' ', (6 << 4) | 15);  } tx = posx; ty = 24;
	
	int prijeatr = attrib;
	int sadatr =  (6 << 4) | 15;
	attrib = sadatr;
	for (int i = 0 ; i < strlen (str) ; i++ ) {
		
		if (str [i] == '\n') continue;
		putc (str [i], attrib);
		
		}
	
	tx = ox; ty = oy;
	attrib = prijeatr;
	move_csr ();
	baractive = 0;
	return;

}

void screen_setup () {

	set_vga (0, 0, 12);
	baractive = 0;
	cls ();
	puts ("\n\n\r\
\t\t\t\t	    8\n\r\
\t\t\t\t         888\n\r\
\t\t\t\t       8888\n\r\
\t\t\t\t      88888\n\r\
\t\t\t\t     888888\n\r\
\t\t\t\t     888888\n\r\
\t\t\t\t     888888\n\r\
\t\t\t\t      8888888\n\r\
\t\t\t\t          8\n\r\
\t\t\t\t8888888888888888888\n\r\
\t\t\t\t  8888888888888888\n\r\
\n\r\
	");
	puts ("\t\t/====================================\\\n\r");
	puts ("\t\t\t\t\t  welcome!\n\n\r");
	puts ("\t\t\t\t  distoro.os@gmail.com \n\r");
	puts ("\t\t\t\t\t\t  - Mario Novak\n\r");
	puts ("\t\t\t\\====================================/\n\r");
	putsbar ("\t\t\t\tdistoro operating system", -1);
	return;

}

void puti (int num) {
	
	int cnt = 0;
	char zn [32] = {'0'};
	if (!num) cnt = 1;
	while (num) {
		
		zn [cnt++] = (num % 10) + 48;
		num /= 10;
		
	}
	
	while (cnt--) putc (zn [cnt], attrib);
	
	return;

}

void putclock () {
	
	extern int uptime_h, uptime_m, uptime_s;
	baractive = 1;
	int ox = tx, oy = ty;
	int posx = 72;
	set_vga (posx, 24, -1);
	
	int prijeatr = attrib;
	attrib = (6 << 4) | 15;
	for (int i = 0 ; i < 8 ; ++i) { putc (' ', (6 << 4) | 15);  } tx = posx; ty = 24;
	
	puti (uptime_h); puts (":"); puti (uptime_m); puts (":"); puti (uptime_s);
	
	tx = ox; ty = oy;
	attrib = prijeatr;
	move_csr ();
	baractive = 0;
	return;

}
