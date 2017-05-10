# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets) == 0.13, but the master branch will probably work just fine
  * Follow the instructions in the [uWebSockets README](https://github.com/uWebSockets/uWebSockets/blob/master/README.md) to get setup for your platform. You can download the zip of the appropriate version from the [releases page](https://github.com/uWebSockets/uWebSockets/releases). Here's a link to the [v0.13 zip](https://github.com/uWebSockets/uWebSockets/archive/v0.13.0.zip).
  * If you run OSX and have homebrew installed you can just run the ./install-mac.sh script to install this
* Simulator. You can download these from the [project intro page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/aca605f8-8219-465d-9c5d-ca72c699561d/lessons/e8235395-22dd-4b87-88e0-d108c5e5bbf4/concepts/6a4d8d42-6a04-4aa6-b284-1697c0fd6562) in the classroom.

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

## Algorithm

### Steering Angle
I implemented a dynamic version of the PID algorithm, taking into account vehicle speed to set the P and D gains. This is done by first calculating the speed factor as follows:
`speed_factor = (MAX_SPEED - speed)/MAX_SPEED`
The speed factor values range from 0 to 1, where 1 corresponds to speed 0 and 1 corresponds to maximum speed. It is used to scale down the P gain based on the observation that when speed increases the gain should be decreased to prevent oscilations. 
This technique indeed improves stability at higher speeds but has a negative side effect of reducing responsiveness which can cause veering of the lane during tight curves. To reduce the effect of reduced manuevrability, the D gain was scaled by `1-speed_factor`, meaning that when speed increases the D gain increases too. This helps because the D gain is very effective in responding to sudden CTE changes which is exactly what happens when entering a curve at high speed. 
In addition, the D parameter has balancing effect on the system which also helps in steady state. In summary, the steering angle calculation is as follows:
`steer_value = -pid.Kp * pid.p_error*speed_factor -  pid.Kd * pid.d_error - pid.Ki * pid.i_error*(1-speed_factor)`

### Throttle
The higher the speed the less stable the system is therefore whenever instability is detected the throttle is reduced. I used very simple but rather effective metric of detecting instability using the absolute value of CTE. Maximum CTE is around 4 (more than that the car is outside of the driving area) and the minimum is 0 and the throttle is negatively proportional to the absolute CTE:
`throttle = 0.9*speed_factor*(MAX_CTE - fabs(cte))/MAX_CTE`

## Hyperparameter Tuning
The first stage was determining what is the maximum value of the P gain without oscilations while I and D gains are 0. This is the anchor that I used to fine tune other parameters empirically using trial and error technique similar to twiddle.

## Results
The following video shows a vehicle controlled by the above PID algorithm in a simulator. The simulator sends CTE and speed for each frame to the PID controller server which calculates the steering angle and throttle and sends it back to the simulator which then moves the car accordingly.
[![Watch the video](https://j.gifs.com/DRnMGq.gif)](https://youtu.be/BY5pcmQY7Jw)

