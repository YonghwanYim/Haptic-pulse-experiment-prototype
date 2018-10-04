/*
 * Project Title : Haptic Pulse ver 2 - Primary experiment for pulse duration selection.
 * Author : Yonghwan Yim
 * Experience Innovation Design Lab.
 * Department of Industrial Engineering
 * Hongik University, Seoul, Korea 
 * Final Update : 2018.10.04
 */
 
// Pulse Wide Modulation (PWM) Pin -> {3, 5, 6, 9, 10, 11}
// Vibration Motor //
#define VCC 6          // VCC pin number (PWM)
#define GND 5          // Ground pin number (PWM)

// The total number of pulses //
#define maxIndex 26

// Global Variable //
String command = "";
String splitResult[6]; // Save the result of the split function.
int vibrationStrength[5] = {0, 150, 185, 220, 255}; // The second argument to the analogWrite function.
float coefficient[maxIndex]; // A coefficient that multiplies each pulse to adjust the pulse period.
                                   
// Coefficients that multiply each pulse to match the period //
float coefficientSet1[maxIndex] = {1.9231, 3.3333, 1.9231, 3.3333, 3.3333, 3.3333, 2.2727, 2.2727, 2.1739, 3.3333,  // Duration : 2.500 second.  - Experiment 3
                                   2.7778, 4.5455, 2.7778, 3.8462, 3.1250, 2.5000, 2.7778, 2.5000, 3.3333, 3.3333,
                                   3.5714, 1.9231, 12.5000, 6.2500, 2.9412, 1.5152};                                

// An array of pointers to point to a set of coefficient //   
float * coefficientPointer[10] = {coefficientSet1};

// Function Declaration //
void Split(String sData, char cSeparator); 
void setDuration();

// Functions that implement pulses ///
void pulse1_FastInSlowOut();
void pulse2_BlinkTwice();
void pulse3_SOSBlink();
void pulse4_BlinkThrice();
void pulse5_FadeIn();
//void pulse6_FadeOut();
//void pulse7_EKG();
void pulse8_GradualBuild();
//void pulse9_Lighthouse();
void pulse10_DarkFlash();
void pulse11_BlinkDecreasing();
void pulse12_Heartbeat();
void pulse13_BlinkIncreasing();
void pulse14_Raindrops();
//void pulse15_Candle();
void pulse16_TransmissionRandomBrightness();
void pulse17_Lightning();
void pulse18_TransmissionFixedBrightness();
void pulse19_StaircaseContinuous();
//void pulse20_Twinkle();
void pulse21_StaircaseBlink();
//void pulse22_IrregularBlink();
void pulse23_BlinkSlow();
void pulse24_BlinkFast();
void pulse25_PulseSlow();
void pulse26_PulseFast();

void setup() {
  Serial.begin(9600);
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1) // Since clocks are different for each CPU,
#endif                                                   // they are defined to match the real time.
  while (!Serial);  // Wait until serial communication is available.
  delay(200);
  Serial.println();
  Serial.println("Aloha");

  // Coefficient Setting //
  for(int i = 0; i < maxIndex; i++)
    coefficient[i] = coefficientSet1[i];

  // Pin Mode Setting //
  pinMode(VCC, OUTPUT);
  pinMode(GND, OUTPUT);
  analogWrite(GND, 0);  // Vibration Motor Ground, 0V
}

