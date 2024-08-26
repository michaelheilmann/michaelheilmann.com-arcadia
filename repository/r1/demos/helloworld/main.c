#include <stdlib.h>
#include "r.h"
#include "arms1.h"

int main(int argc, char** argv) {
  R_Status status = R_startup();
  if (status) {
    return EXIT_FAILURE;
  }
  status = R_shutdown();
  return status ? EXIT_FAILURE : EXIT_SUCCESS;
}
