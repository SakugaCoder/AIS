/*//PROGRAMA PAR CONTROLAR PA PANTALLA DE RIEGO

boolean on = true;
boolean off = false;
boolean estadoLCD = on;
int botonAccionado = 1;
void setup(){
  Serial.begin(9600);
}

void loop(){
  if(Serial.available()){ //preguntamos si existe un valor que leer    
    int valor = Serial.read() //asignamos ese valor a una variable para compararlo
    if(estadoLCD == on && valor == "C"){ //Si la pantalla esta encendida y sis e preciona el boton c, se cancela el riego y se regresa a la pantalla principal 
       
    }
  }
}*/

//PROGRAMA PARA CONTROLAR LA VENTANA DE CONFIRMACION DR GUARDADAO DE LOS DATOS DE RIEGO

boolean on = true,
        off = false,
        estadoLCD = on;
char botonAccionado = '1';        
void setup(){
  
}

void loop(){
  Serial.println("Aqui van los datos que se han ingresado en el sistema"); //De ser posible hacer un buen algoritmo el cual solo muestre una vez un contenido para controlar el consumo
  if(Serial.available()){
    char valor = Serial.read(); // almacena el valor que se ha ingresado;
    
    if(valor == 'c' && estadoLCD == on){ //Si el valor del keypad es igual a C y si la LCD esta encendidad, entonces se regresara a la pantalla anterior      
    }

    if(valor == botonAccionado && estadoLCD == on){ //Si se acciona el boton y si la LCD esta encendida      
    }

    
  }
}

