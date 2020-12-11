int diceRoll(int n, int outcome) {
	int dp[1000][1000] = { 0 };
	for(int i = 1; i <= 6; i++)
		dp[1][i] = 1;
  	for(int i = 2; i <= n; i++)
      	dp[i][i] = 1;

	for(int i = 2; i <= n; i++)
	{
		for(int j = i+1; j <= outcome; j++)
			for(int k = 1; j-k > 0 && k <= 6; k++)
				dp[i][j] += dp[i-1][j-k];
	}

	return dp[n][outcome];
}
