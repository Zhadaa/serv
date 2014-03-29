/*
 * =====================================================================================
 *
 *       Filename:  server.hh
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  23/03/2014 18:53:52
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <vector>

class Server
{
    public:
        Server(int port);
        ~Server();
        int handle_connection();
        int get_ssock() const;

    private:
        int ssock;
        std::vector<int> cli_s;
};
