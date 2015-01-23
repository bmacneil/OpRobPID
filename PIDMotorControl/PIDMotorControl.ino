/* Encoder Library - Basic Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */

#include <Encoder.h>

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder Enc_left(2, 3);    //LEFT ENCODER
Encoder Enc_right(18, 19);  //RIGHT ENCODER
//   avoid using pins with LEDs attached

int INA_L = 39;
int ENA_L = 41;
int PWM_L = 6;
int ENB_L = 43;
int INB_L = 45;

int INA_R = 47;
int ENA_R = 49;
int PWM_R = 7;
int ENB_R = 51;
int INB_R = 53; 


long x1_left = 0;
long x2_left = 0;

long x1_right = 0;
long x2_right = 0;


int dx_left = 0;
int dx_right = 0;

int PWM_Desired = 25;
int pwm_left = 0;
int pwm_right = 0;


void goForward()
{
      analogWrite(PWM_L, 175);
      digitalWrite(INA_L, LOW);
      digitalWrite(INB_L, HIGH);
      digitalWrite(ENA_L, HIGH);
      digitalWrite(ENB_L, HIGH);

      
      analogWrite(PWM_R, 175);
      digitalWrite(INA_R, HIGH);
      digitalWrite(INB_R, LOW);
      digitalWrite(ENA_R, HIGH);
      digitalWrite(ENB_R, HIGH);
      
 
}

void Feedback()
{
  analogWrite(PWM_L, pwm_left);
  analogWrite(PWM_R, pwm_right);
}
void setup() {
  
  pinMode(INA_L, OUTPUT);
  pinMode(INB_L, OUTPUT);
  pinMode(PWM_L, OUTPUT);
  pinMode(ENA_L, OUTPUT); 
  pinMode(ENB_L, OUTPUT);
  
  pinMode(INA_R, OUTPUT);
  pinMode(INB_R, OUTPUT);
  pinMode(PWM_R, OUTPUT);
  pinMode(ENA_R, OUTPUT); 
  pinMode(ENB_R, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("Basic Encoder Test:");
  goForward();
}

long old_left  = 100;
long old_right = 100;

int range_limit(int i) {
  if(i > 255)
    i = 255;
   else if(i < 0)
     i =0;
   return i;
}

void loop() {

  
  long new_left = Enc_left.read();
  long new_right = Enc_right.read();
  
  if ( new_left != old_left ) 
  {
    x1_left = old_left; 
    x2_left = new_left;
    old_left = new_left;
  }
  
  if ( new_right != old_right ) 
  {
    x1_right = old_right; 
    x2_right = new_right;
    old_right = new_right;
  }
  

  dx_left = int(x2_left - x1_left);
  dx_right = int(x2_right - x1_right);
  
  pwm_left += (PWM_Desired - dx_left) / 10;
  pwm_right += (PWM_Desired - dx_right) / 10; 
  
  pwm_left = range_limit(pwm_left);
  pwm_right = range_limit(pwm_right);
  
  Feedback();
  Serial.print(dx_left);
  Serial.print("/");
  Serial.print(dx_right);
  Serial.print("\n");
}
