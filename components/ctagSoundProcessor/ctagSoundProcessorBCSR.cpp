#include "ctagSoundProcessorBCSR.hpp"
#include <iostream>
#include <cmath>
#include "helpers/ctagFastMath.hpp"
#include "esp_log.h"

using namespace CTAG::SP;

#define MAX_GAIN 20.f

ctagSoundProcessorBCSR::ctagSoundProcessorBCSR() {
    setIsStereo();
    model = std::make_unique<ctagSPDataModel>(id, isStereo);
    model->LoadPreset(0);

    // inits
    prevSample = 0.f;
    phase = 0.f;
    egSR.SetSampleRate(44100.f);
    egSR.SetModeLin();
    egBC.SetSampleRate(44100.f);
    egBC.SetModeLin();
    bcEGTrig = true;
    srEGTrig = true;
}

// adapted from https://www.musicdsp.org/en/latest/Effects/139-lo-fi-crusher.html

void ctagSoundProcessorBCSR::Process(const ProcessData &data) {
    // Sample rate reduce params
    float fNormFreq;
    if(cv_sr_amount != -1){
        fNormFreq = 0.51f * (1.f - HELPERS::fastfabs(data.cv[cv_sr_amount]));
    }else{
        fNormFreq = 0.51f * (4095 - sr_amount) / 4095.f;
    }
    bool isSRReduce;
    if(trig_sr_ena != -1){
        isSRReduce = data.trig[trig_sr_ena] != 1;
    }else{
        isSRReduce = sr_ena;
    }

    // Bit crush params
    float fScale;
    if(cv_bc_amount != -1){
        fScale = 16.f - HELPERS::fastfabs(data.cv[cv_bc_amount]) * 15.f;
    }else{
        fScale = 16.f - bc_amount / 4095.f * 15.f;
    }
    bool isBitCrush;
    if(trig_bc_ena != -1){
        isBitCrush = data.trig[trig_bc_ena] != 1;
    }else{
        isBitCrush = bc_ena;
    }

    // gain params
    float fGain;
    if(cv_level != -1){
        fGain = data.cv[cv_level] * data.cv[cv_level] * MAX_GAIN;
    }else{
        fGain = level / 4095.f * MAX_GAIN;
    }
    float fDry;
    if(cv_dry != -1){
        fDry = data.cv[cv_dry] * data.cv[cv_dry];
    }else{
        fDry = dry / 4095.f;
    }
    bool isInvertWet;
    if(trig_invert != -1){
        isInvertWet = data.trig[trig_invert] != 1;
    }else{
        isInvertWet = invert;
    }

    // BC envelope
    if(trig_eg_bc_ena != -1){
        if(data.trig[trig_eg_bc_ena] != bcEGTrig){
            bcEGTrig = data.trig[trig_eg_bc_ena];
            if(!bcEGTrig) egBC.Trigger();
        }
    }else{
        if(eg_bc_ena != bcEGTrig){
            bcEGTrig = eg_bc_ena;
            if(bcEGTrig) egBC.Trigger();
        }
    }
    if(trig_eg_bc_loop != -1){
        egBC.SetLoop(data.trig[trig_eg_bc_loop] != 1);
    }else{
        egBC.SetLoop(eg_bc_loop);
    }
    float fEGBCAmount;
    if(cv_eg_bc_amount != -1){
        fEGBCAmount = -8.f * data.cv[cv_eg_bc_amount];
    }else{
        fEGBCAmount = eg_bc_amount / 4095.f * -8.f;
    }
    if(cv_eg_bc_att != -1){
        egBC.SetAttack(data.cv[cv_eg_bc_att] * data.cv[cv_eg_bc_att]);
    }else{
        egBC.SetAttack(eg_bc_att / 4095.f);
    }
    if(cv_eg_bc_dec != -1){
        egBC.SetDecay(data.cv[cv_eg_bc_dec] * data.cv[cv_eg_bc_dec]);
    }else{
        egBC.SetDecay(eg_bc_dec / 4095.f);
    }
    if(eg_bc_le)egBC.SetModeExp(); else egBC.SetModeLin();

    // SR envelope
    if(trig_eg_sr_ena != -1){
        if(data.trig[trig_eg_sr_ena] != srEGTrig){
            srEGTrig = data.trig[trig_eg_sr_ena];
            if(!srEGTrig) egSR.Trigger();
        }
    }else{
        if(eg_sr_ena != srEGTrig){
            srEGTrig = eg_sr_ena;
            if(srEGTrig) egSR.Trigger();
        }
    }
    if(trig_eg_sr_loop != -1){
        egSR.SetLoop(data.trig[trig_eg_sr_loop] != 1);
    }else{
        egSR.SetLoop(eg_sr_loop);
    }
    float fEGSRAmount;
    if(cv_eg_sr_amount != -1){
        fEGSRAmount = -0.5f * data.cv[cv_eg_sr_amount];
    }else{
        fEGSRAmount = eg_sr_amount / 4095.f * -0.5f;
    }
    if(cv_eg_sr_att != -1){
        egSR.SetAttack(data.cv[cv_eg_sr_att] * data.cv[cv_eg_sr_att]);
    }else{
        egSR.SetAttack(eg_sr_att / 4095.f);
    }
    if(cv_eg_sr_dec != -1){
        egSR.SetDecay(data.cv[cv_eg_sr_dec] * data.cv[cv_eg_sr_dec]);
    }else{
        egSR.SetDecay(eg_sr_dec / 4095.f);
    }
    if(eg_sr_le)egSR.SetModeExp(); else egSR.SetModeLin();

    // process values
    for (int i = 0; i < bufSz; ++i) {
        float out;

        if(isSRReduce){
            float dPhase = fNormFreq + egSR.Process() * fEGSRAmount;
            if(dPhase < 1.f/44100.f) dPhase = 1.f/44100.f;
            if(dPhase > 0.5f) fNormFreq = 1.f;
            phase += dPhase;
            if(phase >= 1.f){
                phase -= 1.f;
                prevSample = data.buf[i*2 + processCh];
            }
            out = prevSample;
        }else{
            out = data.buf[i*2 + processCh];
        }

        out *= fGain;

        if(isBitCrush){
            float crush = egBC.Process() * fEGBCAmount + fScale;
            if(crush < 0.f) crush = 0.f;
            if(crush > 16.f) crush = 16.f;
            crush = HELPERS::fastpow2(crush);
            if(HELPERS::fastfabs(out) < 1.f / crush) out = 0.f;
            out = floorf(out * crush) / crush;
        }

        out = HELPERS::fasttanh(out); // saturate

        if(isInvertWet) out *= -1.f;

        data.buf[i*2 + processCh] = out + data.buf[i*2 + processCh] * fDry;
    }
}

