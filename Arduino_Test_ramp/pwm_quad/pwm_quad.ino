int ledPin = 6;   // potentiometer connected to analog pin 3

float time_1 = 0;
float time_0 = micros();
// ESC endpoints: 1060us - 1860us
int on_time_duty_low = 911; //low responsiveness starts at 1060 us, but ESCs must be armed first
int on_time_duty_high = 1860; //rated high responsiveness ends at 1860 us
float count = 0;
float duty_cycle = 0;

void setup()

{
    pinMode(ledPin, OUTPUT);   // sets the pin as output

}

void loop()

{
  duty_cycle = on_time_duty_low + count;
  
  if((micros() - time_0) < duty_cycle){
    //turn signal to one
    digitalWrite(ledPin, 1);
  }
  else if((micros() - time_0) >= duty_cycle && (micros() - time_0) < 20064) {
     //turn to zero
     digitalWrite(ledPin, 0);
  }
  else if((micros() - time_0) >= 20064) {
      time_0 = micros();
      count+=0.1;
  }
  if(duty_cycle > on_time_duty_high) {
   count = 0; //resets to low duty cycle
  }
  
}

