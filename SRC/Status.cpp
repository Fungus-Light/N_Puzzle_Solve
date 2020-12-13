#include "../INCLUDES/Status.h"

Status::Status()
{
	width = 0;
	height = 0;
	data = std::vector<std::vector<int>>();
	length = 0;
	depth = 0;
	parent = nullptr;
}

Status::Status(int w, int h)
{
	this->width = w;
	this->height = h;
	this->data = std::vector<std::vector<int>>();

	this->length = width * height;
	parent = nullptr;
	depth = 0;
}

Status::~Status()
{
	for (auto i = data.begin(); i < data.end(); i++)
	{
		i->clear();
	}
	data.clear();
}

void Status::Init(int *rawdata)
{
	int index = 0;
	for (int h = 0; h < height; h++)
	{
		std::vector<int> vw = std::vector<int>();
		for (int w = 0; w < width; w++)
		{
			vw.push_back(rawdata[index]);
			//std::cout << rawdata[index];
			index++;
		}
		data.push_back(vw);
	}
}

void Status::Init(std::vector<std::vector<int>> otherdata)
{
	for (int h = 0; h < height; h++)
	{
		std::vector<int> vw = std::vector<int>();
		for (int w = 0; w < width; w++)
		{
			vw.push_back(0);
		}
		data.push_back(vw);
	}

	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			data[h][w] = otherdata[h][w];
		}
	}
}

std::pair<int, int> Status::GetZeroPosition()
{
	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			if (data[h][w] == 0)
			{
				return std::pair<int, int>(w, h);
			}
		}
	}
	return std::pair<int, int>(-1, -1);
}

std::string Status::ToString()
{
	std::string result = "";
	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			result += std::to_string(data[h][w]);
		}
	}
	return result;
}

Status *Status::Up()
{
	std::pair<int, int> pos = GetZeroPosition();
	if (pos.second > 0)
	{
		Status *child = new Status(width, height);

		child->Init(data);
		int w = pos.first;
		int h = pos.second;

		int temp = child->data[h][w];
		child->data[h][w] = child->data[h - 1][w];
		child->data[h - 1][w] = temp;
		child->parent = this;

		return child;
	}
	else
	{
		return nullptr;
	}
	return nullptr;
}

Status *Status::Down()
{
	std::pair<int, int> pos = GetZeroPosition();
	if (pos.second < (height - 1))
	{
		Status *child = new Status(width, height);

		child->Init(data);
		int w = pos.first;
		int h = pos.second;
		int temp = child->data[h][w];
		child->data[h][w] = child->data[h + 1][w];
		child->data[h + 1][w] = temp;
		child->parent = this;

		return child;
	}
	else
	{
		return nullptr;
	}
	return nullptr;
}

Status *Status::Left()
{
	std::pair<int, int> pos = GetZeroPosition();
	if (pos.first > 0)
	{
		Status *child = new Status(width, height);

		child->Init(data);
		int w = pos.first;
		int h = pos.second;
		int temp = child->data[h][w];
		child->data[h][w] = child->data[h][w - 1];
		child->data[h][w - 1] = temp;
		child->parent = this;

		return child;
	}
	else
	{
		return nullptr;
	}
	return nullptr;
}

Status *Status::Right()
{
	std::pair<int, int> pos = GetZeroPosition();
	if (pos.first < (width - 1))
	{
		Status *child = new Status(width, height);

		child->Init(data);
		int w = pos.first;
		int h = pos.second;

		int temp = child->data[h][w];
		child->data[h][w] = child->data[h][w + 1];
		child->data[h][w + 1] = temp;
		child->parent = this;

		return child;
	}
	else
	{
		return nullptr;
	}
	return nullptr;
}

bool Status::Equal(Status *other)
{
	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			if (data[h][w] != other->data[h][w])
			{
				return false;
			}
		}
	}
	return true;
}

