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
	// oluþturulan kova nesnesi otomatikman 3 nesneli araba sýnýfýna ait kovaElemanlarý nesne arrayi oluþturur.
	Kova(){
		adres = -1;
		for(int i=0 ; i<KOVA_SAYISI ; i++){
			kovaElemanlari[i] = new Araba("",0,0,0,0,0,0,"");
		}
	}
	Kova(const Kova& orig){}
	virtual ~Kova(){}

	// 3 tane kovadan hangi kovayý okumak istediðimizi parametre veririz ve okuruz
	Araba* okuEleman(int n){
		if(n>=0 && n<KOVA_SAYISI){
			return kovaElemanlari[n];
		}
		else {
			return NULL;
		}
	}
	void yazEleman(int n, Araba* a) { // Ýstenilen kovaya yazým yapýlýr.
		if(n>=0 && n<KOVA_SAYISI && a!=NULL){
			kovaElemanlari[n] = a;
		}
	}
	// aþýrý yüklediðimiz << elemaný  kova nesnesini gören << operatorü bu friend fonksiyonu çalýþtýrýr.
	friend ostream& operator <<(ostream& o , Kova& ie){
		o<<"KOVA ADRESÝ :"<<ie.adres<<endl;
		o<<"ELEMAN 0 :"<<*ie.kovaElemanlari[0]<<endl;
		o<<"ELEMAN 1 :"<<*ie.kovaElemanlari[1]<<endl;
		o<<"ELEMAN 2 :"<<*ie.kovaElemanlari[2]<<endl;
		o<<"-----------------------------------"<<endl;
		return o;
	}
	// bu satýrdan aþþaðýdaki fonksiyonlarý açýklamaya gerek duymadým kolay olduklarý için.
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
			dosya.seekg(adres * kovaBoyutu(), ios::beg); // iþaretçi kafasýný istediðimiz adrese alýrýz.
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
