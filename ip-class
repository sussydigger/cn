#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// Function to determine the class of an IP address
char findClass(char str[])
{
    // Extract the first octet from the IP address
    char first_octet[4];
    int i = 0;
    while (str[i] != '.')
    {
        first_octet[i] = str[i];
        i++;
    }
    first_octet[i] = '\0';
    // Convert the extracted octet to an integer
    int first_octet_num = atoi(first_octet);
    // Determine the class based on the first octet
    if (first_octet_num >= 1 && first_octet_num <= 126)
        return 'A';
    else if (first_octet_num >= 128 && first_octet_num <= 191)
        return 'B';
    else if (first_octet_num >= 192 && first_octet_num <= 223)
        return 'C';
    else if (first_octet_num >= 224 && first_octet_num <= 239)
        return 'D';
    else if (first_octet_num >= 240 && first_octet_num <= 255)
        return 'E';
    else
        return '\0'; // Invalid IP address char findClasss
}
int main()
{
    char ip_address[20];
    printf("Enter the IP address: ");
    scanf("%s", ip_address);
    char ip_class = findClass(ip_address);
    if (ip_class != '\0')
    {
        printf("IP Address: %s\n", ip_address);
        printf("Class: %c\n", ip_class);
    }
    else
    {
        printf("Invalid IP address.\n");
    }
    return 0;
}
