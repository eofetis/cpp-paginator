#pragma once

#include <utility>
#include <vector>

// template class for a range of iterators
template <typename Iterator>
class IteratorRange {
public:
	IteratorRange(Iterator fst, Iterator lst)
	: first_(fst), last_(lst) {}

	Iterator begin() { return first_; }
	Iterator end() { return last_; }
	Iterator begin() const { return first_; }
	Iterator end() const { return last_; }

	size_t size() const {return distance(first_, last_); }
private:
	Iterator first_;
	Iterator last_;
};

// base paginator class
template <typename Iterator>
class Paginator {
public:
	Paginator(Iterator fst, Iterator lst, size_t page_size) {
		int num_pages = (distance(fst, lst) + page_size - 1) / page_size;
		for (int i = 0; i < num_pages; ++i) {
			pages.push_back({next(fst, page_size * i), min(lst, next(fst, page_size * (i+1)))});
		}
	}

	typename std::vector<IteratorRange<Iterator>>::iterator begin() {
		return pages.begin();
	}
	typename std::vector<IteratorRange<Iterator>>::iterator end() {
		return pages.end();
	}
	typename std::vector<IteratorRange<Iterator>>::const_iterator begin() const {
		return pages.begin();
	}
	typename std::vector<IteratorRange<Iterator>>::const_iterator end() const {
		return pages.end();
	}

	size_t size() const {return pages.size();}
private:
	std::vector<IteratorRange<Iterator>> pages;
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
	auto it = c.begin();
	return Paginator<decltype(it)>(c.begin(), c.end(), page_size);
}
