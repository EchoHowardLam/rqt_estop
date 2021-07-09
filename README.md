# rqt_estop

Basic emergency stop button GUI for ROS. The GUI is a simple toggle push button that can be either depressed to stop the robot or released to allow the robot to continue driving.

This package is currently implemented to publish message on the topic (`\e_stop`) and based on the e-stop button status.

## INSTALLATION 
Requires ROS (tested on Indigo) and rqt
```
sudo apt-get install ros-$ROS_DISTRO-rqt ros-$ROS_DISTRO-rqt-common-plugins

cd ~/catkin_ws/src
git clone https://github.com/EchoHowardLam/rqt_estop.git
cd ..
catkin_make
```

Run using:
`rqt --standalone rqt_estop`

Or add to existing rqt widget
