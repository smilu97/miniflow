/*
 * array.h
 * author: smilu97
 */

#include <vector>
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
    public:
        Array();
        Array(vector<int> _shape);
        ~Array();
        int GetOffset(vector<int> indices);
        ItemType Get(vector<int> indices);
        void Set(vector<int> indices, ItemType item);
        Array<ItemType>* Copy();

        static Array<ItemType>* empty(vector<int> shape);
        static Array<ItemType>* zeros(vector<int> shape);
        static Array<ItemType>* ones(vector<int> shape);
    };

}
