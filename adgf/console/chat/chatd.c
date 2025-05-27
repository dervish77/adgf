/********************************************************
*
* CHAT server program example using the ENet library
*
* File:   chatd.c 
*
* Rev 0   09/14/2012   Originated
*
* Author: Brian Lingard
*
* Usage:  chatd <port>
*
*	where port = numeric name of chat service (ex. 50001)
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


void CHATserver( char *port )
{
    ENetAddress address;
    ENetHost    *server;
    ENetEvent   event;
    ENetPacket  *packet;

    int iPeerCount = 0;
    int portnum = atoi(port);
    int i;
    char buffer[BUFFERSIZE];

    /* Bind the server to the default localhost. */
    /* A specific host address can be specified by */
    /* enet_address_set_host (& address, "x.x.x.x"); */
    address.host = ENET_HOST_ANY;

    /* Bind the server to chat port. */
    address.port = portnum;

    server = enet_host_create (& address /* the address to bind the server host to */,
                                      32 /* allow up to 32 clients and/or outgoing connections */,
                                       2 /* allow up to 2 channels to be used, 0 and 1 */,
                                       0 /* assume any amount of incoming bandwidth */,
                                       0 /* assume any amount of outgoing bandwidth */);
    
    if (server == NULL)
    {
        fprintf (stderr, "An error occurred while trying to create an ENet server host.\n");
        exit(0);
    }

    while (1) 
    {
        while (enet_host_service( server, &event, 1000) > 0)
        {
            switch (event.type)
            {
                case ENET_EVENT_TYPE_CONNECT:
                    printf("server: got ENET_EVENT_TYPE_CONNECT\n"); 
                    break;

                case ENET_EVENT_TYPE_RECEIVE:
                    printf("server: got ENET_EVENT_TYPE_RECEIVE\n"); 
                    if (event.peer->data == NULL)
                    {
                        event.peer->data = malloc(strlen((char*) event.packet->data)+1);
                        strcpy((char*) event.peer->data, (char*) event.packet->data);

                        sprintf(buffer, "%s has connected\n", (char*) event.packet->data);

                        iPeerCount++;

                        packet = enet_packet_create(buffer, strlen(buffer)+1, 0);
                        enet_host_broadcast(server, 1, packet);
                        enet_host_flush(server);
                    }
                    else
                    {
                        for (i = 0; i < iPeerCount; i++)
                        {
                            printf("server: sending to peer %d\n", i);
                            if (&server->peers[i] != event.peer)
                            {
                                sprintf(buffer, "%s: %s", (char*) event.peer->data, (char*) event.packet->data);
                                packet = enet_packet_create(buffer, strlen(buffer)+1, 0);
                                enet_peer_send(&server->peers[i], 0, packet);
                                enet_host_flush(server);
                            }
                            else
                            {
				printf("server: peer error !!\n");
                            }
                        }
                    }
                    break;

                case ENET_EVENT_TYPE_DISCONNECT:
                    printf("server: got ENET_EVENT_TYPE_DISCONNECT\n"); 
                    sprintf(buffer, "%s has disconnected.", (char*) event.peer->data);
                    packet = enet_packet_create(buffer, strlen(buffer)+1, 0);
                    enet_host_broadcast(server, 1, packet);
                    free(event.peer->data);
                    event.peer->data = NULL;
		//    iPeerCount--;
                    break;

                default:
                    printf("server: Tick tock.\n");
                    break;
            }
        }
    }

    enet_host_destroy(server);
}



int main (int argc, char **argv)
{
    char  *host;    		/* host of service */
    char  *port;       		/* service port */
   
    switch (argc) 
    {
        case 2:
            port = argv[1];
            break;

        default:
            fprintf(stderr, "usage: chatd <port>\n");
            exit(1);
    }

    // initialize ENet library
    if (enet_initialize () != 0)
    {
        fprintf (stderr, "An error occurred while initializing ENet\n");
        return EXIT_FAILURE;
    }
    atexit (enet_deinitialize);

    // run the chat server
    printf("CHAT server %s running\n", VERSION);
    CHATserver( port );

    // close down ENet library
    enet_deinitialize();

    exit(0);
}


