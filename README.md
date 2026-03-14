# 🤖 6-Axis Robotic Arm (Cobot) ze zintegrowanym Web-HMI

<div align="center">
  <img src="Media/manipulator.gif" width="600" alt="Demonstracja ruchu manipulatora">
  <p><i>Zrobotyzowany manipulator 6-osiowy w trakcie wykonywania predefiniowanej trajektorii.</i></p>
</div>

## 📌 O projekcie
Kompleksowy projekt 6-osiowego ramienia robotycznego (klasyfikacja: ramię przegubowe / cobot) zaprojektowanego od zera w Fusion 360 i oprogramowanego w czystym C++ na mikrokontrolerze ESP32. 

Projekt nie opiera się na gotowych "zabawkowych" bibliotekach do robotyki. Głównym założeniem było stworzenie **własnego silnika kinematyki odwrotnej (IK)** w przestrzeni 3D oraz przemysłowego panelu sterowania (Teach Pendant) dostępnego z poziomu przeglądarki internetowej (HTML + CSS + JavaScript).

## 🚀 Główne cechy i rozwiązania inżynierskie

* **Autorska Kinematyka Odwrotna (IK):** Samodzielna implementacja trygonometrii przestrzennej i operacji na macierzach rotacji (plik `arm.cpp`). System precyzyjnie wylicza kąty dla 6 osi, pozwalając na zadawanie współrzędnych TCP (Tool Center Point) w osiach kartezjańskich (X, Y, Z) wraz z pożądaną orientacją efektora.
* **Wielowątkowość (FreeRTOS):** Kod wykorzystuje oba rdzenie układu ESP32 (`xTaskCreatePinnedToCore`). Jeden rdzeń zajmuje się bezwzględnym przeliczaniem kinematyki i płynnym generowaniem kroków dla silników, podczas gdy drugi obsługuje komunikację sieciową i asynchroniczny serwer.
* **Web-Based Teach Pendant (HMI):** Zintegrowany interfejs użytkownika napisany w HTML/CSS/JS (serwowany z pamięci SPIFFS). Wykorzystuje **WebSockets** oraz format **JSON** do asynchronicznej, dwukierunkowej wymiany danych z robotem w czasie rzeczywistym (odczyt pozycji, sterowanie manualne, odpalanie makr).
* **Zaawansowane sterowanie napędami:** Precyzyjne sterowanie 6 silnikami krokowymi z profilowaniem przyspieszeń (biblioteka *AccelStepper*) oraz wbudowana procedura automatycznej kalibracji (bazowania) przy użyciu wyłączników krańcowych (plik `steppers.ino`).
* **Rozszerzalność:** System posiada zintegrowaną obsługę chwytaka (Servo) oraz bibliotekę gotowych trajektorii i kształtów (np. `drawHexagon()`), a także procedury współpracy z zewnętrznym transporterem taśmowym.
* **Autorskie przekładnie planetarne:** Przekładnie zostały zaprojektowane w przełożeniu 38.4 : 1, umożliwiając efektywne zwiększenie momentu obrotowego silników krokowych. Przekładnie zostały wyposażone w zęby skośne umożliwiające przenoszenie większych obciążeń, oraz generujących mniej luzów.

## 🛠️ Stack Technologiczny
* **Hardware:** ESP32, Silniki krokowe (NEMA17), serwomechanizm (efektor), druk 3D (PETG/PLA).
* **Software:** C++, FreeRTOS, HTML5/CSS3/JavaScript (jQuery).
* **Kluczowe biblioteki:** `AccelStepper`, `ESPAsyncWebServer`, `ArduinoJson`.
* **CAD:** Autodesk Fusion 360.


## Możliwości
Robot może zostac wyposażony dodatkowo w chwytak i może zostać zsynchronizowany z transporterem. Połączenie tych dwóch elementów wraz z robotem powoduje, że manipulator staje się symulacją stacji przemysłowej.


## 📂 Struktura Repozytorium (Ważniejsze pliki)
* `/libs/arm.cpp` - Niskopoziomowy silnik obliczeniowy macierzy i kinematyki odwrotnej.
* `/headers/rotations.h` - Definicje przestrzennych macierzy rotacji dla efektora.
* `/website.html` & `/websocket.js` - Pliki interfejsu HMI (Teach Pendant).
* `/only_repeat_main.ino` - Główna pętla programu i maszyna stanów.
