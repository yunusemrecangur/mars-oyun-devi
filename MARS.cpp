
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

int main() {

    srand(time(NULL));

    // Karakter durum degiskenleri
    int saglik = 100;
    int enerji = 100;
    int oksijen = 100;
    int su = 30;
    int yedekParca = 5;
    int modulHasari = 10;

    int kilitMuhurlu = 0;
    int gun = 1;
    int tur = 0;

    int zorluk;
    int firtinaSuresi = 3;
    int esik = 50;

    int oyunDevam = 1;
    int oyunKazandi = 0;

    char komut;
    int zar;

    printf("=====================================\n");
    printf("   MARS KOLONISI YASAM DESTEK SISTEMI\n");
    printf("=====================================\n");

    // Zorluk secimi
    do {

        printf("\nZorluk Seviyesi Seciniz:\n");
        printf("K - Kolay\n");
        printf("N - Normal\n");
        printf("Z - Zor\n");
        printf("Seciminiz: ");

        scanf(" %c", &komut);
        komut = toupper(komut);

        switch (komut) {

            case 'K':
                zorluk = 1;
                su = 40;
                yedekParca = 7;
                firtinaSuresi = 3;
                esik = 65;
                printf("\nKolay seviye secildi.\n");
                break;

            case 'N':
                zorluk = 2;
                su = 30;
                yedekParca = 5;
                firtinaSuresi = 5;
                esik = 50;
                printf("\nNormal seviye secildi.\n");
                break;

            case 'Z':
                zorluk = 3;
                su = 20;
                yedekParca = 3;
                firtinaSuresi = 7;
                esik = 35;
                printf("\nZor seviye secildi.\n");
                break;

            default:
                zorluk = 0;
                printf("Gecersiz zorluk seviyesi! Tekrar deneyin.\n");
        }

    } while (zorluk == 0);

    printf("\nKurtarma ekibi 15 gun sonra gelecek.\n");
    printf("Hayatta kalmak icin bol sans!\n");

    // Ana oyun dongusu
    do {

        printf("\n=====================================\n");
        printf("GUN: %d | TUR: %d\n", gun, tur);
        printf("=====================================\n");

        printf("G - Kesif\n");
        printf("O - Oksijen Uret\n");
        printf("T - Tamir\n");
        printf("D - Durum Raporu\n");
        printf("U - Uyu / Dinlen\n");
        printf("K - Kum Firtinasi\n");
        printf("H - Hava Kilidi\n");
        printf("Q - Cikis\n");

        printf("\nKomutunuz: ");
        scanf(" %c", &komut);

        komut = toupper(komut);

        int gecerliKomut = 1;

        switch (komut) {

            // KESIF
            case 'G': {

                if (enerji < 15 || oksijen < 10) {
                    printf("Yetersiz enerji veya oksijen! Kesif yapilamadi.\n");
                    break;
                }

                enerji -= 15;
                oksijen -= 10;

                printf("\nKesif gorevi baslatildi.\n");

                if (enerji > 40 && oksijen > 30)
                    esik = 65;
                else
                    esik = 30;

                zar = rand() % 100;

                printf("Su bulma zari: %d / Esik: %d -> ", zar, esik);

                if (zar < esik) {
                    int bulunanSu = 5 + rand() % 6;
                    su += bulunanSu;
                    printf("BASARILI! %d birim su bulundu.\n", bulunanSu);
                }
                else {
                    printf("BASARISIZ! Su bulunamadi.\n");
                }

                zar = rand() % 100;

                printf("Yedek parca zari: %d / Esik: 45 -> ", zar);

                if (zar < 45) {
                    yedekParca++;
                    printf("BASARILI! 1 yedek parca bulundu.\n");
                }
                else {
                    printf("BASARISIZ! Parca bulunamadi.\n");
                }

                zar = rand() % 100;

                printf("Yaralanma zari: %d / Esik: 10 -> ", zar);

                if (zar < 10 || modulHasari > 70) {
                    saglik -= 15;
                    printf("YARALANDINIZ! 15 saglik kaybettiniz.\n");
                }
                else {
                    printf("BASARILI! Yaralanma olmadi.\n");
                }

                break;
            }

            // OKSIJEN URETIMI
            case 'O': {

                int miktar;

                printf("Kac birim su kullanmak istiyorsunuz? ");
                scanf("%d", &miktar);

                if (miktar <= 0 || miktar > su) {
                    printf("Gecersiz su miktari!\n");
                    break;
                }

                if (enerji < miktar) {
                    printf("Yetersiz enerji! Uretim yapilamadi.\n");
                    break;
                }

                if (miktar % 2 == 0) {

                    int uretilenOksijen = (miktar / 2) * 3;

                    if (oksijen + uretilenOksijen > 100)
                        uretilenOksijen = 100 - oksijen;

                    oksijen += uretilenOksijen;
                    su -= miktar;
                    enerji -= miktar;

                    printf("%d birim su kullanildi.\n", miktar);
                    printf("%d birim oksijen uretildi.\n", uretilenOksijen);

                }
                else {

                    int kullanilanSu = miktar - 1;
                    int uretilenOksijen = (kullanilanSu / 2) * 3;

                    if (oksijen + uretilenOksijen > 100)
                        uretilenOksijen = 100 - oksijen;

                    oksijen += uretilenOksijen;
                    su -= kullanilanSu;
                    enerji -= kullanilanSu;

                    printf("Tek miktar girildi.\n");
                    printf("1 birim su depoda kaldi.\n");
                    printf("%d birim oksijen uretildi.\n", uretilenOksijen);
                }

                break;
            }

            // TAMIR
            case 'T': {

                if (yedekParca <= 0) {
                    printf("Yedek parca bulunmadigi icin tamir yapilamadi.\n");
                    break;
                }

                if (enerji < 10) {
                    printf("Yetersiz enerji! Tamir yapilamadi.\n");
                    break;
                }

                if (modulHasari <= 0) {
                    printf("Modul zaten tamamen saglam.\n");
                    break;
                }

                if (modulHasari <= 30) {

                    modulHasari -= 15;
                    yedekParca--;

                    printf("Hafif hasar onarildi.\n");

                }
                else if (modulHasari <= 70) {

                    modulHasari -= 20;
                    yedekParca--;

                    printf("Orta seviye hasar onarildi.\n");

                }
                else {

                    if (yedekParca < 2) {
                        printf("Agir hasar icin en az 2 parca gerekiyor.\n");
                        break;
                    }

                    modulHasari -= 30;
                    yedekParca -= 2;

                    printf("Agir hasar onarildi.\n");
                }

                enerji -= 10;

                break;
            }

            // DURUM RAPORU
            case 'D': {

                printf("\n========== DURUM RAPORU ==========\n");

                printf("Saglik       : %d\n", saglik);
                printf("Enerji       : %d\n", enerji);
                printf("Oksijen      : %d\n", oksijen);
                printf("Su           : %d\n", su);
                printf("Yedek Parca  : %d\n", yedekParca);
                printf("Modul Hasari : %d\n", modulHasari);
                printf("Kilit Muhurlu: %d\n", kilitMuhurlu);
                printf("Gun          : %d\n", gun);
                printf("Tur          : %d\n", tur);

                if (oksijen < 25)
                    printf("UYARI: Oksijen kritik seviyede!\n");

                if (saglik < 30)
                    printf("UYARI: Saglik kritik seviyede!\n");

                if (enerji < 20)
                    printf("UYARI: Enerji kritik seviyede!\n");

                if (modulHasari > 70)
                    printf("UYARI: Modul agir hasarli!\n");

                if (su < 5)
                    printf("UYARI: Su rezervi kritik!\n");

                if (yedekParca == 0)
                    printf("UYARI: Yedek parca kalmadi!\n");

                if (oksijen >= 25 && saglik >= 30 &&
                    enerji >= 20 && modulHasari <= 70 &&
                    su >= 5 && yedekParca > 0) {

                    printf("TUM SISTEMLER NORMAL.\n");
                }

                printf("==================================\n");

                gecerliKomut = 0;

                break;
            }

            // DINLENME
            case 'U': {

                if (oksijen < 5) {
                    printf("Dinlenmek icin yeterli oksijen yok!\n");
                    break;
                }

                enerji += 25;

                if (oksijen >= 20) {

                    saglik += 15;
                    printf("Dinlenme basarili. Saglik ve enerji yenilendi.\n");

                }
                else {

                    saglik -= 10;
                    printf("Oksijen yetersiz! Dinlenirken saglik kaybettiniz.\n");

                }

                oksijen -= 5;

                break;
            }

            // KUM FIRTINASI
            case 'K': {

                if (enerji < 10) {
                    printf("Yetersiz enerji! Firtinaya hazirlanilamadi.\n");
                    break;
                }

                enerji -= 10;

                int toplamSaglikKaybi = 0;
                int toplamOksijenKaybi = 0;
                int hasarAlinanTur = 0;

                int i;  // FOR dongusu sayac degiskeni

                printf("\nKUM FIRTINASI BASLADI!\n");

                for (i = 1; i <= firtinaSuresi; i++) {

                    if (saglik <= 0 || oksijen <= 0)
                        break;

                    zar = rand() % 100;

                    printf("\nFirtina turu %d - Zar: %d / Esik: 40 -> ", i, zar);

                    if (kilitMuhurlu == 1 && zar >= 30 && zar < 60) {
                        printf("Hava kilidi sayesinde oksijen sizintisi onlendi.\n");
                        continue;
                    }

                    if (zar < 30) {

                        int kayip = 5;

                        if (i % 2 == 0)
                            kayip *= 2;

                        modulHasari += kayip;
                        hasarAlinanTur++;

                        printf("Modul hasari artti: %d\n", kayip);

                    }
                    else if (zar < 60) {

                        int kayip = 5;

                        oksijen -= kayip;
                        toplamOksijenKaybi += kayip;

                        printf("Oksijen sizintisi: %d\n", kayip);

                    }
                    else if (zar < 80) {

                        int kayip = 5;

                        if (i % 2 == 0)
                            kayip *= 2;

                        saglik -= kayip;
                        toplamSaglikKaybi += kayip;

                        printf("Can kaybi: %d\n", kayip);

                    }
                    else {

                        printf("Firtinadan zarar gormeden korunuldu.\n");

                    }

                    if (saglik <= 0 || oksijen <= 0) {
                        printf("Hayati tehlike! Firtina durduruldu.\n");
                        break;
                    }
                }

                printf("\nFIRTINA OZETI\n");
                printf("Hasar alinan tur: %d\n", hasarAlinanTur);
                printf("Kaybedilen saglik: %d\n", toplamSaglikKaybi);
                printf("Kaybedilen oksijen: %d\n", toplamOksijenKaybi);

                break;
            }

            // HAVA KILIDI SIFRESI
            case 'H': {

                if (kilitMuhurlu == 1) {
                    printf("Hava kilidi zaten muhurlenmis!\n");
                    break;
                }

                if (enerji < 5) {
                    printf("Yetersiz enerji! Kilit muhurlenemedi.\n");
                    break;
                }

                char sifre;
                char giris;
                int deneme = 0;

                sifre = 'A' + (gun % 26);

                printf("\nHAVA KILIDI SIFRELEME SISTEMI\n");
                printf("Ipucu: Sifre, A harfinden bugunun gun sayisi kadar ileridedir.\n");

                do {

                    printf("%d. deneme - Sifreyi giriniz: ", deneme + 1);
                    scanf(" %c", &giris);

                    giris = toupper(giris);
                    deneme++;

                    if (giris != sifre) {

                        enerji -= 5;

                        if (giris < sifre)
                            printf("Yanlis! Ileri git.\n");
                        else
                            printf("Yanlis! Geri git.\n");

                    }
                    else {

                        kilitMuhurlu = 1;
                        printf("Sifre dogru! Hava kilidi muhurlendi.\n");

                    }

                } while (giris != sifre && deneme < 3);

                if (kilitMuhurlu == 0) {

                    modulHasari += 20;
                    printf("Uc deneme de basarisiz! Modul hasari 20 artti.\n");

                }

                break;
            }

            // CIKIS
            case 'Q':

                printf("\nSimulasyondan cikiliyor...\n");
                oyunDevam = 0;

                break;

            // GECERSIZ KOMUT
            default:

                printf("Gecersiz komut! Bu komut tur harcamaz.\n");
                gecerliKomut = 0;

                break;
        }

        // Kaynak sinirlandirma
        if (saglik < 0)
            saglik = 0;
        if (saglik > 100)
            saglik = 100;

        if (enerji < 0)
            enerji = 0;
        if (enerji > 100)
            enerji = 100;

        if (oksijen < 0)
            oksijen = 0;
        if (oksijen > 100)
            oksijen = 100;

        if (modulHasari < 0)
            modulHasari = 0;
        if (modulHasari > 100)
            modulHasari = 100;

        // Gecerli komutlarda tur ilerletme
        if (gecerliKomut == 1 && oyunDevam == 1) {

            tur++;

            if (tur % 3 == 0) {

                gun++;

                printf("\nYENI GUN: %d\n", gun);

                oksijen -= 8;

                if (modulHasari > 70)
                    saglik -= 5;

            }
        }

        // Gun sonu ve olum kontrolu
        if (saglik <= 0 || oksijen <= 0) {

            saglik = 0;
            oyunDevam = 0;

            printf("\nHAYATTA KALAMADINIZ! OYUN KAYBEDILDI.\n");

        }

        // 15 gun kontrolu
        if (gun > 15 && saglik > 0 && oksijen > 0) {

            oyunKazandi = 1;
            oyunDevam = 0;

            printf("\nKURTARMA EKIBI GELDI! OYUNU KAZANDINIZ!\n");

        }

    } while (oyunDevam == 1);

    // SONUC RAPORU
    printf("\n=====================================\n");
    printf("          SIMULASYON SONUCU\n");
    printf("=====================================\n");

    if (oyunKazandi == 1)
        printf("SONUC: BASARILI - KURTARILDINIZ!\n");
    else if (saglik <= 0 || oksijen <= 0)
        printf("SONUC: BASARISIZ - KARAKTER HAYATINI KAYBETTI.\n");
    else
        printf("SONUC: OYUNCU SIMULASYONDAN CIKTI.\n");

    int puan = (gun * 100) + saglik + oksijen - modulHasari;

    printf("Hayatta kalinan gun: %d\n", gun);
    printf("Toplam tur: %d\n", tur);
    printf("Saglik: %d\n", saglik);
    printf("Enerji: %d\n", enerji);
    printf("Oksijen: %d\n", oksijen);
    printf("Su: %d\n", su);
    printf("Yedek parca: %d\n", yedekParca);
    printf("Modul hasari: %d\n", modulHasari);
    printf("Hava kilidi muhur durumu: %d\n", kilitMuhurlu);
    printf("-------------------------------------\n");
    printf("TOPLAM PUAN: %d\n", puan);
    printf("=====================================\n");

    return 0;
}

