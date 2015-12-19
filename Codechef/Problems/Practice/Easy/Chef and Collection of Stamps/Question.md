#Chef and Collection of Stamps

Chef has a collection of `N` postage stamps. Each stamp belongs to some type, which are enumerated as positive integers. More valuble stamps have a higher enumerated stamp. So, type `1` is the least valuable type of stamp, and type `2` is a bit more valuable, and so on. 

Chef often communicates with other Philatelists via a stamp exchange website called P-bay. On any particular day, P-Bay lists several offers, each of which is represented as an unordered pair `{A, B}`, allowing its users to exchange stamps of type `A` with an equal number of stamps of type `B`. Chef can use such an offer to put up any number of stamps of enumerated type `A` on the website and get the same number of stamps of type B in return, or vice-versa. (Of course, he must have enough number of stamps of the corresponding type). Assume that any number of items the Chef wants are available on the site's exchange market. Each offer is open during only one day. The Chef can't use it after this day, but he can use it several times during the day. If there are some offers active during a given day, the chef can use them in any order.

The Chef is interested in making his collection as valuable as possible. Help him find the maximum possible value of his collection after going through (accepting / declining) all the offers. Value of the Chef's collection is equal to the sum of type enumerations of all stamps in the collection.

##Input
The first line of input contains an integer `T`, denoting the number of testcases. The description of `T` testcases follows. 

The first line of each test case contains two integers `N` and `M`, denoting the number of stamps in the Chef's collection and the number of offers respectively.

Next line contains `N` integers denoting the enumerated types of stamps in the Chef's collection.

The `i`th of the following `M` lines contains three integers: `Ti`, `Ai`, and `Bi`, denoting that on day `Ti`, there is an offer about exchanging stamps of types `Ai` and `Bi`.

##Output
For each test case, output a single line containing max possible value of the Chef's collection after all offers.

##Constraints
```
1 <= T <= 10
1 <= N <= 2 * (10 ^ 5)
1 <= M <= 5 * (10 ^ 4)
Types are enumerated from integers ranging from 1 to 5 ^ (10 ^ 4)
1 <= Ti <= 5 * (10 ^ 4)
```

##Subtasks
####Subtask One: (33 points)
```
1 <= M <= 1000
Types are enumerated from 1 to 1000
1 <= Ti <= 1000
```

####Subtask Two: (67 points)
Original Constraints

##Example
####Input
```
1
3 4
1 3 5
1 4 3
1 1 3
2 6 22
3 5 8
```

####Output
```
16
```

##Explanation
####Case one
Chef can use the second offer to exchange stamps of type `1` with a stamp of type `3`. After that he can use the first offer to exchange two stamps of type `3` with two stamps of type `4`. Finally on the third day, Chef uses the offer to exchange the stamp of type `5` with a stamp of type `8`. After this transaction, the value of the collection becomes `4 + 4 + 8 = 16`.
