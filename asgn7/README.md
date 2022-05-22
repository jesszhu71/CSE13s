# Assignment 7

Link to assignment instructions [pdf](https://github.com/jesszhu71/CSE13s/blob/main/asgn7/assignments_asgn7.pdf)

  This program will filter out words that are banned. Words will be parsed from stdin and banned words will be read in from badspeak.txt and newspeak.txt. Any changes in speech vocabulary will be notified to the user.
  
## Build

	$ make

## Running

	$ ./banhammer [-hsm] [-t size] [-f size]

 **COMMAND LINE OPTIONS:**
 - -h: Program usage and help.
 - -s: Print program statistics.
 - -m: Enable move-to-front rule.
 - -t size: Specify hash table size (default: 10000)
 - -f size: Specify Bloom filter size (default: 2^20)

## Cleaning

	$ make clean
