#pragma once
#include "Status.h"
#include <list>

class AStar
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

    void InsertOpen(Status* s);

    bool IsNew(Status *s);
    AStar();
    AStar(int w, int h,int m, int *s, int *g);
    ~AStar();
    void Search();
};