#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <Fonts/Picopixel.h>
#include <Fonts/font.h>

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0
#define NEO_PIN 18

#define TEMPO 200
#define TRESHOLD 3600

int melody[] = {

  // Happy Birthday
  // Score available at https://musescore.com/user/8221/scores/26906

  NOTE_C4,4, NOTE_C4,8, 
  NOTE_D4,-4, NOTE_C4,-4, NOTE_F4,-4,
  NOTE_E4,-2, NOTE_C4,4, NOTE_C4,8, 
  NOTE_D4,-4, NOTE_C4,-4, NOTE_G4,-4,
  NOTE_F4,-2, NOTE_C4,4, NOTE_C4,8,

  NOTE_C5,-4, NOTE_A4,-4, NOTE_F4,-4, 
  NOTE_E4,-4, NOTE_D4,-4, NOTE_AS4,4, NOTE_AS4,8,
  NOTE_A4,-4, NOTE_F4,-4, NOTE_G4,-4,
  NOTE_F4,-2,
 
};

int notes = sizeof(melody) / sizeof(melody[0]) / 2;

// this calculates the duration of a whole note in ms
int wholenote = (60000 * 4) / TEMPO;

int divider = 0, noteDuration = 0;
void playHB(int buzzer){
        // iterate over the notes of the melody.
    // Remember, the array is twice the number of notes (notes + durations)
    for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

        // calculates the duration of each note
        divider = melody[thisNote + 1];
        if (divider > 0) {
        // regular note, just proceed
        noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
        // dotted notes are represented with negative durations!!
        noteDuration = (wholenote) / abs(divider);
        noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // we only play the note for 90% of the duration, leaving 10% as a pause
        tone(buzzer, melody[thisNote], noteDuration * 0.9);

        // Wait for the specief duration before playing the next note.
        delay(noteDuration);

        // stop the waveform generation before the next note.
        noTone(buzzer);
    }
}

int buzzer = 27;


Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, NEO_PIN,
  NEO_MATRIX_TOP    + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS,
  NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
    matrix.Color(204, 0, 204), matrix.Color(204, 204, 0), matrix.Color(0, 255, 255),
    matrix.Color(255, 10, 127), matrix.Color(127, 0, 255), matrix.Color(0, 255, 0),
    matrix.Color(255, 99, 255)};

int x = matrix.width();
int pass = 0;

void LEDTask(void *param)
{
    bool wasChange = false;
    while(true){
    matrix.fillScreen(0);    //Turn off all the LEDs
    matrix.setCursor(x, 1);
    if (--x < -270) {
        x = matrix.width();
    }
    if(x < -245 ) {
        if(!wasChange){
        wasChange = true;
        matrix.setTextColor(colors[random(0,6)]);
    }
    } else {
        wasChange = false;
        matrix.setTextColor(colors[0]);
    }
    matrix.print(F("VSETKO NAJLEPSIE K VYROCIU PRAJE KOLEKTIV KTK"));
    matrix.show();    
    delay(50);
  }
}

void BuzzerTask(void *param)
{
    while(true){
        playHB(buzzer);
        delay(2000);
    }
}

void setup()
{
    Serial.begin(115200);
    pinMode(32, OUTPUT);
    digitalWrite(32, LOW);
    matrix.begin();
    matrix.setTextWrap(false);
    matrix.setBrightness(30);
    matrix.setTextColor(colors[0]);
    matrix.fillScreen(0);  
    matrix.setTextSize(1); 
    //matrix.setFont(&Picopixel);
    matrix.show();  
    //matrix.setFont(&dotmat10pt7b_v2);
    while (analogRead(32) < TRESHOLD);
        delay(500);
    while (analogRead(32) < TRESHOLD);
        delay(500);
    while (analogRead(32) < TRESHOLD);
}


void loop()
{
    Serial.println("Starting sequence");
    xTaskCreatePinnedToCore(BuzzerTask, "RTC", 8192, NULL, 1, NULL, 1);
    xTaskCreatePinnedToCore(LEDTask, "RTC", 8192, NULL, 2, NULL, 1);
    while(true);
}