void loop() {
  while(Serial.available())     // If there is a value sent to Serial.
    command = Serial.readString();
  if(!command.equals(""))  // If there is a Command String Value.
  {
    for(int i = 0; i < 6; i++)
      splitResult[i] = "\n";
    Split(command, ' ');
    
    if(splitResult[0] == "set")  // Duration Setting Command.
    {
      switch(splitResult[1].toInt())  // toInt() : "char type" -> "int type"
      {
        case 1:
          setDuration();
          Serial.println("\nThe duration is set to 2.500 second.\n"); break;        
        case 2:
          setDuration();
          Serial.println("\nThe duration is set to 2.700 second.\n"); break;
        case 3:
          setDuration();
          Serial.println("\nThe duration is set to 2.900 second.\n"); break;
        case 4:
          setDuration();
          Serial.println("\nThe duration is set to 3.100 second.\n"); break;
        case 5:
          setDuration();
          Serial.println("\nThe duration is set to 3.300 second.\n"); break;
        default:
          Serial.println("\nOnly integer input of 1~5 is allowed.\n"); break;
      }
    }

    switch(splitResult[0].toInt())  // toInt() : "char type" -> "int type"
    {
      case 1:
        Serial.print("Pulse 1 : Fast In Slow Out");
        pulse1_FastInSlowOut();
        Serial.println(" - Completed."); break;
      case 2:
        Serial.print("Pulse 2 : Blink Twice");
        pulse2_BlinkTwice();
        Serial.println(" - Completed."); break;
      case 3:
        Serial.print("Pulse 3 : SOS Blink");
        pulse3_SOSBlink();
        Serial.println(" - Completed."); break;
      case 4:
        Serial.print("Pulse 4 : Blink Thrice");
        pulse4_BlinkThrice();
        Serial.println(" - Completed."); break;
      case 5:
        Serial.print("Pulse 5 : Fade In");
        pulse5_FadeIn();
        Serial.println(" - Completed."); break;
      //case 6:
      //  Serial.print("Pulse 6 : Fade Out");
      //  pulse6_FadeOut();
      //  Serial.println(" - Completed."); break;
      //case 7:
      //  Serial.print("Pulse 7 : EKG");
      //  pulse7_EKG();
      //  Serial.println(" - Completed."); break;
      case 6:
        Serial.print("Pulse 6 : Gradual Build");
        pulse8_GradualBuild();
        Serial.println(" - Completed."); break;
      //case 9:
      //  Serial.print("Pulse 9 : Lighthouse");
      //  pulse9_Lighthouse();
      //  Serial.println(" - Completed."); break;
      case 7:
        Serial.print("Pulse 7 : Dark Flash");
        pulse10_DarkFlash();
        Serial.println(" - Completed."); break;
      case 8:
        Serial.print("Pulse 8 : Blink Decreasing");
        pulse11_BlinkDecreasing();
        Serial.println(" - Completed."); break;
      case 9:
        Serial.print("Pulse 9 : Heartbeat");
        pulse12_Heartbeat();
        Serial.println(" - Completed."); break;
      case 10:
        Serial.print("Pulse 10 : Blink Increasing");
        pulse13_BlinkIncreasing();
        Serial.println(" - Completed."); break;
      case 11:
        Serial.print("Pulse 11 : Raindrops");
        pulse14_Raindrops();
        Serial.println(" - Completed."); break;
      //case 15:
      //  Serial.print("Pulse 15 : Candle");
      //  pulse15_Candle();
      //  Serial.println(" - Completed."); break;
      case 12:
        Serial.print("Pulse 12 : Transmission, Random Brightness");
        pulse16_TransmissionRandomBrightness();
        Serial.println(" - Completed."); break;
      case 13:
        Serial.print("Pulse 13 : Lightning");
        pulse17_Lightning();
        Serial.println(" - Completed."); break;
      case 14:
        Serial.print("Pulse 14 : Transmission, Fixed Brightness");
        pulse18_TransmissionFixedBrightness();
        Serial.println(" - Completed."); break;
      case 15:
        Serial.print("Pulse 15 : Staircase Continuous");
        pulse19_StaircaseContinuous();
        Serial.println(" - Completed."); break;
      //case 20:
      //  Serial.print("Pulse 20 : Twinkle");
      //  pulse20_Twinkle();
      //  Serial.println(" - Completed."); break;
      case 16:
        Serial.print("Pulse 16 : Staircase Blink");
        pulse21_StaircaseBlink();
        Serial.println(" - Completed."); break;
      //case 22:
      //  Serial.print("Pulse 22 : Irregular Blink");
      //  pulse22_IrregularBlink();
      //  Serial.println(" - Completed."); break;
      case 17:
        Serial.print("Pulse 17 : Blink Slow");
        pulse23_BlinkSlow();
        Serial.println(" - Completed."); break;
      case 18:
        Serial.print("Pulse 18 : Blink Fast");
        pulse24_BlinkFast();
        Serial.println(" - Completed."); break;
      case 19:
        Serial.print("Pulse 19 : Pulse Slow");
        pulse25_PulseSlow();
        Serial.println(" - Completed."); break;
      case 20:
        Serial.print("Pulse 20 : Pulse Fast");
        pulse26_PulseFast();
        Serial.println(" - Completed."); break;
    }
  }
  command = ""; // command reset.
}

