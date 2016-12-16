# Darwin Mini Evolved

This project is a ROS package for control darwin mini(or robotis mini) with Raspberry Pi.

## Hardware Dependency

 * Darwin mini (robotis mini)
 * Raspberry Pi
 * spare OpenCM 9.04

## Software Dependency

 * ROS indigo
 * Rasbian jessie
 * Wiring Pi <http://wiringpi.com/>

## Installation

 1. Download whole project
 2. Install Wiring Pi from <http://wiringpi.com/>\
 3. Upload darwinMiniEvolved.ino to OpenCM 9.04
 4. Move darwin_mini_evolved to proper workspace source folder
 5. Perfotm catkin_make and execute roscore and the node by 'rosrun darwin_mini_evolved darwin_mini_evolved_node'
 
## Current Issues

 * This still is just a feasibility test to control darwin mini with ROS on Raspberry Pi
 * You have to modify to utilize the code for your project
 
## Future works
 * Darwin-Mini hardware upgradesuch as motor or foot
 * message subscription will be performed

## Sub-Projects

OpenCM code, ROS package

## Author

Jeong-Hyeon Bak (superrogin@gmail.com)
