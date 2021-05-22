/*
 * HashDosyasi.h
 *
 *  Created on: 16 May 2020
 *      Author: yusuf
 */

#define EV_ADRESI_SAYISI 23
#include "Kova.h"
#include "SiraliDosya.h"
class HashDosyasi{
private:
	fstream hashDosyasi;
	int kayitSayisi;
public:
	HashDosyasi( char* dosyaAdi){
		kayitSayisi = 0;
		hashDosyasi.open("hashArabalar.bin ", ios::out | ios::trunc | ios::in | ios::binary );
		Kova* temp = new Kova();
		for(int i=0;i <EV_ADRESI_SAYISI ;i++){ //ev_adresi_say�s� nca kovalardaki nesneler s�ras�yla hashDosyas� na yaz�l�r
			temp->binaryYazKova(hashDosyasi,i);
		}
		SiraliDosya* sirali = new SiraliDosya(dosyaAdi);
		Araba* a;
		// arabalar.bin adl� binary dosyadan s�ras�yla okunup ismi a olan araba nesnesine  atan�r.
		for(int RRN=0; (a = sirali->kayitOku(RRN)) !=NULL ; RRN++ ){
			char* isim = a->okuIsim(); // araban�n ismi okunur
				if(isim[0] != '*'){ // silinmemi� ise hashDosyas� na eklenmek �zere hashEkle fonksiyonuna verilir.
					hashEkle(a);
				}
		}
		sirali->~SiraliDosya();
	}
	HashDosyasi(const HashDosyasi& orig){}
	virtual ~HashDosyasi(){}
	// bu y�nteme hashleme denir.isim de�i�keninin sahip oldu�u character topluluklar�na g�re bir adres al�r.
	int hashEvAdresi(const char* isim){
		int x = 0;
		int karakterSayisi = strlen(isim);
		for(int i=0 ; i<karakterSayisi ; i++){
			x = 17*x+isim[i];  //17 taban�na g�re �evrilir.
		}
		int evAdresi = x % EV_ADRESI_SAYISI; // modu al�n�r.
		if(evAdresi<0){
		evAdresi += EV_ADRESI_SAYISI;
		return evAdresi;
		}


	}
	// bu fonksiyonda ise bir sonraki kovaya rahat ge�i� yapmak i�in art�m degerleri belirlenir.
	int hashArtim(const char* isim){
		int x = 0;
		int karakterSayisi = strlen(isim);
		for(int i=0 ; i<karakterSayisi ; i++){
			x = 17*x+isim[i];
		}
		int artim = ((int)(x/EV_ADRESI_SAYISI)) % EV_ADRESI_SAYISI;
		if(artim < 0){
			artim += EV_ADRESI_SAYISI;
		}
	return artim;
	}

