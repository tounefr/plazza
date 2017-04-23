//
// Created by thomas on 19/04/17.
//

#ifndef PLAZZA_PROCESSWRAPPER_HPP
#define PLAZZA_PROCESSWRAPPER_HPP


class ProcessWrapper {
private:
    int _pid;

public:
    ProcessWrapper(int pid);
    void setPid(int pid);
    int& getPid();
};


#endif //PLAZZA_PROCESSWRAPPER_HPP
