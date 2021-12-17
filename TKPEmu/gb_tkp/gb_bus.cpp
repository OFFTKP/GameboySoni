#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <bitset>
#include "gb_bus.h"
#include "gb_addresses.h"
namespace TKPEmu::Gameboy::Devices {
	Bus::Bus(std::vector<DisInstr>& instrs) : instructions_(instrs) {}
	void Bus::handle_mbc(uint16_t address, uint8_t data) {
		auto type = cartridge_->GetCartridgeType();
		switch (type) {
			case CartridgeType::MBC1:
			case CartridgeType::MBC1_RAM:
			case CartridgeType::MBC1_RAM_BATTERY: {
				if (address <= 0x1FFF) {
					if ((data & 0b1111) == 0b1010) {
						ram_enabled_ = true;
					}
					else {
						ram_enabled_ = false;
					}
				}
				else if (address <= 0x3FFF) {
					// BANK register 1 (TODO: this doesnt happen on mbc0?)
					selected_rom_bank_ &= 0b1100000;
					selected_rom_bank_ |= data & 0b11111;
					selected_rom_bank_ %= rom_banks_size_;
				}
				else if (address <= 0x5FFF) {
					// BANK register 2
					selected_rom_bank_ &= 0b11111;
					selected_rom_bank_ |= ((data & 0b11) << 5);
					selected_rom_bank_ %= rom_banks_size_;
					selected_ram_bank_ = data & 0b11;
				}
				else {
					// MODE register
					banking_mode_ = data & 0b1;
				}
				break;
			}
			case CartridgeType::MBC3:
			case CartridgeType::MBC3_RAM:
			case CartridgeType::MBC3_RAM_BATTERY: {
				if (address <= 0x1FFF) {
					if ((data & 0b1111) == 0b1010) {
						ram_enabled_ = true;
						// TODO: enable writing to RTC mbc3 registers
					}
					else {
						ram_enabled_ = false;
					}
				}
				else if (address <= 0x3FFF) {
					selected_rom_bank_ = data & 0b0111'1111;
					if (selected_rom_bank_ == 0) {
						selected_rom_bank_ = 1;
					}
				}
				else if (address <= 0x5FFF) {
					if (data <= 0b11) {
						selected_ram_bank_ = data; 
					} else {
						// TODO: mbc3 rtc
					}
				}
				else {
					// MODE register
					banking_mode_ = data & 0b1;
				}
				break;
			}
			default: {
				return;
			}
		}
	}
	uint8_t& Bus::redirect_address(uint16_t address) {
		unused_mem_area_ = 0;
		WriteToVram = false;
		// Return address from ROM banks
		// TODO: create better exceptions
		switch (address & 0xF000) {
			case 0x0000: {
				if (BiosEnabled) {
					static constexpr uint16_t bios_verify_start = 0xA8;
					static constexpr uint16_t bios_verify_end = 0xD7;
					static constexpr uint16_t logo_cartridge_start = 0x104;
					static constexpr uint16_t logo_cartridge_end = 0x133;
					// The logo is hardcoded in the bios normally to check validity of cartridges, so
					// these two ifs allow us to circmvent the validity check and provide our own logo
					if (address >= bios_verify_start && address <= bios_verify_end) {
						return logo[address - bios_verify_start];
					}
					if (address >= logo_cartridge_start && address <= logo_cartridge_end) {
						return logo[address - logo_cartridge_start];
					}
					if (address < 0x100) {
						return bios[address];
					}
				}
				// If gameboy is not in bios mode, or if the address >= 0x100, we fallthrough
				// to the next case
				[[fallthrough]];  // This avoids a compiler warning. Fallthrough is intentional
			}
			case 0x1000:
			case 0x2000:
			case 0x3000:
			case 0x4000:
			case 0x5000:
			case 0x6000:
			case 0x7000: {
				auto ct = cartridge_->GetCartridgeType();
				switch (ct) {
					case CartridgeType::ROM_ONLY: {
						int index = address / 0x4000;
						return (rom_banks_[index])[address % 0x4000];
					}
					case CartridgeType::MBC1:
					case CartridgeType::MBC1_RAM:
					case CartridgeType::MBC1_RAM_BATTERY: {
						if (address <= 0x3FFF) {
							auto sel = (banking_mode_ ? selected_rom_bank_ & 0b1100000 : 0) % cartridge_->GetRomSize();
							return (rom_banks_[sel])[address % 0x4000];
						}
						else {
							auto sel = selected_rom_bank_ % cartridge_->GetRomSize();
							if ((sel & 0b11111) == 0) {
								// In 4000-7FFF, automatically maps to next addr if addr chosen is 00/20/40/60
								// TODO: fix multicart roms
								sel += 1;
							}
							return (rom_banks_[sel])[address % 0x4000];
						}
						break;
					}
					case CartridgeType::MBC3:
					case CartridgeType::MBC3_RAM:
					case CartridgeType::MBC3_RAM_BATTERY: {
						if (address <= 0x3FFF) {
							auto sel = (banking_mode_ ? selected_rom_bank_ & 0b1100000 : 0) % cartridge_->GetRomSize();
							return (rom_banks_[sel])[address % 0x4000];
						}
						else {
							auto sel = selected_rom_bank_ % cartridge_->GetRomSize();
							return (rom_banks_[sel])[address % 0x4000];
						}
						break;
					}
				}
				std::cerr << "Error: Cartridge type not implemented - " << (int)ct << std::endl;
				exit(1);
				break;
			}
			case 0x8000:
			case 0x9000: {
				WriteToVram = true;
				return vram_[address % 0x2000];
			}
			case 0xA000:
			case 0xB000: {
				if (ram_enabled_) {
					if (cartridge_->GetRamSize() == 0)
						return eram_default_[address % 0x2000];
					auto sel = (banking_mode_ ? selected_ram_bank_ : 0) % cartridge_->GetRamSize();
					return (ram_banks_[sel])[address % 0x2000];
				} else {
					unused_mem_area_ = 0xFF;
					return unused_mem_area_;
				}
			}
			case 0xC000:
			case 0xD000: {
				return wram_[address % 0x2000];
			}
			case 0xE000: {
				return redirect_address(address - 0x2000);
			}
			case 0xF000: {
				if (address <= 0xFDFF) {
					return redirect_address(address - 0x2000);
				}
				else if (address <= 0xFE9F) {
					// OAM
					return oam_[address & 0x9F];
				}
				else if (address <= 0xFEFF) {
					// TODO: check if this is actually unused area
					return unused_mem_area_;
				}
				else if (address <= 0xFFFF) {
					return hram_[address % 0xFF00];
				}
				else {
					std::cerr << "Error: Tried to access address " << address << std::endl;
				}
			}
		}
		return unused_mem_area_;
	}

