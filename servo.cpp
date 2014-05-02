#include "servo.h"
using namespace QArduino;

Servo::Servo(Arduino *board) : m_board(board), m_min(544), m_max(2400)
{

}

Servo::~Servo()
{
    delete m_board;
}

void Servo::setBoard(Arduino *board)
{
    m_board = board;
}

Arduino* Servo::board()
{
    return m_board;
}

void Servo::setMin(int)
{

}

void Servo::setMax(int)
{

}

void Servo::attach(const AnalogWritePin &pin)
{
    if(m_board == NULL)
    {
        emit error("Servo is not attached to any board.");
    }
}
