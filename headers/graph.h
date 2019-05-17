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

	template <typename ItemType = float>
	class Node {
	protected:
		NodeType type_;
		vector<Node<ItemType>*> args_;
		Array<ItemType> * val_;
	public:
		Node();
		Array<ItemType>& GetValue();
		Node* GetArgument(int index);
	};

	template <typename ItemType = float>
	class Operation: public Node<ItemType> {
	public:
		virtual void Update() = 0;
		Operation();
		~Operation();
	};

	template <typename ItemType = float>
	class Variable: public Node<ItemType> {
	public:
		Variable(vector<int> shape);
		~Variable();
		void SetValue(Array<ItemType> * val);
	};

	template <typename ItemType = float>
	class Placeholder: public Node<ItemType> {
	public:
		Placeholder();
		~Placeholder();
	};

}
