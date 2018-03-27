// 코드 17.1 부분합을 계산하는 함수와 이를 이용해 구간합을 계산하는 함수의 구현

// 주어진 벡터 a의 부분합을 계산한다
vector<int> partialSum(const vector<int>& a) {
	vector<int> ret(a.size());
	ret[0] = a[0];
	for (int i = 1; i < a.size(); ++i)
		ret[i] = ret[i - 1] + a[i];
	return ret;
}

// 어떤 벡터의 부분합 psum[]이 주어질 때, 원래 벡터의 a부터 b까지의 합의 구한다
int rangeSum(const vector<int>& psum, int a, int b) {
	if (a == b)
		return psum[b];
	return psum[b] - psum[a - 1];
}
