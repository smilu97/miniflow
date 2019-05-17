/*
 * Graph.h
 * author: smilu97
 */

#include "array.h"
#include <vector>
using namespace std;

namespace miniflow {

	enum NodeType {
		NT_OP = 0,
		NT_VAR,
		NT_PH,
	};

	class Node {
	protected:
		NodeType type_;
		vector<Node*> args_;
		void * val_;
	public:
		Node();
		Node* GetArgument(int index);
	};

	class Operation: public Node {
	public:
		virtual void Update() = 0;
		Operation();
		~Operation();
	};

	template <class ValueType>
	class Variable: public Node {
	public:
		Variable(vector<int> shape);
		~Variable();
		void SetValue(ValueType val);
	};

	template <class ValueType>
	class Placeholder: public Node {
	public:
		Placeholder();
		~Placeholder();
	};

}
