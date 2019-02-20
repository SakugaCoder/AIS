 //***************************************************************************************************************************************
//Configuracion del kypad//;
#include <Keypad.h>
//Define la cantidad de pines de columnas y de filas a utilizar deacuerdo con las caracteristícas del keypad utilizado.

//Define los pines de las columnas y de las filas en un array respectivamente.
const byte filasPins[4] = {A4, A3, A2, A1};
const byte columnasPins[4] = {A0,13, 12, 9};

//Agreglo bidireccional para la declaracion de las letras que contiene el teclado matricial.
char caracteres[4][4] = {
                      {'1', '2', '3', 'A'},
                      {'4', '5', '6', 'B'},
                      {'7', '8', '9', 'C'},
                      {'*', '0', '#', 'D'}
};

//Configuarción e inicialización del teclado matricial
Keypad teclado = Keypad(makeKeymap(caracteres),filasPins, columnasPins, 4, 4);
//***************************************************************************************************************************************


//***************************************************************************************************************************************
//Configuración del boton y el potenciometro//

//Definición de los pines del potenciometro y el boton
#define BOTON 2

//Definicion de los constantes de los dias de la semana

int DR[] = {0, 0, 0, 0, 0, 0, 0};
 
//Decalaración de el dia de referencia
//Declaración de las variables del control del estado del boton
int lecturaBoton;
int estadoBoton;
int estadoBotonAnterior = LOW;

//Declaración de la variable del tiempo o retardo para el control del estado del boton
unsigned long tiempoActivacion;
//***************************************************************************************************************************************


unsigned long tiempo;
unsigned long tiempoAnterior = 0;

byte segundos;
byte minutos;
byte horas;
byte dias;

boolean on = true;
boolean off = false;
boolean estadoLCD = on;
byte tiempoLCD;

boolean bucle = on;
boolean EB;
char valorKeypad;

String fechaRiego;
String HRM;
String MRM;
String HRT;
String MRT;

//Variable para la duracion del riego
String DRAR;
String DRPL;
String DRPA;

byte TDR;
byte c;

 
void setup(){
  Serial.begin(9600);
  pinMode(BOTON, INPUT);
}

void loop(){
  pantallaPrincipal();
}

void pantallaPrincipal(){
     gestionLCD();
  if(EB == on && estadoLCD == on){
//***************************************************************************************************************************************    
    EB = off;
    Serial.println("Menu principal");
    while(bucle == on){
      gestionLCD(); 
      if(valorKeypad && estadoLCD == on){
            tiempoLCD = 0;
            switch(valorKeypad){
              //*************************************************************************************************************************************** 
              case '1':{
                menuHorasRiego();
                break;
                  }
               //***************************************************************************************************************************************  
                
              
              //***************************************************************************************************************************************
              case '2':{
                Serial.println("Teclado accionado: estas en menu de riego manual");
                menuRiegoManual();
                break;
                }
              //***************************************************************************************************************************************
                
                
              //***************************************************************************************************************************************
              case '3':{                                
                Serial.println("Teclado accionado: configuracion hora");
                menuConfiguracionHora();
                break;                
                }
              //***************************************************************************************************************************************

              case '4':{
                Serial.println("Acera de :");
                menuAcercaDe();
                break;
              }

              
              //***************************************************************************************************************************************
              case 'C':{
                  bucle = off;
                  Serial.println("Has regresado a la pantalla principal");
                  break;
                }
             //*************************************************************************************************************************************** 
              default:
                break;
            }
      }
    }
  }
//***************************************************************************************************************************************
}

