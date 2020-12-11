float median(std::vector<int> arr) {
	sort(arr.begin(), arr.end());
	if(arr.size()%2 == 0) return (arr[arr.size()/2-1]+arr[arr.size()/2])/(float)2;
	else return (float)arr[arr.size()/2];
}
