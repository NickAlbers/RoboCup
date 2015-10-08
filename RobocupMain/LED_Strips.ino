/* LedStripColorTester: Example Arduino sketch that lets you
 * type in a color on a PC and see it on the LED strip.
 *
 * To use this, you will need to plug an Addressable RGB LED
 * strip from Pololu into pin 12.  After uploading the sketch,
 * select "Serial Monitor" from the "Tools" menu.  In the input
 * box, type a color and press enter.
 *
 * The format of the color should be "R,G,B!" where R, G, and B
 * are numbers between 0 and 255 representing the brightnesses
 * of the red, green, and blue components respectively.
 *
 * For example, to get green, you could type:
 *   40,100,0!
 *
 * You can leave off the exclamation point if you change the
 * Serial Monitor's line ending setting to be "Newline" instead
 * of "No line ending".
 *
 * Please note that this sketch only transmits colors to the
 * LED strip after it receives them from the computer, so if
 * the LED strip loses power it will be off until you resend
 * the color.
 */


// Create an ledStrip object and specify the pin it will use.
PololuLedStrip<12> ledStripLeft;
PololuLedStrip<13> ledStripRight;

// Create a buffer for holding the colors (3 bytes per color).
//LED Strip:
#define LED_COUNT 16
rgb_color colors[LED_COUNT];

void setupLED()
{
  // Start up the serial port, for communication with the PC.
  Serial.begin(4800);
  Serial.println("Ready to receive colors.");
}

//***********************************************************************************************
// Flash the LED Strips the specified colour
//***********************************************************************************************

void UpdateLED(int red, int green, int blue)
{
  Serial.println("Updating Led Strips");
  // If any digit is received, we will go into integer parsing mode
  // until all three calls to parseInt return an interger or time out.
  // Read the color from the computer.
  rgb_color color;
  color.red = red;
  color.green = blue;
  color.blue = green;

  // Update the colors buffer.
  for (uint16_t i = 0; i < LED_COUNT; i++)
  {
    colors[i] = color;
  }

  // Write to the LED strip.
  ledStripLeft.write(colors, LED_COUNT);
  ledStripRight.write(colors, LED_COUNT);
}

//***********************************************************************************************
// Read LED colours from the serial input in the format R:G:B! exclamation mark denotes line end
//***********************************************************************************************
void LEDFromInput()
{
  // If any digit is received, we will go into integer parsing mode
  // until all three calls to parseInt return an interger or time out.
  if (Serial.available())
  {
    char c = Serial.peek();
    if (!(c >= '0' && c <= '9'))
    {
      Serial.read(); // Discard non-digit character
    }
    else
    {
      // Read the color from the computer.
      rgb_color color;
      color.red = Serial.parseInt();
      color.green = Serial.parseInt();
      color.blue = Serial.parseInt();

      // Update the colors buffer.
      for (uint16_t i = 0; i < LED_COUNT; i++)
      {
        colors[i] = color;
      }

      // Write to the LED strip.
      ledStripLeft.write(colors, LED_COUNT);
      ledStripRight.write(colors, LED_COUNT);

      Serial.print("Showing color: ");
      Serial.print(color.red);
      Serial.print(",");
      Serial.print(color.green);
      Serial.print(",");
      Serial.println(color.blue);
    }
  }
}

//***********************************************************************************************
// Read LED colours from the serial input in the format R:G:B! exclamation mark denotes line end
//***********************************************************************************************

void LEDGradient()
{
  // Update the colors.
  byte time = millis() >> 2;
  for(uint16_t i = 0; i < LED_COUNT; i++)
  {
    byte x = time - 8*i;
    colors[i] = (rgb_color){ x, 255 - x, x };
  }
  
  // Write the colors to the LED strip.
  ledStripLeft.write(colors, LED_COUNT);  
  ledStripRight.write(colors, LED_COUNT);  
  
  delay(10);
}
