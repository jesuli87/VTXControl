/*
THIS IS EXISTS ONLY SO THAT OLD SOFWARESERIAL CODE CAN BE USED
*/

#ifndef Serial2WithHalfDuplex_h
#define Serial2WithHalfDuplex_h

#include <Arduino.h>

// Original sswhdErrors
enum sswhdErrors {
    sswhdNoErrors = 0x00,
    sswhdIsNotListening = 0x01,
    sswhdBufferIsEmpty = 0x02,
    sswhdTxDelayIsZero = 0x04,
    sswhdRXDelayStopBitNotSet = 0x08
};


class Serial2WithHalfDuplex {
public:
    Serial2WithHalfDuplex();
    Serial2WithHalfDuplex(int rxPin, int txPin, bool inverse_logic = false, bool halfDuplex = false);

    void begin(unsigned long baud);
    void begin(unsigned long baud, uint16_t config);
    void end();

    int available();
    int read();
    int peek();
    void flush();
    size_t write(uint8_t byte);
    size_t write(const uint8_t *buffer, size_t size);

    void enableHalfDuplex(bool enable); // Not workign
    bool isHalfDuplex();    //Not really working

    void listen();           // Stub
    void writeDummyByte();   // Stub

    sswhdErrors getErrors();         // Returns simulated errors
    uint16_t getConfiguration();     // Last configuration
    void clearErrors();                // Returns same value always
    unsigned long getSpeed();           // Baudrate

private:
    bool _halfDuplex = false;
    unsigned long _currentBaud = 0;
    uint16_t _currentConfig = SERIAL_8N1;
    int _peeked = -1;
};

#endif // Serial2WithHalfDuplex_h