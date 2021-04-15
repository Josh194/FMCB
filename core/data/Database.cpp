#include "Database.h"

LinkedArray<Client, 8> database::clients = LinkedArray<Client, 8>(); // ? Why can't this be initialized in a method? If it is, memory gets badly corrupted.