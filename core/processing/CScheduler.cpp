#include "CScheduler.h"

#include "data/Database.h"

#include "modules/translate/Translate.h"

// TODO: cleanup
void scheduler::tmpProcess() {
    // TODO: allow variable number of subsystems
    if (database::clients.getLength() != 2) {
        return;
    }

    auto current = database::clients.getHead();

	for (unsigned int i = 0; i < database::clients.getLength(); i++) {
        translate::process(current -> data.communication, i, database::clients.getLength()); // TODO: can this be improved?

		current = current -> next;
    }
}