C++ API to interface between Danfoss SASA Encoder and ROS
===========================================================

The SASA steering Encoder from DANFOSS gives messages via CAN bus which is interpreted by the arduino. The arduino runs sends a serial message to the BeagleBone Black. The BeagleBone Black is connected via rosserial to the laptop where ros runs. This code runs on Beagle Bone Black and is used for publishing to the rostopic: /interfaces/encoder/steering

1. To compile binaries: make
2. To generate libraries: make "Library name"
3. To copy binaries to source path: make install
4. Set IP of host machine from /opt/rosserial/bin/RosSrvrIp
