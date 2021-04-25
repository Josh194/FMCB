#pragma once

// TODO: this namespace should be more modularized
namespace registration_server {

    bool init();

    bool cycle();

    // ? Can this be done better?
    void cleanup();

}