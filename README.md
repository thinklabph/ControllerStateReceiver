# WirelessController

## How to add library to Arduino

1. Using your preferred internet browser visit this github repository, click on **Code** > **Download Zip**
2. In the Arduino IDE, click on **Sketch** > **Include Library** > **Add .Zip library...**
3. Select the Zip file you downloaded in step #1.
4. This will automatically install the library in your Arduino IDE.

## Using the example

1. In the Arduino IDE, click on **Examples** > **ControllerStateReceiver** > **BasicControllerStateReceiver**.
2. Modify the `R24_ADDRESS` to a 5 character string of your choice.
3. Set the Board by clicking on **Tools** > **Board** > **Arduino AVR Boards** > **Arduino Mega or Mega 2560**.
4. Set the Port to the microcontroller of the mobot.
5. Upload.
6. Open Serial Monitor and set to **115200 baud**.