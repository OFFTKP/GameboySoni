#pragma once
#ifndef TKP_GB_BUS_H
#define TKP_GB_BUS_H
#include <string>
#include <cstdint>
#include <array>
#include <vector>
#include <fstream>
#include <iterator>
#include <memory>
#include "gb_cartridge.h"

namespace TKPEmu::Gameboy::Devices {
    const auto cl_white = 0;
    const auto cl_lgray = 1;
    const auto cl_dgray = 2;
    const auto cl_black = 3;
    const auto addr_joy = 0xFF00;
    // Serial registers
    const auto addr_std = 0xFF01;
    const auto addr_stc = 0xFF02;
    // Timer registers
    const auto addr_div = 0xFF04;
    const auto addr_tac = 0xFF07;
    // Interrupt flag
    const auto addr_ifl = 0xFF0F;
    // Sound registers
    const auto addr_s1s = 0xFF10;
    const auto addr_s3e = 0xFF1A;
    const auto addr_s3o = 0xFF1C;
    const auto addr_s4l = 0xFF20;
    const auto addr_s4c = 0xFF23;
    const auto addr_snd = 0xFF26;
    // PPU & OAM related registers
    const auto addr_lcd = 0xFF40;
    const auto addr_sta = 0xFF41;
    const auto addr_lly = 0xFF44;
    const auto addr_dma = 0xFF46;
    const auto addr_bgp = 0xFF47;
    const auto addr_ob0 = 0xFF48;
    const auto addr_ob1 = 0xFF49;
    class Bus {
    private:
        using RamBank = std::array<uint8_t, 0x2000>;
        using RomBank = std::array<uint8_t, 0x4000>;
        bool ram_enabled_ = false;
        uint8_t selected_ram_bank_ = 0;
        uint8_t selected_rom_bank_ = 1;
        uint8_t rom_banks_size_ = 2;
        bool action_key_mode_ = false;
        uint8_t unused_mem_area_ = 0;
        std::vector<RamBank> ram_banks_;
        std::vector<RomBank> rom_banks_;
        std::unique_ptr<Cartridge> cartridge_ = NULL;
        std::array<uint8_t, 0xA0> oam_{};
        std::array<uint8_t, 0x100> hram_{};
        std::array<uint8_t, 0x2000> eram_default_{};
        std::array<uint8_t, 0x2000> wram_{}; // TODO: cgb uses larger wram, maybe change, maybe inherit
        std::array<uint8_t, 0x2000> vram_{};

