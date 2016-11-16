/* 
 * File:   main.c
 * Author: David FLeischlin
 *
 * Created on 7. November 2016, 13:08
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "address.h"

AddressPtr_t head = NULL;



//--------------------- MAIN ----------------------------------------//
int main(int argc, char** argv)
{
    char c;
    do {
        printf("\n");
        printf("N --> New address\n");
        printf("L --> List addresses\n");
        printf("R --> Read addresses from file\n");
        printf("S --> Save addresses to file\n");
        printf("1 --> Sort list by name\n");
        printf("2 --> Sort list by street\n");
        printf("3 --> Sort list by city\n");
        printf("Q --> Quit\n\n");
        while (!isalnum(c = getchar())); // Solange einlesen bis Zahl oder Buchstabe
        c = toupper(c);

        if(c){
            //'\n' aus Buchstabeneingabe aussortieren
            getchar();
        }
        
        switch (c)
        {
            case 'N':
                addNewAddress(&head);
                break;
            case 'L':
                listAddresses(&head);
                break;
            case 'R':
                getAddresses(&head);
                break;
            case 'S':
                saveAddresses(&head);
                break;
            case '1':
                sortBy(&head, NAME);
                break;
            case '2':
                sortBy(&head, STREET);
                break;
            case '3':
                sortBy(&head, CITY);
                break;
        }
    } while (c != 'Q');
    
    return (EXIT_SUCCESS);
}
