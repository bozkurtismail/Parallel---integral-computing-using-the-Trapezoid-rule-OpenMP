/*****************************************************************************
**@author Ýsmail BOZKURT
******************************************************************************/
#include <stdio.h>
#include <math.h>
#include <omp.h>


int     fonksiyon = 0;			     /////////// kullanicinin islem yapacagi fonksiyon secimi icin
double  altLimit = 0.0;			    /////////// belirli integralin alt kismi
double  ustLimit = 0.0;		 	   /////////// belirli integralin ust kismi
int     altAralik = 0;		      /////////// alt ve ust kýsmýn icerisinden bolunecek trapez sayisi
double  seriSonuc;			     /////////// seri hesaplama sonucu
double  seriSure;			    /////////// seri hesaplama gecen sure
double  paralelSonuc;		   /////////// paralel hesaplama sonucu
double  paralelSure;		  /////////// paralel hesaplama gecen sure
double  altAralikGenisligi;  /////////// her trapez araylik olcusu



int menuSecimi(void){         /////////// kullanicinin fonksiyon secip yada programdan cikmasini saglar
    int id;

    printf("[1]. Foksiyon Secimi\n");
    printf("[2]. Cikis\n");

    do {
        printf("\nSeceneginizi giriniz [1-2]: ");
        scanf("%d",&id);
        printf("\n");
    } while (id < 1 || id > 2);

    return id;
}
int fonksiyonSecimi(){        /////////// kullanicinin islem yapacagi fonksiyonu secebilmek icin 
    int id = 0;
    printf("\n\n  FONKSIYON SECIMI\n");
    printf("[1]. 1/(1+x*x)\n");
    printf("[2]. (x*x*x)+1\n");
    printf("[3]. Sin[x]^2 + 2\n");

    do {
        printf("\nSeceneginizi giriniz [1-3]: ");
        scanf("%d",&id);
        printf("\n");
    } while (id < 1 || id>3);
    return id;
}
void parametreDegerleriAl(){  ///////////kullanicidan altLimit,ustLimit ve trapez sayisini alir
   	
	do{
		 printf("     ***********************************************************\n");
  	     printf("     **          INTEGRAL ALT LIMITINI GIRINIZ                **\n");
	     printf("                              ");
	     scanf("%lf",&altLimit);
	     system("CLS");
		 if(altLimit<0)
		 {
		 	printf("\n\t\tEKSI DEGER GIREMEZSINIZ TEKRAR DENEYINIZ!...\n");
		 }
	}while(altLimit<0);  

    system("CLS");
	
	do{
		 printf("     ***********************************************************\n");
	     printf("     **          INTEGRAL UST LIMITINI GIRINIZ                **\n");
	     printf("                              ");
	     scanf("%lf",&ustLimit);
	     system("CLS");
		 if(ustLimit<altLimit)
		 {
		 	printf("\n     UST LIMITI ALT LIMITTEN KUCUK GIREMEZSINIZ TEKRAR DENEYINIZ!...\n");
		 }
	}while(ustLimit<altLimit);   

    system("CLS");
    
    do{
		 printf("     ***********************************************************\n");
    	 printf("     **         INTEGRAL ALT ARALIK DEGERINI GIRINIZ          **\n");
    	 printf("                               ");
     	 scanf("%d",&altAralik);

	     system("CLS");
		 if(altAralik<=0)
		 {
		 	printf("\n   ALT ARALIK SIFIR VE EKSI DEGER GIREMEZSINIZ TEKRAR DENEYINIZ!...\n");
		 }
	}while(altAralik<=0); 
	    
    system("CLS");
}
void girilenParametreler(){   //kullanicinin girmis oldugu altLimit,ustLimit,trapez sayisi ve sectigi fonksiyonu yazdirir
	 char *fonksiyonAdi;
    if (fonksiyon == 1) {
        fonksiyonAdi = "1/(1+x*x)";
    }
    else if (fonksiyon == 2) {
         fonksiyonAdi = "(x*x*x)+1)";
    }
    else if (fonksiyon == 3) {
         fonksiyonAdi = "Sin[x]^2 + 2";
    }
	
    printf("\n\t\t\tKULLANICI TARAFINDAN GIRILEN PARAMETRELER\n");
    printf("\nALT LIMIT\t\tUST LIMIT\t\tALT ARALIK\t\tSECILEN FONKSIYON\n\n");
    printf("******************************************************************************************\n");
    printf("%.f\t\t\t%.f\t\t\t%d\t\t%s\n\n\n\n", altLimit, ustLimit, altAralik,fonksiyonAdi);
    
}
double f(double x){           /////////// kullanicinin secmis oldugu fonksiyona gore gelen x degerini denklem icerisinde hesaplar
    if (fonksiyon == 1) {
        return 1 / (1 + x * x);
    }
    else if (fonksiyon == 2) {
        return (x * x * x) + 1;
    }
    else if (fonksiyon == 3) {
        return pow(sin(x * (3.14 / 180)), 2) + 2;
    }   
}
void sureVeSonucYazdir(char metod[], double sonuc, double sure) { /////////// seri hesaplama veya paralel hesaplama sonuc ve surelerinin yazdirir
    printf("\n\t\t%s", metod);
    printf("\nTOPLAM SONUC\t\tGECEN SURE\n\n");
    printf("********************************************\n");
    printf("%f\t\t%f second\n\n\n\n", sonuc, sure);
}
void seriHesaplama(){         /////////// girilen parametre degerlerine gore seri sekilde hesaplama islemini gerceklestirir
	char 	metod[7] = "SERI";
	double ilkZaman, sonZaman;
	double sonuc; 					/////////// toplam integral sonucu	
	double h; 						/////////// her trapez araliginin genisligi
	double x;					    /////////// her bir aralýktaki fonksiyona gönderilecek x deðeri
	int i;						    /////////// for döngüsü için
	double a=altLimit;
	double b=ustLimit;
	int    N=altAralik;
	
	ilkZaman = omp_get_wtime();		/////////// anlýk zamaný alacak
	h = (b-a)/N;					/////////// her parcanin araliginin genisligi
	sonuc = (f(a)+f(b))/2.0;		/////////// ilk nokta ve son nokta arasý fonksiyon hesaplandý
	x = a;
	for(i = 1; i <= N-1; i++)
	{
	x = x+h;
	sonuc = sonuc + f(x);
	}
	sonuc = sonuc*h;
	sonZaman=omp_get_wtime()-ilkZaman;
	//printf("N sayisi:%d    integral Sonucu:%f suresi:%f",N,sonuc,sonZaman);
    seriSonuc = sonuc;///////test kismi icin kullanilmistir.
    seriSure = sonZaman;
    sureVeSonucYazdir(metod, seriSonuc, seriSure);
}
void paralelHesaplama(){      /////////// girilen parametre degerlerine gore paralel sekilde hesaplama islemini gerceklestirir
	char 	metod[7] = "PARALEL";
	double ilkZaman, sonZaman;
	double sonuc=0.0; 				/////////// toplam integral sonucu
	double genelSonuc=0.0;			/////////// ilk ve son noktalarla berarber toplam integral sonucu
	
	double h; /*base width of subdivision*/
	double x;
	int i;
	
	double a=altLimit;
	double b=ustLimit;
	int    N=altAralik;
	
	//omp_set_num_threads(8);
	
	ilkZaman = omp_get_wtime();		/////////// anlýk zamaný alacak
	h 		 = (b-a)/N;				/////////// her parcanin araliginin genisligi
	
	#pragma omp parallel firstprivate(x, sonuc) shared(genelSonuc)
	{
		#pragma omp for
		for(i = 1; i <= N-1; i++)
		{
			x = a+i*h;
			sonuc = sonuc + f(x);
		}
		#pragma omp critical
		genelSonuc += sonuc;		/////////// her threaden gelen deðer kritik bölgede sýrasý ile toplandý
	}
	genelSonuc 	 = (genelSonuc+(f(a)+f(b))/2.0)*h; 		/////ilk nokta ve son nokta arasý fonksiyon hesaplanýp genelSonuca eklendi
	
	sonZaman	 =omp_get_wtime()-ilkZaman;		/////////// arada geçen süre farký alýndý
	//printf("\nN sayisi:%d    integral Sonucu:%f suresi:%f",N,genelSonuc,sonZaman);
	
	altAralikGenisligi=h;	       /////////// test kismi icin kullanilmistir.
	paralelSonuc = genelSonuc;     /////////// test kismi icin kullanilmistir.
    paralelSure  = sonZaman;	   ////////// süre karþýlaþtýrmasý yapmak için ilgili deðiþkene atandý
    sureVeSonucYazdir(metod, paralelSonuc, paralelSure);
}
void sureKarsilastir(){       /////////// seri ve paralel yapilan hesaplama surelerini karsilastirarak hizli hesaplama bilgisini veriri
	
	///////paralel ve seri hesaplamalar sonucu elde edilen süre sonuclarýna göre karþýlaþtýrma yapýlýp
	//////hangisi daha hýzlý ise hakkýnda bilgi verecek
	if(paralelSure<seriSure)
	{
		printf("\n\n");
		printf("============================================\n");
		printf("==      PARALEL HESAPLAMA DAHA HIZLI      ==\n");
		printf("                 %f second\n\n\n",paralelSure);
	}
	else if(paralelSure==seriSure)
	{
		printf("\n\n");
		printf("============================================\n");
		printf("==   IKI HESAPLAMADA AYNI SUREYE SAHIP    ==\n");
		printf("                %f second\n\n\n",seriSure);	
	}else if(paralelSure>seriSure)
	{
		printf("\n\n");
		printf("============================================\n");
		printf("==        SERI HESAPLAMA DAHA HIZLI       ==\n");
		printf("                %f second\n\n\n",seriSure);	
	}
}

