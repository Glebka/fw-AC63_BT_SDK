#ifndef APP_CONFIG_H
#define APP_CONFIG_H

/*
 * 系统打印总开关
 */


#ifdef CONFIG_RELEASE_ENABLE
#define LIB_DEBUG    0
#else
#define LIB_DEBUG    1
#endif

#define CONFIG_DEBUG_LIB(x)         (x & LIB_DEBUG)

#define CONFIG_DEBUG_ENABLE

#define TCFG_MEDIA_LIB_USE_MALLOC		    1
// Apps example selection. Only one option can be selected, and the corresponding board_config.h must be configured.
#define CONFIG_APP_SPP_LE                 0 //SPP + LE or LE's client
#define CONFIG_APP_FTMS                   0 //FTMS
#define CONFIG_APP_FINDMY                 1 //FINDMY
#define CONFIG_APP_MULTI                  0 // BLE multi-connection + SPP
#define CONFIG_APP_DONGLE                 0 // USB + Bluetooth (BLE host), PC HID device
#define CONFIG_APP_CENTRAL                0 // BLE client, central device
#define CONFIG_APP_LL_SYNC                0 // Tencent Lianlian
#define CONFIG_APP_BEACON                 0 // Bluetooth BLE iBeacon
#define CONFIG_APP_NONCONN_24G            0 // 2.4G non-connected transceiver
#define CONFIG_APP_TUYA                   0 // Tuya Protocol
#define CONFIG_APP_AT_COM                 0 // AT com HEX format command
#define CONFIG_APP_AT_CHAR_COM            0 // AT com string format command
#define CONFIG_APP_IDLE                   0 // Idle task
#define CONFIG_APP_CONN_24G               0 // BLE-based 2.4G, board-level only requires BLE enabled
#define CONFIG_APP_HILINK                 0 // Huawei Protocol
#define CONFIG_APP_ELECTROCAR             0 // Electric vehicle project; note to disable board-level ADKEY and other IO occupations, disable low power: set TCFG_LOWPOWER_LOWPOWER_SEL to 0
// #define LL_SYNC_EN                        CONFIG_APP_LL_SYNC //
// #define TUYA_DEMO_EN                      CONFIG_APP_TUYA

//edr sniff config
#define SNIFF_MODE_RESET_ANCHOR           0
//V5.0 Extended Advertising/Scanning Enable
#define CONFIG_BT_EXT_ADV_MODE            0

#define CONFIG_SET_1M_PHY                 1 //for iot
#define CONFIG_SET_2M_PHY                 2
#define CONFIG_SET_CODED_S2_PHY           3
#define CONFIG_SET_CODED_S8_PHY           4
#define CONFIG_BLE_PHY_SET                CONFIG_SET_1M_PHY //default

// When BLE acts as a master, enable support for searching and connecting to JL test box
#define SUPPORT_TEST_BOX_BLE_MASTER_TEST_EN	   0

#if CONFIG_APP_SPP_LE
// Configure dual-mode with the same name and same address
#define DOUBLE_BT_SAME_NAME                0 // Same name
#define DOUBLE_BT_SAME_MAC                 0 // Same MAC
#define CONFIG_APP_SPP_LE_TO_IDLE          0 // SPP_AND_LE to idle use
#define CONFIG_BLE_HIGH_SPEED              0 // BLE high speed mode: enable DLE+2M, payload must match PDU packet length

// Bluetooth BLE configuration
#define CONFIG_BT_GATT_COMMON_ENABLE       1 // Configure use of the common GATT module
#define CONFIG_BT_SM_SUPPORT_ENABLE        0 // Configure whether encryption is supported
#define CONFIG_BT_GATT_CLIENT_NUM          0 // Configure the number of client connections (supports enabling 1 for search profile)
#define CONFIG_BT_GATT_SERVER_NUM          1 // Configure the number of server connections
#define CONFIG_BT_GATT_CONNECTION_NUM      (CONFIG_BT_GATT_SERVER_NUM + CONFIG_BT_GATT_CLIENT_NUM) // Configure the total number of connections

// BLE peripheral extended search for counterpart services; requires GATT CLIENT enabled
#if CONFIG_BT_GATT_CLIENT_NUM
#define TRANS_CLIENT_SEARCH_PROFILE_ENABLE  1 /* Configure module to search for specified services */

