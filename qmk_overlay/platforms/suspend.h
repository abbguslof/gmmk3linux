#pragma once

#include <stdint.h>
#include <stdbool.h>

void suspend_power_down(void);
bool suspend_wakeup_condition(void);
void suspend_wakeup_init(void);

void suspend_wakeup_init_user(void);
void suspend_wakeup_init_kb(void);
void suspend_wakeup_init_quantum(void);
void suspend_power_down_user(void);
void suspend_power_down_kb(void);
void suspend_power_down_quantum(void);

bool suspend_wakeup_condition_user(void);
bool suspend_wakeup_condition_kb(void);

#ifndef USB_SUSPEND_WAKEUP_DELAY
#    define USB_SUSPEND_WAKEUP_DELAY 0
#endif
