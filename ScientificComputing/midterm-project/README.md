# AMS 562 Midterm Project #
## Sparse Matrix Storage Schemes ##

In this project, you need to finish implementing the routines described
the project, i.e. matrix initialization and finalization, matrix construction,
matrix vector multiplication and extracting diagonal entries.

Regarding the dense vector, I have implemented `DenseVec` under `srcs/vec.hpp`
and `srcs/vec.cpp`.

To be more precise, you need to implement:

1. `create` and `destroy` in `srcs/coo.cpp` and `srcs/csr.cpp`
2. `mv` in `srcs/coo.cpp` and `srcs/csr.cpp`
3. `extract_diag` in `srcs/coo.cpp` and `srcs/csr.cpp`
4. `assign_ijv` in `srcs/coo.cpp`
5. `assign_row` in `srcs/crs.cpp`

I have implemented the `main.cpp` program that calls the routines you need to
implement. In addition, I have implemented some utility functions to load
data from ASCII files under `test_data/`.

Once you have finish implementing the requirements above, you can simply
type `make` to run the test program, you will get full credits if you **PASS**
all tests (**PASS** will be printed out in green color in the terminal/console).

The first thing you should do is under our Docker image (or any other proper
Linux/UNIX environments), see whether or not you can compile and run the
program, i.e. type `make`. To clean all object and executable binaries, just
type `make clean`.

**Be aware that most functions return a boolean flag to indicate the return
status, if the flag is TRUE, which means failure, FALSE for successful
return status**

## Hints ##

Recall that to access an entry of a `struct`, you need to use the accessing
operator `.`, e.g. for `COOMatrix`, `mat.i` is the array of row indices;
for `CSRMatrix`, `mat.indptr` is the `indptr` array.

Don't forget the set the size information for the matrices when you
initializing them, i.e. for `COOMatrix`, `mat.n` is the shape of the square
matrix, and `mat.nnz` is the total number of non-zeros; for `CSRMatrix`,
only `mat.n` is needed.

For the `DenseVec`, the values are stored in memory space `vec.value` and the
size of the vector is given in `vec.n`.

Please look at the header files, i.e. `srcs/*.hpp`, and all APIs are documented
clearly.

Take a look at `srcs/vec.cpp` for initialization and finalization
implementation examples.


# Implementation #
## Git changes ##
> **Created Midterm Project:**
1. Created Midterm project repo - https://github.com/krishnasree45/midterm-project
2. Other team members cloned the repo using - _git clone https://github.com/krishnasree45/midterm-project_

>**Removed existing midterm in AMS562 repo:**
1. Deleted midterm_project folder in AMS562 repo locally. 
2. Added and committed the changes in the _main_ branch of AMS562.

>**Added Midterm project as a submodule to AMS562 repo:**

In the main branch of AMS562 locally do the following steps:
  1. To add submodule - git submodule add 'git@github.com:krishnasree45/midterm-project.git'
  2. Commit the changes - git commit -m "Added submodule"
  3. And push changes from local to remote - git push 

>**Add signature to the commits:**
1. Each member created a branch using the format - _midterm/firstName_. 
2. Added signature to the commits using GPG key using the following steps:
    1. Generate gpg key using: _gpg --gen-key_
    2. Export the GPG key : _gpg key: gpg --export --armor <email_id>_
    3. Copy the GPG key and added it to the remote in github.
    4. Send the gpg public key to the server using the following commmand: _gpg --send-keys B036DF91094219DC_
    5. To fix git signature issue: _export GPG_TTY=$(tty)_
    
 ## Compressed sparse Row matrix: ##
 
 >**Creating CSR**
 1. Create a new ptr of CSRMatrix ? CSRMatrix *ptr = new CSRMatrix;
 2. Initialise the member variables of CSRMatrix:
       1. ptr->value = new double[nnz];
       2. ptr->indices = new int[nnz];
       3. ptr->indptr = new int[n+1];
       4. ptr->n = n;
 3. Return the ptr
 
 >**Destroy CSR**
 1. Use the _delete_ keyword to free the memory after using the structure.
 
 >**Assign a row in CSR:**
 1. For the 0th row, assign the indptr[0] to 0 and indptr[1] to the total number of non-zero elements in the 0th row.
2. For all other rows, assign the indptr[row+1] to inptr[row]+total number of non-zero elements for the row.
3. Assign the indices and values by looping through all the non zero elements in the row starting from the index value of indptr[row].

>**Extract the diagonal in CSR:**
1. For each row in the CSR matrix, mark the start index as indptr[i] and end index as indptr[i+1]-1, find the diagonal elements using the binary search implementation.
2. * Binary Search: * It is a searching technique that divides the search interval in half periodically in a sorted array. The goal behind binary search is to exploit the array's sorted information to minimize the time complexity from O(n) to O(Log n).

>**Binary Search implementation in CSR:**
1.	Begin by using the array's midpoint as a search key
2.	If the search key's value equals the item, return the search key's index.
3.	Alternatively, if the value of the search key is smaller than the item in the interval's middle, limit the interval to the bottom half.
4.	Otherwise, limit it to the top half.
5.	Check from the second point again and again until the value is discovered or the interval is empty.
6.	We have implemented this algorithm using recursion.

>**Matrix Vector multiplication in CSR:**
1.	For each row in the CSR matrix, we multiply the non-zero values of the CSR matrix with the corresponding column elements in the vector and sum them up.
2.	We then store this sum as the first element of the resultant vector. 


## Coordinate Format matrix: ##

>**Creating COO:**
1.	Created a new ptr of COOMatrix ? COOMatrix *ptr = new COOMatrix;
2.	Initialised the member variables of COOMatrix:
    1. ptr->v = new double[nnz];  
    2. ptr->i = new int[nnz];
	3. ptr->j = new int[nnz];
	4. ptr->n = n;
	5. ptr->nnz = nnz;
3. Return the ptr

>**Destroy COO:**
1. Used the _delete_ keyword to free the memory after using the structure.

>**Assign the triplets(i,j,v) in COO:**
1.	Assigned the triplets of row index (i), column index (j) and their corresponding value entry (v).
    1. mat.i[nnz_index] = i;  
    2. mat.j[nnz_index] = j;
    3. mat.v[nnz_index] = v;
    
>**Extract the diagonal in COO:**
1. We extracted the diagonal by iterating through the non-zero values in the matrix A and checked if the index of the row indices (i) is same as the index of the column indices(j).

>**Matrix Vector multiplication in COO:**
1. For each row in the COO matrix, we multiplied the non-zero values of the COO matrix with the corresponding column elements in the vector and sum them up.
