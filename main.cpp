#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <tuple>
#include <queue>

using namespace std;

using ll = long long;
using vb = vector<bool>;
using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;
using vl = vector<ll>;
using tiii = tuple<int, int, int>;

const auto& dx = vi{ -1,1,0,0,0,0 };
const auto& dy = vi{ 0,0,-1,1,0,0 };
const auto& dz = vi{ 0,0,0,0,-1,1 };

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int m, n, h;
	cin >> m >> n >> h;

	auto tom = vvvi(n, vvi(m, vi(h)));
	auto q = queue<tiii>{};
	for (auto k = 0; k < h; ++k) {
		for (auto i = 0; i < n; ++i) {
			for (auto j = 0; j < m; ++j) {
				cin >> tom[i][j][k];

				if (1 == tom[i][j][k]) {
					q.push({ i, j, k });
				}
			}
		}
	}

	while (!q.empty()) {
		auto f = q.front();
		q.pop();

		const auto& fi = get<0>(f);
		const auto& fj = get<1>(f);
		const auto& fk = get<2>(f);

		for (auto d = 0; d < 6; ++d) {
			const auto& ni = fi + dx[d];
			const auto& nj = fj + dy[d];
			const auto& nk = fk + dz[d];

			if (ni < 0 || n <= ni ||
				nj < 0 || m <= nj ||
				nk < 0 || h <= nk) {
				continue;
			}

			if (-1 == tom[ni][nj][nk]) {
				continue;
			}

			const auto& newDist = tom[fi][fj][fk] + 1;

			if (0 == tom[ni][nj][nk]) {
				tom[ni][nj][nk] = newDist;
				q.push({ ni, nj, nk });
			}
		}
	}

	auto mxDate = int{ 0 };
	auto isDone = bool{ true };
	for (auto i = 0; i < n && isDone; ++i) {
		for (auto j = 0; j < m && isDone; ++j) {
			for (auto k = 0; k < h && isDone; ++k) {
				if (0 == tom[i][j][k]) {
					isDone = false;
					break;
				}

				if (mxDate < tom[i][j][k]) {
					mxDate = tom[i][j][k];
				}
			}
		}
	}

	cout << (isDone ? mxDate - 1 : -1);

	return 0;
}