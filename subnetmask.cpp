#include <stdio.h>
#include <string.h>

void calculateSubnet(char *ip, char *mask, char *networkAddr, char *lastAddr);

int main() {
    char ip[16];
    char mask[16];
    char networkAddr[16];
    char lastAddr[16];

    int choice;
    do {
        printf("\n1. Enter IP");
        printf("\n2. Calculate Subnet Information");
        printf("\n3. Display Network Address and Last IP");
        printf("\n4. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("ENTER IP: ");
                scanf("%s", ip);
                break;
            case 2:
                calculateSubnet(ip, mask, networkAddr, lastAddr);
                break;
            case 3:
                if (strlen(networkAddr) > 0 && strlen(lastAddr) > 0) {
                    printf("Network Address: %s\n", networkAddr);
                    printf("Last IP of the block: %s\n", lastAddr);
                } else {
                    printf("Please calculate subnet information first.\n");
                }
                break;
            case 4:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please select a valid option.\n");
                break;
        }
    } while (choice != 4);

    return 0;
}

void calculateSubnet(char *ip, char *mask, char *networkAddr, char *lastAddr) {
    char checkclass[4];
    char defaultMask[16];

    strncpy(checkclass, ip, 3);
    checkclass[3] = '\0';

    int cc = atoi(checkclass);

    if (cc > 0) {
        if (cc <= 127) {
            strcpy(defaultMask, "255.0.0.0");
            printf("Class A IP Address\n");
            printf("SUBNET MASK:\n%s\n", defaultMask);
        } else if (cc >= 128 && cc <= 191) {
            strcpy(defaultMask, "255.255.0.0");
            printf("Class B IP Address\n");
            printf("SUBNET MASK:\n%s\n", defaultMask);
        } else if (cc >= 192 && cc <= 223) {
            strcpy(defaultMask, "255.255.255.0");
            printf("Class C IP Address\n");
            printf("SUBNET MASK:\n%s\n", defaultMask);
        } else if (cc >= 224 && cc <= 239) {
            strcpy(defaultMask, "255.0.0.0");
            printf("Class D IP Address Used for multicasting\n");
        } else if (cc >= 240 && cc <= 254) {
            strcpy(defaultMask, "255.0.0.0");
            printf("Class E IP Address Experimental Use\n");
        }

        char *ipAddrParts[4];
        char *maskParts[4];

        char *token = strtok(ip, ".");
        int i = 0;
        while (token != NULL) {
            ipAddrParts[i] = token;
            token = strtok(NULL, ".");
            i++;
        }

        token = strtok(defaultMask, ".");
        i = 0;
        while (token != NULL) {
            maskParts[i] = token;
            token = strtok(NULL, ".");
            i++;
        }

        char networkAddress[16] = "";
        char lastIPAddress[16] = "";

        for (int i = 0; i < 4; i++) {
            int x = atoi(ipAddrParts[i]);
            int y = atoi(maskParts[i]);
            int z = x & y;
            sprintf(networkAddress, "%s%d.", networkAddress, z);
            int w = z | (y ^ 255);
            sprintf(lastIPAddress, "%s%d.", lastIPAddress, w);
        }

        strcpy(mask, defaultMask);
        strcpy(networkAddr, networkAddress);
        strcpy(lastAddr, lastIPAddress);
    }
}
