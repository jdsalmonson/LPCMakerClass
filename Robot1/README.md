Laser Cutter CAD files
======================

Herein are the design files for our robot chassis.  These are also available on the laser cutter laptop at Robot Garden at:
  * Libraries\Documents\My Documents\LPCMakerClass\Robot1
  
Please see the [Laser Cutter Class Manual](https://drive.google.com/file/d/0B0z8iTjN78OjWFJiWnEyOEs5bFk/edit?usp=sharing) and the [SBU page](http://www.robotgarden.org/workshop/safety-and-basic-use/) robot garden webpages for more information.

Robot1c differs from Robot1b in that it has parts for the nose roller ball mount for the tricycle wheel pattern.  Robot1b differed from Robot1a in that it extended the base to allow for more components to fit.

FreeCAD master file of the cut-out plans:
   * Robot1c.FCStd

An export from FreeCAD of the cut-out plans in "Flattened SVG" format:
   * Robot1c_flattened.svg

The Microsoft format (printed by Inkscape) of the Flattened SVG format.  This is what you open in the Full Spectrum laser cutter software:
   * Robot1c_flattened.xps

The files for just the nose ball trike assembly are:
 * Robot1cTrikeAssembly.FCStd
 * Robot1cTrikeAssembly_flattened.svg

Arduino Sketches
================

Sketches for the testing an use of our robot:
 * [Photoresistor_n_Joystick_to_HbridgeL293D](https://github.com/jdsalmonson/LPCMakerClass/tree/master/Robot1/Photoresistor_n_Joystick_to_HbridgeL293D) - Sketch that runs robot in joystick mode or phototropic mode.  Based on the sketch below.
 * [Photoresistor2_to_HbridgeL293D](https://github.com/jdsalmonson/LPCMakerClass/tree/master/Robot1/Photoresistor2_to_HbridgeL293D) - Full sketch to run motors based on photoresistor levels, causing the robot to phototropically steer toward a flashlight. 
 * [SimplePhotoresistorTest](https://github.com/jdsalmonson/LPCMakerClass/tree/master/Robot1/SimplePhotoresistorTest) - Simple test of the photoresistor circuit: writes the photoresistor voltage reading from analog pin A0 to the serial monitor.

Wiring diagrams
===============

Also we have the Fritzing files for wiring this robot.  These include:
 * Robot1_H-Bridge_Wiring.fzz  - the Fritzing file for the basic wiring of the H-bridge
 * Robot1_H-Bridge_Wiring.png  - PNG graphic of above Fritzing diagram
 * Robot1_H-Bridge_PhotoResistorWiring.fzz  - the H-bridge wiring contained in the file above plus the photoresistor circuits
 * Robot1_H-Bridge_PhotoResistorWiring.png  - PNG graphic of above Fritzing diagram
 * Robot1_H-Bridge_PhotoResistorWiring_9Volt.fzz  - the Fritzing file incorporating a 9 Volt battery instead of 6 Volts.
 * Robot1_H-Bridge_PhotoResistorWiring_9Volt.png  - PNG graphic of above Fritzing diagram

![PhotoResistorWiring figure](Robot1_H-Bridge_PhotoResistorWiring_9Volt.png)
