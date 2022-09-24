#include <cstring>
#include <string>
#include <vector>

class Terminal {
public:
    Terminal();
    int run_terminal();
    int parse_orders(char* buff);
    char** argv;
private:
    void _init_terminal();
    std::vector<std::string> command_line;
    std::vector<std::string> _orders;

    const static int MAXORD = 16;
    const static int MAXLINE = 4096;
    const static int MAXFILE = 4096;
    char user[MAXLINE]; // 用户名
    char mach[MAXLINE]; // 计算机名
    char root [MAXLINE]; // 根目录
    char wdir [MAXLINE]; // 工作目录
    char strin[MAXFILE]; // 重定向标准输入
    char strout[MAXFILE]; // 重定向标准输出
};

class Interpreter {
    private:
};

void doEcho(int argc, char* argv[]);
