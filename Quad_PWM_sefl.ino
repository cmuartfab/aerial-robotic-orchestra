#define OutPin 9
volatile unsigned long time_1 = 0;
volatile unsigned long time_0 = micros();
#define prearm_on_time 900 //Pre-arm on time
#define max_on_time 1860 //ESC Upper Lim
#define min_on_time 1060 //ESC Lower Lim
#define m_dur 100 //per note duration :: playnotes()
volatile unsigned long count = 0;
volatile unsigned long duty_cycle = 0;
unsigned long int note = min_on_time;
int limit = 0; //hold
int notes[10] = {1062, 1110, 1200, 1260, 1200, 1320, 1350, 1260, 1350, 1200};
int NoteLength[10] = {3000, 2700, 2700, 2700, 2700, 2400, 2400, 2100, 2400, 2400};
void setup()
{
  // Serial.begin(9600);
  pinMode(OutPin, OUTPUT);   // sets the pin as output
}

void loop()
{
  while (1) {
    duty_cycle = prearm_on_time + count;
    if ((micros() - time_0) < duty_cycle) {
      //turn signal to one
      digitalWrite(OutPin, 1);
    }
    else if ((micros() - time_0) >= duty_cycle && (micros() - time_0) < 20064) {
      //turn to zero
      digitalWrite(OutPin, 0);
    }
    else if ((micros() - time_0) >= 20064 && duty_cycle <= min_on_time) {
      time_0 = micros();
      count += 1;
      //limit++;
    }
    else if (duty_cycle > min_on_time)
      break;

    // Serial.println(limit);
    if (duty_cycle >= max_on_time) {
      count = 0;
    }
  }
  count = 0;

  while (1) {
  unsigned long curr_time = 0; 
    for (int i = 0; i <= 9 ; i++)
    {
      curr_time = millis() + NoteLength[i];
      while (1) {
        if((curr_time - millis()) > 0) {
          play_note(notes[i], m_dur);
        }
        else
          break;
        }
    }
  }
}

void play_note(unsigned long int note, unsigned long duration) {
  duration += millis();
  while ((duration - millis()) > 0 ) {
    //duty_cycle = min_on_time + count;
    duty_cycle = note;
    if ((micros() - time_0) < duty_cycle) {
      //turn signal to one
      digitalWrite(OutPin, 1);
    }
    else if ((micros() - time_0) >= duty_cycle && (micros() - time_0) < 20064) {
      //turn to zero
      digitalWrite(OutPin, 0);
    }
    else if ((micros() - time_0) >= 20064 && duty_cycle <= note) {
      time_0 = micros();
      //count += 3;
      //limit++;
    }
    else if (duty_cycle > note)
      time_0 = micros();

    // Serial.println(limit);
    if (duty_cycle >= max_on_time) {
      count = 0;
    }
  }
}


