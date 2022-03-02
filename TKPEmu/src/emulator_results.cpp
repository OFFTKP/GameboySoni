#include "../include/emulator_results.h"
namespace TKPEmu::Testing {
const std::unordered_map<Hash, ExpectedResult> QA::PassedTestMap = 
{
    // TODO: generate ini (or csv) file from this, and edit the ini file in the future to add more tests
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //      rom hash                       clocks to            expected                    rom name        //
    //                                    complete test          result                                     //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Gameboy
    // blargg
    { "7d95af543a521ed036dc85f6f232d103", { 1'300'000, "42d5abde92c2678617996dd8f782989c", "cpu_instrs/01-special" } },
    { "d36a85bb94d4c1b373c0e7be0f6f0971", { 300'000, "0f384cd6115fd9b2c33f7d9fc42200b5", "cpu_instrs/02-interrupts" } },
    { "5bccf6b03f661d92b2903694d458510c", { 1'150'000, "3caaa1d70619add931ecfa9e88e3a7ff", "cpu_instrs/03-op sp,hl" } },
    { "e97a5202d7725a3caaf3495e559f2e98", { 1'400'000, "cccde7fb4b57b51d73147233e2789d0e", "cpu_instrs/04-op r,imm" } },
    { "43fc8bfc94938b42d8ecc9ea8b6b811a", { 1'900'000, "2d0258217d9411ae7dc9390b4022e7fa", "cpu_instrs/05-op rp" } },
    { "24da4eed7ef73ec32aae5ffd50ebec55", { 300'000, "45f17918f8da5383982f33eda50b3714", "cpu_instrs/06-ld r,r" } },
    { "6dbf4e754ef2f844246fd08718d1c377", { 400'000, "c81680b1a44aab843cea7936de3da10f", "cpu_instrs/07-jr,jp,call,ret,rst" } },
    { "c21ddacbfa44d61919c8e2d6c3e7d26e", { 350'000, "820df31460734f4451ef46673a5e297c", "cpu_instrs/08-misc instrs" } },
    { "e4c4dd4eebad0c9d6f2ef575331c3aee", { 4'500'000, "7a0cae7fe13aba1179096a74161dbd81", "cpu_instrs/09-op r,r" } },
    { "64632849778ee83ae85db8bf68c84ebc", { 7'000'000, "56d069d71d8b2114149a6a605df2ef28", "cpu_instrs/10-bit ops" } },
    { "6e64346be4d7ccf26f53de105d6cb5f6", { 7'500'000, "3215a908fc7e7aac137f20b9dec08e9e", "cpu_instrs/11-op a,(hl)" } },
    { "b417d5d06c3382ab5836b5d365184f36", { 350'000, "89c5c02898f9299e22457dc47cab40a0", "instr_timing" } },
    { "9537182264201f75611fc96a1de0f086", { 258'877, "bd9fc5fdc70e82b3eb643c4c7dacd4ab", "mem_timing/01-read_timing"} },
    { "d5cf8017991700f267b7b753579cc773", { 222'676, "bc9ff8c11b34a1c09800f79349ede2bf", "mem_timing/02-write_timing" } },
    { "fd3516dca15be20bc124ce4523ae5ad3", { 295'354, "41ad39c61bad61f0e474216d9cfa4c9d", "mem_timing/03-modify_timing" } },
    { "c89dcc0761693f0a42baf6c6a560222f", { 478'725, "3f58de72430b4efd5918282df6ef3d87", "dmg_sound/01-registers" } },
    { "93bdd72292b1f1c25290c7a3ae8b37b3", { 750'364, "266f90572b534e845275df094f1121c3", "halt_bug" } },
    // Gekkio
    { "e459f412e5459636b0ff736787774239", { 206743, "deb3479d8347148912a2018b3f94da93", "acceptance/add_sp_e_timing" } },
    { "f9bf05a2048eb83ce2d25eaa15e59b36", { 193265, "fa43d52c2e302bfff8c0c55c50e9401b", "acceptance/boot_regs-dmgABC" } },
    { "f90d8ad35e5d172845e725996ada8908", { 146898, "25ff67b94ee3da658eafb86457cd34a8", "acceptance/call_timing" } },
    { "f6213e483a93e614ccf28ca0db6fe179", { 145669, "25ff67b94ee3da658eafb86457cd34a8", "acceptance/call_cc_timing" } },
    { "1bf603a22a9c5c4d1a54e42550babe34", { 150000, "f0553923b341e4e57f091f1ce8cc8cf0", "acceptance/di_timing-GS" } },
    { "6bf0f67b415799534dc64e9c60521401", { 176006, "8c77db0a6370393f573540736131d2ef", "acceptance/div_timing" } },
    { "e5a7c1bb00c125db63974ec05b23de33", { 298225, "2eee4e1b02e5aeb4c4c6ae686c8ea07e", "acceptance/ei_sequence" } },
    { "82f55f1beaca6b7efc744b70f36de94e", { 175889, "12da5b255c481dba0f086a2b20001ae1", "acceptance/ei_timing" } },
    { "8ae8e8bfc9985cae9836a76dd4ff41d4", { 175908, "f0553923b341e4e57f091f1ce8cc8cf0", "acceptance/halt_ime0_ei" } },
    { "603ec0145d94806c5ac2e0e150d0f8a7", { 193386, "1975dc57ea974f8b92d14b07f1a9a584", "acceptance/halt_ime1_timing" } },
    { "cd20692d8453b777bb2918bef8431117", { 180487, "f2ead6ee6dc0a2f45504a43ad6536ba6", "acceptance/if_ie_registers" } },
    { "4633fb333f8a9ddf2529ec51887a7f79", { 100000, "bd3e0a29d4ebf43cff3be190bc3f15d7", "acceptance/intr_timing" } },
    { "de63b8399797ed6756f96483190f8711", { 178242, "cad628ffff413571fc8e13b88f084dcf", "acceptance/pop_timing" } },
    { "6794ae9a846fa887e3f976c5a4e9a023", { 154503, "65967bdd08467289185607914abdcea0", "acceptance/push_timing" } },
    { "612dff157f718c752aee5fe4d89f806c", { 175867, "6991e00223ecbd57308a7a7116c328f4", "acceptance/rapid_di_ei" } },
    { "1697d9aa59deb514b71a4a75fe3504ce", { 177314, "747dad4070fe5698071d4b256cb736ce", "acceptance/ret_timing" } },
    { "611bfe319e33dbac599d0b856795de77", { 191003, "747dad4070fe5698071d4b256cb736ce", "acceptance/ret_cc_timing" } },
    { "9afa0b63379028273b06247c0695ee10", { 181851, "747dad4070fe5698071d4b256cb736ce", "acceptance/reti_timing" } },
    { "14e4eed76f51691e27279b74c8254a29", { 175872, "6090b1beba327d9d1934088dc548de60", "acceptance/reti_intr_timing" } },
    { "d4294accaf3ee139381a7aa965e4527e", { 189454, "51d3c7c64b61b512e26d946c0afddbc9", "acceptance/rst_timing" } },
    { "4cdcd4babcfcf781f4af2f0bb0c18f31", { 179795, "25ff67b94ee3da658eafb86457cd34a8", "acceptance/jp_timing" } },
    { "f685b7467b919943bc72ca3ab8282a41", { 206780, "bd64a7d89b3f0c6adaf5796839cef0ae", "acceptance/ld_hl_sp_e_timing" } },
    { "a926d659808d379f34e31a3528c55fc0", { 191358, "33b2a3bfe263c1bbe5e6613696e409e6", "acceptance/oam_dma_start" } },
    { "0462263e88a2eb9b701b2d63bd004690", { 206737, "2944f2e753972f06e3d958e179fa1284", "acceptance/oam_dma_timing" } },
    { "517af19b408ab2835a93dfb905b6b6ba", { 189269, "2944f2e753972f06e3d958e179fa1284", "acceptance/oam_dma_restart" } },
    { "66bafbd73b021d45b174afce483a5614", { 165116, "f0553923b341e4e57f091f1ce8cc8cf0", "acceptance/bits/mem_oam" } },  
    { "04abf53326dec066aad078f4da4ccc33", { 228312, "c1c98a124d8bc1988d22265f64a6209d", "acceptance/bits/reg_f" } },
    { "e905eb9e6e55a5624a915c9a1e81b5a1", { 208289, "f0553923b341e4e57f091f1ce8cc8cf0", "acceptance/bits/unused_hwio-GS" } },
    { "8fa02c48b75200ff96d445ea3bd5f3c3", { 325050, "f0553923b341e4e57f091f1ce8cc8cf0", "acceptance/instrs/daa" } },
    { "71fa2b4f35bd4baae853bb33714de371", { 119634, "f0553923b341e4e57f091f1ce8cc8cf0", "acceptance/interrupts/ie_push" } },
    { "a8a77e3238b319ea9ae09d43eb15f759", { 182991, "49a0ad9cb2a5d507e9207a12dccbf9be", "acceptance/oam_dma/basic" } },
    { "ecb8b4e807ee00e8d7d4affbec330845", { 165264, "1f60b822d2ec4b612fe7f252ff83bd8e", "acceptance/oam_dma/reg_read"} },
    { "c57eada752f746347951f79c828391b9", { 508381, "f0553923b341e4e57f091f1ce8cc8cf0", "acceptance/timer/div_write" } },
    { "d73c739b0950f1720799098c21e8dafd", { 228639, "90472bf97c60517ccae5b2fe2c5c205a", "acceptance/timer/tim_00" } },
    { "22538d107bcd8b989e534e5bd06bfeac", { 193385, "8143d0e2e5f7dcc7015e132d1d1bc9b0", "acceptance/timer/tim_01" } },
    { "f82cb93bb388d1ccfbc125189db2337a", { 188733, "90472bf97c60517ccae5b2fe2c5c205a", "acceptance/timer/tim_10" } },
    { "94e8634725beab0e49c9a956ded2ebe5", { 175968, "90472bf97c60517ccae5b2fe2c5c205a", "acceptance/timer/tim_11" } },
    { "b8ce040bf3dc44ae93dfdd08455db5a3", { 210951, "39d1c2b42ed461c1422e8826143f77f8", "acceptance/timer/tima_reload" } },
    { "bc0ef62f861a22ddac1cd26dc696016d", { 100000, "d26217a6668abd437eb8b5762f2d79f0", "acceptance/timer/tima_write_reloading" } },
    { "d8729ec243af26011dcc37a31f783a6e", { 100000, "3f85d2b88a68b5de845e9b34246ac2e9", "acceptance/timer/tma_write_reloading" } },
    { "23eca8a8d921deaade53761d3a42a0c4", { 100000, "90472bf97c60517ccae5b2fe2c5c205a", "acceptance/timer/tim00_div_trigger" } },
    { "bb631cacc570e0a9b53ff3dc348d43f5", { 100000, "258db64e2110857d17a8b249a301020b", "acceptance/timer/tim01_div_trigger" } },
    { "ccf7d984070e06fd70fab5982df85fb8", { 100000, "c0246c8e3bd539356fa7761ee8de5a9b", "acceptance/timer/tim10_div_trigger" } },
    { "fcccd66a3972183a8e9ca18f0fef6192", { 100000, "90472bf97c60517ccae5b2fe2c5c205a", "acceptance/timer/tim11_div_trigger" } },
    { "1f733875abf08a1d05b8a6ad1fda9454", { 159443, "551999ba57fc569e90a725f0d6dafb2d", "acceptance/ppu/intr_2_mode0_timing" } },
    { "5ecc8a6aca4f3fe01f1381d53093850b", { 173814, "b28e4192f094951889b60e243ced36e6", "acceptance/ppu/intr_2_mode3_timing" } },
    { "a92c9ecda679176355be5cb7df54f169", { 153001, "800c892ae1e7574a89a42aadf418132d", "acceptance/ppu/intr_2_oam_ok_timing" } },
    { "9e141738d28c50860b0b6259ecfaf4a1", { 162660, "3d7eb38ff8c398188759b2574656794e", "acceptance/ppu/vblank_stat_intr-GS" } },
    { "31d2ad77d05566b1dcb92d7ff7232767", { 1614439, "f0553923b341e4e57f091f1ce8cc8cf0", "emulator-only/mbc1/bits_bank1" } },
    { "d7c8eb26b8c276f0d13e2a272a17c308", { 1677811, "f0553923b341e4e57f091f1ce8cc8cf0", "emulator-only/mbc1/bits_bank2" } },
    { "d807288f6cfe34225989dd0d9293043e", { 1614699, "f0553923b341e4e57f091f1ce8cc8cf0", "emulator-only/mbc1/bits_mode" } },
    { "37666e894123e433ad28039992a0dc39", { 3379433, "f0553923b341e4e57f091f1ce8cc8cf0", "emulator-only/mbc1/bits_ramg" } },
    { "7730bddf166d08dc9c3bd1ff72d0902f", { 3189739, "f0553923b341e4e57f091f1ce8cc8cf0", "emulator-only/mbc2/bits_ramg" } },
    { "18164c7ea80cbdba4d0b478605ec5bde", { 1660955, "f0553923b341e4e57f091f1ce8cc8cf0", "emulator-only/mbc2/bits_romb" } },
    { "2c7b1904598e7b4cc905ece8a588f7bf", { 1178817, "f0553923b341e4e57f091f1ce8cc8cf0", "emulator-only/mbc2/bits_unused" } },
    { "b013332419fc1cc0cf02cdd49aa962cb", { 357287, "f0553923b341e4e57f091f1ce8cc8cf0", "emulator-only/mbc2/ram" } },
    { "8d88d40df4728e0cf954f6766483bdf0", { 180969, "f0553923b341e4e57f091f1ce8cc8cf0", "emulator-only/mbc2/rom_512kb" } },
    { "d54deb4dd31599ee087642e592cab64c", { 180969, "f0553923b341e4e57f091f1ce8cc8cf0", "emulator-only/mbc2/rom_1Mb" } },
    { "6b16e82843ffd9520e1afc2e247d2ae0", { 180969, "f0553923b341e4e57f091f1ce8cc8cf0", "emulator-only/mbc2/rom_2Mb" } },
    { "20bb5cd9b26696955e2304c721d658b9", { 752664, "f0553923b341e4e57f091f1ce8cc8cf0", "emulator-only/mbc1/ram_256kb" } },
    { "cc197e887003211e175ba5c2fa1bf0bd", { 557442, "f0553923b341e4e57f091f1ce8cc8cf0", "emulator-only/mbc1/ram_64kb" } },
    { "c4dc3398b815a34591fed91a1d5329b1", { 207111, "f0553923b341e4e57f091f1ce8cc8cf0", "emulator-only/mbc1/rom_16MB" } },
    { "c4620fa2f6a36b8264fb7c876a627fd6", { 172157, "f0553923b341e4e57f091f1ce8cc8cf0", "emulator-only/mbc1/rom_4Mb" } },
    { "2435d3266665065e6b2a5047d1fad186", { 172157, "f0553923b341e4e57f091f1ce8cc8cf0", "emulator-only/mbc1/rom_8Mb" } },
    { "e2e847c8b704de9b111e29cbc4c555a8", { 177514, "f0553923b341e4e57f091f1ce8cc8cf0", "emulator-only/mbc5/rom_16Mb" } },
    { "a4f3be6f01f793b3a54b1769a5b6ad86", { 177514, "f0553923b341e4e57f091f1ce8cc8cf0", "emulator-only/mbc5/rom_1Mb" } },
    { "053f47c6224e00dd6b2ffab705b23d91", { 144543, "f0553923b341e4e57f091f1ce8cc8cf0", "emulator-only/mbc5/rom_2Mb" } },
    { "91714e36c77d453489619949651dde05", { 194991, "f0553923b341e4e57f091f1ce8cc8cf0", "emulator-only/mbc5/rom_32Mb" } },
    { "10fb4cacb112fa9789d2b1a2f26f0104", { 177514, "f0553923b341e4e57f091f1ce8cc8cf0", "emulator-only/mbc5/rom_4Mb" } },
    { "11cc5a856ae0d1a2d2912ae3f7ab8609", { 177514, "f0553923b341e4e57f091f1ce8cc8cf0", "emulator-only/mbc5/rom_512kb" } },
    { "ad8340088e6d48fa747644ff0fed8586", { 177514, "f0553923b341e4e57f091f1ce8cc8cf0", "emulator-only/mbc5/rom_64Mb" } },
    { "33a8606348d323b669f9582575e33d50", { 143752, "f0553923b341e4e57f091f1ce8cc8cf0", "emulator-only/mbc5/rom_8Mb" } },
};
}