//************************************************************************************************************************************************************************
void menuHorasRiego(){
  Serial.println("Telcado accionado: estas en menu ede fecha riego"); 
  while(bucle == on){
    gestionLCD();

    if(estadoLCD == on && valorKeypad == 'C' && (HRM.toInt() == 0 && MRM.toInt() == 0 && HRT.toInt() == 0 && MRT.toInt() == 0)){
      bucle = off;
      Serial.println("Has salido del bucle");
      break;                    
    }
                                                                   
    if(int(valorKeypad) && estadoLCD == on && fechaRiego.length() < 9 && valorKeypad != 'C'){                                
      fechaRiego = fechaRiego + valorKeypad;
      if(fechaRiego.length() < 3){
        HRM = HRM + valorKeypad;
        Serial.println("Manana:       Tarde:");
        Serial.println(HRM+":"+MRM+"      "+HRT+":"+MRT);
      }

      if(fechaRiego.length() > 2 && fechaRiego.length() < 5){                    
        MRM = MRM + fechaRiego.substring(fechaRiego.length() -1);
        Serial.println(HRM+":"+MRM+"      "+HRT+":"+MRT);          
      }

      if(fechaRiego.length() > 4 && fechaRiego.length() < 7){
        HRT = HRT + fechaRiego.substring(fechaRiego.length() -1);
        Serial.println(HRM+":"+MRM+"      "+HRT+":"+MRT);
      }

      if(fechaRiego.length() > 6 && fechaRiego.length() < 9){
        MRT = MRT + fechaRiego.substring(fechaRiego.length() -1);
        Serial.println(HRM+":"+MRM+"      "+HRT+":"+MRT);
      }             
    }
    if(fechaRiego.length() == 8){ 
      if(HRM.toInt() > 10 || HRM.toInt() <6){
        HRM = "08";                                              
      }

      if(HRT.toInt() > 4 || HRT.toInt() < 11){
        HRT = "21";                          
      }

      if(MRM.toInt() > 60){
        MRM = "60";
      }
      
      if(MRT.toInt() > 60){
        MRT = "60";                          
      }                                                                        
    }
                       
    if(estadoLCD == on && valorKeypad == 'C' && ((HRM.length() > 0 && HRM.toInt() > 0) || MRM.toInt() || (HRT.length() >0 && HRT.toInt() > 0) || MRT.toInt())){
      HRM = "";
      MRM = "";
      HRT = "";
      MRT = "";
      fechaRiego = "";
      Serial.println(HRM+":"+MRM+"      "+HRT+":"+MRT);
    }

    if(estadoLCD == on && EB == on && ((HRM.length() > 0 && HRM.toInt() > 0) || MRM.toInt() || (HRT.length() >0 && HRT.toInt() > 0) || MRT.toInt())){
      Serial.println("Cambios guardados");
      Serial.println("Has entrado a menu configuracion dias de riego");
      menuDiasRiego();
    }
  }
 bucle = on;
}
//************************************************************************************************************************************************************************

//************************************************************************************************************************************************************************
void menuDiasRiego(){
  while(bucle == on){
    gestionLCD();
    if(estadoLCD == on && valorKeypad){       
      String diaRiego = String(valorKeypad);
      if(diaRiego.toInt() < 8 && diaRiego.toInt() != 0){
        if(DR[diaRiego.toInt() - 1] == 0){
          DR[diaRiego.toInt() - 1 ] = 1;
        }

        else{
          DR[diaRiego.toInt() - 1] = 0;
        }

        Serial.print("Lunes = "); Serial.println(DR[0]);
        Serial.print("Martes = "); Serial.println(DR[1]);
        Serial.print("Miercoles = "); Serial.println(DR[2]);
        Serial.print("Jueves = "); Serial.println(DR[3]);
        Serial.print("Viernes = "); Serial.println(DR[4]);
        Serial.print("Sabado = "); Serial.println(DR[5]);
        Serial.print("Domingo= "); Serial.println(DR[6]);
      }

      if(valorKeypad == 'C'){
        TDR = 0;
        for(c = 0; c < 7; c++){
          if(DR[c] == 1){
            TDR++; 
          }
        }

        if(TDR > 0){
         for(int c = 0; c < 7; c++){
          if(DR[c] == 1){
           DR[c] = 0;
          }
         }
                                  
        Serial.print("Lunes = "); Serial.println(DR[0]);
        Serial.print("Martes = "); Serial.println(DR[1]);
        Serial.print("Miercoles = "); Serial.println(DR[2]);
        Serial.print("Jueves = "); Serial.println(DR[3]);
        Serial.print("Viernes = "); Serial.println(DR[4]);
        Serial.print("Sabado = "); Serial.println(DR[5]);
        Serial.print("Domingo= "); Serial.println(DR[6]);                                                                
        }

        if(TDR == 0){
          bucle = off;
          Serial.println("Has salido del menu dias de riego");
          break;
          }
      }
    }

    if(estadoLCD == on && EB == on){
      TDR = 0;
      for(c = 0; c < 7; c++){
        if(DR[c] == 1){
          TDR++;
        }
      }
      if(TDR > 0){
        TDR = 0;
        Serial.println("Cambios guardados");
        Serial.println("Has entrado al menu de configuracion de la duracion de riego ARBOLES");
        menuDuracionRiegoArboles();                
      }
     }
     
   }
 bucle = on;
}
//************************************************************************************************************************************************************************

