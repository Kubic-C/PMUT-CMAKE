/*
    PMUT (Porter Multi Use Terminal) is a multi use command line,
    that can do networking, file manipulation, and
    live app manipulation.
    
    PMUT  Copyright (C) 2021 Sawyer Porter

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "headers/commands.h"

namespace hlnet
{
    void add_network_commands()
    {
        std::vector<std::string> args, opts;

        args = { "ip", "port", "c" }, opts = { "ipv", "proto" };
        pmut::data::commands["write to"] = (pmut::command){commands::write_to, args, opts};
    }

    namespace commands
    {
        void write_to()
        {
            pmut::command_gaurd gaurd;
            using namespace pmut::data::cmd_local;

            unsigned int port = 0;
            std::string message = "\000";
            int count = 0;

            try { port = std::stoul(args["port"]), count = std::stoi(args["c"]); } 
            catch(std::exception& x) { pmut::log_err(x.what(), " error", '\n');  return; }           

            asio::io_context context;
            asio::error_code ec;
            
            asio::ip::address ip = 
                asio::ip::address::from_string(args["ip"], ec);

            if(ec.value() != 0)
            {
                pmut::log_err(
                    "failed to convert string ip to ipv6 or ipv4 format\n",
                    "asio reported back with: \n",
                    ec.message(), '\n');
                return;
            }

            asio::ip::tcp::endpoint ep(ip, port);
            asio::ip::tcp::socket socket(context);
            pmut::log_data("connecting...\n");
            socket.connect(ep, ec);
            if(ec.value() != 0)
            {
                pmut::log_err(
                    "could not connect to the ip and port given\n",
                    "asio reported back with: \n",
                    ec.message(), '\n');
                return;
            }

            pmut::log_data("writing to ", args["ip"], " on port ", args["port"], " ", args["c"], " time(s)\n");

            for(int i = 0; i < count; i++)
            {
                socket.write_some(asio::buffer(message.data(), message.size()), ec);
                if(ec.value() != 0)
                {
                    pmut::log_err(
                        "asio error occurred: \n",
                        ec.message()
                    );
                }
            }

            socket.close();
        }
    }
}