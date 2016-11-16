/* 
 * File:   address.h
 * Author: David Fleischlin
 *
 * Created on 7. November 2016, 13:20
 */

#ifndef ADDRESS_H
#define ADDRESS_H

#define MAXBUFFERSIZE 80

typedef struct Address* AddressPtr_t;

typedef struct Address {
    char* firstname;
    char* name;
    char* street;
    char* streetNbr;    //TODO: int Bitfeld
    char* zip;          //TODO: int Bitfeld
    char* city;
    AddressPtr_t next;
} Address_t;

typedef enum StructData {
    FIRSTNAME,
    NAME,
    STREET,
    STREETNBR,
    ZIP,
    CITY
} StructData_t;


//Aus AddressConsoleIO.c
void readLine(void);
void saveBuffer(char** target, char source[], int count);
void addNewAddress(AddressPtr_t* node);
void listAddresses(AddressPtr_t* node);


//Aus AddressFileIO.c
void emptyAddressMemory(AddressPtr_t* node);
void getAddresses(AddressPtr_t* node);
void saveAddresses(AddressPtr_t* node);


//Aus AddressSort.c
void sortBy(AddressPtr_t* node, StructData_t item);


#endif /* ADDRESS_H */

