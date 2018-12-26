////////////////////////////////////////////////////////////////////////////////
//
// Invariant Handling
//
// Macros for invariants for an arbitrary class
//
// PASW
//

#ifndef INVARIANT_H
#define INVARIANT_H

#include <iostream>
#include <stdlib.h>


#define INVARIANT_FAILURE(DATA) do {					\
    std::cerr << "Method " << DATA << ": Invariant Failure; Aborting" << std::endl; \
    abort();								\
  } while (0)

#define INVARIANT_TEST(TEST, DATA) do {		\
    if ((TEST)) {				\
      INVARIANT_FAILURE(DATA);			\
    }						\
  } while(0)

#endif
