// PROFIELWERKSTUK - MIDI-CONTROLLER 
// Last Modified: 3-12-2018 ~ Rens Rutten

#include <Bounce.h>

// ---- MENU CODE ----
const int menuPot = A12;
int mode;


// ---- BUTTONS CODE ----
Bounce buttonPLAY = Bounce(5, 50);
Bounce buttonSTOP = Bounce(4, 50);
Bounce buttonRECORD = Bounce(13, 50);
Bounce buttonREPEAT = Bounce(14, 50);
int previousStateRECORD = 0;
int previousStateREPEAT = 0;

// ---- POTENTIOMETER CODE ----
const int selectPins[3] = {10,11,12};
const int zPin = A5;
const int CCmessage[8] = {14,15,16,17,18,19,20,21};

elapsedMillis msec = 0;

 
// ---- BUTTON PAD CODE ----
#define NUM_LED_COLUMNS (4)
#define NUM_LED_ROWS (4)
#define NUM_BTN_COLUMNS (4)
#define NUM_BTN_ROWS (4)
#define NUM_COLORS (1)
#define MAX_DEBOUNCE (1)

// Global variables
static bool LED_buffer[NUM_LED_COLUMNS][NUM_LED_ROWS];

static const uint8_t btncolumnpins[NUM_BTN_COLUMNS] = {3, 2, 1, 0}; // {SWT-GND 1,2,3,4}
static const uint8_t btnrowpins[NUM_BTN_ROWS]       = {9, 8, 7, 6}; // {SWITCH 1,2,3,4}
static const uint8_t ledcolumnpins[NUM_LED_COLUMNS] = {18, 17, 16, 15}; // {LED-GND 1,2,3,4}
static const uint8_t colorpins[NUM_LED_ROWS]        = {23, 22, 21, 20}; // {BLUE 1,2,3,4}

static int8_t debounce_count[NUM_BTN_COLUMNS][NUM_BTN_ROWS];

static void setuppins()
         {
          uint8_t i;
          
          for (i = 0; i < NUM_LED_COLUMNS; i++)
          {
            pinMode(ledcolumnpins[i], OUTPUT);
        
            // with nothing selected by default
            digitalWrite(ledcolumnpins[i], HIGH);
          }
       
          for (i = 0; i < NUM_BTN_COLUMNS; i++)
          {
            pinMode(btncolumnpins[i], OUTPUT);

            digitalWrite(btncolumnpins[i], HIGH);
          }
        
          for (i = 0; i < NUM_BTN_ROWS; i++)
          {
            pinMode(btnrowpins[i], INPUT_PULLUP);
          }
        
          for (i = 0; i < NUM_LED_ROWS; i++)
          {
            pinMode(colorpins[i], OUTPUT);
            digitalWrite(colorpins[i], LOW);
          }
        
          for (uint8_t i = 0; i < NUM_BTN_COLUMNS; i++)
          {
            for (uint8_t j = 0; j < NUM_BTN_ROWS; j++)
            {
              debounce_count[i][j] = 0;
            }
          }
        }

