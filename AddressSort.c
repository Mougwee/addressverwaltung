#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "address.h"

void sortBy(AddressPtr_t* node, StructData_t item){
    AddressPtr_t* isNode = node;
    
    //Vorhandene Addressen zählen
    int zaehler = 0;
    //alle Nodes durchzählen
    while(*isNode != NULL){
        zaehler += 1;
        isNode = &(*(*isNode)).next;
    }
    //isNode wieder auf Head richten
    isNode = node;
    
    //Alle Structures in ein Pointer-Array füllen
    AddressPtr_t allStructures[zaehler];
    for(int i = 0; i < zaehler; i++){
        allStructures[i] = &(*(*isNode));
        isNode = &(*(*isNode)).next;
    }
    //isNode wieder auf Head richten
    isNode = node;
    
    AddressPtr_t tempPtr = NULL;
    switch(item){
        case NAME:
            //Sortierung des allStructure Arrays
            for(int i = 0; i < zaehler; i++){
                for(int j = 0; j < zaehler; j++){
                    int wert = strcmp((*(allStructures[i])).name, (*(allStructures[j])).name);
                    if(wert < 0){
                        tempPtr = allStructures[j];
                        allStructures[j] = allStructures[i];
                        allStructures[i] = tempPtr;
                    }
                }
            }
            
            //Verkettete Liste neu formieren
            int k;
            *node = allStructures[0];
            for(k = 0; k < zaehler; k++){
                (*allStructures[k]).next = &(*allStructures[k + 1]);
            }
            //letztes next auf NULL setzen
            (*allStructures[k - 1]).next = NULL;
            
            break;
        case STREET:
            //Sortierung des allStructure Arrays
            for(int i = 0; i < zaehler; i++){
                for(int j = 0; j < zaehler; j++){
                    int wert = strcmp((*(allStructures[i])).street, (*(allStructures[j])).street);
                    if(wert < 0){
                        tempPtr = allStructures[j];
                        allStructures[j] = allStructures[i];
                        allStructures[i] = tempPtr;
                    }
                }
            }
            
            //Verkettete Liste neu formieren
            k = 0;
            *node = allStructures[0];
            for(k = 0; k < zaehler; k++){
                (*allStructures[k]).next = &(*allStructures[k + 1]);
            }
            //letztes next auf NULL setzen
            (*allStructures[k - 1]).next = NULL;
            
            break;
        case CITY:
            //Sortierung des allStructure Arrays
            for(int i = 0; i < zaehler; i++){
                for(int j = 0; j < zaehler; j++){
                    int wert = strcmp((*(allStructures[i])).city, (*(allStructures[j])).city);
                    if(wert < 0){
                        tempPtr = allStructures[j];
                        allStructures[j] = allStructures[i];
                        allStructures[i] = tempPtr;
                    }
                }
            }
            
            //Verkettete Liste neu formieren
            k = 0;
            *node = allStructures[0];
            for(k = 0; k < zaehler; k++){
                (*allStructures[k]).next = &(*allStructures[k + 1]);
            }
            //letztes next auf NULL setzen
            (*allStructures[k - 1]).next = NULL;
            
            break;
    }
    
}