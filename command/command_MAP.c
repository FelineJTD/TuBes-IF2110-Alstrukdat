//jef
#include "command.h"

#include "../ADT/boolean.h"
#include "../ADT/nodePaket/nodePaket.h"

#include "../pcolor/pcolor.h"

#include <stdio.h>

//FUNGSI ATAU PROSEDUR TAMBAHAN
char isThereBuildingInThisLoc(buildingList bl, int B, int K){
//mengembalikan char building jika building exist. mengembalikan '0' jika tidak ada.
//HQ tidak termasuk (jika yg diinputkan x y itu HQ, return 0)
    for(int i = 0; i < bl.nEff;i++){
        // printf("testing %d (%d,%d) dengan (%d,%d)\n", i, bl.buffer[i].loc.X, bl.buffer[i].loc.Y, x,y);
        if(bl.buffer[i].loc.X == B && bl.buffer[i].loc.Y == K){
            return bl.buffer[i].name;
        }
    }
    return '0';
}

int cekLokasiKhusus(gameState status, char b, char m){
    // m stands for myloc, b for building
    //cek apakah b ada di pick up atau destination, atau bisa dicapai
    //respectively, 1 2 3. kalo bukan ketiganya, 0
    //sadari kalo ini gk ngecover 'drop off sekaligus pickup'.
    // sementara urutan prioritasnya pickup, destination, bisa dicapai
    //cek pick up dari todo

    Address walker = status.todos;
    while(!isTodoListEmpty(walker)){
        if(walker->info.pickup == b){
            return 1;
        }
        walker = (*walker).next;
    }
    //cek drop off dari top of bag
    if(!isBagEmpty(status.tas)){
        int i = status.tas.idxTop;
        if(status.tas.buffer[i].dropoff == b){
            return 2;
        }
    }
    //cek bisa dicapai dari nearbuilding
    int i = m - 'A' + 1;
    //jika m = 'A', i = 1
    //jika m = 'C', i = 3
    //dst
    int j = b - 'A' + 1;

    //kondisi khusus
    if(status.myLoc.X == status.hq.X && status.myLoc.Y == status.hq.Y){
        i = 0;
    }
    if(status.bangunanSekitar.contents[i][j] == 1){
        return 3;
    }
    //jika program sampe sini, artinya building tersebut bukan salah satu dari ketiga opsi diatas. return 0
    return 0;
     
}

//FUNGSI ATAU PROSEDUR UTAMA
void command_MAP(gameState status){
    //KAMUS
    int baris = status.mapHeight;
    int kolom = status.mapWidth;
    char namaB = '0';
    int AngkaKhusus = 0;
    //ALGORITMA
    //coba color
    // print_red('R');
    // print_green('G');
    // print_magenta('M');
    // print_cyan('C');
    // print_yellow('Y');
    // print_blue('B');
    // printf("\n");
    // printf("HQ(%d,%d)\n", status.hq.X,status.hq.Y);
    
    //cari nama building myLoc dulu
    char namaMyLoc = isThereBuildingInThisLoc(status.buildings,status.myLoc.X,status.myLoc.Y);
    // printf("Myloc %c(%d,%d)\n", namaMyLoc, status.myLoc.X,status.myLoc.Y);
    //print bintang awal
    for(int loop = 1;loop <= kolom+2;loop++){
        printf("*");
    }
    printf("\n");
    for(int b = 1; b<= baris;b++){
        printf("*");
        for(int k = 1; k <= kolom;k++){
            //yang akan dicek(terurut), HQ, lokasi mobita, bukan building, building
            namaB = isThereBuildingInThisLoc(status.buildings,b,k); 
            
            if(status.hq.X == b && status.hq.Y == k){
                if(status.hq.X == status.myLoc.X && status.hq.Y == status.myLoc.Y){
                    //print HQ kuning(harusnya kuning itu myloc, dikasus ini, tapi HQ = myLoc)
                    print_yellow('8');
                    // printf("8");
                }
                //if HQ itu bisa dalam jangkauan destinasi myloc, 
                //myloc pasti bukan HQ, karena sudah ke catch diatas
                else if(status.bangunanSekitar.contents[namaMyLoc - 'A' + 1][0]){
                    //ijo
                    print_green('8');
                    // printf("8");
                }
                else{
                    //print HQ biasa(item)
                    printf("8");
                }
            }
            else if(status.myLoc.X == b && status.myLoc.Y == k){
                //print kuning
                // printf("myloc\n");
                print_yellow(namaMyLoc); 
                // printf("%c", namaMyLoc);
            }
            else if(namaB == '0'){
                printf(" ");
            }
            else{
                //kondisi : Building pasti memiliki nama, building bukan HQ dan bukan myLoc
                //cek apakah namaB ada di pick up, destination drop off, atau bisa dicapai
                //respectively, 1 2 3. kalo bukan ketiganya, 0
                AngkaKhusus = cekLokasiKhusus(status,namaB,namaMyLoc);
                if(AngkaKhusus == 1){
                    print_red(namaB);
                    // printf("%c", namaB);
                }
                else if(AngkaKhusus == 2){
                    print_blue(namaB);
                    // printf("%c", namaB);
                }
                else if(AngkaKhusus == 3){
                    print_green(namaB);
                    // printf("%c", namaB);
                }
                else{
                    printf("%c",namaB);
                }
            }
        }
        printf("*\n");
    }
    //print bintang akhir
    for(int loop = 1;loop <= kolom+2;loop++){
        printf("*");
    }
    printf("\n");
}