#pragma once
#ifndef TKP_N64_TKPWRAPPER_H
#define TKP_N64_TKPWRAPPER_H
#include "../include/emulator.h"
#include "core/n64_impl.hxx"
#include <chrono>
#include <map>

class N64Debugger;

namespace hydra::N64 {
    class N64_TKPWrapper : public Emulator {
        TKP_EMULATOR(N64_TKPWrapper);
    public:
    private:
        N64 n64_impl_;
        static bool ipl_loaded_;
        int GetWidth() override { return n64_impl_.GetWidth(); }
        int GetHeight() override { return n64_impl_.GetHeight(); }
        friend class ::N64Debugger;

        std::map<uint32_t, uint32_t> key_mappings_;
    };
}
#endif