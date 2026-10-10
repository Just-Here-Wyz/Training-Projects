#include <Button.h>

Button button1(17); // Connect your button between pin 2 and GND
Button button2(18); // Connect your button between pin 3 and GND
Button button3(15); // Connect your button between pin 4 and GND

void setup()
{
	button1.begin();
	button2.begin();
	button3.begin();
	pinMode(4,OUTPUT);
	Serial.begin(9600);
}

void loop()
{
	if (button1.pressed())
		{
			digitalWrite(4,HIGH);
			Serial.println("Button 1 pressed");
		}
		

	if (button2.released())
		{
			digitalWrite(4,LOW);
			Serial.println("Button 2 released");
		}
	if (button3.toggled())
	{
		if (button3.read() == Button::PRESSED)
			Serial.println("Button 3 has been pressed");
		else
			Serial.println("Button 3 has been released");
	}
}