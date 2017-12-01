//
// Created by Edouard on 30/11/2017.
//

#ifndef GOMOKU_COMMUNICATION_H
#define GOMOKU_COMMUNICATION_H

#include <string>
#include <sstream>

#define NAME_BRAIN "pbrain-LookAtMyBigBrain"
#define VERSION_BRAIN "1.0"
#define AUTHOR_BRAIN "puillandre,ustarroz,sauvau"
#define COUNTRY_BRAIN "France"

class Communication {
public:
    enum commandSent {
        CmdUnknown = 0,
        CmdError,
        CmdMessage,
        CmdDebug,
        NbCommandSent
    };

private:
    std::string _sendCmd[NbCommandSent];
    std::string _input;

public:
    Communication();
    ~Communication();
    int sendCoord(int x, int y) const;
    int sendAbout() const;
    int sendOk() const;
    int sendCommand(commandSent cmd, std::string const &msg) const;
    int readCommand();
    std::string const &getInput() const;
};


#endif //GOMOKU_COMMUNICATION_H
