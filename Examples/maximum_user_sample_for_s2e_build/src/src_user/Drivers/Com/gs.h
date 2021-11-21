/**
 * @file gs.h
 * @brief Ground Station との通信用の Driver
 */
#ifndef GS_H_
#define GS_H_

#include <src_core/CmdTlm/packet_handler.h>
#include <src_core/Drivers/Super/driver_super.h>
#include <src_core/IfWrapper/uart.h>
#include <src_core/IfWrapper/ccsds.h>
#include "../../IfWrapper/ccsds_user.h"
#include "../../CmdTlm/Ccsds/vcdu.h"
#include "gs_validate.h"

/**
 * @enum GS_TCF_TYPE_ENUM
 * @note rx_header_ <-> stream で 各 CMD との対応の振り分けを行っている. その Index と対応させるため.
 * @note uint8_t を想定
 */
typedef enum
{
  GS_TCF_TYPE_ENUM_AD_CMD,
  GS_TCF_TYPE_ENUM_BC_CMD,
  GS_TCF_TYPE_ENUM_BD_CMD,
  GS_TCF_TYPE_ENUM_UNKNOWN
} GS_TCF_TYPE_ENUM;

/**
 * @enum  GS_PORT_TYPE
 * @brief GS の通信ポートは CCSDS と UART の 2 つある
 * @note  uint8_t を想定
 */
typedef enum
{
  GS_PORT_TYPE_CCSDS, //!< CCSDS
  GS_PORT_TYPE_UART,  //!< UART
  GS_PORT_TYPE_NUM    //!< port 数
} GS_PORT_TYPE;

/**
 * @struct GS_Info
 * @brief  ドライバーの各状態の記録
 */
typedef struct
{
  DS_ERR_CODE rec_status;                   //!< DriverSuper からの受信結果
  GS_TCF_TYPE_ENUM last_rec_tcf_type;       //!< 最後に受信した tcf のタイプ
  DS_ERR_CODE ad_rec_status;                //!< AD CMD を受信したときの analyze 結果
  DS_ERR_CODE bc_rec_status;                //!< BC CMD を受信したときの analyze 結果
  DS_ERR_CODE bd_rec_status;                //!< BD CMD を受信したときの analyze 結果
  GS_VALIDATE_ERR tc_frame_validate_status; //!< TC Frame の検証結果
  int ret_from_if_rx;                       //!< UART or CCSDS からの返り値
  cycle_t last_rec_time;                    //!< 最後に受信した時刻
  PH_ACK cmd_ack;                           //!< 受信した CMD の実行結果

  cycle_t send_cycle;                       //!< 最後に送信したときの時刻
  VCDU_VCID vcid;                           //!< 送信した TLM のタイプ
  uint32_t vcdu_counter;                    //!< VCDU counter
} GS_Info;

/**
 * @struct GS_Driver
 * @brief  GroundStation Driver
 */
typedef struct
{
  // CCSDS 側の Driver
  struct
  {
    DriverSuper  super;
    CCSDS_Config ccsds_config;
  } driver_ccsds;

  // UART 側の Driver
  struct
  {
    DriverSuper super;
    UART_Config uart_config;
  } driver_uart;

  GS_Info info[GS_PORT_TYPE_NUM]; //!< CCSDS 用と UART 用 2 つ
  const GS_Info* latest_info;
  CCSDS_Info ccsds_info;
  GS_PORT_TYPE tlm_tx_port_type;
  uint8_t is_ccsds_tx_valid;      //!< CCSDS TX が有効になっているか (地上試験で突然電波を出すと危険なので)
} GS_Driver;

/**
 * @brief Driver の初期化
 * @param[in] uart_ch: 有線通信時の CH
 * @return int: 0
 */
int GS_init(GS_Driver* gs_driver, uint8_t uart_ch);

/**
 * @brief 地上から CMD を受信する. 形式は TCFrame
 * @param[in] gs_driver: ドライバー
 * @return int: 0
 */
int GS_rec_tcf(GS_Driver* gs_driver);

/**
 * @brief 地上に向けて TLM を送信. 形式は VCDU
 * @note  DS_send_general_cmd が使われているが, これは DS は MOBC コンポ間を想定しているため, MOBC から見るとコンポに cmd を送信している様に見える, が 今回は MOBC から地上に TLM を送信している
 * @note TLM 送信, 形式は VCDU
 * @param[in] gs_driver: ドライバー
 * @param[in] vcdu: 送信する VCDU. 場合によってはそのまま DS に渡すので， local変数ではなくstaticな変数を渡すこと
 * @return DS_CMD_ERR_CODE: 送信結果
 */
DS_CMD_ERR_CODE GS_send_vcdu(GS_Driver* gs_driver, const VCDU* vcdu);

#endif
