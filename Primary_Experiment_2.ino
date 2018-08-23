/*
 * Project Title : Haptic Pulse ver 2 - Primary experiment for pulse duration selection.
 * Author : Yonghwan Yim
 * Experience Innovation Design Lab.
 * Department of Industrial Engineering
 * Hongik University, Seoul, Korea 
 * Final Update : 2018.08.23
 */
 
// Pulse Wide Modulation (PWM) Pin -> {3, 5, 6, 9, 10, 11}
// Vibration Motor //
#define VCC 6          // VCC pin number (PWM)
#define GND 5          // Ground pin number (PWM)

// The total number of pulses //
#define maxIndex 22 

// Global Variable //
String command = "";
String splitResult[6]; // Save the result of the split function.
int vibrationStrength[5] = {0, 150, 185, 220, 255}; // The second argument to the analogWrite function.
float coefficient[maxIndex]; // A coefficient that multiplies each pulse to adjust the pulse period.
float defaultDuration[maxIndex] = {1.30, 0.75, 1.30, 0.75, 0.75, 0.75, 1.10, 1.10, 1.15, 0.75,
                                   0.90, 0.55, 0.90, 0.65, 0.80, 1.00, 0.90, 1.00, 0.75, 0.75,
                                   0.70, 1.30};
                                   
// Coefficients that multiply each pulse to match the period //
/*
float coefficientSet1[maxIndex] = {1.0000, 1.7333, 1.0000, 1.7333, 1.7333, 1.7333, 1.1818, 1.1818, 1.1304, 1.7333,  // Duration : 1.300 second.  - Experiment 1
                                   1.4444, 2.3636, 1.4444, 2.0000, 1.6250, 1.3000, 1.4444, 1.3000, 1.7333, 1.7333,
                                   1.8571, 1.0000};
float coefficientSet2[maxIndex] = {1.6154, 2.8000, 1.6154, 2.8000, 2.8000, 2.8000, 1.9091, 1.9091, 1.8261, 2.8000,  // Duration : 2.100 secnod.  - Experiment 1
                                   2.3333, 3.8182, 2.3333, 3.2308, 2.6250, 2.1000, 2.3333, 2.1000, 2.8000, 2.8000,
                                   3.0000, 1.6154};
float coefficientSet3[maxIndex] = {2.2308, 3.8667, 2.2308, 3.8667, 3.8667, 3.8667, 2.6364, 2.6364, 2.5217, 3.8667,  // Duration : 2.900 second.  - Experiment 1
                                   3.2222, 5.2727, 3.2222, 4.4615, 3.6250, 2.9000, 3.2222, 2.9000, 3.8667, 3.8667,
                                   4.1429, 2.2308};
float coefficientSet4[maxIndex] = {2.8462, 4.9333, 2.8462, 4.9333, 4.9333, 4.9333, 3.3636, 3.3636, 3.2174, 4.9333,  // Duration : 3.700 second.  - Experiment 1
                                   4.1111, 6.7273, 4.1111, 5.6923, 4.6250, 3.7000, 4.1111, 3.7000, 4.9333, 4.9333,
                                   5.2857, 2.8462};
float coefficientSet5[maxIndex] = {3.4615, 6.0000, 3.4615, 6.0000, 6.0000, 6.0000, 4.0909, 4.0909, 3.9130, 6.0000,  // Duration : 4.500 second.  - Experiment 1
                                   5.0000, 8.1818, 5.0000, 6.9231, 5.6250, 4.5000, 5.0000, 4.5000, 6.0000, 6.0000,
                                   6.4286, 3.4615};
*/
float coefficientSet1[maxIndex] = {1.9231, 3.3333, 1.9231, 3.3333, 3.3333, 3.3333, 2.2727, 2.2727, 2.1739, 3.3333,  // Duration : 2.500 second.  - Experiment 2
                                   2.7778, 4.5455, 2.7778, 3.8462, 3.1250, 2.5000, 2.7778, 2.5000, 3.3333, 3.3333,
                                   3.5714, 1.9231};                                
float coefficientSet2[maxIndex] = {2.0769, 3.6000, 2.0769, 3.6000, 3.6000, 3.6000, 2.4545, 2.4545, 2.3478, 3.6000,  // Duration : 2.700 second.  - Experiment 2
                                   3.0000, 4.9091, 3.0000, 4.1538, 3.3750, 2.7000, 3.0000, 2.7000, 3.6000, 3.6000,
                                   3.8571, 2.0769};                     
float coefficientSet3[maxIndex] = {2.2308, 3.8667, 2.2308, 3.8667, 3.8667, 3.8667, 2.6364, 2.6364, 2.5217, 3.8667,  // Duration : 2.900 second.  - Experiment 2
                                   3.2222, 5.2727, 3.2222, 4.4615, 3.6250, 2.9000, 3.2222, 2.9000, 3.8667, 3.8667,
                                   4.1429, 2.2308};              
