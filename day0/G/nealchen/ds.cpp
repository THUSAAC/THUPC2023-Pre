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
struct Segment {
	Segment() : any(false) {
	}
	Segment(const Segment& that) {
		clone(that);
	}
	Segment(const Segment& left, const Segment& right) {
		merge(left, right);
	}
	void init() {
		any = true;
		vertex_id[0] = graph.add_vertex();
		vertex_id[1] = graph.add_vertex();
	}
	void clone(const Segment& that) {
		if (that.any) {
			init();
			graph.add_edge(vertex_id[0], that.vertex_id[0]);
			graph.add_edge(that.vertex_id[1], vertex_id[1]);
		} else {
			any = false;
		}
	}
	void merge(const Segment& left, const Segment& right) {
		if (left.any | right.any) {
			init();
			if (left.any) {
				graph.add_edge(vertex_id[0], left.vertex_id[0]);
				graph.add_edge(left.vertex_id[1], vertex_id[1]);
			}
			if (right.any) {
				graph.add_edge(vertex_id[0], right.vertex_id[0]);
				graph.add_edge(right.vertex_id[1], vertex_id[1]);
			}
		} else {
			any = false;
		}
	}
	Segment attach(size_t to, size_t from) const {
		Segment ret(*this);
		if (!any) {
			ret.init();
		}
		graph.add_edge(ret.vertex_id[0], to);
		graph.add_edge(from, ret.vertex_id[1]);
		return ret;
	}
	bool any;
	size_t vertex_id[2];
};
struct Node {
	Node* lchild;
	Node* rchild;
	Segment info;
};
struct SegmentTree {
	size_t global_start;
	size_t global_stop;
	size_t n_node;
	Node* nil;
	SegmentTree(size_t start, size_t stop) : global_start(start), global_stop(stop), n_node(0) {
		nil = new Node;
		nil->lchild = nil->rchild = nil;
		nil->info = Segment();
	}
	void query(Node* node, size_t start, size_t stop, size_t q_start, size_t q_stop, std::function<void(const Segment&)> collector) const {
		if (q_stop <= start || stop <= q_start) {
			return;
		}
		if (q_start <= start && stop <= q_stop) {
			collector(node->info);
		} else {
			size_t middle = (start + stop) / 2;
			query(node->lchild, start, middle, q_start, q_stop, collector);
			query(node->rchild, middle, stop, q_start, q_stop, collector);
		}
	}
	void query_suffix(Node* root, size_t q_start, std::function<void(const Segment&)> collector) const {
		query(root, global_start, global_stop, q_start, global_stop, collector);
	}
	Node* modify(Node* node, size_t start, size_t stop, size_t m_start, size_t m_stop, std::function<Segment(const Segment&)> modifier) {
		if (m_stop <= start || stop <= m_start) {
			return node;
		}
		Node* ret = new Node;
		if (m_start <= start && stop <= m_stop) {
			ret->lchild = node->lchild;
			ret->rchild = node->rchild;
			ret->info = modifier(node->info);
		} else {
			size_t middle = (start + stop) / 2;
			ret->lchild = modify(node->lchild, start, middle, m_start, m_stop, modifier);
			ret->rchild = modify(node->rchild, middle, stop, m_start, m_stop, modifier);
			ret->info = Segment(ret->lchild->info, ret->rchild->info);
		}
		return ret;
	}
	Node* modify_single(Node* root, size_t m_pos, std::function<Segment(const Segment&)> modifier) {
		return modify(root, global_start, global_stop, m_pos, m_pos + 1, modifier);
	}
};

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
	SegmentTree tree(0, 4 * n);
	Node* root = tree.nil;
	for (size_t i = 0; i != 4 * n; ++i) {
		int a;
		std::cin >> a;
		--a;
		std::vector<int> &prev = pos[a];
		size_t overlap = vertex_overlap[a];
		size_t disjoint = vertex_disjoint[a];
		std::function<Segment(const Segment&)> to_overlap = [overlap, disjoint](const Segment& node) {
			return node.attach(overlap, disjoint);
		};
		std::function<Segment(const Segment&)> to_disjoint = [overlap, disjoint](const Segment& node) {
			return node.attach(disjoint, overlap);
		};
		std::function<void(const Segment&)> from_overlap = [overlap, disjoint](const Segment& node) {
			if (node.any) {
				graph.add_edge(overlap, node.vertex_id[0]);
				graph.add_edge(node.vertex_id[1], disjoint);
			}
		};
		std::function<void(const Segment&)> from_disjoint = [overlap, disjoint](const Segment& node) {
			if (node.any) {
				graph.add_edge(disjoint, node.vertex_id[0]);
				graph.add_edge(node.vertex_id[1], overlap);
			}
		};
		switch (prev.size()) {
		case 1:
			tree.query_suffix(root, prev[0] + 1, from_disjoint);
			root = tree.modify_single(root, prev[0], to_overlap);
			break;
		case 2:
			tree.query_suffix(root, prev[0] + 1, from_overlap);
			root = tree.modify_single(root, prev[0], to_disjoint);
			break;
		case 3:
			tree.query_suffix(root, prev[1] + 1, from_overlap);
			tree.query_suffix(root, prev[2] + 1, from_disjoint);
			root = tree.modify_single(root, prev[1], to_disjoint);
			root = tree.modify_single(root, prev[2], to_overlap);
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
