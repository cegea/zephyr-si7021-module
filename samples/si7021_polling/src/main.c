#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

int main(void) {
  const struct device *const dev = DEVICE_DT_GET_ONE(adafruit_si7021);

  int err = 0;
  struct sensor_value temp_hum;

  if (!device_is_ready(dev)) {
    printk("Dispositivo %s no está listo\n", dev->name);
    return 0;
  }

  printk("Dispositivo %s listo\n", dev->name);

  while (1) {
    err = sensor_sample_fetch(dev);
    if (err < 0) {
      printk("fetch: %d\n", err);
    }

    err = sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &temp_hum);
    printk("temp: %f\n", sensor_value_to_double(&temp_hum));
    err = sensor_channel_get(dev, SENSOR_CHAN_HUMIDITY, &temp_hum);
    printk("hum: %f\n", sensor_value_to_double(&temp_hum));

    k_sleep(K_SECONDS(2));
  }

  return 0;
}
