LEDOS
=====

What is LEDOS?
--------------
LEDOS is a software we are working on for Arduino and ESP8266 that can control an LED strip via multiple interfaces.

Can we make an Ambilight with LEDOS?
------------------------------------
Not only you can, but we already wrote an app that sends the avarage color from your screen to LEDOS. And it is written in C++ with Qt so it is blazingly fast.

See [LEDOS Ambilight](https://github.com/hacktag/LEDOSAmbilight)

How to use it?
--------------
The repo comes with a `Makefile` that does all the magic. All you need to do is:

```bash
make
make upload
```

And the entire code will end up on the Arduino. It's that easy...

License
-------
LEDOS and all of the associated documentation are distributed under the terms of the MIT License. See `LICENSE` for details.
