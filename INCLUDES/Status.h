#pragma once
#include <deque>
#include <utility>
#include <vector>
#include "./Util.h"
#include <cmath>

class Status
{
public:
    ///宽度
    int width;
    ///高度
    int height;
    ///存储数据
    std::vector<std::vector<int>> data;

    ///长度
    int length;

    ///深度
    int depth;

    Status *parent;

    Status();
    Status(int w, int h);
    ~Status();

    ///初始化一个状态，使用一维数组或者其他状态的数据
    void Init(int *rawdata);
    void Init(std::vector<std::vector<int>> otherdata);
    ///获得0所在的位置
    std::pair<int, int> GetZeroPosition();
    ///获得某个数字所在位置
    std::pair<int, int> GetNumPosition(int n);

    ///转化为字符串
    std::string ToString();
    ///获得往上方向的子节点
    Status *Up();
    ///获得往下方向的子节点
    Status *Down();
    ///获得往左方向的子节点
    Status *Left();
    ///获得往右方向的子节点
    Status *Right();

    ///判断两个状态是否一致
    bool Equal(Status *other);
    ///判断是否为目标
    bool IsGoal(Status *goal);
    ///判断是否再打开列表
    bool IsInOpen(std::deque<Status> &open);
    ///判断是否在关闭表
    bool IsInClode(std::deque<Status> &close);

    ///转换为一行数据
    int *ToArray();

    ///矩阵方式打印整个状态
    void Print();

    ///获得A* 启发值
    static int AStartValue(Status* current,Status* goal);

    ///打印一个队列
    static void PrintQuery(std::deque<Status> &query);

    ///判断是是否可解
    static bool CanSolve(Status *start, Status *goal);
};
