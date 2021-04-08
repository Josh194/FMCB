#pragma once

/*
Contains functions needed to interact with the shared IPC buffer.
*/
namespace communication {

	/*
	Maps the IPC buffer into the memory of the calling process.
	
	By using the returned address, a process can interact with the buffer as if it were part of it's own memory.
	
	Returns NULL if the function fails.
	*/
	void* map();

	/*
	Unmaps the IPC buffer from the calling process's memory space and closes the associated handle.
	
	This function will attempt to close the associated handle regardless of whether or not it was able to unmap the buffer, though the return value will reflect the failure.
	Failure to fully complete may result in the buffer staying in system memory until a restart, so processes should strive to insure this function can fully complete,
	or cleanup manually if that is not possible for whatever reason.
	
	Returns
		0: If the function completed successfully.
		1: If the function failed to unmap the buffer.
		2: If the function failed to close the mapping handle.
		3: If the function failed.
	*/
	char unmap();

}