void Split(String sData, char cSeparator)
{  
  int nGetIndex = 0 ;
  int msgCount = 0;
  String sTemp = "";    // Temporary storage.
  String sCopy = sData; // Copy original.

  while(true)
  {
    // Find separator.
    nGetIndex = sCopy.indexOf(cSeparator);

    // Is there a returned index?
    if(-1 != nGetIndex)
    {
      // Loading data.
      sTemp = sCopy.substring(0, nGetIndex); // Copy from 0 to nGetIndex.
      splitResult[msgCount] = sTemp;
      msgCount++;
    
      // Cut the data.
      sCopy = sCopy.substring(nGetIndex + 1);
    }
    else
    {
      // If there is no separator, finish.
      splitResult[msgCount] = sCopy;
      break;
    }
  }
}

void setDuration()
{
   for(int i = 0; i < maxIndex; i++)
     {
        coefficient[i] = coefficientPointer[splitResult[1].toInt() - 1][i];
        //Serial.print("Pulse "); Serial.print(i + 1); Serial.print(" Duration : "); Serial.println(defaultDuration[i] * coefficient[i]); // Print duration.
     }
}

////////////////////////
//// Pulse Function ////
////////////////////////

void pulse1_FastInSlowOut()
{
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[0] * 50);
  analogWrite(VCC, vibrationStrength[1]);
  delay(coefficient[0] * 50);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[0] * 50);
  analogWrite(VCC, vibrationStrength[3]);
  delay(coefficient[0] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[0] * 50);
  analogWrite(VCC, vibrationStrength[3]);
  delay(coefficient[0] * 100);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[0] * 100);
  analogWrite(VCC, vibrationStrength[1]);
  delay(coefficient[0] * 100);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[0] * 150);
  analogWrite(VCC, vibrationStrength[1]);
  delay(coefficient[0] * 50);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[0] * 50);
  analogWrite(VCC, vibrationStrength[3]);
  delay(coefficient[0] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[0] * 50);
  analogWrite(VCC, vibrationStrength[3]);
  delay(coefficient[0] * 100);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[0] * 100);
  analogWrite(VCC, vibrationStrength[1]);
  delay(coefficient[0] * 100);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[0] * 100);
}

void pulse2_BlinkTwice()
{
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[1] * 300);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[1] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[1] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[1] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[1] * 300);
}

void pulse3_SOSBlink()
{
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[2] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[2] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[2] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[2] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[2] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[2] * 50); 
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[2] * 100);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[2] * 100);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[2] * 100);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[2] * 100);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[2] * 100);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[2] * 100);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[2] * 100); 
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[2] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[2] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[2] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[2] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[2] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[2] * 50);
}

void pulse4_BlinkThrice()
{
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[3] * 250);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[3] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[3] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[3] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[3] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[3] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[3] * 250);
}

void pulse5_FadeIn()
{
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[4] * 300);
  analogWrite(VCC, vibrationStrength[1]);
  delay(coefficient[4] * 50);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[4] * 50);
  analogWrite(VCC, vibrationStrength[3]);
  delay(coefficient[4] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[4] * 100);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[4] * 200);
}
/*
void pulse6_FadeOut()
{
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[5] * 200);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[5] * 100);
  analogWrite(VCC, vibrationStrength[3]);
  delay(coefficient[5] * 50);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[5] * 50);
  analogWrite(VCC, vibrationStrength[1]);
  delay(coefficient[5] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[5] * 300);
}

void pulse7_EKG()
{
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[6] * 100);
  analogWrite(VCC, vibrationStrength[3]);
  delay(coefficient[6] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[6] * 50);
  analogWrite(VCC, vibrationStrength[3]);
  delay(coefficient[6] * 50);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[6] * 50);
  analogWrite(VCC, vibrationStrength[1]);
  delay(coefficient[6] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[6] * 50);
  analogWrite(VCC, vibrationStrength[1]);
  delay(coefficient[6] * 50);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[6] * 200);
  analogWrite(VCC, vibrationStrength[3]);
  delay(coefficient[6] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[6] * 50);
  analogWrite(VCC, vibrationStrength[3]);
  delay(coefficient[6] * 50);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[6] * 50);
  analogWrite(VCC, vibrationStrength[1]);
  delay(coefficient[6] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[6] * 50);
  analogWrite(VCC, vibrationStrength[1]);
  delay(coefficient[6] * 50);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[6] * 100);
  analogWrite(VCC, vibrationStrength[0]);
}
*/
void pulse8_GradualBuild()
{
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[7] * 100);
  analogWrite(VCC, vibrationStrength[1]);
  delay(coefficient[7] * 100);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[7] * 100);
  analogWrite(VCC, vibrationStrength[3]);
  delay(coefficient[7] * 100);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[7] * 100);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[7] * 100);
  analogWrite(VCC, vibrationStrength[1]);
  delay(coefficient[7] * 100);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[7] * 100);
  analogWrite(VCC, vibrationStrength[3]);
  delay(coefficient[7] * 100);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[7] * 100);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[7] * 100);
}
/*
void pulse9_Lighthouse()
{
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[8] * 50);
  analogWrite(VCC, vibrationStrength[1]);
  delay(coefficient[8] * 100);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[8] * 50); 
  analogWrite(VCC, vibrationStrength[3]);
  delay(coefficient[8] * 50); 
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[8] * 50);
  analogWrite(VCC, vibrationStrength[3]);
  delay(coefficient[8] * 50); 
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[8] * 50);
  analogWrite(VCC, vibrationStrength[1]);
  delay(coefficient[8] * 100);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[8] * 100);
  analogWrite(VCC, vibrationStrength[1]);
  delay(coefficient[8] * 100);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[8] * 50); 
  analogWrite(VCC, vibrationStrength[3]);
  delay(coefficient[8] * 50); 
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[8] * 50);
  analogWrite(VCC, vibrationStrength[3]);
  delay(coefficient[8] * 50); 
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[8] * 50);
  analogWrite(VCC, vibrationStrength[1]);
  delay(coefficient[8] * 100);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[8] * 100);
}
*/
void pulse10_DarkFlash()
{
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[9] * 200);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[9] * 150);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[9] * 50);  
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[9] * 150);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[9] * 200);
}

