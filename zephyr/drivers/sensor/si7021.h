#ifndef SI7021_H_
#define SI7021_H_

#include "zephyr/drivers/i2c.h"
#include <stdint.h>

#define SI7021_CMD_MEAS_RH_NOHOLD 0xF5
#define SI7021_CMD_MEAS_RH_HOLD 0xE5
#define SI7021_CMD_MEAS_T_NOHOLD 0xF3
#define SI7021_CMD_MEAS_T_HOLD 0xE3
#define SI7021_CMD_MEAS_T_FROM_PREVIOUS_HUM_READ 0xE0

#define SI7021_RESET 0xFE

#define SI7021_CMD_READ_USER_REG_1 0xE6
#define SI7021_CMD_WRITE_USER_REG_1 0xE7

#define SI7021_CMD_WRITE_HEATER_CTRL 0x51
#define SI7021_CMD_READ_HEATER_CTRL 0x11

#define SI7021_ID 0x15

struct si7021_data {
  uint16_t raw_rh;
  uint16_t raw_t;
};

struct si7021_config {
  struct i2c_dt_spec i2c;
};

#endif
