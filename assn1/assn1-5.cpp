std::string isbn13(std::string str) {
	if(str.size() == 13)
	{
		int sum = 0;
		for(int i = 0; i < str.size(); i++)
			sum += (str[i]-'0')*(i%2 == 0 ? 1 : 3);

		if(sum%10 == 0) return "Valid";
		else return "Invalid";
	}

	int sum = 0, mul = 10;
	for(int i = 0; i < str.size()-1; i++)
		sum += (str[i]-'0')*mul--;
	if(str.back() == 'X') sum += 10;
	else sum += str.back()-'0';
	if(sum%11 != 0) return "Invalid";

	str = "978" + str.substr(0, str.size()-1);
	sum = 0;
	for(int i = 0; i < str.size(); i++)
		sum += (str[i]-'0')*(i%2 == 0 ? 1 : 3);
	char last = (10-sum%10) + '0';
	str.push_back(last);
	return str;
}
