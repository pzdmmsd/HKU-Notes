# ENGG1340 / COMP2113 Exam 2019-2020 Detailed Solutions

This solution is based on the local course materials, especially:

- `COMP2113_A4_Cheat_Sheet.md`: Linux commands, pipes, integer division, pointer declaration traps, pointer/array equivalence, dynamic memory, binary search, linked lists.
- `COMP2113_Course_Cheatsheet.md`: course-wide compilation and Linux/C/C++ revision points.

## Section A: Multiple Choice Questions

| Q | Answer | Explanation |
|---|---|---|
| 1 | A | `wc` counts lines, words, and characters/bytes in a file. |
| 2 | C | `sort` sorts lines in alphanumerical/lexicographical order. `sort -r` sorts in reverse order. |
| 3 | B | `cpio` copies files or directory structures in and out of archives. |
| 4 | A | `cat 1.txt` prints the content of `1.txt`. |
| 5 | B | `man more` opens the manual page for `more`. |
| 6 | D | `num != 65` is true when `num - 65` is nonzero. `!(num - 65)` is true only when `num == 65`, so it is the opposite condition. |
| 7 | A | `// This is a comment` is a valid C++ single-line comment. Option B is missing the closing `*/`. |
| 8 | A | `double mySqrt(int x);` declares a function named `mySqrt`, taking one `int`, returning `double`. |
| 9 | D | The function recursively returns `number * mystery(number - 1)` until `number <= 1`; this is factorial. |
| 10 | B | In C strings, `strlen()` returns the string length, excluding the null terminator `'\0'`. |
| 11 | D | Dereferencing an uninitialized/null pointer can crash at run time. A non-pointer variable cannot be dereferenced in valid code; this is a compile-time error, not a fatal run-time error. |
| 12 | C | The address of array element 3 is `&t[3]`. The expressions `*(tPtr + 3)`, `tPtr[3]`, and `*(t + 3)` refer to the element value. |
| 13 | A | In `string* x, y;`, only `x` is a pointer. `y` is a normal `string`. |
| 14 | C | `#include` is handled by the preprocessor as part of the compilation process; among the choices, this is compile time. |
| 15 | C | `s2.insert(0, s1, 0, 3)` inserts `"com"` at the start of `"promise"`, producing `"compromise"`. |

Final Section A answers:

```text
1 A
2 C
3 B
4 A
5 B
6 D
7 A
8 A
9 D
10 B
11 D
12 C
13 A
14 C
15 C
```

## Section B: Short Questions

### B1

Code:

```cpp
int x = 3;
int y = 2;
int z = 1;
if (z / 3 == 0 && x % 3 == 0 && y % x == 1) {
    x+=1;
}
y += x / 2;
cout << x * y * z;
```

Step-by-step:

- `z / 3` is integer division: `1 / 3 == 0`, so the first condition is true.
- `x % 3 == 0`: `3 % 3 == 0`, true.
- `y % x == 1`: `2 % 3 == 2`, false.
- The whole `&&` condition is false, so `x` remains `3`.
- `x / 2` is integer division: `3 / 2 == 1`.
- `y += x / 2`, so `y = 2 + 1 = 3`.
- Output is `x * y * z = 3 * 3 * 1 = 9`.

Answer:

```text
9
```

### B2

Code:

```cpp
void f(int a) {
    a = a*a;
    {
        int a = 4;
        cout << ++a << " ";
    }
    cout << a << " ";
}

int main() {
    int a = 1;
    {
        cout << a << " ";
        int a = 2;
        f(a);
        cout << a << " ";
    }
    f(a);
    return 0;
}
```

Step-by-step:

- In `main`, outer `a = 1`.
- First `cout << a` uses the outer `a`, so prints `1`.
- Inner block declares another `a = 2`.
- `f(a)` is called with value `2`.
  - In `f`, parameter `a = 2`, then `a = a*a = 4`.
  - Inner block in `f` declares a new local `a = 4`.
  - `++a` changes that inner `a` to `5`, so prints `5`.
  - After that block, `cout << a` uses the function parameter, which is `4`.
- Back in `main`, inner `a` is still `2`, because `f` passed by value.
- After the inner block ends, outer `a` is still `1`.
- `f(a)` is called with value `1`.
  - Parameter becomes `1 * 1 = 1`.
  - Inner `++a` prints `5`.
  - Function parameter prints `1`.

Answer:

```text
1 5 4 2 5 1
```

### B3

Code:

