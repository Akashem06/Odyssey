#ifndef ODYSSEY_STATUS_HPP
#define ODYSSEY_STATUS_HPP

typedef enum {
  ODYSSEY_OK = 0,
  ODYSSEY_UNKNOWN,
  ODYSSEY_INVALID_ARGS,
  ODYSSEY_RESOURCE_EXHAUSTED,
  ODYSSEY_UNREACHABLE,
  ODYSSEY_TIMEOUT,
  ODYSSEY_EMPTY,
  ODYSSEY_OUT_OF_RANGE,
  ODYSSEY_UNIMPLEMENTED,
  ODYSSEY_UNINITIALIZED,
  ODYSSEY_INTERNAL_ERROR,
  ODYSSEY_INCOMPLETE,
  ODYSSEY_NUM_STATUS_CODES,
} OdysseyStatus;

// Use to forward failures or continue on success.
#define status_ok_or_return(code)          \
  ({                                       \
    __typeof__(code) status_expr = (code); \
    if (status_expr) return status_expr;   \
  })

#endif