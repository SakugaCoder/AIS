//PROGRAMA PARA OBTENER EL NUMERO DE MINUTOS DE RIEGO DEL SISTEMA
String MRAR; //Minutos riego arboles
String MRPL; //Minutos riego plantas
String MRPA; //Minutos riego pasto
String MR;  
char botonPresionado;
char valorKeypad;
void setup() {
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()){
    char valor = Serial.read();
    MR = MR + valor;
    if(MR.length() == 2){
      MRAR = MR;
      if(MRAR.toInt() > 60){
        MRAR = "60";
      }
      Serial.print("Minutos riego arboles = "); Serial.println(MRAR); 
    }

    else if(MR.length() == 4){
      MRPL = MR.substring(2);
      if(MRPL.toInt() > 60){
        MRPL = "60";
      }
      Serial.print("Minutos riego plantas = "); Serial.println(MRPL);
    }

    else if(MR.length() == 6){
      MRPA = MR;
      if(MRPA.toInt() > 60){
        MRPA = "60";
      }
      Serial.print("Minutos riego pasto = "); Serial.println(MRPA);
    }
  }
}
