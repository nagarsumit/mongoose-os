/*
 * Copyright (c) 2014-2017 Cesanta Software Limited
 * All rights reserved
 */

#ifndef CS_FW_INCLUDE_MGOS_DEBUG_H_
#define CS_FW_INCLUDE_MGOS_DEBUG_H_

#include <stdbool.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef MGOS_DEBUG_UART_BAUD_RATE
#define MGOS_DEBUG_UART_BAUD_RATE 115200
#endif

#define MGOS_DEBUG_TMP_BUF_SIZE 256

/*
 * Arguments for the `MGOS_HOOK_DEBUG_WRITE` hook, see `mgos_hook_register()`.
 */
struct mgos_debug_hook_arg {
  int fd;
  const void *data;
  size_t len;

  /*
   * Buffer which hooks can use for their own needs; size of the buffer is
   * MGOS_DEBUG_TMP_BUF_SIZE.
   */
  char *buf;
};

/*
 * Write debug info `buf`, `len` to the given file descriptor `fd`.
 */
void mgos_debug_write(int fd, const void *buf, size_t len);

/*
 * Flush debug UARTs, both stdout and stderr.
 */
void mgos_debug_flush(void);

/* Set UART for stdout. Negative value disables stdout. */
enum mgos_init_result mgos_set_stdout_uart(int uart_no);

/* Set UART for stderr. Negative value disables stderr. */
enum mgos_init_result mgos_set_stderr_uart(int uart_no);

/* Get stdout UART number; -1 indicates that stdout is disabled. */
int mgos_get_stdout_uart(void);
/* Get stderr UART number; -1 indicates that stderr is disabled. */
int mgos_get_stderr_uart(void);

/*
 * Suspend UART output (both stdout and stderr); see
 * `mgos_debug_resume_uart()`. Nested suspension is supported: UART needs to be
 * resumed as many times as it was suspended.
 */
void mgos_debug_suspend_uart(void);

/*
 * Resume previously suspended UART output, see `mgos_debug_suspend_uart()`.
 */
void mgos_debug_resume_uart(void);

/*
 * Returns whether UART output is suspended at the moment.
 */
bool mgos_debug_uart_is_suspended(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CS_FW_INCLUDE_MGOS_DEBUG_H_ */