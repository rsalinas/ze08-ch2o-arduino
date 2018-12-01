/**
 * Copyright 2018 Raul Salinas-Monteagudo
 */

#include "ze08_ch2o.h"

Ze08CH2O::Ze08CH2O(Stream * stream, std::function<void(void)> onBadChecksum) : stream_(stream), onBadChecksum_(onBadChecksum) {
}

bool Ze08CH2O::read(concentration_t& value) {
	while (stream_->available()) {
		run(stream_->read());
	}
	if (!available_)
		return false;
	value = reading_;
	available_= false;
	return true;
}
Ze08CH2O::concentration_t Ze08CH2O::getFullRange() const {
  return fullrange;
}


void Ze08CH2O::run(unsigned char ch) {
	switch (state) {
	case STATE_START:
		if (ch == 0xFFu) {
			dataSum = 0;
			state = STATE_GASNAME;
			return;
		}
		break;
	case STATE_GASNAME:
		if (ch != 0x17) {
			resetState();
			return;
		}
		break;
	case STATE_UNIT:
		if (ch != 0x04) {
			resetState();
			return;
		}
		break;
	case STATE_NODECIMAL:
		if (ch != 0) {
			resetState();
			return;
		}
		break;
	case STATE_CONCENTRATION_HI:
		concentration = ch << 8;
		break;
	case STATE_CONCENTRATION_LO:
		concentration |= ch;
		break;
	case STATE_FULLRANGE_HI:
		fullrange = ch << 8;
		break;
	case STATE_FULLRANGE_LO:
		fullrange |= ch;
		break;
	case STATE_CHECKSUM:
		unsigned char finalEcksum  = (~dataSum)+1 ;
		if (finalEcksum   == ch ) {
			if (lastConcentration != concentration) {
				available_ = true;
				reading_ = concentration;
				lastConcentration = concentration;
			}
		} else {
			onBadChecksum_();
		}
		state = STATE_START;
		return;

	}
	dataSum += ch;
	state = (State) (state + 1);
}
