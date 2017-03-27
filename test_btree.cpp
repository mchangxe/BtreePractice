#include <cstring>
#include <stdexcept>

#include "btree.h"

using namespace std;

template <class K, class V>
void do_inserts(vector<pair<K, V>>& data, BTree<K, V>& b)
{
    for (auto& key_val : data) {
        b.insert(key_val.first, key_val.second);
    }
}

template <class K, class V>
void verify_finds(vector<pair<K, V>>& data, BTree<K, V>& b)
{
    for (auto& key_val : data) {
        V ret = b.find(key_val.first);
        if (key_val.second != ret) {
            cout << ret << endl;
            cout << "ERROR: Value incorrect for key: " << key_val.first << endl;
        }
    }
}

vector<pair<int, int>> make_int_data(int n, bool random)
{
    vector<pair<int, int>> data;
    if (random) {
        for (int i = 0; i < n; i++) {
            int rand_val = rand();
            data.emplace_back(rand_val, rand_val);
        }
    } else {
        for (int i = 0; i < n; i++) {
            data.emplace_back(i, i);
        }
    }
    return data;
}

void small_btree_small_order()
{
    cout << __func__ << endl;
    /*
     *vector< pair< int, int > > data = { {1, 5}, {4, 7}, {5, 43}, {-43, 3},
     *                                    {99, 2}, {23, 7} };
     *BTree< int, int > b(3);
     *do_inserts(data, b);
     *verify_finds(data, b);
     *cout << "BTree is valid? " << b.is_valid(3) << endl;
     *cout << "Proper value for key not in BTree? " << (0 == b.find(-1)) << endl
     *<< endl;
     */
	cout << "l" << endl;
    vector<pair<int, int>> data
        = {{1, 5}, {4, 7}, {5, 43}, {-43, 3}, {99, 2}, {23, 7}, {3, 2}, {9, 4}};
    	cout << "o" << endl;
    BTree<int, int> b(3);
	cout << "l" << endl;
    do_inserts(data, b);
	cout << "o" << endl;
    verify_finds(data, b);
	cout << "l" << endl;
    b.find(-999);
	cout << "o" << endl;
    b.is_valid(3);
}

void large_btree_small_order()
{
    cout << __func__ << endl;
    BTree<int, int> b(3);
    cout << "Testing sequential data..." << endl;
    auto data = make_int_data(2000, false);
    do_inserts(data, b);
    verify_finds(data, b);
    cout << "BTree is valid? " << b.is_valid(3) << endl;
    b.clear();

    cout << "Testing random data..." << endl;
    data = make_int_data(2000, true);
    do_inserts(data, b);
    verify_finds(data, b);
    cout << "BTree is valid? " << b.is_valid(3) << endl << endl;
}

void huge_btree_large_order()
{
    cout << __func__ << endl;
    BTree<int, int> b;
    cout << "Testing sequential data..." << endl;
    auto data = make_int_data(200000, false);
    do_inserts(data, b);
    verify_finds(data, b);
    cout << "BTree is valid? " << b.is_valid(64) << endl;
    b.clear();

    cout << "Testing random data..." << endl;
    data = make_int_data(200000, true);
    do_inserts(data, b);
    verify_finds(data, b);
    cout << "BTree is valid? " << b.is_valid(64) << endl << endl;
}

void generic_test(int order, int n)
{
    BTree<int, int> b(order);
    cout << "Testing sequential data..." << endl;
    auto data = make_int_data(n, false);
    do_inserts(data, b);
    verify_finds(data, b);
    cout << "BTree is valid? " << b.is_valid(order) << endl;
    b.clear();

    cout << "Testing random data..." << endl;
    data = make_int_data(n, true);
    do_inserts(data, b);
    verify_finds(data, b);
    cout << "BTree is valid? " << b.is_valid(order) << endl << endl;
}


const string USAGE =
"USAGE: test_btree ORDER N\n"
"Tests N inserts and N finds on a BTree< int, int > of order ORDER.\n";

int main(int argc, char* argv[])
{
	//custom tests
	cout << "custom tests:" << endl;
	vector<int> v = {1,2,5,6};
	size_t index1 = insertion_idx(v, 2);
	cout << index1 << endl;
	size_t index2 = insertion_idx(v, 4);
	cout << index2 << endl;
	size_t index3 = insertion_idx(v,10);
 
    srand(time(nullptr));
    cout << boolalpha;
    if (argc == 1) {
        small_btree_small_order();
        large_btree_small_order();
        huge_btree_large_order();
    } else if (argc != 3) {
        cout << USAGE << endl;
        return -1;
    } else {
        try {
            int order = stoi(argv[1]);
            int n = stoi(argv[2]);
            generic_test(order, n);
        } catch (invalid_argument& e) {
            cout << USAGE << endl;
            return -1;
        } catch (out_of_range& e) {
            cout << "Number too large to take as input." << endl;
            return -1;
        }
    }
}