void pulse11_BlinkDecreasing()
{
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[10] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[10] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[10] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[10] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[10] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[10] * 100);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[10] * 100);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[10] * 100);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[10] * 100);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[10] * 150);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[10] * 100);
}

void pulse12_Heartbeat()
{
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[11] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[11] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[11] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[11] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[11] * 150);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[11] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[11] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[11] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[11] * 50);
}

void pulse13_BlinkIncreasing()
{
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[12] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[12] * 150);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[12] * 100);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[12] * 100);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[12] * 100);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[12] * 100);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[12] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[12] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[12] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[12] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[12] * 100);
}

void pulse14_Raindrops()
{
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[13] * 50);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[13] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[13] * 50);
  analogWrite(VCC, vibrationStrength[1]);
  delay(coefficient[13] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[13] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[13] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[13] * 50);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[13] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[13] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[13] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[13] * 50);
  analogWrite(VCC, vibrationStrength[1]);
  delay(coefficient[13] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[13] * 50);
}
/*
void pulse15_Candle()
{
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[14] * 50);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[14] * 100);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[14] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[14] * 100);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[14] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[14] * 50);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[14] * 50);  
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[14] * 50);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[14] * 50);  
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[14] * 100);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[14] * 50);  
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[14] * 50);  
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[14] * 50);
  analogWrite(VCC, vibrationStrength[0]);
}
*/
void pulse16_TransmissionRandomBrightness()
{
  analogWrite(VCC, vibrationStrength[3]);
  delay(coefficient[15] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[15] * 100);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[15] * 100);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[15] * 100);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[15] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[15] * 50);
  analogWrite(VCC, vibrationStrength[1]);
  delay(coefficient[15] * 100);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[15] * 100);
  analogWrite(VCC, vibrationStrength[3]);
  delay(coefficient[15] * 100);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[15] * 100);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[15] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[15] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[15] * 50);
  analogWrite(VCC, vibrationStrength[0]);
}

void pulse17_Lightning()
{
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[16] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[16] * 100);
  analogWrite(VCC, vibrationStrength[1]);
  delay(coefficient[16] * 50);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[16] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[16] * 50);
  analogWrite(VCC, vibrationStrength[1]);
  delay(coefficient[16] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[16] * 150);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[16] * 100);
  analogWrite(VCC, vibrationStrength[1]);
  delay(coefficient[16] * 50);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[16] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[16] * 50);
  analogWrite(VCC, vibrationStrength[1]);
  delay(coefficient[16] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[16] * 100);
}

void pulse18_TransmissionFixedBrightness()
{
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[17] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[17] * 100);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[17] * 100);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[17] * 100);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[17] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[17] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[17] * 100);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[17] * 100);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[17] * 100);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[17] * 100);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[17] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[17] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[17] * 50);
  analogWrite(VCC, vibrationStrength[0]);
}

