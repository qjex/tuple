//
// Created by Andrew Berlin on 2019-01-12.
//

#ifndef TUPLE_TUPLE_H
#define TUPLE_TUPLE_H

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

template<typename Target, typename Head, typename... Tail>
auto &get(tuple<Head, Tail...> &t) {
    return getTypeImpl<Target, Head, Tail...>::value(t);
}

template<int index, typename Head, typename... Tail>
auto &get(tuple<Head, Tail...> &t) {
    return getImpl<index, Head, Tail...>::value(t);
}

template<typename Target, typename Head, typename... Tail>
auto &get(const tuple<Head, Tail...> &t) {
    return getTypeImpl<Target, Head, Tail...>::value(t);
}

template<int index, typename Head, typename... Tail>
auto &get(const tuple<Head, Tail...> &t) {
    return getImpl<index, Head, Tail...>::value(t);
}

#endif //TUPLE_TUPLE_H
