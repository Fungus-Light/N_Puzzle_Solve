#pragma once
#include "Status.h"
#include<list>

class BFS
{
public:

    bool IsPrintResult;

    int width;
    int height;

    Status Goal;
    Status Start;

    std::deque<Status> open, close;
    std::list<std::string> record;

    void SetPrintState(bool v);

    bool IsNew(Status *s);
    BFS();
    BFS(int w, int h, int *s, int *g);
    ~BFS();
    void Search();
};