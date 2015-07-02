# types
Some convenient C types.

An example of the List usage:

```c
// Our List will hold ints, and it will be called "awesome_list". Awesome!
// The NULL is a function pointer. The function passed in is called upon deletion
// of the List. Since we're passing NULL, it won't call anything.
List(int, awesome_list, NULL);

// Here we add some numbers to our list.
List_Add(awesome_list, 240);
List_Add(awesome_list, 360);
List_Add(awesome_list, 480);

// This is how we destroy our list and free memory.
List_Destroy(awesome_list);
```
