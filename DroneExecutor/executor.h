#ifndef EXECUTOR_H
#define EXECUTOR_H
#include <iostream>
#include <vector>
#include <cassert>
#include <cstdint>

class Executor {
public:
    Executor(int32_t x = 0, int32_t y = 0, char heading = 'N', bool isFast = 0 ,bool isBack = 0)
        : x_(x), y_(y), heading_(heading), isFast_(isFast), isBack_(isBack) {}

    void initialize(int32_t x, int32_t y, char heading, bool isFast, bool isBack) {
        x_ = x;
        y_ = y;
        heading_ = heading;
        isFast_ = isFast;
        isBack_ = isBack;
    }

    // 单条指令执行
    void execute(char cmd) {
        if (lastCmdWasT && cmd == 'R') {
            // 执行 TR 掉头指令
            doTurnRound();
            lastCmdWasT = false;
            return;
        }

        lastCmdWasT = (cmd == 'T'); // 记录 T，等待下一个是否是 R

        switch (cmd) {
            case 'F': toggleFast(); break;
            case 'B': toggleBack();  break;
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

    void getStatus(int32_t& x, int32_t& y, char& heading, bool& isFast, bool& isBack) const {
        x = x_;
        y = y_;
        heading = heading_;
        isFast = isFast_;
        isBack = isBack_;
    }

private:
    int32_t x_, y_;
    char heading_;
    bool isFast_;
    bool isBack_;
    bool lastCmdWasT = false;

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
    void toggleBack() { isBack_ = !isBack_; }


    void doMove() {
        if (!isBack_) {
            if (!isFast_) {
                moveForward();
            }
            moveForward();
        } else {
            if (!isFast_) {
                moveBackward();
            }
            moveBackward();
        }
    }

    void doLeft() {
        if (!isBack_) {
            if (!isFast_) {
                moveForward();
            }
            turnLeft();
        } else {
            if (!isFast_) {
                moveBackward();
            }
            turnRight();

        }
    }


    void doRight() {
        if (!isBack_) {
            if (!isFast_) {
                moveForward();
            }
            turnRight();
        } else {
            if (!isFast_) {
                moveBackward();
            }
            turnLeft();

        }
    }


    void doTurnRound() {
        if (!isFast_) {
            turnLeft();
            moveForward();
            turnLeft();
        } else {
            moveForward();
            turnLeft();
            moveForward();
            turnLeft();
        }
    }
};

#endif // EXECUTOR_H
