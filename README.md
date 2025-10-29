Program for viewing inventory by unique ID and by tags.
Note that all search terms only match exact strings.

Testing functions are implemented in a separate header file, TestHashMap.h.
I only tested the functions in hashmap.h because the other data structures used were created for a previous assignment.
It's pretty much self-documenting/commented, but here it is anyway:

insert: tested with normal insertion and a duplicate key (should overwrite the old value).
find: tested with normal search and a nonexistent key.
erase: tested with normal deletion and a nonexistent key.
clear: tested with a map and an empty map.
rehash: tested with a map and an empty map.

the other functions are already for debugging purposes and not tested.

NOTE: some of the categories are huge and might not print to a terminal, consider outputting to a file instead.