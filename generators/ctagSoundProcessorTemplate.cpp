#include "ctagSoundProcessortemplate.hpp"

using namespace CTAG::SP;

void ctagSoundProcessortemplate::Process(const ProcessData &data) {
}

ctagSoundProcessortemplate::ctagSoundProcessortemplate() {
    // construct internal data model
    knowYourself();
    model = std::make_unique<ctagSPDataModel>(id, isStereo);
    LoadPreset(0);
}

ctagSoundProcessortemplate::~ctagSoundProcessortemplate() {
}

void ctagSoundProcessortemplate::knowYourself(){
    // autogenerated code here
    // sectionCpp0
	pMapPar.emplace("undefined", [&](const int val){ undefined = val;});
	pMapCv.emplace("undefined", [&](const int val){ cv_undefined = val;});
	isStereo = true;
	id = "template";
	// sectionCpp0
}