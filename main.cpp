#include <mysql.h>
#include <stdio.h>
#include <string.h>

char ismi[20];
char adres[20];
char yasadigiSehir[20];
char eposta[30];

char bn[3];
char bin[3];
char ukn[10];
char ukn2[10];
char ukn3[10];

char tarih[10];
char saat[4];

char tckn[11];

int aktarma;

char id[3];
char id2[3];
char id3[3];

main() {
 MYSQL *conn;
 MYSQL_RES *res;
 MYSQL_ROW row;
 char *server = "localhost";
 char *user = "root";
 char *password = "1234";
 char *database = "havaalani";
 conn = mysql_init(NULL);

 if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    return 1;
 }

 int secim;
 printf("Sefer eklemek icin '1'\nBilet satin almak icin '2'\nTckn ile yolcu sorgusu icin '3'");
 printf(" \nUcus iptali icin '4'\nBilet iptali icin '5'\nSefer sorgulamak icin '6'\nDoluluk orani icin '7'");
 printf("\ntusuna basip enter tusuna basiniz: ");
 scanf("%d",&secim);
 printf("\n-----------------------------------------\n\n");

 if(secim==1){
    char dizi_sefer_ekle[200],dizi_sefer_ekle_sorgu[200];
    int tarih_uzunluk;

    printf("Sefer baslangic noktasini giriniz: ");
    scanf("%s",bn);
    printf("Sefer bitis noktasini giriniz: ");
    scanf("%s",bin);
    printf("Sefer tarihini giriniz: ");
    scanf("%s",tarih);
    printf("Sefer saatini giriniz: ");
    scanf("%s",saat);
    printf("Seferin ucak kuyruk nosunu giriniz: ");
    scanf("%s",ukn);

    strcpy(dizi_sefer_ekle,"INSERT INTO sefer(bn,bin,tarih,saat,ukn) VALUES (\'");
    strcat(dizi_sefer_ekle,bn);
    strcat(dizi_sefer_ekle,"\',\'");
    strcat(dizi_sefer_ekle, bin);
    strcat(dizi_sefer_ekle,"\',\'");
    strcat(dizi_sefer_ekle,tarih);
    strcat(dizi_sefer_ekle,"\',\'");
    strcat(dizi_sefer_ekle,saat);
    strcat(dizi_sefer_ekle,"\',\'");
    strcat(dizi_sefer_ekle,ukn);
    strcat(dizi_sefer_ekle,"\');");

    strcpy(dizi_sefer_ekle_sorgu,"Select * COUNT FROM ucak WHERE ukn=\'" );
    strcat(dizi_sefer_ekle_sorgu,ukn);
    strcat(dizi_sefer_ekle_sorgu,"\';");

    if (mysql_query(conn, dizi_sefer_ekle_sorgu)) {
        if (mysql_query(conn, dizi_sefer_ekle)) {
            if(mysql_real_connect!=0){
                printf("Hatali ucak kuyruk no girdiniz");
                return 0;
            }

        }
    }


 }

 else if(secim==2){

    char dizi_biletal[500];
    char dizi_biletal1[500];
    char dizi_biletal2[500];
    char dizi_aktarma1[3];
    char dizi_aktarma2[3];
    char dizi_aktarma3[3];

    int biletSayisi;

    printf("Biletin tarihini giriniz: ");
    scanf("%s",tarih);

    ///---------------------1 aktarmali
    strcpy(dizi_biletal1,"Select * from sefer s1, sefer s2 where s1.tarih=\'");
    strcat(dizi_biletal1,tarih);
    ///---------------------aktarmasiz
    strcpy(dizi_biletal,"Select * From sefer where tarih=\'");
    strcat(dizi_biletal,tarih);
    ///---------------------2 aktarmali
    strcpy(dizi_biletal2,"Select * from sefer s1, sefer s2,sefer s3  where s1.tarih=\'");
    strcat(dizi_biletal2,tarih);

    printf("Alinacak ucagin kalkis yerini giriniz: ");
    scanf("%s",bn);

    ///---------------------1 aktarmali
    strcat(dizi_biletal1,"\' AND s1.bn=\'");
    strcat(dizi_biletal1,bn);
    ///--------------------aktarmasiz
    strcat(dizi_biletal,"\' AND bn=\'");
    strcat(dizi_biletal,bn);
    ///--------------------2 aktarmali
    strcat(dizi_biletal2,"\' AND s1.bn=\'");
    strcat(dizi_biletal2,bn);

    printf("Varis yerisini giriniz: ");
    scanf("%s",bin);

    ///---------------------1 aktarmali
    strcat(dizi_biletal1,"\' AND s2.bin=\'");
    strcat(dizi_biletal1,bin);
    strcat(dizi_biletal1,"\' AND s2.bn=s1.bin AND s1.saat<s2.saat;");
    ///---------------------aktarmasiz
    strcat(dizi_biletal,"\' AND bin=\'");
    strcat(dizi_biletal,bin);
    strcat(dizi_biletal,"\';");
    ///---------------------2 aktarmali
    strcat(dizi_biletal2,"\' AND s3.bin=\'");
    strcat(dizi_biletal2,bin);
    strcat(dizi_biletal2,"\' AND s1.bin=s2.bn AND s2.bin=s3.bn AND s1.saat<s2.saat<s3.saat;");

    printf("Alinacak bilet sayisini giriniz: ");
    scanf("%d",&biletSayisi);

    if (mysql_query(conn, dizi_biletal)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    res = mysql_use_result(conn);

    if ((row = mysql_fetch_row(res)) == NULL){
        printf("\n-----Aktarmasiz ucuslar-----\n");
        printf("\nAktarmasiz ucus bulunamadi.\n");
    }

    else{
        printf("\n-----Aktarmasiz ucuslar-----\n");
        printf("\nSefer ID:%s \tBaslangic nok:%s \tVaris Nok:%s \tTarih:%s \tSaat:%s \tUcak kuyruk no:%s\n",row[5],row[0],row[1],row[2],row[3],row[4]);


        while ((row = mysql_fetch_row(res)) != NULL){
            printf("\nSefer ID:%s \tBaslangic nok:%s \tVaris Nok:%s \tTarih:%s \tSaat:%s \tUcak kuyruk no:%s\n",row[5],row[0],row[1],row[2],row[3],row[4]);
        }
    }


    if (mysql_query(conn, dizi_biletal1)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    res = mysql_use_result(conn);

    if ((row = mysql_fetch_row(res)) == NULL){
        printf("\n-----Bir aktarmali ucuslar-----\n");
        printf("\nBir aktarmali ucus bulunamadi.\n");
    }

    else{
        printf("\n-----Bir aktarmali ucuslar-----\n");
        printf("\nSefer ID:%s \tBaslangic nok:%s \tVaris Nok:%s \tTarih:%s \tSaat:%s \tUcak kuyruk no:%s\nSefer ID:%s \tBaslangic nok:%s \tVaris Nok:%s \tTarih:%s \tSaat:%s \tUcak kuyruk no:%s",row[5],row[0],row[1],row[2],row[3],row[4],row[11],row[6],row[7],row[8],row[9],row[10]);
        strcpy(dizi_aktarma1,row[1]);
        while ((row = mysql_fetch_row(res)) != NULL){
            printf("\nSefer ID:%s \tBaslangic nok:%s \tVaris Nok:%s \tTarih:%s \tSaat:%s \tUcak kuyruk no:%s\nSefer ID:%s \tBaslangic nok:%s \tVaris Nok:%s \tTarih:%s \tSaat:%s \tUcak kuyruk no:%s",row[5],row[0],row[1],row[2],row[3],row[4],row[11],row[6],row[7],row[8],row[9],row[10]);

        }
    }

    if (mysql_query(conn, dizi_biletal2)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    res = mysql_use_result(conn);

    if ((row = mysql_fetch_row(res)) == NULL){
        printf("\n\n-----Iki aktarmali ucuslar-----\n");
        printf("\nIki aktarmali ucus bulunamadi.\n");
    }

    else{
        printf("\n\n-----Iki aktarmali ucuslar-----\n");
        printf("\nSefer ID:%s \tBaslangic nok:%s \tVaris Nok:%s \tTarih:%s \tSaat:%s \tUcak kuyruk no:%s\nSefer ID:%s \tBaslangic nok:%s \tVaris Nok:%s \tTarih:%s \tSaat:%s \tUcak kuyruk no:%s\nSefer ID:%s \tBaslangic nok:%s \tVaris Nok:%s \tTarih:%s \tSaat:%s \tUcak kuyruk no:%s",row[5],row[0],row[1],row[2],row[3],row[4],row[11],row[6],row[7],row[8],row[9],row[10],row[17],row[12],row[13],row[14],row[15],row[16]);
        strcpy(dizi_aktarma2,row[1]);
        strcpy(dizi_aktarma3,row[7]);

        while ((row = mysql_fetch_row(res)) != NULL){
            printf("\nSefer ID:%s \tBaslangic nok:%s \tVaris Nok:%s \tTarih:%s \tSaat:%s \tUcak kuyruk no:%s\nSefer ID:%s \tBaslangic nok:%s \tVaris Nok:%s \tTarih:%s \tSaat:%s \tUcak kuyruk no:%s\nSefer ID:%s \tBaslangic nok:%s \tVaris Nok:%s \tTarih:%s \tSaat:%s \tUcak kuyruk no:%s",row[5],row[0],row[1],row[2],row[3],row[4],row[11],row[6],row[7],row[8],row[9],row[10],row[17],row[12],row[13],row[14],row[15],row[16]);
        }
    }

    char dizi_tckn[200];

    char dizi_yeniyolcu[500];
    char dizi_yeniyolcu2[500];
    char dizi_yeniyolcu3[500];

    char dizi_yolcu[500];
    char dizi_yolcu2[500];
    char dizi_yolcu3[500];

    printf("\n\nAktarmasiz ucus sectiyseniz '1' tusuna,\nBir aktarmali ucus sectiyseniz '2' tusuna,\nIki aktarmali ucus sectiyseniz '3' tusuna basiniz: ");
    scanf("%d",&aktarma);


    if(aktarma==1){
        printf("\nSectiginiz aktarmasiz ucusun ucak kuyruk nosunu giriniz: ");
        scanf("%s",ukn);
        printf("Sectiginiz seferin sefer id'sini giriniz:");
        scanf("%s",id);
    }

    else if(aktarma==2){
        printf("\nSectiginiz aktarmali ucusun ilkinin ucak kuyruk nosunu giriniz: ");
        scanf("%s",ukn);
        printf("Sectiginiz aktarmali ucusun ilkinin sefer id'sini giriniz: ");
        scanf("%s",id);
        printf("Sectiginiz aktarmali ucusun diger ucak kuyruk nosunu giriniz: ");
        scanf("%s",ukn2);
        printf("Sectiginiz aktarmali ucusun diger seferin id'sini giriniz: ");
        scanf("%s",id2);

    }

    else if(aktarma==3){
        printf("\nSectiginiz aktarmali ucusun ilkinin ucak kuyruk nosunu giriniz: ");
        scanf("%s",ukn);
        printf("Sectiginiz aktarmali ucusun ilkinin sefer id'sini giriniz: ");
        scanf("%s",id);
        printf("Sectiginiz aktarmali ucusun ikincisinin ucak kuyruk nosunu giriniz: ");
        scanf("%s",ukn2);
        printf("Sectiginiz aktarmali ucusun ikincisinin sefer id'sini giriniz: ");
        scanf("%s",id2);
        printf("Sectiginiz aktarmali ucusun ucuncusunun ucak kuyruk nosunu giriniz: ");
        scanf("%s",ukn3);
        printf("Sectiginiz aktarmali ucusun ucuncusunun sefer id'sini giriniz: ");
        scanf("%s",id3);

    }

    for(int i=1;i<=biletSayisi;i++){
        printf("%d. biletin tc kimlik nosunu giriniz: ",i);
        scanf("%s",tckn);

        strcpy(dizi_tckn,"Select * From yolcu where tckn=\'");
        strcat(dizi_tckn,tckn);
        strcat(dizi_tckn,"\';");

        mysql_query(conn, dizi_tckn);
        res = mysql_use_result(conn);
        if((row = mysql_fetch_row(res)) == NULL){
            printf("\nYolcu ismi: ");
            scanf("%s",ismi);
            printf("Adresi: ");
            scanf("%s",adres);
            printf("Yasadigi sehir: ");
            scanf("%s",yasadigiSehir);
            printf("Eposta: ");
            scanf("%s",eposta);


            if(aktarma==1){
                strcpy(dizi_yeniyolcu,"INSERT INTO yolcu(ismi,adresi,yasadigiSehir,eposta,bn,bin,tckn,tarih,ukn,id) values(\'");
                strcat(dizi_yeniyolcu,ismi);
                strcat(dizi_yeniyolcu,"\',\'");
                strcat(dizi_yeniyolcu,adres);
                strcat(dizi_yeniyolcu,"\',\'");
                strcat(dizi_yeniyolcu,yasadigiSehir);
                strcat(dizi_yeniyolcu,"\',\'");
                strcat(dizi_yeniyolcu,eposta);
                strcat(dizi_yeniyolcu,"\',\'");
                strcat(dizi_yeniyolcu,bn);
                strcat(dizi_yeniyolcu,"\',\'");
                strcat(dizi_yeniyolcu,bin);
                strcat(dizi_yeniyolcu,"\',\'");
                strcat(dizi_yeniyolcu,tckn);
                strcat(dizi_yeniyolcu,"\',\'");
                strcat(dizi_yeniyolcu,tarih);
                strcat(dizi_yeniyolcu,"\',\'");
                strcat(dizi_yeniyolcu,ukn);
                strcat(dizi_yeniyolcu,"\',");
                strcat(dizi_yeniyolcu,id);
                strcat(dizi_yeniyolcu,");");

                printf(dizi_yeniyolcu);

                mysql_query(conn, dizi_yeniyolcu);
            }


            else if(aktarma==2){
                mysql_query(conn, dizi_biletal1);
                res = mysql_use_result(conn);
                while ((row = mysql_fetch_row(res)) != NULL){
                    strcpy(dizi_yeniyolcu,"INSERT INTO yolcu(ismi,adresi,yasadigiSehir,eposta,bn,bin,tckn,tarih,ukn,id) values(\'");
                    strcat(dizi_yeniyolcu,ismi);
                    strcat(dizi_yeniyolcu,"\',\'");
                    strcat(dizi_yeniyolcu,adres);
                    strcat(dizi_yeniyolcu,"\',\'");
                    strcat(dizi_yeniyolcu,yasadigiSehir);
                    strcat(dizi_yeniyolcu,"\',\'");
                    strcat(dizi_yeniyolcu,eposta);
                    strcat(dizi_yeniyolcu,"\',\'");
                    strcat(dizi_yeniyolcu,bn);
                    strcat(dizi_yeniyolcu,"\',\'");
                    strcat(dizi_yeniyolcu,row[1]);
                    strcat(dizi_yeniyolcu,"\',\'");
                    strcat(dizi_yeniyolcu,tckn);
                    strcat(dizi_yeniyolcu,"\',\'");
                    strcat(dizi_yeniyolcu,tarih);
                    strcat(dizi_yeniyolcu,"\',\'");
                    strcat(dizi_yeniyolcu,ukn);
                    strcat(dizi_yeniyolcu,"\',");
                    strcat(dizi_yeniyolcu,id);
                    strcat(dizi_yeniyolcu,");");


                    strcpy(dizi_yeniyolcu2,"INSERT INTO yolcu(ismi,adresi,yasadigiSehir,eposta,bn,bin,tckn,tarih,ukn,id) values(\'");
                    strcat(dizi_yeniyolcu2,ismi);
                    strcat(dizi_yeniyolcu2,"\',\'");
                    strcat(dizi_yeniyolcu2,adres);
                    strcat(dizi_yeniyolcu2,"\',\'");
                    strcat(dizi_yeniyolcu2,yasadigiSehir);
                    strcat(dizi_yeniyolcu2,"\',\'");
                    strcat(dizi_yeniyolcu2,eposta);
                    strcat(dizi_yeniyolcu2,"\',\'");
                    strcat(dizi_yeniyolcu2,row[1]);
                    strcat(dizi_yeniyolcu2,"\',\'");
                    strcat(dizi_yeniyolcu2,bin);
                    strcat(dizi_yeniyolcu2,"\',\'");
                    strcat(dizi_yeniyolcu2,tckn);
                    strcat(dizi_yeniyolcu2,"\',\'");
                    strcat(dizi_yeniyolcu2,tarih);
                    strcat(dizi_yeniyolcu2,"\',\'");
                    strcat(dizi_yeniyolcu2,ukn2);
                    strcat(dizi_yeniyolcu,"\',");
                    strcat(dizi_yeniyolcu,id2);
                    strcat(dizi_yeniyolcu,");");




                }

                mysql_query(conn, dizi_yeniyolcu);

                mysql_query(conn, dizi_yeniyolcu2);

            }

            else if(aktarma==3){
                mysql_query(conn, dizi_biletal2);
                res = mysql_use_result(conn);
                while ((row = mysql_fetch_row(res)) != NULL){
                    strcpy(dizi_yeniyolcu,"INSERT INTO yolcu(ismi,adresi,yasadigiSehir,eposta,bn,bin,tckn,tarih,ukn,id) values(\'");
                    strcat(dizi_yeniyolcu,ismi);
                    strcat(dizi_yeniyolcu,"\',\'");
                    strcat(dizi_yeniyolcu,adres);
                    strcat(dizi_yeniyolcu,"\',\'");
                    strcat(dizi_yeniyolcu,yasadigiSehir);
                    strcat(dizi_yeniyolcu,"\',\'");
                    strcat(dizi_yeniyolcu,eposta);
                    strcat(dizi_yeniyolcu,"\',\'");
                    strcat(dizi_yeniyolcu,bn);
                    strcat(dizi_yeniyolcu,"\',\'");
                    strcat(dizi_yeniyolcu,row[1]);
                    strcat(dizi_yeniyolcu,"\',\'");
                    strcat(dizi_yeniyolcu,tckn);
                    strcat(dizi_yeniyolcu,"\',\'");
                    strcat(dizi_yeniyolcu,tarih);
                    strcat(dizi_yeniyolcu,"\',\'");
                    strcat(dizi_yeniyolcu,ukn);
                    strcat(dizi_yeniyolcu,"\',");
                    strcat(dizi_yeniyolcu,id);
                    strcat(dizi_yeniyolcu,");");


                    strcpy(dizi_yeniyolcu2,"INSERT INTO yolcu(ismi,adresi,yasadigiSehir,eposta,bn,bin,tckn,tarih,ukn,id) values(\'");
                    strcat(dizi_yeniyolcu2,ismi);
                    strcat(dizi_yeniyolcu2,"\',\'");
                    strcat(dizi_yeniyolcu2,adres);
                    strcat(dizi_yeniyolcu2,"\',\'");
                    strcat(dizi_yeniyolcu2,yasadigiSehir);
                    strcat(dizi_yeniyolcu2,"\',\'");
                    strcat(dizi_yeniyolcu2,eposta);
                    strcat(dizi_yeniyolcu2,"\',\'");
                    strcat(dizi_yeniyolcu2,row[1]);
                    strcat(dizi_yeniyolcu2,"\',\'");
                    strcat(dizi_yeniyolcu2,row[7]);
                    strcat(dizi_yeniyolcu2,"\',\'");
                    strcat(dizi_yeniyolcu2,tckn);
                    strcat(dizi_yeniyolcu2,"\',\'");
                    strcat(dizi_yeniyolcu2,tarih);
                    strcat(dizi_yeniyolcu2,"\',\'");
                    strcat(dizi_yeniyolcu2,ukn2);
                    strcat(dizi_yeniyolcu2,"\',");
                    strcat(dizi_yeniyolcu2,id2);
                    strcat(dizi_yeniyolcu2,");");

                    strcpy(dizi_yeniyolcu3,"INSERT INTO yolcu(ismi,adresi,yasadigiSehir,eposta,bn,bin,tckn,tarih,ukn,id) values(\'");
                    strcat(dizi_yeniyolcu3,ismi);
                    strcat(dizi_yeniyolcu3,"\',\'");
                    strcat(dizi_yeniyolcu3,adres);
                    strcat(dizi_yeniyolcu3,"\',\'");
                    strcat(dizi_yeniyolcu3,yasadigiSehir);
                    strcat(dizi_yeniyolcu3,"\',\'");
                    strcat(dizi_yeniyolcu3,eposta);
                    strcat(dizi_yeniyolcu3,"\',\'");
                    strcat(dizi_yeniyolcu3,row[7]);
                    strcat(dizi_yeniyolcu3,"\',\'");
                    strcat(dizi_yeniyolcu3,bin);
                    strcat(dizi_yeniyolcu3,"\',\'");
                    strcat(dizi_yeniyolcu3,tckn);
                    strcat(dizi_yeniyolcu3,"\',\'");
                    strcat(dizi_yeniyolcu3,tarih);
                    strcat(dizi_yeniyolcu3,"\',\'");
                    strcat(dizi_yeniyolcu3,ukn3);
                    strcat(dizi_yeniyolcu3,"\',");
                    strcat(dizi_yeniyolcu3,id3);
                    strcat(dizi_yeniyolcu3,");");
                }

                mysql_query(conn, dizi_yeniyolcu);

                mysql_query(conn, dizi_yeniyolcu2);

                mysql_query(conn, dizi_yeniyolcu3);

            }

        }


        else{
            if(aktarma==1){
                strcpy(dizi_yeniyolcu,"INSERT INTO yolcu(ismi,adresi,yasadigiSehir,eposta,bn,bin,tckn,tarih,ukn,id) values(\'");
                strcat(dizi_yeniyolcu,row[0]);
                strcat(dizi_yeniyolcu,"\',\'");
                strcat(dizi_yeniyolcu,row[1]);
                strcat(dizi_yeniyolcu,"\',\'");
                strcat(dizi_yeniyolcu,row[2]);
                strcat(dizi_yeniyolcu,"\',\'");
                strcat(dizi_yeniyolcu,row[3]);
                strcat(dizi_yeniyolcu,"\',\'");
                strcat(dizi_yeniyolcu,bn);
                strcat(dizi_yeniyolcu,"\',\'");
                strcat(dizi_yeniyolcu,bin);
                strcat(dizi_yeniyolcu,"\',\'");
                strcat(dizi_yeniyolcu,tckn);
                strcat(dizi_yeniyolcu,"\',\'");
                strcat(dizi_yeniyolcu,tarih);
                strcat(dizi_yeniyolcu,"\',\'");
                strcat(dizi_yeniyolcu,ukn);
                strcat(dizi_yeniyolcu,"\',");
                strcat(dizi_yeniyolcu,id);
                strcat(dizi_yeniyolcu,");");
                mysql_free_result(res);

            if (mysql_query(conn, dizi_yeniyolcu)) {
                    fprintf(stderr, "%s\n", mysql_error(conn));
                    return 1;
                }

        }

            else if(aktarma==2){
                    strcpy(dizi_yeniyolcu,"INSERT INTO yolcu(ismi,adresi,yasadigiSehir,eposta,bn,bin,tckn,tarih,ukn,id) values(\'");
                    strcat(dizi_yeniyolcu,row[0]);
                    strcat(dizi_yeniyolcu,"\',\'");
                    strcat(dizi_yeniyolcu,row[1]);
                    strcat(dizi_yeniyolcu,"\',\'");
                    strcat(dizi_yeniyolcu,row[2]);
                    strcat(dizi_yeniyolcu,"\',\'");
                    strcat(dizi_yeniyolcu,row[3]);
                    strcat(dizi_yeniyolcu,"\',\'");
                    strcat(dizi_yeniyolcu,bn);
                    strcat(dizi_yeniyolcu,"\',\'");
                    strcat(dizi_yeniyolcu,dizi_aktarma1);
                    strcat(dizi_yeniyolcu,"\',\'");
                    strcat(dizi_yeniyolcu,tckn);
                    strcat(dizi_yeniyolcu,"\',\'");
                    strcat(dizi_yeniyolcu,tarih);
                    strcat(dizi_yeniyolcu,"\',\'");
                    strcat(dizi_yeniyolcu,ukn);
                    strcat(dizi_yeniyolcu,"\',");
                    strcat(dizi_yeniyolcu,id);
                    strcat(dizi_yeniyolcu,");");

                    strcpy(dizi_yeniyolcu2,"INSERT INTO yolcu(ismi,adresi,yasadigiSehir,eposta,bn,bin,tckn,tarih,ukn,id) values(\'");
                    strcat(dizi_yeniyolcu2,row[0]);
                    strcat(dizi_yeniyolcu2,"\',\'");
                    strcat(dizi_yeniyolcu2,row[1]);
                    strcat(dizi_yeniyolcu2,"\',\'");
                    strcat(dizi_yeniyolcu2,row[2]);
                    strcat(dizi_yeniyolcu2,"\',\'");
                    strcat(dizi_yeniyolcu2,row[3]);
                    strcat(dizi_yeniyolcu2,"\',\'");
                    strcat(dizi_yeniyolcu2,dizi_aktarma1);
                    strcat(dizi_yeniyolcu2,"\',\'");
                    strcat(dizi_yeniyolcu2,bin);
                    strcat(dizi_yeniyolcu2,"\',\'");
                    strcat(dizi_yeniyolcu2,tckn);
                    strcat(dizi_yeniyolcu2,"\',\'");
                    strcat(dizi_yeniyolcu2,tarih);
                    strcat(dizi_yeniyolcu2,"\',\'");
                    strcat(dizi_yeniyolcu2,ukn2);
                    strcat(dizi_yeniyolcu2,"\',");
                    strcat(dizi_yeniyolcu2,id2);
                    strcat(dizi_yeniyolcu2,");");
                    mysql_free_result(res);

                if (mysql_query(conn, dizi_yeniyolcu)) {
                    fprintf(stderr, "%s\n", mysql_error(conn));
                    return 1;
                }

                if (mysql_query(conn, dizi_yeniyolcu2)) {
                    fprintf(stderr, "%s\n", mysql_error(conn));
                    return 1;
                }

            }

            else if(aktarma==3){
                    strcpy(dizi_yeniyolcu,"INSERT INTO yolcu(ismi,adresi,yasadigiSehir,eposta,bn,bin,tckn,tarih,ukn,id) values(\'");
                    strcat(dizi_yeniyolcu,row[0]);
                    strcat(dizi_yeniyolcu,"\',\'");
                    strcat(dizi_yeniyolcu,row[1]);
                    strcat(dizi_yeniyolcu,"\',\'");
                    strcat(dizi_yeniyolcu,row[2]);
                    strcat(dizi_yeniyolcu,"\',\'");
                    strcat(dizi_yeniyolcu,row[3]);
                    strcat(dizi_yeniyolcu,"\',\'");
                    strcat(dizi_yeniyolcu,bn);
                    strcat(dizi_yeniyolcu,"\',\'");
                    strcat(dizi_yeniyolcu,dizi_aktarma2);
                    strcat(dizi_yeniyolcu,"\',\'");
                    strcat(dizi_yeniyolcu,tckn);
                    strcat(dizi_yeniyolcu,"\',\'");
                    strcat(dizi_yeniyolcu,tarih);
                    strcat(dizi_yeniyolcu,"\',\'");
                    strcat(dizi_yeniyolcu,ukn);
                    strcat(dizi_yeniyolcu,"\',");
                    strcat(dizi_yeniyolcu,id);
                    strcat(dizi_yeniyolcu,");");

                    strcpy(dizi_yeniyolcu2,"INSERT INTO yolcu(ismi,adresi,yasadigiSehir,eposta,bn,bin,tckn,tarih,ukn,id) values(\'");
                    strcat(dizi_yeniyolcu2,row[0]);
                    strcat(dizi_yeniyolcu2,"\',\'");
                    strcat(dizi_yeniyolcu2,row[1]);
                    strcat(dizi_yeniyolcu2,"\',\'");
                    strcat(dizi_yeniyolcu2,row[2]);
                    strcat(dizi_yeniyolcu2,"\',\'");
                    strcat(dizi_yeniyolcu2,row[3]);
                    strcat(dizi_yeniyolcu2,"\',\'");
                    strcat(dizi_yeniyolcu2,dizi_aktarma2);
                    strcat(dizi_yeniyolcu2,"\',\'");
                    strcat(dizi_yeniyolcu2,dizi_aktarma3);
                    strcat(dizi_yeniyolcu2,"\',\'");
                    strcat(dizi_yeniyolcu2,tckn);
                    strcat(dizi_yeniyolcu2,"\',\'");
                    strcat(dizi_yeniyolcu2,tarih);
                    strcat(dizi_yeniyolcu2,"\',\'");
                    strcat(dizi_yeniyolcu2,ukn2);
                    strcat(dizi_yeniyolcu2,"\',");
                    strcat(dizi_yeniyolcu2,id2);
                    strcat(dizi_yeniyolcu2,");");

                    strcpy(dizi_yeniyolcu3,"INSERT INTO yolcu(ismi,adresi,yasadigiSehir,eposta,bn,bin,tckn,tarih,ukn,id) values(\'");
                    strcat(dizi_yeniyolcu3,row[0]);
                    strcat(dizi_yeniyolcu3,"\',\'");
                    strcat(dizi_yeniyolcu3,row[1]);
                    strcat(dizi_yeniyolcu3,"\',\'");
                    strcat(dizi_yeniyolcu3,row[2]);
                    strcat(dizi_yeniyolcu3,"\',\'");
                    strcat(dizi_yeniyolcu3,row[3]);
                    strcat(dizi_yeniyolcu3,"\',\'");
                    strcat(dizi_yeniyolcu3,dizi_aktarma3);
                    strcat(dizi_yeniyolcu3,"\',\'");
                    strcat(dizi_yeniyolcu3,bin);
                    strcat(dizi_yeniyolcu3,"\',\'");
                    strcat(dizi_yeniyolcu3,tckn);
                    strcat(dizi_yeniyolcu3,"\',\'");
                    strcat(dizi_yeniyolcu3,tarih);
                    strcat(dizi_yeniyolcu3,"\',\'");
                    strcat(dizi_yeniyolcu3,ukn3);
                    strcat(dizi_yeniyolcu3,"\',");
                    strcat(dizi_yeniyolcu3,id3);
                    strcat(dizi_yeniyolcu3,");");
                    mysql_free_result(res);


                if (mysql_query(conn, dizi_yeniyolcu)) {
                    fprintf(stderr, "%s\n", mysql_error(conn));
                    return 1;
                }

                if (mysql_query(conn, dizi_yeniyolcu2)) {
                    fprintf(stderr, "%s\n", mysql_error(conn));
                    return 1;
                }

                if (mysql_query(conn, dizi_yeniyolcu3)) {
                    fprintf(stderr, "%s\n", mysql_error(conn));
                    return 1;
                }


            }

        }
    }

 }

 else if(secim==3){
    char dizi_tckn[200];

    printf("Yolcu tc kimlik no giriniz: ");
    scanf("%s",tckn);

    strcpy(dizi_tckn,"SELECT * FROM yolcu WHERE tckn=\'");
    strcat(dizi_tckn,tckn);
    strcat(dizi_tckn,"\';");

    if (mysql_query(conn, dizi_tckn)) {
        return 1;
    }
    res = mysql_use_result(conn);

    if ((row = mysql_fetch_row(res)) == NULL)
           printf("Sistemde boyle bir tc kimlik no bulunamadi");

    else{
        printf("\nIsim:%s\tAdres:%s\tYasadigi Sehir:%s\nEposta:%s\tBas Sehri:%s\tBitis Sehri:%s\nTc Kimlik No:%s\tTarih%s\tUcak Kuyruk No:%s\n\n",row[0],row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8]);

        while ((row = mysql_fetch_row(res)) != NULL){
            printf("\nIsim:%s\tAdres:%s\tYasadigi Sehir:%s\nEposta:%s\tBas Sehri:%s\tBitis Sehri:%s\nTc Kimlik No:%s\tTarih%s\tUcak Kuyruk No:%s\n\n",row[0],row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8]);

        }
    }

 }

 else if(secim==4){
    char dizi_delete[500];
    printf("Ucus silme icin \nUcus baslangic noktasini giriniz: ");
    scanf("%s",bn);
    printf("Ucus bitis noktasini giriniz: ");
    scanf("%s",bin);
    printf("Ucus tarihini giriniz: ");
    scanf("%s",tarih);
    printf("Ucak kuyruk no giriniz: ");
    scanf("%s",ukn);
    printf("Sefer ID giriniz giriniz: ");
    scanf("%s",id);

    strcpy(dizi_delete,"DELETE FROM havaalani.sefer WHERE havaalani.sefer.bn=\'");
    strcat(dizi_delete,bn);
    strcat(dizi_delete,"\' AND havaalani.sefer.bin=\'");
    strcat(dizi_delete,bin);
    strcat(dizi_delete,"\' AND havaalani.sefer.tarih=\'");
    strcat(dizi_delete,tarih);
    strcat(dizi_delete,"\' AND havaalani.sefer.ukn=\'");
    strcat(dizi_delete,ukn);
    strcat(dizi_delete,"\' AND havaalani.sefer.id=\'");
    strcat(dizi_delete,id);
    strcat(dizi_delete,"\';");

    if (mysql_query(conn, dizi_delete)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

}

 else if(secim==5){

    char dizi_biletiptal[500];

    printf("Bilet iptali icin \nTc kimlik no giriniz: ");
    scanf("%s",tckn);
    printf("Bilet tarihini giriniz: ");
    scanf("%s",tarih);
    printf("Ucak kimlik no giriniz: ");
    scanf("%s",ukn);

    strcpy(dizi_biletiptal,"DELETE FROM havaalani.yolcu WHERE havaalani.yolcu.tckn=\'");
    strcat(dizi_biletiptal,tckn);
    strcat(dizi_biletiptal,"\' AND havaalani.yolcu.tarih=\'");
    strcat(dizi_biletiptal,tarih);
    strcat(dizi_biletiptal,"\' AND havaalani.yolcu.ukn=\'");
    strcat(dizi_biletiptal,ukn);
    strcat(dizi_biletiptal,"\';");

    if (mysql_query(conn, dizi_biletiptal)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    /*if(mysql_real_connect!=0)
            printf("Boyle bir bilet bulunmamaktadir");*/
}

 else if(secim==6){
    char dizi_sefer_sorgu[200];

    printf("Sefer tarihini giriniz: ");
    scanf("%s",tarih);
    printf("Sefer ucaginin kuyruk nosunu giriniz: ");
    scanf("%s",ukn);


    strcpy(dizi_sefer_sorgu,"SELECT * FROM yolcu WHERE tarih=\'");
    strcat(dizi_sefer_sorgu,tarih);
    strcat(dizi_sefer_sorgu,"\' AND ukn=\'");
    strcat(dizi_sefer_sorgu,ukn);
    strcat(dizi_sefer_sorgu,"\';");

    if (mysql_query(conn, dizi_sefer_sorgu)) {
        return 1;
    }

    res = mysql_use_result(conn);

    if ((row = mysql_fetch_row(res)) == NULL)
           printf("Boyle bir sefer sorgusu bulunamadi");

    else{
        printf("\nIsim: %s\tAdres: %s\tYasadigi Sehir: %s\nEposta: %s\tBas Sehir: %s\tBitis Sehri: %s\nTc Kimlik No: %s\tTarih: %s\tUcak Kimlik No: %s\tSefer ID: %s\n\n",row[0],row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8],row[9]);

        while ((row = mysql_fetch_row(res)) != NULL){
            printf("\nIsim: %s\tAdres: %s\tYasadigi Sehir: %s\nEposta: %s\tBas Sehir: %s\tBitis Sehri: %s\nTc Kimlik No: %s\tTarih: %s\tUcak Kimlik No: %s\tSefer ID: %s\n\n",row[0],row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8],row[9]);

        }
    }

}

 else if(secim==7){

    if (mysql_query(conn,"Select *, COUNT(*) AS sayac From yolcu group by ukn,tarih order by sayac desc;")) {
        return 1;
    }

    res = mysql_use_result(conn);

    while ((row = mysql_fetch_row(res)) != NULL){
            printf("Baslangic nok:%s \tBitis nok:%s \tTarih:%s \tUcak Kanat No:%s \tSefer ID:%s \tDoluluk:%s \n",row[4],row[5],row[7],row[8],row[9],row[10]);
    }

}

 res = mysql_use_result(conn);

 mysql_free_result(res);
 mysql_close(conn);
 return 0;
}

