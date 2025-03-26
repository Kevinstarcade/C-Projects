#include <stdio.h>
#include <stdlib.h>
// reads instructions from stdin to manipulate two mathematical sets, x and y:
// a - add value to set, does nothing if set already contains value. usage: a <set> <value>
// r - remove a value from a set, does nothing if set does not contain value. usage: r <set> <value>
// p - print set. usage: p <set>
// u - prints the union of the two sets. usage: u
// i - prints the intersect of the two sets. usage: i
// q - quits the program. usage: q
// used as an introduction to structs and practice for dynamic memory, incuding allocating structs on the heap and freeing memory properly

struct set {
    int *arr;
    int len, cap;

};

struct set *makeSet() {
    struct set *ret = malloc(sizeof(struct set)*1);
    ret->arr = malloc(sizeof(int)*4);
    ret->len = 0;
    ret->cap = 4;
    return ret;
}

void destroySet(struct set *s) {
    free(s->arr);
    free(s);
}

void printSet(struct set *s) {
    if (s->len == 0) return;
    for (int i = 0; i < s->len-1; ++i) printf("%d ", (s->arr)[i]);
    printf("%d\n", (s->arr)[s->len-1]);
}  

int checkIn(struct set *s, int val) {
    for (int i = 0; i < s->len; ++i) {
        if ((s->arr)[i] == val) return 1;
    }
    return 0;
}

void add(struct set *s, int val) {
    if (checkIn(s, val)) return;

    if (s->cap == s->len) {
		int *newArr = malloc(s->cap*sizeof(int)*2);
		for (int i = 0; i < s->len; ++i) newArr[i] = (s->arr)[i];
		free(s->arr);
		s->arr = newArr;
		s->cap *= 2;
	}
	
    int ind = s->len;
    for (; (s->arr)[ind-1] >= val && ind > 0; --ind) {
        (s->arr)[ind] = (s->arr)[ind-1];
    }
    (s->arr)[ind] = val;
    ++(s->len);
}

void removeVal(struct set *s, int val) {
    if (!checkIn(s, val)) return;

    int ind = 0;
    for (; (s->arr)[ind] != val; ++ind);
    for (; ind < s->len-1; ++ind) {
        (s->arr)[ind] = (s->arr)[ind+1];
    }
    --(s->len);
}

void setUnion(struct set *x, struct set *y) {
    struct set *tempSet = makeSet();
    int i = 0;
    int j = 0;
    for (; i < x->len && j < y->len;) {
        if ((x->arr)[i] == (y->arr)[j]){
            add(tempSet, (x->arr)[i]);
            ++i, ++j;
        } else if ((x->arr)[i] < (y->arr)[j]) {
            add(tempSet, (x->arr)[i]);
            ++i;
        } else if ((x->arr)[i] > (y->arr)[j]) {
            add(tempSet, (y->arr)[j]);
            ++j;
        }
    }
    if (i == x->len) for (; j < y->len; ++j) add(tempSet, (y->arr)[j]);
    if (j == y->len) for (; i < x->len; ++i) add(tempSet, (x->arr)[i]);

    printSet(tempSet);
    destroySet(tempSet);

}

void intersection(struct set *x, struct set *y) {
    struct set *tempSet = makeSet();
    for (int i = 0; i < x->len; ++i) {
        for (int j = 0; j < y->len && (y->arr)[j] <= (x->arr)[i]; ++j) {
            if ((x->arr)[i] == (y->arr)[j]) add(tempSet, (x->arr)[i]);
        }
    }
    printSet(tempSet);
    destroySet(tempSet);
}

int main() {
    struct set *x = makeSet();
    struct set *y = makeSet();

    struct set *setList[] = {x, y};

    char instruction;
    char targ;
    struct set *targSet;
    int val;

    while (scanf(" %c", &instruction)) {
        if (instruction == 'a') {
            scanf(" %c %d", &targ, &val);
            targSet = setList[targ - 'x'];
            add(targSet, val);
        } else if (instruction == 'r') {
            scanf(" %c %d", &targ, &val);
            targSet = setList[targ - 'x'];
            removeVal(targSet, val);
        } else if (instruction == 'p') {
            scanf(" %c", &targ);
            targSet = setList[targ - 'x'];
            printSet(targSet);
        } else if (instruction == 'u') {
            setUnion(x, y);
        } else if (instruction == 'i') {
            intersection(x, y);
        } else if (instruction == 'q') {
            destroySet(x);
            destroySet(y);
            break;
        }
    }
}
