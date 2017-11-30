//
// Created by Edouard on 29/11/2017.
//

#include <iostream>
#include <sstream>
#include "Core.h"

Core::~Core() = default;

Core::Core()
{
    this->_readFctArray[CmdStart] = &Core::proceedStart;
    this->_readFctArray[CmdTurn] = &Core::proceedTurn;
    this->_readFctArray[CmdBegin] = &Core::proceedBegin;
    this->_readFctArray[CmdBoard] = &Core::proceedBoard;
    this->_readFctArray[CmdInfo] = &Core::proceedInfo;
    this->_readFctArray[CmdEnd] = &Core::proceedEnd;
    this->_readFctArray[CmdAbout] = &Core::proceedAbout;
    this->_readCmd[CmdStart] = "START";
    this->_readCmd[CmdTurn] = "TURN";
    this->_readCmd[CmdBegin] = "BEGIN";
    this->_readCmd[CmdBoard] = "BOARD";
    this->_readCmd[CmdInfo] = "INFO";
    this->_readCmd[CmdEnd] = "END";
    this->_readCmd[CmdAbout] = "ABOUT";
    this->_state = StateLaunch;
}

int     Core::proceedStart(std::stringstream &inputStream)
{
    int width;

    inputStream >> width;
    if (inputStream.fail())
        return (_com.sendCommand(Communication::CmdError, "Start: Incorrect arguments"));
    else if (width != WIDTH_BOARD)
        return (_com.sendCommand(Communication::CmdError, "Start: Incorrect width or height"));
    _state = StateStart;
    this->_board.clear();
    return (this->_com.sendOk());
}

int     Core::proceedTurn(std::stringstream &inputStream)
{
    int x;
    int y;
    char separator;

    if (_state == StateStart)
        _state = StateInGame;
    else if (_state != StateInGame)
        return (_com.sendCommand(Communication::CmdError, "Turn: Never Received START"));
    inputStream >> x >> separator >> y;
    if (inputStream.fail() || separator != ',')
        return (_com.sendCommand(Communication::CmdError, "Turn: Incorrect arguments"));
    else if (x < 0 || x >= 19 || y < 0 || y >= 19)
        return (_com.sendCommand(Communication::CmdError, "Turn: Incorrect value"));
    if (this->_board._board[x][y] != Board::EmptyStone)
        return (_com.sendCommand(Communication::CmdError, "Turn: Incorrect position"));
    this->_board._board[x][y] = Board::TheirStone;
    if (this->_brain.calculateTurn(x, y) == -1)
        return (_com.sendCommand(Communication::CmdError, "Turn: Fatal Error of Brain"));
    x = this->_brain.getLastMoveX();
    y = this->_brain.getLastMoveY();
    _board._board[x][y] = Board::OurStone;
    return (_com.sendCoord(x, y));
}

int             Core::proceedBegin(std::stringstream &inputStream)
{
    std::string str;
    int         x;
    int         y;

    if (_state != StateStart)
        return (_com.sendCommand(Communication::CmdError, "Begin: Never Received START"));
    _state = StateInGame;
    inputStream >> str;
    if (!str.empty())
        return (_com.sendCommand(Communication::CmdError, "Begin: Incorrect arguments"));
    if (this->_brain.putFirstPiece() == -1)
        return (_com.sendCommand(Communication::CmdError, "Begin: Fatal Error of Brain"));
    x = this->_brain.getLastMoveX();
    y = this->_brain.getLastMoveY();
    _board._board[x][y] = Board::OurStone;
    return (_com.sendCoord(x, y));
}

int                 Core::proceedBoard(std::stringstream &inputStream)
{
    std::string         str;
    int                 x;
    int                 y;
    char                separator;
    int                 type;

    if (_state == StateStart)
    {
        _state = StateBoard;
        _board.clear();
        _brain.clear();
        return (0);
    }
    else if (_state != StateBoard)
        return (_com.sendCommand(Communication::CmdError, "Board: Never Received START"));
    inputStream >> str;
    if (str == "DONE")
        return (proceedDone());
    inputStream = std::stringstream(str);
    inputStream >> x >> separator >> y;
    if (inputStream.fail())
        return (_com.sendCommand(Communication::CmdError, "Board: Incorrect arguments"));
    else if (separator != ',')
        return (_com.sendCommand(Communication::CmdError, "Board: Incorrect arguments"));
    _lastBoardX = x;
    _lastBoardY = y;
    inputStream >> separator >> type;
    if (inputStream.fail() ||separator != ',' || type >= Board::NbTypeStone || type < 0)
        return (_com.sendCommand(Communication::CmdError, "Board: Incorrect arguments"));
    x = this->_brain.getLastMoveX();
    y = this->_brain.getLastMoveY();
    _board._board[x][y] = static_cast<Board::TypeStone>(type);
    if (_brain.putBoardPiece(x, y, static_cast<Board::TypeStone>(type)))
        return (_com.sendCommand(Communication::CmdError, "Board: Fatal Error of Brain"));
    return (0);
}

int Core::proceedDone()
{
    int x;
    int y;

    _state = StateInGame;
    if (this->_brain.calculateTurn(_lastBoardX, _lastBoardY) == -1)
        return (_com.sendCommand(Communication::CmdError, "Done: Fatal Error of Brain"));
    x = this->_brain.getLastMoveX();
    y = this->_brain.getLastMoveY();
    _board._board[x][y] = Board::OurStone;
    return (_com.sendCoord(x, y));
}

int             Core::proceedInfo(std::stringstream &inputStream)
{
    std::string str;

    inputStream >> str;
    if (!str.empty())
        return (_com.sendCommand(Communication::CmdError, "Info: Incorrect arguments"));
    return (0);
}

int             Core::proceedEnd(std::stringstream &inputStream)
{
    std::string str;

    inputStream >> str;
    if (!str.empty())
        return (_com.sendCommand(Communication::CmdError, "End: Incorrect arguments"));
    _state = StateEnd;
    return (0);
}

int             Core::proceedAbout(std::stringstream &inputStream)
{
    std::string str;

    inputStream >> str;
    if (!str.empty())
        return (_com.sendCommand(Communication::CmdError, "About: Incorrect arguments"));
    return (_com.sendAbout());
}

int                     Core::readAndProceedCommand()
{
    std::string         input;
    std::string         cmd;
    std::stringstream   inputStream;

    _com.readCommand();
    input = _com.getInput();
    inputStream = std::stringstream(input);
    if (_state == StateBoard)
    {
        return ((this->*_readFctArray[CmdBoard])(inputStream));
    }
    inputStream >> cmd;
    if (cmd.empty())
    {
        return (_com.sendCommand(Communication::CmdError, "No Command"));
    }
    for (int i = 0; i < NbCommandRead; i++)
    {
        if (cmd == _readCmd[i])
        {
            return ((this->*_readFctArray[i])(inputStream));
        }
    }
    return (_com.sendCommand(Communication::CmdUnknown, "Unknown command"));
}

int Core::run()
{
    while (_state != StateEnd)
    {
        if (readAndProceedCommand() == -1)
            return (-1);
    }
    return (0);
}