static void scanNOTE()
      {
        static uint8_t current = 0;
        uint8_t val;
        uint8_t i, j;
      
        digitalWrite(btncolumnpins[current], LOW);
        digitalWrite(ledcolumnpins[current], LOW);
        
        for (i = 0; i < NUM_LED_ROWS; i++)
        {
          if (LED_buffer[current][i])
          {
            digitalWrite(colorpins[i], HIGH);
          }
        }
      
        delay(1);

        for ( j = 0; j < NUM_BTN_ROWS; j++)
        {
          val = digitalRead(btnrowpins[j]);
    
          if (val == LOW)
          {
            if ( debounce_count[current][j] < MAX_DEBOUNCE)
            {
              debounce_count[current][j]++;
              if ( debounce_count[current][j] == MAX_DEBOUNCE )
              {
                Serial.print("Key Down ");
                Serial.println((current * NUM_BTN_ROWS) + j);
        
                // (current * NUM_BTN_ROWS) + j   = 0 t/m 15
                /* {3 = C2 , 7 = C#2, 11 = D2 ,  15 = D#2, 
                    2 = G#1, 6 = A1 , 10 = A#1,  14 = B  , 
                    1 = E1 , 5 = F1 , 9 = F#1 ,  13 = G1 , 
                    0 = C1 , 4 = C#1, 8 = D1  ,  12 = D#1} */
                
                if ( (current * NUM_BTN_ROWS) + j == 0) {usbMIDI.sendNoteOn(36, 99, 1);}  // 60 = C4}   
                if ( (current * NUM_BTN_ROWS) + j == 4) {usbMIDI.sendNoteOn(37, 99, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 8) {usbMIDI.sendNoteOn(38, 99, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 12) {usbMIDI.sendNoteOn(39, 99, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 1) {usbMIDI.sendNoteOn(40, 99, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 5) {usbMIDI.sendNoteOn(41, 99, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 9) {usbMIDI.sendNoteOn(42, 99, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 13) {usbMIDI.sendNoteOn(43, 99, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 2) {usbMIDI.sendNoteOn(44, 99, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 6) {usbMIDI.sendNoteOn(45, 99, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 10) {usbMIDI.sendNoteOn(46, 99, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 14) {usbMIDI.sendNoteOn(47, 99, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 3) {usbMIDI.sendNoteOn(48, 99, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 7) {usbMIDI.sendNoteOn(49, 99, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 11) {usbMIDI.sendNoteOn(50, 99, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 15) {usbMIDI.sendNoteOn(51, 99, 1);}

                LED_buffer[current][j] =! LED_buffer[current][j];
                delay(2);
              }
            }
          }
          else
          {
            if ( debounce_count[current][j] > 0)
            {
              debounce_count[current][j]--;
              if ( debounce_count[current][j] == 0 )
              {
                Serial.print("Key Up ");
                Serial.println((current * NUM_BTN_ROWS) + j);
      
                if ( (current * NUM_BTN_ROWS) + j == 0) {usbMIDI.sendNoteOff(36, 0, 1);}  // 36 = C2}   
                if ( (current * NUM_BTN_ROWS) + j == 4) {usbMIDI.sendNoteOff(37, 0, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 8) {usbMIDI.sendNoteOff(38, 0, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 12) {usbMIDI.sendNoteOff(39, 0, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 1) {usbMIDI.sendNoteOff(40, 0, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 5) {usbMIDI.sendNoteOff(41, 0, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 9) {usbMIDI.sendNoteOff(42, 0, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 13) {usbMIDI.sendNoteOff(43, 0, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 2) {usbMIDI.sendNoteOff(44, 0, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 6) {usbMIDI.sendNoteOff(45, 0, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 10) {usbMIDI.sendNoteOff(46, 0, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 14) {usbMIDI.sendNoteOff(47, 0, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 3) {usbMIDI.sendNoteOff(48, 0, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 7) {usbMIDI.sendNoteOff(49, 0, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 11) {usbMIDI.sendNoteOff(50, 0, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 15) {usbMIDI.sendNoteOff(51, 0, 1);}
                LED_buffer[current][j] =! LED_buffer[current][j];
              }
            }
          }
        }
      
        delay(1);
      
        digitalWrite(btncolumnpins[current], HIGH);
        digitalWrite(ledcolumnpins[current], HIGH);
      
        for (i = 0; i < NUM_LED_ROWS; i++)
        {
          digitalWrite(colorpins[i], LOW);
        }
      
        current++;
        if (current >= NUM_LED_COLUMNS)
        {
          current = 0;
        }
      
      }


static void scanCC()
     {
        static uint8_t current = 0;
        uint8_t val;
        uint8_t i, j;
      
        digitalWrite(btncolumnpins[current], LOW);
        digitalWrite(ledcolumnpins[current], LOW);
      
        for (i = 0; i < NUM_LED_ROWS; i++)
        {
          if (LED_buffer[current][i])
          {
            digitalWrite(colorpins[i], HIGH);
          }
        }
      
        delay(1);

        for ( j = 0; j < NUM_BTN_ROWS; j++)
        {
          val = digitalRead(btnrowpins[j]);
    
          if (val == LOW)
          {
            if ( debounce_count[current][j] < MAX_DEBOUNCE)
            {
              debounce_count[current][j]++;
              if ( debounce_count[current][j] == MAX_DEBOUNCE )
              {
                Serial.print("Key Down ");
                Serial.println((current * NUM_BTN_ROWS) + j);
        
                // (current * NUM_BTN_ROWS) + j   = 0 t/m 15

                if ( (current * NUM_BTN_ROWS) + j == 0) {usbMIDI.sendNoteOn(52, 99, 1);}     
                if ( (current * NUM_BTN_ROWS) + j == 4) {usbMIDI.sendNoteOn(53, 99, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 8) {usbMIDI.sendNoteOn(54, 99, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 12) {usbMIDI.sendNoteOn(55, 99, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 1) {usbMIDI.sendNoteOn(56, 99, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 5) {usbMIDI.sendNoteOn(57, 99, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 9) {usbMIDI.sendNoteOn(58, 99, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 13) {usbMIDI.sendNoteOn(59, 99, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 2) {usbMIDI.sendNoteOn(60, 99, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 6) {usbMIDI.sendNoteOn(61, 99, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 10) {usbMIDI.sendNoteOn(62, 99, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 14) {usbMIDI.sendNoteOn(63, 99, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 3) {usbMIDI.sendNoteOn(64, 99, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 7) {usbMIDI.sendNoteOn(65, 99, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 11) {usbMIDI.sendNoteOn(66, 99, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 15) {usbMIDI.sendNoteOn(67, 99, 1);}
                
                LED_buffer[current][j] =! LED_buffer[current][j];
                
                delay(2);
              }
            }
          }
          else
          {
            if ( debounce_count[current][j] > 0)
            {
              debounce_count[current][j]--;
              if ( debounce_count[current][j] == 0 )
              {
                Serial.print("Key Up ");
                Serial.println((current * NUM_BTN_ROWS) + j);
      
                if ( (current * NUM_BTN_ROWS) + j == 0) {usbMIDI.sendNoteOn(52, 0, 1);}  // 36 = C2}   
                if ( (current * NUM_BTN_ROWS) + j == 4) {usbMIDI.sendNoteOn(53, 0, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 8) {usbMIDI.sendNoteOn(54, 0, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 12) {usbMIDI.sendNoteOn(55, 0, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 1) {usbMIDI.sendNoteOn(56, 0, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 5) {usbMIDI.sendNoteOn(57, 0, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 9) {usbMIDI.sendNoteOn(58, 0, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 13) {usbMIDI.sendNoteOn(59, 0, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 2) {usbMIDI.sendNoteOn(60, 0, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 6) {usbMIDI.sendNoteOn(61, 0, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 10) {usbMIDI.sendNoteOn(62, 0, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 14) {usbMIDI.sendNoteOn(63, 0, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 3) {usbMIDI.sendNoteOn(64, 0, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 7) {usbMIDI.sendNoteOn(65, 0, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 11) {usbMIDI.sendNoteOn(66, 0, 1);}
                if ( (current * NUM_BTN_ROWS) + j == 15) {usbMIDI.sendNoteOn(67, 0, 1);}
                LED_buffer[current][j] =! LED_buffer[current][j];
              }
            }
          }
        }
      
        delay(1);
      
        digitalWrite(btncolumnpins[current], HIGH);
        digitalWrite(ledcolumnpins[current], HIGH);
      
        for (i = 0; i < NUM_LED_ROWS; i++)
        {
          digitalWrite(colorpins[i], LOW);
        }
      
        current++;
        if (current >= NUM_LED_COLUMNS)
        {
          current = 0;
        }
      
      }


static void scan()
      {
        static uint8_t current = 0;
        uint8_t val;
        uint8_t i, j;

        digitalWrite(btncolumnpins[current], LOW);
        digitalWrite(ledcolumnpins[current], LOW);

        for (i = 0; i < NUM_LED_ROWS; i++)
        {
          if (LED_buffer[current][i])
          {
            digitalWrite(colorpins[i], HIGH);
          }
        }
      
        delay(1);
      
        for ( j = 0; j < NUM_BTN_ROWS; j++)
        {
          val = digitalRead(btnrowpins[j]);
    
          if (val == LOW)
          {
            if ( debounce_count[current][j] < MAX_DEBOUNCE)
            {
              debounce_count[current][j]++;
              if ( debounce_count[current][j] == MAX_DEBOUNCE )
              {
                Serial.print("Key Down ");
                Serial.println((current * NUM_BTN_ROWS) + j);
                LED_buffer[current][j] =! LED_buffer[current][j];
                delay(1);
              }
            }
          }
          else
          {
            if ( debounce_count[current][j] > 0)
            {
              debounce_count[current][j]--;
              if ( debounce_count[current][j] == 0 )
              {
                Serial.print("Key Up ");
                Serial.println((current * NUM_BTN_ROWS) + j);
              }
            }
          }
        }// for j = 0 to 3;
      
        delay(1);
      
        digitalWrite(btncolumnpins[current], HIGH);
        digitalWrite(ledcolumnpins[current], HIGH);
      
        for (i = 0; i < NUM_LED_ROWS; i++)
        {
          digitalWrite(colorpins[i], LOW);
        }
      
        current++;
        if (current >= NUM_LED_COLUMNS)
        {
          current = 0;
        }
      
      }

      
void setup()
{
  // ---- BUTTONS CODE ----
  pinMode(5, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
  
  // ---- POTENTIOMETER CODE ----
  for (int i=0; i<3; i++)
  {
    pinMode(selectPins[i], OUTPUT);
    digitalWrite(selectPins[i], HIGH);
  }
  pinMode(zPin, INPUT); 
  
  Serial.begin(115200);

  setuppins();

  for (uint8_t i = 0; i < NUM_LED_COLUMNS; i++)
  {
    for (uint8_t j = 0; j < NUM_LED_ROWS; j++)
    {
      LED_buffer[i][j] = 0;
    }
  }

  Serial.println("Setup Complete.");
 
}

void channelSelect(byte pin){
  for (int i=0; i<3; i++){
    if (pin & (1<<i))
      digitalWrite(selectPins[i], HIGH);
    else
      digitalWrite(selectPins[i], LOW);
  }
}

void loop() {
   // ---- POTENTIOMETER CODE ----
  
  static int previous_inputValue[8] = {-1,-1,-1,-1,-1,-1,-1,-1};
  
 if (msec >= 50) {

    for (byte pin=0; pin<=7; pin++){
      channelSelect(pin); 
      int inputValue[8] = {analogRead(A5)/8, analogRead(A5)/8, analogRead(A5)/8, analogRead(A5)/8, analogRead(A5)/8, analogRead(A5)/8, analogRead(A5)/8, analogRead(A5)/8}; 
      if ((inputValue[pin] != previous_inputValue[pin])) {
        if ((inputValue[pin] - 1 > previous_inputValue[pin] || inputValue[pin] + 1 < previous_inputValue[pin])) {
        usbMIDI.sendControlChange(CCmessage[pin], inputValue[pin], 1);
        previous_inputValue[pin] = inputValue[pin]; 
        Serial.print(inputValue[pin]);
        Serial.print("    ");
      }
    } 
    } 
    Serial.println();
  } 
  
  // ---- MENU CODE ----
  mode = analogRead(menuPot);

  if (mode >= 512){
    scanNOTE();
  } else if (mode < 512 && mode > 4){
      scanCC();
    } else {
        scan();
      }
  // ---- BUTTONS CODE ----
  buttonPLAY.update();
  buttonSTOP.update();
  buttonRECORD.update();
  buttonREPEAT.update();
  
  if (buttonPLAY.fallingEdge()) {usbMIDI.sendControlChange(22, 127, 1); Serial.println(22);}

  if (buttonSTOP.fallingEdge()) {usbMIDI.sendControlChange(23, 127, 1); Serial.println(23);}
  
    //TOGGLE SWITCH RECORD BUTTON
int toggleStateRECORD;
  if (buttonRECORD.fallingEdge() && (previousStateRECORD == 0)) {
    usbMIDI.sendControlChange(24, 127, 1); 
    Serial.println("24 ON");
    toggleStateRECORD = 1;
    previousStateRECORD = toggleStateRECORD;
    delay(50);
    msec = 0;
    } 
  if ((buttonRECORD.fallingEdge() && (toggleStateRECORD != 0) && msec >= 50)) {
    usbMIDI.sendControlChange(24, 0, 1); 
    Serial.println("24 OFF");
    toggleStateRECORD = 0;
    previousStateRECORD = toggleStateRECORD;
    }
     
    //TOGGLE SWITCH REPEAT BUTTON
int toggleStateREPEAT;
  if (buttonREPEAT.fallingEdge() && (previousStateREPEAT == 0)) {
    usbMIDI.sendControlChange(25, 127, 1); 
    Serial.println("25 ON");
    toggleStateREPEAT = 1;
    previousStateREPEAT = toggleStateREPEAT;
    delay(50);
    msec = 0;
    } 
  if ((buttonREPEAT.fallingEdge() && (toggleStateREPEAT != 0) && msec >= 50)) {
    usbMIDI.sendControlChange(25, 0, 1); 
    Serial.println("25 OFF");
    toggleStateREPEAT = 0;
    previousStateREPEAT = toggleStateREPEAT;
    }




  while (usbMIDI.read()) {
  }
}


