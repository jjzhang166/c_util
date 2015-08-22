#ifndef EZ_CUTIL_EZ_ATOMIC_H
#define EZ_CUTIL_EZ_ATOMIC_H

#define ATOM_CAS(ptr, oval, nval)         __sync_bool_compare_and_swap(ptr, oval, nval)
#define ATOM_CAS_POINTER(ptr, oval, nval) __sync_bool_compare_and_swap(ptr, oval, nval)

#define ATOM_INC(ptr)      __sync_add_and_fetch(ptr, 1)
#define ATOM_INC_N(ptr,n)  __sync_add_and_fetch(ptr, n)
#define ATOM_FINC(ptr)     __sync_fetch_and_add(ptr, 1)
#define ATOM_FINC_N(ptr,n) __sync_fetch_and_add(ptr, n)

#define ATOM_DEC(ptr)      __sync_sub_and_fetch(ptr, 1)
#define ATOM_DEC_N(ptr,n)  __sync_sub_and_fetch(ptr, n)
#define ATOM_FDEC(ptr)     __sync_fetch_and_sub(ptr, 1)
#define ATOM_FDEC_N(ptr,n) __sync_fetch_and_sub(ptr, n)

/* Atomic BIT operator */
#define ATOM_AND(ptr,n)    __sync_and_and_fetch(ptr, n)

#endif //EZ_CUTIL_EZ_ATOMIC_H
