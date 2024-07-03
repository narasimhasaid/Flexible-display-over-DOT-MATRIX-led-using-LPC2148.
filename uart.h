#include "types.h"

void initUART(u32 rate);
u8 rxUART(void);
void txUART(u8 data); // Give char you want to send
void strUART(u8 *ptr); // Give string / char array you want to send

