/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  Just the main function
 *
 *        Version:  1.0
 *        Created:  23/03/2014 19:30:57
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhada 
 *
 *
 * =====================================================================================
 */
#define NB_CORE 2
#include <string>
#include <boost/thread.hpp>
#include "server.hh"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  Launch the serv on port 8080 and handle connections
 * =====================================================================================
 */

int main(int argc, char *argv[])
{
    Server serv(8080);
    boost::thread_group tg;
    for (int i = 0; i < NB_CORE; i++)
        tg.add_thread(new boost::thread(&Server::handle_connection, &serv));
    tg.join_all();
    return 0;
}				/* ----------  end of function main  ---------- */
