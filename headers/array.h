/*
 * array.h
 * author: smilu97
 */

#include <vector>
#include <tuple>
using namespace std;

namespace miniflow {

    struct NDarray {
        vector<int> shape;
        vector<int> strides;
        int ndims;
        char * data;
        int size;
        int itemsize;
        int nbytes;
    };

    template <typename ItemType = float>
    class Array: public NDarray {
        bool alloc;
    public:
        Array(vector<int> _shape, bool alloc=true);
        ~Array();
        int GetOffset(vector<int> indices);
        ItemType Get(vector<int> _indices);
        void Set(vector<int> indices, ItemType item);
        Array<ItemType>* Clone();
        
        Array<ItemType> BroadcastTo(vector<int> shape);
        static vector<int> CombineShape(vector<int> shape_a, vector<int> shape_b);

        static Array<ItemType>* empty(vector<int> shape);
        static Array<ItemType>* zeros(vector<int> shape);
        static Array<ItemType>* ones(vector<int> shape);

        void MultiplyTo(Array<ItemType>& b, Array<ItemType>& dest);
        void MultiplyTo(float b, Array<ItemType>& dest);
        void MultiplyTo(int b, Array<ItemType>& dest);

        void AddTo(Array<ItemType>& b, Array<ItemType>& dest);
        void AddTo(float b, Array<ItemType>& dest);
        void AddTo(int b, Array<ItemType>& dest);

        void DivideTo(Array<ItemType>& b, Array<ItemType>& dest);
        void DivideTo(float b, Array<ItemType>& dest);
        void DivideTo(int b, Array<ItemType>& dest);
    };

}