ctagSoundProcessorBCSR::~ctagSoundProcessorBCSR() {
}

const char *ctagSoundProcessorBCSR::GetCStrID() const {
    return id.c_str();
}


void ctagSoundProcessorBCSR::setParamValueInternal(const string& id, const string& key, const int val) {
// autogenerated code here
// sectionCpp0
if(id.compare("level") == 0){
	if(key.compare("current") == 0){
		level = val;
		return;
	}
	if(key.compare("cv") == 0){
		if(val >= -1 && val <= 3)
			cv_level = val;
		return;
	}
}
if(id.compare("invert") == 0){
	if(key.compare("current") == 0){
		invert = val;
		return;
	}
	if(key.compare("trig") == 0){
		if(val >= -1 && val <= 1)
			trig_invert = val;
		return;
	}
}
if(id.compare("dry") == 0){
	if(key.compare("current") == 0){
		dry = val;
		return;
	}
	if(key.compare("cv") == 0){
		if(val >= -1 && val <= 3)
			cv_dry = val;
		return;
	}
}
if(id.compare("bc_ena") == 0){
	if(key.compare("current") == 0){
		bc_ena = val;
		return;
	}
	if(key.compare("trig") == 0){
		if(val >= -1 && val <= 1)
			trig_bc_ena = val;
		return;
	}
}
if(id.compare("bc_amount") == 0){
	if(key.compare("current") == 0){
		bc_amount = val;
		return;
	}
	if(key.compare("cv") == 0){
		if(val >= -1 && val <= 3)
			cv_bc_amount = val;
		return;
	}
}
if(id.compare("eg_bc_ena") == 0){
	if(key.compare("current") == 0){
		eg_bc_ena = val;
		return;
	}
	if(key.compare("trig") == 0){
		if(val >= -1 && val <= 1)
			trig_eg_bc_ena = val;
		return;
	}
}
if(id.compare("eg_bc_loop") == 0){
	if(key.compare("current") == 0){
		eg_bc_loop = val;
		return;
	}
	if(key.compare("trig") == 0){
		if(val >= -1 && val <= 1)
			trig_eg_bc_loop = val;
		return;
	}
}
if(id.compare("eg_bc_le") == 0){
	if(key.compare("current") == 0){
		eg_bc_le = val;
		return;
	}
	if(key.compare("trig") == 0){
		if(val >= -1 && val <= 1)
			trig_eg_bc_le = val;
		return;
	}
}
if(id.compare("eg_bc_amount") == 0){
	if(key.compare("current") == 0){
		eg_bc_amount = val;
		return;
	}
	if(key.compare("cv") == 0){
		if(val >= -1 && val <= 3)
			cv_eg_bc_amount = val;
		return;
	}
}
if(id.compare("eg_bc_att") == 0){
	if(key.compare("current") == 0){
		eg_bc_att = val;
		return;
	}
	if(key.compare("cv") == 0){
		if(val >= -1 && val <= 3)
			cv_eg_bc_att = val;
		return;
	}
}
if(id.compare("eg_bc_dec") == 0){
	if(key.compare("current") == 0){
		eg_bc_dec = val;
		return;
	}
	if(key.compare("cv") == 0){
		if(val >= -1 && val <= 3)
			cv_eg_bc_dec = val;
		return;
	}
}
if(id.compare("sr_ena") == 0){
	if(key.compare("current") == 0){
		sr_ena = val;
		return;
	}
	if(key.compare("trig") == 0){
		if(val >= -1 && val <= 1)
			trig_sr_ena = val;
		return;
	}
}
if(id.compare("sr_amount") == 0){
	if(key.compare("current") == 0){
		sr_amount = val;
		return;
	}
	if(key.compare("cv") == 0){
		if(val >= -1 && val <= 3)
			cv_sr_amount = val;
		return;
	}
}
if(id.compare("eg_sr_ena") == 0){
	if(key.compare("current") == 0){
		eg_sr_ena = val;
		return;
	}
	if(key.compare("trig") == 0){
		if(val >= -1 && val <= 1)
			trig_eg_sr_ena = val;
		return;
	}
}
if(id.compare("eg_sr_loop") == 0){
	if(key.compare("current") == 0){
		eg_sr_loop = val;
		return;
	}
	if(key.compare("trig") == 0){
		if(val >= -1 && val <= 1)
			trig_eg_sr_loop = val;
		return;
	}
}
if(id.compare("eg_sr_le") == 0){
	if(key.compare("current") == 0){
		eg_sr_le = val;
		return;
	}
	if(key.compare("trig") == 0){
		if(val >= -1 && val <= 1)
			trig_eg_sr_le = val;
		return;
	}
}
if(id.compare("eg_sr_amount") == 0){
	if(key.compare("current") == 0){
		eg_sr_amount = val;
		return;
	}
	if(key.compare("cv") == 0){
		if(val >= -1 && val <= 3)
			cv_eg_sr_amount = val;
		return;
	}
}
if(id.compare("eg_sr_att") == 0){
	if(key.compare("current") == 0){
		eg_sr_att = val;
		return;
	}
	if(key.compare("cv") == 0){
		if(val >= -1 && val <= 3)
			cv_eg_sr_att = val;
		return;
	}
}
if(id.compare("eg_sr_dec") == 0){
	if(key.compare("current") == 0){
		eg_sr_dec = val;
		return;
	}
	if(key.compare("cv") == 0){
		if(val >= -1 && val <= 3)
			cv_eg_sr_dec = val;
		return;
	}
}
// sectionCpp0







}

