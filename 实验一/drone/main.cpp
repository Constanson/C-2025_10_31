#include <iostream>
#include <vector>
#include <cassert>
#include <cstdint>
#include <cstdlib>
using namespace std;

class Executor {
public:
    // 构造函数：初始化位置和朝向，默认(0,0,N)
    Executor(int32_t x = 0, int32_t y = 0, char heading = 'N')
        : x_(x), y_(y), heading_(heading) {}

    // 初始化接口
    void initialize(int32_t x, int32_t y, char heading) {
        x_ = x;
        y_ = y;
        heading_ = heading;
    }

    // 执行单个指令
    void execute(char cmd) {
        switch (cmd) {
            case 'M': move(); break;
            case 'L': turnLeft(); break;
            case 'R': turnRight(); break;
            default: break; // 不处理非法命令
        }
    }

    // 批量执行指令
    void executeBatch(const std::vector<char>& commands) {
        for (char cmd : commands) {
            execute(cmd);
        }
    }

    // 查询接口
    void getStatus(int32_t& x, int32_t& y, char& heading) const {
        x = x_;
        y = y_;
        heading = heading_;
    }

private:
    int32_t x_;
    int32_t y_;
    char heading_;

    void move() {
        switch (heading_) {
            case 'N': y_ += 1; break;
            case 'S': y_ -= 1; break;
            case 'E': x_ += 1; break;
            case 'W': x_ -= 1; break;
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
};

//测试函数
void testExecutor() {
    Executor car;

    // 测试初始化
    int32_t x, y; char heading;
    car.getStatus(x, y, heading);
    assert(x == 0 && y == 0 && heading == 'N');

    // 测试初始化接口
    car.initialize(5, 5, 'S');
    car.getStatus(x, y, heading);
    assert(x == 5 && y == 5 && heading == 'S');

    // 测试单条移动
    car.execute('M'); // S -> y-1
    car.getStatus(x, y, heading);
    assert(x == 5 && y == 4 && heading == 'S');

    // 测试左转和右转
    car.execute('L'); // S -> E
    car.getStatus(x, y, heading);
    assert(heading == 'E');

    car.execute('R'); // E -> S
    car.getStatus(x, y, heading);
    assert(heading == 'S');

    // 测试批量指令
    car.initialize(5,5,'S');
    std::vector<char> cmds = {'M', 'M', 'L', 'M', 'R', 'M'};
    car.executeBatch(cmds);
    car.getStatus(x, y, heading);
    assert(x == 6 && y == 2 && heading == 'S');

    cout << "All passed!\n";
}

int main() {
    testExecutor();
    system("pause");
    return 0;
}
