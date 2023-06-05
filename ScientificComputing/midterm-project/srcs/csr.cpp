// This is the source file that contains the implementation of
// CSRMatrix and its corresponding functions

#include "csr.hpp"
#include "vec.hpp"

#include <iostream>
using namespace std;
namespace csr {

    double binarySearch(const CSRMatrix &A, int x, int l, int r)
    {
        if (r >= l) {
            int mid = l + (r - l) / 2;
            if (A.indices[mid] == x)
                return A.value[mid];
            if (A.indices[mid] > x)
                return binarySearch(A, x, l, mid - 1);
            return binarySearch(A, x, mid + 1, r);
        }
        return 0;
    }
// impls

// create a csr matrix
CSRMatrix *create(const int n, const int nnz) {
  CSRMatrix *ptr = new CSRMatrix;
  ptr->value = new double[nnz];
  ptr->indices = new int[nnz];
  ptr->indptr = new int[n+1];
  ptr->n = n;
  return ptr;
}

// destroy a csr matrix
void destroy(CSRMatrix *mat) {
  if (!mat) {
    return;
  }
  else{
      delete []mat;
  }
}

// assign a row
bool assign_row(CSRMatrix &mat, const int row, const int *cols,
                const double *vals, const int nnz) {
  int start;
  if (row < 0 || row > mat.n || nnz < 0) return true;
  else if(row == 0){
    start =0;
    mat.indptr[row] = 0;
  }
  else{
    start = mat.indptr[row];
  }
  
  // bonus, this is how to get the starting entry of this row
  
  mat.indptr[row+1] = start+nnz;
  for(int i=0;i<nnz;i++){
      mat.indices[start+i] = cols[i];
      mat.value[start+i] = vals[i];
  }
  return false;
}

// extract the diagonal values
bool extract_diag(const CSRMatrix &A, vec::DenseVec &diag) {
  if (A.n != diag.n) return true;
  int index =0;
  for(int i =0; i<A.n;i++){
      bool diagonal_found = false;
      int strt_idx = A.indptr[i];
      int end_idx = A.indptr[i+1]-1;
      diag.value[index] = binarySearch(A, i, strt_idx, end_idx);
      index++;
  }
  return false;
}

// matrix vector multiplication
bool mv(const CSRMatrix &A, const vec::DenseVec &x, vec::DenseVec &y) {
  for(int i=0;i<A.n;i++){
    double sum =0;
    for(int j=A.indptr[i];j<A.indptr[i+1];j++){
      sum+=A.value[j]*x.value[A.indices[j]];
    }
    y.value[i] = sum;
  }
  return false;
}

}  // namespace csr