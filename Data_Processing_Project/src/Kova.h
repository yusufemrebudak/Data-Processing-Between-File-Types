/*
 * Kova.h
 *
 *  Created on: 16 May 2020
 *      Author: yusuf
 */

#include "genel.h"
#include "Araba.h"
#define KOVA_SAYISI 3

class Kova{
private :
	int adres;
	Araba* kovaElemanlari[KOVA_SAYISI];
public:
	// olu�turulan kova nesnesi otomatikman 3 nesneli araba s�n�f�na ait kovaElemanlar� nesne arrayi olu�turur.
	Kova(){
		adres = -1;
		for(int i=0 ; i<KOVA_SAYISI ; i++){
			kovaElemanlari[i] = new Araba("",0,0,0,0,0,0,"");
		}
	}
	Kova(const Kova& orig){}
	virtual ~Kova(){}

	// 3 tane kovadan hangi kovay� okumak istedi�imizi parametre veririz ve okuruz
	Araba* okuEleman(int n){
		if(n>=0 && n<KOVA_SAYISI){
			return kovaElemanlari[n];
		}
		else {
			return NULL;
		}
	}
	void yazEleman(int n, Araba* a) { // �stenilen kovaya yaz�m yap�l�r.
		if(n>=0 && n<KOVA_SAYISI && a!=NULL){
			kovaElemanlari[n] = a;
		}
	}
	// a��r� y�kledi�imiz << eleman�  kova nesnesini g�ren << operator� bu friend fonksiyonu �al��t�r�r.
	friend ostream& operator <<(ostream& o , Kova& ie){
		o<<"KOVA ADRES� :"<<ie.adres<<endl;
		o<<"ELEMAN 0 :"<<*ie.kovaElemanlari[0]<<endl;
		o<<"ELEMAN 1 :"<<*ie.kovaElemanlari[1]<<endl;
		o<<"ELEMAN 2 :"<<*ie.kovaElemanlari[2]<<endl;
		o<<"-----------------------------------"<<endl;
		return o;
	}
	// bu sat�rdan a��a��daki fonksiyonlar� a��klamaya gerek duymad�m kolay olduklar� i�in.
	int okuAdres(){
		return adres;
	}
	static int KovaSayisi(){
		return KOVA_SAYISI;
	}
	int kovaBoyutu(){
		return KOVA_SAYISI* ( kovaElemanlari[0]->boyut() );
	}
	void binaryOkuKova(fstream& dosya){
		for(int i=0 ; i<KOVA_SAYISI ; i++){
			kovaElemanlari[i]->binaryOku(dosya);
		}
	}
	void binaryOkuKova(fstream& dosya , int adr){
			adres = adr;
			dosya.seekg(adres * kovaBoyutu(), ios::beg); // i�aret�i kafas�n� istedi�imiz adrese al�r�z.
			binaryOkuKova(dosya);
		}
	void binaryYazKova(fstream& dosya){
			for(int i=0 ; i<KOVA_SAYISI ; i++){
				kovaElemanlari[i]->binaryYaz(dosya);
			}
		}
	void binaryYazKova(fstream& dosya , int adr){
				adres = adr;
				dosya.seekp(adres * kovaBoyutu(), ios::beg);
				binaryYazKova(dosya);
			}


};
