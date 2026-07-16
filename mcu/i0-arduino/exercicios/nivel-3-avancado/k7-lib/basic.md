
**Arquivo: RGBLed.h**
```cpp
#ifndef RGBLed_h
#define RGBLed_h

#include "Arduino.h"

class RGBLed {
  public:
    // Construtor
    RGBLed(uint8_t redPin, uint8_t greenPin, uint8_t bluePin);
    
    // Inicialização
    void begin();
    
    // Métodos de controle
    void setColor(uint8_t r, uint8_t g, uint8_t b);
    void setRed(uint8_t value);
    void setGreen(uint8_t value);
    void setBlue(uint8_t value);
    void off();
    
    // Efeitos
    void fade(uint8_t r, uint8_t g, uint8_t b, uint16_t duration);
    void rainbow(uint16_t duration);
    void blink(uint8_t r, uint8_t g, uint8_t b, uint16_t interval, uint8_t times);
    
    // Cores pré-definidas
    static const uint32_t RED     = 0xFF0000;
    static const uint32_t GREEN   = 0x00FF00;
    static const uint32_t BLUE    = 0x0000FF;
    static const uint32_t YELLOW  = 0xFFFF00;
    static const uint32_t CYAN    = 0x00FFFF;
    static const uint32_t MAGENTA = 0xFF00FF;
    static const uint32_t WHITE   = 0xFFFFFF;
    
    void setColorHex(uint32_t color);
    
  private:
    uint8_t _redPin;
    uint8_t _greenPin;
    uint8_t _bluePin;
    
    uint8_t _currentR;
    uint8_t _currentG;
    uint8_t _currentB;
    
    void _writeColor();
};

#endif
```

**Arquivo: RGBLed.cpp**
```cpp
#include "RGBLed.h"

RGBLed::RGBLed(uint8_t redPin, uint8_t greenPin, uint8_t bluePin) {
  _redPin = redPin;
  _greenPin = greenPin;
  _bluePin = bluePin;
  
  _currentR = 0;
  _currentG = 0;
  _currentB = 0;
}

void RGBLed::begin() {
  pinMode(_redPin, OUTPUT);
  pinMode(_greenPin, OUTPUT);
  pinMode(_bluePin, OUTPUT);
  off();
}

void RGBLed::setColor(uint8_t r, uint8_t g, uint8_t b) {
  _currentR = r;
  _currentG = g;
  _currentB = b;
  _writeColor();
}

void RGBLed::setRed(uint8_t value) {
  _currentR = value;
  _writeColor();
}

void RGBLed::setGreen(uint8_t value) {
  _currentG = value;
  _writeColor();
}

void RGBLed::setBlue(uint8_t value) {
  _currentB = value;
  _writeColor();
}

void RGBLed::off() {
  setColor(0, 0, 0);
}

void RGBLed::_writeColor() {
  analogWrite(_redPin, _currentR);
  analogWrite(_greenPin, _currentG);
  analogWrite(_bluePin, _currentB);
}

void RGBLed::fade(uint8_t r, uint8_t g, uint8_t b, uint16_t duration) {
  uint8_t startR = _currentR;
  uint8_t startG = _currentG;
  uint8_t startB = _currentB;
  
  uint16_t steps = duration / 10;  // 10ms por step
  
  for (uint16_t i = 0; i <= steps; i++) {
    float progress = (float)i / steps;
    
    uint8_t newR = startR + (r - startR) * progress;
    uint8_t newG = startG + (g - startG) * progress;
    uint8_t newB = startB + (b - startB) * progress;
    
    setColor(newR, newG, newB);
    delay(10);
  }
}

void RGBLed::rainbow(uint16_t duration) {
  uint16_t steps = duration / 20;
  
  for (uint16_t i = 0; i < steps; i++) {
    float hue = (float)i / steps * 360.0;
    
    // HSV to RGB conversion (simplified)
    uint8_t r, g, b;
    
    if (hue < 120) {
      r = 255 - (hue / 120.0) * 255;
      g = (hue / 120.0) * 255;
      b = 0;
    } else if (hue < 240) {
      r = 0;
      g = 255 - ((hue - 120) / 120.0) * 255;
      b = ((hue - 120) / 120.0) * 255;
    } else {
      r = ((hue - 240) / 120.0) * 255;
      g = 0;
      b = 255 - ((hue - 240) / 120.0) * 255;
    }
    
    setColor(r, g, b);
    delay(20);
  }
}

void RGBLed::blink(uint8_t r, uint8_t g, uint8_t b, uint16_t interval, uint8_t times) {
  for (uint8_t i = 0; i < times; i++) {
    setColor(r, g, b);
    delay(interval);
    off();
    delay(interval);
  }
}

void RGBLed::setColorHex(uint32_t color) {
  uint8_t r = (color >> 16) & 0xFF;
  uint8_t g = (color >> 8) & 0xFF;
  uint8_t b = color & 0xFF;
  setColor(r, g, b);
}
```

**Arquivo: keywords.txt**
```
RGBLed	KEYWORD1
begin	KEYWORD2
setColor	KEYWORD2
setRed	KEYWORD2
setGreen	KEYWORD2
setBlue	KEYWORD2
off	KEYWORD2
fade	KEYWORD2
rainbow	KEYWORD2
blink	KEYWORD2
setColorHex	KEYWORD2
RED	LITERAL1
GREEN	LITERAL1
BLUE	LITERAL1
YELLOW	LITERAL1
CYAN	LITERAL1
MAGENTA	LITERAL1
WHITE	LITERAL1
```

**Arquivo: library.properties**
```
name=RGBLed
version=1.0.0
author=Seu Nome <email@example.com>
maintainer=Seu Nome <email@example.com>
sentence=Biblioteca para controle de LED RGB
paragraph=Fornece controle fácil de LEDs RGB com efeitos e cores pré-definidas
category=Device Control
url=https://github.com/seuusuario/RGBLed
architectures=*
includes=RGBLed.h
```

**Exemplo de Uso:**
```cpp
#include <RGBLed.h>

// Criar objeto LED RGB nos pinos 9, 10, 11
RGBLed led(9, 10, 11);

void setup() {
  led.begin();
}

void loop() {
  // Cores pré-definidas
  led.setColorHex(RGBLed::RED);
  delay(1000);
  
  led.setColorHex(RGBLed::GREEN);
  delay(1000);
  
  led.setColorHex(RGBLed::BLUE);
  delay(1000);
  
  // Fade suave
  led.fade(255, 255, 0, 2000);  // Amarelo em 2s
  
  // Rainbow
  led.rainbow(3000);  // 3 segundos
  
  // Blink
  led.blink(255, 0, 255, 500, 5);  // Magenta, 500ms, 5x
}
```
