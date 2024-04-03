/*
 * Void app_log if logging component not included
 * include header is included
 */

#ifndef LOG_H_
#define LOG_H_

#if defined(SL_CATALOG_APP_LOG_PRESENT)
#include "app_log.h"
#else
#define app_log (void)
#endif


#endif /* LOG_H_ */
