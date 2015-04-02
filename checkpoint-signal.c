//required headers
#include <unistd.h>

//[child] wait
char c; //stub char
read(checkpoint[0],&c,1);
//[parent] signal read code
close(checkpoint[1]);