#if !TRANS_CLIENT_SEARCH_PROFILE_ENABLE && CONFIG_BT_SM_SUPPORT_ENABLE /* Custom search for ANCS & AMS services */
#define TRANS_ANCS_EN                       1 /* Configure to search for the host's ANCS service, pairing required */
#define TRANS_AMS_EN                        0 /* Configure to search for the host's AMS service, pairing required */
#endif
#endif //#if CONFIG_BT_GATT_CLIENT_NUM

#elif CONFIG_APP_DONGLE
/* Default: search for devices by matching names before initiating connection (inquiry + page) */
#define EDR_EMITTER_EN                     0 // Bluetooth (EDR host)

#if EDR_EMITTER_EN
/* Do not perform search matching + connection; just enable connectable mode and wait for the other side to connect */
#define EDR_EMITTER_PAGESCAN_ONLY          0 /* */
#endif

#define CONFIG_BT_GATT_COMMON_ENABLE       1
#define CONFIG_BT_SM_SUPPORT_ENABLE        1 // Configure whether to support encryption
#define CONFIG_BT_GATT_CLIENT_NUM          1 // Set number of hosts: 1~2 (number of Bluetooth BLE devices the dongle can connect; if =2, one extra USB device will be registered)
#define CONFIG_BT_COMPOSITE_EQUIPMENT      0
#define CONFIG_BT_GATT_SERVER_NUM          0 /* */
#define CONFIG_BT_GATT_CONNECTION_NUM      (CONFIG_BT_GATT_SERVER_NUM + CONFIG_BT_GATT_CLIENT_NUM) /* */
#define CONFIG_BLE_HIGH_SPEED              0 // BLE high-speed mode: enable DLE+2M, payload must match PDU packet length

#elif CONFIG_APP_CENTRAL
#define CONFIG_BT_GATT_COMMON_ENABLE       1
#define CONFIG_BT_SM_SUPPORT_ENABLE        0 // Configure whether to support encryption
#define CONFIG_BT_GATT_CLIENT_NUM          1 /* */
#define CONFIG_BT_GATT_SERVER_NUM          0 /* (If enabled, on the master link, provides a service for the other side to search and operate, without creating a new connection) */
#define CONFIG_BT_GATT_CONNECTION_NUM      (CONFIG_BT_GATT_SERVER_NUM + CONFIG_BT_GATT_CLIENT_NUM) /* */
#define CONFIG_BLE_HIGH_SPEED              0 // BLE high-speed mode: enable DLE+2M, payload must match PDU packet length

#elif CONFIG_APP_MULTI
#define CONFIG_BT_GATT_COMMON_ENABLE       1
#define CONFIG_BT_SM_SUPPORT_ENABLE        0
#define CONFIG_BT_GATT_CLIENT_NUM          1 //range(0~7)
#define CONFIG_BT_GATT_SERVER_NUM          0 //range(0~1)
#define CONFIG_BT_GATT_CONNECTION_NUM      (CONFIG_BT_GATT_SERVER_NUM + CONFIG_BT_GATT_CLIENT_NUM) // range (0~8)
#define CONFIG_BLE_HIGH_SPEED              0 // BLE high-speed mode: enable DLE+2M, payload must match PDU packet length

#elif CONFIG_APP_AT_COM
// Select AT: choose either master or slave
#define TRANS_AT_COM                       1 // Serial control for Bluetooth dual-mode transparent transmission
#define TRANS_AT_CLIENT                    0 // Serial control for Bluetooth BLE master transparent transmission

#define CONFIG_BT_GATT_COMMON_ENABLE       0 // (apps not supported, application does not support)
#define CONFIG_BT_SM_SUPPORT_ENABLE        0 // (apps not supported, application does not support)
#define CONFIG_BT_GATT_CLIENT_NUM          1 // max is 1
#define CONFIG_BT_GATT_SERVER_NUM          1 // max is 1
#define CONFIG_BT_GATT_CONNECTION_NUM      (CONFIG_BT_GATT_SERVER_NUM + CONFIG_BT_GATT_CLIENT_NUM)

