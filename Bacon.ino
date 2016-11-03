int infraFrontal = 2;
int infraEsquerdo = 3;
int infraDireito = 4;
int ultaSonicoFrontal;
int motorFrontalEsquerda = 11; //Testar
int motorFrontalDireita = 12; //Testar
int motorTraseiroFrente = 9; //Testar
int motorTraseiroRe = 8; //Testar

bool seguindo = false;
bool modoCurva = false;
bool bloqueado = false;

bool encontrouFaixa(){
  int leitura = digitalRead(infraFrontal);
  if(leitura == 0) return true;
  else return false;
}

/*implementar*/
bool encontrouObstaculo(){
  return false;
}

void andarEmFrente(){
  digitalWrite(motorTraseiroFrente,HIGH);
  digitalWrite(motorTraseiroRe,LOW);
}

void curvar(char lado, int tempoDeCurva){
  
  /*Curvar pra esquerda*/
  if(lado == 'e' || lado == 'E'){
    digitalWrite(motorFrontalEsquerda,HIGH);
    digitalWrite(motorFrontalDireita,LOW);
    delay(tempoDeCurva);
  }
  /*Curvar pra direito*/
  else if(lado == 'd' || lado == 'D'){
    digitalWrite(motorFrontalEsquerda,LOW);
    digitalWrite(motorFrontalDireita,HIGH);
    delay(tempoDeCurva);
  }
  /*Curvar pra lugar nenhum*/
  else{
    tempoDeCurva = 0;
    digitalWrite(motorFrontalEsquerda,LOW);
    digitalWrite(motorFrontalDireita,LOW);
    delay(tempoDeCurva);
  }
}

/*implementar*/
char leituraProximaCurva(){
  return 'e'; //Curvar à esquerda
  return 'd'; //Curvar à direita
  return 'n'; //Curvar pra lado nenhum
  
}

void absBoladao(){
  delay(27);
  digitalWrite(motorTraseiroFrente,LOW);
  digitalWrite(motorTraseiroRe,HIGH);
  delay(100);
  digitalWrite(motorTraseiroFrente,LOW);
  digitalWrite(motorTraseiroRe,LOW);
}

void setup() {
  pinMode(infraFrontal,INPUT);
  pinMode(infraEsquerdo,INPUT);
  pinMode(infraDireito,INPUT);
  pinMode(ultaSonicoFrontal,INPUT);
  
  pinMode(motorFrontalEsquerda,OUTPUT);
  pinMode(motorFrontalDireita,OUTPUT);
  pinMode(motorTraseiroFrente,OUTPUT);
  pinMode(motorTraseiroRe,OUTPUT);
  Serial.begin(9600);
  
  int cont = 0; //Zueira
  while(cont < 80){
    digitalWrite(motorTraseiroFrente,LOW);
    digitalWrite(motorTraseiroRe,HIGH);
    delay(27);
    digitalWrite(motorTraseiroFrente,HIGH);
    digitalWrite(motorTraseiroRe,LOW);
    delay(27);
    cont++;
  }
  
}
int cont = -1;
void loop() {

  

  if(encontrouObstaculo()){
    modoCurva = false;
    seguindo = false;
    bloqueado = true;
    cont = 0;
  }
  else if(encontrouFaixa()){
    modoCurva = true;
    seguindo = false;
    bloqueado = false;
    cont++;
  }
  else{ //Segue
    seguindo = true;  
    modoCurva = false;
    bloqueado = false;
    cont++;
  }
  



  if(seguindo){
   andarEmFrente();
   curvar('n',0);
   
   /*Testes*/
   if(digitalRead(infraEsquerdo) == LOW) curvar('d',200);
   if(digitalRead(infraDireito) == LOW) curvar('e',200);
   
  }
  else if(modoCurva){
   andarEmFrente();
   curvar('e',2000);
   modoCurva = false;
   seguindo = true;
  }
  else if(bloqueado){
    if(cont == 0) absBoladao();
    
  }
  
}

