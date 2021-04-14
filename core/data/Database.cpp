#include "Database.h"

LinkedArray<Client, 32> database::clients;

void database::init() {
   clients = LinkedArray<Client, 32>();
}