#Receipt Recovery

###[Codechef Link](https://www.codechef.com/problems/RECRECOV)

While vacationing in Egypt, Chef found a recipe of an ancient dish. The receipt is a sequence of hieroglyphs written on a magic paper - it survived for thousands of years! The sequence is written on a long scroll. Unfortunately, the scroll is split into pieces, and possibly, some pieces of the scroll are missing. Chef has a total of `N` pieces, numbered for convenience from `1` to `N`. He gave the pieces of a tape to his friend who studies hieroglyphs for analysis. Chef was happy to hear that there are some relations between the pieces. Some of the pieces may follow other pieces.

The informations about these relations is given as a list of `M` pairs `(Ai, Bi)`. Such a pair means that the *Ai*th piece can be immediately followed by the *Bi*th one.

Chef is working on recovering the recipe to prepare this dish for his Egyptian friends. He wants to place all the pieces into lines such that any pair of consecutive pieces `(L, R)` in a line must be explicitly allowed by one of the `M` rules described above. In other words, for some *i* (`1 <= i <= M`), `(Ai, Bi) = (L, R)`. It appears that in general, not all the pieces can be placed in a single line while following the rules. So, please help Chef find what is the minimum number of lines required for all the pieces to be placed acoording to the rules.

##Input

The first line of the input contains an integer `T` denoting the number of test cases. The description of `T` test cases follows.

The first line of each test case contains two space-separated integers `N` and `M` denoting the number of pieces and number of relations of those `N` pieces. Next `M` lines contain two space-separated integers `A` and `B` denoting that piece number `A` can be followed by piece number `B`, all those pairs are guaraneed to be unique within a test case.

##Output

For each test case, output a single line containing the minimum number of lines required for all the pieces to be placed acoording to the rules.

###Constraints

```
1 <= T <= 20
1 <= N <= 100
1 <= M <= N^2
1 <= Ai <= N
1 <= Bi <= N
```

There is no sequence `S1, S2, ..., Sk` such that the piece `Si` can be immediately followed by the piece `Si + 1` for all `i` from `1` to `k - 1`, and that piece `Sk` can be followed by piece `S1`.

##Example

#####Inputs and Outputs
Input:
```
3
3 3
1 2
2 3
1 3
3 2
1 2
1 3
5 4
1 3
2 3
3 4
2 5
```
Output:
```
1
2
2
```
Input:
```
1
5 7
1 2
1 3
2 4
2 5
3 4
3 5
4 5
```
Output:
```
2
```
Input:
```
1
7 9
1 2
1 3
1 4
2 5
2 6
3 6
3 7
4 7
4 5
```
Output:
```
3
```
Input:
```
1
9 11
1 2
1 3
1 4
1 5
2 6
2 7
3 7
3 8
4 8
4 9
5 9
```
Output:
```
4
```
Input:
```
1
9 8
1 2
1 3
1 4
2 5
2 6
3 7
4 8
4 9
```
Output:
```
5
```
