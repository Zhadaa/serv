/*
 * =====================================================================================
 *
 *       Filename:  serv.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  23/03/2014 18:51:13
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
*/

#define MAX_EVENTS 64
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <vector>
#include "server.hh"

Server::Server(int port)
{
    int s_serv = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof (struct sockaddr));
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    bind(s_serv, (struct sockaddr *) &serv_addr, sizeof (serv_addr));
    listen(s_serv, 5);
    fcntl(s_serv, F_SETFL, fcntl(s_serv, F_GETFL, 0) | O_NONBLOCK |
                           SO_REUSEADDR);
    this->ssock = s_serv;
}

Server::~Server()
{
    close(this->ssock);
    for (std::vector<int>::iterator it = this->cli_s.begin();
         it != this->cli_s.end(); ++it)
        close(*it);
}

int Server::get_ssock() const
{
    return this->ssock;
}

int Server::handle_connection()
{
    int epfd = epoll_create1(0);
    struct epoll_event *events;
    struct epoll_event event;
    event.data.fd = this->ssock;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(epfd, EPOLL_CTL_ADD, this->ssock, &event);
    events = (epoll_event *)calloc(MAX_EVENTS, sizeof (event));
   
    while (1)
    {
        int n;
        n = epoll_wait(epfd, events, MAX_EVENTS, -1);
        for (int i = 0; i < n; i++)
        {
            if ((events[i].events & EPOLLERR) ||
                (events[i].events & EPOLLHUP) ||
                (!events[i].events & EPOLLIN))
            {
                //error on fd
                continue;
            }
            else if (this->ssock == events[i].data.fd)
            {
                //Server received one or more connections
                while (1)
                {
                    int s_client = accept(this->ssock, NULL, NULL);
                    if (s_client == -1)
                        break;
                    std::cout << "New client" << std::endl;
                    fcntl(s_client, F_SETFL, fcntl(s_client, F_GETFL, 0) |
                                             O_NONBLOCK);
                    event.data.fd = s_client;
                    event.events = EPOLLIN | EPOLLET;
                    epoll_ctl(epfd, EPOLL_CTL_ADD, s_client, &event);
                    this->cli_s.push_back(s_client);
                }
            }
            else
            {
                //Data received
                int count = 0;
                char buff[512] = "";
                std::string txt = "";
                while (1)
                {
                    count = read(events[i].data.fd, buff, sizeof (buff));

                    if (count == -1 || !count) // End of data
                        break;
                    txt.append(buff, count);
                }
            }
        }
    }
    free(events);
    return 0;
}