float coefficientSet4[maxIndex] = {2.3846, 4.1333, 2.3846, 4.1333, 4.1333, 4.1333, 2.8182, 2.8182, 2.6957, 4.1333,  // Duration : 3.100 second.  - Experiment 2
                                   3.4444, 5.6364, 3.4444, 4.7692, 3.8750, 3.1000, 3.4444, 3.1000, 4.1333, 4.1333,
                                   4.4286, 2.3846};
float coefficientSet5[maxIndex] = {2.5385, 4.4000, 2.5385, 4.4000, 4.4000, 4.4000, 3.0000, 3.0000, 2.8696, 4.4000,  // Duration : 3.300 second.  - Experiment 2
                                   3.6667, 6.0000, 3.6667, 5.0769, 4.1250, 3.3000, 3.6667, 3.3000, 4.4000, 4.4000,
                                   4.7143, 2.5385};

// An array of pointers to point to a set of coefficient //   
float * coefficientPointer[10] = {coefficientSet1, coefficientSet2, coefficientSet3, coefficientSet4, coefficientSet5};

// Function Declaration //
void Split(String sData, char cSeparator); 
void setDuration();

// Functions that implement pulses ///
void pulse1_FastInSlowOut();
void pulse2_BlinkTwice();
void pulse3_SOSBlink();
void pulse4_BlinkThrice();
void pulse5_FadeIn();
void pulse6_FadeOut();
void pulse7_EKG();
void pulse8_GradualBuild();
void pulse9_Lighthouse();
void pulse10_DarkFlash();
void pulse11_BlinkDecreasing();
void pulse12_Heartbeat();
void pulse13_BlinkIncreasing();
void pulse14_Raindrops();
void pulse15_Candle();
void pulse16_TransmissionRandomBrightness();
void pulse17_Lightning();
void pulse18_TransmissionFixedBrightness();
void pulse19_StaircaseContinuous();
void pulse20_Twinkle();
void pulse21_StaircaseBlink();
void pulse22_IrregularBlink();


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
    coefficient[i] = 1.0;

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
      case 6:
        Serial.print("Pulse 6 : Fade Out");
        pulse6_FadeOut();
        Serial.println(" - Completed."); break;
      case 7:
        Serial.print("Pulse 7 : EKG");
        pulse7_EKG();
        Serial.println(" - Completed."); break;
      case 8:
        Serial.print("Pulse 8 : Gradual Build");
        pulse8_GradualBuild();
        Serial.println(" - Completed."); break;
      case 9:
        Serial.print("Pulse 9 : Lighthouse");
        pulse9_Lighthouse();
        Serial.println(" - Completed."); break;
      case 10:
        Serial.print("Pulse 10 : Dark Flash");
        pulse10_DarkFlash();
        Serial.println(" - Completed."); break;
      case 11:
        Serial.print("Pulse 11 : Blink Decreasing");
        pulse11_BlinkDecreasing();
        Serial.println(" - Completed."); break;
      case 12:
        Serial.print("Pulse 12 : Heartbeat");
        pulse12_Heartbeat();
        Serial.println(" - Completed."); break;
      case 13:
        Serial.print("Pulse 13 : Blink Increasing");
        pulse13_BlinkIncreasing();
        Serial.println(" - Completed."); break;
      case 14:
        Serial.print("Pulse 14 : Raindrops");
        pulse14_Raindrops();
        Serial.println(" - Completed."); break;
      case 15:
        Serial.print("Pulse 15 : Candle");
        pulse15_Candle();
        Serial.println(" - Completed."); break;
      case 16:
        Serial.print("Pulse 16 : Transmission, Random Brightness");
        pulse16_TransmissionRandomBrightness();
        Serial.println(" - Completed."); break;
      case 17:
        Serial.print("Pulse 17 : Lightning");
        pulse17_Lightning();
        Serial.println(" - Completed."); break;
      case 18:
        Serial.print("Pulse 18 : Transmission, Fixed Brightness");
        pulse18_TransmissionFixedBrightness();
        Serial.println(" - Completed."); break;
      case 19:
        Serial.print("Pulse 19 : Staircase Continuous");
        pulse19_StaircaseContinuous();
        Serial.println(" - Completed."); break;
      case 20:
        Serial.print("Pulse 20 : Twinkle");
        pulse20_Twinkle();
        Serial.println(" - Completed."); break;
      case 21:
        Serial.print("Pulse 21 : Staircase Blink");
        pulse21_StaircaseBlink();
        Serial.println(" - Completed."); break;
      case 22:
        Serial.print("Pulse 22 : Irregular Blink");
        pulse22_IrregularBlink();
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

