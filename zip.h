#pragma once
#include <tuple>
#include <utility>
#include <algorithm>

namespace zip {

template<class... Iterators>
struct iterator {
  iterator(std::tuple<Iterators...> iterators) : m_iterators(iterators) {}

  auto operator*() {
    return std::apply([](auto &... its) {
      return std::make_tuple(*its...);
    }, m_iterators);
  }

  auto operator++() -> iterator& {
    std::apply([](auto &... its) {
      (++its, ...);
    }, m_iterators);
    return *this;
  }

  auto operator++(int) -> iterator {
    iterator self = *this;
    ++(*this);
    return self;
  };

  auto operator==(const iterator &other) -> bool {
    return this->eq(other, std::index_sequence_for<Iterators...>{});
  };

  auto operator!=(const iterator &other) -> bool {
    return !(*this == other);
  }

private:
  template<std::size_t... I>
  auto eq(const iterator &other, std::index_sequence<I...>) -> bool {
    return ((std::get<I>(m_iterators) == std::get<I>(other.m_iterators)) || ...);
  }

  std::tuple<Iterators...> m_iterators;
};


template<class... Containers>
struct zip_object {
  using iterator = zip::iterator<typename Containers::iterator...>;

  zip_object(Containers *... containers)
    : m_containers(containers...)
  {}

  auto begin() -> iterator {
    return iterator(std::apply([](auto &... c) { return std::make_tuple(c->begin()...); }, m_containers));
  }

  auto end() -> iterator {
    return iterator(std::apply([](auto &... c) { return std::make_tuple(c->end()...); }, m_containers));
  }

private:
  std::tuple<Containers*...> m_containers;
};


template<class... Containers>
auto zip(Containers &... containers) {
  return zip_object<Containers...>(&containers...);
}

}

