#include "coo.hpp"
#include "vec.hpp"
#include <iostream>

namespace coo {

// create a csr matrix
COOMatrix *create(const int n, const int nnz) {
  COOMatrix *ptr = new COOMatrix;
  ptr->v = new double[nnz];
  ptr->i = new int[nnz];
  ptr->j = new int[nnz];
  ptr->n = n;
  ptr->nnz = nnz;
  return ptr;
}

// destroy a csr matrix
void destroy(COOMatrix *mat) {
  if (!mat) return;
  delete(mat->i);
  delete(mat->j);
  delete(mat->v);
  delete(mat);
}

// assign a triplet (i,j,v)
bool assign_ijv(COOMatrix &mat, const int i, const int j, const double v,
                const int nnz_index) {
  bool fail = false;
  mat.i[nnz_index] = i;
  mat.j[nnz_index] = j;
  mat.v[nnz_index] = v;
  return fail;
}

// extract the diagonal values
bool extract_diag(const COOMatrix &A, vec::DenseVec &diag) {
  if (A.n != diag.n) return true;
  bool fail = false;
  for (int index=0; index<A.nnz; index++) {
    if (A.i[index] == A.j[index]){
      diag.value[A.i[index]] = A.v[index];
    }
  }

  // FINISH ME
  // extracting diagonal entries
  // FINISH ME
  return fail;
}

// matrix vector multiplication
bool mv(const COOMatrix &A, const vec::DenseVec &x, vec::DenseVec &y) {
    std::cout<<" Entering the mv of COO";
    bool fail = false;
    for(int i=0;i<A.n;i++){
      y.value[i]=0;
    }
    for (int index=0; index<A.nnz; index++) {
      y.value[A.i[index]]=y.value[A.i[index]]+ A.v[index]*x.value[A.j[index]];
      // std::cout<<" Vector index "<<A.i[index]<< "; Value at this index: "<<y.value[A.i[index]];
    }
  // FINISH ME
  // matrix vector multiplication
  // FINISH ME
  return fail;
}

}  // namespace coo