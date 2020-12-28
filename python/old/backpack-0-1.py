v = 10
w = [0, 1, 2, 3, 4, 5, 6]
m = [0, 6, 5, 4, 3, 2, 1]

dp = [[0 for j in range(11)] for i in range(7)]
for i in range(1, 7):
	for j in range(1, 11):
		if w[i] > j:
			dp[i][j] = dp[i - 1][j]
		else:
			nex = dp[i - 1][j - w[i]] + m[i]
			dp[i][j] = nex if nex > dp[i - 1][j] else dp[i - 1][j]
print(dp[6][10])

print()
for row in dp:
	print(row)
