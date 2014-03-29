/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
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

#include "server.hh"
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */

int main(int argc, char *argv[])
{
    Server serv(8080);
    serv.handle_connection();
    return 0;
}				/* ----------  end of function main  ---------- */
