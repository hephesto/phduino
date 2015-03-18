# About #
This project describes an open software open hardware [pH meter](http://en.wikipedia.org/wiki/PH_meter) using an [Arduino](http://www.arduino.cc)/[Freeduino](http://www.freeduino.org) board. In other words, this is an electronic circuit to be connected with a [glass electrode](http://en.wikipedia.org/wiki/Glass_electrode) [pH](http://en.wikipedia.org/wiki/PH) sensor.

It was possible by the idea from my friend Mr. Denis Vidal, the space that my supervisor gave me, prof. Dr. Emanuel Carrilho, [BioMicS Group](http://sites.google.com/site/biomicsgroup/), [Instituto de Química de São Carlos](http://www.iqsc.usp.br/), [Universidade de São Paulo](http://www.usp.br/), Brazil, and by facilities and suggestions from prof. Dr. Claudimir Lucio do Lago, [LAIA Laboratory](http://sites.google.com/site/laiaiqusp/), [Instituto de Química da Universidade de São Paulo](http://www.iq.usp.br/), Brazil. Thanks [Fapesp - Fundação de Amparo à Pesquisa do Estado de São Paulo](http://www.fapesp.br/) by the financial support for my different projects during my academic life.

<table><tr><td><a href='http://picasaweb.google.com.br/lh/photo/twkMUkjBq27yMgWh0ellqQ?feat=embedwebsite'><img src='http://lh6.ggpht.com/_CjTtOo4QsAQ/SpxadcFk71I/AAAAAAAAAMc/83hcoe7n7yg/s400/phduino_v02_PIC_0050.JPG' /></a></td></tr><tr><td>De <a href='http://picasaweb.google.com.br/caneves/PHduinoV02?feat=embedwebsite'>pHduino v0.2</a></td></tr></table>

# Importance and Applications #
[pH](http://en.wikipedia.org/wiki/PH) is a very important property in aqueous solutions. The pH is defined the colog (-log) of the hydrogen ion (H<sup>+</sup>) activity in the medium (or concentration when the H<sup>+</sup> is low quantity). This property indicates if the medium is acid, neutral, or basic.

For example, it is necessary control the pH of an aquarium. Some species of fish can not live out of a range of pH. So, we need read it and make the write correction of the pH. Other areas or applications where is important to know the pH are hydroponic, fermentation processes like beer and wine production, environmental monitoring of soils, water of rivers, lakes, and rain, sewage treatment tanks, monitoring of solution and buffers in laboratories of chemistry, and etc.

# Overview #
The pHduino can operate using a LCD to display the pH and the temperature data like a pH meter. Also, you can control it using a computer by USB port.

The signal gain (slope) and the signal offset are adjusted manually by trimpots. The signal is compensated by a temperature sensor.

It seems inferior and a little bit more expensive compared with a pH meter bench instrument. However, it is interfaceable, programmable, expansible, and, the more important, open and free!

Again, it is not intent to be a high resolution analytical instrument to compete with a commercial pH meter. It is to be simple, easy to understand, easy to modify, and different!

# News #

  * **2012-07-13** Released Python Jabberbot script v0.1.

  * **2012-03-12** Arduino 1.0 compatible.

  * **2011-01-01** pHduino Datalogger hardware v0.1 and firmware v0.4.1-0.3 released.

  * **2010-09-07** Released new hardware v0.2\_0.3 and gerber files package v0.1.

  * **2010-04-25** Released pYpHpoT v0.1.

  * **2010-04-21** Released firmware v0.4.1.

  * **2009-09-20** Released firmware v0.4.

  * **2009-09-13** Released firmware v0.3.

  * **2009-08-31** Released hardware v0.2 and firmware v0.2.

  * **2009-08-12** First public release of the electronic circuit.

  * **2009-08-04** Project opened.

# License #
The layout PCB is under Creative Commons 3.0 and the source code under GPLv2.

# Photos #
PCB layout.

<a href='http://picasaweb.google.com.br/lh/photo/JQOwhpcaMs1ZrYlBou0nGw?feat=embedwebsite'><img src='http://lh3.ggpht.com/_CjTtOo4QsAQ/SpxZME3GwPI/AAAAAAAAAMA/l-w8Vk6oWhg/s800/pHduino_v02.02_PCB.png' /></a>

Electronic scheme.

<a href='http://picasaweb.google.com.br/lh/photo/GH973jZej_jhEzqNdsHK_A?feat=embedwebsite'><img src='http://lh5.ggpht.com/_CjTtOo4QsAQ/SpxZLVArCKI/AAAAAAAAAL0/7gO3MwHGcnw/s800/pHduino_v02.02_scheme.png' /></a>

# References #

The Simplest Possible pH Meter
[http://www.66pacific.com/ph/simplest\_ph.aspx](http://www.66pacific.com/ph/simplest_ph.aspx)

pH Meter - ProjectWIKI
[http://blea.ch/wiki/index.php/PH\_Meter](http://blea.ch/wiki/index.php/PH_Meter)

pH Meter - Circuit Operation
http://home.zonnet.nl/rsetteur/ph_ice.org/www.ice.org/equipment/phmeter/phoper.html

pH-meter.info
[http://www.ph-meter.info/pH-meter-construction](http://www.ph-meter.info/pH-meter-construction)

Tiny pH-meter
[http://damien.douxchamps.net/elec/ph\_meter/](http://damien.douxchamps.net/elec/ph_meter/)

pH Amplifier for Micro
[http://www.electro-tech-online.com/electronic-projects/41430-ph-amplifier-micro.html](http://www.electro-tech-online.com/electronic-projects/41430-ph-amplifier-micro.html)

pH Probe Amplifier/Temperature Compensator
[LF444 Datasheet - Typical Application](http://www.national.com/ds/LF/LF444.pdf)

pH Meter
[OPA129 Datasheet - High impedance amplifier.](http://focus.ti.com/lit/ds/symlink/opa129.pdf)

# Articles #

[Da Rocha, Rogerio T.; Gutz, Ivano G. R.; do Lago, Claudimir L., "From Christmas Ornament to Glass Electrode", Journal of Chemical Education, 1995, 72, 1135-1136](http://jchemed.chem.wisc.edu/Journal/Issues/1995/Dec/abs1135.html).


---

Updated: 2012-07-13