/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Sample mínimo (fase 1): obtiene el dispositivo Si7021 creado por el driver
 * y comprueba que su init terminó bien. Todavía no lee el sensor.
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/sys/printk.h>

int main(void)
{
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
	if (!device_is_ready(dev)) {
		printk("Dispositivo %s no está listo\n", dev->name);
		return 0;
	}

	printk("Dispositivo %s listo\n", dev->name);

	return 0;
}
