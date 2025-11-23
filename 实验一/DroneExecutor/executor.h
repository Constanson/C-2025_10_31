#ifndef EXECUTOR_H
#define EXECUTOR_H
#include <iostream>
#include <vector>
#include <cassert>
#include <cstdint>

class Executor {
public:
    Executor(int32_t x = 0, int32_t y = 0, char heading = 'N')
        : x_(x), y_(y), heading_(heading){}

    void initialize(int32_t x, int32_t y, char heading) {
        x_ = x;
        y_ = y;
        heading_ = heading;
    }

    // 单条指令执行
    void execute(char cmd) {
        switch (cmd) {
            case 'M': doMove();      break;
            case 'L': doLeft();      break;
            case 'R': doRight();     break;

            default: break;
        }
    }

    void executeBatch(const std::vector<char>& commands) {
        for (char cmd : commands)
            execute(cmd);
    }

    void getStatus(int32_t& x, int32_t& y, char& heading) const {
        x = x_;
        y = y_;
        heading = heading_;
    }

private:
    int32_t x_, y_;
    char heading_;

    void moveForward() {
        switch (heading_) {
            case 'N': y_ += 1; break;
            case 'S': y_ -= 1; break;
            case 'E': x_ += 1; break;
            case 'W': x_ -= 1; break;
        }
    }

    void moveBackward() {
        switch (heading_) {
            case 'N': y_ -= 1; break;
            case 'S': y_ += 1; break;
            case 'E': x_ -= 1; break;
            case 'W': x_ += 1; break;
        }
    }

    void turnLeft() {
        switch (heading_) {
            case 'N': heading_ = 'W'; break;
            case 'W': heading_ = 'S'; break;
            case 'S': heading_ = 'E'; break;
            case 'E': heading_ = 'N'; break;
        }
    }

    void turnRight() {
        switch (heading_) {
            case 'N': heading_ = 'E'; break;
            case 'E': heading_ = 'S'; break;
            case 'S': heading_ = 'W'; break;
            case 'W': heading_ = 'N'; break;
        }
    }

    void doMove() {
        moveBackward();
    }


    void doLeft() {
        turnRight();
    }


    void doRight()  {
        turnLeft();
    }
};

#endif // EXECUTOR_H
