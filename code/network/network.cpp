#include "network.hpp"
#include <iostream>
#include <stdint.h>
#include "network_connection.hpp"


namespace Network {


namespace
{
  ENetAddress address;
  ENetHost *host = nullptr;
  ENetPeer *peer = nullptr;
}


bool
setup_network()
{
  if(enet_initialize())
  {
    std::cout << "Failed setting up network" << std::endl;
    return false;
  }

  return true;
}


bool
setup_as_client()
{
  host = enet_host_create(NULL, 1, 2, 57600 / 8, 14400 / 8);

  if(!host)
  {
    std::cout << "Failed to setup client" << std::endl;
    return false;
  }

  return true;
}


bool
setup_as_server()
{
  address.host = ENET_HOST_ANY;
  address.port = 1234;
  host = enet_host_create(&address, 4, 2 ,0, 0);

  if(!host)
  {
    std::cout << "Failed setting up server" << std::endl;
    return false;
  }

  return true;
}


bool
connect_to_server(const char *str)
{
  enet_address_set_host (& address, str);
  address.port = 1234;
  /* Initiate the connection, allocating the two channels 0 and 1. */
  peer = enet_host_connect (host, & address, 2, 0);    
  if (peer == NULL)
  {
     std::cout << "No available peers for initiating an ENet connection." << std::endl;
     return false;
  }  

  ENetEvent event;
  /* Wait up to 5 seconds for the connection attempt to succeed. */
  if (enet_host_service (host, & event, 5000) > 0 &&
      event.type == ENET_EVENT_TYPE_CONNECT)
  {
     std::cout << "Connected" << std::endl;
     return true;
  }
  else
  {
      /* Either the 5 seconds are up or a disconnect event was */
      /* received. Reset the peer in the event the 5 seconds   */
      /* had run out without any significant event.            */
      enet_peer_reset (peer);
      std::cout << "Failed" << std::endl;
      return false;
  }
  
  return false;
}


void
poll_events()
{
  std::cout << "Ping" << std::endl;

  ENetEvent event;
  /* Wait up to 1000 milliseconds for an event. */
  while (enet_host_service (host, & event, 0) > 0)
  {
      switch (event.type)
      {
      case ENET_EVENT_TYPE_CONNECT:
          printf ("A new client connected from %x:%u.\n", 
                  event.peer -> address.host,
                  event.peer -> address.port);
          /* Store any relevant client information here. */
          event.peer -> data = nullptr;
          peer = event.peer;

          // reply
          {
            if(peer)
            {
              send_unrel_packet();
            }
          }
          
          break;
      case ENET_EVENT_TYPE_RECEIVE:
          //printf ("A packet of length %u containing %s was received from %s on channel %u.\n",
          //        event.packet -> dataLength,
          //        event.packet -> data,
          //        event.peer -> data,
          //        event.channelID);
          std::cout << *reinterpret_cast<uint32_t*>(event.packet->data) << std::endl;

          /* Clean up the packet now that we're done using it. */
          enet_packet_destroy (event.packet);
          
          break;
         
      case ENET_EVENT_TYPE_DISCONNECT:
          printf ("%s disconnected.\n", event.peer -> data);
          /* Reset the peer's client information. */
          event.peer -> data = NULL;
      }
  }
}


bool
send_rel_packet()
{
  uint32_t i = 987;

  ENetPacket * packet = nullptr;
  packet = enet_packet_create(&i, sizeof(i), ENET_PACKET_FLAG_RELIABLE);

  enet_peer_send(peer, 0, packet);

  return true;
}


bool
send_unrel_packet()
{
  uint32_t i = 456;

  ENetPacket * packet = nullptr;
  packet = enet_packet_create(&i, sizeof(i), ENET_PACKET_FLAG_UNSEQUENCED);

  enet_peer_send(peer, 0, packet);

  return true;
}


void
destroy_network()
{
  enet_host_destroy(host);
}


} // ns