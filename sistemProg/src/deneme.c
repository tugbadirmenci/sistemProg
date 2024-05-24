#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "fields.h"
#include "jval.h"
#include "dllist.h"

#define MAX_BUFFER 1024

void islemYaz(char *buffer, int *cursor, char karakter, int adet) {
    for (int i = 0; i < adet; i++) {
        buffer[(*cursor)++] = karakter;
    }
}

void islemSil(char *buffer, int *cursor, char karakter, int adet) {
    int index = *cursor - 1;
    while (index >= 0 && adet > 0) {
        if (buffer[index] == karakter) {
            memmove(&buffer[index], &buffer[index + 1], *cursor - index);
            (*cursor)--;
            adet--;
        }
        index--;
    }
}

void islemSonagit(char *buffer, int *cursor) {
    while (buffer[*cursor] != '\0') {
        (*cursor)++;
    }
}

void islemDur(FILE *dosya, const char *buffer, int cursor) {
    fwrite(buffer, sizeof(char), cursor, dosya);
}

int main() {
    char girisDosyaAdi[256];
    char cikisDosyaAdi[256];
    char buffer[MAX_BUFFER] = {0};
    int cursor = 0;

    printf("Giriş dosyasının adını giriniz: ");
    scanf("%255s", girisDosyaAdi);
    printf("Çıkış dosyasının adını giriniz: ");
    scanf("%255s", cikisDosyaAdi);

    FILE *girisDosya = fopen(girisDosyaAdi, "r");
    FILE *cikisDosya = fopen(cikisDosyaAdi, "w");

    if (!girisDosya || !cikisDosya) {
        fprintf(stderr, "Dosya açılamadı.\n");
        return 1;
    }

    char komut[10];
    char karakter;
    int adet;

    while (!feof(girisDosya)) {
        if (fscanf(girisDosya, "%s", komut) != 1) break;

        if (strcmp(komut, "yaz:") == 0) {
            while (fscanf(girisDosya, "%d %c", &adet, &karakter) == 2) {
                if (karakter == '\\') {
                    fscanf(girisDosya, "%c", &karakter);
                    if (karakter == 'b') karakter = ' ';
                    else if (karakter == 'n') karakter = '\n';
                }
                islemYaz(buffer, &cursor, karakter, adet);
            }
        } else if (strcmp(komut, "sil:") == 0) {
            fscanf(girisDosya, "%d %c", &adet, &karakter);
            islemSil(buffer, &cursor, karakter, adet);
        } else if (strcmp(komut, "sonagit:") == 0) {
            islemSonagit(buffer, &cursor);
        } else if (strcmp(komut, "dur:") == 0) {
            islemDur(cikisDosya, buffer, cursor);
            break; // Programdan çık
        }
    }

    fclose(girisDosya);
    fclose(cikisDosya);

    // Çıkış dosyasının içeriğini terminale yazdırma
    cikisDosya = fopen(cikisDosyaAdi, "r");
    if (!cikisDosya) {
        fprintf(stderr, "Çıkış dosyası okunamadı.\n");
        return 1;
    }

    char ch;
    while ((ch = fgetc(cikisDosya)) != EOF) {
        putchar(ch);
    }

    fclose(cikisDosya);
    return 0;
}
