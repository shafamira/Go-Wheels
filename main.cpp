#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Prototypes
void registration();
void login();
void mainMenu();
void infoCar();
void sortPrice(struct Car *data, int len);
void displayJudul();
void displayAll();
int displaySorted(int choice);
void carRequest();
void displayReq();
void carBooking();
void goWheelsArt();
void displayExitArt();
int noBooking(int n);
// Struct
struct User{
    char username[50];
    char password[50];
    int money;
};

struct typeCar{
    char nameCar[50];
    int yearProduction; 
    int price;
    int kilometers;
    double rate;
    char reasons[100];
};

struct Car{
    char brandCar[100];
    struct typeCar tc;
}cars[9000];

struct AdminDetails{
	char nameCar[50];
	int Duration;
	char Driver[4];
};

struct Admin{
	char Name[255];
	char Address[255];
	long int PhoneNum;
  struct AdminDetails pc;
};

int main(){
    goWheelsArt();
    int ch;
    Logout:
    // Main Menu
    puts("\n\t[1]> Car Info View"); 
    puts("\t[2]> Car Request"); 
    puts("\t[3]> Car Booking\n\n");
    puts("\t[0]> Logout\n");
    printf(" >> "); scanf("%d", &ch); 
    fflush(stdin);

    while(1){
        if(ch==0){
            displayExitArt();
            puts("");
            break;
        } else if (ch==2){
            carRequest();
            goto Logout;
            break;
        } else if (ch==3){
            carBooking();
            break;
        } else if (ch==1){
            infoCar();
            goto Logout;
            break;
        }
    }
}

// function apabila user milih (1) di main menu
void infoCar(){
    fflush(stdin);
    puts("\t+---------------+");
    puts("\t| Car Info View |");
    puts("\t+---------------+\n");

    displayAll();

    int cho;
    puts("\t[1]> Sort by Price");
    puts("\t[2]> Sort by Year of Production\n");
    puts("\t[0]> Go Back");
    printf(" >> "); scanf("%d", &cho);

    while(1){
        if(cho == 0){
            main();
            break;
        } else if (cho == 1) {
            int cp;
            puts("\t+---------------+");
            puts("\t| Sort by Price |");
            puts("\t+---------------+\n");
            puts("\t[1]> Low-High\n\t[2]> High-Low\n");
            puts("\t[0]> Go Back");
            printf(" >> "); scanf("%d", &cp);

            if(cp==1){
                displaySorted(0);
                break;
            } else if (cp==2){
                displaySorted(1);
                break;
            } else if (cp==0){
                infoCar();
                break;
            }
        } else if (cho == 2){
            int cy;
            puts("\t+----------------------------+");
            puts("\t| Sort by Year of Production |");
            puts("\t+----------------------------+\n");
            puts("\t[1]> Old-New\n\t[2]> New-Old\n");
            puts("\t[0]> Go Back");
            printf(" >> "); scanf("%d", &cy);

            if(cy==1){

            } else if (cy==2){

            }
        }
    }
}

// sort berdasarkan price pake buble sort
void sortPrice(struct Car *data, int len){
    for(int i=0; i<len; i++){
        for(int j=0; j<len-1-i; j++){
            if(data[j].tc.price >= data[j+1].tc.price){
                struct Car temp;
                temp = data[j];
                data[j] = data[j+1];
                data[j+1] = temp;
            }
        }
    }
}

// function utk display judul di tabel
void displayJudul(){
    puts("\t+-----------------------------------------------------------------------------+");
    puts("\t| Brand          | Rate   | Name          | Year of Production | Price (/day) |");
    puts("\t+-----------------------------------------------------------------------------+");
}

// function utk display tabel berdasarkan file carList.txt tanpa dimanipulasi
void displayAll(){
    int i = 0, j;
    FILE *fp = fopen("./database/carList.txt", "r");
    while(fscanf(fp, "%[^#]#%lf#%[^#]#%d#%d\n", cars[i].brandCar, &cars[i].tc.rate, cars[i].tc.nameCar, &cars[i].tc.yearProduction, &cars[i].tc.price) != EOF){
        i++;
    }
    fclose(fp);

    displayJudul();
        for (int j = 0; j < i; j++){
            printf("\t| %-15s| %-6.2lf | %-13s | %-18d | %-12d |\n", cars[j].brandCar, cars[j].tc.rate, cars[j].tc.nameCar, cars[j].tc.yearProduction, cars[j].tc.price);
        }
    puts("\t+-----------------------------------------------------------------------------+\n");
}

