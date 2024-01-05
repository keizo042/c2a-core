#ifndef APP_REGISTRY_H_
#define APP_REGISTRY_H_
#include <src_user/settings/applications/timeline_command_dispatcher_define.h>

// こいつの自動生成がほしい．．．
typedef enum
{
  AR_NOP,
  AR_CSRV_GS_CMD_PH,
  AR_CSRV_GS_RT_TLM_PH,
  AR_CSRV_GS_RP_TLM_PH,
  AR_CSRV_AOBC,
  AR_CSRV_AOBC_CDIS,
  AR_CSRV_UART_TEST,
  AR_GSC_DISPATCHER,
  AR_RTC_DISPATCHER,
  AR_TLC_DISPATCHER_GS,
  AR_TLC_DISPATCHER_BC,
  AR_TLC_DISPATCHER_TLM,
#ifdef TLCD_ENABLE_MISSION_TL
  AR_TLC_DISPATCHER_MIS,
#endif
  AR_EVENT_UTILITY,
  AR_MEM_DUMP,
  AR_CCP_DUMP,
  AR_TL_BCT_DIGEST,
  AR_TELEMETRY_MANAGER,
  AR_DIVIDED_CMD_UTILITY,
  AR_UTILITY_CMD,
  AR_UTILITY_COUNTER,
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