#elif CONFIG_APP_AT_CHAR_COM
#define CONFIG_BT_GATT_COMMON_ENABLE       0 // (apps not supported, application does not support)
#define CONFIG_BT_SM_SUPPORT_ENABLE        0 // (apps not supported, application does not support)
#define CONFIG_BT_GATT_CLIENT_NUM          1 // max is 1
#define CONFIG_BT_GATT_SERVER_NUM          1 // max is 1
#define CONFIG_BT_GATT_CONNECTION_NUM      (CONFIG_BT_GATT_SERVER_NUM + CONFIG_BT_GATT_CLIENT_NUM)

#elif CONFIG_APP_TUYA
// Configure dual-mode with the same name and same address
#define DOUBLE_BT_SAME_NAME                0 // same name

// Bluetooth configuration
#define CONFIG_BT_GATT_COMMON_ENABLE       1 // Use the GATT common module
#define CONFIG_BT_SM_SUPPORT_ENABLE        0 // Configure whether encryption is supported
#define CONFIG_BT_GATT_CLIENT_NUM          0 // Configure number of master clients (apps do not support)
#define CONFIG_BT_GATT_SERVER_NUM          1 // Configure number of slave servers, max is 1
#define CONFIG_BT_GATT_CONNECTION_NUM      (CONFIG_BT_GATT_SERVER_NUM + CONFIG_BT_GATT_CLIENT_NUM) // Configure number of connections

#elif CONFIG_APP_LL_SYNC
// Configure dual-mode with the same name and same address
#define DOUBLE_BT_SAME_NAME                0 // same name

// Bluetooth configuration
#define CONFIG_BT_GATT_COMMON_ENABLE       1 // Use common GATT module
#define CONFIG_BT_SM_SUPPORT_ENABLE        0 // Enable encryption support
#define CONFIG_BT_GATT_CLIENT_NUM          0 // Number of host client connections (app does not support enabling)
#define CONFIG_BT_GATT_SERVER_NUM          1 // Number of slave server connections (max is 1)
#define CONFIG_BT_GATT_CONNECTION_NUM      (CONFIG_BT_GATT_SERVER_NUM + CONFIG_BT_GATT_CLIENT_NUM) // Total number of connections

#elif CONFIG_APP_CONN_24G

#define CONFIG_BT_GATT_COMMON_ENABLE       1 // Use common GATT module
#define CONFIG_BT_SM_SUPPORT_ENABLE        0 // (Not supported by the app)
#define CONFIG_BT_GATT_CLIENT_NUM          0 // Enable host client connections (max is 1)
#define CONFIG_BT_GATT_SERVER_NUM          1 // Enable slave server connections (max is 1)
// 2.4G mode: 0---BLE, non-0---2.4G pairing code; !!! For master-slave connection, pairing codes must match
// !!! After initialization, pairing code can be modified via API rf_set_conn_24g_coded when not connected
#define CFG_RF_24G_CODE_ID_SCAN            (0x5555AAAA) // <=24bits, pairing code for host scanning in 2.4G mode
#define CFG_RF_24G_CODE_ID_ADV             (0x5555AAAA) // <=24bits, pairing code for slave advertising in 2.4G mode
#define CONFIG_BT_GATT_CONNECTION_NUM      (CONFIG_BT_GATT_SERVER_NUM + CONFIG_BT_GATT_CLIENT_NUM)
#define CONFIG_BLE_HIGH_SPEED              0 // BLE high-speed mode: enable DLE+2M, payload must match PDU packet length
#undef  CONFIG_BLE_PHY_SET
#define CONFIG_BLE_PHY_SET                 4 // PHY selection: 1--1M, 2--2M, 3--CODED_S2, 4--CODED_S8
#if CONFIG_BLE_HIGH_SPEED
#undef CONFIG_BLE_PHY_SET
#define CONFIG_BLE_PHY_SET                 2 // Set 2M PHY for protection
#endif

#elif CONFIG_APP_HILINK
// Configure dual-mode with the same name and same address
#define DOUBLE_BT_SAME_NAME                1 // same name
#define DOUBLE_BT_SAME_MAC                 0 // same address

// Bluetooth configuration
#define CONFIG_BT_GATT_COMMON_ENABLE       1 // Use common GATT module
#define CONFIG_BT_SM_SUPPORT_ENABLE        1 // Enable encryption support
#define CONFIG_BT_GATT_CLIENT_NUM          0 // Number of host client connections (app does not support enabling)
#define CONFIG_BT_GATT_SERVER_NUM          1 // Number of slave server connections (max is 1)
#define CONFIG_BT_GATT_CONNECTION_NUM      (CONFIG_BT_GATT_SERVER_NUM + CONFIG_BT_GATT_CLIENT_NUM)

