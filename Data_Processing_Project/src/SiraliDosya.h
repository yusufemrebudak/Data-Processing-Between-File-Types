/*
 * SiraliDosya.h
 *
 *  Created on: 16 May 2020
 *      Author: yusuf
 */
#ifndef SIRALIDOSYA_H
#define SIRALIDOSYA_H

#include "genel.h"
#include "Araba.h"

class SiraliDosya {
private:
char* dosyaAdi;
fstream dosya;
deque<int> boslarListesi;
//
public:
    SiraliDosya(char* dosyaAdi){
        this->dosyaAdi = dosyaAdi;
        dosya.open(dosyaAdi, ios::out|ios::in|ios::binary);
        basaSar();
    }
    SiraliDosya(){}
    SiraliDosya(const SiraliDosya& orig){}
    virtual ~SiraliDosya(){
        dosya.close();
    }
    Araba* kayitOku(int RRN){
        Araba* a = new Araba();
        int kayitSayisi = bulKayitSayisi();
        if(RRN<kayitSayisi){
            a->kaydiOku(dosya, RRN+1);
            return a;
        }
        return NULL;
    }

    void basaSar(){
        dosya.clear();
        dosya.flush();
    }
    void kayitSil(char* isim, int RRN){
        Araba a;
        basaSar();
        a.kaydiOku(dosya,(RRN+1));
        a.sil();
        a.kaydiYaz(dosya, (RRN+1));
        basaSar();
        boslarListesi.push_back(RRN);
        cout<<RRN<<". RRN boþlar listesine eklenmiþtir."<<endl;
        cout<<isim<<" isimli kayit dosyadan silinmiþtir."<<"\n";
    }
    int kayitEkle(Araba& a){
        int RRN = -1;
        basaSar();
        if (boslarListesi.size()>0){
            RRN = boslarListesi.front();
            boslarListesi.pop_front();
        }
        if(RRN==-1){
            cout<<"Boþlar listesinde boþ yer bulunamadý."<<
                    " Kayit sona eklenecek."<<endl;

            RRN = bulKayitSayisi();
            a.binaryYaz(dosya);
        }
        else{
            cout<<"Boþlar listesinde boþ yer bulundu. RRN: "<<RRN<<endl;
            a.kaydiYaz(dosya, (RRN+1));
        }
        cout<<"Yeni kayit dosyaya eklenmiþtir."<<endl;
        cout<<a;
        basaSar();
        return RRN;
    }
    streampos bulKayitSayisi(){
        Araba a;
        streampos bas, son;
        dosya.seekp(0,ios::beg);
        bas = dosya.tellp();
        dosya.seekp(0,ios::end);
        son = dosya.tellp();
        int kayitSayisi = int(son-bas)/a.boyut();
        return kayitSayisi;
    }
};

#endif /* SIRALIDOSYA_H */
