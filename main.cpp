#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include<conio.h>

// Prototypes
void mainMenu();
void infoCar();
void sortPrice(struct Car *, int);
void sortYearProduction(struct Car *, int);
void displayJudul();
void displayAll();
int displaySorted(int);
void carRequest();
void displayReq();
void carBooking(int);
void goWheelsArt();
void displayExitArt();
int noBooking(int);
void rentDate(int, int, int);
void currTime();
void menuBooking();
void login();
void regis();
void adminMenu();
void loginAdmin();
void history();

// Struct
struct UserList{
    char name[15];
    char pass[15];
}user[100];

struct typeCar{
    char nameCar[50];
    int yearProduction; 
    int price;
    int kilometers;
    double rate;
    char reasons[255];
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

struct Date {
    int day;
    int month;
    int year;
    char next;
};

struct Admin{
    char Name[105];
	char Address[105];
	long int PhoneNum;
    struct AdminDetails pc;
    struct Date pd;
};

struct History{
    int tp;
    int tD;
    int dur;
    int no;
    char n[105];
    char al[105];
    long int na;
    char m[105];
    long int t;
    int u;
    int d;
    int i;
    int y;
    char curr[30];
}order[255];

int main(){
    int choose;
    do{
        goWheelsArt();

        printf("\n\t[1]> Login\n");
        printf("\t[2]> Register\n");
        printf("\t[3]> Admin Login\n");
        printf("\t[0]> Exit Program\n\n");
        printf(" >> ");
        scanf("%d",&choose);getchar();
        switch(choose){
            case 1:
                login();
                break;
            case 2:
                char r;
                regis();
                printf("\tPress [Enter] to return ...");
                scanf("%c",r); getchar();
                system("cls");
                break;
            case 0:
                system("cls");
                break;
            case 3:
                loginAdmin();
                break;
            default:
                system("cls");
                break;
        }
    }while(choose != 0);

    return 0;
}

void historyA(){
    FILE *fp1 = fopen("./database/history.txt","r");
    FILE *fp2 = fopen("./database/historyTime.txt","r");
    int i=0;
    // hari,supir,durasi,nobook,nama,alamat,notelp,mobil,totalharga,uangmuka,rentdate
    while(fscanf(fp1,"%d#%d#%d#%d#%[^#]#%[^#]#%d#%[^#]#%d#%d#%d#%d#%d",&order[i].tp,&order[i].tD,&order[i].dur,&order[i].no,order[i].n,
    order[i].al,&order[i].na,order[i].m,&order[i].t,&order[i].u,&order[i].d,&order[i].i,&order[i].y) != EOF){
        i++;
    }
    int j=0;
    //waktu pemesanan
    while(fscanf(fp2,"%[^\n]\n",order[j].curr) != EOF){
        j++;
    }
    int temp = i;
    for(int j=0;j<temp;j++){
        printf("\t__________________________________________________________________________________________\n\n");
        printf("\tNo Booking    : %d",order[j].no);
        printf("%66s\n",order[j].curr);
        printf("\tName          : %s\n",order[j].n);
        printf("\tAddress       : %s\n", order[j].al);
        printf("\tPhone number  : %ld\n", order[j].na);
        printf("\tCar Name      : %s\n", order[j].m);
        rentDate(order[j].d,order[j].i,order[j].y);
        if(order[j].tp == 1){
            printf("\tRent Duration : %d day\n", order[j].dur);
        }else if(order[j].tp == 2){
            printf("\tRent Duration : %d week\n", order[j].dur);
        }
        if(order[j].tD == 1){
            printf("\tDriver        : Yes\n");
        }else {
            printf("\tDriver        : No\n");
        }
        printf("\tTotal Price   : %ld\n",order[j].t);
        printf("\tDown payment  : %d\n",order[j].u);
        printf("\t==========================================================================================\n");
    }

    fclose(fp1);
    fclose(fp2);
}

void loginAdmin(){
    FILE *fp = fopen("./database/admin.txt","r");
    int i=0;
    while(fscanf(fp,"%[^#]#%s\n",user[i].name,user[i].pass) != EOF){
        i++;
    }
    fclose(fp);
    login:
    char users[15];
    char first[15];
    printf("\tUsername : ");
    scanf("%s",users); getchar();
    printf("\tPassword : ");
        int p=0;
        do{
            first[p]=getch();
            if(first[p]!='\r'){
                printf("*");
            }
            p++;
        }while(first[p-1]!='\r');
        first[p-1]='\0';
        getch();
        puts("");

    int ctr = 0;
    for(int j=0;j<i;j++){
        if(strcmp(users,user[j].name) == 0){
            ctr++;
        }
    }
    if(ctr == 0){
            printf("\tYOURE NOT AUTHORIZED\n");
            goto login;
    }
    ctr = 0;
    for(int j=0;j<i;j++){
        if(strcmp(first,user[j].pass) == 0){
            ctr++;
        }
    }
    if(ctr == 0){
        printf("\tYOURE NOT AUTHORIZED\n");
        goto login;
    }else{
        system("cls");
        adminMenu();
    }
}

// admin menu
void adminMenu(){
    AM:
    int ch;
    goWheelsArt();
    printf("\n\t[1]> History Order\n");
    printf("\t[0]> Logout\n\n");
    printf(" >> ");
    scanf("%d",&ch);getchar();
    char next;
    while(1){
        if(ch==0){
            system("cls");
            displayExitArt();
            puts("");
            printf("\nPress [Enter] return to Home Page ...");
            scanf("%c",&next); 
            system("cls");
            main();
            break;
            }else if (ch==1){
            system("cls");
            historyA();
            printf("\nPress [Enter] to return ...");
            scanf("%c",&next);
            system("cls");
            goto AM;
            break;
        }
        else{
            system("cls");
            goto AM;
        }
    }
}

// main menu
void mainMenu(){
    MM:
    goWheelsArt();
    int ch;
    puts("\n\t[1]> Car Info View"); 
    puts("\t[2]> Car Request"); 
    puts("\t[3]> Car Booking\n\n");
    puts("\t[0]> Logout\n");
    printf(" >> "); scanf("%d", &ch); 
    fflush(stdin);

    char next;
    while(1){
        if(ch==0){
            system("cls");
            displayExitArt();
            puts("");
            printf("Press [Enter] return to Home Page ...");
            scanf("%c",&next);
            system("cls");
            main();
            break;
        } else if (ch==2){
            system("cls");
            carRequest();
            printf("Press [Enter] to return ...");
            scanf("%c",&next);
            system("cls");
            carRequest();
            break;
        } else if (ch==3){
            system("cls");
            menuBooking();
            printf("\n\tPress [Enter] to return ...");
            scanf("%c",&next);
            system("cls");
            menuBooking();
            break;
        } else if (ch==1){
            system("cls");
            infoCar();
            printf("Press [Enter] to return ...");
            scanf("%c",&next);
            system("cls");
            infoCar();
            break;
        }
        else{
            system("cls");
            goto MM;
        }
    }
}

// registrasi
void regis(){
    FILE *fp = fopen("./database/users.txt","a+");
    int i=0;
    while(fscanf(fp,"%[^#]#%s",user[i].name,user[i].pass) != EOF){
        i++;
    }
        char users[15];
        char first[15];
        char second[15];
        int len = 0;
        
        regis:
        printf("\tUsername  [7-15 Word]: ");
        scanf("%s",users); getchar();
        len = strlen(users);
        if(len < 7 || len > 15){
            printf("\tUsername Invalid\n");
            goto regis;
        }

        pass:
        printf("\tPassword  [7-15 Word]: ");
        int p=0;
        do{
            first[p]=getch();
            if(first[p]!='\r'){
                printf("*");
            }
            p++;
        }while(first[p-1]!='\r');
        first[p-1]='\0';
        getch();
        puts("");
        len = strlen(first);
        if(len < 7 || len > 15){
            printf("\tPassword Invalid\n");
            goto pass;
        }

        printf("\tConfirm Password     : ");
        int j=0;
        do{
            second[j]=getch();
            if(second[j]!='\r'){
                printf("*");
            }
            j++;
        }while(second[j-1]!='\r');
        second[j-1]='\0';
        getch();
        puts("");
    if(strcmp(first,second) == 0){
	    fprintf(fp,"%s#%s\n",users,first);
        printf("\tSucces Now Try to Login\n\n");
    }else{
        printf("\tPassword Invalid\n");
        goto pass;
    }
    fclose(fp);
}

// login
void login(){
    FILE *fp = fopen("./database/users.txt","r");
    int i=0;
    while(fscanf(fp,"%[^#]#%s\n",user[i].name,user[i].pass) != EOF){
        i++;
    }
    fclose(fp);
    login:
    char users[15];
    char first[15];
    printf("\tUsername : ");
    scanf("%s",users); getchar();
    printf("\tPassword : ");
        int p=0;
        do{
            first[p]=getch();
            if(first[p]!='\r'){
                printf("*");
            }
            p++;
        }while(first[p-1]!='\r');
        first[p-1]='\0';
        getch();
        puts("");

    int ctr = 0;
    for(int j=0;j<i;j++){
        if(strcmp(users,user[j].name) == 0){
            ctr++;
        }
    }
    if(ctr == 0){
            printf("\tYOURE NOT AUTHORIZED\n");
            goto login;
    }
    ctr = 0;
    for(int j=0;j<i;j++){
        if(strcmp(first,user[j].pass) == 0){
            ctr++;
        }
    }
    if(ctr == 0){
        printf("\tYOURE NOT AUTHORIZED\n");
        goto login;
    }else{
        system("cls");
        mainMenu();
    }
}

// function apabila user milih (1) di main menu
void infoCar(){
    IC:
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
            system("cls");
            // main();
            mainMenu();
            break;
        } else if (cho == 1) {
            system("cls");
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
            system("cls");
            int cy;
            puts("\t+----------------------------+");
            puts("\t| Sort by Year of Production |");
            puts("\t+----------------------------+\n");
            puts("\t[1]> Old-New\n\t[2]> New-Old\n");
            puts("\t[0]> Go Back");
            printf(" >> "); scanf("%d", &cy);

            if(cy==1){
                displaySorted(2);
                break;
            } else if (cy==2){
                displaySorted(3);
                break;
             }else if (cy==0){
                infoCar();
                break;
            }
        } else{
            system("cls");
            goto IC;
        }
    }
}

