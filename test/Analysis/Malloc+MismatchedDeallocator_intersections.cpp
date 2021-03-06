// RUN: %clang_cc1 -analyze -analyzer-checker=core,unix.Malloc,unix.MismatchedDeallocator -analyzer-store region -std=c++11 -verify %s
// expected-no-diagnostics

typedef __typeof(sizeof(int)) size_t;
void *malloc(size_t);
void free(void *);

//--------------------------------------------------------------------
// Check that unix.Malloc + unix.MismatchedDeallocator does not enable
// warnings produced by the alpha.cplusplus.NewDelete checker.
//--------------------------------------------------------------------
void testNewDeleteNoWarn() {
  int i;
  delete &i; // no-warning

  int *p1 = new int;
  delete ++p1; // no-warning

  int *p2 = new int;
  delete p2;
  delete p2; // no-warning

  int *p3 = new int; // no-warning

  int *p4 = new int;
  delete p4;
  int j = *p4; // no-warning  
}
