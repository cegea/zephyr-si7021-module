#define DT_DRV_COMPAT adafruit_si7021

#include <si7021.h>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/sensor.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(si7021, CONFIG_SENSOR_LOG_LEVEL);

static int si7021_sample_fetch(const struct device *dev,
                               enum sensor_channel chan) {
  const struct si7021_config *config = dev->config;
  struct si7021_data *data = dev->data;

  return -ENOTSUP;
}

static int si7021_channel_get(const struct device *dev,
                              enum sensor_channel chan,
                              struct sensor_value *val) {
  struct si7021_data *data = dev->data;

  return -ENOTSUP; // hasta completar con SENSOR_CHAN_AMBIENT_TEMP y
                   // SENSOR_CHAN_HUMIDITY
}

static DEVICE_API(sensor, si7021_api) = {
    .sample_fetch = &si7021_sample_fetch,
    .channel_get = &si7021_channel_get,
};

static int si7021_init(const struct device *dev) {
  const struct si7021_config *config = dev->config;

  if (!i2c_is_ready_dt(&config->i2c)) {
    LOG_ERR("I2C not ready");
    return -ENODEV;
  }

  LOG_DBG("si7021 ok");

  return 0;
}

#define SI7021_INIT(i)                                                         \
  static struct si7021_data si7021_data_##i;                                   \
                                                                               \
  static const struct si7021_config si7021_config_##i = {                      \
      .i2c = I2C_DT_SPEC_INST_GET(i),                                          \
  };                                                                           \
                                                                               \
  SENSOR_DEVICE_DT_INST_DEFINE(i, si7021_init, NULL, &si7021_data_##i,         \
                               &si7021_config_##i, POST_KERNEL,                \
                               CONFIG_SENSOR_INIT_PRIORITY, &si7021_api);

DT_INST_FOREACH_STATUS_OKAY(SI7021_INIT)
