#ifndef CRTP_CAST
#define CRTP_CAST(T, val) (static_cast<const T &>(val))
#endif
