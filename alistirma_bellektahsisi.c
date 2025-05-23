#include <stdio.h>
#include <stdlib.h>


int faktoryelHesapla(int sayi) {
    int sonuc=1;
    if (sayi<0) {
        printf("negatif sayilarin faktoryeli hesaplanamaz!");
        return -1;//hata durumu belirtir
    }
    if (sayi==0) {
        return 0;// 0!=1
    }
    for(int i = 1; i<= sayi; i++) {
    sonuc =sonuc*i;

    }
return sonuc;
}

int* faktoryelDizisiolustur(int dizi[], int boyut) {
    int* yenidizi=(int*)malloc(boyut*sizeof(int));

    if(yenidizi==NULL) {
        printf("yeni dizi icin bellek tahsisi basarisiz oldu!");
        exit(1); //hata kodu ile program sonlandırılır.
    }
    for (int i=0;i<boyut;i++) {
        yenidizi[i]=faktoryelHesapla(dizi[i]);
    }
return yenidizi;
}
int main() {

    int dizi[5]={5,3,8,2,7};

    int *p=faktoryelDizisiolustur(dizi,5);

    for(int i=0;i<5;i++) {

        printf("%d!=%d " ,dizi[i],p[i]);
        printf("\n");
    }
    free(p);
    return 0;
}