void ctagSoundProcessorBCSR::loadPresetInternal() {
// autogenerated code here
// sectionCpp1
level = model->GetParamValue("level", "current");
cv_level = model->GetParamValue("level", "cv");
invert = model->GetParamValue("invert", "current");
trig_invert = model->GetParamValue("invert", "trig");
dry = model->GetParamValue("dry", "current");
cv_dry = model->GetParamValue("dry", "cv");
bc_ena = model->GetParamValue("bc_ena", "current");
trig_bc_ena = model->GetParamValue("bc_ena", "trig");
bc_amount = model->GetParamValue("bc_amount", "current");
cv_bc_amount = model->GetParamValue("bc_amount", "cv");
eg_bc_ena = model->GetParamValue("eg_bc_ena", "current");
trig_eg_bc_ena = model->GetParamValue("eg_bc_ena", "trig");
eg_bc_loop = model->GetParamValue("eg_bc_loop", "current");
trig_eg_bc_loop = model->GetParamValue("eg_bc_loop", "trig");
eg_bc_le = model->GetParamValue("eg_bc_le", "current");
trig_eg_bc_le = model->GetParamValue("eg_bc_le", "trig");
eg_bc_amount = model->GetParamValue("eg_bc_amount", "current");
cv_eg_bc_amount = model->GetParamValue("eg_bc_amount", "cv");
eg_bc_att = model->GetParamValue("eg_bc_att", "current");
cv_eg_bc_att = model->GetParamValue("eg_bc_att", "cv");
eg_bc_dec = model->GetParamValue("eg_bc_dec", "current");
cv_eg_bc_dec = model->GetParamValue("eg_bc_dec", "cv");
sr_ena = model->GetParamValue("sr_ena", "current");
trig_sr_ena = model->GetParamValue("sr_ena", "trig");
sr_amount = model->GetParamValue("sr_amount", "current");
cv_sr_amount = model->GetParamValue("sr_amount", "cv");
eg_sr_ena = model->GetParamValue("eg_sr_ena", "current");
trig_eg_sr_ena = model->GetParamValue("eg_sr_ena", "trig");
eg_sr_loop = model->GetParamValue("eg_sr_loop", "current");
trig_eg_sr_loop = model->GetParamValue("eg_sr_loop", "trig");
eg_sr_le = model->GetParamValue("eg_sr_le", "current");
trig_eg_sr_le = model->GetParamValue("eg_sr_le", "trig");
eg_sr_amount = model->GetParamValue("eg_sr_amount", "current");
cv_eg_sr_amount = model->GetParamValue("eg_sr_amount", "cv");
eg_sr_att = model->GetParamValue("eg_sr_att", "current");
cv_eg_sr_att = model->GetParamValue("eg_sr_att", "cv");
eg_sr_dec = model->GetParamValue("eg_sr_dec", "current");
cv_eg_sr_dec = model->GetParamValue("eg_sr_dec", "cv");
// sectionCpp1







}
