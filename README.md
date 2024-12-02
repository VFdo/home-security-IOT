![GitHub License](https://img.shields.io/github/license/VFdo/home-security-IOT) ![GitHub contributors](https://img.shields.io/github/contributors/VFdo/home-security-IOT)


# Home-Security-IOT

### Description
  This is an IOT project made for Home Security. The setup contains two main components, 
  1. the client build, which is able to detect motion and smoke. 
  2. the base build, which is able to receive messages from multiple clients to sound an alarm and send messages to the user via the Telegram app.
  
  Additionally a video call can be made to the house using an old iPhone using the 'Auto answer calls' feature of the device.
    
## Components
#### Base
+ NodeMCU Microcontroller
+ MQ135 Air Quality Gas Sensor Module
+ nRF24L01 Reciever

#### Client
+ AnrduinoUNO Microcontroller
+ KY-008 Laser Transmitter Module
+ Buzzer 


## Third-party
  - TelegramBot Library
  
## Communication
  - HTTP Protocol
  - SPI Protocol (nRF24L01 tranciever)

## Future Work
- [ ] Add camera to capture a snapshot when the motion is detected.
- [ ] Power off system through Telegram.
- [ ] Send alert if power is compromised.
- [ ] Combine with pet-feeder project.
