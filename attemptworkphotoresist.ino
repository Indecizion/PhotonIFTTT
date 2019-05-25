
int led = D0; 

int photoresistor = A0; 

int power = A5; 

int analogvalue; 

#define LIGHT_LEVEL_LOW 800 
#define LIGHT_LEVEL_HIGH 150
#define THRESHOLD_SENSITIVITY 50 

void setup() {

    pinMode(led,OUTPUT); 
    pinMode(photoresistor,INPUT);  
    pinMode(power,OUTPUT); 
    digitalWrite(power,HIGH);

    Particle.variable("analogvalue", &analogvalue, INT);
    Particle.function("led" ,ledToggle);

}



void loop()
{

analogvalue = analogRead(photoresistor);

analogWrite(led,analogvalue);
            
  
   if (analogvalue >= LIGHT_LEVEL_LOW) 
        { 
            Particle.publish("light-level-changed", "dark");
        } 
      
    else if (analogvalue <= LIGHT_LEVEL_HIGH)
        {
            Particle.publish("light-level-changed", "high");
        }

}
// Finally, we will write out our ledToggle function, which is referenced by the Particle.function() called "led"

int ledToggle(String command) {

    if (command=="on") {
        digitalWrite(led,HIGH);
        return 1;
    }
    else if (command=="off") {
        digitalWrite(led,LOW);
        return 0;
    }
    else {
        return -1;
    }
}