This project detects the voltage on a particular pin on stm32f072 and notifies
the other controller on voltage above a particular voltage using the analog watchdog feature.
SPI is used to communicate to other controller with help of handshaking mechanism.
Watchdog is serviced in a low priority task

