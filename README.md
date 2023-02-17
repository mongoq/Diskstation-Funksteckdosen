# Diskstation-Funksteckdosen
Control Pollin Funksteckdosen with an Arduino Nano and a Synology Diskstation

To use this with Synology Diskstations install the file **ch341.ko** from:
**https://github.com/robertklep/dsm7-usb-serial-drivers**.

You need to do an "**insmod usbserial.ko**" before you can do an "**insmod ch341.ko**" (otherwise you will get an error "**unknown symbol**").

The circuit should look like this (D11 is used in the example code).

The antenna shall measure 17,5cm (433MHz --> lambda/4).

![Arduini Nano](https://1.bp.blogspot.com/-GuZSmIRy9X0/W_oqlHoSKsI/AAAAAAAAmd8/-qJu2fF4lZMlJeRqeO1R3uueKHD2nZiGwCLcBGAs/s1600/circuit.png)
