# Peregrine

Peregrine is a tilt-rotor/ tilt-wing VTOL controller designed to use an ESP32 board. This uses two rotors along with 4 servos (one for each wing, one for the elevator and the other for the rudder) to control the pitch, roll and yaw controls.

The controller is compatible with Arduino although I haven't tested it. Arduino Uno or any other board which utilizes the ATmega328P chip might not have the required IO pins to connect everything together. So using a more advanced Arduino board might work.

## ESP32

The controller only supports ESP32 boards out of the box. But it can be modified to work on other boards as well. Below are the pins that should be connected to different components (for an ESP32 dev board).

| Pin Number |       Usage      |
|:----------:|:----------------:|
|     14     |   Rudder servo   |
|     27     |  Elevator servo  |
|     26     | Right wing servo |
|     25     |  Left wing servo |
|     33     |    Right rotor   |
|     32     |    Left rotor    |

The MPU6050 sensor is attached to the `SCL` and `SDA` pins of the board. But since the ESP32 dev board does not have a 5v output (just a VIN pin), you need to use the external supply which is used to power the board to power the sensor.

## Connecting everything together

The most important part when connecting all the electronics together is the way we install the MPU6050 sensor. Make sure that the sensor's X-axis is parallel to the wing and goes from left to right. This will result in the Y axis pointing directly forward. The sensor should be set upright.

Hereafter, connecting everything else is pretty straightforward. Connect the correct pins to the PWM inputs of the servos/ motor drivers and you're good to go.

If you're using a Flysky FS-i6 transmitter/ receiver module with the drone, the Arduino boards will not be viable since they don't have the required iBus protocol. This leaves us with the ESP32 board. Here you can connect it to the correct pins (which are yet to be defined) and you should be ready to go. You can also use an NRF24L01+PA+LNA Wireless Transceiver to control the drone. Here I believe you can use both types of boards, Arduino or ESP32 but I have yet to test it out.

Tuning the PID algorithm is currently done by editing the constant values in the `src/systems/Stabilizer.hpp` file. We will introduce a better system to tune the PID rather than altering header files.

As mentioned earlier, this can also be used for tilt-wing applications. The servos connect similarly, but here, rather than the servos controlling only the rotors, it also controls the whole wing. This will increase the load the servo motors will have to operate with which will increase the odds of it failing. Make sure to use servos that support large amounts of force with adequate response times to mitigate any unwanted issues.

### Using the FS-i6 radio control system

When using the FS-i6 radio control system, make sure to define the correct pre-compile definition (please refer to the [Enabling/ disabling features](https://github.com/DhirajWishal/Peregrine#enabling-disabling-features) section). And on the transmitter (radio), go to settings and assign the Ch5 (channel 5) to a switch (this could be anything from `SwA`, `SwB`, and `SwD`). This channel is used to switch from Hover mode to Cruise mode.

If you're new to the transmitter, use the following steps to do so.

1. Switch on the transmitter.
2. Hold down the "OK" button till the setting menu pops up.
3. Using the "UP" button, select the "Functions setup" option and press the "OK" button.
4. Using the "DOWN" button, select the "Aux. channels" option in the menu and press the "OK" button.
5. Using the "UP" button, cycle through the source list till it reaches the desired switch.
6. Once selected, press down the "CANCEL" button till you get redirected back to the previous menu.
7. When you're back at the menu, this means the settings has been updated. Now you can press "CANCEL" a couple more times to get back to the main menu.

## Upload the code and monitor

First and foremost, download or clone this repository to a local directory.

```sh
git clone https://github.com/DhirajWishal/Peregrine {SOURCE}
```

*Here `{SOURCE}` stands for whichever location you clone this repository to.*

After this, if you may have noticed, this project is based on [PlatformIO](https://platformio.org/). Make sure that you have it installed to use this controller. And if you don't have it, while it's being installed, make sure you have all the necessary drivers.

Once everything is ready, go ahead and connect the board to your computer. PlatformIO will attempt to automatically select the correct port but if it failed, make sure to select it manually. Afterwards, you can upload the code and monitor the output.

### Enabling/ disabling features

The `core/Configuration.hpp` file contains a couple of pre-compiler definitions which can be commented/ uncommented out for different features.

- Uncomment/ comment out the `PEREGRINE_DATA_LINK_FS_I6` pre-compiler definition if you're using the FS-i6 receiver to control the drone.
- Uncomment/ comment out the `PEREGRINE_DATA_LINK_NRF24L01` pre-compiler definition if you're using the NRF24L01[+PA+LNA] transceiver to control the drone.

*Note that multiple related features can be enabled/ disable in which case a default or the best will be chosen.*

## License

This project is licensed under Apache-2.0.
