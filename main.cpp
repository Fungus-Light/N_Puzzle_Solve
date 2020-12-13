#include "./INCLUDES/Util.h"
#include "./INCLUDES/DFS.h"
#include "./INCLUDES/BFS.h"
#include "./INCLUDES/AStar.h"

int main(int, char **)
{
    Util::PrintLine("*====================*");
    Util::PrintLine("*1: Eight-Puzzle");
    Util::PrintLine("*2: Fifteen-Puzzle");
    Util::PrintLine("*3: M * N ");
    Util::PrintLine("*4: Quit Program");
    Util::PrintLine("*====================*");
    Util::PrintLine("Select Puzzle:");
    int select = -1;

    select = Util::SefeInputInt("Please Input Again: ", 1, 5);

    Util::PrintLine("You Select " + Util::Stringfy(select));

    switch (select)
    {
    case 1:
    {
        Util::PrintLine("*=====Eight-Puzzle=====*");

        int goal[9] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
        int start[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

        Util::PrintLine("Please input 0~8 and seperate them with space: ");

        for (int i = 0; i < 9; i++)
        {
            std::cin >> start[i];
        }

        DFS dfs_eight = DFS(3, 3, 5, start, goal);
        dfs_eight.Start.Print();
        Util::PrintLine("*1-->Use DFS: ");
        dfs_eight.SetPrintState(true);
        dfs_eight.Search();
        Util::PrintLine(" ");
        Util::PrintLine("*2-->Use BFS: ");
        BFS bfs_eight = BFS(3, 3, start, goal);
        bfs_eight.SetPrintState(true);
        bfs_eight.Search();
        Util::PrintLine(" ");
        Util::PrintLine("*3-->Use A*: ");
        AStar astart_eight = AStar(3, 3, 5, start, goal);
        astart_eight.SetPrintState(true);
        astart_eight.Search();
        break;
    }

    case 2:
    {
        Util::PrintLine("*=====Fifteen-Puzzle=====*");

        int goal[16] = {1, 2, 3, 4,
                        5, 6, 7, 8,
                        9, 10, 11, 12,
                        13, 14, 15, 0};
        int start[16] = {0, 0, 0, 0,
                         0, 0, 0, 0,
                         0, 0, 0, 0,
                         0, 0, 0, 0};

        Util::PrintLine("Please input 0~15 and seperate them with space: ");

        for (int i = 0; i < 16; i++)
        {
            std::cin >> start[i];
        }

        DFS dfs = DFS(4, 4, 10, start, goal);
        dfs.Start.Print();
        Util::PrintLine("*1-->Use DFS: ");
        dfs.SetPrintState(true);
        dfs.Search();
        Util::PrintLine(" ");
        Util::PrintLine("*2-->Use BFS: ");
        BFS bfs = BFS(4, 4, start, goal);
        bfs.SetPrintState(true);
        bfs.Search();
        Util::PrintLine(" ");
        Util::PrintLine("*3-->Use A*: ");
        AStar astart = AStar(4, 4, 10, start, goal);
        astart.SetPrintState(true);
        astart.Search();
        break;
    }

    case 3:
    {
        Util::PrintLine("*===== M * N =====*");

        int *start;
        int *goal;

        Util::PrintLine("M means col and N means row ");
        Util::PrintLine("Between 1 ~ 10");
        int col;
        int row;

        Util::PrintLine("Please input M: ");
        col = Util::SefeInputInt("please reinput:", 1, 10);

        Util::PrintLine("Please input N: ");
        row = Util::SefeInputInt("please reinput:", 1, 10);

        Util::PrintLine("col: " + Util::Stringfy(col) + " row: " + Util::Stringfy(row));

        int length = row * col;

        Util::PrintLine("Please input 0~" + Util::Stringfy(length - 1) + " and seperate them with space: ");

        start = new int[length];
        goal = new int[length];

        for (int i = 0; i < length; i++)
        {
            std::cin >> start[i];
        }

        goal[length - 1] = 0;
        for (int i = 0; i < length - 1; i++)
        {
            goal[i] = (i + 1);
        }

        DFS dfs = DFS(col, row, 5, start, goal);
        dfs.Start.Print();
        dfs.Goal.Print();
        Util::PrintLine("*1-->Use DFS: ");
        dfs.SetPrintState(true);
        dfs.Search();
        Util::PrintLine(" ");
        Util::PrintLine("*2-->Use BFS: ");
        BFS bfs = BFS(col, row, start, goal);
        bfs.SetPrintState(true);
        //bfs.Search();
        Util::PrintLine(" ");
        Util::PrintLine("*3-->Use A*: ");
        AStar astart = AStar(col, row, 5, start, goal);
        astart.SetPrintState(true);
        astart.Search();
        break;
    }
    case 4:
    {
        Util::PrintLine("Thank You!!!");
        break;
    }

    default:
    {
        Util::PrintLine("ERR::Something Wrong With The Program!!!");
        return -1;
    }
    }

    return 0;
}
