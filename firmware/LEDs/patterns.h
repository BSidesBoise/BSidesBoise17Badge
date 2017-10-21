/*******************************************************************************
 * This file contains the patterns used by the 2017 BSidesBoise badge.
 ******************************************************************************/
#ifndef PATTERNS_H
#define PATTERNS_H

// How many LED's this badge has total
#define NUMBER_OF_LEDS 12

/*******************************************************************************
 * A moment is the current state of all system LED's at any moment in time.
 * In order to create a pattern that gets drawn, create an array of Moments,
 * which the system can iterate trough setting LED values.
 ******************************************************************************/
struct Moment
{
    // Desired LED RBG (Red Green Blue) values are represented by this array.
    // The array is ordered from left to right, and top to bottom.
    // For example, index 0 represents the top-left-red, index 1 is
    // top-right-green, index 2 is top-right-blue, and index 6 is
    // bottom-left-red and so on.
    // The value in this array should be between 0 and 100 representing the
    // percentage of brightness for that color.
    uint8_t leds[NUMBER_OF_LEDS];

    // This value indicates the speed to which the system should fade the LED's
    // to your desired values. The lower the number the faster the transition,
    // and 0 means no fade (set immediately). Sane values stay between 0-30.
    uint8_t fade_speed;

    // How long (in milliseconds) to stay in this moment
    uint16_t delay_time;
};

// Single color chase Moment(s)
Moment chase_red[] =
        {
                {                       
                        { 100, 0, 0,   0, 0, 0,    0, 0, 0,     0, 0, 0     }, 0, 100
                },
                {
                        { 0, 0, 0,     100, 0, 0,  0, 0, 0,     0, 0, 0     }, 0, 100                
                        },
                {
                        { 0, 0, 0,     0, 0, 0,    100, 0, 0,   0, 0, 0     }, 0, 100
                },
                {
                        { 0, 0, 0,     0, 0, 0,    0, 0, 0,     100, 0, 0   }, 0, 100
                }
        };

Moment chase_green[] =
        {
                {                       
                        { 0, 100, 0,   0, 0, 0,    0, 0, 0,     0, 0, 0   }, 0, 100
                },
                {
                        { 0, 0, 0,     0, 100, 0,  0, 0, 0,     0, 0, 0   }, 0, 100                
                },
                {
                        { 0, 0, 0,     0, 0, 0,    0, 100, 0,   0, 0, 0   }, 0, 100
                },
                {
                        { 0, 0, 0,     0, 0, 0,    0, 0, 0,     0, 100, 0 }, 0, 100
                }
        };

Moment chase_blue[] =
        {
                {                       
                        { 0, 0, 100,   0, 0, 0,    0, 0, 0,     0, 0, 0   }, 0, 100
                },
                {
                        { 0, 0, 0,     0, 0, 100,  0, 0, 0,     0, 0, 0   }, 0, 100                
                },
                {
                        { 0, 0, 0,     0, 0, 0,    0, 0, 100,   0, 0, 0   }, 0, 100
                },
                {
                        { 0, 0, 0,     0, 0, 0,    0, 0, 0,     0, 0, 100 }, 0, 100
                }
        };
Moment chase_white[] =
        {
                {                       
                        { 100, 100, 100,   0, 0, 0,   0, 0, 0,   0, 0, 0 }, 0, 100
                },
                {
                        { 0, 0, 0,   100, 100, 100,   0, 0, 0,   0, 0, 0 }, 0, 100                
                },
                {
                        { 0, 0, 0,   0, 0, 0,   100, 100, 100,   0, 0, 0 }, 0, 100
                },
                {
                        { 0, 0, 0,   0, 0, 0,   0, 0, 0,   100, 100, 100 }, 0, 100
                }
        };
// End Single color chase Moment(s)


Moment roy_g_biv[] =
        {
            {   //RED
                {100, 0, 0,     100, 0, 0,      100, 0, 0,      100, 0, 0       }, 10, 100
            },            
            {   //orange                               
                {100, 40, 13,   100, 40, 13,    100, 40, 13,    100, 40, 13     }, 10, 100
            },            
            {   //yellow 
                {100, 70, 15,   100, 70, 15,    100, 70, 15,    100, 70, 15     }, 10, 100
            },            
            {   //Green
                {0, 100, 0,     0, 100, 0,      0, 100, 0,      0, 100, 0       }, 10, 100
            },            
            {   //Blue
                {0, 0, 100,     0, 0, 100,      0, 0, 100,      0, 0, 100       }, 10, 100
            },            
            {   //indigo       
                {50, 0, 50,     50, 0, 50,      50, 0, 50,      50, 0, 50       }, 10, 100
            },            
            {   //Violet
                {100, 0, 100,   100, 0, 100,    100, 0, 100,    100, 0, 100     }, 10, 100
            },            
            {   //White
                {100, 100, 100, 100, 100, 100,  100, 100, 100,  100, 100, 100   }, 10, 100
            },
            {   // Off
                {0, 0, 0,       0, 0, 0,        0, 0, 0,        0, 0, 0         }, 2, 75
            },
            {   //White
                {100, 100, 100, 100, 100, 100,  100, 100, 100,  100, 100, 100   }, 10, 100
            }
        };

