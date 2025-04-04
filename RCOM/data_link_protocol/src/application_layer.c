// Application layer protocol implementation
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#include "application_layer.h"
#include "link_layer.h"

#define MAX_PACKET_SIZE 2037 //1+1+2+256*8+255
#define TRUE 1
#define FALSE 0
// in the guide sequance number is (0-99) but since we have 1 byte for
// sequance we can have sequance number (0-255)
#define SEQUANCE_MAX 255

char R_FILE_NAME[50];
long R_FILE_SIZE = 0;

typedef struct {
    int value;      // integer value
    unsigned char *pointer;  // pointer to a character array
} Result;

Result getControlPacket(int control_field, const char *file_name, long file_size)
{
    char C, T1, T2, L1, L2;
    C = control_field;
    T1 = 0; //file size
    T2 = 1; //file name
    L1 = 8; //long is 8 bytes
    L2 = strlen(file_name);

    int packet_length = 5+L1+L2; //5 FOR C, Ts and Ls
    int index = 0;

    unsigned char *packet = (unsigned char*) malloc((packet_length) * sizeof(char));
    
    packet[index++] = C;
    packet[index++] = T1;
    packet[index++] = L1;

    packet[index++] = (file_size >> 56) & 0xFF; // Extract the most significant byte
    packet[index++] = (file_size >> 48) & 0xFF; // Extract the second byte
    packet[index++] = (file_size >> 40) & 0xFF; // Extract the third byte
    packet[index++] = (file_size >> 32) & 0xFF; // Extract the fourth byte
    packet[index++] = (file_size >> 24) & 0xFF; // Extract the fifth byte
    packet[index++] = (file_size >> 16) & 0xFF; // Extract the sixth byte
    packet[index++] = (file_size >> 8) & 0xFF;  // Extract the seventh byte
    packet[index++] = file_size & 0xFF;

    long tmp=0;
    for(int i=3;i<=10;i++){
        tmp = tmp*256+packet[i];
    }
    printf("=============================== %ld\n", tmp);

    packet[index++] = T2;
    packet[index++] = L2;

    memcpy(&packet[index], file_name, L2);  // Copy file name into packet
    index += L2;
    Result r;
    r.pointer = packet;
    r.value = packet_length;

    return r;
}

Result getDataPacket(unsigned char *buf, int buf_size, int sequence_number)
{
    unsigned char *packet = (unsigned char*) malloc((buf_size + 4) * sizeof(char));
    int index=0;
    packet[index++] = 2;
    packet[index++] = sequence_number;
    packet[index++] = (buf_size >> 8) & 0xFF;
    packet[index++] = buf_size & 0xFF;
    memcpy(&packet[index], buf, buf_size);
    Result r;
    r.pointer = packet;
    r.value = buf_size+4;

    return r;
}

int parsePacket(unsigned char *packet, int size, FILE* fptr)
{
    int tmp;
    switch (packet[0])
    {
    case 1:
        for(int i=0;i<8;i++){
            R_FILE_SIZE = R_FILE_SIZE * 256 + packet[3+i];
        }
        printf("received file size is suppoosed to be %ld bytes\n", R_FILE_SIZE);

        tmp = packet[12]; // in our case tmp (length of saved information L1 or L2)
                          // can be hardcoded bc we previous info avays takes same amount of place
        for(int i=0;i<tmp;i++){
            R_FILE_NAME[i] = packet[13+i];
        }
        printf("received file name is suppoosed to be %.50s\n", R_FILE_NAME);
        return 1;
    case 2:
        int Ls = 256*packet[2]+packet[3];
        for(int i=0;i<Ls+4;i++){
            printf("%x",packet[i]);
        }
        printf("\n");
        fwrite(&packet[4],1,Ls,fptr);
        return 2;
    case 3:
        long file_size = 0;
        for(int i=0;i<8;i++){
            file_size = file_size * 256 + packet[3+i];
        }

        char file_name[50];
        tmp = packet[12];
        for(int i=0;i<tmp;i++){
            file_name[i] = packet[13+i];
        }

        if(file_size != R_FILE_SIZE){
            printf("file size from 1st and last contr. packet is different\n");
            printf("%ld vs. %ld\n", file_size, R_FILE_SIZE);
            exit(-1);
        }

        for(int i=0;i<50;i++){
            if(R_FILE_NAME[i] != file_name[i]){
                printf("file name from 1st and last contr. packet is different\n");
                exit(-1);
            }
        }
        return 3;
    default:
        return -1;
    }
}

