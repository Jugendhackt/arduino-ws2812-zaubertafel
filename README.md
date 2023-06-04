# Arduino WS2812 Zaubertafel

Eine Zaubertafel angelehnt an [Etch A Sketch](https://de.wikipedia.org/wiki/Etch_A_Sketch) gebaut aus RGB LEDs (WS2812).

Entstanden im Jugend hackt Lab Isenbüttel.

## Anleitung Arduino IDE

- Arduino IDE installieren
- Arduino IDE → Sketch → Library → Manage Libraries → folgende installieren:
  - NeoMatrix
  - NeoPixel
  - BasicEncoder
- Inhalt aus [src/main.cpp](./src/main.cpp) in die Arduino IDE kopieren.
- Tools → Board → richtiges Board auswählen
- Upload

## Anleitung PlatformIO

- In [platform.ini](./platformio.ini) das richtige Board einstellen.
- `pio run --target upload` oder in der IDE "Upload" wählen.
