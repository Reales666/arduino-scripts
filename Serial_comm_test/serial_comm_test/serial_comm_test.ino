int input_value;

void setup() {
  // Initialize serial comm
  Serial.begin(115200);
  Serial.setTimeout(1);
}

void loop() {
    while (!Serial.available()); // Wait until Serial port is available
    
    input_value = Serial.readString().toInt(); // Read input value
    
    Serial.print(input_value); // Print the value
}