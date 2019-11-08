#pragma once

#include <queue>
#include <set>
#include "BaseTreeNode.h"

using std::priority_queue;
using std::set;

typedef unsigned char byte;
typedef vector<vector<byte>> matrix;

namespace AStar {

	struct TreeNode : BaseTreeNode {
		byte distanceFromStart = 0;

		TreeNode(matrix m) : BaseTreeNode(m), distanceFromStart(0) {}

		TreeNode(matrix m, TreeNode* parent) : BaseTreeNode(m, parent) {
			if (parent != nullptr) distanceFromStart = parent->distanceFromStart + 1;
		}

		byte getF() {
			return distanceFromStart + getManhattan();
		}

		TreeNode* moveZero(byte dx, byte dy) {
			TreeNode* res = new TreeNode(m, this);
			byte newZeroX = zeroX + (byte)dx;
			byte newZeroY = zeroY + (byte)dy;
			res->zeroX = newZeroX;
			res->zeroY = newZeroY;
			std::swap(res->m[zeroX][zeroY], res->m[newZeroX][newZeroY]);
			return res;
		}

		vector<TreeNode*> getChilds() {
			vector<TreeNode*> res;
			if (zeroX > 0) res.push_back(this->moveZero(-1, 0));
			if (zeroY > 0) res.push_back(this->moveZero(0, -1));
			if (zeroX < N - 1) res.push_back(this->moveZero(1, 0));
			if (zeroY < N - 1) res.push_back(this->moveZero(0, 1));
			return res;
		}

		struct priority_less {
			bool operator()(TreeNode* t1, TreeNode* t2) const {
				return t1->getF() > t2->getF();
			}
		};
	};

	TreeNode* solve(matrix start, byte zeroX, byte zeroY) {
		TreeNode* s = new TreeNode(start);
		s->zeroX = zeroX;
		s->zeroY = zeroY;
		set<matrix> values;
		priority_queue<TreeNode*, vector<TreeNode*>, TreeNode::priority_less> q;
		q.push(s);

		while (!q.empty()) {
			TreeNode* item = q.top(); q.pop();
			values.insert(item->m);
			if (item->isGoal()) return item;

			for (auto node : item->getChilds()) {
				if (values.find(node->m) == values.end())
					q.push(node);
				else delete node;
			}
		}
		return nullptr;
	}

}