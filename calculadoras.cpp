#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <math.h>
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
}
template<std::size_t SIZE>
int bitSetToInt(std::bitset<SIZE> bitSet) {
    if (!bitSet[SIZE - 1]) return bitSet.to_ulong();
    bitSet.flip();
    return -(bitSet.to_ulong() + 1);
}
bitset<32> F(bitset<32> B, bitset<32> C, bitset<32> D){
    return (B & C) | (~B & D);
}
bitset<32> G(bitset<32> B, bitset<32> C, bitset<32> D){
    return (B & D) | (C & ~D);
}
bitset<32> H(bitset<32> B, bitset<32> C, bitset<32> D){
    return (B ^ C ^ D);
}
bitset<32> I(bitset<32> B, bitset<32> C, bitset<32> D){
    return C ^ (B | ~D);
}
void SumMod(bitset<32> &A,bitset<32> B){
    long int mod = pow(2,32);
    long int A_valor = bitSetToInt(A);
    long int B_valor = bitSetToInt(B);
    long int R = A_valor + B_valor;
    R = R % mod;
    A = R;
}
void MD5(string mensaje){
    bitset<32> A = 0x67452301;
    bitset<32> B = 0xEFCDAB89;
    bitset<32> C = 0x98BADCFE;
    bitset<32> D = 0x10325476;
    vector<bitset<32>> registro_de_vectores;
    registro_de_vectores.push_back(A);
    registro_de_vectores.push_back(B); 
    registro_de_vectores.push_back(C);
    registro_de_vectores.push_back(D); 
    vector<bitset<512>> bloques = ConvertirBloques(mensaje,true);
    for (auto bloque:bloques)
    {
        int indice_bloque = 0;
        for (int vuelta = 0; vuelta < 64; vuelta++)
        {
            if(vuelta < 16){
                SumMod(registro_de_vectores[0], F(registro_de_vectores[1],registro_de_vectores[2],registro_de_vectores[3]));
            }
            else if(vuelta < 32){
                SumMod(registro_de_vectores[0], G(registro_de_vectores[1],registro_de_vectores[2],registro_de_vectores[3]));
            }
            else if(vuelta < 48){
                SumMod(registro_de_vectores[0], H(registro_de_vectores[1],registro_de_vectores[2],registro_de_vectores[3]));
            }
            else{
                SumMod(registro_de_vectores[0], I(registro_de_vectores[1],registro_de_vectores[2],registro_de_vectores[3]));
            }
        }
        modf()
    }
}
int main()
{
    
    string mensaje;
    cin>>mensaje;
    MD5(mensaje);
    return 0;
}