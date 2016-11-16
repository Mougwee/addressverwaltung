#include <stdio.h>
#include <stdlib.h>
#include "address.h"

char ch;
char buffer[MAXBUFFERSIZE];
int char_count;

void readLine(void){
    //Buffer leeren
    for(int i = 0; i < MAXBUFFERSIZE; i++){
        buffer[i] = '\0';
    }
    //Charakteranzahl leeren
    char_count = 0;
    
    ch = getchar();                 //ein Zeichen wird abgerufen
    while((ch != '\n') && (char_count < (MAXBUFFERSIZE - 1))){
        if(ch != '\b'){
            buffer[char_count] = ch;    //das abgerufene Zeichen wird in eine Zelle des Char-Arrays eingefügt
            char_count++;               //der Zeichenzähler wird erhöht
        }
        else{   // == Backspace, einen Character zurèck
            char_count--;
        }
        ch = getchar();             //das nächste Zeichen wird abgerufen
    }
    buffer[char_count] = '\0';      //Schliesst den String ab
}


void saveBuffer(char** target, char source[], int count){
    *target = (char*) malloc(count * sizeof(char));
    for(int i = 0; i <= count; i++){
        (*target)[i] = source[i];   //TODO: dynamische Darstellung: (*(*target) + i)
        //Achtung Operatorenpriorität
        //*target[i] ist gleich *(target[i]), es gibt aber nur ein target
    }
}



void addNewAddress(AddressPtr_t* node){
    //die nächste freie Adresse auswählen
    while(*node != NULL){
        node = &(*(*node)).next;
        //*node =, würde den Inhalt von node, also head, verändern!
    }
    
    //entsprechend Speicher allozieren
    *node = (AddressPtr_t)malloc(sizeof(Address_t));
    
    // --- Firstname
    printf("%-15s", "firstname:");
    readLine();
    saveBuffer(&(*(*node)).firstname, buffer, char_count);
    
    // --- Name
    printf("%-15s", "name:");
    readLine();
    saveBuffer(&(*(*node)).name, buffer, char_count);
    
    // --- Street
    printf("%-15s", "street:");
    readLine();
    saveBuffer(&(*(*node)).street, buffer, char_count);
    
    // --- StreetNbr
    printf("%-15s", "number:");
    readLine();
    saveBuffer(&(*(*node)).streetNbr, buffer, char_count); //TODO: int-Wert, nicht char
    
    // --- ZIP
    printf("%-15s", "zip:");
    readLine();
    saveBuffer(&(*(*node)).zip, buffer, char_count); //TODO: int-Wert, nicht char
    
    // --- City
    printf("%-15s", "city:");
    readLine();
    saveBuffer(&(*(*node)).city, buffer, char_count);
    
    //Nullpointer auf die nächste Node, damit die while-Schleife wieder funktioniert
    (*(*node)).next = NULL;
    
    
}

void listAddresses(AddressPtr_t* node){
    while(*node != NULL){
        printf("%s %s\n", (*(*node)).firstname, (*(*node)).name);
        printf("%s %s\n", (*(*node)).street, (*(*node)).streetNbr);
        printf("%s %s\n\n", (*(*node)).zip, (*(*node)).city);
        node = &(*(*node)).next;
        //*node =, würde den Inhalt von node, also head, verändern!
    }
}