// NIM : 13520055
// Nama : Christopher Jeffrey
// Tanggal : 15 September 2021
// Topik praktikum : list dinamik explisit
// Deskripsi : pra prak empat
#include "boolean.h"
#include "listdin.h"
#include<stdio.h>
#include<stdlib.h>
/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create list kosong  */
void CreateListDin(ListDin *l, int capacity){
    CAPACITY(*l) = capacity;
    BUFFER(*l) = malloc(sizeof(ElType) * CAPACITY(*l));
    NEFF(*l) = 0;
}
/* I.S. l sembarang, capacity > 0 */
/* F.S. Terbentuk list dinamis l kosong dengan kapasitas capacity */

void dealocate(ListDin *l){
    NEFF(*l) = 0;
    CAPACITY(*l) = 0;
    free(BUFFER(*l));
}
/* I.S. l terdefinisi; */
/* F.S. (l) dikembalikan ke system, CAPACITY(l)=0; NEFF(l)=0 */

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int length(ListDin l){
    return NEFF(l);
}
/* Mengirimkan banyaknya elemen efektif list */
/* Mengirimkan nol jika list l kosong */
/* *** Daya tampung container *** */

/* *** Selektor INDEKS *** */
IdxType getLastIdx(ListDin l){
    return NEFF(l) - 1;
}
/* Prekondisi : List l tidak kosong */
/* Mengirimkan indeks elemen l terakhir */

/* ********** Test Indeks yang valid ********** */
boolean isIdxValid(ListDin l, int i){
    return(i >= 0 && i < CAPACITY(l));
}
/* Mengirimkan true jika i adalah indeks yang valid utk kapasitas list l */
/* yaitu antara indeks yang terdefinisi utk container*/
boolean isIdxEff(ListDin l, IdxType i){
    return (i >= 0 && i < NEFF(l));
}
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk list */
/* yaitu antara 0..NEFF(l) */

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test list kosong *** */
boolean isEmpty(ListDin l){
    boolean is_empty = false;
    if (NEFF(l) == 0)
        is_empty = true;
    return is_empty;
}
/* Mengirimkan true jika list l kosong, mengirimkan false jika tidak */
/* *** Test list penuh *** */
boolean isFull(ListDin l){
    boolean is_full = false;
    if (NEFF(l) == CAPACITY(l))
        is_full = true;
    return is_full;
}
/* Mengirimkan true jika list l penuh, mengirimkan false jika tidak */

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi list dari pembacaan *** */
void readList(ListDin *l){
    int N = -1;
    while(N < 0 || N > CAPACITY(*l)){
        scanf("%d", &N);
    }
    NEFF(*l) = N;
    for(int b = 0; b< N; b++){
        scanf("%d", &BUFFER(*l)[b]);
    }
}
/* I.S. l sembarang dan sudah dialokasikan sebelumnya */
/* F.S. List l terdefinisi */
/* Proses : membaca banyaknya elemen l dan mengisi nilainya */
/* 1. Baca banyaknya elemen diakhiri enter, misalnya N */
/*    Pembacaan diulangi sampai didapat N yang benar yaitu 0 <= N <= CAPACITY(l) */
/*    Jika N tidak valid, tidak diberikan pesan kesalahan */
/* 2. Jika 0 < N <= CAPACITY(l); Lakukan N kali: Baca elemen mulai dari indeks
      0 satu per satu diakhiri enter */
/*    Jika N = 0; hanya terbentuk l kosong */
void displayList(ListDin l){
    printf("[");
    for(int b = 0;b < NEFF(l);b++){
        printf("%d", BUFFER(l)[b]);
        if(b < NEFF(l) - 1)
            printf(",");
    }
    printf("]");
}
/* Proses : Menuliskan isi list dengan traversal, list ditulis di antara kurung siku;
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. l boleh kosong */
/* F.S. Jika l tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */

