const int pins[7] = {2, 3, 4, 5, 6, 7, 8};

const int segment_map[31][2] = {
//pins[G], pins[V] 
    {6, 5},  // Segment 1: G7 V6
    {5, 6},  // Segment 2: G6 V7
    {5, 3},  // Segment 3: G6 V4
    {4, 5},  // Segment 4: G5 V6
    {0, 1},  // Segment 5: G1 V2
    {0, 2},  // Segment 6: G1 V3
    {3, 0},  // Segment 7: G4 V1
    {4, 0},  // Segment 8: G5 V1
    {0, 3},  // Segment 9: G1 V4
    {1, 0},  // Segment 10: G2 V1
    {2, 0},  // Segment 11: G3 V1
    {4, 6},  // Segment 12: G5 V7
    {2, 5},  // Segment 13: G3 V6
    {1, 2},  // Segment 14: G2 V3
    {1, 3},  // Segment 15: G2 V4
    {4, 1},  // Segment 16: G5 V2
    {1, 5},  // Segment 17: G2 V6
    {1, 4},  // Segment 18: G2 V5
    {2, 1},  // Segment 19: G3 V2
    {3, 1},  // Segment 20: G4 V2
    {2, 3},  // Segment 21: G3 V4
    {4, 3},  // Segment 22: G5 V4
    {2, 4},  // Segment 23: G3 V5
    {3, 4},  // Segment 24: G4 V5
    {5, 0},  // Segment 25: G6 V1
    {5, 2},  // Segment 26: G6 V3
    {3, 2},  // Segment 27: G4 V3
    {4, 2},  // Segment 28: G5 V3
    {3, 5},  // Segment 29: G4 V6
    {5, 4},  // Segment 30: G6 V5
    {6, 4}   // Segment 31: G7 V5
};

unsigned long refresh_rate_micros = 2000000;
unsigned long previous_micros = 0;
int current_segment = 0;

void set_to_input()
{
    for(auto i : pins) pinMode(i, INPUT);
}

void set_to_output()
{
    for(auto i : pins) pinMode(i, OUTPUT);
}

void light_segment(int segment)
{
    set_to_output();
    int gnd_pin = segment_map[segment - 1][0];
    int vcc_pin = segment_map[segment - 1][1];

    for(int i = 0; i < 7; i++)
    {
        if(i == gnd_pin || i == vcc_pin)
        {
            pinMode(pins[i], OUTPUT);
        }
        else
        {
            pinMode(pins[i], INPUT); //turning the other pins into INPUT (floating state) to simulate pins being physically removed from the breadboard
        }
    }

    digitalWrite(pins[gnd_pin], LOW);
    digitalWrite(pins[vcc_pin], HIGH);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
    set_to_output();
}

void loop() {
  // put your main code here, to run repeatedly:
    unsigned long current_micros = micros();
    if(current_micros - previous_micros >= refresh_rate_micros)
    {
        previous_micros = current_micros;
        current_segment++;
        Serial.print(current_micros);
        Serial.print(" | ");
        Serial.print("Segment: ");
        Serial.println(current_segment);
        if(current_segment >= 31)
        {
            current_segment = 0;
        }
        light_segment(current_segment);
    }
}
