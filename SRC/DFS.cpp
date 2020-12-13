#include "../INCLUDES/DFS.h"

DFS::DFS(int w, int h, int m, int *s, int *g)
{
    IsPrintResult = false;

    width = w;
    height = h;
    depthMax = m;
    Goal = Status(w, h);
    Goal.Init(g);

    Start = Status(w, h);
    Start.Init(s);
    Start.depth = 0;
    record = std::list<std::string>();
}

DFS::DFS()
{
    IsPrintResult = false;

    width = 3;
    height = 3;
    depthMax = 10;
    Goal = Status(width, height);
    int a[9] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    Goal.Init(a);

    Start = Status(3, 3);
    Start.Init(a);
    Start.depth = 0;
    record = std::list<std::string>();
}

DFS::~DFS()
{
    open.clear();
    close.clear();
}

bool DFS::IsNew(Status *s)
{

    if (s != nullptr)
    {
        std::string key = s->ToString();
        for (auto i = record.begin(); i != record.end(); i++)
        {
            if (key == *i)
            {
                return false;
            }
        }

        if (!s->IsInClode(close) && !s->IsInOpen(open))
        {
            return true;
        }
    }
    return false;
}

void DFS::Search()
{
    if (Status::CanSolve(&Start, &Goal) == false)
    {
        Util::PrintLine("Sorry Solution Does Not Exist!!!");
        return;
    }
    else
    {
        Util::PrintLine("Yes Solution Does Exist!!!");
    }

    //a) 把初始节点放入Open表中；
    open.push_back(Start);

    record.push_back(Start.ToString());

    int StepCount = 0;
    //b) 如果Open表为空，则问题无解，失败退出；
    while (!open.empty())
    {
        StepCount++;
        //Util::PrintLine("Step: " + Util::Stringfy(i));

        //c) 把Open表的第一个节点取出放入Close表，并标记该节点为n；
        close.push_back(open.front());
        open.pop_front();

        //d) 考察n节点是否为目标节点。如果是，则得到问题的解，成功退出；
        if (close.back().IsGoal(&Goal))
        {
            std::deque<Status> steps = std::deque<Status>();

            Status *current = &close.back();
            while (current->parent != nullptr)
            {
                steps.push_front(*current);
                current = current->parent;
            }

            Util::PrintLine("Solution Found");
            if (IsPrintResult)
            {
                Status::PrintQuery(steps);
            }

            //Util::PrintLine("Move Step: " + Util::Stringfy(StepCount));
            //Goal.Print();
            return;
        }

        if (close.back().depth >= depthMax)
        {
            continue;
        }
        else
        {
            //e) 如果节点n不可扩展，则转第b)步；
            //f) 扩展节点n，计算每一个子节点的f值，并
            //为每个子节点设置指向节点n的指针，将这些子节点放入Open头部中；
            Status *up = close.back().Up();
            if (IsNew(up))
            {
                open.push_front(*up);
                record.push_back(up->ToString());
            }

            Status *down = close.back().Down();
            if (IsNew(down))
            {
                open.push_front(*down);
                record.push_back(down->ToString());
            }

            Status *left = close.back().Left();
            if (IsNew(left))
            {
                open.push_front(*left);
                record.push_back(left->ToString());
            }

            Status *right = close.back().Right();
            if (IsNew(right))
            {
                open.push_front(*right);
                record.push_back(right->ToString());
            }
        }
    }
}

void DFS::SetPrintState(bool v)
{
    IsPrintResult = v;
}