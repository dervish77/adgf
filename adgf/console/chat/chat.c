/********************************************************
*
* CHAT client program example using the ENet library
*
* File:   chat.c 
*
* Rev 0   09/14/2012   Originated
*
* Author: Brian Lingard
*
* Usage:  chat <user> <host> <port>
*
*	where host = name of machine (ex. tif686)
*	      port = numeric name of echo service (ex. 50001)
*
*********************************************************/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <enet/enet.h>

#include "chat.h"


int CHATclient( char *user, char *host, char *port )
{
    ENetHost     *client;
    ENetAddress  address;
    ENetEvent    event;
    ENetPeer     *peer;
    ENetPacket   *packet;

    int connected = 0;
    int portnum = atoi(port);
    char buffer[BUFFERSIZE];

    client = enet_host_create (NULL /* create a client host */,
                                  1 /* only allow 1 outgoing connection */,
                                  2 /* allow up 2 channels to be used, 0 and 1 */,
                                  57600 / 8 /* 56K modem with 56 Kbps downstream bandwidth */,
                                  14400 / 8 /* 56K modem with 14 Kbps upstream bandwidth */);

    if (client == NULL)
    {
        fprintf (stderr, "An error occurred while trying to create an ENet client host\n");
        exit (EXIT_FAILURE);
    }


    enet_address_set_host(&address, host);
    address.port = portnum;

    peer = enet_host_connect(client, &address, 2, 0);

    if (peer == NULL) 
    {
        printf("Could not connect to server\n");
        return 0;
    }

    if (enet_host_service(client, &event, 1000) > 0 
            && event.type == ENET_EVENT_TYPE_CONNECT) 
    {
        printf("Connection to %s succeeded.\n", host);
        connected++;

        strncpy(buffer, user, BUFFERSIZE);

        packet = enet_packet_create(buffer, strlen(buffer)+1, ENET_PACKET_FLAG_RELIABLE);
        enet_peer_send(peer, 0, packet);
    } 
    else 
    {
        enet_peer_reset(peer);
        printf("Could not connect to %s.\n", host);
        return 0;
    }


    while (1) 
    {
        while (enet_host_service(client, &event, 1000) > 0) 
        {
            switch (event.type) 
            {
                case ENET_EVENT_TYPE_RECEIVE:
                    puts( (char*) event.packet->data);
                    break;
                case ENET_EVENT_TYPE_DISCONNECT:
                    connected=0;
                    printf("You have been disconnected.\n");
                    return 2;
            }
        }

        if (connected) 
        {
            printf("Input: ");
            gets(buffer);

            if (strlen(buffer) == 0) { continue; }

            if (strncmp("q", buffer, BUFFERSIZE) == 0) 
            {
                connected=0;
                enet_peer_disconnect(peer, 0);
                continue;
            } 

            packet = enet_packet_create(buffer, strlen(buffer)+1, ENET_PACKET_FLAG_RELIABLE);
            enet_peer_send(peer, 0, packet);
        }
    }

    enet_host_destroy(client);
}



int main (int argc, char **argv)
{
    char  *user;    		/* user of service */
    char  *host;    		/* host of service */
    char  *port;       		/* service port */
   
    switch (argc) 
    {
        case 4:
            user = argv[1];
            host = argv[2];
            port = argv[3];
            break;

        default:
            fprintf(stderr, "usage: chat <user> <host> <port>\n");
            exit(1);
    }

    // initialize ENet library
    if (enet_initialize () != 0)
    {
        fprintf (stderr, "An error occurred while initializing ENet\n");
        return EXIT_FAILURE;
    }
    atexit (enet_deinitialize);

    // run the chat client
    CHATclient( user, host, port );

    // close down ENet library
    enet_deinitialize();

    exit(0);
}


