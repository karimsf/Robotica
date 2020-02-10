#include  <Servo.h>
#include  <stdio.h>

bool      conect, record, play, reset;

Servo     srv_0,    srv_1,      srv_2,    srv_3,      srv_4,      srv_5;    //añadir servo para su uso
int       pot_bs,   pot_hmb,    pot_cd,   pot_mnc,    pot_gr,     pot_pnz;  //valores de los pote
byte      srv_bs,   srv_hmb,    srv_cd,   srv_mnc,    srv_gr,     srv_pnz;  //valores de los servo

byte      play_2;
byte      array_c, array_2, c;
byte      matriz[1000][5];
unsigned long   time0, time1;

byte      bt = 0;           //en milisegundos
byte      toler = 5;        //tolerancia de guardado de datos +-x ms

void setup() {
  
  Serial.begin(9600);
  
  pinMode(2, INPUT);          //replicaador conectado
  pinMode(3, INPUT);          //grabar
  pinMode(4, INPUT);          //reproducir parar
  pinMode(5, INPUT);          //reset

  srv_0.attach(7);            //servo base  us max y min
  srv_1.attach(8);            //servo hombro
  srv_2.attach(9,70,230);     //servo codo    500-2500
  srv_3.attach(10,70,230);    //servo muneca
  srv_4.attach(11,70,230);    //servo giro
  srv_5.attach(12);           //servo pinza
  
  }

void loop() {
  
  conect  = digitalRead(2);
  record  = digitalRead(3);
  play    = digitalRead(4);
  reset   = digitalRead(5);

//_______________________llamar replicador___________________________________________________

  while(conect == HIGH && record == LOW && play_2 == 0){  //robo_pote conectado
                                                          //puls_grabrar no pulsado
    replicar();                                           //no esta reproduciendo

    conect  = digitalRead(2);
    record  = digitalRead(3);
    }

//_______________________llamar grabado______________________________________________________

  while(conect == HIGH && record == HIGH && play_2 == 0 && c == 0){   //robo_pote conectado
                                                                      //puls_grabrar pulsado
    grabado();                                                        //no esta reproduciendo
                                                                      //contador c = 0
    conect  = digitalRead(2);
    record  = digitalRead(3);
    }
    
//_______________________llamar bucle________________________________________________________
  
  if(play == HIGH && record == LOW && play_2 == 0 && c == 1){

      while(play == HIGH){
        
        play_2 = 1;
        }
      }

  while(play_2 == 1){

      bucle();

      record  = digitalRead(3);
      play  = digitalRead(4);
      
      if(play == HIGH && record == LOW){
        
        while(play == HIGH){
          
          play_2 = 0;
          c = 1;
        }
      }
    }

//_______________________reset_______________________________________________________________
  if(reset == HIGH && c != 0){
    
    for(array_c = 1000; array_c >= 0; array_c --){
      matriz[array_c][0] = 0;
      matriz[array_c][1] = 0;
      matriz[array_c][2] = 0;
      matriz[array_c][3] = 0;
      matriz[array_c][4] = 0;
      matriz[array_c][5] = 0;

      c = 0;
      }
    }
    
  }

//____________________________________________replicar_______________________________________

void  replicar() {

  //base
  pot_bs  =   analogRead(0);                  //lee pote
  srv_bs  =   map(pot_bs, 0, 1023, 8, 188);   //escalado
  srv_0.write(srv_bs);                        //mueve valor al servo

  //hombro
  pot_hmb  =   analogRead(1);                 //lee pote
  srv_hmb =   map(pot_hmb, 0, 1023, 0, 180);  //escalado
  srv_1.write(srv_hmb);                       //mueve valor al servo

  //codo
  pot_cd  =   analogRead(2);                  //lee pote
  srv_cd  =   map(pot_cd, 0, 1023, 0, 180);   //escalado
  srv_2.write(srv_cd);                        //mueve valor al servo
  
  //muneca
  pot_mnc  =   analogRead(3);                 //lee pote
  srv_mnc  =  map(pot_mnc, 0, 1023, 0, 180);  //escalado 
  srv_3.write(srv_mnc);                       //mueve valor al servo

  //giro
  pot_gr  =   analogRead(4);                  //lee pote
  srv_gr  =  map(pot_gr, 0, 1023, 0, 180);    //escalado
  srv_4.write(srv_gr);                        //mueve valor al servo

  //pinza
  pot_pnz  =   analogRead(5);                 //lee pote
  srv_pnz  =  map(pot_pnz, 0, 1023, 0, 180);  //escalado
  srv_5.write(srv_pnz);                       //mueve valor al servo
  }
//________________________________________grabado____________________________________________

void  grabado()  {
  
  if(c == 0){
    
    array_c = 0;
    time0 = millis();
    c = 1;
  }
  
  //base
  pot_bs  =   analogRead(0);                  //lee pote
  srv_bs  =   map(pot_bs, 0, 1023, 8, 188);   //escalado
  srv_0.write(srv_bs);                        //mueve valor al servo

  //hombro
  pot_hmb  =   analogRead(1);                 //lee pote
  srv_hmb =   map(pot_hmb, 0, 1023, 0, 180);  //escalado
  srv_1.write(srv_hmb);                       //mueve valor al servo

  //codo
  pot_cd  =   analogRead(2);                  //lee pote
  srv_cd  =   map(pot_cd, 0, 1023, 0, 180);   //escalado
  srv_2.write(srv_cd);                        //mueve valor al servo
  
  //muneca
  pot_mnc  =   analogRead(3);                 //lee pote
  srv_mnc  =  map(pot_mnc, 0, 1023, 0, 180);  //escalado 
  srv_3.write(srv_mnc);                       //mueve valor al servo

  //giro
  pot_gr  =   analogRead(4);                  //lee pote
  srv_gr  =  map(pot_gr, 0, 1023, 0, 180);    //escalado
  srv_4.write(srv_gr);                        //mueve valor al servo

  //pinza
  pot_pnz  =   analogRead(5);                 //lee pote
  srv_pnz  =  map(pot_pnz, 0, 1023, 0, 180);  //escalado
  srv_5.write(srv_pnz);                       //mueve valor al servo
  
  time1 = millis();

  if((time1 - time0) > (bt - toler) && (bt + toler) < (time1 - time0) && array_c < 1000){  //guardar datos cada 'bt' (+-5ms) ms
    
    time0 = time1;
    
    matriz[array_c][0]  =   srv_bs;
    matriz[array_c][1]  =   srv_hmb;
    matriz[array_c][2]  =   srv_cd;
    matriz[array_c][3]  =   srv_mnc;
    matriz[array_c][4]  =   srv_gr;
    matriz[array_c][5]  =   srv_pnz;

    array_2 = array_c;
    array_c = array_c + 1;
    }   
}

//_________________________________________bucle_____________________________________________

void bucle(){
  
  if(c == 1){
    
    time0 = millis();
    c = 2;
    array_c = 0;
    }

  time1 = millis();

  if((time1 - time0) >= bt && array_c <= array_2){
  
    srv_0.write(matriz[array_c][0]);
    srv_1.write(matriz[array_c][1]);
    srv_2.write(matriz[array_c][2]);
    srv_3.write(matriz[array_c][3]);
    srv_4.write(matriz[array_c][4]);
    srv_5.write(matriz[array_c][5]);
    
    array_c = array_c + 1;
    time0 = time1;

    if(array_c == array_2){
    
      array_c = 0;
      }
    }
  }
