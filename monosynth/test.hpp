#define _MAIKE_TARGET(x) TARGETS x
_MAIKE_TARGET(foo)
#define STR(x) #x
#define MAIKE_TARGET(x) STR(_MAIKE_TARGET(x))
MAIKE_TARGET(foo)

//#include MAIKE_TARGET(foo)