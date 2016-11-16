#include <stdio.h>
#include <stdlib.h>
#include "address.h"

#define ADDRESSFILE "addresses.txt"

void saveAddresses(AddressPtr_t* node){
    FILE *fp;
    fp = fopen(ADDRESSFILE, "w+");
    
    // --- HEADER
    fprintf(fp, "Name,Vorname,Strasse,PLZ,Ort\n"); //evtl. Komma?
    
    while(*node != NULL){
        fprintf(fp, "%s,", (*(*node)).firstname);
        fprintf(fp, "%s,", (*(*node)).name);
        fprintf(fp, "%s,", (*(*node)).street);
        fprintf(fp, "%s,", (*(*node)).streetNbr);
        fprintf(fp, "%s,", (*(*node)).zip);
        fprintf(fp, "%s\n", (*(*node)).city);
        
        node = &(*(*node)).next;
        //*node =, würde den Inhalt von node, also head, verändern!
    }
    
    fclose(fp);
}

void emptyAddressMemory(AddressPtr_t* node){
    AddressPtr_t* isNode = node;
    int zaehler = 0;
    //alle Nodes durchzählen
    while(*isNode != NULL){
        zaehler += 1;
        isNode = &(*(*isNode)).next;
    }
    //isNode wieder auf Head richten
    isNode = node;
    
    //Alle Addressen in ein Pointer-Array füllen
    AddressPtr_t* allAddresses[zaehler];
    for(int i = 0; i < zaehler; i++){
        allAddresses[i] = isNode;
        isNode = &(*(*isNode)).next;
    }
    //isNode wieder auf Head richten
    isNode = node;
    
    //Addressen rückwärts durchgehen und Speicher freigeben
    for(int i = (zaehler - 1); i >= 0; i--){
        free((*(*(allAddresses[i]))).firstname);
        free((*(*(allAddresses[i]))).name);
        free((*(*(allAddresses[i]))).street);
        free((*(*(allAddresses[i]))).streetNbr);
        free((*(*(allAddresses[i]))).zip);
        free((*(*(allAddresses[i]))).city);
        free((*(*(allAddresses[i]))).next);
    }
    //Head freigeben
    free(*node);
    *node = NULL;   //naja... TODO?
    
}

void getAddresses(AddressPtr_t* node){
    //1. speicher der bisher eingegebenen Addressen freigeben
    emptyAddressMemory(node);
    
    //2. Speicher neu allozieren und einfüllen
    FILE *fp;
    fp = fopen(ADDRESSFILE, "r"); //Datei öffnen
    
    char tempBuffer[MAXBUFFERSIZE];
    int tempCharCount = 0;
    char ch;
    int structData = 0;
    AddressPtr_t oldNode;
    
    //erste Structure allozieren
    *node = (AddressPtr_t)malloc(sizeof(Address_t));
    
    ch = getc(fp);
    while(ch != '\n'){
        //erste Zeile überspringen
        ch = getc(fp);
    }
    
    ch = getc(fp);
    while(ch != EOF){
        while((ch != '\n') && (ch != ',')){
            tempBuffer[tempCharCount] = ch;
            tempCharCount++;
            ch = getc(fp);
        }
        //wort (und evtl auch Zeile) abgeschlossen
        tempBuffer[tempCharCount] = '\0'; //Wort-Array abschliessen
        
        if((ch == ',') || (structData < 6)){  //Wort abgeschlossen
            //Wort entsprechend abspeichern
            switch(structData){
                case FIRSTNAME:
                    saveBuffer(&(*(*node)).firstname, tempBuffer, tempCharCount);
                    structData++;
                    break;
                case NAME:
                    saveBuffer(&(*(*node)).name, tempBuffer, tempCharCount);
                    structData++;
                    break;
                case STREET:
                    saveBuffer(&(*(*node)).street, tempBuffer, tempCharCount);
                    structData++;
                    break;
                case STREETNBR:
                    saveBuffer(&(*(*node)).streetNbr, tempBuffer, tempCharCount);
                    structData++;
                    break;
                case ZIP:
                    saveBuffer(&(*(*node)).zip, tempBuffer, tempCharCount);
                    structData++;
                    break;
                case CITY:
                    saveBuffer(&(*(*node)).city, tempBuffer, tempCharCount);
                    structData++;
                    break;
            }
            //Wort fertig abgespeichert
            tempCharCount = 0;  //Buffer zurücksetzen
        }
        
        if(ch == '\n'){    //Zeile abgeschlossen
            structData = 0; //switch zurücksetzen
            oldNode = *node;
            (*(*node)).next = (AddressPtr_t)malloc(sizeof(Address_t)); //Speicher für nächste Structure allozieren
            node = &(*(*node)).next; //node-Pointer neu zuweisen für nächsten Durchgang
        }
        
        ch = getc(fp);      //nächsten Character, nach einem '\n' oder ',', abrufen
    }
    
    //EOF, letzte Allozierung wieder auflösen und NULL-Pointer zuweisen
    free((*oldNode).next);
    (*oldNode).next = NULL;
    
    fclose(fp); //Datei schliessen
}