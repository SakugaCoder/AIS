//RROGRAMA PARA GUARDAR LOS DIAS DE RIEGO.
//inicio 7:20
boolean DR[] = {false, false, false, false, false, false, false};

void setup(){
  Serial.begin(9600);  
}

void loop(){
  if(Serial.available()){
    byte numero = Serial.read();
    while(numero < 8){
      if(DR[numero - 1] == false){
        DR[numero - 1] = true;
      }
      else{
        DR[numero - 1] = false;
      }
    }  
    Serial.println("LU = " + DR[0]);

    //Tecla de borrar
    if(numero == 8){
      int c = 0;
      for(int i = 0; i < 7; i++){
        if(DR[i] == true){
          c++;       
        }
      }

      if( c > 0){
        for(int i = 0; i < 7; i++){
        if(DR[i] == true){
          DR[i] = false;       
        }
      }
        
      }

      if(c == 0){
        //break;
        //Salir
      }
    }
    
    if(numero == 9){  
      int c = 0;
      for(int i = 0; i < 7; i++){
        if(DR[i] == true){
          c++;       
        }
      }

      if(c > 0){
        Serial.println("Has entrado al menu principal");
      }
    }    
  }
}

