#pragma once

#include <capnzero/CapnZero.h>
#include <SystemConfig.h>

namespace srg{
    class SRGWorldModel;

    namespace wm{
        class Communication{
        public:
            Communication(SRGWorldModel *wm);
            virtual ~Communication();

        private:
            void onTelegramMessage(capnp::FlatArrayMessageReader &msg);

            SRGWorldModel *wm;
            essentials::SystemConfig *sc;
            void* ctx;
            capnzero::Subscriber *TelegramMessageSub;

        };
    }
}