//************************************************************************************************************************************************************************
void menuDuracionRiegoArboles(){
  while(bucle == on){
      gestionLCD();
      if(estadoLCD == on && valorKeypad){
        String DURI = String(valorKeypad);
        if(DURI.toInt() >= 0 && DURI.toInt() <= 9 && DRPA.length() != 2){
          DRAR = DRAR + DURI; 
          Serial.print("Duracion minutos de riego ARBOLES : "); Serial.println(DRAR);                                           
        }

        if(DRAR.length() == 2 && DRAR.toInt() > 60){
          DRAR = "60";
        }
        
        if(valorKeypad == 'C' && DRAR.length() > 0){
          DRAR = "";
        }

         if(valorKeypad == 'C' && DRAR.length() == 0){
          bucle == off;
          Serial.println("Has salido del bucle duracion de riego ARBOLES");  
          break;
         }                                   
      }
      if(estadoLCD == on && EB == on && DRAR.length() == 2){
        Serial.println("Cambios guardados");
        Serial.println("Has entrado al menu de cofiguracion de la duracion de riego PLANTAS");
        menuDuracionRiegoPlantas();
      }
    }
  bucle = on;
}
//************************************************************************************************************************************************************************

//************************************************************************************************************************************************************************
void menuDuracionRiegoPlantas(){
    while(bucle == on){
      gestionLCD();
      if(estadoLCD == on && valorKeypad){
        String DURI = String(valorKeypad);
        if(DURI.toInt() >= 0 && DURI.toInt() <= 9 && DRPL.length() != 2){
          DRPL = DRPL + DURI; 
          Serial.print("Duracion minutos de riego PLANTAS : "); Serial.println(DRPL);                                           
        }

        if(DRPL.length() == 2 && DRPL.toInt() > 60){
          DRPA = "60";
        }
        
        if(valorKeypad == 'C' && DRPL.length() > 0){
          DRPL = "";
        }

        if(valorKeypad == 'C' && DRPL.length() == 0){
          bucle == off;
          Serial.println("Has salido del bucle duracion de riego PLANTAS");  
          break;
         }                                   
      }

      if(estadoLCD == on && EB == on && DRPL.length() == 2){
        Serial.println("Cambios guardados");
        Serial.println("Has entrado al menu de configuracion de la duracion de riego PASTO");
        menuDuracionRiegoPasto();
      }
    }
  bucle = on;
}
//************************************************************************************************************************************************************************

//************************************************************************************************************************************************************************
void menuDuracionRiegoPasto(){
  while(bucle == on){
      gestionLCD();
      if(estadoLCD == on && valorKeypad){
        String DURI = String(valorKeypad);
        if(DURI.toInt() >= 0 && DURI.toInt() <= 9 && DRPA.length() != 2){
          DRPA = DRPA + DURI; 
          Serial.print("Duracion minutos de riego PASTO : "); Serial.println(DRPA);                                           
        }

        if(DRPA.length() == 2 && DRPA.toInt() > 60){
          DRPA = "60";
        }
        
        if(valorKeypad == 'C' && DRPA.length() > 0){
          DRPA = "";
        }

         if(valorKeypad == 'C' && DRPA.length() == 0){
          bucle == off;
          Serial.println("Has salido del bucle duracion de riego PASTO");  
          break;
         }                       
      }

      if(estadoLCD == on && EB == on && DRPA.length() == 2){
        Serial.println("Cambios guradados");
        Serial.println("Has entrado al menu de confiramcion");
        menuConfirmacion();
      }
    }
  bucle = on;
}
//************************************************************************************************************************************************************************

