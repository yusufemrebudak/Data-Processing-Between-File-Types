//============================================================================
// Name        : LAB_5.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include "HashDosyasi.h"
using namespace std;

void binaryDosyaYenidenYaz(){
    Araba *arabalar[50];
    int i;
    string satir;
    ifstream dosya("arabalar.txt", ios::in);
    fstream binDosya("arabalar.bin", ios::out|ios::in|ios::trunc|ios::binary);
    // txt dosyadaki kayýt içermeyen ilk iki satir okunur
    getline(dosya, satir);
    getline(dosya, satir);
    for(i=0; i<50; i++){
            arabalar[i] = new Araba();
            arabalar[i]->txtOku(dosya);
            arabalar[i]->binaryYaz(binDosya);
    }
    dosya.close();
    binDosya.close();
}

int main() {
    binaryDosyaYenidenYaz();
    HashDosyasi hb("arabalar.bin");
    hb.hashYazdir();
    Araba a1("Opel Manta", 24, 4, 116, 75, 2158, 73, "Europe");
    Araba a2("Toyota Mark", 20, 6, 156, 122, 2807, 73, "Japan");
    hb.hashArama("Subaru DL");
    hb.hashArama("Chrysler Lebaron Salon");
    hb.hashSil("Cadillac Eldorado");
    hb.hashEkle(&a1);
    hb.hashEkle(&a2);
    hb.hashSil("Honda Civic");
    hb.hashArama("Dodge Aries");
    hb.hashArama("Toyota Mark");
     hb.hashYazdir();
    hb.yogunlasmaFaktoruHesapla();
    return 0;
}
