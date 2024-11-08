#define ANALOG_IN_PIN A1 // voltage sensor input pin
 
// Floats for ADC voltage & Input voltage
float adc_voltage = 0.0;
float in_voltage = 0.0;
 
// Floats for resistor values in divider (in ohms)
float R1 = 30000.0;
float R2 = 7500.0; 
 
// Float for Reference Voltage
float ref_voltage = 5.0;
 
// Integer for ADC value
int adc_value = 0;

// Measure current with ACS712
// and print on Serial Monitor
const int nSamples = 500;
const float vcc = 5.0;
const int adcMax = 1023;

const float sens = 0.185;  // 5A
//const float sens = 0.100;  // 20A
//const float sens = 0.66;  // 30A

float avg() {
  float val = 0;
  for (int i = 0; i < nSamples; i++) {
    val += analogRead(A0);
    delay(1);
  }
  return val / adcMax / nSamples;
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  float cur = ((vcc / 2 - vcc * avg()) / sens)*1000;

  // Read the Analog Input
  adc_value = analogRead(ANALOG_IN_PIN);
  
  // Determine voltage at ADC input
  adc_voltage  = (adc_value * ref_voltage) / 1024.0;
  
  // Calculate voltage at divider input
  in_voltage = adc_voltage*(R1+R2)/R2;
  
  // Print results to Serial Monitor to 2 decimal places
  Serial.print("Input Voltage = ");
  Serial.println(in_voltage, 2);
  
  Serial.print("Current:");
  Serial.println(cur);

  Serial.print("Watts:");
  Serial.println(in_voltage * cur);
}