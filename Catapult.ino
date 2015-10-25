#include <Servo.h>

Servo servos[13];

/***   Global variables   ***/
int _internal_readJoystick_array_A4_A5[3];
//bqButtons
int adc_key_val[5] ={20,50, 100, 200, 600 };
int NUM_KEYS = 5;
int adc_key_in;
int key=-1;
int oldkey=-1;

/***   Function declaration   ***/
int * readJoystick_A4_A5();
int get_key(unsigned int input);


void setup()
{
  pinMode(1,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(2,INPUT_PULLUP);

  servos[10].attach(10);
  servos[9].attach(9);
  Serial.begin(9600);
}


void loop()
{
  digitalWrite(1,LOW);
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  int *joystick=(int*)malloc(3*sizeof(int));
  joystick[0]=0;
  joystick[1]=0;
  joystick[2]=0;
  int final=0;
  int posy=90;
  int shoot=0;
  int prevjoystick=1;
  servos[9].write(posy);
  servos[10].write(shoot);
  //Bucle
  while (final == 0) {
    //Mirar joystick
    joystick=readJoystick_A4_A5();
    if (joystick[0] < 341) {
      Serial.print("Xpetit");
      Serial.print("\t");
      Serial.print(joystick[0]);
      Serial.print("\t");
      //servos[14].write(200);
      posy=posy+1;
      if (posy>=180){
        posy=180;
        }
      servos[10].write(posy);
     }else if (joystick[0] > 682) {
       Serial.print("Xgran");
       Serial.print("\t");
       Serial.print(joystick[0]);
       Serial.print("\t");
       //servos[14].write(1000);
       posy=posy-1;
      if (posy<=0){
        posy=0;
        }
        servos[10].write(posy);
     }
    if (joystick[2] == 1) {
      Serial.print("lliure");
      Serial.print("\t");
      prevjoystick=1;
     }else {
       Serial.print("apretat");
       Serial.print("\t");
       if (prevjoystick==1){
       
         prevjoystick=0;
         servos[9].write(shoot);
         if (shoot==0){
           shoot=90;
          }else{
           shoot=0;
          }
       }
     }
     //Obtencio de botons
      adc_key_in =analogRead(A3);
      key = get_key(adc_key_in);
      Serial.println(key);
      if (key != oldkey)
      {
        delay(50);
        adc_key_in = analogRead(A3);
        key = get_key(adc_key_in);
        if (key != oldkey)
        {
          oldkey = key;
          //Comprobacio de tecla premuda
          if (key >=0){
            switch(key)
            {
              case 0:
                 posy=90;
                 servos[10].write(posy);
                 if (shoot==0){
                  servos[9].write(0);
                  }
              break;
              case 1:
                 if (shoot==90){
                  servos[9].write(90);
                  shoot=0;
                  }
              break;
              case 2:
              break;
              case 3:
              break;
              case 4:
                if (shoot==0){
                  servos[9].write(0);
                  shoot=90;
                  }
              break;
            }
          }
        }
      }
   }
}

/***   Function definition   ***/
int * readJoystick_A4_A5(){
  _internal_readJoystick_array_A4_A5[0]=analogRead(A4);
  _internal_readJoystick_array_A4_A5[1]=analogRead(A5);
  _internal_readJoystick_array_A4_A5[2]=digitalRead(2);
  return _internal_readJoystick_array_A4_A5;
}
int get_key(unsigned int input)
  {
    int k;
    for (k = 0; k < NUM_KEYS; k++)
    {
      if (input < adc_key_val[k])
      {
        return k;
      }
    }
    if (k >= NUM_KEYS)k = -1;
      return k;
}
