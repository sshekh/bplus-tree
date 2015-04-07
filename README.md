## Submitted By
Saurav Shekhar, 12640
Assignment 2 - CS315

## Build
- Build using `make`
- Build a new tree and clear all the data using `make fresh` 
- It first loads the tree using `tree.config` and if tree is not present, constructs a new tree.


## Query 
- If the tree is not present, it loads `assgn2_bplus_data.txt` and injects the points.
- Run queries using `./main < querysample.txt > querysample.out`, this will print all the output in `querysample.out` file.
- For range query, it will print it space separated in a line `key:data`. For ex - if keys are `(0.1, 0.1, 0.2, 0.3)` and query is `2 0.15 0.3` output is `0.2:foo 0.3:bar`. 
- Output format for point query is same as that of range query. It will print all the data that has the same key as the input key. Ex in the above example if the query is `1 0.1` then output is `0.1:rand 0.1:string`.
- Output for each query is printed in a line, and then a newline is printed. If there is no result for a particular output, a blank line is printed.


## Stats
- Query type, time taken (in microseconds), and number of files accessed are written for each query in a new line in the file `time.out`. 
- Run `python data.py > stats.out` to generate the final stats in file `stats.out`. 

