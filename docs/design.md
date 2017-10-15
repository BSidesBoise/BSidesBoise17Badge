BSides Boise 2017 Badge Design
==============================
This years badge is purposely stupid simple for a couple of reasons:
* We procrastinated, and therefore time constrained
* We were budget constrained due to sponsor issues (Note for sponsors, _please_
  get your funding in fast so we have time to plan cooler badges in the future)
  
The goal of this years badge was to be a development kit that would allow (and 
encourage) attendees to hack it. This is why it's presented on a development 
board.

The Micro-Controller
-------------------
We chose the NodeMCU micro-controller because it's a chip we haven't worked with
before and we wanted to play with it, but it also gives an impressive amount of
capability at a very low cost. The hope is that this simple platform may allow a
foundation from which we can build on for future badges. (Unless we find a
cooler toy)

The Firmware
------------
The firmware was written using the Arduino platform, again, to try to make the
badge as friendly to new hackers as possible. To learn how to program the
firmware yourself, please see [The Building Instructions](building.md)

The design of the firmware consists of two objects and a Moment struct.

### Moment
The Moment is defined in the patterns.h file, and defines a moment in time for
all system LED's including information about how long the system should remain
in that moment, and how it transitions into it.

See the patterns.h header file for more information.

### Led_pin
This object wraps a single LED pin (which there are three of for each tri-color
LED) and handles how that pin gets manipulated. This is the only object that
needs to have knowledge over the fact that the PWM goes between 1 and 1024. As
far as all other objects are concerned, they're setting a percentage brightness
between 0 and 100.

See class documentation for more information.

### Leds
This object, upon creation, populates an array of Led_pin objects and 
initializes them to their initial values and associates them with their initial
values. This object controls all LEDs from a top-level and provides the public
API to other objects in the system.

The fade_to method of this object does the majority of the work in setting all
system LEDs to a specified state. Using information provided within the Moment
struct, it executes the transition into the specified Moment. 

The draw method sits at a higher level uses the fade_to method transition to an
array of Moments provided to the draw method in turn, providing a smooth flow
between Moments. 

### loop
The loop function is where we draw the various LED patterns we're using for the
badge. This is also where potential future functionality will live. Feel free
and extend or modify this firmware as you see fit!