void pulse19_StaircaseContinuous()
{
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[18] * 50);
  analogWrite(VCC, vibrationStrength[1]);
  delay(coefficient[18] * 150);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[18] * 150);
  analogWrite(VCC, vibrationStrength[3]);
  delay(coefficient[18] * 150);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[18] * 150);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[18] * 100);
}
/*
void pulse20_Twinkle()
{
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[19] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[19] * 50);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[19] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[19] * 50);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[19] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[19] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[19] * 50);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[19] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[19] * 50);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[19] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[19] * 100);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[19] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[19] * 100);
}
*/
void pulse21_StaircaseBlink()
{
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[20] * 50);
  analogWrite(VCC, vibrationStrength[1]);
  delay(coefficient[20] * 100);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[20] * 50);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[20] * 100);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[20] * 50);
  analogWrite(VCC, vibrationStrength[3]);
  delay(coefficient[20] * 100);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[20] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[20] * 100);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[20] * 100);
}
/*
void pulse22_IrregularBlink()
{
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[21] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[21] * 100);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[21] * 50);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[21] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[21] * 50);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[21] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[21] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[21] * 150);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[21] * 100);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[21] * 100);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[21] * 50);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[21] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[21] * 50);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[21] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[21] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[21] * 150);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[21] * 100);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[21] * 50);
  analogWrite(VCC, vibrationStrength[0]);
}
*/

void pulse23_BlinkSlow()
{
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[22] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[22] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[22] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[22] * 50);
}

void pulse24_BlinkFast()
{
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[23] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[23] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[23] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[23] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[23] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[23] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[23] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[23] * 50);
}

void pulse25_PulseSlow()
{
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[24] * 50);
  analogWrite(VCC, vibrationStrength[3]);
  delay(coefficient[24] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[24] * 50);
  analogWrite(VCC, vibrationStrength[3]);
  delay(coefficient[24] * 50);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[24] * 50);
  analogWrite(VCC, vibrationStrength[1]);
  delay(coefficient[24] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[24] * 50);
  analogWrite(VCC, vibrationStrength[1]);
  delay(coefficient[24] * 50);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[24] * 50);
  analogWrite(VCC, vibrationStrength[3]);
  delay(coefficient[24] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[24] * 50);
  analogWrite(VCC, vibrationStrength[3]);
  delay(coefficient[24] * 50);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[24] * 50);
  analogWrite(VCC, vibrationStrength[1]);
  delay(coefficient[24] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[24] * 50);
  analogWrite(VCC, vibrationStrength[1]);
  delay(coefficient[24] * 50);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[24] * 50);
  analogWrite(VCC, vibrationStrength[0]); // end.
}

void pulse26_PulseFast()
{
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[25] * 50);
  analogWrite(VCC, vibrationStrength[3]);
  delay(coefficient[25] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[25] * 50);
  analogWrite(VCC, vibrationStrength[3]);
  delay(coefficient[25] * 50);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[25] * 50);
  analogWrite(VCC, vibrationStrength[1]);
  delay(coefficient[25] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[25] * 50);
  analogWrite(VCC, vibrationStrength[1]);
  delay(coefficient[25] * 50);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[25] * 50);
  analogWrite(VCC, vibrationStrength[3]);
  delay(coefficient[25] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[25] * 50);
  analogWrite(VCC, vibrationStrength[3]);
  delay(coefficient[25] * 50);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[25] * 50);
  analogWrite(VCC, vibrationStrength[1]);
  delay(coefficient[25] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[25] * 50);
  analogWrite(VCC, vibrationStrength[1]);
  delay(coefficient[25] * 50);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[25] * 50);
  analogWrite(VCC, vibrationStrength[3]);
  delay(coefficient[25] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[25] * 50);
  analogWrite(VCC, vibrationStrength[3]);
  delay(coefficient[25] * 50);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[25] * 50);
  analogWrite(VCC, vibrationStrength[1]);
  delay(coefficient[25] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[25] * 50);
  analogWrite(VCC, vibrationStrength[1]);
  delay(coefficient[25] * 50);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[25] * 50);
  analogWrite(VCC, vibrationStrength[3]);
  delay(coefficient[25] * 50);
  analogWrite(VCC, vibrationStrength[4]);
  delay(coefficient[25] * 50);
  analogWrite(VCC, vibrationStrength[3]);
  delay(coefficient[25] * 50);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[25] * 50);
  analogWrite(VCC, vibrationStrength[1]);
  delay(coefficient[25] * 50);
  analogWrite(VCC, vibrationStrength[0]);
  delay(coefficient[25] * 50);
  analogWrite(VCC, vibrationStrength[1]);
  delay(coefficient[25] * 50);
  analogWrite(VCC, vibrationStrength[2]);
  delay(coefficient[25] * 50);
  analogWrite(VCC, vibrationStrength[0]); // end.
}
