<<<<<<< HEAD

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

#define NB_MES 13


int main(int argc, char **argv)
{

    //int tableau[10] = {0,1,2,3,4,5,6,7,8,9};
    int i;
    int s,status;
    char buffer[30];

    int timestamp[NB_MES]  = {1541692273,1541692573,1541692873,1541693173,1541693473,1541693773,1541694073,1541694373,1541694673,1541694973,1541695273,1541695573,1541695873};
    float lat[NB_MES] = {42.475537,42.462165,42.459861,42.487563,42.468548,42.445896,42.495632,42.458961,42.464587,42.431256,42.459864,42.485214,42.484562};
    float longi[NB_MES] = {3.476611,3.497214,3.486521,3.465423,3.498541,3.475632,3.475698,3.482541,3.476589,3.463251,3.463254,3.48520,3.458900};


    //sprintf(buffer,"%d;%f;%f",timestamp[0],lat[0],longi[0]);
    //printf("%s\n",buffer);


    struct sockaddr_rc addr = { 0 };
    char dest[18] = "98:4F:EE:03:F8:20";

    // allocate a socket
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // set the connection parameters (who to connect to)
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t) 1;
    str2ba(dest, &addr.rc_bdaddr);

    // connect to server
    status = connect(s, (struct sockaddr *)&addr, sizeof(addr));



    // send a message
    if( status == 0 ) {
        for(i=0;i<NB_MES;i++){
            // show the message
            sprintf(buffer,"%d;%f;%f",timestamp[i],lat[i],longi[i]);
            printf("Message %d : [ %s ]\n",i+1,buffer);
            status = write(s, buffer, sizeof(buffer));
        }
        //status = write (s,"end",3);
    }


    if( status < 0 ) perror("uh oh");

    close(s);
    return 0;
}
