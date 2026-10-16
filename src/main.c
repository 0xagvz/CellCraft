
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

#if defined(__PPU__) || defined(__PS3__) || defined(__CELLOS_LV2__) || defined(UCRAFT_PS3)
#include <sysutil/sysutil.h>
#else
#include <signal.h>
#endif

#include "UCraft.h"
static uint8_t cleanup_flag;

#if defined(__PPU__) || defined(__PS3__) || defined(__CELLOS_LV2__) || defined(UCRAFT_PS3)
static void cleanup_callback(u64 status, u64 param, void *userdata)
{
  (void)param;
  (void)userdata;
  if (status == SYSUTIL_EXIT_GAME)
  {
    // clean up flag
    cleanup_flag = 1;
  }
}
#else
void cleanup(int signal_number)
{
  (void)signal_number;
  // clean up flag
  cleanup_flag = 1;
}
#endif
int main(int argc, char const *argv[])
{
  (void)argc;
  (void)argv;
#if defined(__PPU__) || defined(__PS3__) || defined(__CELLOS_LV2__) || defined(UCRAFT_PS3)
  sysUtilRegisterCallback(SYSUTIL_EVENT_SLOT0, cleanup_callback, NULL);
  int rc = UCraftStart(&cleanup_flag);
  sysUtilUnregisterCallback(SYSUTIL_EVENT_SLOT0);
  return rc;
#else
  signal(SIGINT, cleanup);
  return UCraftStart(&cleanup_flag);
#endif
}
