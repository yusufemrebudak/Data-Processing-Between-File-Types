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
		for(int i=0;i <EV_ADRESI_SAYISI ;i++){ //ev_adresi_sayýsý nca kovalardaki nesneler sýrasýyla hashDosyasý na yazýlýr
			temp->binaryYazKova(hashDosyasi,i);
		}
		SiraliDosya* sirali = new SiraliDosya(dosyaAdi);
		Araba* a;
		// arabalar.bin adlý binary dosyadan sýrasýyla okunup ismi a olan araba nesnesine  atanýr.
		for(int RRN=0; (a = sirali->kayitOku(RRN)) !=NULL ; RRN++ ){
			char* isim = a->okuIsim(); // arabanýn ismi okunur
				if(isim[0] != '*'){ // silinmemiþ ise hashDosyasý na eklenmek üzere hashEkle fonksiyonuna verilir.
					hashEkle(a);
				}
		}
		sirali->~SiraliDosya();
	}
	HashDosyasi(const HashDosyasi& orig){}
	virtual ~HashDosyasi(){}
	// bu yönteme hashleme denir.isim deðiþkeninin sahip olduðu character topluluklarýna göre bir adres alýr.
	int hashEvAdresi(const char* isim){
		int x = 0;
		int karakterSayisi = strlen(isim);
		for(int i=0 ; i<karakterSayisi ; i++){
			x = 17*x+isim[i];  //17 tabanýna göre çevrilir.
		}
		int evAdresi = x % EV_ADRESI_SAYISI; // modu alýnýr.
		if(evAdresi<0){
		evAdresi += EV_ADRESI_SAYISI;
		return evAdresi;
		}


	}
	// bu fonksiyonda ise bir sonraki kovaya rahat geçiþ yapmak için artým degerleri belirlenir.
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
		//sýrasýyla ev adresi sayýsýnca kovaya sýrasýyla kayýtlar yazýlýr ve konsola bastýrýlýr.
		for(int i=0 ; i<EV_ADRESI_SAYISI ; i++){
			k->binaryOkuKova(hashDosyasi,i);
			cout<<*k;
		}
	basaSar();
	}
	void hashEkle(Araba* a){
		Kova gecici;
		if(kayitSayisi == (gecici.KovaSayisi()*EV_ADRESI_SAYISI)){ // tablo dolum kontrolu
			cout<<"Tablo dolu . Ekleme yapýlamaz ."<<endl;
		}
		if(a==NULL){	// parametre null ise girdi almak için kontrol bloðu.
			cin>>(*a);
		}
		char* eklenecekIsim = a->okuIsim();
		int evAdresi = hashEvAdresi(eklenecekIsim); // eklenecekIsim haslenir ve evAdresi deðiþkenine atýlýr.
		int artim = hashArtim(eklenecekIsim); // artim deðiþkenine eklenecekIsim in artým degeri atýlýr.
		int arananAdres = evAdresi;
		Araba* eleman;
		Kova* k = new Kova();
		basaSar();
			while(true){
				k->binaryOkuKova(hashDosyasi,arananAdres); // belirli adrese gidilip hashDosyasýndan okuma yapýlýr.
				for(int i=0 ; i<k->KovaSayisi() ; i++){ // 3 kova vardýr ve sýrasýyla okunur .
					eleman = k->okuEleman(i);
					char* isim = eleman->okuIsim();
					if(strcmp(isim,eklenecekIsim) == 0){ // eðer eklemek istediðim isim var ise ekleme yapýlmadan çýkýlýr.
						cout<<"Çifte kayýt! Zaten"<<a->okuIsim()<<" isimli bir kayýt olduðundan ekleme yapýlamamaktadýr."<<endl;
						return;
					}
					if(strcmp(isim,"")==0 ||isim[0]== '*'){ // eðer mezar taþý veya boþluk var ise yazým iþlemi yapýlýr.
						k->yazEleman(i,a);
						k->binaryYazKova(hashDosyasi,k->okuAdres());
						kayitSayisi++;
						cout<<a->okuIsim()<<" isimli kayit baþarýyla eklenmiþtir."<<"\n";
						cout<<"Ev adresi: "<<evAdresi<<" Artim degeri: "<<artim<<endl;
						cout<<"Eklendiði adres :"<<arananAdres<<" Eklendiði sýra: "<< i <<endl;
					basaSar();
					return ;
					}
				}
			arananAdres = (arananAdres + artim) % EV_ADRESI_SAYISI; // gittiði adreste yer bulamazsa diye diðer adrese geçiþ yapmasý için.
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
			k->binaryOkuKova(hashDosyasi,arananAdres);// adresine gidiip okuma yapýlýr.
				for(int i=0; i<k->KovaSayisi() ;i++){ // 3 kovadan hangisinde olacaðý belli deðildir sýrasýyla aranýr.
					eleman = k->okuEleman(i); // belirli adresteki ilk kova elemaný   eleman  a atanýr.
					char* okunanIsim = eleman->okuIsim();
				  	  	  if(strcmp(isim,okunanIsim) == 0){ // isim ve okunanIsim kontrolu yapýlýr ayný ise bulunmuþ demektir ve bilgiler konsola basýlýr.
				  	  	  cout<<isim<<" isimli kayýt : "<<arananAdres<<".Adreste , "<<i<<". sýrada "<<sorguSayisi<<". sorguda bulundu"<<endl;
				  	  	  return k;

				  	  	  }
				  	  	  if(strcmp(okunanIsim,"") == 0){
				  	  		  return NULL;
				  	  		  cout<<isim <<" isimli  kayýt bulunamadý "<<endl;
				  	  	  }
				  	  	  if(okunanIsim[0] == '*') continue;

				}
			sorguSayisi++;
			arananAdres = (arananAdres + artim) % EV_ADRESI_SAYISI ;
		}

	}
	void hashSil(char* isim) {
		Kova* k = new Kova();
		k = hashArama(isim); // hashArama fonksiyonu k deðiþkenine uygun adresteki kovayý döner .
		Araba* a;
		if(k!= NULL){ // NULL deðilse girer.
				for(int i=0 ; i<k->KovaSayisi() ; i++){ // Adreste bulunan kovanýn nesneleri gezilir.
					a = k->okuEleman(i);
					char* okunanIsim = a->okuIsim();
					if(strcmp(isim,okunanIsim) == 0){ // isim ile okunanIsim ayný olduðunda if çalýþýr.
						a->sil();  // silme iþlemi gerçekleþir.
						k->yazEleman(i,a); // tekrar kovanýn uygun nesnesine  geri atýlýr.
						k->binaryYazKova(hashDosyasi,k->okuAdres()); // dosyaya yazýlýr.
						cout<<isim<<" isimli kayýt baþarýyla silinmiþtir"<<endl;
					}
				}

			}
	}
	// Kullandýðýmýz alaný yüzde olarak buluyoruz, Kayýt sayýmýz toplam memory e bölünür.
	void yogunlasmaFaktoruHesapla() {
		Kova* k = new Kova();
		float oran = (  float((kayitSayisi)) / float((EV_ADRESI_SAYISI * k->kovaBoyutu())) );
		float yuzdeOran = oran*100;
		cout<<endl<<"Yüzde oran : "<<yuzdeOran;
		cout<<"  Dosyanýn yeniden düzenlenmesini gerektirecek bir durum yoktur. ";

	}
//iþaretçi ve bayraklarý sýfýrlamak için clear , tampondaki bilgileri dosyaya yazdýrmak için flush fonk kullandýk.
	void basaSar(){
		hashDosyasi.clear();
		hashDosyasi.flush();
	}



};
