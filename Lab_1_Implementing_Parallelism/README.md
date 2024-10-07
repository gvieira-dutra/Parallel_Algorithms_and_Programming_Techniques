# Lab 1 Report: GPU 621 NSA

Hello,

This is my report for Lab 1, GPU 621 NSA. The instructions advised creating a report about **Performance Comparison** & **Challenges Faced**.

## Performance Comparison

My program executes the task sequentially, then with 2, 4, and 8 threads. The performance comparison is printed each time my program runs. Below is the run I will use as a reference for this report.

### Final Results:

| Execution Type | Time (µs) | Time (ms) | Time (s) |
| -------------- | --------- | --------- | -------- |
| Sequential     | 123274    | 123.27    | 0.12     |
| 2 Threads      | 91421     | 91.42     | 0.09     |
| 4 Threads      | 55565     | 55.56     | 0.06     |
| 8 Threads      | 47875     | 47.88     | 0.05     |

### Improvements

- Improvement using 2 Threads: **25.84%**
- Improvement using 4 Threads: **54.93%**
- Improvement using 8 Threads: **61.16%**

We observe that, although the performance improvement is not linear, there was a continuous progression in how much faster the application ran as the number of threads increased.

Although my laptop has 8 cores, it is expected that the application running on 8 cores is faster than with 4, but not double the speed. Thus, these results align with expectations.

## Challenges Faced

The first challenge was to remember C++ syntax. Although we have seen the language in many semesters, once we shifted to the more web development-focused part of the program, C++ was not a language we were working with often. This required some time to readapt.

The other challenges were related to understanding how to fulfill the assignment's requirements. The "what to do" was quite clear, but "how to get there" presented some roadblocks. For example, when creating the array with 100 million items, I had to use `malloc` to allocate that much memory, which I had never done before. This necessitated some effort to learn what was happening rather than just copying code from the internet.

I also attempted a different approach for the threading part. Before arriving at the working code, I tried creating a vector of threads and looping over that vector to run each task on a thread. However, it didn't work as expected, so I opted for a simpler approach, which yielded the code I am submitting.
