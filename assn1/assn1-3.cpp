std::vector<std::string> makeBox(int n) {
	std::vector<std::string> s;

	if(n == 1) s.push_back("#");
	else
	{
		std::string temp, temp2 = "#";
		for(int i = 0; i < n; i++) temp += "#";
		s.push_back(temp);
		for(int i = 0; i < n-2; i++) temp2 += " ";
		temp2 += "#";
		for(int i = 0; i < n-2; i++) s.push_back(temp2);
		s.push_back(temp);
	}
	return s;
}