/* ********** OPERATOR ARITMATIKA ********** */
/* *** Aritmatika list : Penjumlahan, pengurangan, perkalian, ... *** */
ListDin plusMinusList(ListDin l1, ListDin l2, boolean plus){
    ListDin l;
    CreateListDin(&l, CAPACITY(l1));
    if (plus)
        for(int b = 0; b< NEFF(l1);b++){
            BUFFER(l)[b] = BUFFER(l1)[b] + BUFFER(l2)[b];
        }
    else
        for(int b = 0; b< NEFF(l1);b++){
            BUFFER(l)[b] = BUFFER(l1)[b] - BUFFER(l2)[b];
        }
    NEFF(l) = NEFF(l1);
    return l;
}
/* Prekondisi : l1 dan l2 memiliki Neff sama dan tidak kosong */
/* Jika plus = true, mengirimkan  l1+l2, yaitu setiap elemen l1 dan l2 pada indeks yang sama dijumlahkan */
/* Jika plus = false, mengirimkan l1-l2, yaitu setiap elemen l1 dikurangi elemen l2 pada indeks yang sama */

/* ********** OPERATOR RELASIONAL ********** */
/* *** Operasi pembandingan list : < =, > *** */
boolean isListEqual(ListDin l1, ListDin l2){
    boolean is_equal = true;
    if (NEFF(l1) == NEFF(l2)){
        int b = 0;
        while(b< NEFF(l1) && (is_equal)){
            if (BUFFER(l1)[b] != BUFFER(l2)[b]){
                is_equal = false;
            }
            b++;
        }
    }
    else    
        is_equal = false;
    return is_equal;
    
}
/* Mengirimkan true jika l1 sama dengan l2 yaitu jika nEff l1 = l2 dan semua elemennya sama */

/* ********** SEARCHING ********** */
/* ***  Perhatian : list boleh kosong!! *** */
IdxType indexOf(ListDin l, ElType val){
    IdxType i = 0;
    IdxType result = IDX_UNDEF;
    
    while (i < length(l) && result == IDX_UNDEF){
        if (ELMT(l,i)== val)
            result = i;
        else
            i++;
    }
    
    return result;
}
/* Search apakah ada elemen List l yang bernilai val */
/* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = val */
/* Jika tidak ada, mengirimkan IDX_UNDEF */
/* Menghasilkan indeks tak terdefinisi (IDX_UNDEF) jika List l kosong */
/* Skema Searching yang digunakan bebas */

/* ********** NILAI EKSTREM ********** */
void extremes(ListDin l, ElType *max, ElType *min){
    *min = BUFFER(l)[0];
    *max = BUFFER(l)[0];
    for(int b = 0;b< NEFF(l);b++){
        if (BUFFER(l)[b] > *max){
            *max = BUFFER(l)[b];
        }
        if (BUFFER(l)[b] < *min){
            *min = BUFFER(l)[b];
        }
    }
}
/* I.S. List l tidak kosong */
/* F.S. max berisi nilai maksimum l;
        min berisi nilai minimum l */

/* ********** OPERASI LAIN ********** */
void copyList(ListDin lIn, ListDin *lOut){
    CreateListDin(lOut,CAPACITY(lIn));
    NEFF(*lOut) = NEFF(lIn);
    for(int b = 0;b < NEFF(lIn);b++){
        ELMT(*lOut,b) = ELMT(lIn,b);
    }
}
/* I.S. lIn terdefinisi tidak kosong, lOut sembarang */
/* F.S. lOut berisi salinan dari lIn (identik, nEff dan capacity sama) */
/* Proses : Menyalin isi lIn ke lOut */
ElType sumList(ListDin l){
    int sum = 0;
    for (int b = 0;b< NEFF(l) ;b++){
        sum = sum + BUFFER(l)[b];
    }
    return sum;
}
/* Menghasilkan hasil penjumlahan semua elemen l */
/* Jika l kosong menghasilkan 0 */
int countVal(ListDin l, ElType val){
    int occurance = 0;
    for(int b = 0 ;b< NEFF(l);b++){
        if(BUFFER(l)[b] == val)
            occurance += 1;
    }
    return occurance;
}
/* Menghasilkan berapa banyak kemunculan val di l */
/* Jika l kosong menghasilkan 0 */
boolean isAllEven(ListDin l){
    boolean is_all_even = true;
    int b = 0;
    while(is_all_even && b< NEFF(l)){
        if(BUFFER(l)[b] % 2 != 0)
            is_all_even = false;
        else
            b++;
    }
    return is_all_even;
}
/* Menghailkan true jika semua elemen l genap. l boleh kosong */

