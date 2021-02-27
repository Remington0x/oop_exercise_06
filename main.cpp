#include <algorithm>
#include "allocator.hpp"
#include "stack.hpp"
#include "triangle.hpp"

const std::size_t BLOCK_SIZE = 256;

int main() {
	auto Print = [](const auto & elem) {
		std::cout << elem << std::endl;
	};
	size_t n;
	std::cout << "Input number of triangles in stack" << std::endl;
	std::cin >> n;
	int cordX, cordY, side;
	stack_t< TTriangle<int>, allocator< TTriangle<int>, BLOCK_SIZE > > st;
	for (size_t i = 0; i < n; ++i) {
		size_t n;
		std::cout << "Input index to insert a triangle" << std::endl;
		std::cin >> n;
		std::cout << "Input triangle as follows: x y a" << std::endl;
		std::cout << "x, y is a left bottom corner cords" << std::endl;
		std::cout << "a is triangle side" << std::endl;
		std::cin >> cordX >> cordY >> side;
		try {
			stack_t< TTriangle<int>, allocator< TTriangle<int>, BLOCK_SIZE > >::iterator it = st.begin();
			while (n--) {
				++it;
			}
			st.insert(it, TTriangle<int>(std::pair<int, int>(cordX, cordY), side));
		} catch (std::runtime_error & exception) {
			std::cout << exception.what() << std::endl;
		}
	}
	std::cout << "Your input:" << std::endl;
	std::for_each(st.begin(), st.end(), Print);
	std::cout << "Input index to erase from stack" << std::endl;
	std::cin >> n;
	try {
		stack_t< TTriangle<int>, allocator< TTriangle<int>, BLOCK_SIZE > >::iterator it = st.begin();
		while (n > 1) {
			++it;
			--n;
		}
		st.erase(it);
	} catch (std::runtime_error & exception) {
		std::cout << exception.what() << std::endl;
	}
	std::cout << "After erase:" << std::endl;
	std::for_each(st.begin(), st.end(), Print);
	return 0;
}
