# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

a disease of the lungs resulting from the inhalation of very fine silicate or quartz dust

## According to its man page, what does `getrusage` do?

int getrusage(int who, struct rusage *usage);
getrusage() returns resource usage measures for who, which can be one of the following:

       RUSAGE_SELF
              Return resource usage statistics for the calling process,
              which is the sum of resources used by all threads in the
              process.

       RUSAGE_CHILDREN
              Return resource usage statistics for all children of the
              calling process that have terminated and been waited for.
              These statistics will include the resources used by
              grandchildren, and further removed descendants, if all of the
              intervening descendants waited on their terminated children.

       RUSAGE_THREAD (since Linux 2.6.26)
              Return resource usage statistics for the calling thread.  The
              _GNU_SOURCE feature test macro must be defined (before
              including any header file) in order to obtain the definition
              of this constant from <sys/resource.h>.




## Per that same man page, how many members are in a variable of type `struct rusage`?

16:
           struct rusage {
               struct timeval ru_utime; /* user CPU time used */
               struct timeval ru_stime; /* system CPU time used */
               long   ru_maxrss;        /* maximum resident set size */
               long   ru_ixrss;         /* integral shared memory size */
               long   ru_idrss;         /* integral unshared data size */
               long   ru_isrss;         /* integral unshared stack size */
               long   ru_minflt;        /* page reclaims (soft page faults) */
               long   ru_majflt;        /* page faults (hard page faults) */
               long   ru_nswap;         /* swaps */
               long   ru_inblock;       /* block input operations */
               long   ru_oublock;       /* block output operations */
               long   ru_msgsnd;        /* IPC messages sent */
               long   ru_msgrcv;        /* IPC messages received */
               long   ru_nsignals;      /* signals received */
               long   ru_nvcsw;         /* voluntary context switches */
               long   ru_nivcsw;        /* involuntary context switches */
           };



## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

to take advantage of sys/resource.h library and use before and after as rusage structures predefined in the library

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

The loop in main is reading one letter of the file at a time until end of file.

    If the character is alphabetical, or the character is an apostrophe, add the character to the word at index. Increase index by 1.
        If index is greater than 45 (the global variable from dictionary.h), then ignore rest of the word and set index to zero.
    Else if the charcter is a digit, then ignore the rest of the word and set index to zero.
    Else if index is greater then zero, then end the word by putting \0 and update the word counter.
        Check the word's spelling and update the benchmark. Print the word if mispelled. Prepare for the next word.


## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

fscanf with a format string like "%s" will read subsequent characters
until a whitespace is found (whitespace characters are considered to be
blank, newline and tab). Because words within the txt files sometimes
end with punctuation, fscanf will view them as being part of the word,
which complicates the reading procedure. In addition, if a longer string
than expected was read using fscanf (e.g. a jibberish string like asdfba
asdkdfawemflkasciaoeufalkesfasldkfjaoiwefjaslkdmcalksdfiwoefalskdfamsdcl
asdflkasdlkmceaasdfasdf..., which could be included in a text file from
a malicious source that is trying to break our program), we could
overwrite important data in memory or cause a segmentation fault.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

const char *ptr : This is a pointer to a constant character.
You cannot change the value pointed by ptr, but you can change the pointer itself.
The parameters for check (const char* word)
and load (const char* dictionary) are declared as const pointers because
we want to prevent changes to a read word and the dictionary we are using.

Mutable pointer to a mutable character
char *p;

Mutable pointer to a constant character
const char *p;

Constant pointer to a mutable character
char * const p;

Constant pointer to a constant character
const char * const p;