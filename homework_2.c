
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // str fonksiyonları için

#define FILE_NAME "students.dat"

// Öğrenci yapısı tanımı
typedef struct {
    int id;
    char firstName[20];
    char lastName[20];
    float gpa; // Not ortalaması (Grade Point Average)
} Student;

// Fonksiyon prototipleri
void showMenu();
void addStudent();
void updateStudentGPA();
void listStudents();
void deleteStudent();

int main() {
    showMenu();
    return 0;
}

// Ana menüyü gösteren ve seçimleri işleyen fonksiyon
void showMenu() {
    int choice;
    while (1) {
        printf("\n--- Ogrenci Yonetim Sistemi ---\n");
        printf("1 - Ogrenci Ekle\n");
        printf("2 - Ogrenci Not Ortalamasini Guncelle\n");
        printf("3 - Ogrencileri Listele\n");
        printf("4 - Ogrenci Sil\n");
        printf("5 - Cikis\n");

        printf("Seciminizi girin: ");
        scanf("%d", &choice);

        // scanf sonrası kalan newline karakterini temizle

        while (getchar() != '\n'); 

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                updateStudentGPA();
                break;
            case 3:
                listStudents();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                printf("Cikis yapiliyor...\n");
                exit(0);
            default:
                printf("Gecersiz secim. Lutfen tekrar deneyin.\n");
        }
    }
}

// Yeni öğrenci ekleyen fonksiyon
void addStudent() {
    FILE *file = fopen(FILE_NAME, "ab"); // Binary ekleme modunda aç
    if (!file) {
        puts("Dosya acma hatasi!");
        return;
    }

    Student s;

    printf("Ogrenci ID girin: ");
    scanf("%d", &s.id);
    while (getchar() != '\n'); // scanf sonrası kalan newline temizle

    printf("Ogrenci adi girin: ");
    fgets(s.firstName, sizeof(s.firstName), stdin);
    s.firstName[strcspn(s.firstName, "\n")] = 0; // Sondaki newline'ı kaldır

    printf("Ogrenci soyadi girin: ");
    fgets(s.lastName, sizeof(s.lastName), stdin);
    s.lastName[strcspn(s.lastName, "\n")] = 0; // Sondaki newline'ı kaldır

    printf("Ogrenci not ortalamasi girin: ");
    scanf("%f", &s.gpa);
    while (getchar() != '\n'); // scanf sonrası kalan newline temizle

    if (fwrite(&s, sizeof(Student), 1, file) == 1) {
        printf("Ogrenci basariyla eklendi!\n");
    } else {
        printf("Ogrenci eklenirken hata olustu.\n");
    }

    fclose(file);
}

// Öğrenci not ortalamasını güncelleyen fonksiyon
void updateStudentGPA() {
    FILE *file = fopen(FILE_NAME, "rb+"); // Binary okuma/yazma modunda aç
    if (!file) {
        puts("Dosya acma hatasi!"); // perror yerine puts
        return;
    }

    Student s;
    int id_to_update, found = 0;

    printf("Guncellenecek ogrencinin ID'sini girin: ");
    scanf("%d", &id_to_update);
    while (getchar() != '\n'); // scanf sonrası kalan newline temizle

    while (fread(&s, sizeof(Student), 1, file)) {
        if (s.id == id_to_update) {
            found = 1;
            printf("Yeni not ortalamasini girin: ");
            scanf("%f", &s.gpa);
            while (getchar() != '\n'); // scanf sonrası kalan newline temizle

            fseek(file, -sizeof(Student), SEEK_CUR); // Bir önceki kayda geri sar
            if (fwrite(&s, sizeof(Student), 1, file) == 1) {
                printf("Ogrenci not ortalamasi basariyla guncellendi!\n");
            } else {
                printf("Ogrenci guncellenirken hata olustu.\n");
            }
            break; // Güncelleme yapıldı, döngüden çık
        }
    }

    if (!found) {
        printf("Ogrenci bulunamadi.\n");
    }

    fclose(file);
}

// Öğrencileri listeleyen veya belirli bir öğrenciyi arayan fonksiyon
void listStudents() {
    FILE *file = fopen(FILE_NAME, "rb"); // Binary okuma modunda aç
    if (!file) {
        puts("Dosya acma hatasi!");
        return;
    }

    Student s;
    int id_to_search, found_count = 0;

    printf("Aranacak ogrenci ID'sini girin (tumunu listelemek icin 0): ");
    scanf("%d", &id_to_search);
    while (getchar() != '\n'); // scanf sonrası kalan newline temizle

    if (id_to_search == 0) {
        printf("\n--- Tum Ogrenciler ---\n");
        printf("ID   | Ad                 | Soyad              | Not Ort.\n");
        printf("-----|--------------------|--------------------|----------\n");
        while (fread(&s, sizeof(Student), 1, file)) {
            printf("%-4d | %-18s | %-18s | %.2f\n", s.id, s.firstName, s.lastName, s.gpa);
            found_count++;
        }
        if (found_count == 0) {
            printf("Henuz hic ogrenci eklenmemis.\n");
        }
    } else {
        while (fread(&s, sizeof(Student), 1, file)) {
            if (s.id == id_to_search) {
                printf("\n--- Bulunan Ogrenci ---\n");
                printf("ID: %d\nAd: %s\nSoyad: %s\nNot Ortalamasi: %.2f\n", s.id, s.firstName, s.lastName, s.gpa);
                found_count = 1; // Öğrenci bulundu
                break;
            }
        }
        if (found_count == 0) {
            printf("Ogrenci bulunamadi.\n");
        }
    }

    fclose(file);
}

// Öğrenci silen fonksiyon
void deleteStudent() {
    FILE *file = fopen(FILE_NAME, "rb");
    FILE *tempFile = fopen("temp_students.dat", "wb"); // Geçici dosya

    if (!file || !tempFile) {
        puts("Dosya acma hatasi!"); // perror yerine puts
        // Eğer bir dosya açıldıysa kapatmayı unutma
        if (file) fclose(file);
        if (tempFile) fclose(tempFile);
        return;
    }

    Student s;
    int id_to_delete, found = 0;

    printf("Silinecek ogrencinin ID'sini girin: ");
    scanf("%d", &id_to_delete);
    while (getchar() != '\n'); // scanf sonrası kalan newline temizle

    while (fread(&s, sizeof(Student), 1, file)) {
        if (s.id == id_to_delete) {
            found = 1; // Silinecek öğrenci bulundu
            continue;  // Bu kaydı geçici dosyaya yazma
        }
        fwrite(&s, sizeof(Student), 1, tempFile); // Diğer kayıtları yaz
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove(FILE_NAME); // Orijinal dosyayı sil
        rename("temp_students.dat", FILE_NAME); // Geçici dosyayı yeniden adlandır
        printf("Ogrenci basariyla silindi.\n");
    } else {
        remove("temp_students.dat"); // Geçici dosyayı sil (işe yaramadı)
        printf("Ogrenci bulunamadi.\n");
    }
}
