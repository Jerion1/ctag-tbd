#include <atomic>
#include "ctagSoundProcessor.hpp"

namespace CTAG {
    namespace SP {
        class ctagSoundProcessortemplate : public ctagSoundProcessor {
        public:
            virtual void Process(const ProcessData &) override;
            ctagSoundProcessortemplate();
            virtual ~ctagSoundProcessortemplate();

        private:
            virtual void knowYourself() override;

            // private attributes could go here
            // autogenerated code here
            // sectionHpp
	atomic<int32_t> undefined, cv_undefined;
	// sectionHpp
        };
    }
}