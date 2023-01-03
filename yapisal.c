#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

void dbgPrint(char *msg)
{
    printf("\033[0;31m");
    printf("\n");
    printf("%s", msg);
    printf("\n");
    printf("\033[0m");
}
//**********************************************   STRUCT TANIMLAMALARI   ***********************************************
#pragma region StructTanimlamalari
//------------------------------------------------------------
typedef struct Ogrenci
{
    char ogrID[10];
    char ad[30];
    char soyad[30];
    int puan;
    struct Ogrenci *next;
    struct Ogrenci *prev;
} Ogrenci;
//------------------------------------------------------------
typedef struct Yazar
{
    int yazarID;
    char yazarAd[30];
    char yazarSoyad[30];
    struct Yazar *next;
} Yazar;
//------------------------------------------------------------
typedef struct KitapOrnek
{
    char EtiketNo[20];
    char Durum[10];
    struct KitapOrnek *next;
} KitapOrnek;
//------------------------------------------------------------
typedef struct Kitap
{
    char kitapAdi[30];
    char ISBN[13];
    int adet;
    struct Kitap *next;
    struct KitapOrnek *head;
} Kitap;
//------------------------------------------------------------
typedef struct KitapYazar
{
    char ISBN[13];
    int YazarID;
} KitapYazar;
//------------------------------------------------------------
typedef struct Tarih
{
    int gun : 5;
    int ay : 4;
    int yil : 12;
} Tarih;
//------------------------------------------------------------
typedef struct KitapOdunc
{
    char EtiketNo[20];
    char ogrID[8];
    int islemTipi : 1;
    struct Tarih islemTarihi;
} KitapOdunc;
#pragma endregion StructTanimlamalari
//**********************************************   YAZAR FONKSIYONLARI   ************************************************
#pragma region YazarFonksiyonlari
//------------------------------------------------------------
void yazarEkle(Yazar **yazarListesi, char *ad, char *soyad)
{
    Yazar *yazar = (Yazar *)malloc(sizeof(Yazar));
    yazar->yazarID = 0; // initialize yazarID to 0
    strcpy(yazar->yazarAd, ad);
    strcpy(yazar->yazarSoyad, soyad);
    yazar->next = NULL;

    // Yazar listesi boşsa, yeni yazarı listenin başına ekle
    if (*yazarListesi == NULL)
    {
        *yazarListesi = yazar;
        yazar->yazarID = 1; // assign ID of 1 to the first node
    }
    else
    {
        // Listenin sonuna kadar ilerle
        Yazar *iter = *yazarListesi;
        while (iter->next != NULL)
        {
            iter = iter->next;
        }
        // Listenin sonuna yeni yazarı ekle
        yazar->yazarID = iter->yazarID + 1; // assign ID to the new node by increasing the ID of the last node by 1
        iter->next = yazar;
    }
}
//------------------------------------------------------------
void yazarSil(Yazar *yazarListesi, int yazarID)
{
    Yazar *iter = yazarListesi;
    Yazar *prev = NULL;

    // Listenin ilk elemanı aranılan yazar ise
    if (iter != NULL && iter->yazarID == yazarID)
    {
        yazarListesi = iter->next; // İlk elemanı atla
        free(iter);                // Önceden alınan yerin belleğinden serbest bırak
        return;
    }

    // Listenin diğer elemanlarını arama
    while (iter != NULL && iter->yazarID != yazarID)
    {
        prev = iter;
        iter = iter->next;
    }

    // Eğer aranan yazar bulunamadıysa, uyarı ver
    if (iter == NULL)
    {
        printf("Yazar bulunamadi.\n");
        return;
    }

    // Aranan yazar bulunduysa, listenin içinden çıkar
    prev->next = iter->next;
    free(iter); // Önceden alınan yerin belleğinden serbest bırak
}
//------------------------------------------------------------
void yazarDuzenle(Yazar *yazarListesi, int yazarID, char *yeniAd, char *yeniSoyad)
{
    Yazar *iter = yazarListesi;

    // Listenin ilk elemanı aranılan yazar ise
    if (iter != NULL && iter->yazarID == yazarID)
    {
        strcpy(iter->yazarAd, yeniAd);
        strcpy(iter->yazarSoyad, yeniSoyad);
        return;
    }

    // Listenin diğer elemanlarını arama
    while (iter != NULL && iter->yazarID != yazarID)
    {
        iter = iter->next;
    }

    // Eğer aranan yazar bulunamadıysa, uyarı ver
    if (iter == NULL)
    {
        printf("Yazar bulunamadi.\n");
        return;
    }

    // Aranan yazar bulunduysa, bilgilerini güncelle
    strcpy(iter->yazarAd, yeniAd);
    strcpy(iter->yazarSoyad, yeniSoyad);
}
//------------------------------------------------------------
void yazarListele(Yazar *yazarListesi)
{
    printf("\nYazar Listesi:\n");
    Yazar *iter = yazarListesi;

    while (iter != NULL)
    {
        printf("Yazar ID: %d, Ad: %s, Soyad: %s\n", iter->yazarID, iter->yazarAd, iter->yazarSoyad);
        iter = iter->next;
    }
}
#pragma endregion YazarFonksiyonlari
//**********************************************   KİTAP FONKSIYONLARI   ************************************************
#pragma region KitapFonksiyonlari
//------------------------------------------------------------
void kitapEkle(Kitap **kitapListesi, char *ad, char *ISBN, int adet, KitapOrnek **KitapOrnekListesi)
{
    Kitap *kitap = (Kitap *)malloc(sizeof(Kitap));
    strcpy(kitap->kitapAdi, ad);
    strcpy(kitap->ISBN, ISBN);
    kitap->adet = adet;
    kitap->next = NULL;
    kitap->head = *KitapOrnekListesi;

    // Kitap listesi boşsa, yeni kitabı listenin başına ekle
    if (*kitapListesi == NULL)
    {
        *kitapListesi = kitap;
    }
    else
    {
        // Listenin sonuna kadar ilerle
        Kitap *iter = *kitapListesi;
        while (iter->next != NULL)
        {
            iter = iter->next;
        }
        // Listenin sonuna yeni kitabı ekle
        iter->next = kitap;
    }
}
//------------------------------------------------------------
void kitapSil(Kitap *kitapListesi, char *ISBN)
{
    Kitap *iter = kitapListesi;
    Kitap *prev = NULL;

    // Listenin ilk elemanı aranılan kitap ise
    if (iter != NULL && strcmp(iter->ISBN, ISBN) == 0)
    {
        kitapListesi = iter->next; // İlk elemanı atla
        free(iter);                // Önceden alınan yerin belleğinden serbest bırak
        return;
    }

    // Listenin diğer elemanlarını arama
    while (iter != NULL && strcmp(iter->ISBN, ISBN) != 0)
    {
        prev = iter;
        iter = iter->next;
    }

    // Eğer aranan kitap bulunamadıysa, uyarı ver
    if (iter == NULL)
    {
        printf("Kitap bulunamadi.\n");
        return;
    }

    // Aranan kitap bulunduysa, listenin içinden çıkar
    prev->next = iter->next;
    free(iter); // Önceden alınan yerin belleğinden serbest bırak
}
//------------------------------------------------------------
void kitapDuzenle(Kitap *kitapListesi, char *ISBN, char *yeniAd, int yeniAdet)
{
    Kitap *iter = kitapListesi;

    // Listenin ilk elemanı aranılan kitap ise
    if (iter != NULL && strcmp(iter->ISBN, ISBN) == 0)
    {
        strcpy(iter->kitapAdi, yeniAd);
        iter->adet = yeniAdet;
        return;
    }

    // Listenin diğer elemanlarını arama
    while (iter != NULL && strcmp(iter->ISBN, ISBN) != 0)
    {
        iter = iter->next;
    }

    // Eğer aranan kitap bulunamadıysa, uyarı ver
    if (iter == NULL)
    {
        printf("Kitap bulunamadi.\n");
        return;
    }

    // Aranan kitap bulunduysa, bilgilerini güncelle
    strcpy(iter->kitapAdi, yeniAd);
    iter->adet = yeniAdet;
}
//------------------------------------------------------------
void kitapOrnekListele(KitapOrnek *kitapOrnekListesi)
{
    KitapOrnek *iter = kitapOrnekListesi;

    while (iter != NULL)
    {
        printf("--> ISBN: %s, Durum: %s\n", iter->EtiketNo, iter->Durum);
        iter = iter->next;
    }
}
//------------------------------------------------------------
void kitapListele(Kitap *kitapListesi)
{
    printf("\nKitap Listesi:\n");
    Kitap *iter = kitapListesi;

    while (iter != NULL)
    {
        printf("ISBN: %s, Ad: %s, Adet: %d\n", iter->ISBN, iter->kitapAdi, iter->adet);

        kitapOrnekListele(iter->head);

        iter = iter->next;
    }
}
//------------------------------------------------------------
void kitapOrnekEkle(KitapOrnek **KitapOrnekListesi, char *etiketNo, char *Durum)
{
    KitapOrnek *kitapOrnek = (KitapOrnek *)malloc(sizeof(KitapOrnek));
    strcpy(kitapOrnek->EtiketNo, etiketNo);
    strcpy(kitapOrnek->Durum, Durum);
    kitapOrnek->next = NULL;

    // Kitap listesi boşsa, yeni kitabı listenin başına ekle
    if (*KitapOrnekListesi == NULL)
    {
        *KitapOrnekListesi = kitapOrnek;
    }
    else
    {
        // Listenin sonuna kadar ilerle
        KitapOrnek *iter = *KitapOrnekListesi;
        while (iter->next != NULL)
        {
            iter = iter->next;
        }
        // Listenin sonuna yeni kitabı ekle
        iter->next = kitapOrnek;
    }
}
//------------------------------------------------------------
#pragma endregion KitapFonksiyonlari
//**********************************************   ÖĞRENCİ FONKSIYONLARI   **********************************************
#pragma region OgrenciFonksiyonlari
//------------------------------------------------------------
void ogrenciEkle(Ogrenci **ogrenciListesi, char *ad, char *soyad, int puan, char *ogrenciNo)
{
    Ogrenci *ogrenci = (Ogrenci *)malloc(sizeof(Ogrenci));
    strcpy(ogrenci->ad, ad);
    strcpy(ogrenci->soyad, soyad);
    ogrenci->puan = puan;
    strcpy(ogrenci->ogrID, ogrenciNo);
    ogrenci->next = NULL;
    ogrenci->prev = NULL;

    // Öğrenci listesinde tek bir eleman varsa, yeni öğrenci bu elemanın yerini alır
    if (*ogrenciListesi == NULL)
    {
        *ogrenciListesi = ogrenci;
    }
    else
    {
        // Listenin sonuna kadar ilerle
        Ogrenci *iter = *ogrenciListesi;
        while (iter->next != NULL)
        {
            iter = iter->next;
        }
        // Listenin sonuna yeni öğrenciyi ekle
        iter->next = ogrenci;
        ogrenci->prev = iter;
    }
}
//------------------------------------------------------------
void ogrenciSil(Ogrenci *ogrenciListesi, char *ogrenciNo)
{
    Ogrenci *iter = ogrenciListesi;
    Ogrenci *prev = NULL;

    // Listenin ilk elemanı aranılan öğrenci ise
    if (iter != NULL && strcmp(iter->ogrID, ogrenciNo) == 0)
    {
        ogrenciListesi = iter->next; // İlk elemanı atla
        if (iter->next != NULL)
        {
            iter->next->prev = NULL;
        }
        free(iter); // Önceden alınan yerin belleğinden serbest bırak
        return;
    }

    // Listenin diğer elemanlarını arama
    while (iter != NULL && strcmp(iter->ogrID, ogrenciNo) != 0)
    {
        prev = iter;
        iter = iter->next;
    }

    // Eğer aranan öğrenci bulunamadıysa, uyarı ver
    if (iter == NULL)
    {
        printf("Ogrenci bulunamadi.\n");
        return;
    }

    // Aranan öğrenci bulunduysa, listenin içinden çıkar
    prev->next = iter->next;
    if (iter->next != NULL)
    {
        iter->next->prev = prev;
    }
    free(iter); // Önceden alınan yerin belleğinden serbest bırak
}
//------------------------------------------------------------
void ogrenciDuzenle(Ogrenci *ogrenciListesi, char *ogrenciNo, char *yeniAd, char *yeniSoyad, int yeniPuan)
{
    Ogrenci *iter = ogrenciListesi;

    // Listenin ilk elemanı aranılan öğrenci ise
    if (iter != NULL && strcmp(iter->ogrID, ogrenciNo) == 0)
    {
        strcpy(iter->ad, yeniAd);
        strcpy(iter->soyad, yeniSoyad);
        iter->puan = yeniPuan;
        return;
    }

    // Listenin diğer elemanlarını arama
    while (iter != NULL && strcmp(iter->ogrID, ogrenciNo) != 0)
    {
        iter = iter->next;
    }

    // Eğer aranan öğrenci bulunamadıysa, uyarı ver
    if (iter == NULL)
    {
        printf("Ogrenci bulunamadi.\n");
        return;
    }

    // Aranan öğrenci bulunduysa, bilgilerini güncelle
    strcpy(iter->ad, yeniAd);
    strcpy(iter->soyad, yeniSoyad);
    iter->puan = yeniPuan;
}
//------------------------------------------------------------
void ogrenciListele(Ogrenci *ogrenciListesi)
{
    printf("\nOgrenci Listesi:\n");
    Ogrenci *iter = ogrenciListesi;

    while (iter != NULL)
    {
        printf("Ad: %s, Soyad: %s, Puan: %d, Ogrenci No: %s\n", iter->ad, iter->soyad, iter->puan, iter->ogrID);
        iter = iter->next;
    }
}
//------------------------------------------------------------
Ogrenci ogrenciAra(Ogrenci *ogrenciListesi, char *ogrenciNo)
{
    Ogrenci *iter = ogrenciListesi;

    // Listenin ilk elemanı aranılan öğrenci ise
    if (iter != NULL && strcmp(iter->ogrID, ogrenciNo) == 0)
    {
        return *iter;
    }

    // Listenin diğer elemanlarını arama
    while (iter != NULL && strcmp(iter->ogrID, ogrenciNo) != 0)
    {
        iter = iter->next;
    }

    // Eğer aranan öğrenci bulunamadıysa, uyarı ver
    if (iter == NULL)
    {
        printf("Ogrenci bulunamadi.\n");
        return *iter;
    }

    // Aranan öğrenci bulunduysa, bilgilerini döndür
    return *iter;
}
#pragma endregion OgrenciFonksiyonlari
//**********************************************   ODÜNÇ İŞLEMLERİ FONKSİYONLARI **********************************************
Kitap kitapAra(Kitap *kitapListesi, char *kitapID)
{
    Kitap *iter = kitapListesi;

    while (iter != NULL && strcmp(iter->ISBN, kitapID) != 0)
    {
        iter = iter->next;
    }

    return *iter;
}
//------------------------------------------------------------
Yazar yazarAra(Yazar *yazarListesi, char *yazarID)
{
    Yazar *iter = yazarListesi;

    char yazarID2[10];
    while (iter != NULL && strcmp(itoa(iter->yazarID,yazarID2,10), yazarID) != 0)
    {
        iter = iter->next;
    }

    return *iter;
}
//------------------------------------------------------------
int check_book_availability(char *book_label_number)
{
    // Open the database file
    FILE *fp = fopen("KitapDurumu.csv", "r");

    // Read each record from the file
    KitapOdunc record;
    int available = 1;
    while (fscanf(fp, "%d,%d,%d,%10s", &record.ogrID, &record.EtiketNo, record.islemTipi, record.islemTarihi) == 4)
    {
        if (record.EtiketNo == book_label_number && record.islemTipi == 0)
        {
            available = 0;
            break;
        }
    }

    // Close the file and return the availability
    fclose(fp);
    return available;
}
//------------------------------------------------------------
void oduncVer(Ogrenci *ogrenciListesi, Kitap *kitapListesi, char ogrID, char kitapEtiketNo)
{
    // Öğrenci ve kitap listelerinde arama yap
    Ogrenci *ogrenci = NULL;
    *ogrenci = ogrenciAra(ogrenciListesi, ogrID);
    Kitap *kitap = NULL;
    *kitap = kitapAra(kitapListesi, kitapEtiketNo);

    // Eğer öğrenci veya kitap bulunamadıysa, uyarı ver
    if (ogrenci->ogrID == -1 || kitap->ISBN == -1)
    {
        printf("Ogrenci veya kitap bulunamadi.\n");
        return;
    }

    // Eğer kitap öğrenciye ödünç verilmişse, uyarı ver
    if (check_book_availability(kitapEtiketNo) == 0)
    {
        printf("Kitap zaten ogrenciye verilmis.\n");
        return;
    }

    // Kitap öğrenciye ödünç verilebilirse, veritabanına kaydet
    FILE *fp = fopen("KitapDurumu.csv", "a");
    fprintf(fp, "%d,%d,%d,%s", ogrID, kitapEtiketNo, 0, "2020-01-01");
    fclose(fp);
}
//------------------------------------------------------------
void oduncAl(Ogrenci *ogrenciListesi, Kitap *kitapListesi, int ogrID, int kitapEtiketNo)
{
    // Öğrenci ve kitap listelerinde arama yap
    Ogrenci *ogrenci = NULL;
    *ogrenci = ogrenciAra(ogrenciListesi, ogrID);
    Kitap *kitap = NULL;
    *kitap = kitapAra(kitapListesi, kitapEtiketNo);

    // Eğer öğrenci veya kitap bulunamadıysa, uyarı ver
    if (ogrenci->ogrID == -1 || kitap->ISBN == -1)
    {
        printf("Ogrenci veya kitap bulunamadi.\n");
        return;
    }

    // Eğer kitap öğrenciye ödünç verilmemişse, uyarı ver
    if (check_book_availability(kitapEtiketNo) == 1)
    {
        printf("Kitap ogrenciye verilmemis.\n");
        return;
    }

    // Kitap öğrenciden alınabilirse, veritabanına kaydet
    FILE *fp = fopen("KitapDurumu.csv", "a");
    fprintf(fp, "%d,%d,%d,%s", ogrID, kitapEtiketNo, 1, "2020-01-01");
    fclose(fp);
}
//**********************************************   KİTAP-YAZAR İLİŞKİLENDİRME FONKSIYONLARI   ***************************
//------------------------------------------------------------
void kitapYazarEslestir(Kitap **kitapListesi, Yazar **yazarListesi, KitapYazar *kitapYazar)
{
    Kitap *kitap = NULL;
    *kitap = kitapAra(kitapListesi, kitapYazar->ISBN);

    Yazar *yazar = NULL;
    *yazar = yazarAra(yazarListesi, kitapYazar->YazarID);

    if (kitap == NULL || yazar == NULL)
    {
        printf("Kitap veya yazar bulunamadi.\n");
        return;
    }

    appendCSV("KitapYazar.csv", kitapYazar->ISBN, kitapYazar->YazarID);
}
//**********************************************   DOSYALAMA FONKSIYONLARI   ********************************************
#pragma region DosyalamaFonksiyonlari
//------------------------------------------------------------
// Function to read data from a CSV file
void readCSV(const char *filename)
{
    int BUFFER_SIZE = 1024;
    // Open the CSV file
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Error: Could not open file '%s'\n", filename);
        return;
    }

    // Read the data from the file, one line at a time
    char buffer[1024];
    while (fgets(buffer, BUFFER_SIZE, fp) != NULL)
    {
        // Find the length of the line (excluding the newline character)
        int length = strcspn(buffer, "\n");
        // Copy the line into the buffer without the newline character
        strncpy(buffer, buffer, length);
        // Add a null terminator to the end of the string
        buffer[length] = '\0';

        // Split the line into individual values
        char *value = strtok(buffer, ",");
        while (value != NULL)
        {
            // Process the value (e.g., print it to the screen)
            printf("%s ", value);

            // Get the next value
            value = strtok(NULL, ",");
        }
        printf("\n");
    }

    // Close the file
    fclose(fp);
}
//------------------------------------------------------------
void createLinkedListFromCSV(const char *filename, Kitap **kitapListesi, Yazar **yazarListesi, Ogrenci **ogrenciListesi)
{
    // Open the file
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Error: Could not open file '%s'\n", filename);
        return;
    }

    KitapOrnek *kitapOrnekListesi = NULL;
    int kitapAdet = 0, kitapIter = 0;

    // Read the file line by line
    char line[1024];
    while (fgets(line, sizeof(line), fp))
    {
        // Remove the trailing newline character
        int len = strlen(line);
        if (line[len - 1] == '\n')
            line[len - 1] = '\0';

        // Split the line into tokens
        char *tokens[4];
        int i = 0;
        char *token = strtok(line, ",");
        while (token != NULL)
        {
            tokens[i] = token;
            i++;
            token = strtok(NULL, ",");
        }

        // Determine the type of record and add it to the appropriate linked list
        if (strcmp(filename, "Kitaplar.csv") == 0)
        {

            if (kitapIter == 0)
            {
                kitapAdet = atoi(tokens[2]);
                // Add a book to the linked list
                kitapEkle(kitapListesi, tokens[1], tokens[0], atoi(tokens[2]), &kitapOrnekListesi);

                kitapIter++;
            }
            else if (kitapIter == kitapAdet)
            {
                kitapOrnekEkle(&kitapOrnekListesi, tokens[0], tokens[1]);

                kitapOrnekListesi = NULL;

                kitapIter = 0;
            }
            else
            {
                // Add a book copy to the linked list
                kitapOrnekEkle(&kitapOrnekListesi, tokens[0], tokens[1]);
                kitapIter++;
            }
        }
        else if (strcmp(filename, "Yazarlar.csv") == 0)
        {
            // Add an author to the linked list
            yazarEkle(yazarListesi, tokens[1], tokens[2]);
        }
        else if (strcmp(filename, "Ogrenciler.csv") == 0)
        {
            // Add a student to the linked list
            ogrenciEkle(ogrenciListesi, tokens[1], tokens[2], atoi(tokens[3]), tokens[0]);
        }
    }

    // Close the file
    fclose(fp);
}
//------------------------------------------------------------
// Function to append data to a CSV file
void appendCSV(const char *filename, const char *data)
{
    // Open the CSV file in append mode
    FILE *fp = fopen(filename, "a");
    if (fp == NULL)
    {
        fprintf(stderr, "Error: Could not open file '%s'\n", filename);
        return;
    }

    // Write the new entry to the file
    fprintf(fp, "%s\n", data);

    // Close the file
    fclose(fp);
}
//------------------------------------------------------------
// Function to write data to a CSV file
void writeCSV(const char *filename, Kitap **kitapListesi, Yazar **yazarListesi, Ogrenci **ogrenciListesi)
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        fprintf(stderr, "Error: Could not open file '%s' for writing\n", filename);
        return;
    }
    // Determine the type of record based on the filename
    if (strcmp(filename, "Kitaplar.csv") == 0)
    {
        // Write the contents of the book linked list to the file
        Kitap *kitap = *kitapListesi;
        while (kitap != NULL)
        {
            fprintf(fp, "%s,%s,%d\n", kitap->ISBN, kitap->kitapAdi, kitap->adet);
            kitap = kitap->next;

            // KitapOrnek *kitapOrnek = kitap->head;
            // printf("%s", kitapOrnek->EtiketNo);

            /*
            while (kitapOrnek != NULL)
            {
                // fprintf(fp, "%s,%s,%d\n", kitapOrnek->EtiketNo, kitapOrnek->Durum, 0);
                printf("%s,%s,%d\n", kitapOrnek->EtiketNo, kitapOrnek->Durum, 0);
                kitapOrnek = kitapOrnek->next;
            }
            */

            // fprintf(fp, "%s,%s,%d\n", kitap->head->EtiketNo, kitap->head->Durum, 0);
        }

        // Close the file
        fclose(fp);
    }
    else if (strcmp(filename, "Yazarlar.csv") == 0)
    {
        // Write the contents of the author linked list to the file
        Yazar *yazar = *yazarListesi;
        while (yazar != NULL)
        {
            fprintf(fp, "%d,%s,%s\n", yazar->yazarID, yazar->yazarAd, yazar->yazarSoyad);
            yazar = yazar->next;
        }

        // Close the file
        fclose(fp);
    }
    else if (strcmp(filename, "Ogrenciler.csv") == 0)
    {
        // Write the contents of the student linked list to the file
        Ogrenci *ogrenci = *ogrenciListesi;
        while (ogrenci != NULL)
        {
            fprintf(fp, "%s,%s,%s,%d\n", ogrenci->ogrID, ogrenci->ad, ogrenci->soyad, ogrenci->puan);
            ogrenci = ogrenci->next;
        }

        // Close the file
        fclose(fp);
    }
}
#pragma endregion DosyalamaFonksiyonlari
//**********************************************   MENÜ FONKSIYONLARI   *************************************************
#pragma region MenuFonksiyonlari
//------------------------------------------------------------
void studentMenu(Ogrenci *ogrenciListesi)
{
    // Student operations menu
    dbgPrint("*** STUDENT OPERATIONS ***\n");
    printf("1. Add student\n");
    printf("2. Delete student\n");
    printf("3. Edit student\n");
    printf("4. View student information\n");
    printf("5. List students who have not returned books\n");
    printf("6. List penalized students\n");
    printf("7. List all students\n");
    printf("8. Check out/return book\n");
    printf("9. Go back\n");
    printf("Enter your choice: ");

    int choice;
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
    {
        // Get student details from user
        char ad[50], soyad[50], no[50];
        int puan = 100;
        printf("Enter student name: ");
        scanf("%s", ad);
        printf("Enter student surname: ");
        scanf("%s", soyad);
        printf("Enter student number: ");
        scanf("%s", no);

        // Add student
        ogrenciEkle(&ogrenciListesi, ad, soyad, puan, no);

        break;
    }
    case 2:
    {
        char no[50];
        // Get student number from user
        printf("Enter student number: ");
        scanf("%s", no);

        // Delete student
        ogrenciSil(ogrenciListesi, no);
        break;
    }
    case 3:
    {
        // Get student details from user
        char ad[50], soyad[50], no[50];
        int puan;
        printf("Enter student name: ");
        scanf("%s", ad);
        printf("Enter student surname: ");
        scanf("%s", soyad);
        printf("Enter student number: ");
        scanf("%s", no);
        printf("Enter student puan: ");
        scanf("%d", &puan);

        // Edit student
        ogrenciDuzenle(ogrenciListesi, no, ad, soyad, puan);
        break;
    }
    case 4:
        // View student information
        break;
    case 5:
        // List students who have not returned books
        break;
    case 6:
        // List penalized students
        break;
    case 7:
    {
        // List all students
        ogrenciListele(ogrenciListesi);
        break;
    }
    case 8:
        // Check out/return book
        break;
    case 9:
        return;
    default:
    {
        printf("Invalid choice.\n");
        break;
    }
    }
}
//------------------------------------------------------------
void bookMenu(Kitap *kitapListesi, Yazar *yazarListesi)
{
    // Book operations menu
    dbgPrint("*** BOOK OPERATIONS ***");
    printf("1. Add book\n");
    printf("2. Delete book\n");
    printf("3. Edit book\n");
    printf("4. Kitap-Yazar Eşleştir\n");
    printf("5. List all books\n");
    printf("6. Go back\n");
    printf("Enter your choice: ");

    int choice;
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
    {
        char ad[50], ISBN[50];
        int adet;

        printf("Enter book name: ");
        scanf("%s", ad);
        printf("Enter book ISBN: ");
        scanf("%s", ISBN);
        printf("Enter number of the book: ");
        scanf("%d", &adet);

        KitapOrnek *kitapOrnekListesi = NULL;

        kitapEkle(&kitapListesi, ad, ISBN, adet, &kitapOrnekListesi);

        dbgPrint("Kitap eklendi.\n");

        int iterationKitapOrnekleri = 1;

        for (; iterationKitapOrnekleri <= adet; iterationKitapOrnekleri++)
        {
            char newISBN[50] = "";
            strcpy(newISBN, ISBN);
            strcat(newISBN, "_");

            sprintf(newISBN, "%s%d", newISBN, iterationKitapOrnekleri);

            kitapOrnekEkle(&kitapOrnekListesi, newISBN, "0");

            printf("\n%s\n", kitapOrnekListesi->EtiketNo);
        }

        break;
    }
    case 2:
    {
        char ISBN[50];

        printf("Enter author number: ");
        scanf("%d", &ISBN);
        kitapSil(kitapListesi, ISBN);
        break;
    }

    case 3:
    {
        char ad[50], ISBN[50];
        int adet;

        printf("Enter book name: ");
        scanf("%s", ad);
        printf("Enter book ISBN: ");
        scanf("%s", ISBN);
        printf("Enter number of the book: ");
        scanf("%d", &adet);

        kitapDuzenle(kitapListesi, ad, ISBN, adet);
        break;
    }
    case 4:
    {
        KitapYazar *kitapYazar = NULL;

        printf("Eşleştirmek istediğiniz kitap ISBN'sini giriniz: ");
        scanf("%s", kitapYazar->ISBN);

        printf("Eşleştirmek istediğiniz yazar numarasını giriniz: ");
        scanf("%d", kitapYazar->YazarID);

        kitapYazarEslestir(&kitapListesi, &yazarListesi, kitapYazar);
        break;
    }

    case 5:
    {
        kitapListele(kitapListesi);
        break;
    }
    case 6:
        return;
    default:
        printf("Invalid choice.\n");
        break;
    }
}
//------------------------------------------------------------
void authorMenu(Yazar *yazarListesi)
{
    // Author operations menu
    dbgPrint("*** AUTHOR OPERATIONS ***\n");
    printf("1. Add author\n");
    printf("2. Delete author\n");
    printf("3. Edit author\n");
    printf("4. View author information\n");
    printf("5. List all authors\n");
    printf("6. Go back\n");
    printf("Enter your choice: ");

    int choice;
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
    {
        char ad[50], soyad[50];
        printf("Enter author name: ");
        scanf("%s", ad);
        printf("Enter author surname: ");
        scanf("%s", soyad);

        yazarEkle(&yazarListesi, ad, soyad);
        break;
    }
    case 2:
    {
        int id;
        printf("Enter author ID: ");
        scanf("%d", &id);
        yazarSil(yazarListesi, id);
        break;
    }
    case 3:
    {
        char ad[50], soyad[50];
        int id;
        printf("Enter author name: ");
        scanf("%s", ad);
        printf("Enter author surname: ");
        scanf("%s", soyad);
        printf("Enter author ID: ");
        scanf("%d", &id);

        yazarDuzenle(yazarListesi, id, ad, soyad);
        break;
    }
    case 4:
        // View author information function here
        break;
    case 5:
        yazarListele(yazarListesi);
        break;
    case 6:
        return;
    default:
        printf("Invalid choice.\n");
        break;
    }
}
//------------------------------------------------------------
void mainMenu()
{
    Yazar *yazarListesi = NULL;
    Kitap *kitapListesi = NULL;
    Ogrenci *ogrenciListesi = NULL;

    createLinkedListFromCSV("Kitaplar.csv", &kitapListesi, NULL, NULL);
    createLinkedListFromCSV("Yazarlar.csv", NULL, &yazarListesi, NULL);
    createLinkedListFromCSV("Ogrenciler.csv", NULL, NULL, &ogrenciListesi);

    while (1)
    {
        dbgPrint("*** LIBRARY MANAGEMENT SYSTEM ***\n");
        printf("1. Student operations\n");
        printf("2. Book operations\n");
        printf("3. Author operations\n");
        printf("4. Quit\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            studentMenu(ogrenciListesi);
            writeCSV("Ogrenciler.csv", NULL, NULL, &ogrenciListesi);
            break;
        }
        case 2:
            bookMenu(kitapListesi, yazarListesi);
            writeCSV("Kitaplar.csv", &kitapListesi, NULL, NULL);
            break;
        case 3:
            authorMenu(yazarListesi);
            writeCSV("Yazarlar.csv", NULL, &yazarListesi, NULL);
            break;
        case 4:
        {
            dbgPrint("Are you sure you want to quit? (1/0):");
            int quit;
            scanf("%d", &quit);
            if (quit == 1)
            {
                return;
            }
        }

        default:
            printf("Invalid choice.\n");
            break;
        }
    }
}
#pragma endregion MenuFonksiyonlari
//**********************************************   MAIN   ***************************************************************
int main()
{

    mainMenu();

    return 0;
}