        uint8_t& redirect_address(uint16_t address);
    public:
        enum LCDCFlag {
            BG_ENABLE = 1 << 0,
            OBJ_ENABLE = 1 << 1,
            OBJ_SIZE = 1 << 2,
            BG_TILEMAP = 1 << 3,
            BG_TILES = 1 << 4,
            WND_ENABLE = 1 << 5,
            WND_TILEMAP = 1 << 6,
            LCD_ENABLE = 1 << 7
        };
        enum STATFlag {
            MODE = 0b11,
            COINCIDENCE = 1 << 2,
            MODE0_INTER = 1 << 3,
            MODE1_INTER = 1 << 4,
            MODE2_INTER = 1 << 5,
            COINC_INTER = 1 << 6
        };
        enum IFInterrupt {
            VBLANK = 1 << 0,
            LCDSTAT = 1 << 1,
            TIMER = 1 << 2,
            SERIAL = 1 << 3,
            JOYPAD = 1 << 4
        };
        struct Sprite {
            uint8_t y_pos = 0;
            uint8_t x_pos = 0;
            uint8_t tile_index = 0;
            uint8_t flags = 0;
        };
        struct Pixel {
            uint8_t color : 2;
            uint8_t palette : 2;
            // TODO: CGB Sprite priority
            uint8_t bg_prio : 1;
        };
        struct Tile {
            Pixel pixels[64];
        };
        // Currently unused
        // TODO: Implement bios, change reset default values
        bool inBios;
        int bios[0x100] = {
        0x31, 0xFE, 0xFF, 0xAF, 0x21, 0xFF, 0x9F, 0x32, 0xCB, 0x7C, 0x20, 0xFB, 0x21, 0x26, 0xFF, 0x0E,
        0x11, 0x3E, 0x80, 0x32, 0xE2, 0x0C, 0x3E, 0xF3, 0xE2, 0x32, 0x3E, 0x77, 0x77, 0x3E, 0xFC, 0xE0,
        0x47, 0x11, 0x04, 0x01, 0x21, 0x10, 0x80, 0x1A, 0xCD, 0x95, 0x00, 0xCD, 0x96, 0x00, 0x13, 0x7B,
        0xFE, 0x34, 0x20, 0xF3, 0x11, 0xD8, 0x00, 0x06, 0x08, 0x1A, 0x13, 0x22, 0x23, 0x05, 0x20, 0xF9,
        0x3E, 0x19, 0xEA, 0x10, 0x99, 0x21, 0x2F, 0x99, 0x0E, 0x0C, 0x3D, 0x28, 0x08, 0x32, 0x0D, 0x20,
        0xF9, 0x2E, 0x0F, 0x18, 0xF3, 0x67, 0x3E, 0x64, 0x57, 0xE0, 0x42, 0x3E, 0x91, 0xE0, 0x40, 0x04,
        0x1E, 0x02, 0x0E, 0x0C, 0xF0, 0x44, 0xFE, 0x90, 0x20, 0xFA, 0x0D, 0x20, 0xF7, 0x1D, 0x20, 0xF2,
        0x0E, 0x13, 0x24, 0x7C, 0x1E, 0x83, 0xFE, 0x62, 0x28, 0x06, 0x1E, 0xC1, 0xFE, 0x64, 0x20, 0x06,
        0x7B, 0xE2, 0x0C, 0x3E, 0x87, 0xF2, 0xF0, 0x42, 0x90, 0xE0, 0x42, 0x15, 0x20, 0xD2, 0x05, 0x20,
        0x4F, 0x16, 0x20, 0x18, 0xCB, 0x4F, 0x06, 0x04, 0xC5, 0xCB, 0x11, 0x17, 0xC1, 0xCB, 0x11, 0x17,
        0x05, 0x20, 0xF5, 0x22, 0x23, 0x22, 0x23, 0xC9, 0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B,
        0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D, 0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E,
        0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99, 0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC,
        0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E, 0x3c, 0x42, 0xB9, 0xA5, 0xB9, 0xA5, 0x42, 0x4C,
        0x21, 0x04, 0x01, 0x11, 0xA8, 0x00, 0x1A, 0x13, 0xBE, 0x20, 0xFE, 0x23, 0x7D, 0xFE, 0x34, 0x20,
        0xF5, 0x06, 0x19, 0x78, 0x86, 0x23, 0x05, 0x20, 0xFB, 0x86, 0x20, 0xFE, 0x3E, 0x01, 0xE0, 0x50,
        };
        Bus();
        uint8_t Read(uint16_t address);
        uint16_t ReadL(uint16_t address);
        uint8_t& GetReference(uint16_t address);
        void Write(uint16_t address, uint8_t data);
        void WriteL(uint16_t address, uint16_t data);
        void Reset();
        void SoftReset();
        void LoadCartridge(std::string&& fileName);
        std::array<std::array<float, 3>, 4> Palette;
        std::array<uint8_t, 4> BGPalette{};
        std::array<uint8_t, 4> OBJ0Palette{};
        std::array<uint8_t, 4> OBJ1Palette{};
        std::array<Sprite, 40> OAM;
        bool DIVReset = false;
        bool TACChanged = false;
        uint8_t NextMode = 0;
        uint8_t DirectionKeys = 0b1110'1111;
        uint8_t ActionKeys = 0b1101'1111;
    };
}
#endif
