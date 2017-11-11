/*******************************************************************************
 * This sketch defines the 2017 BSidesBoise badge.
 * 
 * See design.md for more information on how this firmware works.
 ******************************************************************************/
#include "patterns.h"
#include "ESP8266WiFi.h"
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`
/*******************************************************************************
 * Constants used throughout this sketch
 ******************************************************************************/
// Constants defining PWM min/max values
//#define MAXRED 350
//#define MAXLED 50
//#define MINLED 1023

//#define MAXRED 674
//#define MAXLED 974
//#define MINLED 0

#define MAXRED 174
#define MAXLED 287
#define MINLED 0

// GPIO pin that's not defined elsewhere by Arduino:
//#define S3 9 //For LOLIN clone due to bug
#define S3 10 //For legitimate NodeMCU
#define RX 3
#define TX 1

/*******************************************************************************
 * Object that abstracts a single LED Pin (a third of a tri-color LED) and
 * controls allowed value setting.
 ******************************************************************************/
class Led_pin
{
public:
    /***************************************************************************
     * Constructor
     * @param[in] led The GPIO pin defining this LED
     * @param[in] initial_brightness The initial brightness of this LED
     * @param[in] max_brightness The maximum brightness PWM level for this LED
     * @param[in] min_brightness The minimum brightness PWM level for this LED
     *
     * Initializes LED pin as outputs and sets it to initial brightness.
     **************************************************************************/
    Led_pin(int led, uint16_t initial_brightness, uint16_t max_brightness,
            uint16_t min_brightness) : m_led(led),
                                       m_brightness(initial_brightness),
                                       m_max_brightness(max_brightness),
                                       m_min_brightness(min_brightness)
    {
        // Set the initial value.
        if (m_led > 0)
            pinMode(m_led, OUTPUT);
            analogWrite(m_led, m_brightness);
    }

    /***************************************************************************
     * Set the PWM value for this LED
     *
     * @param[in] percent_value The PWM value to set in percentage from 0-100
     *
     * @return The current brightness of this LED in percentage between 0-100
     *
     * @remarks Clamps pwm value to min or max value for this LED.
     **************************************************************************/
    uint8_t set_pwm(uint8_t percent_value)
    {
        // Convert percent to real PWM values in the range of this LED
        uint16_t pwm_value = map(percent_value, 0, 100, m_min_brightness,
                                 m_max_brightness);

        if (pwm_value < m_min_brightness)
        {
            // The user tried to set the brightness above the minimum, clamp it
            m_brightness = m_min_brightness;
        }
        else if (pwm_value > m_max_brightness)
        {
            // The user tried to set the brightness below the maximum, clamp it
            m_brightness = m_max_brightness;
        }
        else
        {
            // Set whatever the user specified.
            m_brightness = pwm_value;
        }

        // Now set the value
        if (m_led > 0)
            analogWrite(m_led, m_brightness);
        return percent_value;
    }

private:
    // This LED pin.
    int m_led;

    // The current brightness value in PWM value between 0-1024.
    uint16_t m_brightness;

    // The min/max values that this LED will tolerate.
    uint16_t const m_max_brightness;
    uint16_t const m_min_brightness;
};

/*******************************************************************************
 * Top-level object controls the whole system's LED's and draws patterns with
 * them.
 ******************************************************************************/
class Leds
{
public:
    /***************************************************************************
     * Constructor
     *
     * @remarks Turns all LED's off initially
     **************************************************************************/
    Leds() : m_pin_array(
            {
                    // Top Left Red
                    Led_pin(S3, MINLED, MAXRED, MINLED),
                    // Top Left Green
                    Led_pin(D0, MINLED, MAXLED, MINLED),
                    // Top Left Blue
                    Led_pin(D1, MINLED, MAXLED, MINLED),
                    // Top Right Red
                    Led_pin(D2, MINLED, MAXRED, MINLED),
                    // Top Right Green
                    Led_pin(-1, MINLED, MAXLED, MINLED),
                    // Top Right Blue
                    Led_pin(D4, MINLED, MAXLED, MINLED),
                    // Bottom Left Red
                    Led_pin(D7, MINLED, MAXRED, MINLED),
                    // Bottom Left Green
                    Led_pin(D6, MINLED, MAXLED, MINLED),
                    // Bottom Left Blue
                    Led_pin(-1, MINLED, MAXLED, MINLED),
                    // Bottom Right Red
                    Led_pin(D8, MINLED, MAXRED, MINLED),
                    // Bottom Right Green
                    Led_pin(RX, MINLED, MAXLED, MINLED),
                    // Bottom Right Blue
                    Led_pin(TX, MINLED, MAXLED, MINLED)
            }),
             m_brightness{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    {
        // Nothing to do here.
    }

    /***************************************************************************
     * Sets all LEDs from their current brightness to their specified brightness
     * handling fade times.
     *
     * @param[in] state The Moment containing information about the state to
     *            transition into.
     **************************************************************************/
    void fade_to(Moment state)
    {
        // Loop until all LED's have faded to their set values
        while(true)
        {
            // Reset the done LED counter
            uint8_t done_leds = 0;

            // For every LED, check the current brightness against the state
            // brightness and determine if they need to change.
            for (int i = 0; i < NUMBER_OF_LEDS; i++)
            {
                if (m_brightness[i] != state.leds[i])
                {
                    // Fade the LED a bit in the right direction
                    if (state.leds[i] < m_brightness[i])
                    {
                        if (state.fade_speed > 0)
                        {
                            // Need to dim a bit
                            m_brightness[i] = m_pin_array[i].set_pwm(
                                    --m_brightness[i]);
                        }
                        else
                        {
                            // Set LED immediately
                            m_brightness[i] = m_pin_array[i].set_pwm(
                                    state.leds[i]);
                        }
                    }
                    else
                    {
                        if (state.fade_speed > 0)
                        {
                            // Need to brighten a bit (smaller PWM)
                            m_brightness[i] = m_pin_array[i].set_pwm(
                                    ++m_brightness[i]);
                        }
                        else
                        {
                            // Set LED immediately
                            m_brightness[i] = m_pin_array[i].set_pwm(
                                    state.leds[i]);
                        }
                    }
                }
                else
                {
                    // We don't need to touch this LED, it's already set.
                    done_leds++;
                }
            }
            delay(state.fade_speed);

            // Check to see if we're done fading all LED's yet
            if (done_leds == NUMBER_OF_LEDS)
            {
                return;
            }
        }
    }

    /***************************************************************************
     * Draws an LED pattern using an array of Moments that define that pattern
     *
     * @param[in] pattern The moment array to draw
     * @param[in] pattern_size How many moments are in the array.
     **************************************************************************/
    void draw(Moment *pattern, uint8_t pattern_size)
    {
        for (int i = 0; i < pattern_size; i++)
        {
            fade_to(pattern[i]);
            delay(pattern[i].delay_time);
        }
    }

private:
    // An array of LED Pin's
    Led_pin m_pin_array[NUMBER_OF_LEDS];

    // An array of current LED brightness levels between 0-100%
    uint8_t m_brightness[NUMBER_OF_LEDS];
};

// Our system's LED's
Leds ZE_LEDS;

// Initialize the OLED display using Wire library
SSD1306 display(0x3c, D3, D5);

void setup()
{
    // Initialising the UI will init the display too.
    display.init();
    display.clear();

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
}

// Generate random int to determine how many times to loop each Moment
int get_random(int min, int max)
{
    return random(min,max);
}

void loop_Unlock_patterns(){
    // Red/Blue 'cop' pattern #1
    for(int i = 0; i < get_random(4,10); i++){
        ZE_LEDS.draw(cop_pattern_1, sizeof(cop_pattern_1)/ sizeof(*cop_pattern_1));
    }
    // Red/Blue 'cop' pattern #2
    for(int i = 0; i < get_random(4,10); i++){
        ZE_LEDS.draw(cop_pattern_2, sizeof(cop_pattern_2)/ sizeof(*cop_pattern_2));
    };
}
void loop_Patterns(){
    // random loop Moment chase_rgb
    for(int i = 0; i < get_random(4,10); i++){
        ZE_LEDS.draw(chase_rgb, sizeof(chase_rgb)/ sizeof(*chase_rgb));
    }

    // Moment roy_g_biv
        ZE_LEDS.draw(roy_g_biv, sizeof(roy_g_biv)/ sizeof(*roy_g_biv));

    // random loop Moment chase_red
    for(int i = 0; i < get_random(0,8); i++){
        ZE_LEDS.draw(chase_red, sizeof(chase_red)/ sizeof(*chase_red));
    }

    // random loop Moment chase_green
    for(int i = 0; i < get_random(0,8); i++){
        ZE_LEDS.draw(chase_green, sizeof(chase_green)/ sizeof(*chase_green));
    }

    // random loop Moment chase_blue
    for(int i = 0; i < get_random(0,8); i++){
        ZE_LEDS.draw(chase_blue, sizeof(chase_blue)/ sizeof(*chase_blue));
    }

    // random loop Moment chase_white
    for(int i = 0; i < get_random(0,8); i++){
        ZE_LEDS.draw(chase_white, sizeof(chase_white)/ sizeof(*chase_white));
    }

    // random loop Moment pulse_bang
    for(int i = 0; i < get_random(1,6); i++){
        ZE_LEDS.draw(pulse_bang, sizeof(pulse_bang)/ sizeof(*pulse_bang));
    };
}
void loop()
{
    // Grab the wifi networks
    int n = WiFi.scanNetworks();

    // Setup the screen
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10); //We Get 5 lines of 24 characters at this font size

    // Format the screen output
    String output = "";
    if (n == 0)
    {
        output = "No networks found";
    }
    else
    {
        if (n > 5)
            n = 5;

        for (int i = 0; i < n; ++i)
        {
            String ssid = WiFi.SSID(i);
            String data = " (";
            data.concat(WiFi.RSSI(i));
            data.concat(")");
            if (WiFi.encryptionType(i) == ENC_TYPE_NONE)
            {
                data.concat(" *");
            }
            else if (WiFi.encryptionType(i) == ENC_TYPE_WEP)
            {
                data.concat(" WEP");
            }
            else if (WiFi.encryptionType(i) == ENC_TYPE_TKIP)
            {
                data.concat(" TKIP");
            }
            else if (WiFi.encryptionType(i) == ENC_TYPE_CCMP)
            {
                data.concat(" CCMP");
            }
            else if (WiFi.encryptionType(i) == ENC_TYPE_AUTO)
            {
                data.concat(" AUTO");
            }

            String line = ssid;
            line.concat(data);
            int ssid_size = ssid.length() - 3;

            while (display.getStringWidth(line) > 128)
            {
                ssid_size--;
                ssid.remove(ssid_size);
                ssid.concat("...");
                line = ssid;
                line.concat(data);
            }

            output.concat(line);
            output.concat("\n");
        }
    }

    display.drawString(0, 0, output);
    display.display();

    // criss_cross pattern on power on
    // Followed by Member Mode
    // Followed by loop custom patterns
    for(int i = 0; i < 1; i++)
    {
        ZE_LEDS.draw(criss_cross, sizeof(criss_cross)/ sizeof(*criss_cross));
    }
    ZE_LEDS.draw(turn_off, sizeof(turn_off)/ sizeof(*turn_off));
    delay(1000);

    // attendee_glow - GREEN
    // speaker_glow BLUE
    // staff_glow RED
    for(int i = 0; i < 10; i++)
    {
        ZE_LEDS.draw(attendee_glow, sizeof(attendee_glow)/ sizeof(*attendee_glow));
    };

    loop_Patterns();
    delay(1000);

    // Uncomment the following line for super sekret 'cop' pattern unlock
    loop_Unlock_patterns();
    delay(1000);
}
