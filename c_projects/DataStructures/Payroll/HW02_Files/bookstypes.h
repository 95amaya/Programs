/*
 * Macro: New
 * Usage: p = New(pointer-type);
 * -----------------------------
 * The New pseudofunction allocates enough space to hold an
 * object of the type to which pointer-type points and returns
 * a pointer to the newly allocated pointer.  Note that
 * "New" is different from the "new" operator used in C++; 
 * the former takes a pointer type and the latter takes the
 * target type.
 */
#define New(type) ((type) malloc(sizeof *((type) NULL)))


/*
 * Macro: NewArray
 * Usage: p = NewArray(n, element-type);
 * -------------------------------------
 * NewArray allocates enough space to hold an array of n
 * values of the specified element type.
 */
#define NewArray(n, type) ((type *) malloc((n) * sizeof (type)))