/*
Proje Kazanımlarım:
1. Veri yapıları ve algoritmaları kullanarak, ilişkisel veri tabanı yönetim sistemlerini tasarlayabilir seviyeye geldim.
2.Structure yapılarını öğrendim ve uygulama fırsatı buldum.
3.Structure'lar üzerinden oluşturulan linkli liste veri yapısını öğrendim ve kullandım. Bunları iç içe kullanarak daha karmaşık veri yapıları oluşturmayı öğrendim.
4.İlişkisel veri tabanı yönetim sistemlerindeki veri tabanı işlemlerini (CRUD) gerçekleştirebilecek seviyeye geldim.
5.Yapısal programlama konseptlerini anlama ve kontrol etme becerilerim gelişti.
6.Proje sürecinde, dosya işlemlerinin genel mantığını kavradım ve bunları kullanarak dosyalar aracılığıyla veri saklama, okuma ve yazma işlemlerini gerçekleştirmeyi öğrendim. Ayrıca, dosya işlemlerinin güvenliği konusunda bilgi sahibi oldum ve dosya işlemleri sırasında oluşabilecek hataları önleyici önlemler almayı öğrendim.
7.Kütüphane yönetim sistemi projesi sürecinde, kod yazma standartlarını ve dokümantasyonu önemsemeyi öğrendim. Bu sayede kodlarımın anlaşılır ve okunaklı olmasını sağladım. Ayrıca proje sürecinde oluşturduğum dokümantasyon sayesinde proje hakkında detaylı bilgi edinme imkanı buldum ve proje içerisinde yer alan çalışmaları daha kolay takip etme olanağına sahip oldum. Böylece proje geliştirme sürecinde daha etkin bir şekilde çalışma imkanı buldum ve proje bütünlüğünü koruma imkanı elde ettim.
*/