// sort berdasarkan price pake bubble sort
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

//sort berdasarkan tahun produksi pake bubble sort
void sortYearProduction(struct Car *data, int len){
    for(int i=0; i<len; i++){
        for(int j=0; j<len-1-i; j++){
            if(data[j].tc.yearProduction >= data[j+1].tc.yearProduction){
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
            printf("\t| %-15s| %-6.2lf | %-13s | %-18d | Rp%-10d |\n", cars[j].brandCar, cars[j].tc.rate, cars[j].tc.nameCar, cars[j].tc.yearProduction, cars[j].tc.price);
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
            printf("\t| %-15s| %-6.2lf | %-13s | %-18d | Rp%-10d |\n", cars[j].brandCar, cars[j].tc.rate, cars[j].tc.nameCar, cars[j].tc.yearProduction, cars[j].tc.price);
        }
        puts("\t+-----------------------------------------------------------------------------+\n");
    } else if(choice==1){ 
        sortPrice(cars, i);
        displayJudul();
        for(int j = i-1; j>=0; j--){
            printf("\t| %-15s| %-6.2lf | %-13s | %-18d | Rp%-10d |\n", cars[j].brandCar, cars[j].tc.rate, cars[j].tc.nameCar, cars[j].tc.yearProduction, cars[j].tc.price);
        }
        puts("\t+-----------------------------------------------------------------------------+\n");
    } else if (choice==2){
        sortYearProduction(cars, i);
        displayJudul();
        for (int j = 0; j < i; j++){
            printf("\t| %-15s| %-6.2lf | %-13s | %-18d | Rp%-10d |\n", cars[j].brandCar, cars[j].tc.rate, cars[j].tc.nameCar, cars[j].tc.yearProduction, cars[j].tc.price);
        }
        puts("\t+-----------------------------------------------------------------------------+\n");
    } else if (choice==3){
        sortYearProduction(cars, i);
        displayJudul();
        for(int j = i-1; j>=0; j--){
            printf("\t| %-15s| %-6.2lf | %-13s | %-18d | Rp%-10d |\n", cars[j].brandCar, cars[j].tc.rate, cars[j].tc.nameCar, cars[j].tc.yearProduction, cars[j].tc.price);
        }
        puts("\t+-----------------------------------------------------------------------------+\n");
    }
    return i;
}

// function apabila user milih (2) di main menu
void carRequest(){
    CR:
    puts("\t+-------------+");
    puts("\t| Car Request |");
    puts("\t+-------------+\n");

    displayReq();

    int choice;
    printf("\t[1]> Add Car Request\n\n\n");
    puts("\t[0]> Go Back\n");
    printf(" >> "); scanf("%d", &choice); fflush(stdin);

    if(choice==1){
        // Add Car Request
        system("cls");
        puts("\t+-------------+");
        puts("\t| Car Request |");
        puts("\t+-------------+\n");
        printf("\tCar Brand\t\t: "); scanf("%[^\n]", cars->brandCar); 
        printf("\tRate Car [1-5]\t\t: "); getchar(); scanf("%lf", &cars->tc.rate); 
        printf("\tCar Name\t\t: "); getchar(); scanf("%[^\n]", cars->tc.nameCar); 
        printf("\tYear of Production\t: " ); getchar(); scanf("%d", &cars->tc.yearProduction);
        printf("\tPrice Request (/day)\t: "); getchar(); scanf("%d", &cars->tc.price);
        printf("\n\tAnd lastly, please write down your reasons for requesting that car\n");
        printf("\tbecause your reasons can be a consideration for us\n");
        printf("\t>> "); getchar(); scanf("%[^\n]", cars->tc.reasons); getchar();

        // masukin ke reasonsList
        FILE *fr = fopen("./database/reasonsList.txt", "a");
        fprintf(fr, "%s#%s\n", cars->tc.nameCar, cars->tc.reasons);
        fclose(fr);

        // masukin ke reqList
        FILE *fp = fopen("./database/reqList.txt", "a");
        fprintf(fp,"%s#%.2lf#%s#%d#%d\n", cars->brandCar, cars->tc.rate, cars->tc.nameCar, cars->tc.yearProduction, cars->tc.price);
        fclose(fp);

        printf("\n");
        displayReq();
    }else if (choice == 0){
        system ("cls");
        mainMenu();
    } else{
        system ("cls");
        goto CR;
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
        printf("\t| %-15s| %-6.2lf | %-13s | %-18d | Rp%-10d |\n", cars[j].brandCar, cars[j].tc.rate, cars[j].tc.nameCar, cars[j].tc.yearProduction, cars[j].tc.price);
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
    fclose(fb);
  return number[n];
}

// untuk display tanggal rental
void rentDate(int day, int month, int year){
    if (day < 10 && month < 10){
        printf("\tRent Date     : 0%d/0%d/%d\n",day,month,year);
    }else if (day < 10){
        printf("\tRent Date     : 0%d/%d/%d\n",day,month,year);
    }else if (month < 10){
        printf("\tRent Date     : %d/0%d/%d\n",day,month,year);
    }
}

// fungsi waktu sekarang diambil dari waktu default komputer
void currTime(){
    FILE *fp1 = fopen("./database/historyTime.txt","a");
    struct tm *currentTime;
 
    time_t userTime;
    userTime = time(NULL);
    currentTime = localtime(&userTime);

    printf("%66s",asctime (currentTime));
    fprintf(fp1,"%s",asctime (currentTime));
    fclose(fp1);
}

// function apabila user milih (3) di main menu
void menuBooking(){
    MB:
    puts("\t+-------------+");
    puts("\t| Car Booking |");
    puts("\t+-------------+\n");
    printf("\t[1]> Rent Per Day\n\t[2]> Rent Per Week Disc 10%% Off\n\n");
    puts("\n\t[0]> Go back\n");
    printf(" >> ");
    int choose;
    scanf("%d",&choose);
    switch (choose){
    case 1:
        system ("cls");
        carBooking(1);
        break;
    case 2:
        system ("cls");
        carBooking(2);
        break;

    case 0:
        system ("cls");
        mainMenu();
        break;

    default:
        system ("cls");
        goto MB;
    }
}

void carBooking(int temp){

    puts("\t+-------------+");
    puts("\t| Car Booking |");
    puts("\t+-------------+\n");

    //scan file carlist.txt untuk menentukan harga rental mobil
    FILE *fp = fopen("./database/carList.txt","r");
    FILE *fp1 = fopen("./database/history.txt","a");
    int i=0;
    while(fscanf(fp,"%[^#]#%lf#%[^#]#%d#%d",cars[i].brandCar,&cars[i].tc.rate,
        cars[i].tc.nameCar,&cars[i].tc.yearProduction,&cars[i].tc.price) != EOF){
            i++;
    }

    //biodata user
    struct Admin infoPelanggan;
    puts("\tPlease fill in Your Biodata");
    printf("\tName\t\t : "); scanf(" %[^\n]",infoPelanggan.Name);
    printf("\tAddress\t\t : "); scanf(" %[^\n]",infoPelanggan.Address);getchar();
    printf("\tPhone Number\t : "); scanf("%ld",&infoPelanggan.PhoneNum);getchar();

    Date:
    //tanggal peminjaman
    printf("\n\tPlease Fill in Your Rent Date ex: (01/01/2000)\n");
    printf("\tDay   : ");
    scanf("%d",&infoPelanggan.pd.day); getchar();
    printf("\tMonth : ");
    scanf("\t%d",&infoPelanggan.pd.month); getchar();
    printf("\tYear  : ");
    scanf("%d",&infoPelanggan.pd.year); getchar();
    int tempe = infoPelanggan.pd.month % 2;
    if(infoPelanggan.pd.day > 31 || infoPelanggan.pd.month > 12 || infoPelanggan.pd.year < 2022){
        printf("\tInvalid Input\n");
        goto Date;
    }

    puts("\n\tPlease Fill in Your Rent Car Data");
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
    if (temp == 1){
        printf("\tRent Duration (/day)\t: "); scanf("%d",&infoPelanggan.pc.Duration); getchar();
    }
    else if(temp == 2){
        printf("\tRent Duration (/week)\t: "); scanf("%d",&infoPelanggan.pc.Duration); getchar();
    }
    printf("\tHire Driver (Yes/No)\t: "); scanf(" %[^\n]",infoPelanggan.pc.Driver); getchar();

    long int harga = 0;
    int tempDriver = 0;
    //searching mobil & harga day
    if(temp == 1){
        for(int j=0;j<=i;j++){
            if(strcmp(infoPelanggan.pc.nameCar , cars[j].tc.nameCar) == 0){
                harga =  infoPelanggan.pc.Duration * cars[j].tc.price;
            }
        }
    // menetukan harga sopir
            if(strcmp(infoPelanggan.pc.Driver,"Yes") == 0 || strcmp(infoPelanggan.pc.Driver,"yes" ) == 0 || strcmp(infoPelanggan.pc.Driver,"YES") == 0){
            harga = harga + 100000 * infoPelanggan.pc.Duration;
            tempDriver++;
        }
    }

    //searching mobil & harga week
    if(temp == 2){
        for(int j=0;j<=i;j++){
            if(strcmp(infoPelanggan.pc.nameCar , cars[j].tc.nameCar) == 0){
                harga =  (infoPelanggan.pc.Duration * cars[j].tc.price) * 7;
                harga = harga * 0.9;
            }
        }
    // menetukan harga sopir
        if(strcmp(infoPelanggan.pc.Driver,"Yes") == 0 || strcmp(infoPelanggan.pc.Driver,"yes" ) == 0 || strcmp(infoPelanggan.pc.Driver,"YES") == 0){
            harga = harga + (100000 * infoPelanggan.pc.Duration * 7);
            tempDriver++;
        }
    }

    //harga akhir
    printf("\tTotal Price\t\t: %ld\n",harga);
    int uangMuka = harga*0.6;
    printf("\tDown payment\t\t: %d\n",uangMuka);

    char question;
    printf("\n\tAre you sure with this information? (Y/N) "); scanf("%c",&question); getchar();

    int bookNumber = uangMuka % 9;
    int number = noBooking(bookNumber);
    if(question == 'Y' || question == 'y'){
		system ("cls");
        printf("\t_________________________________________________________________________________________\n\n");
        printf("\tNo Booking    : %d",number);
        currTime();
        printf("\tName          : %s\n",infoPelanggan.Name);
        printf("\tAddress       : %s\n", infoPelanggan.Address);
        printf("\tPhone number  : %ld\n", infoPelanggan.PhoneNum);
        printf("\tCar Name      : %s\n", infoPelanggan.pc.nameCar);
        rentDate(infoPelanggan.pd.day,infoPelanggan.pd.month,infoPelanggan.pd.year);
        if(temp == 1){
            printf("\tRent Duration : %d day\n", infoPelanggan.pc.Duration);
        }else if(temp == 2){
            printf("\tRent Duration : %d week\n", infoPelanggan.pc.Duration);
        }
        if(tempDriver == 1){
            printf("\tDriver        : Yes\n");
        }else {
            printf("\tDriver        : No\n");
        }
        
        printf("\tTotal Price   : %ld\n",harga);
        printf("\tDown payment  : %d\n",uangMuka);
        printf("\n\tPlease pay your down payment first and you can take the car at Go-Wheels Rent Car nearby\n");
        printf("\t==========================================================================================\n");        
        displayExitArt();
        // hari, supir, durasi, nobook, nama, alamat, notelp, mobil, totalharga, uangmuka
        fprintf(fp1,"%d#%d#%d#%d#%s#%s#%ld#%s#%ld#%d#",temp,tempDriver,infoPelanggan.pc.Duration,number,
        infoPelanggan.Name,infoPelanggan.Address,infoPelanggan.PhoneNum,infoPelanggan.pc.nameCar,harga,uangMuka);
        //rentdate
        fprintf(fp1,"%d#%d#%d\n",infoPelanggan.pd.day,infoPelanggan.pd.month,infoPelanggan.pd.year);
    } else if (question == 'N'|| question == 'n'){
		system ("cls");
        menuBooking();
        printf("\n") ;
    }
    fclose(fp1);
    fclose(fp);
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