// utk display tabel yg udah di-sorting
int displaySorted(int choice){
    fflush(stdin);
    // 1 -> sortP (Low-High)
    // 2 -> sortP (High-Low)
    // 3 -> sortY (Old-New)
    // 4 -> sortY (New-Old)

    int i = 0, j;
    FILE *fp = fopen("./database/carList.txt", "r");
    while(fscanf(fp, "%[^#]#%lf#%[^#]#%d#%d\n", cars[i].brandCar, &cars[i].tc.rate, cars[i].tc.nameCar, &cars[i].tc.yearProduction, &cars[i].tc.price) != EOF){
        i++;
    }
    fclose(fp);

    if(choice==0){
        sortPrice(cars, i);
        displayJudul();
        for (int j = 0; j < i; j++){
            printf("\t| %-15s| %-6.2lf | %-13s | %-18d | %-12d |\n", cars[j].brandCar, cars[j].tc.rate, cars[j].tc.nameCar, cars[j].tc.yearProduction, cars[j].tc.price);
        }
        puts("\t+-----------------------------------------------------------------------------+\n");
    } else if(choice==1){ 
        sortPrice(cars, i);
        displayJudul();
        for(int j = i-1; j>=0; j--){
            printf("\t| %-15s| %-6.2lf | %-13s | %-18d | %-12d |\n", cars[j].brandCar, cars[j].tc.rate, cars[j].tc.nameCar, cars[j].tc.yearProduction, cars[j].tc.price);
        }
        puts("\t+-----------------------------------------------------------------------------+\n");
    } else if (choice==3){

    } else if (choice==4){

    }
    return i;
}

// function apabila user milih (2) di main menu
void carRequest(){
    puts("\t+-------------+");
    puts("\t| Car Request |");
    puts("\t+-------------+\n");

    displayReq();

    int choice;
    printf("\t[1]> Add Car Request\n");
    printf("\t[2]> Remove Car Request\n\n");
    printf(" >> "); scanf("%d", &choice); fflush(stdin);

    if(choice==1){
        // Add Car Request
        printf("\tCar Brand\t\t: "); scanf("%[^\n]", cars->brandCar); 
        printf("\tRate Car\t\t: "); getchar(); scanf("%lf", &cars->tc.rate); 
        printf("\tCar Name\t\t: "); getchar(); scanf("%[^\n]", cars->tc.nameCar); 
        printf("\tYear of Production\t: " ); getchar(); scanf("%d", &cars->tc.yearProduction);
        printf("\tPrice Request (/day)\t: "); getchar(); scanf("%d", &cars->tc.price);
        printf("\n\tAnd lastly, please write down your reasons for requesting that car\n");
        printf("\tbecause your reasons can be a consideration for us\n");
        printf("\t>> "); getchar(); scanf("%[^\n]", cars->tc.reasons); 

        FILE *fr = fopen("./database/reasonsList.txt", "a");
        fprintf(fr, "%s#%s\n", cars->tc.nameCar, cars->tc.reasons);
        fclose(fr);

        FILE *fp = fopen("./database/reqList.txt", "a");
        fprintf(fp,"%s#%.2lf#%s#%d#%d\n", cars->brandCar, cars->tc.rate, cars->tc.nameCar, cars->tc.yearProduction, cars->tc.price);
        fclose(fp);

        printf("\n");
        displayReq();

    } else if (choice==2){
        // // Remove Car Request
        puts("\tStill on Progress...");
    }
}

