/**
 * Driver for Winsen ze08-ch2o formaldehyd sensors.
 *
 * Copyright 2018 Raul Salinas-Monteagudo
 */

#pragma once

#include <Stream.h>
#include <functional>

class Ze08CH2O {
public:
	// The type used for the measurements
    typedef unsigned short concentration_t;

    // Constructor. An optional parameter is a function that will be invoked on checksum errors
    Ze08CH2O(Stream * stream, std::function<void(void)> onBadChecksum = [](){});

    // Whether there is a reading available
    bool available() const {
        return available_;
    }

    // Return a reading, if available. Otherwise returns false.
	bool read(concentration_t& value);

	// Returns the maximum value this device can detect
	concentration_t getFullRange() const;

private:
    void resetState() {
        state = STATE_START;
    }
    enum State : char {
        STATE_START, STATE_GASNAME, STATE_UNIT, STATE_NODECIMAL,
        STATE_CONCENTRATION_HI, STATE_CONCENTRATION_LO,
        STATE_FULLRANGE_HI, STATE_FULLRANGE_LO, STATE_CHECKSUM
    } state = STATE_START;
    unsigned char dataSum;
    concentration_t concentration, fullrange = 0;
    concentration_t lastConcentration = 0;
	std::function<void(void)> onBadChecksum_;
	void run(unsigned char ch);
    Stream* stream_;
    concentration_t reading_ = 0;
    bool available_ = false;
};
