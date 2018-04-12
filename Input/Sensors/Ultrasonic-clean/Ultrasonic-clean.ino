// Andrew R. Brown March 2018
// works up to about 5 metres (2 metres reliably)

const int trigPin = 7;//2; // add 1k resistor if using 3.3v (Teensy LC)
const int echoPin = 8;//3;
int duration, cm;
int prevDur[] = {0, 0, 0, 0};
int prevDurIndex = 0;
long ms, readTime;

void setup() {
   Serial.begin(9600);

   pinMode(trigPin, OUTPUT);
   pinMode(echoPin, INPUT);
   pinMode(13, OUTPUT); //LED indicator
   digitalWrite(13, HIGH);
}

void loop() {
   ms = millis();
   if (ms > readTime) {
     digitalWrite(trigPin, LOW);	// to ensure a clean pulse
     delayMicroseconds(2);
     digitalWrite(trigPin, HIGH); 	// send an ultrasonic pulse
     delayMicroseconds(5);
     digitalWrite(trigPin, LOW);
     duration = pulseIn(echoPin, HIGH); // measure the wait time
     if (duration < 170000) {
      prevDur[prevDurIndex] = duration;
      prevDurIndex = (prevDurIndex + 1) % 4;
      Serial.print(duration); Serial.print(" "); Serial.print(duration / 62); Serial.print(" "); 
      Serial.print(avePrev(prevDur) / 62); Serial.println("cm");
     } else {
      //Serial.println("Distant");
     }
     readTime += 200; // much quicker than 200ms seens to clag it up on Teensy LC
   }
}

/// smooth output
int avePrev(int a[]) {
  int tmp = 0;
  for (int i=0; i < 4; i++) {
    tmp += a[i];
  }
  return tmp * 0.25; 
}

