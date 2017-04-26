//
// Created by thomas on 19/04/17.
//

#ifndef PLAZZA_PROCESSWRAPPER_HPP
#define PLAZZA_PROCESSWRAPPER_HPP


class ProcessWrapper {
protected:
    int _pid;
    int _status;

public:
    ProcessWrapper(int pid);
    void setPid(int pid);
    int& getPid();
};


#endif //PLAZZA_PROCESSWRAPPER_HPP
