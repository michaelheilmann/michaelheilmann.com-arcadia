#if !defined(R_EXCEPTION_H_INCLUDED)
#define R_EXCEPTION_H_INCLUDED

/// @brief Set the exception value.
/// @param value The exception value.
void R_setException(R_Value value);

/// @brief Get the exception value.
/// @return The exception value.
R_Value R_getException();

#endif // R_EXCEPTION_H_INCLUDED