/////////////////////TEST BOLUMU////////////////////////

void altLimitTesti(const char* testIsmi){	
	printf("\n\n------------------------------------------------------------\n");
	printf("                     ALT LIMIT TESTI                      \n");
	printf("ALT LIMIT =%.f  ",altLimit);
	if(altLimit>=0.0)
	{
		printf("\n%s TESTI GECTI    ",testIsmi);		
	}
	else
	{
		printf("\n%s TESTI GECEMEDI HATA OLUSTU",testIsmi); 		
	}
	printf("\n------------------------------------------------------------\n");	
}
void ustLimitTesti(const char* testIsmi){		
	printf("                     UST LIMIT TESTI                      \n");
	printf("UST LIMIT =%.f",ustLimit);
	if(ustLimit<=altLimit)
	{
		printf("\n%s TESTI GECEMEDI HATA OLUSTU",testIsmi);			
	}
	else
	{
		printf("\n%s TESTI GECTI",testIsmi);			
	}
	printf("\n------------------------------------------------------------\n");	
}
void altAralikTesti(const char* testIsmi){	
	printf("                    ALT ARALIK TESTI                      \n");
	printf("ALT ARALIK =%d",altAralik);
	if(altAralik<=0)
	{
		printf("\n%s TESTI GECEMEDI HATA OLUSTU",testIsmi);			
	}
	else
	{
		printf("\n%s TESTI GECTI",testIsmi);			
	}
	printf("\n------------------------------------------------------------\n");	
}
void altAralikGenisligiTesti(const char* testIsmi){
	printf("ALT ARALIK GENISLIGI =%lf",altAralikGenisligi);
	if(altAralikGenisligi<0)
	{
		printf("\n%s TESTI GECEMEDI HATA OLUSTU",testIsmi);			
	}
	else
	{
		printf("\n%s TESTI GECTI",testIsmi);			
	}	
	printf("\n------------------------------------------------------------\n");
}	
void seriHesaplamaTesti(const char* testIsmi){
	printf("SERI HESAP SONUCU =%lf",seriSonuc);
	if(seriSonuc<=0)
	{
		printf("\n%s TESTI GECEMEDI HATA OLUSTU",testIsmi);			
	}
	else
	{
		printf("\n%s TESTI GECTI",testIsmi);			
	}	
	printf("\n------------------------------------------------------------\n");
}
void seriHesaplamaSureTesti(const char* testIsmi){
	printf("SERI HESAP SURE SONUCU =%lf second",seriSure);
	if(seriSure<0)
	{
		printf("\n%s TESTI GECEMEDI HATA OLUSTU",testIsmi);			
	}
	else
	{
		printf("\n%s TESTI GECTI",testIsmi);			
	}	
	printf("\n------------------------------------------------------------\n");
}
void fonksiyonFormulTesti(const char* testIsmi){
	double sonuc;
	fonksiyon=2;
	sonuc=f(5);
	printf("FORMUL HESAP SONUCU =%.f",sonuc);
	if(sonuc==126)	
	{
		printf("\n%s TESTI GECTI",testIsmi);		
	}
	else
	{		
		printf("\n%s TESTI GECEMEDI HATA OLUSTU",testIsmi);				
	}	
	printf("\n------------------------------------------------------------\n");
}
void paralelHesaplamaTesti(const char* testIsmi){
	printf("PARALEL HESAP SONUCU =%lf",paralelSonuc);
	if(paralelSonuc<0)
	{
		printf("\n%s TESTI GECEMEDI HATA OLUSTU",testIsmi);			
	}
	else
	{
		printf("\n%s TESTI GECTI",testIsmi);			
	}	
	printf("\n------------------------------------------------------------\n");
}
void paralelHesaplamaSureTesti(const char* testIsmi){
	printf("PARALEL HESAP SURE SONUCU =%lf second",paralelSure);
	if(paralelSure<0)
	{
		printf("\n%s TESTI GECEMEDI HATA OLUSTU",testIsmi);			
	}
	else
	{
		printf("\n%s TESTI GECTI",testIsmi);			
	}	
	printf("\n------------------------------------------------------------\n");
}
void paralelVeSeriHesaplamaSonucTesti(const char* testIsmi){
	printf("SERI HESAPLAMA SONUCU =%lf\n",seriSonuc);
	printf("PARALEL HESAPLAMA SONUCU =%lf\n",paralelSonuc);	
	if(paralelSonuc!=seriSonuc)
	{
		printf("\n%s TESTI GECTI",testIsmi);		
	}
	else
	{		
		printf("\n%s TESTI GECEMEDI HATA OLUSTU",testIsmi);				
	}	
	printf("\n------------------------------------------------------------\n");
}
void paralelVeSeriHesaplamaSureTesti(const char* testIsmi){
	printf("SERI HESAPLAMA SURE SONUCU =%lf second\n",seriSure);
	printf("PARALEL HESAPLAMA SURE SONUCU =%lf second\n",paralelSure);	
	if(paralelSure>seriSure)
	{
		printf("\nSERI HESAPLAMA PARALEL HESAPLAMADAN DAHA HIZLI\n");
		printf("\n%s TESTI GECEMEDI HATA OLUSTU",testIsmi);		
	}
	else if(paralelSure==seriSure)
	{
		printf("\nSERI HESAPLAMA ve PARALEL HESAPLAMA ESIT HIZDA\n");
		printf("\n%s TESTI GECEMEDI HATA OLUSTU",testIsmi);			
	}
	else
	{	
		printf("\nPARALEL HESAPLAMA SERI HESAPLAMADAN DAHA HIZLI\n");			
		printf("\n%s TESTI GECTI",testIsmi);				
	}	
	printf("\n------------------------------------------------------------\n");
}		