bool Status::IsGoal(Status *goal)
{
	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			if (data[h][w] != goal->data[h][w])
			{
				return false;
			}
		}
	}
	return true;
}

bool Status::IsInOpen(std::deque<Status> &open)
{
	for (auto i = open.begin(); i < open.end(); i++)
	{
		if (i->Equal(this))
		{
			return true;
		}
	}
	return false;
}

bool Status::IsInClode(std::deque<Status> &close)
{
	for (auto i = close.begin(); i < close.end(); i++)
	{
		if (i->Equal(this))
		{
			return true;
		}
	}
	return false;
}

void Status::Print()
{
	Util::PrintLine("");
	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			std::cout << data[h][w] << " ";
		}
		Util::PrintLine("");
	}
}

void Status::PrintQuery(std::deque<Status> &query)
{
	for (auto i = query.begin(); i < query.end(); i++)
	{
		i->Print();
	}
}

int *Status::ToArray()
{
	int index = 0;
	int *result = new int[length];
	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			result[index] = data[h][w];
			index++;
		}
	}
	return result;
}

bool Status::CanSolve(Status *start, Status *goal)
{
	int *start_raw = start->ToArray();
	int *goal_raw = goal->ToArray();

	int nlength = start->length - 1;

	int *s = new int[nlength];
	int *g = new int[nlength];

	//分别给开始和目标的一维数组 去除0
	int s_index = 0;
	for (int i = 0; i < start->length; i++)
	{
		if (start_raw[i] != 0)
		{
			s[s_index] = start_raw[i];
			s_index++;
		}
	}

	int g_index = 0;
	for (int i = 0; i < goal->length; i++)
	{
		if (goal_raw[i] != 0)
		{
			g[g_index] = goal_raw[i];
			g_index++;
		}
	}

	// Util::PrintLine("Show Array ");
	// Util::PrintArray(start_raw,start->length);
	// Util::PrintArray(goal_raw,goal->length);

	// Util::PrintLine("Show Array Without Zero");
	// Util::PrintArray(s,nlength);
	// Util::PrintArray(g,nlength);

	//开始统计逆序数对
	int s_RNum = 0;
	int g_RNum = 0;

	for (int i = 0; i < nlength; i++)
	{

		for (int k = 0; k < i; k++)
		{
			if (s[k] > s[i])
			{
				s_RNum++;
			}

			if (g[k] > g[i])
			{
				g_RNum++;
			}
		}
	}

	//开始判断是否有解

	//这里实际上可解性由列数和逆序对个数共同决定
	//列数极为width
	//行步数为空格的距离
	if (start->width % 2 == 0)
	{
		//列数为偶数
		//如果逆序数对数量奇偶性一致且空格距离为偶数
		//或者逆序数对数量奇偶性不一致且空格距离为奇数
		//这两种情况才有解

		//求空格距离
		int spaceDis = start->GetZeroPosition().second - goal->GetZeroPosition().second;
		spaceDis = abs(spaceDis);

		if (s_RNum % 2 == g_RNum % 2)
		{
			if (spaceDis % 2 == 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			if (spaceDis % 2 == 0)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	}
	else
	{
		//列数为奇数
		//与八数码的判定一样
		if (s_RNum % 2 == g_RNum % 2)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

std::pair<int, int> Status::GetNumPosition(int n)
{
	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			if (data[h][w] == n)
			{
				return std::pair<int, int>(w, h);
			}
		}
	}
	return std::pair<int, int>(-1, -1);
}

int Status::AStartValue(Status *current, Status *goal)
{

	//这里使用曼哈顿距离之和作为启发数值

	int Count = 0;
	Count += current->depth;

	for (int i = 0; i < current->length; i++)
	{
		std::pair<int, int> c_p = current->GetNumPosition(i);
		std::pair<int, int> g_p = goal->GetNumPosition(i);
		Count += (abs(c_p.first - g_p.first) + abs(c_p.second - g_p.second));
	}

	return Count;
}