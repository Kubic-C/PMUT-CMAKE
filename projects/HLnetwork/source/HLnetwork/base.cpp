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

#include "headers/base.h"

namespace hlnet
{
    void lib_test()
    {
        std::cout << "Library test - HLnetwork\n";
        asio::io_context asio_test;
        asio::error_code ec;
        asio::ip::tcp::endpoint ep(asio::ip::make_address("172.217.2.110", ec), 80);
        std::cout << ec.message() << '\n';

        asio::ip::tcp::socket hello(asio_test);
        hello.connect(ep, ec);
        std::cout << ec.message() << '\n';
        hello.close();
    }
}
