#include <atomic>
#include "ctagSoundProcessor.hpp"

namespace CTAG {
    namespace SP {
        class ctagSoundProcessorbbeats : public ctagSoundProcessor {
        public:
            virtual void Process(const ProcessData &) override;
            ctagSoundProcessorbbeats();
            virtual ~ctagSoundProcessorbbeats();

        private:
            virtual void knowYourself() override;

            inline static int process_param( const ProcessData &data, int cv_myparm, int my_parm, int parm_range ); // rescale incoming data
            inline static float process_param_float( const ProcessData &data, int cv_myparm, int my_parm ); // rescale incoming data to 0.0-1.0
            inline static bool process_param_bool( const ProcessData &data, int cv_myparm, int my_parm ); // rescale incoming data to bool
            inline float logic_operation_on_beat( );   // Logical operation on the bytebeats

            bool logic_mixes_allowed = false;
            float xfade_val = 0.0;      // This is our value to Xfade between ByteBeatA and ByteBeatB
            int xfade_val_int = 0;      // We also need to remember the integer value of the Xfader to select logical operation on the first 25% of the fader if activated

            // private attributes could go here
            int beat_byte_A = 0;  // Currently calculated or temporarily stored ByteBeatA
            int beat_byte_B = 0;  // Currently calculated or temporarily stored ByteBeatB
            float beat_val_A = 0.0;      // Currently calculated or temporarily stored audio value for ByteBeatA
            float beat_val_B = 0.0;      // Currently calculated or temporarily stored audio value for ByteBeatB
            uint32_t t1 = 0;             // Iterator for ByteBeat1
            uint32_t t2 = 0;             // Iterator for ByteBeat2

            bool stop_beatA = false;     // BeatA will not play if stopped
            bool reset_beatA = false;    // BeatB will play from start again on restart if true
            bool reverse_beatA = false;  // True if ByteBeat1 is meant to play backwards
            uint16_t slow_down_A = 0;    // Speed counter for ByteBeat1
            int slow_down_A_factor = 0;  // Speed factor for ByteBeat1

            bool stop_beatB = false;     // BeatB will not play if stopped
            bool reset_beatB = false;    // BeatB will play from start again on restart if true
            bool reverse_beatB = false;  // True if ByteBeat2 is meant to play backwards
            uint16_t slow_down_B = 0;    // Speed counter for ByteBeat2
            int slow_down_B_factor = 0;  // Speed factor for ByteBeat2

            int beat_index_A = 0;         // Used to decide which ByteBeat1 from the lists below has been selected by controller / CV
            int beat_index_B = 0;         // Used to decide which ByteBeat2 from the lists below has been selected by controller / CV
            int logic_operation_id = 0;   // If we mix both ByteBeats using various logical operators, this is the index to select the operation

            // autogenerated code here
            // sectionHpp
            atomic<int32_t> beatA_reset_on_stop, trig_beatA_reset_on_stop;
            atomic<int32_t> beatA_stop, trig_beatA_stop;
            atomic<int32_t> beatA_backwards, trig_beatA_backwards;
            atomic<int32_t> beatA_select, cv_beatA_select;
            atomic<int32_t> beatA_pitch, cv_beatA_pitch;
            atomic<int32_t> beatB_reset_on_stop, trig_beatB_reset_on_stop;
            atomic<int32_t> beatB_stop, trig_beatB_stop;
            atomic<int32_t> beatB_backwards, trig_beatB_backwards;
            atomic<int32_t> beatB_select, cv_beatB_select;
            atomic<int32_t> beatB_pitch, cv_beatB_pitch;
            atomic<int32_t> allow_logic_mixes, trig_allow_logic_mixes;
            atomic<int32_t> xFadeA_B, cv_xFadeA_B;
	// sectionHpp
        };
    }
}