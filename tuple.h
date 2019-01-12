//
// Created by Andrew Berlin on 2019-01-12.
//

#ifndef TUPLE_TUPLE_H
#define TUPLE_TUPLE_H

#include <cstddef>

template<typename Head, typename... Tail>
struct tuple : public tuple<Tail...> {
    tuple(Head head, Tail... tail) : tuple<Tail...>(tail...), head(head) {}

    Head head;
};

template<typename Head>
struct tuple<Head> {
    tuple(Head head) : head(head) {}

    Head head;
};

template<size_t index, typename Head, typename... Tail>
struct getImpl {
    static auto &value(tuple<Head, Tail...> &t) {
        return getImpl<index - 1, Tail...>::value(t);
    }
    static auto const &value(const tuple<Head, Tail...> &t) {
        return getImpl<index - 1, Tail...>::value(t);
    }
};

template<typename Head, typename... Tail>
struct getImpl<0, Head, Tail...> {
    static Head &value(tuple<Head, Tail...> &t) {
        return t.head;
    }
    static Head const &value(const tuple<Head, Tail...> &t) {
        return t.head;
    }
};

template<typename Target, typename Head, typename... Tail>
struct getTypeImpl {
    static auto &value(tuple<Head, Tail...> &t) {
        return getTypeImpl<Target, Tail...>::value(t);
    }
    static auto const &value(const tuple<Head, Tail...> &t) {
        return getTypeImpl<Target, Tail...>::value(t);
    }
};

template<typename Head, typename... Tail>
struct getTypeImpl<Head, Head, Tail...> {
    static Head &value(tuple<Head, Tail...> &t) {
        return t.head;
    }
    static Head const &value(const tuple<Head, Tail...> &t) {
        return t.head;
    }
};

template<size_t cnt, typename Target, typename Head, typename... Tail>
struct checkImpl {
    static void check(const tuple<Head, Tail...> &t) {
        checkImpl<cnt, Target, Tail...>::check(t);
    }
};

template<typename Target, typename Head>
struct checkImpl<0, Target, Head> {
    static void check(const tuple<Head> &t) {
    }
};

template<typename Target, typename Head>
struct checkImpl<1, Target, Head> {
    static void check(const tuple<Head> &t) {
    }
};

template<typename Target, typename Head>
struct checkImpl<2, Target, Head> {
};

template<typename Head>
struct checkImpl<0, Head, Head> {
    static void check(const tuple<Head> &t) {
    }
};

template<typename Head>
struct checkImpl<1, Head, Head> {
};

template<size_t cnt, typename Head, typename... Tail>
struct checkImpl<cnt, Head, Head, Tail...> {
    static void check(const tuple<Head, Tail...> &t) {
        checkImpl<cnt + 1, Head, Tail...>::check(t);
    }
};

template<typename Target, typename Head, typename... Tail>
auto &get(tuple<Head, Tail...> &t) {
    checkImpl<0, Target, Head, Tail...>::check(t);
    return getTypeImpl<Target, Head, Tail...>::value(t);
}

template<size_t index, typename Head, typename... Tail>
auto &get(tuple<Head, Tail...> &t) {
    return getImpl<index, Head, Tail...>::value(t);
}

template<typename Target, typename Head, typename... Tail>
auto &get(const tuple<Head, Tail...> &t) {
    checkImpl<0, Target, Head, Tail...>::check(t);
    return getTypeImpl<Target, Head, Tail...>::value(t);
}

template<size_t index, typename Head, typename... Tail>
auto &get(const tuple<Head, Tail...> &t) {
    return getImpl<index, Head, Tail...>::value(t);
}

#endif //TUPLE_TUPLE_H