```cpp
int f(char n[]) {
    int j = 0;
    for (int i = 0; n[i] != '\0'; ++i){
        int k = n[i] - '0';
        j = j * 10 + k + 1;
    }
    return j;
}

int main() {
    char n[] = "2019";
    cout << f(n);
    return 0;
}
```

Trace:

| Character | `k` | New `j` |
|---|---:|---:|
| `'2'` | 2 | `0 * 10 + 2 + 1 = 3` |
| `'0'` | 0 | `3 * 10 + 0 + 1 = 31` |
| `'1'` | 1 | `31 * 10 + 1 + 1 = 312` |
| `'9'` | 9 | `312 * 10 + 9 + 1 = 3130` |

Answer:

```text
3130
```

### B4

Code:

```cpp
void f(int p[], int size)
{
    int *a = &p[1];
    for (int i = size-2; i >= 0; --i)
        a[i] += a[i-1];
}

int main()
{
    int a[] = {6, 5, 4, 3, 2, 1};

    int * q = &a[2];
    f(q, 3);

    for (int i = 0; i < 6; ++i)
        cout << a[i] << ' ';

    return 0;
}
```

Important pointer mapping:

- In `main`, `q = &a[2]`, so inside `f`, `p[0]` is original `a[2]`.
- Inside `f`, `int *a = &p[1]`, so local `a[0]` is original `a[3]`.

Therefore:

- Local `a[-1]` is original `a[2]`, value `4`.
- Local `a[0]` is original `a[3]`, value `3`.
- Local `a[1]` is original `a[4]`, value `2`.

Loop:

- `i = 1`: local `a[1] += a[0]`, so original `a[4] = 2 + 3 = 5`.
- `i = 0`: local `a[0] += a[-1]`, so original `a[3] = 3 + 4 = 7`.

Final array:

```text
6 5 4 7 5 1
```

Answer:

```text
6 5 4 7 5 1
```

### B5

Task:

Find all lines containing `wonderful` from `day.txt`, sort them alphabetically, take the first 15 sorted lines, and count the number of characters in those 15 lines.

Answer:

```bash
grep "wonderful" day.txt | sort | head -15 | wc -m
```

Explanation:

- `grep "wonderful" day.txt`: keep only lines containing `wonderful`.
- `sort`: sort the matching lines alphabetically.
- `head -15`: take the first 15 lines.
- `wc -m`: count characters.

If the grading environment treats characters as bytes for ASCII text, `wc -c` may also be accepted:

```bash
grep "wonderful" day.txt | sort | head -15 | wc -c
```

### B6

For a four-digit positive integer `x`, store the middle two digits in integer variable `y`.

Example: if `x = 1234`, then the middle two digits are `23`.

Answer:

```cpp
y = (x / 10) % 100;
```

Explanation:

- `x / 10` removes the last digit.
- `% 100` keeps the last two digits of the remaining number.

### B7

Original code:

```cpp
int main()
{
  int* p1, p2;
  int n = 42;
  p1 = p2 = &n;       // You cannot change this line
  printf("%d", *p1);  // You cannot change this line
}
```

Problem:

```cpp
int* p1, p2;
```

means:

- `p1` is an `int*`.
- `p2` is an `int`.

So `p2 = &n` tries to store an address into an `int`, which is invalid.

Fix line 3:

```cpp
int *p1, *p2;
```

Corrected code:

```cpp
int main()
{
  int *p1, *p2;
  int n = 42;
  p1 = p2 = &n;
  printf("%d", *p1);
}
```

Answer:

```text
Change line 3 to:
int *p1, *p2;
```

### B8

Original code:

```cpp
int main()
{
  const int SIZE = 42;
  double *p;
  if ((p = (double*)malloc(sizeof(double)*SIZE)) == NULL)
  { exit(EXIT_FAILURE); }
  for (int i = 0; i < SIZE; i++)
  { *(p + i) = i; }
  double *index = p + SIZE;
  double lastVal = *index;   // You cannot change this line
  printf("%lf\n", lastVal);  // You cannot change this line
  return 0;
}
```

Problem:

- The array has valid indexes `0` to `SIZE - 1`, i.e. `0` to `41`.
- `p + SIZE` points one position after the allocated array.
- Dereferencing `p + SIZE` is out-of-bounds and causes undefined behavior.

Fix:

```cpp
double *index = p + SIZE - 1;
```

Then `*index` is `p[41]`, whose value is `41`.

Answer:

