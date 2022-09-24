#include <iostream>
#include "Interpreter.h"
using namespace std;

Terminal::Terminal(){
    argv = new char*[MAXORD];
    for (int i = 0; i < MAXORD; i++){
        argv[i] = new char[MAXLINE];
    }
    _init_terminal();
}

char* clean_lb(char* buff){
    int n = strlen(buff);
    while (buff[n - 1] == '\r' || buff[n - 1] == '\n'){
        buff[n - 1] = '\0';
        n--;
    }
    return buff;
}

string clean_head_lb(string inputs){
    while(inputs[0] == ' ' || inputs[0] == '\t' || inputs[0] == '\r'){
        inputs = inputs.substr(1);
    }
    // while(inputs[0] == ' '){
    //     inputs = inputs.substr(1);
    // }
    return inputs;
}

void Terminal::_init_terminal(){
    strcpy(wdir, "/");
    memset(user, 0, sizeof(strin));
    memset(user, 0, sizeof(strout));
    char* buff = new char[MAXLINE];

    strcpy(mach, "a");
    strcpy(root, "a");
    strcpy(user, "a");
    
    // printf("Machine Name: ");
    // fgets(buff, sizeof(buff), stdin);
    // strcpy(mach, clean_lb(buff));
    
    // printf("Root Directory: ");
    // fgets(buff, sizeof(buff), stdin);
    // strcpy(root, clean_lb(buff));
    
    // printf("Login: ");
    // fgets(buff, sizeof(buff), stdin);
    // strcpy(user, clean_lb(buff));

    _orders.push_back("diff");
    _orders.push_back("grep");
    _orders.push_back("tee");
    _orders.push_back("cat");
    _orders.push_back("cp");
    _orders.push_back("cd");
    _orders.push_back("pwd");
    _orders.push_back("echo");
    
    delete []buff;
}

int Terminal::run_terminal(){
    int err_num = 0;
    char* buff = new char[MAXLINE];
    while (err_num == 0){
        printf("\e[92;1m%s@%s\e[0m:\e[94;1m%s\e[0m$ ", user, mach, wdir);
        fgets(buff, sizeof(char) * MAXLINE, stdin);
        clean_lb(buff); // 去除后面的换行符
        parse_orders(buff);
        //memset(buff, 0, MAXLINE);
    }
    delete []buff;
    return err_num;
}

int Terminal::parse_orders(char* buff){
    if (buff == nullptr){
        return 0;
    }
    int pos = -1;
    // cout << "[Info]" << "input: "  << buff << endl;
    std::string inputs = buff;
    std::string order;
    int argc = 0;
    
    inputs = clean_head_lb(inputs);
    // cout << "[Info]" << "input: "  << inputs << endl;
    pos = inputs.find(' ');
    if (pos == -1){ // 只有一个命令行参数
        order = inputs;
    }
    else {
        order = inputs.substr(0, pos); // 第一个为命令
        inputs = inputs.substr(pos + 1); // 后面的是参数
        inputs = clean_head_lb(inputs);
        
        // 拆分inputs
        pos = inputs.find(' ');
        while(pos != -1){ // 不止一个参数
            strcpy(argv[argc], inputs.substr(0, pos).c_str());
            argc++;
            inputs = clean_head_lb(inputs.substr(pos + 1));
            pos = inputs.find(' ');
        }
        strcpy(argv[argc], inputs.c_str());
        argc++;
    }

    // check orders
    // cout << "[Info]"  << "order: " << order << endl;
    // std::cout << "[Info]"  << "param: "  << argc << ' ';
    // for (int i = 0; i < argc; i++){
    //     std::cout << argv[i] << ' ';
    // }
    // std::cout << std::endl;

    // do orders
    // cout << order.c_str() << endl;
    if (strcmp(order.c_str(), "echo") == 0){
        doEcho(argc, argv);
    }
    else{
        cerr << "Command '" << order << "' not found" << endl;
    }

    return 0;
}

void doEcho(int argc, char* argv[]){
    if(argc == 0){
        return; // 没有参数则直接返回
    }
    if(strcmp(argv[0], "--help") == 0){
        cout << "[HELP] func:  echo prints what you input" << endl;
        cout << "       usage: echo [-n] $INPUT" << endl;
        return;
    }
    bool change_line = true;
    int begin = 0;
    if(strcmp(argv[0], "-n") == 0){
        change_line = false; // 不换行
        begin = 1;
    }
    
    for(int i = begin; i < argc; i++){
        std::cout << argv[i];
        if (i != argc - 1){
            std::cout << ' ';
        }
    }
    if(change_line){
        std::cout << std::endl;
    }
    return;
}

void doDiff(int argc, char* argv[]){
    if(argc == 0){
        return; // 没有参数则直接返回
    }
}