#elif CONFIG_APP_FINDMY
#define CONFIG_BLE_HIGH_SPEED              1 // BLE high-speed mode: enable DLE+2M, payload must match PDU packet length

// Bluetooth BLE configuration
#define CONFIG_BT_GATT_COMMON_ENABLE       1 // Use common GATT module
#define CONFIG_BT_SM_SUPPORT_ENABLE        1 // Enable encryption support
#define CONFIG_BT_GATT_CLIENT_NUM          0 // Number of host client connections (app does not support enabling)
#define CONFIG_BT_GATT_SERVER_NUM          2 // Number of slave server connections
#define CONFIG_BT_GATT_CONNECTION_NUM      (CONFIG_BT_GATT_SERVER_NUM + CONFIG_BT_GATT_CLIENT_NUM) // Total number of connections

// Debug: output sensor data to UART
#define FMY_DEBUG_SENSOR_TO_UART_ENBALE    0
// Debug: test sensor movement detection
#define FMY_DEBUG_TEST_MOTION_DETETION     0
// Authentication test mode
#define FMY_FMCA_TEST_MODE                 0
// Support pair status: enter or exit test box connection mode via button
#define FMY_SUPPORT_TEST_BOX_MODE          0

#elif CONFIG_APP_FTMS

// Configure dual-mode with the same name and same address
#define DOUBLE_BT_SAME_NAME                0 // same name
#define DOUBLE_BT_SAME_MAC                 0 // same address
#define CONFIG_APP_SPP_LE_TO_IDLE          0 // SPP_AND_LE to idle use
#define CONFIG_BLE_HIGH_SPEED              0 // BLE high-speed mode: enable DLE+2M, payload must match PDU packet length

// Bluetooth BLE configuration
#define CONFIG_BT_GATT_COMMON_ENABLE       1 // Use common GATT module
#define CONFIG_BT_SM_SUPPORT_ENABLE        0 // Enable encryption support
#define CONFIG_BT_GATT_CLIENT_NUM          0 // Number of host client connections (support enabling 1 for search profile)
#define CONFIG_BT_GATT_SERVER_NUM          1 // Number of slave server connections
#define CONFIG_BT_GATT_CONNECTION_NUM      (CONFIG_BT_GATT_SERVER_NUM + CONFIG_BT_GATT_CLIENT_NUM) // Total number of connections

#else
#define CONFIG_BT_GATT_COMMON_ENABLE       0
#define CONFIG_BT_SM_SUPPORT_ENABLE        0
#define CONFIG_BT_GATT_CLIENT_NUM          0
#define CONFIG_BT_GATT_SERVER_NUM          0
#define CONFIG_BT_GATT_CONNECTION_NUM      0

#endif

#if CONFIG_APP_ELECTROCAR
// Currently, only bd19 (AC632N) supports 433/nrf/One-Key operations
//                                          433 Configuration                                 //
#define TCFG_433_ENABLE                     DISABLE_THIS_MOUDLE
#define TCFG_433_PORT                       IO_PORTB_00
#define TCFG_433_IO_TEST                    ENABLE_THIS_MOUDLE // Capture 433 input data via IO
//                                          nrf Configuration                                 //
#define TCFG_NFC_ENABLE                     DISABLE_THIS_MOUDLE
#define TCFG_NFC_PORT                       IO_PORTB_01
#define TCFG_NFC_IO_TEST                    ENABLE_THIS_MOUDLE // Capture 433 input data via IO
//                                          One-Key Configuration                              //
#define TCFG_ONE_PARSE_ENABLE               DISABLE_THIS_MOUDLE
#define TCFG_ONE_PARSE_PORT                 IO_PORTB_03
#define TCFG_ONE_PARSE_IO_TEST              ENABLE_THIS_MOUDLE // Capture 433 input data via IO

// Bluetooth BLE configuration
#define CONFIG_BT_GATT_COMMON_ENABLE       1 // Use the common GATT module
#define CONFIG_BT_SM_SUPPORT_ENABLE        0 // Configure whether encryption is supported
#define CONFIG_BT_GATT_CLIENT_NUM          0 // Configure number of host client connections (app not supported)
#define CONFIG_BT_GATT_SERVER_NUM          1 // Configure number of slave server connections
#define CONFIG_BT_GATT_CONNECTION_NUM      (CONFIG_BT_GATT_SERVER_NUM + CONFIG_BT_GATT_CLIENT_NUM) // Configure total number of connections

