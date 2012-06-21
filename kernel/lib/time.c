#include "../h/system.h"

extern int uptime_s;

void sleep (int num) {

	int cekaj  = uptime_s + num;
	while (uptime_s < cekaj);
	return;

}