void applicationLayer(const char *serialPort, const char *role, int baudRate,
                      int nTries, int timeout, const char *file_name)
{
    LinkLayer connectionParameters;
    strcpy(connectionParameters.serialPort, serialPort);
    connectionParameters.role = *role;
    connectionParameters.baudRate = baudRate;
    connectionParameters.nRetransmissions = nTries;
    connectionParameters.timeout = timeout;

    if(llopen(connectionParameters) < 0){
            printf("Couldnt open the connection\n");
            exit(-1);
        }

    if(strcmp(role,"tx") == 0){
        FILE* fptr;
        fptr = fopen(file_name, "rb");
    
        fseek(fptr, 0, SEEK_END);
        long file_size = ftell(fptr);
        fseek(fptr, 0, SEEK_SET);

        printf("File size: %ld bytes\n", file_size);
        int buffer_size = ceil(file_size / SEQUANCE_MAX+1);
        printf("buffer size: %d bytes\n", buffer_size);
        unsigned char* buffer = (unsigned char*)malloc(buffer_size * sizeof(unsigned char));

        Result r = getControlPacket(1, file_name, file_size);
        if(llwrite(r.pointer,r.value) < 0){
            printf("llwrite coulding send opening packet\n");
            exit(-1);
        }

        int sequence = 0;
        int actual_size;
        while((actual_size = fread(buffer,1,  buffer_size, fptr)) > 0)
        {
            printf("act = %d, buf = %d\n",actual_size,buffer_size);
            r = getDataPacket(buffer, actual_size, sequence);

            printf("sequence #%d sent\n", r.pointer[1]);
            for(int i=0;i<256*r.pointer[2]+r.pointer[3]+4;i++)
            {
                printf("%x",r.pointer[i]);
            }
            printf("\n");

            int send = TRUE;
            while(send){
                switch (llwrite(r.pointer, r.value))
                {
                case -1: // big error
                    printf("llwrite couldnt send packet %d\n", sequence);
                    exit(-1);
                    break;
                case -2: // REJ received so retransmission
                    printf("retransmitting packet %d\n", sequence);
                case -11: // ignoring?
                    send = FALSE;
                    break;
                case -12: // ignoring?
                    send = FALSE;
                    break;
                case -13: // ignoring?
                    send = FALSE;
                    break;
                default: // >0 so okay
                    send = FALSE;
                    break;
                }
            }
            sequence++;
        }   

        r = getControlPacket(3, file_name, file_size);
        if(llwrite(r.pointer, r.value) < 0)
        {
            printf("llwrite couldn send ending packet\n");
            exit(-1);
        }
        if(llclose(1)<0){
            printf("smh wrong with tx llclose\n");
            exit(-1);
        }
        fclose(fptr);
    }
    else{
        FILE* fptr;
        fptr = fopen(file_name, "wb");
        int result;
        unsigned char* buffer = (unsigned char*)malloc(MAX_PACKET_SIZE * sizeof(unsigned char));

        int END = FALSE;

        while(!END){
            result = llread(buffer);
            if(result>=0){
                if(parsePacket(buffer, result, fptr)==3) END = TRUE;
            }
            if(result<0){
                printf("llread returned error\n");
                exit(-1);
            }
        }
        if(llclose(1)<0){
            printf("smh wrong with rx llclose\n");
            exit(-1);
        }
        fclose(fptr);
    }
}