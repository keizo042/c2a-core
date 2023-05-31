#ifndef APP_REGISTRY_H_
#define APP_REGISTRY_H_
#include <src_user/Settings/Applications/timeline_command_dispatcher_define.h>

// こいつの自動生成がほしい．．．
typedef enum
{
  AR_NOP,
  AR_DI_MOBC_CMD_PH,
  AR_DI_MOBC_RT_TLM_PH,
  AR_GSC_DISPATCHER,
  AR_RTC_DISPATCHER,
  AR_TLC_DISPATCHER_GS,
  AR_TLC_DISPATCHER_BC,
  AR_TLC_DISPATCHER_TLM,
#ifdef TLCD_ENABLE_MISSION_TL
  AR_TLC_DISPATCHER_MIS,
#endif
  AR_EVENT_UTILITY,
  AR_APP_DBG_FLUSH_SCREEN,
  AR_APP_DBG_PRINT_TIMESTAMP,
  AR_APP_DBG_PRINT_CMD_STATUS,
  AR_APP_DBG_PRINT_EVENT_LOGGER0,
  AR_APP_DBG_PRINT_EVENT_LOGGER1,
  AR_APP_DBG_PRINT_EVENT_HANDLER,
  AR_APP_DBG_PRINT_GIT_REV
} AR_APP_ID;

void AR_load_initial_settings(void);

#endif // APP_REGISTRY_H_
