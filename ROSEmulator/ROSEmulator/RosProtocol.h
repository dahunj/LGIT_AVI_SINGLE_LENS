#pragma once
#include <string>
#include <vector>


namespace RosProtocol
{
	inline std::vector<std::string> Split(const std::string& s)
	{
		std::vector<std::string> v;

		size_t start = 0, pos;

		while ((pos = s.find(',', start)) != std::string::npos)
		{
			v.push_back(s.substr(start, pos - start));
			start = pos + 1;
		}

		v.push_back(s.substr(start));

		return v;
	}

	inline bool Number(const std::string& s, int low, int high)
	{
		if (s.empty() || s.size() > 6)
			return false;

		int n = 0;

		for (size_t i = 0; i < s.size(); ++i)
		{
			if (s[i] < '0' || s[i] > '9')
				return false;

			n = n * 10 + s[i] - '0';
		}

		return n >= low && n <= high;
	}

	inline bool JudgeRequest(const std::vector<std::string>& v)
	{
		return v.size() == 10 && v[0] == "JUDGE" && v[1] == "REQUEST" && Number(v[5], 1, 3) && Number(v[6], 1, 10) && Number(v[7], 1, 200);
	}

	inline std::string JudgeReply(const std::vector<std::string>& v, const std::string& ip, char judge)
	{
		std::string s = "@JUDGE,REPLY," + ip;

		for (size_t i = 3; i < 10; ++i)
			s += "," + v[i];
		s += ",";
		s += judge;
		s += "\n";

		return s;
	}
}