	void hashYazdir(){
		Kova* k = new Kova();
		basaSar();
		//s�ras�yla ev adresi say�s�nca kovaya s�ras�yla kay�tlar yaz�l�r ve konsola bast�r�l�r.
		for(int i=0 ; i<EV_ADRESI_SAYISI ; i++){
			k->binaryOkuKova(hashDosyasi,i);
			cout<<*k;
		}
	basaSar();
	}
	void hashEkle(Araba* a){
		Kova gecici;
		if(kayitSayisi == (gecici.KovaSayisi()*EV_ADRESI_SAYISI)){ // tablo dolum kontrolu
			cout<<"Tablo dolu . Ekleme yap�lamaz ."<<endl;
		}
		if(a==NULL){	// parametre null ise girdi almak i�in kontrol blo�u.
			cin>>(*a);
		}
		char* eklenecekIsim = a->okuIsim();
		int evAdresi = hashEvAdresi(eklenecekIsim); // eklenecekIsim haslenir ve evAdresi de�i�kenine at�l�r.
		int artim = hashArtim(eklenecekIsim); // artim de�i�kenine eklenecekIsim in art�m degeri at�l�r.
		int arananAdres = evAdresi;
		Araba* eleman;
		Kova* k = new Kova();
		basaSar();
			while(true){
				k->binaryOkuKova(hashDosyasi,arananAdres); // belirli adrese gidilip hashDosyas�ndan okuma yap�l�r.
				for(int i=0 ; i<k->KovaSayisi() ; i++){ // 3 kova vard�r ve s�ras�yla okunur .
					eleman = k->okuEleman(i);
					char* isim = eleman->okuIsim();
					if(strcmp(isim,eklenecekIsim) == 0){ // e�er eklemek istedi�im isim var ise ekleme yap�lmadan ��k�l�r.
						cout<<"�ifte kay�t! Zaten"<<a->okuIsim()<<" isimli bir kay�t oldu�undan ekleme yap�lamamaktad�r."<<endl;
						return;
					}
					if(strcmp(isim,"")==0 ||isim[0]== '*'){ // e�er mezar ta�� veya bo�luk var ise yaz�m i�lemi yap�l�r.
						k->yazEleman(i,a);
						k->binaryYazKova(hashDosyasi,k->okuAdres());
						kayitSayisi++;
						cout<<a->okuIsim()<<" isimli kayit ba�ar�yla eklenmi�tir."<<"\n";
						cout<<"Ev adresi: "<<evAdresi<<" Artim degeri: "<<artim<<endl;
						cout<<"Eklendi�i adres :"<<arananAdres<<" Eklendi�i s�ra: "<< i <<endl;
					basaSar();
					return ;
					}
				}
			arananAdres = (arananAdres + artim) % EV_ADRESI_SAYISI; // gitti�i adreste yer bulamazsa diye di�er adrese ge�i� yapmas� i�in.
			}


	}
		// Arama fonksiyonu
		Kova* hashArama(char* isim){
		int evAdresi = hashEvAdresi(isim);
		int artim = hashArtim(isim);
		int arananAdres = evAdresi;
		int sorguSayisi = 0 ;
		Kova* k = new Kova();
		Araba* eleman;

			while(true){
			k->binaryOkuKova(hashDosyasi,arananAdres);// adresine gidiip okuma yap�l�r.
				for(int i=0; i<k->KovaSayisi() ;i++){ // 3 kovadan hangisinde olaca�� belli de�ildir s�ras�yla aran�r.
					eleman = k->okuEleman(i); // belirli adresteki ilk kova eleman�   eleman  a atan�r.
					char* okunanIsim = eleman->okuIsim();
				  	  	  if(strcmp(isim,okunanIsim) == 0){ // isim ve okunanIsim kontrolu yap�l�r ayn� ise bulunmu� demektir ve bilgiler konsola bas�l�r.
				  	  	  cout<<isim<<" isimli kay�t : "<<arananAdres<<".Adreste , "<<i<<". s�rada "<<sorguSayisi<<". sorguda bulundu"<<endl;
				  	  	  return k;

				  	  	  }
				  	  	  if(strcmp(okunanIsim,"") == 0){
				  	  		  return NULL;
				  	  		  cout<<isim <<" isimli  kay�t bulunamad� "<<endl;
				  	  	  }
				  	  	  if(okunanIsim[0] == '*') continue;

				}
			sorguSayisi++;
			arananAdres = (arananAdres + artim) % EV_ADRESI_SAYISI ;
		}

	}
	void hashSil(char* isim) {
		Kova* k = new Kova();
		k = hashArama(isim); // hashArama fonksiyonu k de�i�kenine uygun adresteki kovay� d�ner .
		Araba* a;
		if(k!= NULL){ // NULL de�ilse girer.
				for(int i=0 ; i<k->KovaSayisi() ; i++){ // Adreste bulunan kovan�n nesneleri gezilir.
					a = k->okuEleman(i);
					char* okunanIsim = a->okuIsim();
					if(strcmp(isim,okunanIsim) == 0){ // isim ile okunanIsim ayn� oldu�unda if �al���r.
						a->sil();  // silme i�lemi ger�ekle�ir.
						k->yazEleman(i,a); // tekrar kovan�n uygun nesnesine  geri at�l�r.
						k->binaryYazKova(hashDosyasi,k->okuAdres()); // dosyaya yaz�l�r.
						cout<<isim<<" isimli kay�t ba�ar�yla silinmi�tir"<<endl;
					}
				}

			}
	}
	// Kulland���m�z alan� y�zde olarak buluyoruz, Kay�t say�m�z toplam memory e b�l�n�r.
	void yogunlasmaFaktoruHesapla() {
		Kova* k = new Kova();
		float oran = (  float((kayitSayisi)) / float((EV_ADRESI_SAYISI * k->kovaBoyutu())) );
		float yuzdeOran = oran*100;
		cout<<endl<<"Y�zde oran : "<<yuzdeOran;
		cout<<"  Dosyan�n yeniden d�zenlenmesini gerektirecek bir durum yoktur. ";

	}
//i�aret�i ve bayraklar� s�f�rlamak i�in clear , tampondaki bilgileri dosyaya yazd�rmak i�in flush fonk kulland�k.
	void basaSar(){
		hashDosyasi.clear();
		hashDosyasi.flush();
	}



};
