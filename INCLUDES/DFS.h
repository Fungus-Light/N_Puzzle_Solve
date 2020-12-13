#pragma once
#include "Status.h"
#include <list>

class DFS
{

public:

    bool IsPrintResult;

    int width;
    int height;
    int depthMax;

    Status Goal;
    Status Start;

    std::deque<Status> open, close;

    std::list<std::string> record;

    void SetPrintState(bool v);

    bool IsNew(Status *s);
    DFS();
    DFS(int w, int h, int m, int *s, int *g);
    ~DFS();
    void Search();
};