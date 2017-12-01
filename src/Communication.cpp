//
// Created by Edouard on 30/11/2017.
//

#include <iostream>
#include "Communication.h"

Communication::Communication()
{
    _sendCmd[CmdUnknown] = "UNKNOWN";
    _sendCmd[CmdError] = "ERROR";
    _sendCmd[CmdMessage] = "MESSAGE";
    _sendCmd[CmdDebug] = "DEBUG";
}

Communication::~Communication()
= default;

int Communication::readCommand()
{
    getline(std::cin, _input);
    return (0);
}

int Communication::sendCommand(commandSent cmd, std::string const &msg) const
{
    std::cout << this->_sendCmd[cmd] << " " << msg << std::endl;
    std::flush(std::cout);
    return (0);
}

int Communication::sendCoord(int x, int y) const
{
    std::cout << x << "," << y << std::endl;
    std::flush(std::cout);
    return (0);
}

int Communication::sendOk() const
{
    std::cout << "OK" << std::endl;
    std::flush(std::cout);
    return (0);
}

int Communication::sendAbout() const
{
    std::cout << "name=\"" << NAME_BRAIN << "\""
              << ", version=\"" << VERSION_BRAIN << "\""
              << ", author=\"" << AUTHOR_BRAIN << "\""
              << ", country=\"" << COUNTRY_BRAIN << "\""
              << std::endl;
    std::flush(std::cout);
    return (0);
}

std::string const &Communication::getInput() const
{
    return (this->_input);
}