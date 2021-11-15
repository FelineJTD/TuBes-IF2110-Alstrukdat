// Feli
#include "command.h"
#include "../fungsi/gameStateInput.h"
#include <stdio.h>
#include "../fungsi/getLoc.h"

void command_DROP_OFF(gameState* status){
    /* KAMUS LOKAL */
    Address p;
    paket paket;
    char currLoc;
    boolean found;
    int uang;
    /* ALGORITMA */
    currLoc = getLoc(status->myLoc, status->buildings);
    paket = status->tas.buffer[status->tas.idxTop];
    if (paket.dropoff == currLoc) {
        if (paket.item == 'N') {
            uang = 200;
        } else if (paket.item == 'H') {
            uang = 400;
        } else if (paket.item == 'P') {
            uang = 400;
        }
        popBag(&(status->tas), &paket);
        deleteFirstInProgressList(&(status->inProgress), &paket);
        status->money += uang;
        printf("Pesanan %c Item berhasil diantarkan!\n", paket.item);
        printf("Uang yang didapatkan: %d Yen\n", uang);
    } else {
        printf("Tidak ada pesanan yang dapat diantarkan!\n");
    }
}