#endif

#if CONFIG_BT_GATT_CONNECTION_NUM > 8
#error "SUPPORT MAX IS 8 !!!"
#endif


#include "board_config.h"

#include "usb_common_def.h"

#include "btcontroller_mode.h"

#include "user_cfg_id.h"

#define APP_PRIVATE_PROFILE_CFG

#if CONFIG_BT_EXT_ADV_MODE
#define APP_TO_ALLOW_EXT_ADV
//unsupport sleep
#undef  TCFG_LOWPOWER_LOWPOWER_SEL
#define TCFG_LOWPOWER_LOWPOWER_SEL                0
#endif

#if (CONFIG_BT_MODE == BT_NORMAL)
//enable dut mode,need disable sleep(TCFG_LOWPOWER_LOWPOWER_SEL = 0)
#define TCFG_NORMAL_SET_DUT_MODE                  0
#if TCFG_NORMAL_SET_DUT_MODE
//unsupport sleep
#undef  TCFG_LOWPOWER_LOWPOWER_SEL
#define TCFG_LOWPOWER_LOWPOWER_SEL                0

#if TCFG_USER_EDR_ENABLE && TCFG_USER_BLE_ENABLE
// Simultaneous activation is not supported
#error "dut need disable one bt!!!"
#endif

#endif //#if TCFG_NORMAL_SET_DUT_MODE

#else

#undef  TCFG_BD_NUM
#define TCFG_BD_NUM						          1

#undef  TCFG_USER_TWS_ENABLE
#define TCFG_USER_TWS_ENABLE                      0     // Enable TWS functionality

#undef  TCFG_USER_BLE_ENABLE
#define TCFG_USER_BLE_ENABLE                      1     // Enable BLE functionality

#undef  TCFG_AUTO_SHUT_DOWN_TIME
#define TCFG_AUTO_SHUT_DOWN_TIME		          0

#undef  TCFG_SYS_LVD_EN
#define TCFG_SYS_LVD_EN						      0

#undef  TCFG_LOWPOWER_LOWPOWER_SEL
#define TCFG_LOWPOWER_LOWPOWER_SEL                0

#undef TCFG_AUDIO_DAC_LDO_VOLT
#define TCFG_AUDIO_DAC_LDO_VOLT				DACVDD_LDO_2_65V

#undef TCFG_LOWPOWER_POWER_SEL
#define TCFG_LOWPOWER_POWER_SEL				PWR_LDO15

#undef  TCFG_PWMLED_ENABLE
#define TCFG_PWMLED_ENABLE					DISABLE_THIS_MOUDLE

#undef  TCFG_ADKEY_ENABLE
#define TCFG_ADKEY_ENABLE                   DISABLE_THIS_MOUDLE

#undef  TCFG_IOKEY_ENABLE
#define TCFG_IOKEY_ENABLE					DISABLE_THIS_MOUDLE

#undef TCFG_TEST_BOX_ENABLE
#define TCFG_TEST_BOX_ENABLE			    0

#undef TCFG_AUTO_SHUT_DOWN_TIME
#define TCFG_AUTO_SHUT_DOWN_TIME	        0

#undef TCFG_POWER_ON_NEED_KEY
#define TCFG_POWER_ON_NEED_KEY		        0

#undef TCFG_UART0_ENABLE
#define TCFG_UART0_ENABLE					DISABLE_THIS_MOUDLE

#endif


#define BT_FOR_APP_EN                     0

// To enable app (BLE) upgrade, you need to enable the following macro definition
#if CONFIG_APP_OTA_ENABLE
#define RCSP_BTMATE_EN                    1
#define RCSP_UPDATE_EN                    1
#define UPDATE_MD5_ENABLE                 0
#else
#define RCSP_BTMATE_EN                    0
#define RCSP_UPDATE_EN                    0
#define UPDATE_MD5_ENABLE                 0
#endif


#ifdef CONFIG_SDFILE_ENABLE
#define SDFILE_DEV				"sdfile"
#define SDFILE_MOUNT_PATH     	"mnt/sdfile"

