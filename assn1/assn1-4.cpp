std::string truncatable(int num) {
	int temp = num;
	if(num == 0) return "none";
	while(temp)
	{
		if(temp%10 == 0) return "none";
		temp /= 10;
	}

	bool check[1000001] = {1, 1, };
	for(int i = 2; i <= num; i++)
	{
		if(check[i] == false)
			for(int j = 2; i*j <= num; j++)
				check[i*j] = true;
	}

	int left = 1, right = 1;
	temp = num;
	while(temp)
	{
		if(check[temp] == true)
		{
			right = 0;
			break;
		}
		temp /= 10;
	}

	temp = num;
	int d;
	for(d = 1; d < temp; d *= 10) ;
	d /= 10;
	while(temp)
	{
		if(check[temp] == true)
		{
			left = 0;
			break;
		}
		temp %= d;
		d /= 10;
	}

	if(left == 1 && right == 1) return "both";
	if(left == 1) return "left";
	if(right == 1) return "right";
	return "none";
}
