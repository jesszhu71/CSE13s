# Assignment 5
This program encodes a file using hamming codes (8, 4) and decodes the files, checking for any errors that happened between encoding and decoding. Error will inject errors into the encoded files to see how errors are corrected when decoding a file. Entropy will measure the amount of entropy generated. 
## Build

	$ make

## Running

	$ ./encode [-h] [-i infile] [-o outfile]
  	$ ./decode [-h] [-v] [-i infile] [-o outfile]
  	$ ./error [-h] [-s seed] [-e error_rate]
  	$ ./entropy < [input (reads from stdin)]

 **COMMAND LINE OPTIONS:**
 - -h: Program usage and help.
 - -v: Print statistics of decoding to stderr
 - -i infile: Input data to encode.
 - -o outfile: Output of encoded data.
 - -s seed: Specifies the random seed.
 - -e error_rate Specifies the error rate.


## Cleaning

	$ make clean