// utk display tabel car request dari file reqList.txt
void displayReq(){
    int i = 0, j;
    FILE *fa = fopen("./database/reqList.txt", "r");
    while(fscanf(fa, "%[^#]#%lf#%[^#]#%d#%d\n", cars[i].brandCar, &cars[i].tc.rate, cars[i].tc.nameCar, &cars[i].tc.yearProduction, &cars[i].tc.price) != EOF){
        i++;
    }
    fclose(fa);
    displayJudul();
    for(int j = 0; j < i; j++){
        printf("\t| %-15s| %-6.2lf | %-13s | %-18d | %-12d |\n", cars[j].brandCar, cars[j].tc.rate, cars[j].tc.nameCar, cars[j].tc.yearProduction, cars[j].tc.price);
    }
    puts("\t+-----------------------------------------------------------------------------+\n");
}
//function untuk mendapatkan no booking
int noBooking(int n){
  int number[10];
  FILE *fb = fopen("./database/noBooking.txt","r");
  int i = 0;
  while(fscanf(fb,"%d",&number[i]) != EOF){
    i++;
  }
  return number[n];
}
// function apabila user milih (3) di main menu
void carBooking(){
    profile:
    puts("\t+-------------+");
    puts("\t| Car Booking |");
    puts("\t+-------------+\n");

    //scan file carlist.txt untuk menentukan harga rental mobil
    FILE *fp = fopen("./database/carList.txt","r");
    int i=0;
    while(fscanf(fp,"%[^#]#%lf#%[^#]#%d#%d",cars[i].brandCar,&cars[i].tc.rate,
        cars[i].tc.nameCar,&cars[i].tc.yearProduction,&cars[i].tc.price) != EOF){
            i++;
    }

    //biodata user
    struct Admin infoPelanggan;
    puts("\tPlease fill Your Biodata");
    printf("\tName\t\t : "); scanf(" %[^\n]",infoPelanggan.Name);
    printf("\tAddress\t\t : "); scanf(" %[^\n]",infoPelanggan.Address);getchar();
    printf("\tPhone Number\t : "); scanf("%ld",&infoPelanggan.PhoneNum);getchar();
    puts("\n\tFill in the information below to continue booking your car rental");
    name:
    printf("\tCar Name\t\t: "); scanf(" %[^\n]",infoPelanggan.pc.nameCar);
    int name = 0;
    for(int j=0;j<=i;j++){
        if(strcmp(infoPelanggan.pc.nameCar ,cars[j].tc.nameCar) == 0)
          name++;
    }
    if(name == 0){
      printf("\n\tCar Not Found! Please Try Again\n\n");
      goto name;
    }
    printf("\tRent Duration (/day)\t: "); scanf("%d",&infoPelanggan.pc.Duration); getchar();
    printf("\tHire Driver (Yes/No)\t: "); scanf(" %[^\n]",infoPelanggan.pc.Driver); getchar();

    //searching mobil & harga
    long int harga = 0;
    for(int j=0;j<=i;j++){
        if(strcmp(infoPelanggan.pc.nameCar , cars[j].tc.nameCar) == 0){
            harga =  infoPelanggan.pc.Duration * cars[j].tc.price;
        }
    }

    // menetukan harga sopir
    if(strcmp(infoPelanggan.pc.Driver,"Yes") == 0){
        harga = harga + 50000 * infoPelanggan.pc.Duration;
    }

    //harga akhir
    printf("\tTotal Price\t\t: %ld\n",harga);
    int uangMuka = harga*0.4;
    printf("\tDown payment\t\t: %d\n",uangMuka);

    char question;
    printf("\n\tAre you sure with this information? (Y/N) "); scanf("%c",&question); getchar();

    int bookNumber = uangMuka % 9;
    int number = noBooking(bookNumber);
    if(question == 'Y' || question == 'y'){
        printf("\t_________________________________________________________________________________________\n\n");
        printf("\tNo Booking    : %d\n",number);
        printf("\tName          : %s\n",infoPelanggan.Name);
        printf("\tAddress       : %s\n", infoPelanggan.Address);
        printf("\tPhone number  : %ld\n", infoPelanggan.PhoneNum);
        printf("\tCar Name      : %s\n", infoPelanggan.pc.nameCar);
        printf("\tRent Duration : %d day\n", infoPelanggan.pc.Duration);
        printf("\tDriver        : %s\n", infoPelanggan.pc.Driver);
        printf("\tTotal Price   : %ld\n",harga);
        printf("\tDown payment  : %d\n",uangMuka);
        printf("\n\tPlease pay your down payment first and you can take the car at Go-Wheels Rent Car nearby\n");
        printf("\t=========================================================================================\n");        
        displayExitArt();
    } else if (question == 'N'|| question == 'n'){
        printf("\n") ;
        goto profile;
    }
}

// ASCII ART
void goWheelsArt(){
    FILE *fwa = fopen("./assets/gwArt.txt", "r");
    char wArt[500];
    while (fscanf(fwa, "%[^\n]", wArt) != EOF){
        fgetc(fwa);
        printf("%s\n", wArt);
    }
    fclose(fwa);
}

void displayExitArt(){
    FILE *fea = fopen("./assets/thankYou.txt", "r");
    char eArt[500];
    while (fscanf(fea, "%[^\n]", eArt) != EOF){
        fgetc(fea);
        printf("%s\n", eArt);
    }
    fclose(fea);
}