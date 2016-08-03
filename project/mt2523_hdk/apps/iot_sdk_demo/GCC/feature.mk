IC_CONFIG                             = mt2523
BOARD_CONFIG                             = mt2523_hdk

# combo sensor of accelerometer and gyroscope
#MTK_SENSOR_ACCELEROMETER_USE = BMI160
#MTK_SENSOR_MAGNETIC_USE = YAS533
#MTK_SENSOR_BAROMETER_USE = BMP280
#MTK_SENSOR_PROXIMITY_USE = CM36672
MTK_SENSOR_BIO_USE = MT2511
MTK_SENSOR_ACCELEROMETER_USE = BMA255

# fusion algorithm
#FUSION_PEDOMETER_USE = M_INHOUSE_PEDOMETER
#FUSION_SLEEP_TRACKER_USE = M_INHOUSE_SLEEP_TRACKER
FUSION_HEART_RATE_MONITOR_USE = M_INHOUSE_HEART_RATE_MONITOR
FUSION_HEART_RATE_VARIABILITY_USE = M_INHOUSE_HEART_RATE_VARIABILITY
#FUSION_BLOOD_PRESSURE_USE = M_INHOUSE_BLOOD_PRESSURE

# gnss
MTK_GNSS_ENABLE = y

# battery_management
MTK_SMART_BATTERY_ENABLE = y

# bt at command
MTK_BT_AT_COMMAND_ENABLE = y

# CTP module on
MTK_CTP_ENABLE = y
# debug level: none, error, warning, and info
MTK_DEBUG_LEVEL = info

# BT A2DP codec AAC support
MTK_BT_A2DP_AAC_ENABLE = y

# MVG flash test support
MTK_MVG_FLASH_TEST_ENABLE = n

MTK_SENSOR_AT_COMMAND_ENABLE = y

# Support MTK audio tuning tool
MTK_AUDIO_TUNING_ENABLED = n

# System service debug feature for internal use
MTK_SUPPORT_HEAP_DEBUG              = n
MTK_HEAP_SIZE_GUARD_ENABLE          = n

# Development board type: EVB, HDK
MTK_DEVELOPMENT_BOARD_TYPE = HDK

# syslog over uart dma
MTK_SYSLOG_DMA                      = n

# SDK version
MTK_FW_VERSION                      = SDK_VER_IOT_SDK_DEMO

#SDK version query cmd
MTK_QUERY_SDK_VERSION = y

#LED support
MTK_LED_ENABLE = n

#FATFS support
MTK_FATFS_ENABLE = n	
