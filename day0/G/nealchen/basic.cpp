#include <bits/stdc++.h>
struct Graph {
	size_t n_vertex;
	std::vector<std::vector<size_t>> adj;
	void clear() {
		n_vertex = 0;
		adj.clear();
	}
	size_t add_vertex() {
		adj.push_back({});
		return n_vertex++;
	}
	void add_edge(size_t u, size_t v) {
		adj[u].push_back(v);
	}
};
struct SCC {
	size_t scc_cnt;
	std::vector<size_t> scc_id;
};
class SCCTarjanAlgorithm : public SCC {
	const Graph* graph_;
	size_t clock_;
	std::vector<size_t> dfn_;
	std::vector<size_t> low_;
	std::vector<char> vis_;
	std::vector<size_t> stack_;
	std::vector<char> in_stack_;
	void dfs(size_t u) {
		vis_[u] = true;
		dfn_[u] = low_[u] = clock_++;
		stack_.push_back(u);
		in_stack_[u] = true;
		for (size_t v : graph_->adj[u]) {
			if (!vis_[v]) {
				dfs(v);
				low_[u] = std::min(low_[u], low_[v]);
			} else if (in_stack_[v]) {
				low_[u] = std::min(low_[u], dfn_[v]);
			}
		}
		if (dfn_[u] == low_[u]) {
			size_t v;
			do {
				v = stack_.back();
				stack_.pop_back();
				scc_id[v] = scc_cnt;
				in_stack_[v] = false;
			} while (v != u);
			++scc_cnt;
		}
	}
public:
	SCCTarjanAlgorithm(const Graph& graph) : graph_(&graph) {
		size_t n_vertex = graph_->n_vertex;
		scc_cnt = 0;
		scc_id.resize(n_vertex);
		clock_ = 0;
		dfn_.resize(n_vertex);
		low_.resize(n_vertex);
		vis_.assign(n_vertex, false);
		stack_.clear();
		in_stack_.assign(n_vertex, false);
		for (size_t i = 0; i != n_vertex; ++i) {
			if (!vis_[i]) {
				dfs(i);
			}
		}
	}
};

Graph graph;
std::multimap<int, int> where;
void exclude(int left, int var) {
	for (auto it = where.emplace(left, var); it != where.end(); ++it) {
		if (it->first > left) {
			graph.add_edge(it->second, var^1);
			graph.add_edge(var, it->second^1);
		}
	}
}
int main() {
	size_t n;
	std::cin >> n;
	std::vector<std::vector<int>> pos(n);
	std::vector<int> vertex_overlap(n);
	std::vector<int> vertex_disjoint(n);
	for (size_t i = 0; i != n; ++i) {
		vertex_overlap[i] = graph.add_vertex();
		vertex_disjoint[i] = graph.add_vertex();
	}
	for (size_t i = 0; i != 4 * n; ++i) {
		int a;
		std::cin >> a;
		--a;
		std::vector<int> &prev = pos[a];
		size_t t = vertex_overlap[a];
		size_t f = vertex_disjoint[a];
		switch (prev.size()) {
		case 1:
			exclude(prev[0], f);
			break;
		case 2:
			exclude(prev[0], t);
			break;
		case 3:
			exclude(prev[1], t);
			exclude(prev[2], f);
			break;
		}
		prev.push_back(i);
	}
	SCCTarjanAlgorithm scc(graph);
	for (size_t i = 0; i != n; ++i) {
		if (scc.scc_id[vertex_overlap[i]] == scc.scc_id[vertex_disjoint[i]]) {
			std::cout << "No" << std::endl;
			exit(0);
		}
	}
	std::string ans(4 * n, '0');
	for (size_t i = 0; i != n; ++i) {
		ans[pos[i][3]] = '1';
		if (scc.scc_id[vertex_overlap[i]] < scc.scc_id[vertex_disjoint[i]]) {
			ans[pos[i][2]] = '1';
		} else {
			ans[pos[i][1]] = '1';
		}
	}
	std::cout << "Yes\n" << ans << std::endl;
}