///////////////////MAIN BOLUMU/////////////////////////

int main(){
	int    secim = 0;
    for (; ; ) {
        printf("\n");
        secim = menuSecimi();        
        system("CLS");

        if (secim == 2)
        {
            printf("CIKIS YAPILIYOR");
            break;
        }
        
		fonksiyon = fonksiyonSecimi();        
        system("CLS");	
        
        parametreDegerleriAl();
		girilenParametreler();  
		seriHesaplama();
		paralelHesaplama();
		sureKarsilastir();
		
		//////////         TEST ISLEMLERI         ////////
		altLimitTesti("ALT LIMIT (EKSI DEGERI GIRILDI)");
		ustLimitTesti("UST LIMIT (ALT LIMIT ALTINDA DEGER GIRILDI)");
		altAralikTesti("ALT ARALIK (0 VE ALTINDA DEGER GIRILDI)");
		altAralikGenisligiTesti("ALT ARALIK GENISLIGI (EKSI SONUC GELDI)");
		seriHesaplamaTesti("SERI HESAPLAMA SONUCU(EKSI GELDI)");
		seriHesaplamaSureTesti("SERI SURE SONUCU (EKSI GELDI)");
		fonksiyonFormulTesti("F(1+(x*x*x)) FONKSIYONA 5 GONDERILDI 126 GELDI");	
		paralelHesaplamaTesti("PARALEL HESAPLAMA SONUCU(EKSI GELDI)");
		paralelHesaplamaSureTesti("PARALEL SURE SONUCU (EKSI GELDI)");
		paralelVeSeriHesaplamaSonucTesti("SERI VE PARALEL HESAPLAMA SONUCU(SONUC ESIT GELMEDI)");
		paralelVeSeriHesaplamaSureTesti("SERI VE PARALEL HESAPLAMA SURE SONUCU(SERI HESAPLAMA HIZLI GELDI)");	
	}
	return 0;	
}
	


