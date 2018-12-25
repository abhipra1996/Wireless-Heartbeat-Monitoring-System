
void serialOutput(){   // Decide How To Output Serial.
  switch(outputType){
    
    case SERIAL_PLOTTER:  // open the Arduino Serial Plotter to visualize these data
      Serial.print("BPM : ");
      Serial.print(BPM);
      Serial.print(",");
      Serial.print("IBI : ");
      Serial.print(IBI);
      Serial.print(",");
      Serial.print("SIGNAL : ");
      Serial.println(Signal);
      break;
    
    default:
      break;
  }

}

//  Decides How To OutPut BPM and IBI Data
void serialOutputWhenBeatHappens(){
  
   switch(outputType){
    
    case SERIAL_PLOTTER:  
      Serial.print("FOUND BPM : ");
      Serial.print(BPM);
     
      Serial.print(" , ");
      Serial.print(" IBI : ");
      Serial.print(IBI);
      Serial.print(" , ");
      Serial.print(" SIGNAL : ");
      Serial.println(Signal);
      break;

    default:
      break;
  }
}

//  Sends Data to Pulse Sensor Processing App, Native Mac App, or Third-party Serial Readers.

//void sendDataToSerial(char symbol, int data ){
  //  Serial.print(symbol);
   // Serial.println(data);
  // }