```text
Change line 9 to:
double *index = p + SIZE - 1;
```

Corrected fragment:

```cpp
double *index = p + SIZE - 1;
double lastVal = *index;
printf("%lf\n", lastVal);
```

The printed value is:

```text
41.000000
```

## Section C: Programming Questions

### C1(a): Iterative Binary Search

Answer:

```cpp
int BinarySearch(int arr[], int l, int r, int x) {
    while (l <= r) {
        int mid = l + (r - l) / 2;

        if (arr[mid] == x) {
            return mid;
        }
        else if (x < arr[mid]) {
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }
    }

    return -1;
}
```

Explanation:

- `l` and `r` are inclusive boundaries.
- `mid = l + (r - l) / 2` avoids overflow and chooses the lower middle.
- If `x` is smaller than `arr[mid]`, search the left half.
- If `x` is larger than `arr[mid]`, search the right half.
- If the interval becomes empty, return `-1`.

For the sample:

```cpp
arr = {2, 3, 4, 10, 40}
x = 10
```

The function returns index `3`.

### C1(b): Recursive Binary Search

Answer:

```cpp
int BinarySearch(int arr[], int l, int r, int x) {
    if (l > r) {
        return -1;
    }

    int mid = l + (r - l) / 2;

    if (arr[mid] == x) {
        return mid;
    }
    else if (x < arr[mid]) {
        return BinarySearch(arr, l, mid - 1, x);
    }
    else {
        return BinarySearch(arr, mid + 1, r, x);
    }
}
```

Explanation:

- Base case: if `l > r`, the interval is empty, so `x` is not found.
- Recursive case:
  - Search left half if `x < arr[mid]`.
  - Search right half if `x > arr[mid]`.

Note: the provided main function in the paper has a missing semicolon after:

```cpp
printf("Element is not present in array")
```

If writing a full compilable program, add the semicolon. The exam question only asks for the `BinarySearch` function.

### C2(a): Deliver the Oldest Order

The linked list stores newest orders at the head:

```text
head -> newest -> ... -> oldest -> NULL
```

So the oldest order is the tail node. To deliver the oldest order, delete the last node, not the head node.

Answer:

```cpp
void deliver(Mask *&head) {
    if (head == NULL) {
        return;
    }

    if (head->next == NULL) {
        cout << "Delivering " << head->type;
        cout << " for " << head->customer << endl;
        delete head;
        head = NULL;
        return;
    }

    Mask *prev = NULL;
    Mask *curr = head;

    while (curr->next != NULL) {
        prev = curr;
        curr = curr->next;
    }

    cout << "Delivering " << curr->type;
    cout << " for " << curr->customer << endl;

    prev->next = NULL;
    delete curr;
}
```

Explanation:

- If the list is empty, there is nothing to deliver.
- If there is only one node, print and delete it, then set `head = NULL`.
- Otherwise:
  - Move `curr` until it points to the last node.
  - Keep `prev` pointing to the node before `curr`.
  - Print the delivered order.
  - Set `prev->next = NULL`.
  - Delete the old tail node.

With the given input, this deletes Alice's order, because Alice ordered first and is at the tail.

### C2(b): Remove All 3M-N95 Orders

Need to remove every node whose:

```cpp
type == "3M-N95"
```

Important cases:

- Matching nodes may appear at the head.
- Matching nodes may appear in the middle or at the tail.
- There may be consecutive matching nodes.

Answer:

```cpp
void remove(Mask *&head) {
    while (head != NULL && head->type == "3M-N95") {
        Mask *temp = head;
        head = head->next;
        delete temp;
    }

    Mask *curr = head;

    while (curr != NULL && curr->next != NULL) {
        if (curr->next->type == "3M-N95") {
            Mask *temp = curr->next;
            curr->next = curr->next->next;
            delete temp;
        }
        else {
            curr = curr->next;
        }
    }
}
```

Explanation:

- The first `while` loop removes all matching nodes at the front of the list.
- Then `curr` scans the remaining list.
- If `curr->next` should be removed:
  - Save it in `temp`.
  - Bypass it by changing `curr->next`.
  - Delete it.
- Do not advance `curr` immediately after deleting `curr->next`, because the new `curr->next` may also be `"3M-N95"`.

Example:

Before removal:

```text
head -> Cindy(3M-N95) -> Bruce(OxyAir) -> Alice(3M-N95) -> NULL
```

After removal:

```text
head -> Bruce(OxyAir) -> NULL
```

