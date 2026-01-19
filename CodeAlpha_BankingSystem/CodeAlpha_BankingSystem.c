#include <stdio.h>

struct bank {
    int accNo;
    float balance;
};

void deposit();
void withdraw();
void balanceEnquiry();

int main() {
    int choice;

    do {
        printf("\n========== BANKING SYSTEM ==========\n");
        printf("1. Deposit\n");
        printf("2. Withdraw\n");
        printf("3. Balance Enquiry\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: deposit(); break;
            case 2: withdraw(); break;
            case 3: balanceEnquiry(); break;
            case 4: printf("Program Exited.\n"); break;
            default: printf("Invalid Choice!\n");
        }
    } while (choice != 4);

    return 0;
}

/* Ensure file is initialized */
void initFile() {
    FILE *fp = fopen("bank.dat", "rb");
    struct bank b;

    if (fp == NULL) {
        fp = fopen("bank.dat", "wb");
        b.accNo = 1001;
        b.balance = 0.0;
        fwrite(&b, sizeof(b), 1, fp);
        fclose(fp);
        return;
    }

    fseek(fp, 0, SEEK_END);
    if (ftell(fp) == 0) {   // empty file
        fclose(fp);
        fp = fopen("bank.dat", "wb");
        b.accNo = 1001;
        b.balance = 0.0;
        fwrite(&b, sizeof(b), 1, fp);
    }

    fclose(fp);
}

/* Deposit */
void deposit() {
    FILE *fp;
    struct bank b;
    float amt;

    initFile();

    fp = fopen("bank.dat", "rb+");
    fread(&b, sizeof(b), 1, fp);

    printf("Enter Deposit Amount: ");
    scanf("%f", &amt);

    b.balance += amt;

    rewind(fp);
    fwrite(&b, sizeof(b), 1, fp);

    printf("Amount Deposited Successfully!\n");
    fclose(fp);
}

/* Withdraw */
void withdraw() {
    FILE *fp;
    struct bank b;
    float amt;

    initFile();

    fp = fopen("bank.dat", "rb+");
    fread(&b, sizeof(b), 1, fp);

    printf("Enter Withdraw Amount: ");
    scanf("%f", &amt);

    if (amt <= b.balance) {
        b.balance -= amt;
        rewind(fp);
        fwrite(&b, sizeof(b), 1, fp);
        printf("Amount Withdrawn Successfully!\n");
    } else {
        printf("Insufficient Balance!\n");
    }

    fclose(fp);
}

/* Balance Enquiry */
void balanceEnquiry() {
    FILE *fp;
    struct bank b;

    initFile();

    fp = fopen("bank.dat", "rb");
    fread(&b, sizeof(b), 1, fp);

    printf("\nAccount Number : %d\n", b.accNo);
    printf("Available Balance : %.2f\n", b.balance);

    fclose(fp);
}