/* ********** SORTING ********** */
void sort(ListDin *l, boolean asc){
    boolean changes = true;
    ElType temp;
    if (asc)
        while(changes){
            changes = false;
            for(int b = 1;b<length(*l);b++){
                if(ELMT(*l,b-1) > ELMT(*l, b)){
                    temp = ELMT(*l, b-1);
                    ELMT(*l,b-1) = ELMT(*l, b);
                    ELMT(*l, b) = temp;
                    changes = true;
                }
            }
        }
    else
        while(changes){
            changes = false;
            for(int b = 1;b<length(*l);b++){
                if(ELMT(*l,b-1) < ELMT(*l, b)){
                    temp = ELMT(*l, b-1);
                    ELMT(*l,b-1) = ELMT(*l, b);
                    ELMT(*l, b) = temp;
                    changes = true;
                }
            }
        }
}
/* I.S. l boleh kosong */
/* F.S. Jika asc = true, l terurut membesar */
/*      Jika asc = false, l terurut mengecil */
/* Proses : Mengurutkan l dengan salah satu algoritma sorting,
   algoritma bebas */

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void insertLast(ListDin *l, ElType val){
    BUFFER(*l)[NEFF(*l)] = val;
    NEFF(*l) += 1;
}
/* Proses: Menambahkan val sebagai elemen terakhir list */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen terakhir l yang baru */
/* ********** MENGHAPUS ELEMEN ********** */
void deleteLast(ListDin *l, ElType *val){
    *val = BUFFER(*l)[NEFF(*l) - 1];
    NEFF(*l) -= 1;
}
/* Proses : Menghapus elemen terakhir list */
/* I.S. List tidak kosong */
/* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
/*      Banyaknya elemen list berkurang satu */
/*      List l mungkin menjadi kosong */

/* ********* MENGUBAH UKURAN ARRAY ********* */
void growList(ListDin *l, int num){
    int newcap = CAPACITY(*l) + num;
    ListDin temp;
    copyList(*l, &temp);
    dealocate(l);
    CreateListDin(l, newcap);
        NEFF(*l) = NEFF(temp);
    for (int b = 0; b < NEFF(temp); b++){
        ELMT(*l,b) = ELMT(temp,b);
    }
    dealocate(&temp);
}
/* Proses : Menambahkan capacity l sebanyak num */
/* I.S. List sudah terdefinisi */
/* F.S. Ukuran list bertambah sebanyak num */

void shrinkList(ListDin *l, int num){
    int newcap = CAPACITY(*l) - num;
    ListDin temp;
    copyList(*l, &temp);
    dealocate(l);
    CreateListDin(l, newcap);
    NEFF(*l) = NEFF(temp);
    for (int b = 0; b < NEFF(temp); b++){
        ELMT(*l,b) = ELMT(temp,b);
    }
    dealocate(&temp);
}
/* Proses : Mengurangi capacity sebanyak num */
/* I.S. List sudah terdefinisi, ukuran capacity > num, dan nEff < capacity - num. */
/* F.S. Ukuran list berkurang sebanyak num. */

void compactList(ListDin *l){
    ListDin temp;
    copyList(*l, &temp);
    dealocate(l);
    CreateListDin (&(*l) , NEFF(temp) );
    
    NEFF(*l) = NEFF(temp);
    for (int b = 0; b < NEFF(temp); b++){
        ELMT(*l,b) = ELMT(temp,b);
    }
    dealocate(&temp);
}
/* Proses : Mengurangi capacity sehingga nEff = capacity */
/* I.S. List tidak kosong */
/* F.S. Ukuran nEff = capacity */
