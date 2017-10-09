/*******************************************************************************
 * This sketch defines the 2017 BSidesBoise badge.
 * 
 * See design documents for more information on how this firmware works.
 ******************************************************************************/

/*******************************************************************************
 * Constants used throughout this sketch
 ******************************************************************************/
// Constants defining PWM min/max values
#define MAXRED 350
#define MAXLED 50
#define MINLED 1023

// GPIO pin that's not defined elsewhere by Arduino
#define S3 9

/*******************************************************************************
 * Object that abstracts a single LED Pin
 ******************************************************************************/
class Led_pin
{
public:
    /***************************************************************************
     * Constructor
     * @param[in] led The GPIO pin defining this LED
     * @param[in] initial_brightness The intial brightness of this LED
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
        pinMode(m_led, OUTPUT);
        analogWrite(m_led, m_brightness);
    }

    /***************************************************************************
     * Fade this LED from current brightness to off at the given rate.
     *
     * @param[in] fade_speed The speed in milliseconds to fade. Typically
     *            between 0 - 30.
     *
     * @remarks Uses this LED's current brightness setting as a starting point.
     **************************************************************************/
    void fade_off(uint8_t fade_speed)
    {
        // The PWM range is 0-1024. This is the step size to fade down per
        // fade_speed milliseconds.
        uint8_t fadeAmount = 10;

        while(true)
        {
            if (m_brightness >= (m_min_brightness - fadeAmount))
            {
                // Turn the LED full off and bail, we're done.
                m_brightness = m_min_brightness;
                analogWrite(m_led, m_brightness);
                break;
            }
            else
            {
                // Still fading
                delay(fade_speed);
            }

            // Fade a bit more
            m_brightness = m_brightness + fadeAmount;
            analogWrite(m_led, m_brightness);
        }
    }

    /***************************************************************************
     * Fade this LED from current brightness to on at the given rate.
     *
     * @param[in] fade_speed The speed in milliseconds to fade. Typically
     *            between 0 - 30.
     *
     * @remarks Uses this LED's current brightness setting as a starting point.
     **************************************************************************/
    void fade_on(uint8_t fade_speed)
    {
        // The PWM range is 0-1024. This is the step size to fade down per
        // fade_speed milliseconds.
        uint8_t fadeAmount = 10;

        while(true)
        {
            if (m_brightness <= fadeAmount)
            {
                // Turn the LED full on and bail, we're done.
                m_brightness = m_max_brightness;
                analogWrite(m_led, m_brightness);
                break;
            }
            else
            {
                // Still fading
                delay(fade_speed);
            }

            // Fade a bit more
            m_brightness = m_brightness - fadeAmount;
            analogWrite(m_led, m_brightness);
        }
    }

private:
    int m_led;
    uint16_t m_brightness;
    uint16_t m_max_brightness;
    uint16_t m_min_brightness;
};

/*******************************************************************************
 * Object that abstracts a tri-color LED
 ******************************************************************************/
class Led
{
public:
    /***************************************************************************
     * Constructor
     * @param[in] red The GPIO pin defining RED for this LED
     * @param[in] green The GPIO pin defining GREEN for this LED
     * @param[in] blue The GPIO pin defining BLUE for this LED
     *
     * Initializes LED pins as outputs and sets them high to turn LED's off.
     **************************************************************************/
    Led(Led_pin red, Led_pin green, Led_pin blue) : m_red_led(red),
                                                    m_green_led(green),
                                                    m_blue_led(blue)
    {
        // Nothing to see here, initialization happens at the LED pin level
    }

    /***************************************************************************
     * Pattern drawer
     *
     * @param[in] pattern
     *
     **************************************************************************/
    bool draw()
    {
        // TODO - For now, we'll just fade the three pins for testing
        m_red_led.fade_on(5);
        m_red_led.fade_off(5);
        m_green_led.fade_on(5);
        m_green_led.fade_off(5);
        m_blue_led.fade_on(5);
        m_blue_led.fade_off(5);
    }
    
private:
    // LED Pin's
    Led_pin m_red_led;
    Led_pin m_green_led;
    Led_pin m_blue_led;
};

/*******************************************************************************
 * Global Variables
 ******************************************************************************/
// Our system's LED's
Led_pin TLRED(S3, MINLED, MAXRED, MINLED);
Led_pin TLGREEN(D0, MINLED, MAXLED, MINLED);
Led_pin TLBLUE(D1, MINLED, MAXLED, MINLED);

Led_pin TRRED(D2, MINLED, MAXRED, MINLED);
Led_pin TRGREEN(D3, MINLED, MAXLED, MINLED);
Led_pin TRBLUE(D4, MINLED, MAXLED, MINLED);

Led_pin BLRED(D5, MINLED, MAXRED, MINLED);
Led_pin BLGREEN(D6, MINLED, MAXLED, MINLED);
Led_pin BLBLUE(D7, MINLED, MAXLED, MINLED);

Led_pin BRRED(D8, MINLED, MAXRED, MINLED);
Led_pin BRGREEN(D9, MINLED, MAXLED, MINLED);
Led_pin BRBLUE(D10, MINLED, MAXLED, MINLED);

Led TOP_LEFT(TLRED, TLGREEN, TLBLUE);
Led TOP_RIGHT(TRRED, TRGREEN, TRBLUE);
Led BOTTOM_LEFT(BLRED, BLGREEN, BLBLUE);
Led BOTTOM_RIGHT(BRRED, BRGREEN, BRBLUE);

void setup()
{
    // Everything's done by the object initializer's.
}

void loop()
{
    TOP_LEFT.draw();
    TOP_RIGHT.draw();
    BOTTOM_LEFT.draw();
    BOTTOM_RIGHT.draw();
}

