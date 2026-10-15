#ifndef WRAPPER_H
#define WRAPPER_H

#ifdef _MSC_VER
#include "wrapper_win.h"
#elif defined(__PPU__) || defined(__PS3__) || defined(__CELLOS_LV2__) || defined(UCRAFT_PS3)
#include "wrapper_ps3.h"
#elif CUSTOM_WRAPPER
#include "wrapper_custom.h"
#elif __PS3__
#include "wrapper_ps3.h"
#else
#include "wrapper_unix.h"
#endif
#ifdef UCRAFT_TEST_HOOKS
#include "test_hooks.h"
#endif
#endif
