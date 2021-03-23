#include "clock.h"

void updateClock_8MHz()
{
    MCG->C1 &= ~MCG_C1_CLKS_MASK;
    MCG->C1 |= MCG_C1_IREFS(1);
    MCG->C6 &= ~MCG_C6_PLLS_MASK;
    MCG->C4 &= ~MCG_C4_DRST_DRS_MASK;
    MCG->C4 |= MCG_C4_DMX32(1);
    SIM->CLKDIV1 |= SIM_CLKDIV1_OUTDIV1(2); // 8Mhz
}
