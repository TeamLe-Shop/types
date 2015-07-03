# types
Some convenient C types.

## List

An example of the List usage:

```c
// Our List will hold ints, and it will be called "awesome_list". Awesome!
List(int, awesome_list);

// Here we add some numbers to our list.
List_Append(awesome_list, 240);
List_Append(awesome_list, 360);
List_Append(awesome_list, 480);

// This is how we destroy our list and free memory.
List_Destroy(awesome_list);
```

For List handler usage, you can look at `examples/list-example2.c`.
