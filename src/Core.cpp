//
// Created by Edouard on 29/11/2017.
//

#include <iostream>
#include <sstream>
#include "Core.h"

Core::~Core() = default;

Core::Core(): _state(StateLaunch), _mutex(), _cond(), _queue()
{
    _readFctArray[CmdStart] = &Core::proceedStart;
    _readFctArray[CmdTurn] = &Core::proceedTurn;
    _readFctArray[CmdBegin] = &Core::proceedBegin;
    _readFctArray[CmdBoard] = &Core::proceedBoard;
    _readFctArray[CmdInfo] = &Core::proceedInfo;
    _readFctArray[CmdEnd] = &Core::proceedEnd;
    _readFctArray[CmdAbout] = &Core::proceedAbout;
    _readCmd[CmdStart] = "START";
    _readCmd[CmdTurn] = "TURN";
    _readCmd[CmdBegin] = "BEGIN";
    _readCmd[CmdBoard] = "BOARD";
    _readCmd[CmdInfo] = "INFO";
    _readCmd[CmdEnd] = "END";
    _readCmd[CmdAbout] = "ABOUT";
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
    _board.reset();
    return (_com.sendOk());
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
    if (_board._board[x][y] != Board::EmptyStone)
        return (_com.sendCommand(Communication::CmdError, "Turn: Incorrect position"));
    _board._board[x][y] = Board::TheirStone;
	std::unique_lock<std::mutex> lck(_mutex);
    _queue.push(Point(x, y));
	_cond.notify_one();
    lck.unlock();
    return (0);
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
    if (_brain.putFirstPiece() == -1)
        return (_com.sendCommand(Communication::CmdError, "Begin: Fatal Error of Brain"));
    x = _brain.getLastMoveX();
    y = _brain.getLastMoveY();
    _board._board[x][y] = Board::OurStone;
    return (_com.sendCoord(x, y));
}

int                 Core::proceedBoard(std::stringstream &inputStream)
{
    std::string         str;
    unsigned int        x;
    unsigned int        y;
    char                separator;
    int                 type;

    if (_state == StateStart)
    {
        _state = StateBoard;
        _board.reset();
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
    _lastBoard.x = x;
    _lastBoard.y = y;
    inputStream >> separator >> type;
    if (inputStream.fail() ||separator != ',' || type >= Board::NbTypeStone || type < 0)
        return (_com.sendCommand(Communication::CmdError, "Board: Incorrect arguments"));
    x = _brain.getLastMoveX();
    y = _brain.getLastMoveY();
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
    if (_brain.calculateTurn(_lastBoard.x, _lastBoard.y) == -1)
        return (_com.sendCommand(Communication::CmdError, "Done: Fatal Error of Brain"));
    x = _brain.getLastMoveX();
    y = _brain.getLastMoveY();
    _board._board[x][y] = Board::OurStone;
    return (_com.sendCoord(x, y));
}

int             Core::proceedInfo(std::stringstream &inputStream)
{
    std::string str;

    inputStream >> str;
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

int                     Core::proceedThreadTurn(int x, int y)
{
    if (_brain.calculateTurn(x, y) == -1)
        return (_com.sendCommand(Communication::CmdError, "Turn: Fatal Error of Brain"));
    x = _brain.getLastMoveX();
    y = _brain.getLastMoveY();
    _board._board[x][y] = Board::OurStone;
    return (_com.sendCoord(x, y));
}

int             Core::runAndProceedTurn()
{
    Point    pos;

    while (_state != StateEnd)
    {
		std::unique_lock<std::mutex> lock(_mutex);
        while (_state != StateEnd && _queue.empty())
        {
            _cond.wait(lock);
        }
        if (_state == StateEnd)
            return (0);
        pos = _queue.front();
        proceedThreadTurn(pos.x, pos.y);
        _queue.pop();
        lock.unlock();
    }
	return (0);
}

int             Core::run()
{
    std::thread thrd(&Core::runAndProceedTurn, this);

    while (_state != StateEnd)
    {
        if (readAndProceedCommand() == -1)
        {
            _state = StateEnd;
            _cond.notify_one();
            thrd.join();
            return (-1);
        }
    }
    _cond.notify_one();
    thrd.join();
    return (0);
}
