/*
THIS IS EXISTS ONLY SO THAT OLD SOFWARESERIAL CODE CAN BE USED
*/
#include "Serial2WithHalfDuplex.h"

Serial2WithHalfDuplex::Serial2WithHalfDuplex() : _halfDuplex(false), _peeked(-1) {}
Serial2WithHalfDuplex::Serial2WithHalfDuplex(int rxPin, int txPin, bool inverse_logic, bool halfDuplex)
{
    _halfDuplex = halfDuplex;
    (void)rxPin; (void)txPin; (void)inverse_logic; // ignored
}

void Serial2WithHalfDuplex::begin(unsigned long baud)
{
    _currentBaud = baud;
    _currentConfig = SERIAL_8N1;
    Serial2.begin(baud);
}

void Serial2WithHalfDuplex::begin(unsigned long baud, uint16_t config)
{
    _currentBaud = baud;
    _currentConfig = config;
    Serial2.begin(baud, config);
}

void Serial2WithHalfDuplex::end()
{
    Serial2.end();
}

int Serial2WithHalfDuplex::available()
{
    if (_peeked >= 0) return 1 + Serial2.available();
    return Serial2.available();
}

int Serial2WithHalfDuplex::peek()
{
    if (_peeked >= 0) return _peeked;
    return Serial2.peek();
}

int Serial2WithHalfDuplex::read()
{
    if (_peeked >= 0) {
        int c = _peeked;
        _peeked = -1;
        return c;
    }
    return Serial2.read();
}

void Serial2WithHalfDuplex::flush()
{
    Serial2.flush();
}

size_t Serial2WithHalfDuplex::write(uint8_t byte)
{
    if (_halfDuplex) {
        // Optional: toggle DE pin for half-duplex
    }
    size_t r = Serial2.write(byte);
    Serial2.flush();
    return r;
}

size_t Serial2WithHalfDuplex::write(const uint8_t *buffer, size_t size)
{
    if (_halfDuplex) {
        // Optional: toggle DE pin
    }
    size_t r = Serial2.write(buffer, size);
    Serial2.flush();
    return r;
}

void Serial2WithHalfDuplex::enableHalfDuplex(bool enable)
{
    _halfDuplex = enable;
}

bool Serial2WithHalfDuplex::isHalfDuplex()
{
    return _halfDuplex;
}

// Stubs
void Serial2WithHalfDuplex::listen() {}
void Serial2WithHalfDuplex::writeDummyByte() {}

// Simulate errors for compatibility
sswhdErrors Serial2WithHalfDuplex::getErrors()
{
    return sswhdIsNotListening; // always indicate "not listening" for HardwareSerial
}

void Serial2WithHalfDuplex::clearErrors()
{
    // HardwareSerial does not require clearing errors.
    // This is a no-op to satisfy existing code.
}

unsigned long Serial2WithHalfDuplex::getSpeed()
{
    return _currentBaud;  // return the baud set in begin()
}

uint16_t Serial2WithHalfDuplex::getConfiguration()
{
    return _currentConfig;
}