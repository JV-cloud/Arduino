// Experimento 3 - Aula 2 - RFID

// Exemplo de leitura de ID de uma tag RFID Addicore 13.56MHz

#include <AddicoreRFID.h>
#include <SPI.h>

#define  uchar unsigned char
#define uint  unsigned int

uchar fifobytes;
uchar fifoValue;

AddicoreRFID myRFID; // cria um objeto AddicoreRFID para controlar o módulo RFID

/////////////////////////////////////////////////////////////////////
//setando nossas pinagens
/////////////////////////////////////////////////////////////////////

const int chipSelectPin = 10;
const int NRSTPD = 5;

//Comprimento máximo do array
#define MAX_LEN 16

void setup() {                
   Serial.begin(9600);                        // Pino SOUT do leitor RFID conectado ao pino Serial RX a 9600bps
 
  // start the SPI library:
  SPI.begin();

  Serial.print("hello world");
  
  pinMode(chipSelectPin,OUTPUT);              // Definindo o pino digital 10 como OUTPUT para conectá-lo ao pino RFID / ENABLE
    digitalWrite(chipSelectPin, LOW);         // Ativando o leitor RFID
  pinMode(NRSTPD,OUTPUT);                     // Definindo o pino digital 5, não redefinir e desligar
    digitalWrite(NRSTPD, HIGH);

  myRFID.AddicoreRFID_Init();  
}

void loop()
{
    uchar i, tmp, checksum1;
  uchar status;
        uchar str[MAX_LEN];
        uchar RC_size;
        uchar blockAddr;  // Endereço de bloco de operação de seleção 0 a 63
        String mynum = "";

        str[1] = 0x4400;
        
  // Encontra tags e tretorna tipo de tag
  status = myRFID.AddicoreRFID_Request(PICC_REQIDL, str);
  Serial.print( status);
  if (status == MI_OK)
  {
          Serial.println("Tag RFID detectada");
          Serial.print("Tipo de tag:\t\t");
          uint tagType = str[0] << 8;
          tagType = tagType + str[1];
          switch (tagType) {
            case 0x4400:
              Serial.println("Mifare UltraLight");
              break;
            case 0x400:
              Serial.println("Mifare One (S50)");
              break;
            case 0x200:
              Serial.println("Mifare One (S70)");
              break;
            case 0x800:
              Serial.println("Mifare Pro (X)");
              break;
            case 0x4403:
              Serial.println("Mifare DESFire");
              break;
            default:
              Serial.println("Unknown");
              break;
          }
  }

  // Anti-colisão, retorna os 4 bytes do número de série da tag
  status = myRFID.AddicoreRFID_Anticoll(str);
  if (status == MI_OK)
  {
          checksum1 = str[0] ^ str[1] ^ str[2] ^ str[3];
          Serial.print("O numero da tag e:\t");
          Serial.print(str[0]);
            Serial.print(" , ");
          Serial.print(str[1]);
            Serial.print(" , ");
          Serial.print(str[2]);
            Serial.print(" , ");
          Serial.println(str[3]);

          Serial.print("Ler Checksum:\t\t");
            Serial.println(str[4]);
          Serial.print("Checksum Calculado:\t");
            Serial.println(checksum1);
            
            // Deve realmente verificar todos os pares, mas por enquanto vamos usar o primeiro
            if(str[0] == 197)                      // Você pode alterar esse valor de acordo com o primeiro byte da sua tag, localizando o ID do cartão por meio do Serial Monitor
            {
                Serial.println("\nRFID indetificado!\n");
            } else if(str[0] == 244) {             // Você pode alterar esse valor de acordo com o primeiro byte da sua tag, localizando o ID do cartão por meio do Serial Monitor
                Serial.println("\nRFID nao identificado!\n");
            }
            Serial.println();
            delay(1000);
  }
    
        myRFID.AddicoreRFID_Halt();      // Comando para hibernação (halt) da tag              

}
