#ifndef EXECUTOR_H
#define EXECUTOR_H
#include <iostream>
#include <vector>
#include <cassert>
#include <cstdint>

class Executor {
public:
    Executor(int32_t x = 0, int32_t y = 0, char heading = 'N', bool isFast = 0 )
        : x_(x), y_(y), heading_(heading), isFast_(isFast){}

    void initialize(int32_t x, int32_t y, char heading, bool isFast) {
        x_ = x;
        y_ = y;
        heading_ = heading;
        isFast_ = isFast;
    }

    // 单条指令执行
    void execute(char cmd) {
       switch (cmd) {
            case 'F': toggleFast(); break;
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

    void getStatus(int32_t& x, int32_t& y, char& heading, bool& isFast) const {
        x = x_;
        y = y_;
        heading = heading_;
        isFast = isFast_;
    }

private:
    int32_t x_, y_;
    char heading_;
    bool isFast_;

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

    void toggleFast() { isFast_ = !isFast_; }


    void doMove() {
       if (!isFast_) {
                moveBackward();
            }
            moveBackward();
        }


    void doLeft() {

            if (!isFast_) {
                moveBackward();
            }
            turnRight();


    }


    void doRight()  {
            if (!isFast_) {
                moveBackward();
            }
            turnLeft();

        }

};

#endif // EXECUTOR_H