//************************************************************************************************************************************************************************
void menuConfirmacion(){
  while(bucle == on){
      gestionLCD();
      if(estadoLCD == on && valorKeypad){
        if(valorKeypad == 'C'){
          bucle = off;
          Serial.println("Has regresado a el menu duracion de riego PASTO");
          break;
        }
      }

      if(estadoLCD == on && EB == on){
        Serial.println("Has guardado los cambios regresando a la pantalla prinipal");
        Serial.println("valores: ");
        Serial.print("Manana:       Tarde:");
        Serial.println(HRM+":"+MRM+"      "+HRT+":"+MRT);    
        Serial.println("");
        Serial.print("Lunes = "); Serial.println(DR[0]);
        Serial.print("Martes = "); Serial.println(DR[1]);
        Serial.print("Miercoles = "); Serial.println(DR[2]);
        Serial.print("Jueves = "); Serial.println(DR[3]);
        Serial.print("Viernes = "); Serial.println(DR[4]);
        Serial.print("Sabado = "); Serial.println(DR[5]);
        Serial.print("Domingo= "); Serial.println(DR[6]);  
        Serial.println("");
        Serial.println("Duracion Riego:");
        Serial.print("Arboles: "); Serial.println(DRAR);
        Serial.print("Plantas: "); Serial.println(DRPL);
        Serial.print("Pasto: "); Serial.println(DRPA);  
        EB = off;
        bucle = on;
        pantallaPrincipal();                                                                
       }
      }
  bucle = on;
}
//************************************************************************************************************************************************************************

void menuRiegoManual(){
  
}

void menuConfiguracionHora(){
  
}
void menuAcercaDe(){
  
}


int gestionLCD(){
  tiempo = millis();
  if((tiempo - tiempoAnterior) == 1000){
    tiempoAnterior = tiempo;
    if(estadoLCD == on){
      tiempoLCD++;     
      Serial.println(tiempoLCD); 
    }    
  }

  if(estadoLCD == on && tiempoLCD == 10){
    estadoLCD = off;
    Serial.println("LCD apagada: apagado por inactividad");
  }

  valorKeypad = teclado.getKey();
  
  if(valorKeypad && estadoLCD == off){
    estadoLCD = on;
    tiempoLCD = 0;
    Serial.println("LCD encendida: has presionado una tecla del keypad");
  }

  if(valorKeypad && estadoLCD == on){
    tiempoLCD = 0;
  }

  
  //Se realiza la lectura aprueba de rebote del boton
  lecturaBoton = digitalRead(BOTON);
  if(lecturaBoton != estadoBotonAnterior){ //Comprueba si hay un cambio de estado del boton.
    tiempoActivacion = millis();           //Si lo hay simplemente inicia una variable con un valor millis para iniciar el retardo.
  }

  if((millis() - tiempoActivacion) >= 50){ //Si el tiempo - elTiempoActivacion = retardo(se a cumplido el tiempo especifiacdo.
    if(lecturaBoton != estadoBoton){  //Si la lectura es diferente al estado del boton, es decir varia de estadp LOW a HIGH y viceversa. El estado del boton es diferente.
      estadoBoton = lecturaBoton;     //El estado del boton es igual a la lectura.
      if(estadoBoton == HIGH && estadoLCD == on){        //Cuando el estado del boton sea igual a HIGH.         
         EB = on;                     //Manda señal de activación del boton.    
         tiempoLCD = 0;    
      }

      if(estadoBoton == LOW){
        EB = off;
      }

      if(estadoBoton == HIGH && estadoLCD == off){
        estadoLCD = on;
        tiempoLCD = 0;
        Serial.println("LCD encendida");        
      }
    }
  }
  estadoBotonAnterior = lecturaBoton;   //Se guarda el estado anterior del boton con el valor de la lectura.
  }