Moment chase_rgb[] =
        {
                {       // Red          Green           Blue            Off
                        { 100, 0, 0,    0, 100, 0,      0, 0, 100,      0, 0, 0 }, 0, 75
                },

                {       // Off          Red            Green            Blue                 
                        { 0, 0, 0,      100, 0, 0,     0, 100, 0,       0, 0, 100 }, 0, 75                
                },

                {       // Blue         Off            Red              Green
                        { 0, 0, 100,    0, 0, 0,       100, 0, 0,       0, 100, 0 }, 0, 75
                },

                {       // Green        Blue            Off             Red
                        { 0, 100, 0,    0, 0, 100,      0, 0, 0,        100, 0, 0 }, 0, 75
                }
        };




Moment pulse_bang[] =
        {
            {   //White
                {100, 100, 100, 100, 100, 100,  100, 100, 100,  100, 100, 100   }, 2, 75
            },
            {   //off
                {0, 0, 0,       0, 0, 0,         0, 0, 0,       0, 0, 0         }, 2, 25
            },
            {   //White
                {100, 100, 100, 100, 100, 100,  100, 100, 100,  100, 100, 100   }, 2, 75
            },
            {   
                {100, 0, 100,   0, 100, 0,      100, 0, 100,    0, 100, 0       }, 0, 25
            },
            {   //off
                {0, 0, 0,       0, 0, 0,        0, 0, 0,        0, 0, 0         }, 2, 25
            },
            {   //Violet
                {100, 0, 100,   0, 100, 0,      100, 0, 100,    0, 100, 0       }, 0, 25
            },
            {   //off
                {0, 0, 0,       0, 0, 0,        0, 0, 0,        0, 0, 0         }, 2, 25
            }
        };
        
Moment criss_cross[] =
        {
                {
                        // Red          Blue            Blue            Red
                        {100, 0, 0,     0, 100, 0,      0, 100, 0,      100, 0, 0}, 0, 250
                },
                {       // Blue         Red             Red             Blue
                        {0, 100, 0,     100, 0, 0,      100, 0, 0,      0, 100, 0}, 0, 250
                },
                {       // Green                                        Green
                        {0, 0, 100,     50, 50, 0,      0, 50, 50,      0, 0, 100}, 0, 250
                },
                {       //              Green           Green           
                        {50, 50, 0,     0, 0, 100,      0, 0, 100,      50, 50, 0}, 0, 250
                },
                {       // Red          Blue            Blue            Red
                        {100, 0, 0,     0, 100, 0,      0, 100, 0,      100, 0, 0}, 0, 250
                },
                {       // Blue         Red             Red             Blue
                        {0, 100, 0,     100, 0, 0,      100, 0, 0,      0, 100, 0}, 0, 250
                },
                {       // Green                                        Green
                        {0, 0, 100,     50, 50, 0,      0, 50, 50,      0, 0, 100}, 0, 250
                },
                {       //              Green           Green             
                        {50, 50, 0,     0, 0, 100,      0, 0, 100,      50, 50, 0}, 0, 250
                },
                {       // Red          Blue            Blue            Red           
                        {100, 0, 0,     0, 100, 0,      0, 100, 0,      100, 0, 0}, 0, 250
                },
                {       // Blue         Red             Red             Blue
                        {0, 100, 0,     100, 0, 0,      100, 0, 0,      0, 100, 0}, 0, 250
                },
                {       // Green                                        Green
                        {0, 0, 100,     50, 50, 0,      0, 50, 50,      0, 0, 100}, 0, 250
                },
                {       //              Green           Green           
                        {50, 50, 0,     0, 0, 100,      0, 0, 100,      50, 50, 0}, 0, 250
                },
                {       // Red          Blue            Blue            Red
                        {100, 0, 0,     0, 100, 0,      0, 100, 0,      100, 0, 0}, 0, 250
                },
                {       // Blue         Red             Red             Blue
                        {0, 100, 0,     100, 0, 0,      100, 0, 0,      0, 100, 0}, 0, 250
                },
                {       // Green                                        Green
                        {0, 0, 100,     50, 50, 0,      0, 50, 50,      0, 0, 100}, 0, 250
                },
                {       //              Green           Green           
                        {50, 50, 0,     0, 0, 100,      0, 0, 100,      50, 50, 0}, 0, 250
                }
        };



// Original Test Patterns
Moment test_rgb[] =
        {
                {
                        // Only Red LED's full on, with fast fade.
                        {100, 0, 0, 100, 0, 0, 100, 0, 0, 100, 0, 0}, 5, 250
                },
                {
                        // Only Green LED's full on with medium fade.
                        {0, 100, 0, 0, 100, 0, 0, 100, 0, 0, 100, 0}, 10, 250
                },
                {
                        // Only Blue LED's full on with slow fade.
                        {0, 0, 100, 0, 0, 100, 0, 0, 100, 0, 0, 100}, 20, 250
                }
        };

Moment test_pattern[] =
        {
                {
                        // All LED's start off, no fade.
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 0, 1000
                },
                {
                        // Only Red LED's full on, with fast fade.
                        {100, 0, 0, 100, 0, 0, 100, 0, 0, 100, 0, 0}, 5, 250
                },
                {
                        // Only Green LED's full on with medium fade.
                        {0, 100, 0, 0, 100, 0, 0, 100, 0, 0, 100, 0}, 10, 250
                },
                {
                        // Only Blue LED's full on with slow fade.
                        {0, 0, 100, 0, 0, 100, 0, 0, 100, 0, 0, 100}, 20, 250
                }
        };

#endif // PATTERNS_H
