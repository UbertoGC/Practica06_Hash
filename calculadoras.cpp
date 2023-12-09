#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <bitset>
#include <math.h>
#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21
using namespace std;
vector<bitset<512>> ConvertirBloques(string mensaje, bool LittleEdian){
    int i = 0;
    int max= 0;
    vector<bitset<512>> bloques;
    while(i < mensaje.size()){
        max += 56;
        bitset<512> nuevo_bloque = 0;
        int k = 0;
        int real_maximo = max-1;
        if(max > mensaje.size())
            real_maximo = mensaje.size()-1;
        if(LittleEdian){
            for (int j = real_maximo; j >= i; j--){
                int k_final = k+8;
                bitset<8> caracter_en_bits = mensaje[j];
                for (; k < k_final; k++)
                    nuevo_bloque[k] = caracter_en_bits[k%8]; 
            }
        }
        else{
            for (int j = i; j <= real_maximo; j++){
                int k_final = k+8;
                bitset<8> caracter_en_bits = mensaje[j];
                for (; k < k_final; k++)
                    nuevo_bloque[k] = caracter_en_bits[k%8]; 
            }
        }
        nuevo_bloque[512-64]=true;
        bloques.push_back(nuevo_bloque);
        i = max;
    }
    return bloques;
}
vector<uint32_t> ConvertirEnPalabras(bitset<512> bloque){
    vector<uint32_t> palabras;
    bitset<32> palabra = 0;
    for (int i = 0; i < 512; i++)
    {
        palabra[i%32] = bloque[i];
        if(i%32 == 31){
            palabras.push_back(palabra.to_ulong());
        }
    }
    return palabras;
}

uint32_t F(uint32_t B, uint32_t C, uint32_t D){
    return (B & C) | (~B & D);
}
uint32_t G(uint32_t B, uint32_t C, uint32_t D){
    return (B & D) | (C & ~D);
}
uint32_t H(uint32_t B, uint32_t C, uint32_t D){
    return (B ^ C ^ D);
}
uint32_t I(uint32_t B, uint32_t C, uint32_t D){
    return C ^ (B | ~D);
}
void MD5(string mensaje){
    
    uint32_t A = 0x67452301;
    uint32_t B = 0xEFCDAB89;
    uint32_t C = 0x98BADCFE;
    uint32_t D = 0x10325476;
    vector<uint32_t> registro_de_vectores;
    registro_de_vectores.push_back(A);
    registro_de_vectores.push_back(B); 
    registro_de_vectores.push_back(C);
    registro_de_vectores.push_back(D); 
    vector<bitset<512>> bloques = ConvertirBloques(mensaje,true);
    uint32_t Constante[64] = {
        0xd76aa478,0xe8c7b756,0x242070db,0xc1bdceee
        ,0xf57c0faf,0x4787c62a,0xa8304613,0xfd469501
        ,0x698098d8,0x8b44f7af,0xffff5bb1,0x895cd7be
        ,0x6b901122,0xfd987193,0xa679438e,0x49b40821
        ,0xf61e2562,0xc040b340,0x265e5a51,0xe9b6c7aa
        ,0xd62f105d,0x2441453,0xd8a1e681,0xe7d3fbc8
        ,0x21e1cde6,0xc33707d6,0xf4d50d87,0x455a14ed
        ,0xa9e3e905,0xfcefa3f8,0x676f02d9,0x8d2a4c8a
        ,0xfffa3942,0x8771f681,0x6d9d6122,0xfde5380c
        ,0xa4beea44,0x4bdecfa9,0xf6bb4b60,0xbebfbc70
        ,0x289b7ec6,0xeaa127fa,0xd4ef3085,0x4881d05
        ,0xd9d4d039,0xe6db99e5,0x1fa27cf8,0xc4ac5665
        ,0xf4292244,0x432aff97,0xab9423a7,0xfc93a039
        ,0x655b59c3,0x8f0ccc92,0xffeff47d,0x85845dd1
        ,0x6fa87e4f,0xfe2ce6e0,0xa3014314,0x4e0811a1
        ,0xf7537e82,0xbd3af235,0x2ad7d2bb,0xeb86d391
        };
    int S[64] ={
        S11,S12,S13,S14,
        S11,S12,S13,S14,
        S11,S12,S13,S14,
        S11,S12,S13,S14,
        S21,S22,S23,S24,
        S21,S22,S23,S24,
        S21,S22,S23,S24,
        S21,S22,S23,S24,
        S31,S32,S33,S34,
        S31,S32,S33,S34,
        S31,S32,S33,S34,
        S31,S32,S33,S34,
        S41,S42,S43,S44,
        S41,S42,S43,S44,
        S41,S42,S43,S44,
        S41,S42,S43,S44
    };
    for (auto bloque:bloques)
    {
        vector<uint32_t> palabras = ConvertirEnPalabras(bloque);
        for (int vuelta = 0; vuelta < 64; vuelta++)
        {
            if(vuelta < 16){
                registro_de_vectores[0] = (registro_de_vectores[0] + F(registro_de_vectores[1],registro_de_vectores[2],registro_de_vectores[3])) % 4294967296;
            }
            else if(vuelta < 32){
                registro_de_vectores[0] = (registro_de_vectores[0] + G(registro_de_vectores[1],registro_de_vectores[2],registro_de_vectores[3])) % 4294967296;
            }
            else if(vuelta < 48){
                registro_de_vectores[0] = (registro_de_vectores[0] + H(registro_de_vectores[1],registro_de_vectores[2],registro_de_vectores[3])) % 4294967296;
            }
            else{
                registro_de_vectores[0] = (registro_de_vectores[0] + I(registro_de_vectores[1],registro_de_vectores[2],registro_de_vectores[3])) % 4294967296;
            }
            registro_de_vectores[0] = (registro_de_vectores[0] + palabras[vuelta]) % 4294967296;
            registro_de_vectores[0] = (registro_de_vectores[0] + Constante[vuelta]) % 4294967296;
            registro_de_vectores[0] <<= S[vuelta];
            registro_de_vectores[0] = (registro_de_vectores[0] + registro_de_vectores[1]) % 4294967296;
            uint32_t TMP = registro_de_vectores[3];
            registro_de_vectores.erase(registro_de_vectores.end()-1);
            registro_de_vectores.insert(registro_de_vectores.begin(),TMP);
        }
    }
    for (int m = 0; m < 4; m++)
    {
        ostringstream ss;
        ss << hex << registro_de_vectores[m];
        string result = ss.str();
        cout << result <<" ";
    }
    cout<<endl;
}
int main()
{
    
    string mensaje;
    cin>>mensaje;
    MD5(mensaje);
    return 0;
}