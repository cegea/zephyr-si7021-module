/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Sample mínimo (fase 1): obtiene el dispositivo Si7021 creado por el driver
 * y comprueba que su init terminó bien. Todavía no lee el sensor.
 */

#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

int main(void) {
  /* Se resuelve en tiempo de compilación: busca la única instancia con
   * compatible "adafruit,si7021" (en forma de identificador, como
   * DT_DRV_COMPAT). Si el driver no ha creado el dispositivo (nodo ausente,
   * CONFIG_SI7021=n, DT_DRV_COMPAT mal escrito...), el build falla al
   * enlazar en vez de fallar en silencio.
   */
  const struct device *const dev = DEVICE_DT_GET_ONE(adafruit_si7021);

  /* Se comprueba en tiempo de ejecución: false si si7021_init devolvió
   * error. Ojo: ahora mismo init solo comprueba el bus I2C del micro, así
   * que esto sale true aunque el sensor no esté conectado.
   */
  int err = 0;
  struct sensor_value temp;

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

    err = sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &temp);
    printk("temp: %d\n", temp.val1);
    err = sensor_channel_get(dev, SENSOR_CHAN_HUMIDITY, &temp);
    printk("hum: %d\n", temp.val2);

    k_sleep(K_SECONDS(2));
  }

  return 0;
}
