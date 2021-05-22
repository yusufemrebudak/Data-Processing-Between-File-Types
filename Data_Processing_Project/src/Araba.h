/*
 * Araba.h
 *
 *  Created on: 16 May 2020
 *      Author: yusuf
 */

#ifndef ARABA_H
#define ARABA_H

#include "genel.h"

class Araba {
public:
    Araba(){}
    Araba(const char* i, float m, int sil, double dev, float bg, double agr, int mod, const char* men){
        strcpy(isim, i);
        mpg = m;
        silindir = sil;
        devinim = dev;
        beygirGucu = bg;
        agirlik = agr;
        model = mod;
        strcpy(mensei, men);
    }
    Araba(const Araba& orig){}
    virtual ~Araba(){}
    friend ostream& operator<<(ostream& o, Araba& a){
        o<<"#"<<a.isim<<"||"<<a.mpg<<"||"<<a.silindir<<"||"<<
                a.devinim<<"||"<<a.beygirGucu<<"||"<<
                a.agirlik<<"||"<<a.model<<"||"<<a.mensei<<"\n";
        o.flush();
        return o;
    }
    friend istream& operator>>(istream& i, Araba& a){
        string data;
        cout<<"isim: ";
        getline(i, data, '\n');
        strcpy(a.isim, data.c_str());
        cout<<"mpg: ";
        i>>a.mpg;
        cout<<"silindir: ";
        i>>a.silindir;
        cout<<"devinim: ";
        i>>a.devinim;
        cout<<"beygirGücü: ";
        i>>a.beygirGucu;
        cout<<"agirlik: ";
        i>>a.agirlik;
        cout<<"model: ";
        i>>a.model;
        cout<<"mensei: ";
        i>>a.mensei;
        i.ignore();
        return i;
    }
    void txtOku(ifstream& dosya){
        string data;
        getline(dosya, data, '\t');
        strcpy(isim, data.c_str());
        getline(dosya, data, '\t');
        mpg = atof(data.c_str());
        getline(dosya, data, '\t');
        silindir = atoi(data.c_str());
        getline(dosya, data, '\t');
        devinim = (double)atof(data.c_str());
        getline(dosya, data, '\t');
        beygirGucu = atof(data.c_str());
        getline(dosya, data, '\t');
        agirlik = (double)atof(data.c_str());
        getline(dosya, data, '\t');
        model = atoi(data.c_str());
        getline(dosya, data, '\n');
        strcpy(mensei, data.c_str());
    }
    void binaryOku(fstream& dosya){
        dosya.read(isim, sizeof(isim));
        dosya.read(reinterpret_cast<char*>(&mpg), sizeof(float));
        dosya.read(reinterpret_cast<char*>(&silindir), sizeof(int));
        dosya.read(reinterpret_cast<char*>(&devinim), sizeof(double));
        dosya.read(reinterpret_cast<char*>(&beygirGucu), sizeof(float));
        dosya.read(reinterpret_cast<char*>(&agirlik), sizeof(double));
        dosya.read(reinterpret_cast<char*>(&model), sizeof(int));
        dosya.read(mensei, sizeof(mensei));
    }
    void binaryYaz(fstream& dosya){
        dosya.write(isim, sizeof(isim));
        dosya.write(reinterpret_cast<const char*>(&mpg), sizeof(float));
        dosya.write(reinterpret_cast<const char*>(&silindir), sizeof(int));
        dosya.write(reinterpret_cast<const char*>(&devinim), sizeof(double));
        dosya.write(reinterpret_cast<const char*>(&beygirGucu), sizeof(float));
        dosya.write(reinterpret_cast<const char*>(&agirlik), sizeof(double));
        dosya.write(reinterpret_cast<const char*>(&model), sizeof(int));
        dosya.write(mensei, sizeof(mensei));
    }
    void kaydiOku(fstream& dosya, int siraNo){
        dosya.seekg((siraNo-1)*boyut(),ios::beg);
        binaryOku(dosya);
    }
    void kaydiYaz(fstream& dosya, int siraNo){
        dosya.seekp((siraNo-1)*boyut(),ios::beg);
        binaryYaz(dosya);
    }
    void sil(){
        isim[0] = '*';
    }
    int boyut(){
        return sizeof(isim)+2*sizeof(float)+2*sizeof(int)+
                2*sizeof(double)+sizeof(mensei);
    }
    char* okuIsim(){    return isim;    }
    int okuModel(){    return model;    }

private:
    char isim[50];
    float mpg;
    int silindir;
    double devinim;
    float beygirGucu;
    double agirlik;
    int model;
    char mensei[20];
};

#endif /* ARABA_H */