#if (USE_SDFILE_NEW)
#define SDFILE_APP_ROOT_PATH        SDFILE_MOUNT_PATH"/app/"  // app partition
#define SDFILE_RES_ROOT_PATH        SDFILE_MOUNT_PATH"/res/"  // resource file partition
#else
#define SDFILE_RES_ROOT_PATH       	SDFILE_MOUNT_PATH"/C/"
#endif

#endif
#if TCFG_USER_EDR_ENABLE
#if RCSP_BTMATE_EN
#define CONFIG_BT_RX_BUFF_SIZE  (3 * 512)
#define CONFIG_BT_TX_BUFF_SIZE  (3 * 512)
#else
#define CONFIG_BT_RX_BUFF_SIZE  (5 * 512)
#define CONFIG_BT_TX_BUFF_SIZE  (5 * 512)
#endif
#else
#define CONFIG_BT_RX_BUFF_SIZE  (0)
#define CONFIG_BT_TX_BUFF_SIZE  (0)
#endif

#if (CONFIG_BT_MODE != BT_NORMAL)
////bqb 如果测试3M tx buf 最好加大一点
#undef  CONFIG_BT_TX_BUFF_SIZE
#define CONFIG_BT_TX_BUFF_SIZE  (6 * 1024)

#endif
#define BT_NORMAL_HZ	            CONFIG_BT_NORMAL_HZ
//*********************************************************************************//
//                                 Clock Switching Configuration                                    //
//*********************************************************************************//

#define BT_NORMAL_HZ	            CONFIG_BT_NORMAL_HZ
#define BT_CONNECT_HZ               CONFIG_BT_CONNECT_HZ

#define BT_A2DP_HZ	        	    CONFIG_BT_A2DP_HZ
#define BT_TWS_DEC_HZ	        	CONFIG_TWS_DEC_HZ

//#define MUSIC_DEC_CLOCK			    CONFIG_MUSIC_DEC_CLOCK
//#define MUSIC_IDLE_CLOCK		    CONFIG_MUSIC_IDLE_CLOCK

#define BT_CALL_HZ		            CONFIG_BT_CALL_HZ
#define BT_CALL_ADVANCE_HZ          CONFIG_BT_CALL_ADVANCE_HZ
#define BT_CALL_16k_HZ	            CONFIG_BT_CALL_16k_HZ
#define BT_CALL_16k_ADVANCE_HZ      CONFIG_BT_CALL_16k_ADVANCE_HZ

//*********************************************************************************//
//                                 Upgrade Configuration                                        //
//*********************************************************************************//
#if (defined(CONFIG_CPU_BR30))
// Enable LED display for firmware upgrade
//#define UPDATE_LED_REMIND
// Enable voice reminder for firmware upgrade
//#define UPDATE_VOICE_REMIND
#endif

#if (defined(CONFIG_CPU_BR23) || defined(CONFIG_CPU_BR25))
// Enable IO retention for firmware upgrade
//#define DEV_UPDATE_SUPPORT_JUMP           // Currently only supported by br23/br25
#endif

#if (defined(CONFIG_CPU_BR23) || defined(CONFIG_CPU_BR25) || defined(CONFIG_CPU_BD29) || defined(CONFIG_CPU_BD19) || defined(CONFIG_CPU_BR30) || defined(CONFIG_CPU_BR34))
#define USER_UART_UPDATE_ENABLE           0 // For customer's application development of host computer or multi-MCU serial upgrade solution, make sure to exit powerdown before starting serial communication. You need to add corresponding initialization and wake-up port configuration in the board (refer to board_ac632n_demo.c)

#define UART_UPDATE_SLAVE	0
#define UART_UPDATE_MASTER	1

// Configure serial upgrade IO
#define UART_UPDATE_RX_PORT               IO_PORTA_02
#define UART_UPDATE_TX_PORT               IO_PORTA_03

// Configure the role for serial upgrade
#define UART_UPDATE_ROLE	UART_UPDATE_SLAVE

#if USER_UART_UPDATE_ENABLE
#undef TCFG_CHARGESTORE_ENABLE
#undef TCFG_TEST_BOX_ENABLE
#define TCFG_CHARGESTORE_ENABLE				DISABLE_THIS_MOUDLE       // User serial upgrade also uses UART1
#endif

#endif  //USER_UART_UPDATE_ENABLE

#define FLOW_CONTROL           0  // AT command serial port flow control, currently only tested on br30


#endif

