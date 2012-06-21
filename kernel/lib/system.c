unsigned char *memcpy (unsigned char *dest, const unsigned char *src, int count) {

	unsigned char *ret = (unsigned char *) dest;
	while (count--) {*dest++ = *src++; }
	return ret;

}

unsigned char *memset (unsigned char *dest, unsigned char val, int count) {

	unsigned char *ret = (unsigned char *) dest;
	while (count--) { *dest++ = val; }
	return ret;

}

unsigned short *memsetw (unsigned short *dest, unsigned short val, int count) {

	unsigned short *ret = (unsigned short *) dest;
	while (count--) *dest++ = val;
	return ret;

}

int strlen (const char *str) {

	int kol = 0;
	while (*str) { ++kol; ++str; }
	return kol;

}

unsigned char iport (unsigned short _port) {
	
	for (int i = 0 ; i < 500 ; ++i);
	unsigned char rv;
	__asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
	return rv;

}
void oport (unsigned short _port, unsigned char _data) {
	
	for (int i = 0 ; i < 500 ; ++i);
	__asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));

}
