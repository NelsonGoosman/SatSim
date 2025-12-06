# General
- This package contains examples of using the **Astrodynamics Standards (AS)** libraries in C

## Notes:
- C/C++ requires a NULL ('\0') terminating character in character arrays in order to print, 
  so it is highly recommended to allocate 1 array size larger than the required array size, 
  then setting this last position to NULL.  This applies to mainly to output parameters.  
  For example, if a function requires "char varname[8]", then create "char varname[9]" before 
  passing it to the function.  Upon return from the function, set the last position to NULL 
  (e.g.. varname[8]='\0').