#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <math.h>

#define POLY        0x1021
using namespace std;

//CODIGO DE HAMMING

// Función para generar código hamming
vector<int> generateHammingCode(
        vector<int> msgBits, int m, int r)
{
    // Almacena el código Hamming
    vector<int> hammingCode(r + m);

    // Encuentra posiciones de bits redundantes
    for (int i = 0; i < r; ++i) {

        // Colocando -1 en bits redundantes
        // lugar para identificarlo más tarde

        hammingCode[pow(2, i) - 1] = -1;
    }

    int j = 0;

    // Iterar para actualizar el código
    for (int i = 0; i < (r + m); i++) {

        // Colocando msgBits donde -1 es
        // ausente es decir, excepto redundante
        // bits todas las posiciones son msgBits


        if (hammingCode[i] != -1) {
            hammingCode[i] = msgBits[j];
            j++;
        }
    }

    for (int i = 0; i < (r + m); i++) {

        // Si el bit actual no es redundante
        // bit y luego continuar
        if (hammingCode[i] != -1)
            continue;

        int x = log2(i + 1);
        int one_count = 0;



        // Encuentra los bits de mensaje que contienen
        // establece el bit en la posición x'th


        for (int j = i + 2;
             j <= (r + m); ++j) {

            if (j & (1 << x)) {
                if (hammingCode[j - 1] == 1) {
                    one_count++;
                }
            }
        }

        // Generando código de hamming para
        // paridad uniforme
        if (one_count % 2 == 0) {
            hammingCode[i] = 0;
        }
        else {
            hammingCode[i] = 1;
        }
    }

    // Devuelve el código generado
    return hammingCode;
}

// Función para encontrar el código de Hamming
// del bit de mensaje dado msgBit []

void findHammingCode(vector<int>& msgBit)
{

    // Tamaño de bits del mensaje
    int m = msgBit.size();

    // r es el número de bits redundantes
    int r = 1;

    // Encuentra no. de bits redundantes
    while (pow(2, r) < (m + r + 1)) {
        r++;
    }

    // Generando código
    vector<int> ans
            = generateHammingCode(msgBit, m, r);



    // Imprime el código
    cout << "Message bits are: ";
    for (int i = 0; i < msgBit.size(); i++)
        cout << msgBit[i] << " ";

    cout << "\nHamming code is: ";
    for (int i = 0; i < ans.size(); i++)
        cout << ans[i] << " ";
}



//CODIGO DE REDUNDANCIA CICLICA

uint16_t crc16(unsigned char *addr, int num, uint16_t crc)
{
    int i;
    for (; num > 0; num--)              /* Step through bytes in memory */
    {
        crc = crc ^ (*addr++ << 8);     /* Fetch byte from memory, XOR into CRC top byte*/
        for (i = 0; i < 8; i++)             /* Prepare to rotate 8 bits */
        {
            if (crc & 0x8000)            /* b15 is set... */
                crc = (crc << 1) ^ POLY;    /* rotate and XOR with polynomic */
            else                          /* b15 is clear... */
                crc <<= 1;                  /* just rotate */
        }                             /* Loop for 8 bits */
        crc &= 0xFFFF;                  /* Ensure CRC remains 16-bit value */
    }                               /* Loop until num=0 */
    return(crc);                    /* Return updated CRC */
}

int main (int argc , char* argv[])
{
    unsigned char data1[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    unsigned char data2[] = {'5', '6', '7', '8', '9'};
    unsigned short c1, c2;
    c1 = crc16(data1, 9, 0xffff);
    c2 = crc16(data1, 4, 0xffff);
    c2 = crc16(data2, 5, c2);
    printf("%04x\n", c1);
    printf("%04x\n", c2);
    // Bits de mensaje dados
    vector<int> msgBit = { 0, 1, 0, 1 };

    // Llamada de función
    findHammingCode(msgBit);

    return 0;


}
//CODIGO CKECKSUM

void checksum(){
    char a[20], b[20];
    char sum[20],complement[20];
    int i, length;
    /*
     * printf("inserte el primer numero binario");
     * scanf("%s",&a);
     * printf("Inserte el segundo numero binario");
     * scanf("%s",&a);
     */
    if(strlen(a)==strlen(b)){
        length = strlen(a);
        char carry = '0';

        for(i=length-1;i>=0;i--){
            if(a[i]=='0' && b[i]=='0' && carry=='0'){
                sum[i]='0';
                carry='0';
            }
            else if(a[i]=='0' && b[i]=='0' && carry=='1'){
                sum[i]='1';
                carry='0';
            }
            else if(a[i]=='0' && b[i]=='1' && carry=='0'){
                sum[i]='1';
                carry='0';
            }
            else if(a[i]=='0' && b[i]=='1' && carry=='1'){
                sum[i]='1';
                carry='0';
            }
            else if(a[i]=='1' && b[i]=='1' && carry=='0'){
                sum[i]='1';
                carry='0';
            }
            else if(a[i]=='1' && b[i]=='1' && carry=='1'){
                sum[i]='1';
                carry='0';
            }
            else if(a[i]=='1' && b[i]=='1' && carry=='0'){
                sum[i]='1';
                carry='0';
            }
            else if(a[i]=='1' && b[i]=='1' && carry=='1'){
                sum[i]='1';
                carry='0';
            }
            else{
                break;
            }
            //printf("Sum=%c%s",carry,sum);

            for(i=0;i<length;i++){
                if(sum[i]=='0'){
                    complement[i]='1';
                }
                else{
                    complement[i]='0';
                }
                if(carry=='1')
                    carry='0';
                else
                    carry='1';
                //printf("Checksum=%c%s",carry,complement);


            }
            //printf("Wrong input strings");
        }
    }
}