	uint8_t Bus::Read(uint16_t address) {
		return ReadSafe(address);
	}
	uint8_t Bus::ReadSafe(uint16_t address) {
		// ReadSafe does not alter the machine state
		switch(address) {
			case addr_joy: {
				if (action_key_mode_) { 
					return ActionKeys;
				} else {
					return DirectionKeys;
				}
			}
		}
		uint8_t read = redirect_address(address);
		return read;
	}
	uint16_t Bus::ReadL(uint16_t address) {
		return Read(address) + (Read(address + 1) << 8);
	}
	uint8_t& Bus::GetReference(uint16_t address) {
		return redirect_address(address);
	}
	std::string Bus::GetVramDump() {
		std::stringstream s;
		for (const auto& m : vram_) {
			s << std::hex << std::setfill('0') << std::setw(2) << m;
		}
		for (const auto& m : OAM) {
			s << std::hex << std::setfill('0') << std::setw(2) << m.flags;
			s << std::hex << std::setfill('0') << std::setw(2) << m.tile_index;
			s << std::hex << std::setfill('0') << std::setw(2) << m.x_pos;
			s << std::hex << std::setfill('0') << std::setw(2) << m.y_pos;
		}
		return std::move(s.str());
	}
	void Bus::Write(uint16_t address, uint8_t data) {	
		if (address <= 0x7FFF) {
			handle_mbc(address, data);
		}
		else {
			switch (address) {
				case addr_std: {
					// TODO: implement serial
					break;
				}
				case addr_bgp: {
					for (int i = 0; i < 4; i++) {
						BGPalette[i] = (data >> (i * 2)) & 0b11;
					}
					break;
				}
				case addr_ob0: {
					for (int i = 0; i < 4; i++) {
						OBJ0Palette[i] = (data >> (i * 2)) & 0b11;
					}
					break;
				}
				case addr_ob1: {
					for (int i = 0; i < 4; i++) {
						OBJ1Palette[i] = (data >> (i * 2)) & 0b11;
					}
					break;
				}
				case addr_dma: {
					// DMA transfer, load oam up.
					uint16_t dma_addr = data << 8;
					for (int i = 0; i <= (0x9F - 4); i += 4) {
						uint16_t source = dma_addr | i;
						// Each sprite is 4 bytes, so the array has size of 160/4 = 40 
						oam_[i]         = ReadSafe(source);
						oam_[i + 1]     = ReadSafe(source + 1);
						oam_[i + 2]     = ReadSafe(source + 2);
						oam_[i + 3]     = ReadSafe(source + 3);
						OAM[i / 4].y_pos      = oam_[i];
						OAM[i / 4].x_pos      = oam_[i + 1];
						OAM[i / 4].tile_index = oam_[i + 2];
						OAM[i / 4].flags      = oam_[i + 3];
					}
					break;
				}
				case addr_lcd: {
					if (data & 0b1000'0000) {
						hram_[0x41] &= 0b1111'1100;
						hram_[0x44] = 0;
						NextMode = 2;
					}
					break;
				}

				// Any unused bits in these registers are set, passes unused_hwio-GS.gb test (mooneye)
				case addr_div: {
					DIVReset = true;
					break;
				}
				case addr_tac: {
					TACChanged = true;
					data |= 0b1111'1000;
					break;
				}
				case addr_joy: {
					action_key_mode_ = (data == 0x10);
					return;
				}
				case addr_stc: {
					data |= 0b0111'1110;
					break;
				}
				case addr_ifl: {
					data |= 0b1110'0000;
					break;
				}
				case addr_sta: {
					data |= 0b1000'0000;
					break;
				}
				case addr_s1s: {
					data |= 0b1000'0000;
					break;
				}
				case addr_s3e: {
					data |= 0b0111'1111;
					break;
				}
				case addr_s3o: {
					data |= 0b1001'1111;
					break;
				}
				case addr_s4l: {
					data |= 0b1110'0000;
					break;
				}
				case addr_s4c: {
					data |= 0b0011'1111;
					break;
				}
				case addr_snd: {
					data |= 0b0111'0000;
					break;
				}
				// Unused HWIO registers
				// Writing to these sets all the bits
				case 0xFF03: case 0xFF08: case 0xFF09: case 0xFF0A: case 0xFF0B:
				case 0xFF0C: case 0xFF0D: case 0xFF0E: case 0xFF15: case 0xFF1F:
				case 0xFF27: case 0xFF28: case 0xFF29: case 0xFF4C: case 0xFF4D:
				case 0xFF4E: case 0xFF4F: case 0xFF50: case 0xFF51: case 0xFF52:
				case 0xFF53: case 0xFF54: case 0xFF55: case 0xFF56: case 0xFF57:
				case 0xFF58: case 0xFF59: case 0xFF5A: case 0xFF5B: case 0xFF5C:
				case 0xFF5D: case 0xFF5E: case 0xFF5F: case 0xFF60: case 0xFF61:
				case 0xFF62: case 0xFF63: case 0xFF64: case 0xFF65: case 0xFF66:
				case 0xFF67: case 0xFF68: case 0xFF69: case 0xFF6A: case 0xFF6B:
				case 0xFF6C: case 0xFF6D: case 0xFF6E: case 0xFF6F: case 0xFF70:
				case 0xFF71: case 0xFF72: case 0xFF73: case 0xFF74: case 0xFF75:
				case 0xFF76: case 0xFF77: case 0xFF78: case 0xFF79: case 0xFF7A:
				case 0xFF7B: case 0xFF7C: case 0xFF7D: case 0xFF7E: case 0xFF7F: {
					data |= 0b1111'1111;
					break;
				}
			}
			if (address >= 0xFE00 && address <= 0xFE9F) {
				switch (address % 4) { 
					case 0: OAM[(address & 0xFF) / 4].y_pos      = data; break;
					case 1: OAM[(address & 0xFF) / 4].x_pos      = data; break;
					case 2: OAM[(address & 0xFF) / 4].tile_index = data; break;
					case 3: OAM[(address & 0xFF) / 4].flags      = data; break;
				}
			}
			if (address == 0xFFFF) {
			}
			redirect_address(address) = data;
		}
	}
	void Bus::WriteL(uint16_t address, uint16_t data) {
		Write(address, data & 0xFF);
		Write(address + 1, data >> 8);
	}
	void Bus::Reset() {
		SoftReset();
		for (auto& rom : rom_banks_) {
			rom.fill(0);
		}	
	}
	void Bus::SoftReset() {
		for (auto& ram : ram_banks_) {
			ram.fill(0);
		}
		hram_.fill(0);
		oam_.fill(0);
		vram_.fill(0);
		selected_rom_bank_ = 1;
		selected_ram_bank_ = 0;
		BiosEnabled = true;
	}
	const Cartridge* const Bus::GetCartridge() const {
		return cartridge_.get();
	}
	void Bus::LoadCartridge(std::string fileName) {
		Reset();
		cartridge_ = std::make_unique<Cartridge>();
		cartridge_->Load(fileName, rom_banks_, ram_banks_);
		rom_banks_size_ = cartridge_->GetRomSize();
	}
}
