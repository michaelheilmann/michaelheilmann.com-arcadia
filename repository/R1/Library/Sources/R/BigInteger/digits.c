#include "R/BigInteger/digits.h"

#include "Arms.h"
#include "R/DynamicArrayUtilities.h"

void
Digits_allocate
  (
    Arcadia_Process* process,
    R_BigInteger_Digit** array,
    Arcadia_SizeValue capacity
  )
{
  if (Arms_MemoryManager_allocate(Arms_getDefaultMemoryManager(), array, sizeof(R_BigInteger_Digit) * (capacity))) {
    Arcadia_Process_setStatus(process, Arcadia_Status_AllocationFailed);
    Arcadia_Process_jump(process);
  }
}

void
Digits_deallocate
  (
    R_BigInteger_Digit* array
  )
{
  Arms_MemoryManager_deallocate(Arms_getDefaultMemoryManager(), array);
}

void
Digits_reallocate
  (
    Arcadia_Process* process,
    R_BigInteger_Digit** array,
    Arcadia_SizeValue capacity
  )
{
  if (Arms_MemoryManager_reallocate(Arms_getDefaultMemoryManager(), array, sizeof(R_BigInteger_Digit) * (capacity))) {
    Arcadia_Process_setStatus(process, Arcadia_Status_AllocationFailed);
    Arcadia_Process_jump(process);
  }
}

void
Digits_ensureFreeCapacity
  (
    Arcadia_Process* process,
    R_BigInteger_Digit** array,
    Arcadia_SizeValue size,
    Arcadia_SizeValue* capacity,
    Arcadia_SizeValue requiredFreeCapacity
  )
{
  if (R_DynamicArrayUtilities_ensureFreeCapacity(array, sizeof(R_BigInteger_Digit), size, capacity, requiredFreeCapacity, R_DynamicArrayUtilities_GrowthStrategy4)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_AllocationFailed);
    Arcadia_Process_jump(process);
  }
}
