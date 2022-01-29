#include "UM-Memory.h"
#include "GameSDK.h"
#include "xorstr.hpp"
#include <Eigen/Geometry>

bool mfound = false;

std::string readCharString(DWORD64 address, int length) {
	std::string str = "";
	for (int i = 0; i < length; i++) {
		str += mem->Read<char>(address + i);
	}

	return str;
}

std::wstring readWCharString(DWORD64 address, int length) {
	std::wstring str = L"";
	for (int i = 0; i < length; i++) {
		//std::wcout << mem->Read<UCHAR>(address + i * 2);
		str += mem->Read<wchar_t>(address + i * 2);
	}

	return str;
}

std::string wstring_to_string(const std::wstring& wstr)
{
	static std::wstring_convert< std::codecvt_utf8<wchar_t>, wchar_t > converter;

	return converter.to_bytes(wstr);
}

bool ReadBuffer(uint64_t address, uint64_t* buffer, int size) {
	for (int i = 0; i < size; i++) {
		buffer[i] = mem->Read<uint64_t>(address + i * sizeof(uint64_t));
	}

	return true;
}

EFTData* EFTData::Instance() {
	static EFTData instance;
	return &instance;
}

bool EFTData::setupItemIdDict() {
    this->ItemIdDict = {
        {"5447ac644bdc2d6c208b4567" , "5.56x45 M193 Ball ammo"},
        {"54527a984bdc2d4e668b4567" , "5.56x45 mm M855"},
        {"54527ac44bdc2d36668b4567" , "5.56x45 mm M855A1"},
        {"560d5e524bdc2d25448b4571" , "12x70 7mm Buckshot"},
        {"560d61e84bdc2da74d8b4571" , "7.62x54R SNB"},
        {"560d75f54bdc2da74d8b4573" , "7.62x54 R SNB ammo"},
        {"5649ed104bdc2d3d1c8b458b" , "7.62x39 PS ammo package"},
        {"5656d7c34bdc2d9d198b4587" , "7.62x39 mm PS"},
        {"5656eb674bdc2d35148b457c" , "40 mm VOG-25"},
        {"56d59d3ad2720bdb418b4577" , "9x19 mm Pst gzh"},
        {"56dfef82d2720bbd668b4567" , "5.45x39 mm BP"},
        {"56dff026d2720bb8668b4567" , "5.45x39 mm BS"},
        {"56dff061d2720bb5668b4567" , "5.45x39 mm BT"},
        {"56dff0bed2720bb0668b4567" , "5.45x39 mm FMJ"},
        {"56dff216d2720bbd668b4568" , "5.45x39 mm HP"},
        {"56dff2ced2720bb4668b4567" , "5.45x39 mm PP"},
        {"56dff338d2720bbd668b4569" , "5.45x39 mm PRS"},
        {"56dff3afd2720bba668b4567" , "5.45x39 mm PS"},
        {"56dff421d2720b5f5a8b4567" , "5.45x39 mm SP"},
        {"56dff4a2d2720bbd668b456a" , "5.45x39 mm T"},
        {"56dff4ecd2720b5f5a8b4568" , "5.45x39 mm US"},
        {"5735fdcd2459776445391d61" , "7.62x25mm TT AKBS"},
        {"5735ff5c245977640e39ba7e" , "7.62x25mm TT FMJ43"},
        {"573601b42459776410737435" , "7.62x25mm TT LRN"},
        {"573602322459776445391df1" , "7.62x25mm TT LRNPC"},
        {"5736026a245977644601dc61" , "7.62x25mm TT P gl"},
        {"573603562459776430731618" , "7.62x25mm TT Pst gzh"},
        {"573603c924597764442bd9cb" , "7.62x25mm TT PT gzh"},
        {"573718ba2459775a75491131" , "9x18 mm PM 9 BZT gzh"},
        {"573719762459775a626ccbc1" , "9x18 mm PM 9 P gzh"},
        {"573719df2459775a626ccbc2" , "9x18 mm PM PBM"},
        {"57371aab2459775a77142f22" , "9x18 mm PM PMM"},
        {"57371b192459775a9f58a5e0" , "9x18 mm PM PPe gzh"},
        {"57371e4124597760ff7b25f1" , "9x18 mm PM PPT gzh"},
        {"57371eb62459776125652ac1" , "9x18 mm PM PRS gs"},
        {"57371f2b24597761224311f1" , "9x18 mm PM PS gs PPO"},
        {"57371f8d24597761006c6a81" , "9x18 mm PM PSO gzh"},
        {"5737201124597760fc4431f1" , "9x18 mm PM Pst gzh"},
        {"5737207f24597760ff7b25f2" , "9x18 mm PM PSV"},
        {"573720e02459776143012541" , "9x18mm PM RG028 gzh"},
        {"57372140245977611f70ee91" , "9x18 mm PM SP7 gzh"},
        {"5737218f245977612125ba51" , "9x18 mm PM SP8 gzh"},
        {"573722e82459776104581c21" , "16 pcs. 9x18 PM BZHT gzh ammo box"},
        {"573724b42459776125652ac2" , "16 pcs. 9x18 PM P gzh ammo box"},
        {"5737250c2459776125652acc" , "16 pcs. 9x18 PM PBM ammo box"},
        {"5737256c2459776125652acd" , "16 pcs. 9x18 PM PMM ammo box"},
        {"573725b0245977612125bae2" , "16 pcs. 9x18 PM Ppe gzh ammo box"},
        {"5737260b24597761224311f2" , "16 pcs. 9x18 PM PPT gzh ammo box"},
        {"5737266524597761006c6a8c" , "16 pcs. 9x18 PM PRS gs ammo box"},
        {"573726d824597765d96be361" , "16 pcs. 9x18 PM PS gs PPO ammo box  "},
        {"5737273924597765dd374461" , "16 pcs. 9x18 PM PSO gzh ammo box"},
        {"573727c624597765cc785b5b" , "16 pcs. 9x18 PM Pst gzh ammo box"},
        {"5737280e24597765cc785b5c" , "16 pcs. 9x18 PM PSV ammo box"},
        {"5737287724597765e1625ae2" , "16 pcs. 9x18 PM RG028 gzh ammo box"},
        {"573728cc24597765cc785b5d" , "16 pcs. 9x18 PM SP7 gzh ammo box"},
        {"573728f324597765e5728561" , "16 pcs. 9x18 PM SP8 gzh ammo box"},
        {"5737292724597765e5728562" , "120 pcs. 5.45x39 BP gs ammo pack"},
        {"57372a7f24597766fe0de0c1" , "120 pcs. 5.45x39 BP gs ammo pack"},
        {"57372ac324597767001bc261" , "30 pcs. 5.45x39 BP gs ammo pack"},
        {"57372b832459776701014e41" , "120 pcs. 5.45x39 BS gs ammo pack"},
        {"57372bad245977670b7cd242" , "120 pcs. 5.45x39 BS gs ammo pack"},
        {"57372bd3245977670b7cd243" , "30 pcs. 5.45x39 BS gs ammo pack"},
        {"57372c21245977670937c6c2" , "120 pcs. 5.45x39 BT gs ammo pack"},
        {"57372c56245977685e584582" , "120 pcs. 5.45x39 BT gs ammo pack"},
        {"57372c89245977685d4159b1" , "30 pcs. 5.45x39 BT gs ammo pack"},
        {"57372d1b2459776862260581" , "120 pcs. 5.45x39 PP gs ammo pack"},
        {"57372d4c245977685a3da2a1" , "120 pcs. 5.45x39 PP gs ammo pack"},
        {"57372db0245977685d4159b2" , "30 pcs. 5.45x39 PP gs ammo pack"},
        {"57372deb245977685d4159b3" , "120 pcs. 5.45x39 PRS gs ammo pack"},
        {"57372e1924597768553071c1" , "120 pcs. 5.45x39 PRS gs ammo pack"},
        {"57372e4a24597768553071c2" , "30 pcs. 5.45x39 PRS gs ammo pack"},
        {"57372e73245977685d4159b4" , "120 pcs. 5.45x39 PS gs ammo pack"},
        {"57372e94245977685648d3e1" , "120 pcs. 5.45x39 PS gs ammo pack"},
        {"57372ebf2459776862260582" , "30 pcs. 5.45x39 PS gs ammo pack"},
        {"57372ee1245977685d4159b5" , "120 pcs. 5.45x39 T gs ammo pack"},
        {"57372f2824597769a270a191" , "120 pcs. 5.45x39 T gs ammo pack"},
        {"57372f5c24597769917c0131" , "30 pcs. 5.45x39 T gs ammo pack"},
        {"57372f7d245977699b53e301" , "120 pcs. 5.45x39 US gs ammo pack"},
        {"57372fc52459776998772ca1" , "120 pcs. 5.45x39 US gs ammo pack"},
        {"5737300424597769942d5a01" , "30 pcs. 5.45x39 US gs ammo pack"},
        {"5737330a2459776af32363a1" , "30 pcs. 5.45x39 FMJ ammo box"},
        {"5737339e2459776af261abeb" , "30 pcs. 5.45x39 HP ammo box"},
        {"573733c72459776b0b7b51b0" , "30 pcs. 5.45x39 SP ammo box"},
        {"5739d41224597779c3645501" , "16 pcs. 9x19 Pst Gzh ammo box"},
        {"57a0dfb82459774d3078b56c" , "9x39 mm SP-5"},
        {"57a0e5022459774d1673f889" , "9x39 mm SP-6"},
        {"58820d1224597753c90aeb13" , "12x70 Led slug"},
        {"58864a4f2459770fcc257101" , "9x19 mm PSO gzh"},
        {"5887431f2459777e1612938f" , "7.62x54R LPS Gzh"},
        {"58dd3ad986f77403051cba8f" , "7.62x51 mm M80"},
        {"5943d9c186f7745a13413ac9" , "Shrapnel"},
        {"5996f6cb86f774678763a6ca" , "RGD-5 Shrapnel"},
        {"5996f6d686f77467977ba6cc" , "F1 Shrapnel"},
        {"5996f6fc86f7745e585b4de3" , "M67 Shrapnel"},
        {"59e0d99486f7744a32234762" , "7.62x39 mm BP"},
        {"59e4cf5286f7741778269d8a" , "7.62x39 mm T45M"},
        {"59e4d24686f7741776641ac7" , "7.62x39 mm US"},
        {"59e4d3d286f774176a36250a" , "7.62x39 mm HP"},
        {"59e6542b86f77411dc52a77a" , ".366 TKM FMJ"},
        {"59e655cb86f77411dc52a77b" , ".366 TKM EKO"},
        {"59e6658b86f77411d949b250" , ".366 TKM Geksa"},
        {"59e68f6f86f7746c9f75e846" , "5.56x45 mm M856"},
        {"59e6906286f7746c9f75e847" , "5.56x45 mm M856A1"},
        {"59e690b686f7746c9f75e848" , "5.56x45 mm M995"},
        {"59e6918f86f7746c9f75e849" , "5.56x45 mm Mk 255 Mod 0"},
        {"59e6920f86f77411d82aa167" , "5.56x45 mm 55 FMJ"},
        {"59e6927d86f77411da468256" , "5.56x45 mm 55 HP"},
        {"59e77a2386f7742ee578960a" , "7.62x54R 7N1 Sniper cartridge"},
        {"5a269f97c4a282000b151807" , "9x21 mm SP10"},
        {"5a26abfac4a28232980eabff" , "9x21 mm SP11"},
        {"5a26ac06c4a282000c5a90a8" , "9x21 mm SP12"},
        {"5a26ac0ec4a28200741e1e18" , "9x21 mm SP13"},
        {"5a38ebd9c4a282000d722a5b" , "20x70 7.5mm Buckshot"},
        {"5a3c16fe86f77452b62de32a" , "9x19 mm Luger CCI"},
        {"5a6086ea4f39f99cd479502f" , "7.62x51 mm M61"},
        {"5a608bf24f39f98ffc77720e" , "7.62x51 mm M62"},
        {"5ba2678ad4351e44f824b344" , "4.6x30mm FMJ SX"},
        {"5ba26812d4351e003201fef1" , "4.6x30mm Action SX"},
        {"5ba26835d4351e0035628ff5" , "4.6x30mm AP SX"},
        {"5ba26844d4351e00334c9475" , "4.6x30mm Subsonic SX"},
        {"5c0d56a986f774449d5de529" , "9x19 mm RIP"},
        {"5c0d591486f7744c505b416f" , "12x70 RIP"},
        {"5c0d5ae286f7741e46554302" , "5.56x45mm Warmage"},
        {"5c0d5e4486f77478390952fe" , "5.45x39 mm 7N39 \"Igolnik\""},
        {"5c0d668f86f7747ccb7f13b2" , "9x39 mm 7N9 SPP"},
        {"5c0d688c86f77413ae3407b2" , "9x39 mm 7N12 BP"},
        {"5c11279ad174af029d64592b" , "20 pcs pack 5.56x45 Warmage ammo"},
        {"5c1127bdd174af44217ab8b9" , "20 pcs. 9x19 mm DIPP ammo box"},
        {"5c1127d0d174af29be75cf68" , "5 pcs. 12x70 DIPP ammo box"},
        {"5c1260dc86f7746b106e8748" , "8 pcs pack of 9x39 7N12 BP ammo"},
        {"5c12619186f7743f871c8a32" , "8 pcs pack of 9x39 7N9 SPP ammo"},
        {"5c1262a286f7743f8a69aab2" , "30 pcs. 5.45x39 7N39 ammo pack"},
        {"5c3df7d588a4501f290594e5" , "9x19 mm Green Tracer"},
        {"5c925fa22e221601da359b7b" , "9x19 mm AP 6.3"},
        {"5cadf6ddae9215051e1c23b2" , "12.7x55 mm PS12"},
        {"5cadf6e5ae921500113bb973" , "12.7x55 mm PS12A"},
        {"5cadf6eeae921500134b2799" , "12.7x55 mm PS12B"},
        {"5cc80f38e4a949001152b560" , "5.7x28 mm SS190"},
        {"5cc80f53e4a949000e1ea4f8" , "5.7x28 mm L191"},
        {"5cc80f67e4a949035e43bbba" , "5.7x28 mm SB193"},
        {"5cc80f79e4a949033c7343b2" , "5.7x28 mm SS198LF"},
        {"5cc80f8fe4a949033b0224a2" , "5.7x28 mm SS197SR"},
        {"5cc86832d7f00c000d3a6e6c" , "5.7x28 mm R37.F"},
        {"5cc86840d7f00c002412c56c" , "5.7x28 mm R37.X"},
        {"5cd157cfd7f00c0011791f36" , "26x75mm flare cartridge"},
        {"5cde8864d7f00c0010373be1" , "12.7x108 mm B-32"},
        {"5d2f2ab648f03550091993ca" , "12.7x108 mm BZT-44M"},
        {"5d6e6772a4b936088465b17c" , "12/70 5.25mm Buckshot"},
        {"5d6e67fba4b9361bc73bc779" , "12x70 6.5 mm \"Express\" Buckshot"},
        {"5d6e6806a4b936088465b17e" , "12/70 8.5 mm \"Magnum\" Buckshot"},
        {"5d6e6869a4b9361c140bcfde" , "12/70 Grizzly 40 Slug "},
        {"5d6e6891a4b9361bd473feea" , "12/70 \"Poleva-3\" Slug"},
        {"5d6e689ca4b9361bc8618956" , "12/70 \"Poleva-6u\" Slug"},
        {"5d6e68a8a4b9360b6c0d54e2" , "12/70 AP-20 Slug"},
        {"5d6e68b3a4b9361bca7e50b5" , "12/70 HP Slug Copper Sabot Premier"},
        {"5d6e68c4a4b9361b93413f79" , "12x70 shell with .50 BMG bullet"},
        {"5d6e68d1a4b93622fe60e845" , "12/70 HP Slug \"SuperFormance\""},
        {"5d6e68dea4b9361bcc29e659" , "12/70 Dual Sabot Slug"},
        {"5d6e68e6a4b9361c140bcfe0" , "12/70 FTX Custom LIte Slug"},
        {"5d6e6911a4b9361bd5780d52" , "12/70 Flechette"},
        {"5d6e695fa4b936359b35d852" , "20/70 5.6mm Buckshot"},
        {"5d6e69b9a4b9361bc8618958" , "20/70 6.2mm Buckshot"},
        {"5d6e69c7a4b9360b6c0d54e4" , "20/70 7.3mm Buckshot"},
        {"5d6e6a05a4b93618084f58d0" , "20/70 Star Slug"},
        {"5d6e6a42a4b9364f07165f52" , "20/70 Slug Poleva-6u"},
        {"5d6e6a53a4b9361bd473feec" , "20/70 Slug \"Poleva-3\""},
        {"5d6e6a5fa4b93614ec501745" , "20/70 Devastator Slug"},
        {"5d70e500a4b9364de70d38ce" , "30x29 mm VOG-30"},
        {"5e023cf8186a883be655e54f" , "7.62x54R T-46M"},
        {"5e023d34e8a400319a28ed44" , "7.62x54R 7BT1"},
        {"5e023d48186a883be655e551" , "7.62x54R 7N37"},
        {"5e023e53d4353e3302577c4c" , "7.62x51 mm BPZ FMJ"},
        {"5e023e6e34d52a55c3304f71" , "7.62x51 mm TPZ SP"},
        {"5e023e88277cce2b522ff2b1" , "7.62x51 mm Ultra Nosler"},
        {"5e81f423763d9f754677bf2e" , ".45 ACP FMJ"},
        {"5e85a9a6eacf8c039e4e2ac1" , "23x75mm Shrapnel 10"},
        {"5e85a9f4add9fe03027d9bf1" , "23x75mm \"Star\""},
        {"5e85aa1a988a8701445df1f5" , "23x75mm \"Barricade\""},
        {"5e85aac65505fa48730d8af2" , "!!!DO_NOT_USE!!!23x75mm \"Cheremukha-7M\""},
        {"5ea2a8e200685063ec28c05a" , ".45 RIP"},
        {"5ede4739e0350d05467f73e8" , "40x46 mm M406 (HE)"},
        {"5ede47405b097655935d7d16" , "40x46 mm M441(HE)"},
        {"5ede474b0c226a66f5402622" , "40x46 mm M381 (HE)"},
        {"5ede475339ee016e8c534742" , "40x46 mm M576(MP-APERS)"},
        {"5ede475b549eed7c6d5c18fb" , "40x46 mm M386(HE)"},
        {"5ede47641cf3836a88318df1" , "!!!DO NOT USE!!!40x46 mm M716(Smoke)"},
        {"5efb0c1bd79ff02a1f5e68d9" , "7.62x51 mm M993"},
        {"5efb0cabfb3e451d70735af5" , ".45 ACP AP"},
        {"5efb0d4f4bc50b58e81710f3" , ".45 ACP Lasermatch FMJ"},
        {"5efb0da7a29a85116f6ea05f" , "9x19 mm 7N31"},
        {"5efb0e16aeb21837e749c7ff" , "9x19 mm QuakeMaker"},
        {"5efb0fc6aeb21837e749c801" , ".45 ACP Hydra-Shok"},
        {"5f0596629e22f464da6bbdd9" , ".366 AP"},
        {"5f0c892565703e5c461894e9" , "40x46 mm M433 (HEDP)"},
        {"5f647f31b6238e5dd066e196" , "23x75mm Shrapnel-25"},
        {"5f647fd3f6e4ab66c82faed6" , "!!!DO_NOT_USE!!!23x75mm Wave-R"},
        {"5fbe3ffdf8b6a877a729ea82" , ".300 BPZ AAC Blackout"},
        {"5fc275cf85fd526b824a571a" , ".338 Lapua Magnum FMJ"},
        {"5fc382a9d724d907e2077dab" , ".338 Lapua Magnum AP"},
        {"5fc382b6d6fa9c00c571bbc3" , ".338 Lapua Magnum TAC-X"},
        {"5fc382c1016cce60e8341b20" , ".338 UPZ Lapua Magnum"},
        {"5fd20ff893a8961fc660a954" , ".300 AAC Blackout AP"},
        {"545cdb794bdc2d3a198b456a" , "6B43 Zabralo-Sh 6A Armor"},
        {"5648a7494bdc2d9d488b4583" , "PACA Soft Armor"},
        {"59e7635f86f7742cbf2c1095" , "Module-3M bodyarmor"},
        {"5ab8e4ed86f7742d8e50c7fa" , "MF-UNTAR armor vest"},
        {"5ab8e79e86f7742d8b372e78" , "BNTI Gzhel-K armor"},
        {"5b44cd8b86f774503d30cba2" , "IOTV Gen4 armor (full protection)"},
        {"5b44cf1486f77431723e3d05" , "IOTV Gen4 armor (assault kit)"},
        {"5b44d0de86f774503d30cba8" , "IOTV Gen4 armor (high mobility kit)"},
        {"5b44d22286f774172b0c9de8" , "BNTI Kirasa-N armor"},
        {"5c0e51be86f774598e797894" , "6B13 assault armor (flora pattern)"},
        {"5c0e53c886f7747fa54205c7" , "6B13 assault armor (digital flora pattern)"},
        {"5c0e541586f7747fa54205c9" , "6B13 M assault armor (tan)"},
        {"5c0e57ba86f7747fa141986d" , "6B23-2 armor (mountain flora pattern)"},
        {"5c0e5bab86f77461f55ed1f3" , "6B23-1 armor (digital flora pattern)"},
        {"5c0e5edb86f77461f55ed1f7" , "Zhuk-3 Press armor"},
        {"5c0e625a86f7742d77340f62" , "Zhuk-6a heavy armor"},
        {"5c0e655586f774045612eeb2" , "Highcom Trooper TFO armor (multicam)"},
        {"5ca2151486f774244a3b8d30" , "FORT Redut-M body armor"},
        {"5ca21c6986f77479963115a7" , "FORT Redut-T5 body armor"},
        {"5df8a2ca86f7740bfe6df777" , "6B2 armor (flora)"},
        {"5e4abb5086f77406975c9342" , "LBT 6094A Slick Plate Carrier"},
        {"5e9dacf986f774054d6b89f4" , "FORT Defender-2 body armor"},
        {"5f5f41476bdad616ad46d631" , "BNTI Korund-VM armor"},
        {"5fd4c474dd870108a754b241" , "5.11 Hexgrid plate carrier"},
        {"544a5cde4bdc2d39388b456b" , "Flyye MBSS Backpack"},
        {"545cdae64bdc2d39198b4568" , "Camelbak Tri-Zip Backpack"},
        {"56e294cdd2720b603a8b4575" , "Mystery Ranch Terraplane Backpack"},
        {"56e335e4d2720b6c058b456d" , "Scav Backpack"},
        {"56e33634d2720bd8058b456b" , "Duffle bag"},
        {"56e33680d2720be2748b4576" , "Transformer Bag"},
        {"59e763f286f7742ee57895da" , "Pilgrim tourist backpack"},
        {"5ab8ebf186f7742d8b372e80" , "SSO \"Attack 2\" raid backpack"},
        {"5ab8ee7786f7742d8f33f0b9" , "VKBO army bag"},
        {"5ab8f04f86f774585f4237d8" , "Tactical sling bag"},
        {"5b44c6ae86f7742d1627baea" , "Ana tactical Beta 2 battle backpack "},
        {"5c0e774286f77468413cc5b2" , "Mystery Ranch Blackjack 50 backpack (multicam)"},
        {"5c0e805e86f774683f3dd637" , "3V G Paratus 3-Day Operator's Tactical Backpack"},
        {"5ca20d5986f774331e7c9602" , "Wartech Berkut VV-102 backpack"},
        {"5d5d940f86f7742797262046" , "Oakley Mechanism heavy duty backpack (black)"},
        {"5df8a4d786f77412672a1e3b" , "6SH118 raid backpack"},
        {"5e4abc6786f77406812bd572" , "LBT-2670 Slim Field Med Pack"},
        {"5e997f0b86f7741ac73993e2" , "Sanitar bag"},
        {"5e9dcf5986f7746c417435b3" , "LBT-8005A Day Pack backpack"},
        {"5f5e45cc5021ce62144be7aa" , "LK 3F Transfer tourist backpack"},
        {"5f5e467b0bc58666c37e7821" , "Eberlestock F5 Switchblade backpack (dry earth)"},
        {"5f5e46b96bdad616ad46d613" , "Eberlestock F4 Terminator load bearing backpack (tiger stripe)"},
        {"5672cb124bdc2d1a0f8b4568" , "AA Battery"},
        {"5672cb304bdc2dc2088b456a" , "D Size Battery"},
        {"5672cb724bdc2dc2088b456b" , "Geiger-Muller counter"},
        {"56742c284bdc2d98058b456d" , "Crickent lighter"},
        {"56742c2e4bdc2d95058b456d" , "Zibbo lighter"},
        {"56742c324bdc2d150f8b456d" , "Broken GPhone"},
        {"5733279d245977289b77ec24" , "Car battery"},
        {"573474f924597738002c6174" , "Chainlet"},
        {"5734758f24597738025ee253" , "Golden neck chain"},
        {"573475fb24597737fb1379e1" , "Apollon Soyuz cigarettes "},
        {"573476d324597737da2adc13" , "Malboro Cigarettes"},
        {"573476f124597737e04bf328" , "Wilston cigarettes"},
        {"5734770f24597738025ee254" , "Strike Cigarettes"},
        {"5734779624597737e04bf329" , "CPU Fan"},
        {"573477e124597737dd42e191" , "PC CPU"},
        {"5734781f24597737e04bf32a" , "DVD drive"},
        {"573478bc24597738002c6175" , "Horse figurine"},
        {"5734795124597738002c6176" , "Insulating tape"},
        {"57347b8b24597737dd42e192" , "Classic matches"},
        {"57347baf24597738002c6178" , "RAM"},
        {"57347c1124597737fb1379e3" , "Duct tape"},
        {"57347c2e24597744902c94a1" , "Power supply unit"},
        {"57347c5b245977448d35f6e1" , "Bolts"},
        {"57347c77245977448d35f6e2" , "Screw nut"},
        {"57347c93245977448d35f6e3" , "Toothpaste"},
        {"57347ca924597744596b4e71" , "Graphics card"},
        {"57347cd0245977445a2d6ff1" , "T-Shaped Plug"},
        {"577e1c9d2459773cd707c525" , "Printer paper"},
        {"5909e99886f7740c983b9984" , "USB Adapter"},
        {"590a358486f77429692b2790" , "Rechargeable battery"},
        {"590a373286f774287540368b" , "Dry fuel"},
        {"590a386e86f77429692b27ab" , "Damaged hard drive"},
        {"590a391c86f774385a33c404" , "Magnet"},
        {"590a3b0486f7743954552bdb" , "Printed circuit board"},
        {"590a3c0a86f774385a33c450" , "Spark plug"},
        {"590a3cd386f77436f20848cb" , "Energy-saving lamp"},
        {"590a3d9c86f774385926e510" , "Ultraviolet lamp"},
        {"590a3efd86f77437d351a25b" , "Gas analyzer"},
        {"590c2b4386f77425357b6123" , "Pliers"},
        {"590c2c9c86f774245b1f03f2" , "Construction measuring tape"},
        {"590c2d8786f774245b1f03f3" , "Screwdriver"},
        {"590c2e1186f77425357b6124" , "A set of tools"},
        {"590c311186f77424d1667482" , "Wrench"},
        {"590c31c586f774245e3141b2" , "A pack of nails"},
        {"590c346786f77423e50ed342" , "Xenomorph sealing foam"},
        {"590c35a486f774273531c822" , "Shustrilo sealing foam"},
        {"590c595c86f7747884343ad7" , "Air filter for gas mask"},
        {"590c5a7286f7747884343aea" , "Gunpowder \"Kite\""},
        {"590c5bbd86f774785762df04" , "WD-40 100ml."},
        {"590c5c9f86f77477c91c36e7" , "WD-40 400ml"},
        {"590de71386f774347051a052" , "Antique teapot"},
        {"590de7e986f7741b096e5f32" , "Antique vase"},
        {"590de92486f77423d9312a33" , "Gold pocket watch on a chain"},
        {"5937fc6786f7742cab753590" , "Silver pocket watch on a chain"},
        {"5937fd0086f7742bf33fc198" , "Bronze pocket watch on a chain"},
        {"5939a00786f7742fe8132936" , "Zibbo lighter"},
        {"593a87af86f774122f54a951" , "Syringe with a chemical"},
        {"59e3556c86f7741776641ac2" , "Ox bleach"},
        {"59e358a886f7741776641ac3" , "Clin wiper"},
        {"59e3596386f774176c10a2a2" , "Paid AntiRoach"},
        {"59e35abd86f7741778269d82" , "Sodium bicarbonate"},
        {"59e35cbb86f7741778269d83" , "Corrugated hose"},
        {"59e35de086f7741778269d84" , "Electric drill"},
        {"59e35ef086f7741777737012" , "A pack of screws"},
        {"59e3606886f77417674759a5" , "Saline solution"},
        {"59e361e886f774176c10a2a5" , "Hydrogen peroxide"},
        {"59e3639286f7741777737013" , "Bronze lion"},
        {"59e3647686f774176a362507" , "Wooden clock"},
        {"59e3658a86f7741776641ac4" , "Cat figurine"},
        {"59e366c186f7741778269d85" , "Piece of plexiglas"},
        {"59e36c6f86f774176c10a2a7" , "Powercord"},
        {"59f32bb586f774757e1e8442" , "Dogtag BEAR"},
        {"59f32c3b86f77472a31742f0" , "Dogtag USEC"},
        {"59faf7ca86f7740dbe19f6c2" , "Roler submariner gold wrist watch"},
        {"59faf98186f774067b6be103" , "Heat-exchange alkali surface washer"},
        {"59fafb5d86f774067a6f2084" , "5L propane tank"},
        {"59faff1d86f7746c51718c9c" , "Physical bitcoin"},
        {"5a29276886f77435ed1b117c" , "Working hard drive"},
        {"5a29284f86f77463ef3db363" , "Toughbook reinforced laptop"},
        {"5a687e7886f7740c4a5133fb" , "Blood sample"},
        {"5af0484c86f7740f02001f7f" , "Coffee Majaica"},
        {"5af04b6486f774195a3ebb49" , "Pliers Elite"},
        {"5af04c0b86f774138708f78e" , "Motor Controller"},
        {"5af04e0a86f7743a532b79e2" , "Single-axis Fiber Optic Gyroscope"},
        {"5af0534a86f7743b6f354284" , "Ophthalmoscope"},
        {"5af0561e86f7745f5f3ad6ac" , "Powerbank"},
        {"5b43237186f7742f3a4ab252" , "Chemical container"},
        {"5b4335ba86f7744d2837a264" , "Medical bloodset"},
        {"5b43575a86f77424f443fe62" , "Fuel conditioner"},
        {"5b4c72b386f7745b453af9c0" , "Motor Controller"},
        {"5b4c72c686f77462ac37e907" , "Motor Controller"},
        {"5b4c72fb86f7745cef1cffc5" , "Single-axis Fiber Optic Gyroscope"},
        {"5b4c81a086f77417d26be63f" , "Chemical container"},
        {"5b4c81bd86f77418a75ae159" , "Chemical container"},
        {"5b9b9020e7ef6f5716480215" , "dogtagt"},
        {"5bc9b355d4351e6d1509862a" , "#FireKlean gun lube"},
        {"5bc9b720d4351e450201234b" , "Golden 1GPhone"},
        {"5bc9b9ecd4351e3bac122519" , "Deadlyslob's beard oil"},
        {"5bc9bc53d4351e00367fbcee" , "Golden rooster"},
        {"5bc9bdb8d4351e003562b8a1" , "Silver Badge"},
        {"5bc9be8fd4351e00334cae6e" , "42nd Signature Blend English Tea"},
        {"5bc9c049d4351e44f824d360" , "Battered antique Book"},
        {"5bc9c377d4351e3bac12251b" , "Old firesteel"},
        {"5c052e6986f7746b207bc3c9" , "Portable defibrillator"},
        {"5c052f6886f7746b1e3db148" , "Military COFDM wireless Signal Transmitter"},
        {"5c052fb986f7746b2101e909" , "UHF RFID Reader "},
        {"5c05300686f7746dce784e5d" , "VPX Flash Storage Module"},
        {"5c05308086f7746b2101e90b" , "Virtex programmable processor"},
        {"5c0530ee86f774697952d952" , "LEDX Skin Transilluminator"},
        {"5c06779c86f77426e00dd782" , "Wires"},
        {"5c06782b86f77426df5407d2" , "Capacitors"},
        {"5c12620d86f7743f8b198b72" , "Tetriz portable game"},
        {"5c1265fc86f7743f896a21c2" , "Broken GPhone X"},
        {"5c1267ee86f77416ec610f72" , "Chain with Prokill medallion"},
        {"5c12688486f77426843c7d32" , "Paracord"},
        {"5c13cd2486f774072c757944" , "Soap"},
        {"5c13cef886f774072e618e82" , "Toilet paper"},
        {"5d0375ff86f774186372f685" , "Military cable"},
        {"5d0376a486f7747d8050965c" , "Military circuit board"},
        {"5d03775b86f774203e7e0c4b" , "Phased array element"},
        {"5d0377ce86f774186372f689" , "Military thermal vision module Iridium"},
        {"5d03784a86f774203e7e0c4d" , "Military gyrotachometer"},
        {"5d0378d486f77420421a5ff4" , "Military power filter"},
        {"5d03794386f77420415576f5" , "6-STEN-140-M military battery"},
        {"5d0379a886f77420407aa271" , "OFZ 30x160mm shell "},
        {"5d1b2f3f86f774252167a52c" , "FP-100 filter absorber"},
        {"5d1b2fa286f77425227d1674" , "Electric motor"},
        {"5d1b2ffd86f77425243e8d17" , "NIXXOR lens"},
        {"5d1b304286f774253763a528" , "Working LCD"},
        {"5d1b309586f77425227d1676" , "Broken LCD"},
        {"5d1b313086f77425227d1678" , "Phase control relay"},
        {"5d1b317c86f7742523398392" , "Hand drill"},
        {"5d1b31ce86f7742523398394" , "Round pliers"},
        {"5d1b327086f7742525194449" , "Pressure gauge"},
        {"5d1b32c186f774252167a530" , "Analog thermometer"},
        {"5d1b36a186f7742523398433" , "Metal fuel tank"},
        {"5d1b371186f774253763a656" , "Expeditionary fuel tank"},
        {"5d1b385e86f774252167b98a" , "Water filter"},
        {"5d1b392c86f77425243e98fe" , "Light bulb"},
        {"5d1b39a386f774252339976f" , "Silicone tube"},
        {"5d1b3a5d86f774252167ba22" , "Pile of meds"},
        {"5d1b3f2d86f774253763b735" , "Disposable syringe"},
        {"5d1c774f86f7746d6620f8db" , "Radiator helix"},
        {"5d1c819a86f774771b0acd6c" , "Weapon parts"},
        {"5d235a5986f77443f6329bc6" , "Gold skull ring"},
        {"5d235b4d86f7742e017bc88a" , "GP coin"},
        {"5d40412b86f7743cb332ac3a" , "Schaman shampoo"},
        {"5d40419286f774318526545f" , "Metal cutting scissors"},
        {"5d4041f086f7743cac3f22a7" , "Ortodontox toothpaste"},
        {"5d40425986f7743185265461" , "Nippers"},
        {"5d4042a986f7743185265463" , "Long flat screwdriver"},
        {"5d63d33b86f7746ea9275524" , "Flat screwdriver"},
        {"5d6fc78386f77449d825f9dc" , "Gunpowder \"Eagle\""},
        {"5d6fc87386f77449db3db94e" , "Gunpowder \"Hawk\""},
        {"5df8a6a186f77412640e2e80" , "Christmas tree decoration ball (red)"},
        {"5df8a72c86f77412640e2e83" , "Christmas tree decoration ball (silver)"},
        {"5df8a77486f77412672a1e3f" , "Christmas tree decoration ball (violet)"},
        {"5e2aedd986f7746d404f3aa4" , "GreenBat lithium battery"},
        {"5e2aee0a86f774755a234b62" , "Cyclon accumulator battery"},
        {"5e2aef7986f7746d3f3c33f5" , "Repellent"},
        {"5e2af00086f7746d3f3c33f7" , "Smoked Chimney drain cleaner"},
        {"5e2af02c86f7746d420957d4" , "Pack of chlorine"},
        {"5e2af22086f7746d3f3c33fa" , "Tube of Poxeram Cold Welding"},
        {"5e2af29386f7746d4159f077" , "KEKTAPE duct tape"},
        {"5e2af2bc86f7746d3f3c33fc" , "Hunter matches"},
        {"5e2af37686f774755a234b65" , "SurvL Survivor Lighter"},
        {"5e2af41e86f774755a234b67" , "Polyamide fabric Cordura"},
        {"5e2af47786f7746d404f3aaa" , "Fleece cloth"},
        {"5e2af4a786f7746d3f3c3400" , "Ripstop cloth"},
        {"5e2af4d286f7746d4159f07a" , "Aramid fiber cloth"},
        {"5e2af51086f7746d3f3c3402" , "UZRGM grenade fuze"},
        {"5e54f62086f774219b0f1937" , "Raven figurine"},
        {"5e54f6af86f7742199090bf3" , "Can of Dr. Lupo's coffee beans"},
        {"5f745ee30acaeb0d490d8c5b" , "Veritas guitar pick"},
        {"557ff21e4bdc2d89578b4586" , "Tactical glasses"},
        {"59e770b986f7742cbd762754" , "Anti-fragmentation glasses"},
        {"5aa2b923e5b5b000137b7589" , "Round frame sunglasses"},
        {"5aa2b986e5b5b00014028f4c" , "Dundukk sport sunglasses"},
        {"5aa2b9aee5b5b00015693121" , "RayBench Hipster Reserve sunglasses"},
        {"5b432be65acfc433000ed01f" , "6B34 Anti-fragmentation glasses"},
        {"5c0d32fcd174af02a1659c75" , "Pyramex Proximity safety glasses"},
        {"5c1a1cc52e221602b3136e3d" , "SI M Frame safety glasses"},
        {"5d5fca1ea4b93635fd598c07" , "Crossbow tactical glasses"},
        {"5d6d2e22a4b9361bd5780d05" , "Gascan glasses"},
        {"5d6d2ef3a4b93618084f58bd" , "RayBench Aviator glasses"},
        {"5e71f70186f77429ee09f183" , "Twitch Rivals 2020 glasses"},
        {"5448fee04bdc2dbc018b4567" , "0.6L water bottle"},
        {"5448ff904bdc2d6f028b456e" , "Army Crackers"},
        {"544fb62a4bdc2dfb738b4568" , "Russian Army pineapple juice"},
        {"544fb6cc4bdc2d34748b456e" , "Slickers bar"},
        {"5673de654bdc2d180f8b456d" , "Can of pacific saury"},
        {"5734773724597737fd047c14" , "Condensed milk"},
        {"57347d3d245977448f7b7f61" , "Rye croutons"},
        {"57347d5f245977448b40fa81" , "Humpback salmon"},
        {"57347d692459774491567cf1" , "Can of green peas"},
        {"57347d7224597744596b4e72" , "Can of beef stew"},
        {"57347d8724597744596b4e76" , "Squash spread"},
        {"57347d90245977448f7b7f65" , "Pack of oat flakes"},
        {"57347d9c245977448b40fa85" , "Can of herring"},
        {"57347da92459774491567cf5" , "Can of delicious beef stew"},
        {"57505f6224597709a92585a9" , "Alyonka chocolate bar"},
        {"575062b524597720a31c09a1" , "Green Ice"},
        {"57513f07245977207e26a311" , "Apple juice"},
        {"57513f9324597720a7128161" , "Grand juice"},
        {"57513fcc24597720a31c09a6" , "Vita juice"},
        {"5751435d24597720a27126d1" , "Max energy"},
        {"57514643245977207f2c2d09" , "TarCola"},
        {"575146b724597720a27126d5" , "Pack of milk"},
        {"5751487e245977207e26a315" , "Emelya rye croutons"},
        {"5751496424597720a27126da" , "Hot Rod"},
        {"590c5d4b86f774784e1b9c45" , "Iskra lunch box"},
        {"590c5f0d86f77413997acfab" , "MRE lunch box"},
        {"59e3577886f774176a362503" , "Pack of sugar"},
        {"5bc9b156d4351e00367fbce9" , "Jar of DevilDog mayo"},
        {"5bc9c29cd4351e003562b8a3" , "Can of sprats"},
        {"5c0fa877d174af02a012e1cf" , "Water bottle with a filter Aquamari"},
        {"5d1b33a686f7742523398398" , "Purified water"},
        {"5d1b376e86f774252519444e" , "\"Fierce Hatchling\" moonshine"},
        {"5d403f9186f7743cac3f229b" , "Bottle of Dan Jackiel Whiskey"},
        {"5d40407c86f774318526545a" , "Bottle of vodka Tarkovskaya"},
        {"5e8f3423fd7471236e6e3b64" , "Premium Kvass \"Norvinskiy Yadreniy\" 0.6L bottle"},
        {"590c37d286f77443be3d7827" , "SAS drive"},
        {"590c392f86f77444754deb29" , "SSD drive"},
        {"590c621186f774138d11ea29" , "Secure Flash drive"},
        {"590c62a386f77412b0130255" , "Sliderkey Secure Flash drive"},
        {"590c639286f774151567fa95" , "Technical documentation"},
        {"590c645c86f77412b01304d9" , "Diary"},
        {"590c651286f7741e566b6461" , "Slim diary"},
        {"591092ef86f7747bb8703422" , "Secure case for documents n.0022"},
        {"591093bb86f7747caa7bb2ee" , "Sealed letter"},
        {"5938188786f77474f723e87f" , "Secure case for documents 0031"},
        {"5938878586f7741b797c562f" , "Secure case for documents 0052"},
        {"593965cf86f774087a77e1b6" , "Secure case for documents 0048"},
        {"5939e5a786f77461f11c0098" , "Secure case for documents 0013"},
        {"5939e9b286f77462a709572c" , "Sealed letter"},
        {"59f9ddae86f77407ab46e047" , "Secure Flash drive"},
        {"5a29357286f77409c705e025" , "Sliderkey Flash drive"},
        {"5a294d7c86f7740651337cf9" , "SAS disk with drones"},
        {"5a294d8486f774068638cd93" , "SAS disk with drones"},
        {"5a6860d886f77411cd3a9e47" , "Secure case for documents 0060"},
        {"5ac620eb86f7743a8e6e0da0" , "Package with graphics cards"},
        {"5ae9a0dd86f7742e5f454a05" , "Goshan cargo manifests"},
        {"5ae9a18586f7746e381e16a3" , "OLI cargo manifests"},
        {"5ae9a1b886f77404c8537c62" , "IDEA cargo manifests"},
        {"5ae9a25386f7746dd946e6d9" , "OLI cargo route documents"},
        {"5ae9a34d86f7740aab00e4de" , "Note for the Therapist"},
        {"5ae9a3f586f7740aab00e4e6" , "Clothes design handbook Part 1"},
        {"5ae9a4fc86f7746e381e1753" , "Clothes design handbook Part 2"},
        {"5c12301c86f77419522ba7e4" , "False flash drive"},
        {"5c12613b86f7743bbe2c3f76" , "Folder with intelligence"},
        {"5d357d6b86f7745b606e3508" , "photo album"},
        {"5d3ec50586f774183a607442" , "Encrypted message"},
        {"5efdaf6de6a30218ed211a48" , "Marked Ophthalmoscope"},
        {"5efdafc1e70b5e33f86de058" , "Marked with a blue symbol surgical set"},
        {"5eff135be0d3331e9d282b7b" , "Marked with tape flash drive"},
        {"5448ba0b4bdc2d02308b456c" , "Factory exit key"},
        {"5671446a4bdc2d97058b4569" , "Pistol Case Key"},
        {"5672c92d4bdc2d180f8b4567" , "Dorm room 118 Key"},
        {"57518f7724597720a31c09ab" , "Key 3"},
        {"57518fd424597720c85dbaaa" , "Key 5"},
        {"5751916f24597720a27126df" , "Key 2"},
        {"5751961124597720a13989a7" , "(off)Keycard"},
        {"5751961824597720a31c09ac" , "(off)Black Keycard"},
        {"5751962524597720a7128169" , "(off)Blue Keycard"},
        {"5780cda02459777b272ede61" , "Dorm room 306 Key"},
        {"5780cf692459777de4559321" , "Dorm room 315 Key"},
        {"5780cf722459777a5108b9a1" , "Dorm room 308 Key"},
        {"5780cf7f2459777de4559322" , "Marked key"},
        {"5780cf942459777df90dcb72" , "Dorm room 214 Key"},
        {"5780cf9e2459777df90dcb73" , "Dorm room 218 Key"},
        {"5780cfa52459777dfb276eb1" , "Dorm room 220 Key"},
        {"5780d0532459777a5108b9a2" , "Customs office key"},
        {"5780d0652459777df90dcb74" , "Cabinet key"},
        {"5780d07a2459777de4559324" , "Portable cabin key"},
        {"57a349b2245977762b199ec7" , "Door key"},
        {"590de4a286f77423d9312a32" , "Car key"},
        {"590de52486f774226a0c24c2" , "Machinery key"},
        {"5913611c86f77479e0084092" , "Trailer park cabin key"},
        {"5913651986f774432f15d132" , "VAZ key"},
        {"59136a4486f774447a1ed172" , "Dorm guard desk key"},
        {"59136e1e86f774432f15d133" , "Dorm room 110 Key"},
        {"59136f6f86f774447a1ed173" , "Car key"},
        {"591382d986f774465a6413a7" , "Dorm room 105 Key"},
        {"591383f186f7744a4c5edcf3" , "Dorm room 104 Key"},
        {"5913877a86f774432f15d444" , "The key to the gas station storage room"},
        {"5913915886f774123603c392" , "Military base checkpoint key"},
        {"5914578086f774123569ffa4" , "Dorm room 108 Key"},
        {"59148c8a86f774197930e983" , "Dorm room 204 Key"},
        {"59148f8286f7741b951ea113" , "Weapon safe key"},
        {"591ae8f986f77406f854be45" , "Yotota car key"},
        {"591afe0186f77431bd616a11" , "Key ZB-014"},
        {"5937ee6486f77408994ba448" , "Machinery key"},
        {"5938144586f77473c2087145" , "Portable cabin key of customs Factory zone"},
        {"5938504186f7740991483f30" , "Dorm room 203 Key"},
        {"593858c486f774253a24cb52" , "Door key"},
        {"5938603e86f77435642354f4" , "Dorm room 206 Key"},
        {"59387a4986f77401cc236e62" , "Dorm room 114 Key"},
        {"5938994586f774523a425196" , "Dorm room 103 Key"},
        {"593962ca86f774068014d9af" , "Unknown key"},
        {"593aa4be86f77457f56379f8" , "Dorm room 303 Key"},
        {"5a043f2c86f7741aa57b5145" , "Quest test key"},
        {"5a0448bc86f774736f14efa8" , "The key to the closed premises of the sanatorium"},
        {"5a0dc45586f7742f6b0b73e3" , "Office 104 West wing key"},
        {"5a0dc95c86f77452440fc675" , "Office 112 West wing key"},
        {"5a0ea64786f7741707720468" , "Office 107 East wing key"},
        {"5a0ea69f86f7741cd5406619" , "Office 108 East wing key"},
        {"5a0ea79b86f7741d4a35298e" , "Health resort utility room key"},
        {"5a0eb38b86f774153b320eb0" , "SMW car key"},
        {"5a0eb6ac86f7743124037a28" , "Cottage back entrance key"},
        {"5a0ec6d286f7742c0b518fb5" , "West wing room 205 key"},
        {"5a0ec70e86f7742c0b518fba" , "West wing room 207 key"},
        {"5a0ee30786f774023b6ee08f" , "West wing room 216 key"},
        {"5a0ee34586f774023b6ee092" , "West wing room 220 key"},
        {"5a0ee37f86f774023657a86f" , "West wing room 221 key"},
        {"5a0ee4b586f7743698200d22" , "East wing room 206 key"},
        {"5a0ee62286f774369454a7ac" , "East wing room 209 key"},
        {"5a0ee72c86f77436955d3435" , "East wing room 213 key"},
        {"5a0ee76686f7743698200d5c" , "East wing room 216 key"},
        {"5a0eeb1a86f774688b70aa5c" , "West wing room 303 key"},
        {"5a0eeb8e86f77461257ed71a" , "West wing room 309 key"},
        {"5a0eebed86f77461230ddb3d" , "West wing room 325 key"},
        {"5a0eec9686f77402ac5c39f2" , "East wing room 310 key"},
        {"5a0eecf686f7740350630097" , "East wing room 313 key"},
        {"5a0eed4386f77405112912aa" , "East wing room 314 key"},
        {"5a0eedb386f77403506300be" , "East wing room 322 key"},
        {"5a0eee1486f77402aa773226" , "East wing room 328 key"},
        {"5a0eff2986f7741fd654e684" , "Health resort room 321 safe key"},
        {"5a0f006986f7741ffd2fe484" , "Weather station safe key"},
        {"5a0f045e86f7745b0f0d0e42" , "Gas station safe key"},
        {"5a0f068686f7745b0d4ea242" , "Cottage safe key"},
        {"5a0f075686f7745bcc42ee12" , "Key to store safe"},
        {"5a0f08bc86f77478f33b84c2" , "Health resort management office safe key"},
        {"5a0f0f5886f7741c4e32a472" , "Health resort warehouse safe key"},
        {"5a13ee1986f774794d4c14cd" , "West wing room 323 key"},
        {"5a13eebd86f7746fd639aa93" , "West wing room 218 key"},
        {"5a13ef0686f7746e5a411744" , "West wing room 219 key"},
        {"5a13ef7e86f7741290491063" , "West wing room 301 key"},
        {"5a13f24186f77410e57c5626" , "East wing room 222 key"},
        {"5a13f35286f77413ef1436b0" , "East wing room 226 key"},
        {"5a13f46386f7741dd7384b04" , "West wing room 306 key"},
        {"5a144bdb86f7741d374bbde0" , "East wing room 205 key"},
        {"5a144dfd86f77445cb5a0982" , "West wing room 203 key"},
        {"5a1452ee86f7746f33111763" , "West wing room 222 key"},
        {"5a145d4786f7744cbb6f4a12" , "East wing room 306 key"},
        {"5a145d7b86f7744cbb6f4a13" , "East wing room 308 key"},
        {"5a145ebb86f77458f1796f05" , "East wing room 316 key"},
        {"5ad5ccd186f774446d5706e9" , "Key to OLI administrator office"},
        {"5ad5cfbd86f7742c825d6104" , "Key to OLI logistics department office"},
        {"5ad5d20586f77449be26d877" , "Key to utility room of OLI outlet"},
        {"5ad5d49886f77455f9731921" , "Key to utility room of power substation"},
        {"5ad5d64486f774079b080af8" , "Key to pharmacy"},
        {"5ad5d7d286f77450166e0a89" , "Key to KIBA store outlet"},
        {"5ad5db3786f7743568421cce" , "Key to EMERCOM medical unit"},
        {"5ad7217186f7746744498875" , "Key to OLI cash register"},
        {"5ad7242b86f7740a6a3abd43" , "Key to IDEA cash register"},
        {"5ad7247386f7747487619dc3" , "Key to Goshan cash register"},
        {"5addaffe86f77470b455f900" , "Key to KIBA Outlet grate door"},
        {"5c094bbd86f7740d467a46f2" , "(off)item_keycard_black"},
        {"5c0a4091e52b1a00125e182d" , "(off)Lab. Black keycard"},
        {"5c0a4247e52b1a00125e1830" , "(off)Lab. Red keycard"},
        {"5c1d0c5f86f7744bb2683cf0" , "Lab. Blue keycard"},
        {"5c1d0d6d86f7744bb2683e1f" , "Lab. Yellow keycard. "},
        {"5c1d0dc586f7744baf2e7b79" , "Lab. Green keycard "},
        {"5c1d0efb86f7744baf2e7b7b" , "Lab. Red keycard"},
        {"5c1d0f4986f7744bb01837fa" , "Lab. Black keycard"},
        {"5c1e2a1e86f77431ea0ea84c" , "Lab. key. Manager office"},
        {"5c1e2d1f86f77431e9280bee" , "Lab. key. Testing area (weap.)"},
        {"5c1e495a86f7743109743dfb" , "Lab. Violet keycard"},
        {"5c1f79a086f7746ed066fb8f" , "Lab. key. Arsenal storage room"},
        {"5c94bbff86f7747ee735c08f" , "TerraGroup Labs access keycard"},
        {"5d08d21286f774736e7c94c3" , "Shturman key"},
        {"5d80c60f86f77440373c4ece" , "RB-BK key"},
        {"5d80c62a86f7744036212b3f" , "RB-VO key"},
        {"5d80c66d86f774405611c7d6" , "RB-AO key"},
        {"5d80c6c586f77440351beef1" , "RB-OB key"},
        {"5d80c6fc86f774403a401e3c" , "RB-TB key"},
        {"5d80c78786f774403a401e3e" , "RB-AK key"},
        {"5d80c88d86f77440556dbf07" , "RB-AM key"},
        {"5d80c8f586f77440373c4ed0" , "RB-OP key"},
        {"5d80c93086f7744036212b41" , "RB-MP11 key"},
        {"5d80c95986f77440351beef3" , "RB-MP12 key"},
        {"5d80ca9086f774403a401e40" , "RB-MP21 key"},
        {"5d80cab086f77440535be201" , "RB-MP22 key"},
        {"5d80cb3886f77440556dbf09" , "RB-PSP1 key"},
        {"5d80cb5686f77440545d1286" , "RB-PS81 key"},
        {"5d80cb8786f774405611c7d9" , "RB-PP key"},
        {"5d80cbd886f77470855c26c2" , "RB-MP13 key"},
        {"5d80ccac86f77470841ff452" , "RB-ORB1 key"},
        {"5d80ccdd86f77474f7575e02" , "RB-ORB2 key"},
        {"5d80cd1a86f77402aa362f42" , "RB-ORB3 key"},
        {"5d8e0db586f7744450412a42" , "RB-KORL key"},
        {"5d8e0e0e86f774321140eb56" , "RB-KPRL key"},
        {"5d8e15b686f774445103b190" , "Key to HEP station storage"},
        {"5d8e3ecc86f774414c78d05e" , "RB-GN key"},
        {"5d947d3886f774447b415893" , "RB-SMP key"},
        {"5d947d4e86f774447b415895" , "RB-KSM key"},
        {"5d95d6be86f77424444eb3a7" , "RB-PS82 key"},
        {"5d95d6fa86f77424484aa5e9" , "Key RB-PSP2"},
        {"5d9f1fa686f774726974a992" , "RB-ST key"},
        {"5da46e3886f774653b7a83fe" , "RB-RS key"},
        {"5da5cdcd86f774529238fb9b" , "RB-RH key"},
        {"5da743f586f7744014504f72" , "USEC stash on Customs key"},
        {"5e42c71586f7747f245e1343" , "ULTRA medical storage key"},
        {"5e42c81886f7742a01529f57" , "Object #11SR keycard"},
        {"5e42c83786f7742a021fdf3c" , "Object #21WS keycard"},
        {"5ede7a8229445733cb4c18e2" , "RB-PKPM key"},
        {"5ede7b0c6d23e5473e6e8c66" , "RB-RLSSA key"},
        {"5efde6b4f5448336730dbd61" , "Key card with a blue marking"},
        {"5eff09cd30a7dc22fd1ddfed" , "Key with tape"},
        {"54491bb74bdc2d09088b4567" , "ER Fulcrum Bayonet"},
        {"57cd379a24597778e7682ecf" , "Kiba Arms Tactical Tomahawk"},
        {"57e26ea924597715ca604a09" , "Bars A-2607- Damascus"},
        {"57e26fc7245977162a14b800" , "Bars A-2607- 95x18"},
        {"5bc9c1e2d4351e00367fbcf0" , "Antique axe"},
        {"5bead2e00db834001c062938" , "MPL-50 entrenching tool"},
        {"5bffdc370db834001d23eca8" , "6h5 Bayonet"},
        {"5bffdd7e0db834001b734a1a" , "Miller Bros. Blades M-2 Tactical Sword "},
        {"5bffe7930db834001b734a39" , "Crash Axe"},
        {"5c010e350db83400232feec7" , "SP-8 Survival Machete"},
        {"5c0126f40db834002a125382" , "Red Rebel Ice pick"},
        {"5c012ffc0db834001d23f03f" , "Camper axe"},
        {"5c07df7f0db834001b73588a" , "Freeman crowbar"},
        {"5fc64ea372b0dd78d51159dc" , "Cultist's knife"},
        {"544fb25a4bdc2dfb738b4567" , "Aseptic bandage"},
        {"544fb3364bdc2d34748b456a" , "Immobilizing splint"},
        {"544fb37f4bdc2dee738b4567" , "Analgin painkillers"},
        {"544fb3f34bdc2d03748b456a" , "Morphine injector"},
        {"544fb45d4bdc2dee738b4568" , "Salewa FIRST AID KIT"},
        {"5751a25924597722c463c472" , "Army bandage"},
        {"5751a89d24597722aa0e8db0" , "Golden Star Balm"},
        {"5755356824597772cb798962" , "AI-2 medikit"},
        {"5755383e24597772cb798966" , "Vaseline"},
        {"590c657e86f77412b013051d" , "Grizzly First Aid Kit"},
        {"590c661e86f7741e566b646a" , "Car first aid kit"},
        {"590c678286f77426c9660122" , "IFAK personal tactical first aid kit"},
        {"590c695186f7741e566b64a2" , "Augmentin antibiotic pills"},
        {"5af0454c86f7746bf20992e8" , "Immobilizing splint"},
        {"5af0548586f7743a532b7e99" , "Ibuprofen painkillers"},
        {"5c0e530286f7747fa1419862" , "Propital"},
        {"5c0e531286f7747fa54205c2" , "Combat stimulant injector SJ1 TGLabs"},
        {"5c0e531d86f7747fa23f4d42" , "Combat stimulant injector SJ6 TGLabs"},
        {"5c0e533786f7747fa23f4d47" , "Hemostatic drug Zagustin"},
        {"5c0e534186f7747fa1419867" , "Regenerative stimulant injector eTG-change"},
        {"5c10c8fd86f7743d7d706df3" , "Adrenaline injector"},
        {"5d02778e86f774203e7dedbe" , "CMS kit"},
        {"5d02797c86f774203f38e30a" , "Surv12 field surgical kit"},
        {"5e831507ea0a7c419c2f9bd9" , "Esmarch tourniquet"},
        {"5e8488fa988a8701445df1e4" , "CALOK-B Hemostatic"},
        {"5e99711486f7744bfc4af328" , "Sanitar first aid kit"},
        {"5e99735686f7744bfc4af32c" , "Sanitar kit"},
        {"5ed515c8d380ab312177c0fa" , "3-(b-TG)"},
        {"5ed515e03a40a50460332579" , "L1 (Norepinephrine)"},
        {"5ed515ece452db0eb56fc028" , "P22"},
        {"5ed515f6915ec335206e4152" , "AHF1-M"},
        {"5ed5160a87bb8443d10680b5" , "Meldonin"},
        {"5ed51652f6c34d2cc26336a1" , "M.U.L.E. stimulator"},
        {"5ed5166ad380ab312177c100" , "Cocktail \"Obdolbos\""},
        {"5fca138c2a7b221b2852a5c6" , "Antidote xTG-12"},
        {"5fca13ca637ee0341a484f46" , "Combat stimulant injector SJ9 TGLabs"},
        {"5448c12b4bdc2d02308b456f" , "90-93 9x18PM Magazine, for 8 PM rounds"},
        {"5448c1d04bdc2dff2f8b4569" , "PMAG GEN M3 20 5.56x45 STANAG 20-round magazine"},
        {"544909bb4bdc2d6f028b4577" , "AN/PEQ-15 tactical device"},
        {"54490a4d4bdc2dbc018b4573" , "Silencerco Sparrow 22 .22LR silencer"},
        {"544a378f4bdc2d30388b4567" , "40-round PMAG GEN M3 40 5.56x45 STANAG magazine"},
        {"544a37c44bdc2d25388b4567" , "60-round MAG5-60 5.56x45 STANAG magazine"},
        {"544a38634bdc2d58388b4568" , "Colt USGI A2 5.56x45 Flash hider for AR-15"},
        {"5580169d4bdc2d9d138b4585" , "510mm barrel for MP-43e-1c 12ga"},
        {"5580239d4bdc2de7118b4583" , "GK-01 compensator"},
        {"55802d5f4bdc2dac148b458e" , "PMAG GEN M3 W 30 5.56x45 STANAG 30-round magazine"},
        {"55802f5d4bdc2dac148b458f" , "Magpul MOE AR-15 pistol grip"},
        {"558032614bdc2de7118b4585" , "Tango Down Stubby BGV-MK46K tactical grip Black"},
        {"559ba5b34bdc2d1f1a8b4582" , "10-round polymer magazine 7.62x54R for SV-98"},
        {"55d355e64bdc2d962f8b4569" , "Upper receiver Colt M4A1 5.56x45 for M4A1 assault rifle"},
        {"55d35ee94bdc2d61338b4568" , "260mm barrel for AR-15 and compatible 5.56x45"},
        {"55d3632e4bdc2d972f8b4569" , "370mm barrel for AR-15 and compatible 5.56x45"},
        {"55d447bb4bdc2d892f8b456f" , "725mm barrel for MP-43e-1s 12ga"},
        {"55d448594bdc2d8c2f8b4569" , "610mm barrel for MP-133 12ga shotgun"},
        {"55d4491a4bdc2d882f8b456e" , "510mm barrel for MP-133 12ga"},
        {"55d449444bdc2d962f8b456d" , "610mm barrel for MP-133 12ga shotgun with rib"},
        {"55d44fd14bdc2d962f8b456e" , " Colt AR-15 charging handle for AR-15"},
        {"55d459824bdc2d892f8b4573" , "Knight's Armament KAC RIS handguard for AR-15 and compatibles"},
        {"55d45d3f4bdc2d972f8b456c" , "Izhmekh MP-133 Beechwood forestock"},
        {"55d45f484bdc2d972f8b456d" , "Custom plastic MP-133 forestock with mounts"},
        {"55d480c04bdc2d1d4e8b456a" , "30-round 6L23 5.45x39 magazine for AK-74 and compatibles"},
        {"55d481904bdc2d8c2f8b456a" , "45-round 6L26 5.45x39 magazine for AK-74 and compatibles"},
        {"55d482194bdc2d1d4e8b456b" , "60-round 6L31 5.45x39 magazine for AK-74 and compatibles"},
        {"55d4837c4bdc2d1d4e8b456c" , "10-round Saiga 545 5.45x39 magazine for AK-74 and compatibles"},
        {"55d484b44bdc2d1d4e8b456d" , "6-shell MP-133x6 12ga magazine"},
        {"55d485804bdc2d8c2f8b456b" , "8-shell MP-133x8 12ga magazine"},
        {"55d485be4bdc2d962f8b456f" , "PM/PPSH 9x18PM 84-round drum mag for PM"},
        {"55d4887d4bdc2d962f8b4570" , "Colt AR-15 5.56x45 STANAG 30-round magazine"},
        {"55d48a634bdc2d8b2f8b456a" , "Kiba Arms International SPRM mount for pump-action shotguns\n"},
        {"55d48ebc4bdc2d8c2f8b456c" , "Delta-tek Sprut mount for pump-action shotguns"},
        {"55d4ae6c4bdc2d8b2f8b456e" , "High Standard M4SS Stock"},
        {"55d4b9964bdc2d1d4e8b456e" , "Colt A2 AR-15 pistol grip"},
        {"55d614004bdc2d86028b4568" , "Surefire SOCOM556-MONSTER 5.56x45 silencer"},
        {"55d617094bdc2d89028b4568" , "Knight's Armament Company KAC QDC Suppressor 6.5x35"},
        {"55d6190f4bdc2d87028b4567" , "Surefire SOCOM556-MINI MONSTER 5.56x45 Silencer"},
        {"55f84c3c4bdc2d5f408b4576" , "Daniel Defence RIS II 9.5 foregrip for AR-15-compatible systems"},
        {"560835c74bdc2dc8488b456f" , "510mm barrel for MP-133 12ga shotgun with rib"},
        {"560836484bdc2d20478b456e" , "540mm barrel for MP-133 12ga shotgun"},
        {"560836b64bdc2d57468b4567" , "540mm barrel for MP-133 12ga shotgun with rib"},
        {"560836fb4bdc2d773f8b4569" , "660mm barrel for MP-133 12ga shotgun"},
        {"560837154bdc2da74d8b4568" , "660mm barrel for MP-133 12ga shotgun with rib"},
        {"5608373c4bdc2dc8488b4570" , "710mm barrel for MP-133 12ga shotgun"},
        {"560837544bdc2de22e8b456e" , "710mm barrel for MP-133 12ga shotgun with rib"},
        {"560837824bdc2d57468b4568" , "750mm barrel for MP-133 12ga shotgun"},
        {"5608379a4bdc2d26448b4569" , "750mm barrel for MP-133 12ga shotgun with rib"},
        {"560838c94bdc2d77798b4569" , "Remington Tactical Choke 12ga"},
        {"56083a334bdc2dc8488b4571" , "Plastic pistol grip for MP-133/153"},
        {"56083be64bdc2d20478b456f" , "Plastic stock for MP-133/153"},
        {"56083cba4bdc2de22e8b456f" , "Wooden stock for MP-133/153"},
        {"56083eab4bdc2d26448b456a" , "SV-98 anti-heat ribbon"},
        {"560d657b4bdc2da74d8b4572" , "Zenit 2P Klesch flashlight + laser designator"},
        {"560e620e4bdc2d724b8b456b" , "SV-98 muzzle device"},
        {"5648ac824bdc2ded0b8b457d" , "Zenit RP-1 charge handle for AK"},
        {"5648ae314bdc2d3d1c8b457f" , "CAA RS47 foregrip for AK-compatible systems"},
        {"5648b0744bdc2d363b8b4578" , "Wooden AK-74 handguard (6P20 Sb.6)"},
        {"5648b1504bdc2d9d488b4584" , "Polymer AK-74 foregrip (6P20 Sb.9)"},
        {"5648b2414bdc2d3b4c8b4578" , "UltiMAK M1-B handguard for AK"},
        {"5648b4534bdc2d3d1c8b4580" , "B-10M foregrip and rail mount B-19"},
        {"5648b62b4bdc2d9d488b4585" , "GP-34 underbarrel grenade launcher"},
        {"5648b6ff4bdc2d3d1c8b4581" , "Tactica Tula 10000 mount"},
        {"5649a2464bdc2d91118b45a8" , "NcStar MPR45 Backup mount"},
        {"5649aa744bdc2ded0b8b457e" , "Izhmash 5.45x39 AK-74 muzzle brake & compensator (6P20 0-20)"},
        {"5649ab884bdc2ded0b8b457f" , "Zenit DTK-1 7.62x39 & 5.45x39 muzzle brake & compensator for AK "},
        {"5649ad3f4bdc2df8348b4585" , "Izhmash AK bakelite pistol grip (6P4 Sb.8V)"},
        {"5649ade84bdc2d1b2b8b4587" , "Izhmash AK polymer pistol grip (6P1 Sb.8)"},
        {"5649ae4a4bdc2d1b2b8b4588" , "Zenit RK-3 AK pistol grip"},
        {"5649af094bdc2df8348b4586" , "Izhmash AK-74 dust cover (6P1 0-1)"},
        {"5649af884bdc2d1b2b8b4589" , "Zenit B-33 dust cover for AK-74"},
        {"5649b0fc4bdc2d17108b4588" , "Izhmash polymer AK-74 stock (6P20 Sb.7)"},
        {"5649b1c04bdc2d16268b457c" , "Izhmash wooden AK-74 stock (6P20 Sb.5)"},
        {"5649b2314bdc2d79388b4576" , "ME adapter for AK"},
        {"5649be884bdc2d79388b4577" , "Colt buffer tube"},
        {"564ca99c4bdc2d16268b4589" , "6L20 30-round 5.45x39 magazine for AK-74 and compatible weapons"},
        {"564ca9df4bdc2d35148b4569" , "6L18 45-round 5.45x39 magazine for AK-74 and compatible weapons"},
        {"564caa3d4bdc2d17108b458e" , "TGP-A 5.45x39 muzzle device/suppressor"},
        {"56d59948d2720bb7418b4582" , "P226 magazine"},
        {"56d5a1f7d2720bb3418b456a" , "112mm barrel for P226 9x19"},
        {"56d5a2bbd2720bb8418b456a" , "Black polymer Sig Sauer pistol grip for P226"},
        {"56d5a407d2720bb3418b456b" , "SIG Sauer P226R 9x19 pistol slide"},
        {"56deec93d2720bec348b4568" , "750 mm barrel for MP-153 12ga shotgun"},
        {"56deed6ed2720b4c698b4583" , "Izhmekh MP-153 Polymer stock"},
        {"56deee15d2720bee328b4567" , "MP-153 forend cap"},
        {"56deeefcd2720bc8328b4568" , "MP-153 8-rd magazine extension"},
        {"56def37dd2720bec348b456a" , "X400 tactical flashlight"},
        {"56e05a6ed2720bd0748b4567" , "TSNIITOCHMASH bakelite PB side grips"},
        {"56e05b06d2720bb2668b4586" , "Stock silencer for PB 9x18 PM"},
        {"56ea6fafd2720b844b8b4593" , "Noveske KX3 5.56x45 flash hider"},
        {"56ea7165d2720b6e518b4583" , "Badger Ordnance Tactical Charging Handle Latch "},
        {"56ea8180d2720bf2698b456a" , "KAC QD Compensator 5.56x45"},
        {"56ea8222d2720b69698b4567" , "Izhmash SV-98 bipod"},
        {"56ea8d2fd2720b7c698b4570" , "Windham Weaponry Rail Gas Block"},
        {"56eabcd4d2720b66698b4574" , "MK12 Low Profile Gas Block"},
        {"56eabf3bd2720b75698b4569" , "MOE Carbine stock"},
        {"571659bb2459771fb2755a12" , "DI ECS FDE pistol grip for AR-15 based systems"},
        {"571a26d524597720680fbe8a" , "116mm 7.62x25 TT barrel"},
        {"571a279b24597720b4066566" , "Homespun 121mm 7.62x25 TT barrel with threading"},
        {"571a282c2459771fb2755a69" , "Standard TT side grips"},
        {"571a28e524597720b4066567" , "Makeshift 7.62x25 TT silencer"},
        {"571a29dc2459771fb2755a6a" , "tt-105 7.62x25 TT Magazine"},
        {"574dad8024597745964bf05c" , "Wooden stock 56-A-231 Sb.5"},
        {"576167ab2459773cad038c43" , "SOK-12 Protection tube"},
        {"576169e62459773c69055191" , "SOK-12 polymer handguard Sb.7-1"},
        {"57616a9e2459773c7a400234" , "Sb.5 5-round 12/76 magazine for SOK-12 and compatible weapons"},
        {"57616c112459773cce774d66" , "Izhmash SOK-12 Sb.0-2 dust cover"},
        {"57616ca52459773c69055192" , "Izhmash SOK-12 AA type stock"},
        {"576a5ed62459771e9c2096cb" , "MP-443 9x19 18-round magazine"},
        {"576a63cd2459771e796e0e11" , "Polymer Izhmekh pistol grip for MP-443"},
        {"576a7c512459771e796e0e17" , "B-8 mount"},
        {"577d128124597739d65d0e56" , "Burris FastFire Weaver Base"},
        {"57838c962459774a1651ec63" , "VSS 9x39 integral barrel-suppressor"},
        {"57838f0b2459774a256959b2" , "10-round 6L24 9x39 VSS magazine"},
        {"57838f9f2459774a150289a0" , "20-round 6L25 9x39 VSS magazine"},
        {"578395402459774a256959b5" , "VSS Vintorez dust cover"},
        {"578395e82459774a0e553c7b" , "TSNIITochMash VSS Vintorez stock"},
        {"57a3459f245977764a01f703" , "B-3 mount"},
        {"57acb6222459771ec34b5cb0" , "Pilad 043-02 Mount"},
        {"57ade1442459771557167e15" , "Armacon Baskak stock"},
        {"57af48872459771f0b2ebf11" , "Hogue OverMolded Rubber Grip FDE"},
        {"57c44dd02459772d2e0ae249" , "AS VAL 9x39 integral barrel-suppressor"},
        {"57c44f4f2459772d2c627113" , "AS VAL Dust cover"},
        {"57c44fa82459772d2d75e415" , "AS VAL Pistol grip"},
        {"57c450252459772d28133253" , "TSNIITochMash AS VAL stock"},
        {"57c55efc2459772d2c6271e7" , "Hogue OverMolded Rubber Grip Black"},
        {"57c55f092459772d291a8463" , "Hogue OverMolded Rubber Grip Ghillie Earth"},
        {"57c55f112459772d28133310" , "Hogue OverMolded Rubber Grip Ghillie Green"},
        {"57c55f172459772d27602381" , "Hogue OverMolded Rubber Grip OD Green"},
        {"57c69dd424597774c03b7bbc" , "30mm Scope mount"},
        {"57c9a89124597704ee6faec1" , "Sig Sauer FDE pistol grip for P226 (Combat)"},
        {"57cff947245977638e6f2a19" , "Magpul MOE AKM HAND GUARD (Black) for AK"},
        {"57cffb66245977632f391a99" , "Magpul M-LOK AFG Tactical grip"},
        {"57cffcd624597763133760c5" , "Magpul M-LOK AFG (Flat Dark Earth) Tactical grip"},
        {"57cffcdd24597763f5110006" , "Magpul M-LOK AFG (Olive Drab) Tactical grip"},
        {"57cffce524597763b31685d8" , "Magpul M-LOK AFG (Stealth Gray) Tactical grip"},
        {"57cffd8224597763b03fc609" , "Magpul MOE AKM HAND GUARD (Flat Dark Earth) for AK"},
        {"57cffddc24597763133760c6" , "Magpul MOE AKM HAND GUARD (Flat Dark Earth) for AK"},
        {"57cffe0024597763b03fc60b" , "Magpul MOE AKM HAND GUARD (Plum) for AK"},
        {"57cffe20245977632f391a9d" , "Magpul MOE AKM HAND GUARD (Stealth Gray) for AK"},
        {"57d14e1724597714010c3f4b" , "Standard 9x18PM 20-round magazine for PP-91"},
        {"57d1519e24597714373db79d" , "Standard 9x18PM 30-round magazine for PP-91"},
        {"57d152ec245977144076ccdf" , "ZMZ Polymer pistol grip for PP-91"},
        {"57d17c5e2459775a5c57d17d" , "Ultrafire WF-501B Flashlight"},
        {"57d17e212459775a1179a0f5" , "25 mm mount ring"},
        {"57da93632459771cb65bf83f" , "KAC QDSS NT-4 Black 5.56x45 silencer"},
        {"57dbb57e2459774673234890" , "KAC QDSS NT-4 FDE 5.56x45 silencer"},
        {"57dc324a24597759501edc20" , "IzhMash 5.45x39 muzzle brake for AKS-74U (6P26 0-20)"},
        {"57dc32dc245977596d4ef3d3" , "Wooden AKS-74U Handguard (6P26 Sb.6)"},
        {"57dc334d245977597164366f" , "AKS-74U Dust cover (6P26 Sb.7)"},
        {"57dc347d245977596754e7a1" , "IzhMash metal stock for AKS-74U (6P26 Sb.5)"},
        {"57e3dba62459770f0c32322b" , "Izhmash AK-74 Textolite pistol grip (6P4 Sb.9)"},
        {"57ee59b42459771c7b045da5" , "Rotor 43 RIS mount for PP Kedr"},
        {"57f3a5ae2459772b0e0bf19e" , "PSO scope eyecup"},
        {"57f3c7e024597738ea4ba286" , "PP-91-01 Kedr-B muzzle thread piece"},
        {"57f3c8cc2459773ec4480328" , "PP-91-01 Kedr-B 9x18PM suppressor"},
        {"57fd23e32459772d0805bcf1" , "Holosun LS321 Tactical device"},
        {"57ffa9f4245977728561e844" , "B-11 AKS-74U Handguard"},
        {"57ffaea724597779f52b3a4d" , "B-12 Mount"},
        {"57ffb0062459777a045af529" , "B-18 Mount"},
        {"57ffb0e42459777d047111c5" , "PBS-4 5.45x39 Silencer"},
        {"5827272a24597748c74bdeea" , "SOK-12 aluminum handguard MTU002 Long Top"},
        {"58272b392459774b4c7b3ccd" , "SOK-12 aluminum handguard MTU002 Short Top"},
        {"58272d7f2459774f6311ddfd" , "GK-02 Muzzle Brake"},
        {"5839a7742459773cf9693481" , "IzhMash AKS-74UB Dust cover"},
        {"587de4282459771bca0ec90b" , "Threaded barrel for P226 9x19"},
        {"587de5ba2459771c0f1e8a58" , "P226 thread protection cap"},
        {"587df3a12459772c28142567" , "10 rnds. SKS internal box magazine 7.62x39"},
        {"587df583245977373c4f1129" , "ProMag SKS-A5 7.62x39 20-round SKS magazine."},
        {"587e0531245977466077a0f7" , "Wooden stock for Molot OP-SKS"},
        {"587e08ee245977446b4410cf" , "Dovetail OP-SKS mount."},
        {"588200af24597742fa221dfb" , "610 mm barrel for MP-153 12ga shotgun"},
        {"588200c224597743990da9ed" , "660 mm barrel for MP-153 12ga shotgun"},
        {"588200cf2459774414733d55" , "710 mm barrel for MP-153 12ga shotgun"},
        {"5882163224597757561aa920" , "MP-153 7-rd magazine extension"},
        {"5882163824597757561aa922" , "MP-153 6-rd magazine extension"},
        {"5882163e24597758206fee8c" , "MP-153 5-rd magazine extension"},
        {"588226d124597767ad33f787" , "Magpul AFG grip black"},
        {"588226dd24597767ad33f789" , "Magpul AFG grip FDE"},
        {"588226e62459776e3e094af7" , "Magpul AFG grip FG"},
        {"588226ef24597767af46e39c" , "Magpul AFG grip OD"},
        {"5888945a2459774bf43ba385" , "500mm .308 barrel for DVL-10"},
        {"5888956924597752983e182d" , "660mm .308 barrel for DVL-10 M2"},
        {"5888961624597754281f93f3" , "Harris HBR Bipod"},
        {"5888976c24597754281f93f5" , "LOBAEV Arms DVL-10 M2 handguard"},
        {"5888988e24597752fe43a6fa" , "10-round .308 DVL-10 magazine"},
        {"5888996c24597754281f9419" , "DVL-10 M2 muzzle brake"},
        {"58889c7324597754281f9439" , "DVL-10 muzzle device"},
        {"58889d0c2459775bc215d981" , "LOBAEV Arms Stock"},
        {"588b56d02459771481110ae2" , "Daniel Defence RIS II 9.5 foregrip for AR-15-compatible systems"},
        {"58949dea86f77409483e16a8" , "A2 9x19 Flash hider for MPX"},
        {"58949edd86f77409483e16a9" , "SIG double latch charging handle for MPX"},
        {"58949fac86f77409483e16aa" , "SIG single latch charging handle for MPX"},
        {"5894a05586f774094708ef75" , "Standard MPX 30-round 9x19 magazine"},
        {"5894a13e86f7742405482982" , "Early produced SIG collapsing/telescoping MCX/MPX stock"},
        {"5894a2c386f77427140b8342" , "203 mm 9x19 barrel for MPX"},
        {"5894a42086f77426d2590762" , "Handguard SIG MPX Gen. 1 for MPX"},
        {"5894a51286f77426d13baf02" , "Pistol grip SIG MPX"},
        {"5894a5b586f77426d2590767" , "Upper receiver of the first generation SIG MPX "},
        {"58a56f8d86f774651579314c" , "SIG MPX Gen1 Handguard 2 inch rail adapter"},
        {"58a5c12e86f7745d585a2b9e" , "SIG MPX Gen1 Handguard 4 inch rail adapter"},
        {"58ac1bf086f77420ed183f9f" , "SIG retractable stock pipe adapter"},
        {"58aeaaa886f7744fc1560f81" , "165 mm 9x19 barrel for MPX-SD"},
        {"58aeac1b86f77457c419f475" , "MPX-SD 9x19 Integrated silencer"},
        {"58c157be86f77403c74b2bb6" , "Tango Down Stubby BGV-MK46K tactical grip FDE"},
        {"58c157c886f774032749fb06" , "Tango Down Stubby BGV-MK46K tactical grip FG"},
        {"58d2664f86f7747fec5834f6" , "Cross Slot Mount base for Deltapoint scopes"},
        {"58d2912286f7744e27117493" , "Magpul Rubber Butt-Pad for Carbine stock series"},
        {"58d2946386f774496974c37e" , "MOE Carbine stock FDE"},
        {"58d2946c86f7744e271174b5" , "MOE Carbine stock FG"},
        {"58d2947686f774485c6a1ee5" , "MOE Carbine stock OD"},
        {"58d2947e86f77447aa070d53" , "MOE Carbine stock SG"},
        {"58d39b0386f77443380bf13c" , "Aimpoint Micro Spacer High"},
        {"58d39d3d86f77445bb794ae7" , "Aimpoint mount for the sights of Micro series."},
        {"591aef7986f774139d495f03" , "Troy M7A1 PDW Blk stock"},
        {"591af10186f774139d495f0e" , "Troy M7A1 PDW FDE stock"},
        {"591af28e86f77414a27a9e1d" , "Viking Tactical UVG Tactical grip"},
        {"591c4e1186f77410354b316e" , "Cobra family sights shade"},
        {"591ee00d86f774592f7b841e" , "Axion Cobra mount"},
        {"5926c0df86f77462f647f764" , "HK MP5 Upper receiver"},
        {"5926c32286f774616e42de99" , "MP5 Cocking Handle"},
        {"5926c36d86f77467a92a8629" , "MP5 Wide Tropical Polymer handguard"},
        {"5926c3b286f774640d189b6b" , "Standard MP5 30-round 9x19 magazine"},
        {"5926d33d86f77410de68ebc0" , "MP5SD 9x19 silencer"},
        {"5926d3c686f77410de68ebc8" , "HK A2 Stock"},
        {"5926d40686f7740f152b6b7e" , "HK A3 old stock model."},
        {"5926dad986f7741f82604363" , "MFI HK Universal Low Profile Scope Mount"},
        {"5926e16e86f7742f5a0f7ecb" , "3 Lug thread protector"},
        {"5926f2e086f7745aae644231" , "HK MP5SD Upper receiver"},
        {"5926f34786f77469195bfe92" , "MP5SD Polymer handguard"},
        {"593d1fa786f7746da62d61ac" , "UTG SKS SOCOM Rail mount"},
        {"593d489686f7745c6255d58a" , "Hexagon AKM 7.62x39 sound suppressor"},
        {"593d490386f7745ee97a1555" , "Hexagon SKS 7.62x39 sound suppressor"},
        {"593d493f86f7745e6b2ceb22" , "Hexagon AK-74 5.45x39 sound suppressor"},
        {"5943ee5a86f77413872d25ec" , "PWS CQB 5.56 x 45 Muzzle brake"},
        {"5943eeeb86f77412d6384f6b" , "PWS CQB 74 5.45x39 Muzzle brake"},
        {"5947c73886f7747701588af5" , "MFT BUS Stock"},
        {"5947e98b86f774778f1448bc" , "UBR GEN2 black stock"},
        {"5947eab886f77475961d96c5" , "UBR GEN2 FDE stock"},
        {"5947f92f86f77427344a76b1" , "TAPCO SAW-Style black pistol grip for AK"},
        {"5947fa2486f77425b47c1a9b" , "TAPCO SAW-Style FDE pistol grip for AK"},
        {"595cf16b86f77427440c32e2" , "Handguard War Sport LVOA-S blk. for use with AR-15 and compatible"},
        {"595cfa8b86f77427437e845b" , "Handguard War Sport LVOA-C blk. for use with AR-15 and compatible"},
        {"59984b4286f77445bd2d4a07" , "PP-19-01 Polymer handguard"},
        {"5998517986f7746017232f7e" , "PP-19-01 Izhmash pistol grip"},
        {"599851db86f77467372f0a18" , "Metal Izhmash stock for PP-19-01"},
        {"5998529a86f774647f44f421" , "10-round Izh.9x19 Sb.7 magazine"},
        {"5998597786f77414ea6da093" , "Izhmash 9x19 PP-19-01 muzzle brake/compensator"},
        {"5998598e86f7740b3f498a86" , "Izhmash 9x19 Saiga-9 muzzle brake/compensator"},
        {"59985a6c86f77414ec448d17" , "Izhmash Vityaz-SN receiver cover"},
        {"59985a8086f77414ec448d1a" , "Izhmash Vityaz receiver cover"},
        {"599860ac86f77436b225ed1a" , "Standard PP-19-01 30-round 9x19 magazine"},
        {"59bfc5c886f7743bf6794e62" , "Vityaz 9x19 sound suppressing device"},
        {"59bfe68886f7746004266202" , "Vltor MUR-1S 5.56x45 Upper receiver for AR systems"},
        {"59bffbb386f77435b379b9c2" , "Silencerco Hybrid 46 multi-caliber silencer"},
        {"59bffc1f86f77435b128b872" , "Direct Thread Mount adapter for Silencerco Hybrid 46."},
        {"59c0ec5b86f77435b128bfca" , "Hexagon 12K sound suppressor"},
        {"59c1383d86f774290a37e0ca" , "Magpul PMAG D-60 5.56x45 60-round magazine"},
        {"59c63b4486f7747afb151c1c" , "B&T MP5 SD Tri Rail Ring Mount"},
        {"59c6633186f7740cf0493bb9" , "AK-74 Gas tube"},
        {"59ccd11386f77428f24a488f" , "PP-19-01 gas tube"},
        {"59ccfdba86f7747f2109a587" , "UltiMAK M1-B gas tube for AK"},
        {"59d36a0086f7747e673f3946" , "AKS-74U Gas tube"},
        {"59d625f086f774661516605d" , "Izhmash AK magazine 30-round for 7.62x39 AK and compatibles"},
        {"59d6272486f77466146386ff" , "Pmag 30 AK/AKM GEN M3 7.62x39 magazine for AK and compatibles, 30-round capacity\n"},
        {"59d64ec286f774171d1e0a42" , "AKM (6P1 Sb.1-2) gas tube"},
        {"59d64f2f86f77417193ef8b3" , "Wooden AK-74 handguard (6P1 Sb.6-1)"},
        {"59d64fc686f774171b243fe2" , "Izhmash 7.62x39 AKM muzzle brake & compensator (6P1 0-14)"},
        {"59d6507c86f7741b846413a2" , "Izhmash AKM dust cover (6P1 0-1)"},
        {"59d6514b86f774171a068a08" , "Izhmash wooden AKM stock (6P1 Sb.5)"},
        {"59d790f486f77403cb06aec6" , "Armytek Predator Pro v3 XHP35 HI Flashlight"},
        {"59db3a1d86f77429e05b4e92" , "Naroh Arms GRAL-S Pistol grip for AR-15-compatible weapons"},
        {"59db3acc86f7742a2c4ab912" , "Stark AR Rifle Grip (black) for AR-15-compatible weapons"},
        {"59db3b0886f77429d72fb895" , "Stark AR Rifle Grip (FDE) for AR-15-compatible weapons"},
        {"59db7eed86f77461f8380365" , "TA51 Mount for sights"},
        {"59e0bdb186f774156f04ce82" , "Vltor CASV KeyMod 2 inch guide"},
        {"59e0be5d86f7742d48765bd2" , "Vltor CASV KeyMod 4 inch guide"},
        {"59e0bed186f774156f04ce84" , "Vltor CASV keymod 6 inch guide"},
        {"59e5d83b86f7745aed03d262" , "7.62x39 ribbed metal magazine for AK and compatibles, 10-round capacity"},
        {"59e5f5a486f7746c530b3ce2" , "Molot 6P2.Sb-11 7.62x39 magazine for AK and compatibles, 40-round capacity"},
        {"59e61eb386f77440d64f5daf" , "Molot 7.62x39 Vepr KM / VPO-136 muzzle brake & compensator"},
        {"59e6227d86f77440d64f5dc2" , "Molot wooden VPO-136 stock"},
        {"59e6284f86f77440d569536f" , "Wooden VPO-136 handguard"},
        {"59e62cc886f77440d40b52a1" , "Izhmash AKM bakelite pistol grip"},
        {"59e6318286f77444dd62c4cc" , "Molot AK bakelite pistol grip"},
        {"59e6449086f7746c9f75e822" , "Molot AKM type dust cover"},
        {"59e649f986f77411d949b246" , "Molot AKM type gas tube\n"},
        {"59e898ee86f77427614bd225" , "Wooden AKM / VPO-209 handguard"},
        {"59e89d0986f77427600d226e" , "Molot wooden VPO-209 stock"},
        {"59e8a00d86f7742ad93b569c" , "Thread protection for AKM/VPO-209"},
        {"59eb7ebe86f7740b373438ce" , "TOZ 6P29M Mount"},
        {"59ecc28286f7746d7a68aa8c" , "AKS-74/AKS-74U PT Lock"},
        {"59ecc3dd86f7746dc827481c" , "Zenit PT-3 \"Klassika\" stock"},
        {"59f8a37386f7747af3328f06" , "Fortis Shift tactical grip"},
        {"59f99a7d86f7745b134aa97b" , "SR1-MP magazine"},
        {"59fafc5086f7740dbe19f6c3" , "Palm US AK30 7.62x39 magazine for AK and compatibles, 30-round capacity (black)"},
        {"59fafc9386f774067d462453" , "Palm US AK30 7.62x39 magazine for AK and compatibles, 30-round capacity (FDE)"},
        {"59fb137a86f7740adb646af1" , "Tromix Monster Claw 12ga muzzle brake"},
        {"59fb257e86f7742981561852" , "Zenit DTK-4M muzzle brake"},
        {"59fb375986f7741b681b81a6" , "Krebs Custom UFM Keymod System handguard for AKM"},
        {"59fc48e086f77463b1118392" , "Magpul RVG grip black"},
        {"59ff3b6a86f77477562ff5ed" , "Izhmash shoulder piece for AKMS (6P4 Sb.1-19)"},
        {"5a0060fc86f7745793204432" , "Izhmash 7.62x39 AKMS aluminium magazine for AK and compatibles, 30-round capacity"},
        {"5a0071d486f77404e23a12b2" , "Wooden Izhmash AKM pistol grip for AK"},
        {"5a01ad4786f77450561fda02" , "Kiba Arms VDM CS gas tube"},
        {"5a01c29586f77474660c694c" , "Izhmash 6L10 7.62x39 magazine for AK and compatibles, 30-round capacity"},
        {"5a0abb6e1526d8000a025282" , "Taktika Tula AK and AKM adapter"},
        {"5a0c59791526d8dba737bba7" , "Recoil pad from GP-25 for AK Accessory Kit"},
        {"5a0d63621526d8dba31fe3bf" , "PBS-1 7.62x39 silencer"},
        {"5a0d716f1526d8000d26b1e2" , "Izhmash 7.62x39 flash hider for AKML system"},
        {"5a16b8a9fcdbcb00165aa6ca" , "Norotos Titanium Advanced Tactical Mount "},
        {"5a16b93dfcdbcbcae6687261" , "Dual Dovetail Mount for PVS-14 monocular"},
        {"5a17fb03fcdbcbcae668728f" , "Standard APS 9x18PM 20-round magazine"},
        {"5a17fb9dfcdbcbcae6687291" , "APB detachable wire stock"},
        {"5a17fc70fcdbcb0176308b3d" , "APS bakelite side-pieces"},
        {"5a1eacb3fcdbcb09800872be" , "REAP-IR scope eyecup"},
        {"5a1ead28fcdbcb001912fa9f" , "UNV DLOC-IRD Mount for sights"},
        {"5a27b281c4a28200741e1e52" , "SR1MP single rail mount"},
        {"5a27b3d0c4a282000d721ec1" , "SR1MP silencer mount"},
        {"5a27b6bec4a282000e496f78" , "SR1MP silencer 9x21"},
        {"5a27bad7c4a282000b15184b" , "SR1MP quad rail mount"},
        {"5a329052c4a28200741e22d3" , "Remington Arms handguard for a R11 RSASS"},
        {"5a32a064c4a28200741e22de" , "SilencerCo Osprey 9 9x19mm sound suppressor"},
        {"5a32aa0cc4a28232996e405f" , "Trijicon RMR mount for a Sig-Sauer pistols"},
        {"5a339805c4a2826c6e06d73d" , "MIAD Pistol grip for AR-15 based systems"},
        {"5a33a8ebc4a282000c5a950d" , "Alpha Dog Alpha 9 9x19 sound suppressor"},
        {"5a33b2c9c4a282000c5a9511" , "Low profile mount for Trijicon RMR"},
        {"5a33b652c4a28232996e407c" , "High profile mount for Trijicon RMR"},
        {"5a33bab6c4a28200741e22f8" , "Trijicon RMR mount for ACOG scopes"},
        {"5a33ca0fc4a282000d72292f" , "COLT \"A2\" buffer tube"},
        {"5a33cae9c4a28232980eb086" , "Magpul PRS GEN2 FDE stock"},
        {"5a33e75ac4a2826c6e06d759" , "Hera Arms CQR pistol grip-stock"},
        {"5a34f7f1c4a2826c6e06d75d" , "18\" barrel for a AR-10 and compatible 7.62x51 NATO"},
        {"5a34fae7c4a2826c6e06d760" , "22\" barrel for a AR-10 and compatible 7.62x51 NATO"},
        {"5a34fbadc4a28200741e230a" , "JP Enterprises Gas System-6"},
        {"5a34fd2bc4a282329a73b4c5" , "AAC Blackout 51T flash hider (7.62x51)"},
        {"5a34fe59c4a282000b1521a2" , "AAC 762 SDN-6 7.62x51 Sound Suppressor "},
        {"5a3501acc4a282000d72293a" , "PMAG SR/LR GEN M3 20 7.62x51 20 rnd"},
        {"5a351711c4a282000b1521a4" , "X Products X-5 MP5 50-round 9x19 magazine"},
        {"5a37ca54c4a282000d72296a" , "30mm ring-mount made by JP"},
        {"5a38ed75c4a28232996e40c6" , "4-shot MC 20-01 Sb.3 20ga magazine for TOZ-106"},
        {"5a38ee51c4a282000c5a955c" , "2-shot MC 20-01 Sb.3 20ga magazine for TOZ-106"},
        {"5a38eecdc4a282329a73b512" , "TOZ 002 pistol grip for TOZ-106"},
        {"5a38ef1fc4a282000b1521f6" , "TOZ stock for TOZ-106"},
        {"5a398ab9c4a282000c5a9842" , "Ops Core Single Clamp Rail Adapter mount"},
        {"5a398b75c4a282000a51a266" , "Ops Core Picatinny Rail Adapter mount"},
        {"5a5f1ce64f39f90b401987bc" , "Zenit 2IRS Klesch flashlight + laser designator"},
        {"5a69a2ed8dc32e000d46d1f1" , "AS VAL Pistol grip-buffer tube"},
        {"5a6b585a8dc32e5a9c28b4f1" , "Thread protector for Alpha Wolf Glock barrels"},
        {"5a6b592c8dc32e00094b97bf" , "Glock thread protector produced by Double Diamond"},
        {"5a6b59a08dc32e000b452fb7" , "Glock thread protector produced by Salient Arms"},
        {"5a6b5b8a8dc32e001207faf3" , "Threaded barrel for Glock 9x19 manufactured by Lone Wolf."},
        {"5a6b5e468dc32e001207faf5" , "Threaded barrel for Glock 9x19 manufactured by Double Diamond"},
        {"5a6b5ed88dc32e000c52ec86" , "Threaded barrel for Glock 9x19 manufactured by Salient Arms"},
        {"5a6b5f868dc32e000a311389" , "Basic barrel for Glock 17 9x19"},
        {"5a6b60158dc32e000a31138b" , "Barrel with compensator for Glock 17 9x19"},
        {"5a6f5e048dc32e00094b97da" , "Glock 9x19 slide"},
        {"5a6f5f078dc32e00094b97dd" , "Glock 9x19 Viper Cut slide"},
        {"5a702d198dc32e000b452fc3" , "Glock Alpha Wolf slide"},
        {"5a7033908dc32e000a311392" , "Glock Alpha Wolf Custom slide"},
        {"5a70366c8dc32e001207fb06" , "Double Diamond flash hider"},
        {"5a7037338dc32e000d46d257" , "Decelerator 3 Port 9x19 Compensator"},
        {"5a705e128dc32e000d46d258" , "Alpha Wolf Bullnose 9x19 Compensator"},
        {"5a718b548dc32e000d46d262" , "Glock 9x19 magazine"},
        {"5a718da68dc32e000d46d264" , "Pmag GL9 polymer magazine"},
        {"5a718f958dc32e00094b97e7" , "SGMT Drum mag for Glock 9x19, 50 rounds capacity"},
        {"5a71e1868dc32e00094b97f3" , "Zev Tech sight mount cap"},
        {"5a71e22f8dc32e00094b97f4" , "Zev Tech Hex Gen3 slide"},
        {"5a71e4f48dc32e001207fb26" , "Glock Zev Tech Hex Spartan slide"},
        {"5a787ebcc5856700142fdd98" , "508mm barrel for M870 12ga with a fixed sight"},
        {"5a787f25c5856700186c4ab9" , "355mm barrel for M870 12ga"},
        {"5a787f7ac5856700177af660" , "508mm barrel for M870 12ga"},
        {"5a787fadc5856700155a6ca1" , "660mm vent rib barrel for M870 12ga"},
        {"5a787fdfc5856700142fdd9a" , "Cut off 325mm barrel for M870 12ga"},
        {"5a788031c585673f2b5c1c79" , "Fab Defence PR870 forestock"},
        {"5a788068c5856700137e4c8f" , "Magpul MOE M870 forestock"},
        {"5a788089c5856700142fdd9c" , "Speedfeed short M870 forestock"},
        {"5a7880d0c5856700142fdd9d" , "Remington SPS Polymer stock for M870"},
        {"5a78813bc5856700186c4abe" , "SGA stock for M870"},
        {"5a788169c5856700142fdd9e" , "Raptor grip for M870"},
        {"5a7882dcc5856700177af662" , "4-shell M870 12ga magazine cap"},
        {"5a78830bc5856700137e4c90" , "7-shell M870x7 12ga magazine"},
        {"5a78832ec5856700155a6ca3" , "10-shell M870x10 12ga magazine"},
        {"5a789261c5856700186c65d3" , "Mesa Tactical magazine clamp for M870"},
        {"5a7893c1c585673f2b5c374d" , "MTU-028SG rail for M870"},
        {"5a78948ec5856700177b1124" , "XS Short rail with Ghost ring for M870"},
        {"5a7ad0c451dfba0013379712" , "Carver Custom 4 Port 9x19 muzzle brake"},
        {"5a7ad1fb51dfba0013379715" , "Lone Wolf Compensator 9 9x19"},
        {"5a7ad2e851dfba0016153692" , "\"Big Stick\" 9x19 magazine for Glock 9x19"},
        {"5a7ad4af51dfba0013379717" , "Aimtech glock base"},
        {"5a7ad55551dfba0015068f42" , "Aimtech Tiger Shark "},
        {"5a7ad74e51dfba0015068f45" , "Fischer Development FD917 suppressor"},
        {"5a7afa25e899ef00135e31b0" , "Polymer80 PS9 Glock slide"},
        {"5a7b32a2e899ef00135e345a" , "Strike Industries G4 slide compensator 9x19"},
        {"5a7b483fe899ef0016170d15" , "Surefire XC1 tactical flashlight"},
        {"5a7b4900e899ef197b331a2a" , "UM Tactical UM3 Sight Mount"},
        {"5a7b4960e899ef197b331a2d" , "Pachmayr tactical rubber grip"},
        {"5a7c147ce899ef00150bd8b8" , "Muzzle brake Vendetta precision VP-09 5.56x45"},
        {"5a7dbfc1159bd40016548fde" , "Hera Arms CQR tactical grip"},
        {"5a800961159bd4315e3a1657" , "Glock Tactical GL21 flashlight with laser"},
        {"5a9548c9159bd400133e97b3" , "MP5 TL-99 Aluminum handguard"},
        {"5a957c3fa2750c00137fa5f7" , "XRSU47SU Tactical Handguard for AKS-74U"},
        {"5a966ec8a2750c00171b3f36" , "B&T 3x rail mount for MP5"},
        {"5a966f51a2750c00156aacf6" , "SAI-02 10-round 12x76 magazine for SOK-12 and compatible weapons"},
        {"5a9685b1a2750c0032157104" , "Glock 9x19 Moto Cut slide"},
        {"5a9d56c8a2750c0032157146" , "Strike industries TRAX 1 foregrip"},
        {"5a9d6d00a2750c5c985b5305" , "Strike industries keymod 4 inch guide"},
        {"5a9d6d13a2750c00164f6b03" , "Strike industries keymod 6 inch guide"},
        {"5a9d6d21a2750c00137fa649" , "Strike industries bridge guide"},
        {"5a9d6d34a2750c00141e07da" , "Strike industries TRAX 2"},
        {"5a9e81fba2750c00164f6b11" , "30-round SR3M.130 9x39 SR3M magazine"},
        {"5a9ea27ca2750c00137fa672" , "Spike tactical dynacomp 7.62x39 muzzle brake & compensator for AK "},
        {"5a9eb32da2750c00171b3f9c" , "Fab Defence GL Shock Stock"},
        {"5a9fb739a2750c003215717f" , "Rotor 43 9x19 muzzle brake"},
        {"5a9fbacda2750c00141e080f" , "Rotor 43 7.62x39 muzzle brake"},
        {"5a9fbb74a2750c0032157181" , "Rotor 43 .366TKM muzzle brake"},
        {"5a9fbb84a2750c00137fa685" , "Rotor 43 5.56x45 muzzle brake"},
        {"5a9fc7e6a2750c0032157184" , "B-3 mount combo"},
        {"5aa66a9be5b5b0214e506e89" , "34mm one piece magmount made by Nightforce"},
        {"5aa66c72e5b5b00016327c93" , "34mm one piece magmount made by Nightforce with a Multimount rail"},
        {"5aaa4194e5b5b055d06310a5" , "Pmag 30 AK74 GEN M3 5.45x39 magazine for AK and compatibles, 30-round capacity"},
        {"5aaa5dfee5b5b000140293d3" , "PMAG GEN M3 30 5.56x45 STANAG 30-round magazine"},
        {"5aaa5e60e5b5b000140293d6" , "PMAG GEN M3 10 5.56x45 STANAG 10-round magazine"},
        {"5aaf8a0be5b5b00015693243" , "M1A 20 round 7.62x51 magazine"},
        {"5aaf8e43e5b5b00015693246" , "M1A Socom 16 stock"},
        {"5aaf9d53e5b5b00015042a52" , "16\" barrel for a M1A 7.62x51 NATO"},
        {"5aafa1c2e5b5b00015042a56" , "Socom 16 7.62x51 muzzle brake & compensator for M1A"},
        {"5ab24ef9e5b5b00fe93c9209" , "M1A Socom 16 upper part"},
        {"5ab372a310e891001717f0d8" , "Troy S.A.S.S. Chassis stock for M14"},
        {"5ab3afb2d8ce87001660304d" , "Socom 16 7.62x51 muzzle brake & compensator for M1A"},
        {"5ab626e4d8ce87272e4c6e43" , "IzhMash metal stock for AKS-74 (6P21 Sb.5)"},
        {"5abcc328d8ce8700194394f3" , "Silencer APB 9x18PM"},
        {"5abcd472d8ce8700166032ae" , "Izhmash shoulder piece for AKMSN (6P4 Sb.1-19)"},
        {"5ac50c185acfc400163398d4" , "Polymer stock for AK-74M (6P34 Sb.15)"},
        {"5ac50da15acfc4001718d287" , "Izhmash AK-74M dust cover (6P34 0-1)"},
        {"5ac66bea5acfc43b321d4aec" , "30-round 7.62x39 magazine for AK-103 and compatible weapons"},
        {"5ac66c5d5acfc4001718d314" , "6L29 30-round 5.56x45 magazine for AK-101 and compatible weapons"},
        {"5ac72e615acfc43f67248aa0" , "Izhmash 5.56x45 AK-101 muzzlebrake & compensator"},
        {"5ac72e725acfc400180ae701" , "Izhmash 5.56x45 AK-102 muzzlebrake & compensator (6P44 0-20)"},
        {"5ac72e7d5acfc40016339a02" , "Izhmash 7.62x39 AK-103 muzzlebrake & compensator"},
        {"5ac72e895acfc43b321d4bd5" , "Izhmash 7.62x39 AK-104 muzzlebrake & compensator (6P46 0-20)"},
        {"5ac72e945acfc43f3b691116" , "Izhmash 5.45x39 AK-105 muzzlebrake & compensator (6P44 0-20)"},
        {"5ac7655e5acfc40016339a19" , "Izhmash 5.45x39 AK-74M muzzle brake & compensator (6P20 0-20)"},
        {"5ac78eaf5acfc4001926317a" , "AK74/AK100 PT Lock"},
        {"5addbac75acfc400194dbc56" , "22\" barrel for a M1A 7.62x51 NATO"},
        {"5addbb6e5acfc408fb1393fd" , "National Match 7.62x51 muzzle brake & compensator for M1A"},
        {"5addbb825acfc408fb139400" , "JP Enterprises tactical compensator 7.62x51 muzzle brake & compensator for M14"},
        {"5addbb945acfc4001a5fc44e" , "Good Iron 7.62x51 muzzle brake & compensator for M14"},
        {"5addbba15acfc400185c2854" , "Vortex DC 7.62x51 muzzle brake & compensator for M14"},
        {"5addbbb25acfc40015621bd9" , "Phantom 7.62x51 muzzle brake & compensator for M14"},
        {"5addbf175acfc408fb13965b" , "M1A Archangel stock"},
        {"5addbfbb5acfc400194dbcf7" , "M14 Ultimak M8 upper part"},
        {"5addbfd15acfc40015621bde" , "M14 Mini Scout mount"},
        {"5addbfe15acfc4001a5fc58b" , "Arms #18 mount  for M14"},
        {"5addbfef5acfc400185c2857" , "M14 UTG 4 point locking deluxe mount"},
        {"5addbffe5acfc4001714dfac" , "M14 DCSB"},
        {"5addc00b5acfc4001669f144" , "CASV 14 mount for M14"},
        {"5addc7005acfc4001669f275" , "M14 M14ALCS(MOD. 0) stock"},
        {"5addc7ac5acfc400194dbd90" , "M14 M14ALCS(MOD. 0) stock"},
        {"5addc7db5acfc4001669f279" , "M14ALCS(MOD. 0) pistol grip for M14"},
        {"5addcce35acfc4001a5fc635" , "M14 30 round 7.62x51 magazine"},
        {"5addccf45acfc400185c2989" , "X-14 M14 50 round 7.62x51 magazine"},
        {"5adf23995acfc400185c2aeb" , "MC 20-01 stock"},
        {"5ae089fb5acfc408fb13989b" , "Trophy"},
        {"5ae096d95acfc400185c2c81" , "Regular Mosin rifle stock"},
        {"5ae0973a5acfc4001562206c" , "Regular 4rnd magazine for Mosin rifle "},
        {"5ae09bff5acfc4001562219d" , "Regular 730mm Mosin barrel"},
        {"5ae30c9a5acfc408fb139a03" , "LMT Sopmod stock"},
        {"5ae30db85acfc408fb139a05" , "Colt M4 Length handguard for AR-15 and compatibles"},
        {"5ae30e795acfc408fb139a0b" , "Colt M4 Front sight"},
        {"5ae35b315acfc4001714e8b0" , "LEO stock adapter for M870"},
        {"5afd7ded5acfc40017541f5e" , "Tapco INTRAFUSE Stock for SKS"},
        {"5afd7e095acfc40017541f61" , "Tapco buffer tube"},
        {"5afd7e445acfc4001637e35a" , "TAPCO SAW-Style pistol grip for SKS INTRAFUSE Kit"},
        {"5b04473a5acfc40018632f70" , "Fab Defense UAS for AK"},
        {"5b057b4f5acfc4771e1bd3e9" , "SE-5 Express Grip"},
        {"5b07db875acfc40dc528a5f6" , "Skeletonized AR-15 pistol grip"},
        {"5b07dd285acfc4001754240d" , "LAS/TAC 2 tactical flashlight"},
        {"5b0800175acfc400153aebd4" , "F93 Pro Stock"},
        {"5b099a765acfc47a8607efe3" , "11\" barrel for SA-58 7.62x51"},
        {"5b099a9d5acfc47a8607efe7" , "DS Arms quad rail foregrip for SA-58"},
        {"5b099ac65acfc400186331e1" , "FAL/SA-58 7.62x51 20 rnd"},
        {"5b099b7d5acfc400186331e4" , " DS Arms \"3 prong trident\" 7.62x51 Flash hider for SA-58"},
        {"5b099b965acfc400186331e6" , "TAPCO SAW-Style black pistol grip for SA-58"},
        {"5b099bb25acfc400186331e8" , "DS Arms Extreme Duty dust cover for SA58"},
        {"5b099bf25acfc4001637e683" , "Buffer Tube adapter for SA-58"},
        {"5b0e794b5acfc47a877359b2" , "Zhukov-S for AK"},
        {"5b1fa9ea5acfc40018633c0a" , "Barrel with compensator for Glock 18C 9x19"},
        {"5b1faa0f5acfc40dc528aeb5" , "Glock 18C 9x19 slide"},
        {"5b1fb3e15acfc4001637f068" , "Bakelite 7.62x39 magazine for AK and compatibles, 40-round capacity"},
        {"5b1fd4e35acfc40018633c39" , "Izhmash 7.62x39 AK aluminium magazine for AK and compatibles, 10-round capacity"},
        {"5b222d335acfc4771e1be099" , "AKM/AK-74 PT Lock"},
        {"5b222d405acfc400153af4fe" , "Zenit PT-1 \"Klassika\" stock"},
        {"5b2240bf5acfc40dc528af69" , "Raptor charging handle for AR-15"},
        {"5b237e425acfc4771e1be0b6" , "Handguard with a gas block combo by TROY Industries for AK"},
        {"5b2389515acfc4771e1be0c0" , "30mm ring-mount AR- P.E.P.R. made by Burris"},
        {"5b2cfa535acfc432ff4db7a0" , "Handguard MK 10 for use with AR-15 and compatible"},
        {"5b30ac585acfc433000eb79c" , "Magpul MOE pistol grip for AK"},
        {"5b30bc165acfc40016387293" , "Alexander Arms 3 inch guide"},
        {"5b30bc285acfc47a8608615d" , "Alexander Arms 10 inch guide"},
        {"5b31163c5acfc400153b71cb" , "Sig Sauer mount for the sights of Romeo series."},
        {"5b363dd25acfc4001a598fd2" , "SilencerCo Salvo 12 sound suppressor"},
        {"5b363dea5acfc4771e1c5e7e" , "SilencerCo choke adapter for 12ga shotguns"},
        {"5b363e1b5acfc4771e1c5e80" , "SilencerCo Salvo 12 thread adapter"},
        {"5b39f8db5acfc40016387a1b" , "EMOD Stock"},
        {"5b39ffbd5acfc47a8773fb06" , "Rubber with finger grooves pistol grip for P226"},
        {"5b3a08b25acfc4001754880c" , "Bridge Sight Mount for P226"},
        {"5b3a16655acfc40016387a2a" , "Annihilator 7.62x39, 5.56x45 and 9mm flash hider for AR-15"},
        {"5b3a337e5acfc4704b4a19a0" , "Zenit 2U Klesch tactical flashlight"},
        {"5b3b6dc75acfc47a8773fb1e" , "Armasight universal base"},
        {"5b3b99265acfc4704b4a1afb" , "30mm rings made by Nightforce"},
        {"5b3baf8f5acfc40dc5296692" , "116mm 7.62x25 TT gilded barrel"},
        {"5b3cadf35acfc400194776a0" , "Fancy TT side grips"},
        {"5b3cbc235acfc4001863ac44" , "Vulcan MG scope eyecup"},
        {"5b3f7bf05acfc433000ecf6b" , "Kochetov Mount for Mosin rifle"},
        {"5b3f7c005acfc4704b4a1de8" , "PU 3.5x ring mount"},
        {"5b4736a986f774040571e998" , "Troy QARS 3.2 inch guide"},
        {"5b4736b986f77405cb415c10" , "Troy QARS 4.2 inch guide"},
        {"5b7be1125acfc4001876c0e5" , "16\" barrel for SA-58 7.62x51"},
        {"5b7be1265acfc400161d0798" , "21\" barrel for SA-58 7.62x51"},
        {"5b7be1ca5acfc400170e2d2f" , "DS Arms Quad Rail Full Length foregrip for SA-58"},
        {"5b7be2345acfc400196d524a" , "Aim sport Universal keymod foregrip for FAL"},
        {"5b7be4575acfc400161d0832" , "Vltor CASV 2 inch guide"},
        {"5b7be4645acfc400170e2dcc" , "Vltor CASV 4 inch guide"},
        {"5b7be46e5acfc400170e2dcf" , "Vltor CASV 5 inch guide"},
        {"5b7be47f5acfc400170e2dd2" , "Magpul M-LOK 2.5 inch guide"},
        {"5b7be4895acfc400170e2dd5" , "Magpul M-LOK 4.1 inch guide"},
        {"5b7bebc85acfc43bca706666" , "Aim sport Universal M-LOK foregrip for FAL"},
        {"5b7bed205acfc400161d08cc" , "Original Austrian foregrip for a FAL"},
        {"5b7bedd75acfc43d825283f9" , "Vltor CASV FAL foregrip for FAL"},
        {"5b7bee755acfc400196d5383" , "Vltor CASV FAS foregrip for FAL"},
        {"5b7bef1e5acfc43d82528402" , "FAL/SA-58 7.62x51 10 rnd"},
        {"5b7bef5d5acfc43bca7067a3" , "FAL/SA-58 7.62x51 30 rnd"},
        {"5b7bef9c5acfc43d102852ec" , "X-FAL FAL/SA-58 7.62x51 50 rnd magazine"},
        {"5b7c2d1d5acfc43d1028532a" , "FAL/SA-58 \"MMW\" 7.62x51 20 rnd plastic mag"},
        {"5b7d37845acfc400170e2f87" , "British FAL/L1A1 7.62x51 30 rnd magazine"},
        {"5b7d63b75acfc400170e2f8a" , "Magpul PRS 2 polymer stock for FAL"},
        {"5b7d63cf5acfc4001876c8df" , "DSA Folding stock for SA-58"},
        {"5b7d63de5acfc400170e2f8d" , "DSA SPR stock for SA-58"},
        {"5b7d64555acfc4001876c8e2" , "DSA BRS stock for SA-58"},
        {"5b7d645e5acfc400170e2f90" , "Polymer stock DSA humpback for SA-58"},
        {"5b7d671b5acfc43d82528ddd" , "DSA Belgian style foregrip for a FAL"},
        {"5b7d678a5acfc4001a5c4022" , "Regular \"DS Arms\" pistol grip for SA-58"},
        {"5b7d679f5acfc4001a5c4024" , "Fab AG FAL pistol grip for SA-58"},
        {"5b7d68af5acfc400170e30c3" , " DS Arms \"Austrian Style\" 7.62x51 muzzle brake for SA-58"},
        {"5b7d693d5acfc43bca706a3d" , "Compensator 2A \"X3\" 7.62x51 for AR-10"},
        {"5b7d6c105acfc40015109a5f" , "Regular dust cover for FAL"},
        {"5b800e9286f7747a8b04f3ff" , "Hexagon handguard for AK"},
        {"5b800ebc86f774394e230a90" , "Medium length rail for Hexagon"},
        {"5b800ed086f7747baf6e2f9e" , "Short length rail for Hexagon"},
        {"5b80242286f77429445e0b47" , "Hexagon handguard for AK(anodized red)"},
        {"5b84038986f774774913b0c1" , "Short length rail for Hexagon(Anodized Red)"},
        {"5b8403a086f7747ff856f4e2" , "Medium length rail for Hexagon(Anodized Red)"},
        {"5b86a0e586f7745b600ccb23" , "Bramit silencer for a Mosin rifle"},
        {"5ba264f6d4351e0034777d52" , "Standard MP7 20-round 4.6x30 magazine"},
        {"5ba2657ed4351e0035628ff2" , "Standard MP7 30-round 4.6x30 magazine"},
        {"5ba26586d4351e44f824b340" , "Standard MP7 40-round4.6x30 magazine"},
        {"5ba26acdd4351e003562908e" , "HK A1 4.6x30 Flash hider for MP7"},
        {"5ba26ae8d4351e00367f9bdb" , "B&T Rotex 2 4.6x30 silencer"},
        {"5ba36f85d4351e0085325c81" , "NSPU-M scope eyecup"},
        {"5bae13bad4351e00320204af" , "ProMag Archangel OPFOR PRS Mosin rifle stock"},
        {"5bae13ded4351e44f824bf38" , "7.62x54r ProMag OPFOR for Archangel Mosin rifle kit, 10-round capacity"},
        {"5bb20d53d4351e4502010a69" , "Upper receiver HK 416A5 5.56x45 for 416A5"},
        {"5bb20d92d4351e00853263eb" , "11\" barrel for 416A5 and compatible 5.56x45"},
        {"5bb20d9cd4351e00334c9d8a" , "14.5\" barrel for 416A5 and compatible 5.56x45"},
        {"5bb20da5d4351e0035629dbf" , "16.5\" barrel for 416A5 and compatible 5.56x45"},
        {"5bb20dadd4351e00367faeff" , "20\" barrel for 416A5 and compatible 5.56x45"},
        {"5bb20dbcd4351e44f824c04e" , "HK Extended latch Charging Handle"},
        {"5bb20dcad4351e3bac1212da" , "HK 416A5 Regular Low Profile Gas Block"},
        {"5bb20de5d4351e0035629e59" , "HK quadrail handguard for 416-compatible systems"},
        {"5bb20df1d4351e00347787d5" , "HK quadrail handguard with a flip-up sight for 416-compatible systems"},
        {"5bb20dfcd4351e00334c9e24" , "HK extended quadrail handguard for 416-compatible systems"},
        {"5bb20e0ed4351e3bac1212dc" , "HK Battle Grip with Beavertail pistol grip for AR-15 based systems"},
        {"5bb20e18d4351e00320205d5" , "HK \"Battle Grip\" pistol grip for AR-15 based systems"},
        {"5bb20e58d4351e00320205d7" , "HK \"Enhanced Tube\" buffer tube"},
        {"5bb20e70d4351e0035629f8f" , "HK Slim Line Stock"},
        {"5bbdb811d4351e45020113c7" , "Aim Sports \"Tri-Rail\" rail for Mosin rifle"},
        {"5bbdb83fd4351e44f824c44b" , "Tacfire Tanker style muzzle brake for Mosin rifle"},
        {"5bbdb870d4351e00367fb67d" , "ATI Monte Carlo Mosin rifle stock"},
        {"5bbdb8bdd4351e4502011460" , "Muzzle brake Odin Works Atlas-7 7.62x51 for AR-10"},
        {"5bbde409d4351e003562b036" , "Recoil pad from Aim Sports for Mosin rifle"},
        {"5bbde41ed4351e003562b038" , "Tacfire pistol grip for Mosin rifle"},
        {"5bc5a351d4351e003477a414" , "Texas Precision Products muzzle brake for Mosin rifle"},
        {"5bc5a35cd4351e450201232f" , "Witt Machine muzzle brake for Mosin rifle"},
        {"5bc5a372d4351e44f824d17f" , "Aim Sports MNG rail for Mosin rifle"},
        {"5bcf0213d4351e0085327c17" , "Regular stock for HK MP7A1"},
        {"5bd704e7209c4d00d7167c31" , "Regular stock for HK MP7A2"},
        {"5bed61680db834001d2c45ab" , "30-round 5.45x39 magazine for AK-12 and compatibles"},
        {"5bed625c0db834001c062946" , "95-round 5.45x39 magazine for RPK-16 and compatibles"},
        {"5beec1bd0db834001e6006f3" , "15\" barrel for RPK-16 and compatible 5.45x39"},
        {"5beec2820db834001b095426" , "22\" barrel for RPK-16 and compatible 5.45x39"},
        {"5beec3420db834001b095429" , "Izhmash 5.45x39 RPK-16 muzzle brake & compensator"},
        {"5beec3e30db8340019619424" , "Izhmash RPK-16 regular handguard"},
        {"5beec8b20db834001961942a" , "Izhmash RPK-16 buffer tube"},
        {"5beec8c20db834001d2c465c" , "Izhmash AK-12 regular stock"},
        {"5beec8ea0db834001a6f9dbf" , "Izhmash AK-12 regular pistol grip"},
        {"5beec91a0db834001961942d" , "Izhmash regular dust cover for RPK-16"},
        {"5beecbb80db834001d2c465e" , "Izhmash RPK-16 rail"},
        {"5bfd35380db83400232fe5cc" , "Infantry Mosin rifle stock"},
        {"5bfd36290db834001966869a" , "Sawn off Mosin rifle sniper stock"},
        {"5bfd36ad0db834001c38ef66" , "Sawn off regular Mosin rifle stock"},
        {"5bfd37c80db834001d23e842" , "Mosin rifle sniper carbine stock"},
        {"5bfd384c0db834001a6691d3" , "Mosin carbine stock"},
        {"5bfd4cbe0db834001b73449f" , "Regular 514mm Mosin carbine barrel"},
        {"5bfd4cc90db834001d23e846" , "Sawn off 200mm Mosin barrel"},
        {"5bfd4cd60db834001c38f095" , "Sawn off 220mm Mosin barrel"},
        {"5bfe7fb30db8340018089fed" , "Stock adapter Tactica Tula 12003 for MP-133/153"},
        {"5bfe86a20db834001d23e8f7" , "Fab Defence AGR-870 pistol grip for Remington-870"},
        {"5bfe86bd0db83400232fe959" , "AGR-870 protection cap"},
        {"5bfe86df0db834001b734685" , "Fab Defence GLR-16-S Stock"},
        {"5bfe89510db834001808a127" , "Fab Defence buffer tube for AGR-870"},
        {"5bfea7ad0db834001c38f1ee" , "5-round .308 M700 magazine"},
        {"5bfeaa0f0db834001b734927" , "10-round .308 M700 magazine"},
        {"5bfeb32b0db834001a6694d9" , "Hogue \"Overmolded ghillie\" stock for Remington Model 700"},
        {"5bfebc250db834001a6694e1" , "26\" barrel for a Remington M700 7.62x51 NATO"},
        {"5bfebc320db8340019668d79" , "20\" barrel for a Remington M700 7.62x51 NATO"},
        {"5bfebc530db834001d23eb65" , "Weaver extended multi-slot base for Remington model 700"},
        {"5bfebc5e0db834001a6694e5" , "30mm ring-mount Remington integral for model 700 rifles"},
        {"5bffcf7a0db83400232fea79" , "PM-Laser TT-206 side grips with LAM"},
        {"5bffd7ed0db834001d23ebf9" , "PM-Laser DTK-TT muzzle brake for TT pistol"},
        {"5bffe7c50db834001d23ece1" , "P226 Axelson tactical Mk.25 pistol slide"},
        {"5bffec120db834001c38f5fa" , "Axelson Tacical MK.25 pistol grip for P226"},
        {"5bffef760db8340019668fe4" , "Hogue Chain link pistol grip for P226"},
        {"5c0000c00db834001a6697fc" , "3 Lug threaded protector"},
        {"5c0006470db834001a6697fe" , "Emperor scorpion Sig Sauer pistol grip for P226"},
        {"5c00076d0db834001d23ee1f" , "Wooden Sig Sauer Elite pistol grip for P226"},
        {"5c0009510db834001966907f" , "P226 Sig Stainless elite pistol slide"},
        {"5c0102aa0db834001b734ba1" , "Remington RAHG 2 inch guide"},
        {"5c0102b20db834001d23eebc" , "Remington RAHG 4 inch guide"},
        {"5c010a700db834001d23ef5d" , "P226 Sig Emperor scorpion pistol slide"},
        {"5c0111ab0db834001966914d" , "ME Cylinder muzzle adapter 12 ga"},
        {"5c0125fc0db834001a669aa3" , "P226 Sig Legion full size pistol slide"},
        {"5c05413a0db834001c390617" , "HK Steel Maritime 5.56x45 STANAG 30-round magazine"},
        {"5c0548ae0db834001966a3c2" , "Arsenal CWP 30-round 5.56x45 magazine for SLR-106 and compatible weapons"},
        {"5c064c400db834001d23f468" , "La Rue Tactical picatinny riser QD LT-101 mount"},
        {"5c06595c0db834001a66af6c" , "LA-5 tactical device"},
        {"5c0672ed0db834001b7353f3" , "PUFGUN SG-919 30 30-round 9x19 magazine for PP-19-01"},
        {"5c0673fb0db8340023300271" , "PUFGUN SG-919 20 20-round 9x19 magazine for  PP-19-01"},
        {"5c0684e50db834002a12585a" , "Hogue like TT rubber grips"},
        {"5c0695860db834001b735461" , "PNV-10T dovetail adapter"},
        {"5c079ec50db834001966a706" , "Razor Arms TT rubber grips"},
        {"5c079ed60db834001a66b372" , "DLP \"Tactical Precision\" LAM Module for TT Pistol"},
        {"5c07a8770db8340023300450" , "Noveske Gen.3 5.56x45 Upper receiver for AR systems"},
        {"5c07c5ed0db834001b73571c" , "HK Noveske style muzzle brake & compensator for MP-5"},
        {"5c07c9660db834001a66b588" , "HK End Cap Stock for MP5"},
        {"5c0e2f26d174af02a9625114" , "Upper receiver ADAR 2-15 5.56x45 for 2-15 assault rifle"},
        {"5c0e2f5cd174af02a012cfc9" , "ADAR 2-15 wooden stock for AR-15 and compatibles"},
        {"5c0e2f94d174af029f650d56" , "406mm Molot barrel for AR-15 and compatible 5.56x45"},
        {"5c0e2ff6d174af02a1659d4a" , "ADAR 2-15 wooden stock"},
        {"5c0faeddd174af02a962601f" , "ADAR buffer tube"},
        {"5c0faf68d174af02a96260b8" , "ADAR 2-15 charging handle for AR-15"},
        {"5c0fafb6d174af02a96260ba" , "ADAR 2-15.56x45 Flashhider"},
        {"5c11046cd174af02a012e42b" , "Wilcox Interface for PVS-7"},
        {"5c17664f2e2216398b5a7e3c" , "VLTOR CMRD Keymod handguard for AK"},
        {"5c1bc4812e22164bef5cfde7" , "Zenit RK-0 Foregrip"},
        {"5c1bc5612e221602b5429350" , "Zenit RK-1 Foregrip"},
        {"5c1bc5af2e221602b412949b" , "Zenit RK-2 Foregrip"},
        {"5c1bc5fb2e221602b1779b32" , "Zenit RK-4 Foregrip"},
        {"5c1bc7432e221602b412949d" , "Zenit RK-5 Foregrip"},
        {"5c1bc7752e221602b1779b34" , "Zenit RK-6 Foregrip"},
        {"5c1cd46f2e22164bef5cfedb" , "Zenit RK-1 Foregrip on B-25U mount"},
        {"5c1cdd302e221602b3137250" , "Compact mount for sights"},
        {"5c471b5d2e221602b21d4e14" , "Polymer stock for SVDS"},
        {"5c471bd12e221602b4129c3a" , "Izhmash SVDS dust cover"},
        {"5c471be12e221602b66cd9ac" , "Izhmash SVDS pistol grip"},
        {"5c471bfc2e221602b21d4e17" , "Izhmash 7.62x54 SVDS muzzlebrake & compensator"},
        {"5c471c2d2e22164bef5d077f" , "SVDS Upper Band"},
        {"5c471c442e221602b542a6f8" , "10-round SVD 7.62x54 magazine"},
        {"5c471c6c2e221602b66cd9ae" , "Polymer SVDS handguard"},
        {"5c471c842e221615214259b5" , "SVDS Gas tube"},
        {"5c471cb32e221602b177afaa" , "22\" barrel for a SVDS 7.62x54"},
        {"5c48a14f2e2216152006edd7" , "Desert Tech foregrip for MDR"},
        {"5c48a2852e221602b21d5923" , "406mm barrel for MDR and compatible 5.56x45"},
        {"5c48a2a42e221602b66d1e07" , "Desert Tech 5.56x45 Flash hider"},
        {"5c48a2c22e221602b313fb6c" , "Desert Tech pistol grip for MDR"},
        {"5c4ee3d62e2216152006f302" , "SRVV \"Mk.2.0\" compensator 7.62x54 for SV-98"},
        {"5c4eec9b2e2216398b5aaba2" , "Thread adapter 7.62x54 for SV-98"},
        {"5c4eecc32e221602b412b440" , "Regular SV-98 7.62x54 silencer"},
        {"5c4eecde2e221602b3140418" , "Heat shield for SV-98 silencer"},
        {"5c5039be2e221602b177c9ff" , "VPO-101 Gas tube"},
        {"5c503ac82e221602b21d6e9a" , "7.62x51 metal magazine for VPO-101 and compatibles, 5-round capacity"},
        {"5c503ad32e2216398b5aada2" , "7.62x51 metal magazine for VPO-101 and compatibles, 10-round capacity"},
        {"5c503af12e221602b177ca02" , "Regular VPO-101 \"Vepr Hunter\" stock"},
        {"5c503d0a2e221602b542b7ef" , "Molot VPO-101 dust cover"},
        {"5c5952732e2216398b5abda2" , "Zenit Perst-3 tactical device"},
        {"5c59529a2e221602b177d160" , "Lancer OEM 14 inch M-LOK foregrip for MPX"},
        {"5c5970672e221602b21d7855" , "ProMag AALVX 35 7.62x39 35-round SKS magazine."},
        {"5c5db5852e2216003a0fe71a" , "4.5\" 9x19 barrel for MPX"},
        {"5c5db5962e2216000e5e46eb" , "6.5\" 9x19 barrel for MPX"},
        {"5c5db5b82e2216003a0fe71d" , "10.5\" 9x19 barrel for MPX"},
        {"5c5db5c62e22160012542255" , "14\" 9x19 barrel for MPX"},
        {"5c5db5f22e2216000e5e47e8" , "Midwest 4.5 inch M-LOK foregrip for MPX"},
        {"5c5db5fc2e2216000f1b2842" , "Midwest 6.5 inch M-LOK foregrip for MPX"},
        {"5c5db6302e2216000e5e47f0" , "Midwest 10.5 inch M-LOK foregrip for MPX"},
        {"5c5db63a2e2216000f1b284a" , "Midwest 14 inch M-LOK foregrip for MPX"},
        {"5c5db6552e2216001026119d" , "Standard MPX 20-round 9x19 magazine"},
        {"5c5db6652e221600113fba51" , "MPX with TTI Base pad +11 41-round 9x19 magazine"},
        {"5c5db6742e2216000f1b2852" , "F5 MPX Drum mag 50-round 9x19 magazine"},
        {"5c5db6b32e221600102611a0" , "Geissele \"SCH\" charging handle for MPX"},
        {"5c5db6ee2e221600113fba54" , "Maxim Defence CQB collapsing/telescoping MCX/MPX stock"},
        {"5c5db6f82e2216003a0fe914" , "PMM \"ULSS\" foldable MCX/MPX stock"},
        {"5c6161fb2e221600113fbde5" , "5-shot MC 20-01 Sb.3 20ga magazine for TOZ-106"},
        {"5c6162682e22160010261a2b" , "Dovetail mount for TOZ-106"},
        {"5c61627a2e22160012542c55" , "TOZ-106 scope mount"},
        {"5c6165902e22160010261b28" , "Sig SRD 9 9x19mm sound suppressor"},
        {"5c6175362e221600133e3b94" , "ProMag AK-A-16 73-round 7.62x39 magazine for AKM and compatibles"},
        {"5c617a5f2e2216000f1e81b3" , "Zenit B-10 AK Handguard"},
        {"5c61a40d2e2216001403158d" , "B-13 rail platform"},
        {"5c6592372e221600133e47d7" , "100-round MAG5-100 5.56x45 STANAG magazine"},
        {"5c6beec32e221601da3578f2" , "TJ Custom 9x19 Compensator"},
        {"5c6bf4aa2e2216001219b0ae" , "US Palm pistol grip for AK"},
        {"5c6c2c9c2e2216000f2002e4" , "Troy Industries 13\" M-LOK foregrip for 416A5"},
        {"5c6d10e82e221601da357b07" , "HK MRS 14\" keymod foregrip for 416A5"},
        {"5c6d10fa2e221600106f3f23" , "Midwest 9\" M-LOK foregrip for 416A5"},
        {"5c6d11072e2216000e69d2e4" , "Midwest 13.5\" M-LOK foregrip for 416A5"},
        {"5c6d11152e2216000f2003e7" , "Strike Industries CRUX 15\" M-LOK foregrip for 416A5"},
        {"5c6d42cb2e2216000e69d7d1" , "HK Polymer mag 30 5.56x45 STANAG 30-round magazine"},
        {"5c6d450c2e221600114c997d" , "HK PM Gen.2 5.56x45 STANAG 30-round magazine"},
        {"5c6d46132e221601da357d56" , "TROY Battlemag 5.56x45 STANAG 30-round magazine"},
        {"5c6d5d8b2e221644fc630b39" , "Stngr Vypr 10\" M-LOK foregrip for AR15"},
        {"5c6d710d2e22165df16b81e7" , "Surefire WarComp 5.56x45 Flash hider for AR-15"},
        {"5c6d7b3d2e221600114c9b7d" , "HK Grip V.2 pistol grip for AR-15 based systems"},
        {"5c6d85e02e22165df16b81f4" , "10.6\" barrel for 416A5 and compatible 5.56x45"},
        {"5c78f2492e221600114c9f04" , "SAI 14.5\" QD Rail foregrip for AR15"},
        {"5c78f2612e221600114c9f0d" , "SAI 10\" QD Rail foregrip for AR15"},
        {"5c78f26f2e221601da3581d1" , "Magpul MOE SL mid length M-LOK foregrip for AR15"},
        {"5c78f2792e221600106f4683" , "Magpul MOE SL carbine length M-LOK foregrip for AR-15"},
        {"5c78f2882e22165df16b832e" , "SAI Jail Break 5.56x45 for AR-15"},
        {"5c791e872e2216001219c40a" , "SI \"Cobra tactical\" tactical grip"},
        {"5c793fb92e221644f31bfb64" , "SI Advanced receiver extension buffer tube"},
        {"5c793fc42e221600114ca25d" , "SI Advanced receiver extension buffer tube (anodized red)"},
        {"5c793fde2e221601da358614" , "SI Viper Mod.1 Stock"},
        {"5c7951452e221644f31bfd5c" , "Venom Antidote muzzle brake & compensator for AK "},
        {"5c7954d52e221600106f4cc7" , "Direct Thread Mount adapter for Gemtech ONE."},
        {"5c7955c22e221644f31bfd5e" , "Gemtech ONE 7.62x51 Sound Suppressor "},
        {"5c7d55f52e221644f31bff6a" , "Aimpoint LRP mount for COMP M4 sights."},
        {"5c7d560b2e22160bc12c6139" , "Standard Spacer for Aimpont sight"},
        {"5c7e5f112e221600106f4ede" , "AAC Blackout 51T 5.56x45 flash-hider"},
        {"5c7e8fab2e22165df16b889b" , "AAC Illusion 9 9x19mm silencer"},
        {"5c7fb51d2e2216001219ce11" , "Surefire SF3P 5.56x45 Flash hider for AR-15"},
        {"5c7fc87d2e221644f31c0298" , "BCM MOD.3 Tactical grip"},
        {"5c86592b2e2216000e69e77c" , "34mm one piece magmount made by I-E-A Mil Optics"},
        {"5c878e9d2e2216000f201903" , "Lantac Dragon 7.62x51 muzzle brake"},
        {"5c878ebb2e2216001219d48a" , "Lantac Dragon 7.62x39 muzzle brake & compensator for AK "},
        {"5c87a07c2e2216001219d4a2" , "HK E1 Stock for AR-15 and compatible"},
        {"5c87ca002e221600114cb150" , "KAC Vertical pistol grip"},
        {"5c88f24b2e22160bc12c69a6" , "20-round SVD 7.62x54 magazine"},
        {"5c90c3622e221601da359851" , "B-13V rail platform above reciever \"Classic\""},
        {"5c920e902e221644f31c3c99" , "P226 Extended magazine 9x19"},
        {"5c99f3592e221644fc633070" , "Custom cut mosin stock for TOZ-106"},
        {"5c9a07572e221644f31c4b32" , "Magpul Zhukov-U HAND GUARD (Black) for AK"},
        {"5c9a1c3a2e2216000e69fb6a" , "Magpul Zhukov-U HAND GUARD (FDE) for AK"},
        {"5c9a1c422e221600106f69f0" , "Magpul Zhukov-U HAND GUARD (Plum) for AK"},
        {"5c9a25172e2216000f20314e" , "Daniel Defence RIS II 12.25 foregrip for AR-15-compatible systems"},
        {"5c9a26332e2216001219ea70" , "Daniel Defence FDE RIS II FSP 9.5 foregrip for AR-15-compatible systems"},
        {"5cadc1c6ae9215000f2775a4" , "Threaded barrel for M9A3 9x19"},
        {"5cadc2e0ae9215051e1c21e7" , "M9A3 9x19 17-round magazine"},
        {"5cadc390ae921500126a77f1" , "M9A3 thread protection cap"},
        {"5cadc431ae921500113bb8d5" , "Polymer pistol grip for M9A3"},
        {"5cadc55cae921500103bb3be" , "M9A3 9x19 pistol slide"},
        {"5caf1041ae92157c28402e3f" , "12.7x55 magazine for ASh-12, 10-round capacity"},
        {"5caf1109ae9215753c44119f" , "12.7x55 magazine for ASh-12, 20-round capacity"},
        {"5caf17c9ae92150b30006be1" , "ASh-12 regular muzzle brake 12.7x55"},
        {"5caf187cae92157c28402e43" , "ASh-12 12.7x55 tactical suppressor"},
        {"5cbda392ae92155f3c17c39f" , "Polymer AK-100 series foregrip"},
        {"5cbda9f4ae9215000e5b9bfc" , "Polymer AK-74 foregrip (6P20 Sb.9) Plum"},
        {"5cbdaf89ae9215000e5b9c94" , "30-round 6L23 Plum 5.45x39 magazine for AK-74 and compatibles"},
        {"5cbdb1b0ae9215000d50e105" , "Izhmash polymer Plum AK-74 stock (6P20 Sb.7)"},
        {"5cbdc23eae9215001136a407" , "Molot magazine for AK and compatibles, 75-round capacity"},
        {"5cc6ea78e4a949000e1ea3c1" , "FN charge handle for P90"},
        {"5cc6ea85e4a949000e1ea3c3" , "K&M The Handler charge handle for P90"},
        {"5cc70093e4a949033c734312" , "FN magazine for P90, 50-round capacity"},
        {"5cc700b9e4a949000f0f0f25" , "FN P90 stock"},
        {"5cc700cae4a949035e43ba72" , "FN Butt pad for P90"},
        {"5cc700d4e4a949000f0f0f28" , "Damage Industries Butt-pad for P90"},
        {"5cc700ede4a949033c734315" , "FN EFFEN 90 Upper receiver for P90"},
        {"5cc70102e4a949035e43ba74" , "FN Upper receiver for P90"},
        {"5cc7012ae4a949001252b43e" , "FN EFFEN 90 rail"},
        {"5cc70146e4a949000d73bf6b" , "FN side rail for regular P90 upper receiver"},
        {"5cc7015ae4a949001152b4c6" , "FN top rail for regular P90 upper receiver"},
        {"5cc701aae4a949000e1ea45c" , "10.5\" barrel for P90 5.7x28"},
        {"5cc701d7e4a94900100ac4e7" , "16\" barrel for P90 5.7x28"},
        {"5cc82796e24e8d000f5859a8" , "FN P90 5.7x28 flash hider"},
        {"5cc9a96cd7f00c011c04e04a" , "SRVV 5.45x39 AK-74 muzzle brake"},
        {"5cc9ad73d7f00c000e2579d4" , "SRVV 7.62x39 AK muzzle brake & compensator"},
        {"5cc9b815d7f00c000e2579d6" , "TROY Claymore 5.56x45 muzzle brake for AR-15"},
        {"5cc9bcaed7f00c011c04e179" , "Hera Arms HG-15 pistol grip for AR-15 based systems"},
        {"5cc9c20cd7f00c001336c65d" , "NcSTAR Tactical blue laser LAM-Module"},
        {"5cda9bcfd7f00c0c0b53e900" , "ASh-12 Vertical pistol grip"},
        {"5cdaa99dd7f00c002412d0b2" , "Polymer ASh-12 foregrip"},
        {"5cdd7685d7f00c000f260ed2" , "Muzzle brake Keeno Arms SHREWD 7.62x51 for AR-10"},
        {"5cdd7693d7f00c0010373aa5" , "Muzzle brake Precision Armament M-11 7.62x51 for AR-10"},
        {"5cde739cd7f00c0010373bd3" , "M700 MOD X Gen.3 stock"},
        {"5cde77a9d7f00c000f261009" , "Buffer tube side folder adapter for M700"},
        {"5cde7afdd7f00c000d36b89d" , "A*B Arms MOD X Gen.3 keymod handguard for M700"},
        {"5cde7b43d7f00c000d36b93e" , "A*B Arms MOD X mount for M700"},
        {"5cdeac22d7f00c000f26168f" , "Magpul PRO 700 chassis"},
        {"5cdeac42d7f00c000d36ba73" , "PRO 700 folding stock"},
        {"5cdeac5cd7f00c000f261694" , "Magpul Pistol Grip for Pro 700 Kit"},
        {"5cdeaca5d7f00c00b61c4b70" , "Magpul inline mount for PRO 700 chassis"},
        {"5ce69cbad7f00c00b61c5098" , "Magpul PMAG .308 AC 5-round M700 magazine"},
        {"5cebec00d7f00c065c53522a" , "FN Attenuator 5.7x28 silencer"},
        {"5cebec10d7f00c065703d185" , "FN PS90 stock"},
        {"5cf12a15d7f00c05464b293f" , "Promag AA-70 20-round .308 M700 magazine"},
        {"5cf13123d7f00c1085616a50" , "Promag Archangel polymer stock for M700"},
        {"5cf4e3f3d7f00c06595bc7f0" , "5.45 Design \"Aggressor\" handguard for AK"},
        {"5cf4fb76d7f00c065703d3ac" , "RTM Pillau Tactical grip"},
        {"5cf50850d7f00c056e24104c" , "SI Enhanced pistol grip for AK"},
        {"5cf508bfd7f00c056e24104e" , "SI Enhanced pistol grip for AK FDE"},
        {"5cf50fc5d7f00c056c53f83c" , "CAA AKTS AK-74 Buffer Tube for AK and compatible"},
        {"5cf518cfd7f00c065b422214" , "CAA AKTS AK-74 Buffer Tube for AK and compatible"},
        {"5cf54404d7f00c108840b2ef" , "KGB MG-47 pistol grip for AK"},
        {"5cf639aad7f00c065703d455" , "USP-1 scope eyecup"},
        {"5cf656f2d7f00c06585fb6eb" , "VS-24 Handguard with a VS-33c gas block combo for AK"},
        {"5cf67a1bd7f00c06585fb6f3" , "Weapon Tuning Mosin rifle tread adapter"},
        {"5cf67cadd7f00c065a5abab7" , "Weapon Tuning SKS tread adapter"},
        {"5cf6935bd7f00c06585fb791" , "Carbine brake for SIG MPX by TACCOM"},
        {"5cf6937cd7f00c056c53fb39" , "Bulletec ST-6012 5.56x45 Flash hider for AR-15"},
        {"5cf78496d7f00c065703d6ca" , "Direct Thread adapter for the Lantac Blast mitigation device."},
        {"5cf78720d7f00c06595bc93e" , "Lantac \"Blast mitigation device\" 7.62x51"},
        {"5cf79389d7f00c10941a0c4d" , "Custom Mosin rifle thread adapter"},
        {"5cf79599d7f00c10875d9212" , "Tiger Rock Mosin rifle tread adapter"},
        {"5cf7acfcd7f00c1084477cf2" , "FN Upper receiver for PS90"},
        {"5cf8f3b0d7f00c00217872ef" , "MaxRounds Powermag 20-round 12/76 magazine for SOK-12 and compatible weapons"},
        {"5cfe8010d7ad1a59283b14c6" , "X-47 AK 7.62x39 50 rnd magazine"},
        {"5cff9e5ed7ad1a09407397d4" , "Daniel Defense Wave Muzzle Brake 5.56x45"},
        {"5cff9e84d7ad1a049e54ed55" , "Daniel Defence Wave QD Sound Suppressor "},
        {"5cffa483d7ad1a049e54ef1c" , "100 rounds belt"},
        {"5d00e0cbd7ad1a6c6566a42d" , "Strike Industries Viper carbine length M-LOK foregrip for AR-15"},
        {"5d00ec68d7ad1a04a067e5be" , "JP Enterprises Gas System-5b"},
        {"5d00ede1d7ad1a0940739a76" , "Noveske SWS N6 10.5 inch foregrip for AR-10-compatible systems"},
        {"5d00ef6dd7ad1a0940739b16" , "Noveske SWS N6 Split handguard for AR-10-compatible systems"},
        {"5d00f63bd7ad1a59283b1c1e" , "Strike Industries Viper carbine length M-LOK foregrip (FDE) for AR-15"},
        {"5d010d1cd7ad1a59283b1ce7" , "CAA HX-5 MP5 handguard"},
        {"5d0236dad7ad1a0940739d29" , "Fab Defence UAS Stock for SKS"},
        {"5d023784d7ad1a049d4aa7f2" , "Fab Defence AG-58 pistol grip for VZ-58"},
        {"5d024f5cd7ad1a04a067e91a" , "Arbalet Patriot K+W mount"},
        {"5d025cc1d7ad1a53845279ef" , "HK Ergo PSG-1 style pistol grip for AR-15 based systems"},
        {"5d02676dd7ad1a049e54f6dc" , "Nordic Corvette 5.56x45 compensator for AR-15"},
        {"5d02677ad7ad1a04a15c0f95" , "Nordic Corvette 7.62x51 muzzle brake for AR-10"},
        {"5d026791d7ad1a04a067ea63" , "Fortis Red Brake 7.62x51 muzzle brake for AR-10"},
        {"5d0a29ead7ad1a0026013f27" , "KMZ 1P59 Dovetail mount"},
        {"5d0a29fed7ad1a002769ad08" , "KMZ 1P69 Weaver mount"},
        {"5d0b5cd3d7ad1a3fe32ad263" , "1P59 scope eyecup"},
        {"5d10b49bd7ad1a1a560708b0" , "AN/PEQ-2 tactical device"},
        {"5d120a10d7ad1a4e1026ba85" , "Double Star Ace Socom gen.4 stock for AR-15"},
        {"5d120a28d7ad1a1c8962e295" , "Double Star recoil pad 0.5 for ACE stock series"},
        {"5d122e7bd7ad1a07102d6d7f" , "URX 3.1 10.75\" handguard for AR15"},
        {"5d123102d7ad1a004e475fe5" , "URX 3 8\" handguard for AR15"},
        {"5d123a3cd7ad1a004e476058" , "KAC short panel for URX 3/3.1"},
        {"5d123b70d7ad1a0ee35e0754" , "KAC long panel for URX 3/3.1"},
        {"5d123b7dd7ad1a004f01b262" , "KAC stopper panel for URX 3/3.1"},
        {"5d124c01d7ad1a115c7d59fb" , "KAC short panel for URX 3/3.1 FDE"},
        {"5d124c0ed7ad1a10d168dd9b" , "KAC long panel for URX 3/3.1 FDE"},
        {"5d124c1ad7ad1a12227c53a7" , "KAC stopper panel for URX 3/3.1 FDE"},
        {"5d133067d7ad1a33013f95b4" , "KAC URX 3 inch guide"},
        {"5d1340b3d7ad1a0b52682ed7" , "PMAG GEN M3 30 5.56x45 STANAG 30-round magazine"},
        {"5d1340bdd7ad1a0e8d245aab" , "40-round PMAG GEN M3 FDE 40 5.56x45 STANAG magazine"},
        {"5d1340cad7ad1a0b0b249869" , "PMAG GEN M3 FDE W 30 5.56x45 STANAG 30-round magazine"},
        {"5d135e83d7ad1a21b83f42d8" , "Magpul CTR Carbine stock"},
        {"5d135ecbd7ad1a21c176542e" , "Magpul CTR Carbine stock FDE"},
        {"5d15ce51d7ad1a1eff619092" , "Alfa Arms Goliaf AKS-74U Handguard"},
        {"5d15cf3bd7ad1a67e71518b2" , "Magpul MOE AR-15 pistol grip (FDE)"},
        {"5d19cd96d7ad1a4a992c9f52" , "PTR Tri-Rail MP5 handguard"},
        {"5d1b198cd7ad1a604869ad72" , "TDI AKM-L handguard for AK"},
        {"5d1c702ad7ad1a632267f429" , "Fab Defence GLR-17 Stock for Glock and compatible"},
        {"5d1f819086f7744b355c219b" , "Daniel Defense Wave Muzzle Brake 7.62x51"},
        {"5d2369418abbc306c62e0c80" , "Steiner Dbal PL tactical flashlight"},
        {"5d25a4a98abbc30b917421a4" , "5-round .308 AICS M700 magazine"},
        {"5d25a6538abbc306c62e630d" , "10-round .308 AICS M700 magazine"},
        {"5d25a6a48abbc306c62e6310" , "12-round .308 MDT AICS M700 magazine"},
        {"5d25a7b88abbc3054f3e60bc" , "Magpul PMAG .308 AC 10-round M700 magazine"},
        {"5d25af8f8abbc3055079fec5" , "Promag AA-70 10-round .308 M700 magazine"},
        {"5d25d0ac8abbc3054f3e61f7" , "AT AICS polymer stock for M700"},
        {"5d2702e88abbc31ed91efc44" , "26\" stainless steel barrel for a Remington M700 7.62x51 NATO"},
        {"5d2703038abbc3105103d94c" , "20\" stainless steel barrel for a Remington M700 7.62x51 NATO"},
        {"5d270b3c8abbc3105335cfb8" , "M700 thread protection cap"},
        {"5d270ca28abbc31ee25ee821" , "M700 thread protection cap"},
        {"5d2c76ed48f03532f2136169" , "AKademia Bastion dust cover for AK"},
        {"5d2c770c48f0354b4a07c100" , "Fab Defence PDC dust cover for AK-74"},
        {"5d2c772c48f0355d95672c25" , "TWS Dog leg rail dust cover for AK"},
        {"5d2c829448f0353a5c7d6674" , "Wooden CAF WASR 10-63 handguard"},
        {"5d2f213448f0355009199284" , "Standard MP5 20-round 9x19 magazine"},
        {"5d2f259b48f0355a844acd74" , "MP5k Polymer handguard"},
        {"5d2f25bc48f03502573e5d85" , "HK End Cap Stock for MP5 Kurz"},
        {"5d2f261548f03576f500e7b7" , "HK MP5 Kurz Upper receiver"},
        {"5d2f2d5748f03572ec0c0139" , "MP5 Kurz Cocking Handle"},
        {"5d3eb44aa4b93650d64e4979" , "Five-seveN MK2 pistol slide"},
        {"5d3eb59ea4b9361c284bb4b2" , "Threaded barrel for Five-seveN 5.7x28"},
        {"5d3eb5b6a4b9361eab311902" , "Barrel for Five-seveN 5.7x28"},
        {"5d3eb5eca4b9363b1f22f8e4" , "Five-seveN 20-Round 5.7x28 magazine"},
        {"5d3ef698a4b9361182109872" , "Gemtech SFN-57 5.7x28mm silencer"},
        {"5d4405aaa4b9361e6a4e6bd3" , "Lightweight upper 5.56x45 for TX15 rifle"},
        {"5d4405f0a4b9361e6a4e6bd9" , "Lone Star Ion Lite handguard for AR-15 and compatible"},
        {"5d440625a4b9361eec4ae6c5" , "Thunder Beast 223CB Muzzle brake 5.56x45"},
        {"5d44064fa4b9361e4f6eb8b5" , "Thunder Beast Ultra 5 Sound Suppressor "},
        {"5d44069ca4b9361ebd26fc37" , "Magpul PRS GEN3 stock"},
        {"5d4406a8a4b9361e4f6eb8b7" , "Magpul PRS GEN3 Grey stock"},
        {"5d440b93a4b9364276578d4b" , "18\" barrel for AR-15 and compatible 5.56x45"},
        {"5d440b9fa4b93601354d480c" , "20\" barrel for AR-15 and compatible 5.56x45"},
        {"5d44334ba4b9362b346d1948" , "Raptor charging handle for AR-15 Grey"},
        {"5d443f8fa4b93678dd4a01aa" , "Thunder Beast 30CB Muzzle Brake 7.62x51"},
        {"5d4aaa54a4b9365392071170" , "TDI AKM-L handguard for AK Anodized Red"},
        {"5d4aaa73a4b9365392071175" , "TDI AKM-L handguard for AK Anodized Bronze"},
        {"5d4aab30a4b9365435358c55" , "VS-24 white handguard with a VS-33c gas block combo for AK"},
        {"5d52d479a4b936793d58c76b" , "AGS-30 30-Grenades box 30x29 "},
        {"5d7b6bafa4b93652786f4c76" , "FN RMR Mount for 5-7 Mk.2"},
        {"5dcbd6b46ec07c0c4347a564" , "Desert Tech foregrip for MDR blk"},
        {"5dcbd6dddbd3d91b3e5468de" , "Desert Tech pistol grip for MDR Black"},
        {"5dcbe9431e1f4616d354987e" , "16 inch .308 barrel for MDR and compatible"},
        {"5dcbe965e4ed22586443a79d" , "Desert Tech .308 Flash hider"},
        {"5de653abf76fdc1ce94a5a2a" , "Metal magazine for VPO-215 and compatibles, .366 TKM 4-round capacity"},
        {"5de65547883dde217541644b" , "23\" barrel for a VPO-215 .366TKM"},
        {"5de6556a205ddc616a6bc4f7" , "VPO-215 thread protection cap"},
        {"5de6558e9f98ac2bc65950fc" , "Scope mount for VPO-215"},
        {"5de655be4a9f347bc92edb88" , "Regular VPO-215 stock"},
        {"5de8e67c4a9f347bc92edbd7" , "Upper receiver B&T 9x19 for MP9-N SMG"},
        {"5de8e8dafd6b4e6e2276dc32" , "Standard 9x19 15-round magazine for MP9"},
        {"5de8ea8ffd6b4e6e2276dc35" , "Standard 9x19 20-round magazine for MP9"},
        {"5de8eaadbbaf010b10528a6d" , "Standard 9x19 25-round magazine for MP9"},
        {"5de8eac42a78646d96665d91" , "Standard 9x19 30-round magazine for MP9"},
        {"5de8f237bbaf010b10528a70" , "B&T adapter for MP9 regular suppressor."},
        {"5de8f2d5b74cd90030650c72" , "B&T MP9 9x19mm sound suppressor"},
        {"5de8fbad2fbe23140d3ee9c4" , "B&T MP9-N Vertical grip"},
        {"5de8fbf2b74cd90030650c79" , "B&T MP9 bottom rail"},
        {"5de8fc0b205ddc616a6bc51b" , "B&T MP9 side rail"},
        {"5de910da8b6c4240ba2651b5" , "Regular stock for B&T MP9"},
        {"5de922d4b11454561e39239f" , "B&T charging handle for MP9"},
        {"5df256570dee1b22f862e9c4" , "660mm .308 barrel for T-5000"},
        {"5df25b6c0b92095fd441e4cf" , "5-round .308 T-5000 magazine"},
        {"5df25d3bfd6b4e6e2276dc9a" , "Orsis handguard for T-5000"},
        {"5df35ddddfc58d14537c2036" , "Orsis T-5000M Stock"},
        {"5df35e59c41b2312ea3334d5" , "Orsis Aluminium body for T-5000"},
        {"5df35e7f2a78646d96665dd4" , "Orsis T-5000M muzzle brake"},
        {"5df35e970b92095fd441e4d2" , "Orsis scope mount for T-5000M"},
        {"5df35ea9c41b2312ea3334d8" , "Orsis long length rail"},
        {"5df35eb2b11454561e3923e2" , "Orsis medium length rail"},
        {"5df36948bb49d91fb446d5ad" , "T-5000 Pad"},
        {"5df38a5fb74cd90030650cb6" , "Orsis T-5000 Pistol Grip"},
        {"5df8e053bb49d91fb446d6a6" , "KAC Charging Handle for SR-25"},
        {"5df8e085bb49d91fb446d6a8" , "KAC Ambidextrous Charging Handle for AR-10"},
        {"5df8e4080b92095fd441e594" , "Upper receiver KAC 7.62x51 for SR-25 rifle"},
        {"5df8f535bb49d91fb446d6b0" , "KAC Steel 10 7.62x51 10 rnd"},
        {"5df8f541c41b2312ea3335e3" , "KAC Steel 20 7.62x51 20 rnd"},
        {"5df916dfbb49d91fb446d6b9" , "URX-4 handguard for AR-10 and compatible"},
        {"5df917564a9f347bc92edca3" , "16\" barrel for SR-25 and compatible 7.62x51"},
        {"5dfa397fb11454561e39246c" , "20\" barrel for SR-25 and compatible 7.62x51"},
        {"5dfa3cd1b33c0951220c079b" , "KAC QDC Flash suppressor kit 7.62x51 flash hider"},
        {"5dfa3d2b0dee1b22f862eade" , "KAC PRS QDC 7.62x51 Sound Suppressor "},
        {"5dfa3d45dfc58d14537c20b0" , "KAC Low Profile Gas Block"},
        {"5dfcd0e547101c39625f66f9" , "SAG MK1 Freefloat Chassis for SVD"},
        {"5dfce88fe9dc277128008b2e" , "Custom SVDS dust cover"},
        {"5dfe14f30b92095fd441edaf" , "ETMI-019 Mount"},
        {"5dff77c759400025ea5150cf" , "25mm rings made by UTG"},
        {"5dff8db859400025ea5150d4" , "SVD Low sidemount"},
        {"5e0090f7e9dc277128008b93" , "Upper receiver B&T 9x19 for MP9 SMG"},
        {"5e01e9e273d8eb11426f5bc3" , "Rotor 43 thread adapter for SVD-S"},
        {"5e01ea19e9dc277128008c0b" , "Rotor 43 7.62x54 muzzle brake"},
        {"5e208b9842457a4a7a33d074" , "Hexagon \"DTKP MK.2\" 7.62x39 sound suppressor"},
        {"5e217ba4c1434648c13568cd" , "Hexagon \"Kocherga\" stock red"},
        {"5e2192a498a36665e8337386" , "KGB MG-47 pistol grip for AK red"},
        {"5e21a3c67e40bd02257a008a" , "Pmag 30 AK/AKM GEN M3 7.62x39 magazine for AK and compatibles, 30-round capacity (banana)\n"},
        {"5e21ca18e4d47f0da15e77dd" , "CNC Warrior AK 5.56x45 mm muzzle device adapter"},
        {"5e56991336989c75ab4f03f6" , "Izhmash modern handguard for SVD"},
        {"5e5699df2161e06ac158df6f" , "CAA XRS DRG for SVD"},
        {"5e569a0156edd02abe09f27d" , "IzhMash modern rail for SVD"},
        {"5e569a132642e66b0b68015c" , "CAA DRG L-1 mount for SVD"},
        {"5e569a2e56edd02abe09f280" , "CAA XD RGL mount for SVD"},
        {"5e81c4ca763d9f754677befa" , "M1911 .45 ACP 7-round magazine"},
        {"5e81c519cb2b95385c177551" , "Standart barrel for M1911A1 .45 ACP"},
        {"5e81c539cb2b95385c177553" , "Slide lock for M1911A1"},
        {"5e81c550763d9f754677befd" , "Hammer for M1911A1"},
        {"5e81c6a2ac2bb513793cdc7f" , "Trigger for M1911A1"},
        {"5e81c6bf763d9f754677beff" , "Standart polymerpistol grip for M1911A1"},
        {"5e81edc13397a21db957f6a1" , "M1911A1 .45 ACP slide"},
        {"5e848d1c264f7c180b5e35a9" , "510mm barrel for KS-23 23x75mm"},
        {"5e848d2eea0a7c419c2f9bfd" , "700mm barrel for KS-23 23x75mm"},
        {"5e848d51e4dbc5266a4ec63b" , "TOZ KS-23M forestock"},
        {"5e848d99865c0f329958c83b" , "Polymer pistol grip for KS-23M"},
        {"5e848db4681bea2ada00daa9" , "Wooden stock for KS-23"},
        {"5e848dc4e4dbc5266a4ec63d" , "Wired stock for KS-23M"},
        {"5e87071478f43e51ca2de5e1" , "20\" barrel for M590 12ga"},
        {"5e87076ce2db31558c75a11d" , "Speedfeed short M590A1 forestock"},
        {"5e87080c81c4ed43e83cefda" , "8-shell M590A1 12ga magazine cap"},
        {"5e87116b81c4ed43e83cefdd" , "Polymer stock for M590A1"},
        {"5ea02bb600685063ec28bfa1" , "10.6\" barrel for PPSH-41 7.62x25"},
        {"5ea034eb5aad6446a939737b" , "35-round 7.62x25 magazine for PPSH-41"},
        {"5ea034f65aad6446a939737e" , "71-round 7.62x25 magazine for PPSH-41"},
        {"5ea03e5009aa976f2e7a514b" , "PPSH-41 dust cover"},
        {"5ea03e9400685063ec28bfa4" , "PPSH-41 stock"},
        {"5ea16acdfadf1d18c87b0784" , "Geissele SMR Mk.16 9.5 inch M-LOK handguard for AR-15"},
        {"5ea16ada09aa976f2e7a51be" , "Geissele SMR Mk.16 13.5 inch M-LOK handguard for AR-15"},
        {"5ea16d4d5aad6446a939753d" , "Geissele ACH charging handle for AR-15"},
        {"5ea172e498dacb342978818e" , "Surefire FH556RC 5.56x45 Flash hider for AR-15"},
        {"5ea17bbc09aa976f2e7a51cd" , "Surefire SOCOM556-RC2 5.56x45 silencer"},
        {"5eea21647547d6330471b3c9" , "Magpul MOE M590 forestock"},
        {"5eea217fc64c5d0dfc05712a" , "SGA stock for M590"},
        {"5eeb2ff5ea4f8b73c827350b" , "Tactical rail for M590"},
        {"5ef1b9f0c64c5d0dfc0571a1" , "LEO stock adapter gen.1 for M590"},
        {"5ef1ba28c64c5d0dfc0571a5" , "Mesa Tactical Crosshair Hydraulic buffer tube"},
        {"5ef32e4d1c1fd62aea6a150d" , "Caspian Trik Trigger for M1911A1"},
        {"5ef3448ab37dfd6af863525c" , "Mec-Gar .45 ACP 11-round magazine for M1911A1"},
        {"5ef3553c43cb350a955a7ccb" , "Wilson Extended slide stop for M1911A1"},
        {"5ef35bc243cb350a955a7ccd" , "Wilson Ultralight skeletonized hammer for M1911A1"},
        {"5ef35d2ac64c5d0dfc0571b0" , "Hammer for M1911A1"},
        {"5ef35f46382a846010715a96" , "STI HEX Hammer for M1911A1"},
        {"5ef366938cef260c0642acad" , "Pachmayr \"American legend grip #423 for M1911A1"},
        {"5ef369b08cef260c0642acaf" , "NCStar Trigger guard mount for M1911A1"},
        {"5ef5d994dfbc9f3c660ded95" , "Weigand Weig-a-tinny mount for M1911A1"},
        {"5ef61964ec7f42238c31e0c1" , "Anarchy Outdoors Muzzle Brake .45 ACP"},
        {"5efaf417aeb21837e749c7f2" , "B-30 foregrip and rail mount B-31C"},
        {"5f2aa43ba9b91d26f20ae6d2" , "RFB Thread spacer"},
        {"5f2aa4464b50c14bcf07acdb" , "RFB thread protection cap"},
        {"5f2aa4559b44de6b1b4e68d1" , "Regular RFB 7.62x51 Flash hider"},
        {"5f2aa46b878ef416f538b567" , "18\" barrel for RFB 7.62x51"},
        {"5f2aa47a200e2c0ee46efa71" , "Kel-Tec RFB regular handguard"},
        {"5f2aa493cd375f14e15eea72" , "Kel-Tec RFB handguard rail"},
        {"5f2aa49f9b44de6b1b4e68d4" , "Kel-Tec RFB scope mount rail"},
        {"5f3e76d86cda304dcc634054" , "Hammer for M45A1"},
        {"5f3e772a670e2a7b01739a52" , "Trigger for M45A1"},
        {"5f3e777688ca2d00ad199d25" , "Slide lock for M45A1"},
        {"5f3e778efcd9b651187d7201" , "Standart polymerpistol grip for M45A1"},
        {"5f3e77b26cda304dcc634057" , "M45A1 .45 ACP 7-round magazine"},
        {"5f3e77f59103d430b93f94c1" , "Threaded barrel for M1911A1 .45 ACP"},
        {"5f3e7801153b8571434a924c" , "National match barrel for M1911 .45 ACP"},
        {"5f3e7823ddc4f03b010e2045" , "M45A1 .45 ACP slide"},
        {"5f6331e097199b7db2128dc2" , "X47 Tactical Handguard for AK and compatible"},
        {"5f6336bbda967c74a42e9932" , "Lancer LCH-7 12.5 inch M-LOK handguard for AR-10"},
        {"5f6339d53ada5942720e2dc3" , "Ferfrans \"CRD\" 5.56x45"},
        {"5f633f68f5750b524b45f112" , "JMAC RRD-4C 7.62x39 muzzle brake for AKM type thread"},
        {"5f633f791b231926f2329f13" , "JMAC RRD-4C muzzle brake for AK-74 type thread"},
        {"5f633ff5c444ce7e3c30a006" , "Avalanche Mod.2 charging handle for AR-15"},
        {"5f63405df5750b524b45f114" , "VPO-101 SVD style stock"},
        {"5f63407e1b231926f2329f15" , "Rotor 43 7.62x51 muzzle brake for VPO-101"},
        {"5f6340d3ca442212f4047eb2" , "TD Aluminium skeletonized vertical grip"},
        {"5f6341043ada5942720e2dc5" , "Aeroknox scorpius pistol grip for AK"},
        {"5f63418ef5750b524b45f116" , "SOK-12 aluminum handguard Bravo-18"},
        {"5f6372e2865db925d54f3869" , "Ferfrans Muzzle Brake 5.56x45"},
        {"5f647d9f8499b57dc40ddb93" , "3-shell KS-23M 23mm magazine cap"},
        {"5fb651b52b1b027b1f50bcff" , "Glock .45 ACP magazine"},
        {"5fb651dc85f90547f674b6f4" , "Magex G30 magazine for Glock .45 ACP"},
        {"5fb65363d1409e5ca04b54f5" , "5\" Vector barrel .45 ACP"},
        {"5fb653962b1b027b1f50bd03" , "6\" Vector barrel .45 ACP"},
        {"5fb65424956329274326f316" , "Kriss Vector .45 ACP Flash hider"},
        {"5fb6548dd1409e5ca04b54f9" , "Kriss Vector .45 ACP  thread protection cap"},
        {"5fb6558ad6f0b2136f2d7eb7" , "KRISSVector Gen.2 folding stock"},
        {"5fb655a72b1b027b1f50bd06" , "Kriss Vector Pistol Sling Adapter"},
        {"5fb655b748c711690e3a8d5a" , "KRISS Vector non folding stock adapter"},
        {"5fbb976df9986c4cff3fe5f2" , "KRISS Vector Bottom rail"},
        {"5fbb978207e8a97d1f0902d3" , "KRISS Mk.5 Modular rail for Vector"},
        {"5fbbaa86f9986c4cff3fe5f6" , "KRISS Defiance DS150 stock"},
        {"5fbbc3324e8a554c40648348" , "KRISS Vector 9x19 Flash hider"},
        {"5fbbc34106bde7524f03cbe9" , "Vector 9x19 thread protection cap"},
        {"5fbbc366ca32ed67276c1557" , "5\" barrel for Vector 9x19"},
        {"5fbbc383d5cb881a7363194a" , "6\" barrel for Vector 9x19"},
        {"5fbbfabed5cb881a7363194e" , "171mm barrel for MCX and compatible .300 BLK"},
        {"5fbbfacda56d053a3543f799" , "229mm barrel for MCX and compatible .300 BLK"},
        {"5fbc210bf24b94483f726481" , "SIG MCX Gas Block"},
        {"5fbc226eca32ed67276c155d" , "SIG 8\" keymod foregrip for MCX"},
        {"5fbc227aa56d053a3543f79e" , "SIG 12\" keymod foregrip for MCX"},
        {"5fbc22ccf24b94483f726483" , "SIG Taper-LOK Muzzle Adapter"},
        {"5fbcbcf593164a5b6278efb2" , "3-prong SIG Flash hider 7.62x51"},
        {"5fbcbd02900b1d5091531dd3" , "SIG micro brake muzzle brake 7.62x51"},
        {"5fbcbd10ab884124df0cd563" , "SIG Two Port brake muzzle brake 7.62x51"},
        {"5fbcbd6c187fea44d52eda14" , "SIG MCX pistol grip"},
        {"5fbcc3e4d6fa9c00c571bb58" , "Upper receiver of the first generation Sig-Sauer MCX"},
        {"5fbcc429900b1d5091531dd7" , "SIG Sauer telescoping MCX/MPX stock"},
        {"5fbcc437d724d907e2077d5c" , "SIG Sauer Thin lightweight MCX/MPX stock"},
        {"5fbcc640016cce60e8341acc" , "Sig-Sauer charging handle for MCX"},
        {"5fbe760793164a5b6278efc8" , "Sig-Sauer SRD QD 7.62x51 Sound Suppressor "},
        {"5fbe7618d6fa9c00c571bb6c" , "Sig-Sauer \"SRD\" 7.62x51 Sound Suppressor "},
        {"5fc0f9b5d724d907e2077d82" , "MVF001 A3 Vertical Grip KeyMod black"},
        {"5fc0f9cbd6fa9c00c571bb90" , "Sig Sauer Vertical Foregrip Keymod Black"},
        {"5fc23426900b1d5091531e15" , "Sword Int. Mk-18 .338 LM 10-round magazine"},
        {"5fc235db2770a0045c59c683" , "Sword int. 18 inch handguard for Mk-18"},
        {"5fc2360f900b1d5091531e19" , "Mk-18 Gas Block"},
        {"5fc23636016cce60e8341b05" , "SilencerCo AC-858 ASR .338 LM Muzzle brake"},
        {"5fc23678ab884124df0cd590" , "24\" barrel for Mk-18 .338 LM"},
        {"5fc2369685fd526b824a5713" , "B5 Precision stock"},
        {"5fc278107283c4046c581489" , "Sword Int. Mk-18 mod 1 Upper receiver"},
        {"5fc3e466187fea44d52eda90" , "Standard UMP 25-round .45 ACP magazine"},
        {"5fc3e4a27283c4046c5814ab" , "8\" barrel for UMP .45 ACP"},
        {"5fc3e4ee7283c4046c5814af" , "Polymer stock for UMP"},
        {"5fc4b97bab884124df0cd5e3" , "Piston Mount adapter for Silencerco Omega 45k"},
        {"5fc4b992187fea44d52edaa9" , "Direct Thread Mount adapter for Silencerco Omega 45k"},
        {"5fc4b9b17283c4046c5814d7" , "SilencerCo Omega 45k .45 ACP sound suppressor"},
        {"5fc53954f8b6a877a729eaeb" , "HK UMP Bottom rail"},
        {"5fc5396e900b1d5091531e72" , "HK UMP Side rail"},
        {"5fce0cf655375d18a253eff0" , "Magpul RVG grip FDE"},
        {"5fce0f9b55375d18a253eff2" , "KRISS Vector Side rail"},
        {"5fce16961f152d4312622bc9" , "KRISS Defiance DS150 FDE stock"},
        {"5449016a4bdc2d6f028b456f" , "Roubles"},
        {"544901bf4bdc2ddf018b456d" , "Wad of roubles"},
        {"5696686a4bdc2da3298b456a" , "Dollars"},
        {"569668774bdc2da2298b4568" , "Euros"},
        {"544a3a774bdc2d3a388b4567" , "Leupold Mark 4 HAMR 4x24mm DeltaPoint hybrid assault scope"},
        {"544a3d0a4bdc2d1b388b4567" , "Nightforce NXS 2.5-10x24 scope"},
        {"544a3f024bdc2d1d388b4568" , "ELCAN Specter OS4x assault scope"},
        {"558022b54bdc2dac148b458d" , "Eotech EXPS3 holographic sight"},
        {"55d4af3a4bdc2d972f8b456f" , " UTG Low Profile A2 Frontsight AR-15"},
        {"55d5f46a4bdc2d1b198b4567" , "Colt A2 Rearsight AR-15"},
        {"56083e1b4bdc2dc8488b4572" , "Izhmash SV-98 Rearsight"},
        {"5649b0544bdc2d1b2b8b458a" , "AK-74 Standard Rearsight (6P1 Sb.2)"},
        {"5649d9a14bdc2d79388b4580" , "Tactica Tula TT01 Rearsight Weaver Adapter"},
        {"56d5a661d2720bd8418b456b" , "Sig Sauer Standard Frontsight"},
        {"56d5a77ed2720b90418b4568" , "Sig Sauer P226 Standard Rearsight"},
        {"56ea70acd2720b844b8b4594" , "Hensoldt FF 4-16x56 scope"},
        {"56ea7293d2720b8d4b8b45ba" , "Sight Mount Sig 220-239 rear sight bearing"},
        {"570fd6c2d2720bc6458b457f" , "Eotech 553 holographic sight"},
        {"570fd721d2720bc5458b4596" , "Walther MRS reflex sight"},
        {"570fd79bd2720bc7458b4583" , "OKP-7 reflex sight"},
        {"57235b6f24597759bf5a30f1" , "AN/PVS-14 Night Vision Monocular"},
        {"57486e672459770abd687134" , "OKP-7 reflex sight"},
        {"574db213245977459a2f3f5d" , "SKS Standard Rearsight"},
        {"576fd4ec2459777f0b518431" , "Zenit-Belomo PSO 1M2-1 4x24 scope"},
        {"577d141e24597739c5255e01" , "Burris FastFire 3 Reflex Sight"},
        {"57838e1b2459774a256959b1" , "VSS Vintorez Standard Rearsight"},
        {"57a9b9ce2459770ee926038d" , "IzhMash SOK-12 rear sight"},
        {"57ac965c24597706be5f975c" , "ELCAN SpecterDR 1x/4x Scope"},
        {"57aca93d2459771f2c7e26db" , "ELCAN SpecterDR 1x/4x Scope FDE"},
        {"57adff4f24597737f373b6e6" , "Sig BRAVO4 4X30 Scope"},
        {"57ae0171245977343c27bfcf" , "Belomo PK-06 reflex sight"},
        {"57c44e7b2459772d28133248" , "AS VAL Standard rear sight"},
        {"57c5ac0824597754771e88a9" , "Optical scope March Tactical 3-24x42 FFP"},
        {"58272b842459774abc128d50" , "SOK-12 CSS SIGHT RAIL MOUNT rear sight"},
        {"58491f3324597764bc48fa02" , "Eotech XPS3-0 holographic sight"},
        {"584924ec24597768f12ae244" , "Eotech XPS3-2 holographic sight"},
        {"584984812459776a704a82a6" , "VOMZ Pilad P1X42 \"WEAVER\" reflex sight"},
        {"5894a73486f77426d259076c" , "SIG MPX Flip Up Frontsight"},
        {"5894a81786f77427140b8347" , "SIG MPX Flip Up Rearsight"},
        {"58d268fc86f774111273f8c2" , "Leupold DeltaPoint Reflex Sight"},
        {"58d399e486f77442e0016fe7" , "Aimpoint Micro T-1 reflex sight"},
        {"591c4efa86f7741030027726" , "Cobra EKP-8-18 reflex sight"},
        {"5926d2be86f774134d668e4e" , "HK MP5 Drum Rearsight"},
        {"5947db3f86f77447880cf76f" , "Cobra EKP-8-02 reflex sight"},
        {"599860e986f7743bb57573a6" , "Izhmash rear sight fro PP-19-01"},
        {"59d650cf86f7741b846413a4" , "AKM Standard Rearsight (6P1 Sb.2-1)"},
        {"59db7e1086f77448be30ddf3" , "Trijicon ACOG 3.5x35 scope"},
        {"59e8977386f77415a553c453" , "AKM / VPO-209 Standard Rearsight"},
        {"59f9d81586f7744c7506ee62" , "Vortex Razor AMG UH-1 holographic sight"},
        {"5a0eb980fcdbcb001a3b00a6" , "AKMB system rear sight"},
        {"5a0ed824fcdbcb0176308b0d" , "AKMP system rear sight device"},
        {"5a0f096dfcdbcb0176308b15" , "AKMP system front sight device"},
        {"5a1eaa87fcdbcb001865f75e" , "Trijicon REAP-IR thermal riflescope"},
        {"5a32aa8bc4a2826c6e06d737" , "Trijicon RMR"},
        {"5a37cb10c4a282329a73b4e7" , "Leupold Mark 4 LR 6.5-20x50 riflescope"},
        {"5a6f58f68dc32e000a311390" , "Glock Front Sight"},
        {"5a6f5d528dc32e00094b97d9" , "Glock Rear Sight"},
        {"5a71e0048dc32e000c52ecc8" , "Glock ZEV Tech front sight"},
        {"5a71e0fb8dc32e00094b97f2" , "Glock ZEV Tech Rear sight"},
        {"5a7c74b3e899ef0014332c29" , "NSPU-M night Scope"},
        {"5a7d90eb159bd400165484f1" , "Dead Ringer Snake Eye Glock front sight"},
        {"5a7d9104159bd400134c8c21" , "Truglo TFX Glock front sight"},
        {"5a7d9122159bd4001438dbf4" , "Dead Ringer Snake Eye Glock rear sight"},
        {"5a7d912f159bd400165484f3" , "Truglo TFX Glock rear sight"},
        {"5aa66be6e5b5b0214e506e97" , "Nightforce ATACR 7-35x56 riflescope"},
        {"5aafa49ae5b5b00015042a58" , " SA XS Post .125 blade Frontsight M1A"},
        {"5aba62f8d8ce87001943946b" , "APS Frontsight"},
        {"5aba637ad8ce87001773e17f" , "APS Rearsight"},
        {"5aba639ed8ce8700182ece67" , "APB Rearsight"},
        {"5abcbb20d8ce87001773e258" , "M14 Enlarged Military Aperture Rearsight "},
        {"5ac72e475acfc400180ae6fe" , "AK-74M Standard Rearsight (6P20 Sb.2)"},
        {"5ac733a45acfc400192630e2" , "AK-105 Standard Rearsight (6P44 Sb.1-30)"},
        {"5addba3e5acfc4001669f0ab" , " SA National Match .062 blade Frontsight M1A"},
        {"5ae099875acfc4001714e593" , "Mosin frontsight"},
        {"5ae099925acfc4001a5fc7b3" , "Mosin Rearsight"},
        {"5ae30bad5acfc400185c2dc4" , " Rearsight AR-15 Carry Handle"},
        {"5b0bc22d5acfc47a8607f085" , "DS Arms Holland Type Rearsight for SA-58"},
        {"5b2388675acfc4771e1be0be" , "Burris FullField TAC 30 1-4x24 riflescope"},
        {"5b30b0dc5acfc400153b7124" , "Holosun HS401G5 reflex sight"},
        {"5b3116595acfc40019476364" , "Sig Sauer Romeo 4 reflex sight"},
        {"5b3b6e495acfc4330140bd88" , "Vulcan MG night scope 3.5x"},
        {"5b3b99475acfc432ff4dcbee" , "EOtech Vudu 1-6 riflescope"},
        {"5b3f7c1c5acfc40dc5296b1d" , "PU 3.5x riflescope"},
        {"5ba26b01d4351e0085325a51" , "MP7 Flip Up Frontsight"},
        {"5ba26b17d4351e00367f9bdd" , "MP7 Flip Up Rearsight"},
        {"5bb20e49d4351e3bac1212de" , "HK 416A5 Flip Up Rearsight"},
        {"5bc09a18d4351e003562b68e" , " Magpul MBUS Gen.2 Rearsight"},
        {"5bc09a30d4351e00367fb7c8" , " Magpul MBUS Gen.2 Frontsight"},
        {"5beec9450db83400970084fd" , "Izhmash Rearsight base for RPK-16"},
        {"5bf3f59f0db834001a6fa060" , "Izhmash Rearsight for RPK-16"},
        {"5bfd4c980db834001b73449d" , "Mosin carbine Rearsight"},
        {"5c0505e00db834001b735073" , "Valday 1P87 holographic sight"},
        {"5c0517910db83400232ffee5" , "Valday PS-320 1x/6x Scope"},
        {"5c05293e0db83400232fff80" , "Trijicon ACOG TA01NSN 4x32 scope"},
        {"5c05295e0db834001a66acbb" , "Trijicon ACOG backup rear sight"},
        {"5c052a900db834001a66acbd" , "Trijicon ACOG TA01NSN 4x32 scope TAN"},
        {"5c0558060db834001b735271" , "GPNVG-18 Night Vision"},
        {"5c066e3a0db834001b7353f0" , "Armasight N-15 Night Vision"},
        {"5c0696830db834001d23f5da" , "PNV-10T Night Vision"},
        {"5c07b36c0db834002a1259e9" , "Meprolight \"Tru Dot Night Sight\" Frontsight for P226"},
        {"5c07b3850db834002330045b" , "Meprolight Tru Dot Night Sight rear sight for P226"},
        {"5c07dd120db834001c39092d" , "Eotech HHS-1 sight"},
        {"5c0a2cec0db834001b7ce47d" , "Eotech HHS-1 sight Tan"},
        {"5c110624d174af029e69734c" , "T-7 Thermal Goggles with Night Vision Mounts"},
        {"5c1780312e221602b66cc189" , "KAC Folding sight Rear"},
        {"5c17804b2e2216152006c02f" , "KAC Folding sight Frontsight"},
        {"5c18b90d2e2216152142466b" , " Magpul MBUS Gen.2 Frontsight FDE"},
        {"5c18b9192e2216398b5a8104" , " Magpul MBUS Gen.2 Rearsight FDE"},
        {"5c1cdd512e22161b267d91ae" , "Primary Arms Compact prism scope 2.5x"},
        {"5c471b7e2e2216152006e46c" , "SVDS Rearsight"},
        {"5c471ba12e221602b3137d76" , "SVDS frontsight"},
        {"5c503b1c2e221602b21d6e9d" , "VPO-101 Standard Rearsight"},
        {"5c7d55de2e221644f31bff68" , "Aimpoint COMP M4 reflex sight"},
        {"5c82342f2e221644f31c060e" , "Zenit-Belomo PSO 1 4x24 scope"},
        {"5c82343a2e221644f31c0611" , "Zenit-Belomo PSO 1M2 4x24 scope"},
        {"5cadd919ae921500126a77f3" , "M9A3 Standard Frontsight"},
        {"5cadd940ae9215051e1c2316" , "Beretta M9A3 Standard Rearsight"},
        {"5cadd954ae921500103bb3c2" , "Sight Mount M9 rear sight bearing"},
        {"5caf1691ae92152ac412efb9" , " Rearsight ASh-12 Carry Handle"},
        {"5caf16a2ae92152ac412efbc" , "ASh-12 Folding sight Frontsight"},
        {"5cebec38d7f00c00110a652a" , "FN Ring sight reflex sight"},
        {"5cf638cbd7f00c06595bc936" , "NPZ USP-1 4x scope"},
        {"5d0a3a58d7ad1a669c15ca14" , "KMZ 1P59 3-10x riflescope"},
        {"5d0a3e8cd7ad1a6f6a3d35bd" , "KMZ 1P69 3-10x riflescope"},
        {"5d1b5e94d7ad1a2b865a96b0" , "FLIR RS-32 2.25-9x 35mm 60Hz thermal riflescope"},
        {"5d2da1e948f035477b1ce2ba" , "Trijicon SRS-02 reflex sight"},
        {"5d2dc3e548f035404a1a4798" , "Monstrum Compact prism scope 2x32"},
        {"5d3eb4aba4b93650d64e497d" , "Five-seveN Standard Rear-sight"},
        {"5d3eb536a4b9363b1f22f8e2" , "Five-seveN MK2 Standard Frontsight"},
        {"5d53f4b7a4b936793d58c780" , "PAG-17 scope"},
        {"5de8fb539f98ac2bc659513a" , "B&T MP9 Standard Rear-sight"},
        {"5dfa3d7ac41b2312ea33362a" , "KAC Folding micro sight Rear"},
        {"5dfa3d950dee1b22f862eae0" , "KAC Folding micro sight Frontsight"},
        {"5dfe6104585a0c3e995c7b82" , "NcSTAR ADO P4 Sniper 3-9x42 riflescope"},
        {"5dff772da3651922b360bf91" , "VOMZ Pilad 4x32 riflescope"},
        {"5e81ee213397a21db957f6a6" , "M1911A1 Front Sight"},
        {"5e81ee4dcb2b95385c177582" , "M1911A1 Rear Sight"},
        {"5e8708d4ae379e67d22e0102" , "Ghost ring kit M590 Frontsight"},
        {"5e87114fe2db31558c75a120" , "Ghost ring Rear sight for M590"},
        {"5f3e7897ddc4f03b010e204a" , "Novak Lomount Rear Sight"},
        {"5f3e78a7fbf956000b716b8e" , "Novak Lomount Front Sight"},
        {"5fb6564947ce63734e3fa1da" , "KRISS Defiance Low Profile Flip-Up rear sight"},
        {"5fb6567747ce63734e3fa1dc" , "Kriss \"Defiance Low Profile Flip Up\" Frontsight"},
        {"5fc0fa362770a0045c59c677" , "SIG MCX Folding sight Frontsight"},
        {"5fc0fa957283c4046c58147e" , "SIG MCX Flip Up sight Rearsight"},
        {"544fb5454bdc2df8738b456a" , "Leatherman Multitool"},
        {"591094e086f7747caa7bb2ef" , "Body armor repair kit"},
        {"5910959486f7747d96753485" , "Knife repair and sharpening kit"},
        {"5910968f86f77425cf569c32" , "Weapons repair kit"},
        {"5991b51486f77447b112d44f" , "MS2000 Marker"},
        {"5ac78a9b86f7741cca0bbd8d" , "Signal Jammer"},
        {"5af056f186f7746da511291f" , "IMP minedetector"},
        {"5b4391a586f7745321235ab2" , "WIFI Camera"},
            {"5448be9a4bdc2dfd2f8b456a" , "RGD-5 hand grenade"},
            {"5710c24ad2720bc3458b45a3" , "F-1 Hand grenade"},
            {"58d3db5386f77426186285a0" , "M67 Hand grenade"},
            {"5a0c27731526d80618476ac4" , "Zarya stun grenade"},
            {"5a2a57cfc4a2826c6e06d44a" , "RDG-2B Smoke grenade"},
            {"5e32f56fcb6d5863cc5e5ee4" , "VOG-17 Khattabka grenade"},
            {"5e340dcdcb6d5863cc5e5efb" , "VOG-25 Khattabka grenade"},
            {"544a5caa4bdc2d1a388b4568" , "Crye Precision AVS platecarrier"},
            {"5648a69d4bdc2ded0b8b457b" , "BlackRock chest rig"},
            {"572b7adb24597762ae139821" , "Scav Vest"},
            {"5929a2a086f7744f4b234d43" , "UMTBS 6sh112 Scout-Sniper"},
            {"592c2d1a86f7746dbe2af32a" , "ANA Tactical Alpha chest rig"},
            {"59e7643b86f7742cbf2c109a" , "Wartech gear rig (TV-109, TV-106)"},
            {"5ab8dab586f77441cd04f2a2" , "Wartech MK3 chest rig (TV-104)"},
            {"5ab8dced86f774646209ec87" , "ANA Tactical M2 armored rig"},
            {"5b44c8ea86f7742d1627baf1" , "Blackhawk! Commando Chest Harness"},
            {"5b44cad286f77402a54ae7e5" , "5.11 Tactec plate carrier"},
            {"5c0e3eb886f7742015526062" , "6B5-16 Zh -86 \"Uley\" armored rig"},
            {"5c0e446786f7742013381639" , "6B5-15 Zh -86 \"Uley\" armored rig"},
            {"5c0e6a1586f77404597b4965" , "Belt-A + Belt-B gear rig"},
            {"5c0e722886f7740458316a57" , "ANA Tactical M1 armored rig"},
            {"5c0e746986f7741453628fe5" , "Wartech TV-110 plate carrier"},
            {"5c0e9f2c86f77432297fe0a3" , "Blackhawk! Commando Chest Harness (black)"},
            {"5ca20abf86f77418567a43f2" , "Triton M43-A Chest Harness"},
            {"5d5d646386f7742797261fd9" , "6B3TM-01M armored rig"},
            {"5d5d85c586f774279a21cbdb" , "Haley Strategic D3CRX Chest Harness"},
            {"5d5d87f786f77427997cfaef" , "Ars Arma A18 Skanda plate carrier"},
            {"5d5d8ca986f7742798716522" , "SOE Micro Rig"},
            {"5df8a42886f77412640e2e75" , "Velocity Systems Multi-Purpose Patrol Vest"},
            {"5e4abc1f86f774069619fbaa" , "Spiritus Systems Bank Robber Chest Rig"},
            {"5e4abfed86f77406a2713cf7" , "Splav Tarzan M22 Rig"},
            {"5e4ac41886f77406a511c9a8" , "Ars Arma CPC MOD.2 plate carrier"},
            {"5e9db13186f7742f845ee9d3" , "LBT-1961A Load Bearing Chest Vest"},
            {"5f5f41f56760b4138443b352" , "Direct Action Thunderbolt compact chest rig"},
            {"5fd4c4fa16cac650092f6771" , "DIY IDEA chest rig"},
            {"5fd4c5477a8d854fa0105061" , "Security vest"},
            {"5fd4c60f875c30179f5d04c2" , "Gear Craft GC-BSS-MK1 rig"},
        {"5447a9cd4bdc2dbd208b4567" , "Colt M4A1 5.56x45 Assault Rifle"},
        {"5448bd6b4bdc2dfc2f8b4569" , "PM 9x18PM pistol"},
        {"54491c4f4bdc2db1078b4568" , "MP-133 12ga shotgun"},
        {"55801eed4bdc2d89578b4588" , "SV-98 bolt-action sniper rifle"},
        {"5580223e4bdc2d1c128b457f" , "MP43e double-barrel shotgun"},
        {"5644bd2b4bdc2d3b4c8b4572" , "AK-74N 5.45x39 assault rifle"},
        {"56d59856d2720bd8418b456a" , "P226R 9x19 pistol"},
        {"56dee2bdd2720bc8328b4567" , "MP-153 12ga semi-automatic shotgun"},
        {"56e0598dd2720bb5668b45a6" , "PB 9x18PM silenced pistol"},
        {"571a12c42459771f627b58a0" , "TT pistol 7.62x25 TT"},
        {"574d967124597745970e7c94" , "Simonov Semi-Automatic Carbine SKS 7.62x39"},
        {"576165642459773c7a400233" , "Saiga 12ga ver. 10 12/76 shotgun"},
        {"576a581d2459771e7b1bc4f1" , "Yarygin MP-443 Grach 9x19 pistol"},
        {"57838ad32459774a17445cd2" , "Special Sniper Rifle VSS Vintorez "},
        {"579204f224597773d619e051" , "PM (t) 9x18PM pistol"},
        {"57c44b372459772d2b39b8ce" , "AS VAL"},
        {"57d14d2524597714373db789" , "PP-91 Kedr 9x18PM SMG"},
        {"57dc2fa62459775949412633" , "Kalashnikov AKS-74U 5.45x39"},
        {"57f3c6bd24597738e730fa2f" , "PP-91-01 Kedr-B 9x18PM SMG"},
        {"57f4c844245977379d5c14d1" , "PP-9 Klin 9x18PMM SMG"},
        {"583990e32459771419544dd2" , "Kalashnikov AKS-74UN 5.45x39"},
        {"5839a40f24597726f856b511" , "Kalashnikov AKS-74UB 5.45x39"},
        {"587e02ff24597743df3deaeb" , "Simonov Semi-Automatic Carbine SKS 7.62x39 Hunting Rifle\nVersion"},
        {"588892092459774ac91d4b11" , "DVL-10 Saboteur sniper rifle"},
        {"58948c8e86f77409493f7266" , "SIG MPX 9x19 Submachine gun"},
        {"5926bb2186f7744b1c6c6e60" , "HK MP5 9x19 submachinegun (Navy 3 Round Burst)"},
        {"59984ab886f7743e98271174" , "Submachinegun PP-19-01 Vityaz-SN 9x19"},
        {"59d6088586f774275f37482f" , "AKM 7.62x39 assault rifle"},
        {"59e6152586f77473dc057aa1" , "Vepr KM / VPO-136 7.62x39 carbine"},
        {"59e6687d86f77411d949b251" , "Vepr AKM / VPO-209 366TKM carbine"},
        {"59f98b4986f7746f546d2cef" , "9x21 Serdyukov automatic pistol SR1MP Gyurza"},
        {"59f9cabd86f7743a10721f46" , "Saiga-9 9x19 Carbine"},
        {"59ff346386f77477562ff5e2" , "AKMS 7.62x39 assault rifle"},
        {"5a0ec13bfcdbcb00165aa685" , "AKMN 7.62x39 assault rifle"},
        {"5a17f98cfcdbcb0980087290" , "Stechkin Automatic Pistol 9x18PM"},
        {"5a367e5dc4a282000e49738f" , "Remington R11 RSASS 7.62x51"},
        {"5a38e6bac4a2826c6e06d79b" , "TOZ-106 bolt-action shotgun"},
        {"5a7828548dc32e5a9c28b516" , "Remington Model 870 12ga shotgun"},
        {"5a7ae0c351dfba0017554310" , "GLOCK 17 9x19 pistol"},
        {"5aafa857e5b5b00018480968" , "Springfield Armory M1A 7.62x51"},
        {"5ab8e9fcd8ce870019439434" , "AKS-74N 5.45x39 assault rifle"},
        {"5abcbc27d8ce8700182eceeb" , "AKMSN 7.62x39 assault rifle"},
        {"5abccb7dd8ce87001773e277" , "Silenced Stechkin Automatic Pistol 9x18PM"},
        {"5ac4cd105acfc40016339859" , "AK-74M 5.45x39 assault rifle"},
        {"5ac66cb05acfc40198510a10" , "AK-101 5.56x45 assault rifle"},
        {"5ac66d015acfc400180ae6e4" , "AK-102 5.56x45 assault rifle"},
        {"5ac66d2e5acfc43b321d4b53" , "AK-103 7.62x39 assault rifle"},
        {"5ac66d725acfc43b321d4b60" , "AK-104 7.62x39 assault rifle"},
        {"5ac66d9b5acfc4001633997a" , "AK-105 5.45x39 assault rifle"},
        {"5ae083b25acfc4001a5fc702" , "Master Hand"},
        {"5ae08f0a5acfc408fb1398a1" , "Mosin bolt-action sniper rifle"},
        {"5b0bbe4e5acfc40dc528a72d" , "DS Arms SA-58 7.62x51"},
        {"5b1fa9b25acfc40018633c01" , "GLOCK 18C 9x19 pistol"},
        {"5b3b713c5acfc4330140bd8d" , "TT pistol 7.62x25 TT Gold"},
        {"5ba26383d4351e00334c93d9" , "HK MP7A1 4.6x30 submachinegun"},
        {"5bb2475ed4351e00853264e3" , "HK 416A5 5.56x45 Assault Rifle"},
        {"5bd70322209c4d00d7167b8f" , "HK MP7A2 4.6x30 submachinegun"},
        {"5beed0f50db834001c062b12" , "RPK-16 5.45x39 light machine gun"},
        {"5bf3e03b0db834001d2c4a9c" , "AK-74 5.45x39 assault rifle"},
        {"5bf3e0490db83400196199af" , "AKS-74 5.45x39 assault rifle"},
        {"5bfd297f0db834001a669119" , "Mosin bolt-action infantry rifle"},
        {"5bfea6e90db834001b7347f3" , "Remington Model 700 Sniper rifle"},
        {"5c07c60e0db834002330051f" , "ADAR 2-15 .223 Carbine"},
        {"5c46fbd72e2216398b5a8c9c" , "SVDS 7.62x54 Sniper rifle"},
        {"5c488a752e221602b412af63" , "DT MDR 5.56x45 Assault Rifle"},
        {"5c501a4d2e221602b412b540" , "Vepr Hunter/VPO-101 7.62x51 carbine"},
        {"5cadc190ae921500103bb3b6" , "Beretta M9A3 9x19 pistol"},
        {"5cadfbf7ae92152ac412eeef" , "ASh-12 12.7x55 assault rifle"},
        {"5cc82d76e24e8d00134b4b83" , "FN P90 5.7x28 submachinegun"},
        {"5cdeb229d7f00c000e7ce174" , "NSV \"Utes\" 12.7x108 machine gun"},
        {"5d2f0d8048f0356c925bc3b0" , "HK MP5 Kurz 9x19 submachinegun"},
        {"5d3eb3b0a4b93615055e84d2" , "FN Five-seveN MK2 5.7x28 pistol"},
        {"5d43021ca4b9362eab4b5e25" , "Lone Star TX-15 DML Rifle"},
        {"5d52cc5ba4b9367408500062" , "AGS 30x29 mm automatic grenade launcher"},
        {"5d67abc1a4b93614ec50137f" , "FN Five-seveN MK2 FDE Frame 5.7x28 pistol"},
        {"5dcbd56fdbd3d91b3e5468d5" , "DT MDR 7.62x51 Assault Rifle"},
        {"5de652c31b7e3716273428be" , "Molot VPO-215 .366 TKM rifle"},
        {"5de7bd7bfd6b4e6e2276dc25" , "B&T MP9-N 9x19 Submachinegun"},
        {"5df24cf80dee1b22f862e9bc" , "Orsis T-5000 .308 sniper rifle"},
        {"5df8ce05b11454561e39243b" , "Knight's Armament Company SR-25 7.62x51"},
        {"5e00903ae9dc277128008b87" , "B&T MP9 9x19 submachinegun"},
        {"5e81c3cbac2bb513793cdc75" , "Colt M1911A1 .45 ACP pistol"},
        {"5e81ebcd8e146c7080625e15" , "FN GL40 Mk.2 grenade launcher"},
        {"5e848cc2988a8701445df1e8" , "TOZ KS-23M 23x75mm shotgun"},
        {"5e870397991fd70db46995c8" , "Mossberg 590A1 12ga shotgun"},
        {"5ea03f7400685063ec28bfa8" , "Submachinegun PPSH-41 7.62x25"},
        {"5f2a9575926fd9352339381f" , "Kel-Tec RFB 7.62x51"},
        {"5f36a0e5fbf956000b716b65" , "Colt M45A1 .45 ACP pistol"},
        {"5fb64bc92b1b027b1f50bcf2" , "TDI KRISS Vector Gen.2 .45 ACP submachinegun"},
        {"5fbcc1d9016cce60e8341ab3" , "SIG MCX .300 AAC Blackout Assault Rifle"},
        {"5fc22d7c187fea44d52eda44" , "Mk-18 .338 LM marksman rifle"},
        {"5fc3e272f8b6a877a729eac5" , "HK UMP 45 submachinegun"},
        {"5fc3f2d5900b1d5091531e57" , "TDI Kriss Vector Gen.2 9x19 submachinegun"},
        {"59fafd4b86f7745ca07e1232" , "Keytool"},
        {"59fb023c86f7746d0d4b423c" , "Weapon case"},
        {"59fb016586f7746d0d4b423a" , "Moneycase"},
        {"619cbf9e0a7c3a1a2731940a" , "Keycard Holder"},
        {"5b7c710788a4506dec015957" , "junkbox"},
        {"5aafbcd986f7745e590fff23" , "medscase"},
        {"59fb042886f7746c5005a7b2" , "Itemcase"},
        { "5c127c4486f7745625356c13" , "magbox" },
        { "5c093e3486f77430cb02e593" , "dogtag" },
        { "5c093db286f7740a1b2617e3" , "lunchbox" },
        { "619cbf476b8a1b37a54eebf8" , "MilTube"}

    };
    return true;
}

bool EFTData::InitOffsets() {
	//std::cout << "--------------IN InitOffsets()--------------\n";
	/* 
	* 
	* 
	*			Initialize Base Address and find GameObjectManager using GOM offset
	* 
	* 
	*/
	this->offsets.gameObjectManager = mem->Read<DWORD64>(mem->get_module_base_address("UnityPlayer.dll") + this->offsets.oGOM);
	//std::cout <<  "UnityPlayer.dll: " << std::hex << mem->get_module_base_address("UnityPlayer.dll") << std::dec << std::endl;
	//std::cout << this->offsets.oGOM << std::endl;
	//std::cout << "GOM:" << std::hex << this->offsets.gameObjectManager << std::dec << std::endl;

	/*
	* 
	* 
	*			Iterate through active objects in the game to find the GameWorld object 
	* 
	* 
	*/
	auto active_objects = mem->Read<std::array<uint64_t, 2>>(this->offsets.gameObjectManager + offsetof(EFTStructs::GameObjectManager, lastActiveObject));
	//std::cout << "GOM + " << std::hex << offsetof(EFTStructs::GameObjectManager, lastActiveObject) << std::dec << std::endl;
	
	uint64_t activeObjList = mem->Read<uint64_t>(this->offsets.gameObjectManager + offsetof(EFTStructs::GameObjectManager, activeObjects));
	uint64_t lastActiveObj = mem->Read<uint64_t>(this->offsets.gameObjectManager + offsetof(EFTStructs::GameObjectManager, lastActiveObject));

	//if either activeObjects are empty return false
	if (!activeObjList || !lastActiveObj)
		return false;


	//std::cout << "--------------SEARCHING FOR GAMEWORLD--------------\n";
	//find correct gameworld
	{
		int playerCount = 0;
		while (playerCount == 0 || playerCount > 128) {
			if (!(this->offsets.gameWorld = GetObjectFromList(activeObjList, lastActiveObj, _xor_("GameWorld"))))
				return false;
																						//Change 78 and 18.. RegisteredPlayers & PlayerCount
			playerCount = (int)mem->ReadChain(this->offsets.gameWorld, { 0x30, 0x18, 0x28, 0x80, 0x18 });
			//std::cout << "Players: " << playerCount << std::endl;
		}
	}
	//std::cout << "GameWorld: "<< std::hex <<this->offsets.gameWorld << std::dec << std::endl;
	//Set Local gameworld after finding GameWorld
	this->offsets.localGameWorld = mem->ReadChain(this->offsets.gameWorld, { 0x30, 0x18, 0x28 });
	//std::cout << "LocalGameWorld: " << std::hex << this->offsets.localGameWorld << std::dec << std::endl;

	//std::cout << "--------------FOUND GAME WORLD--------------\n";

	/*
	*
	*
	*			Iterate through camera objects in the game to find the FPS Camera object
	*
	*
	*/
	auto camera_objects = mem->Read<uint64_t>(this->offsets.gameObjectManager + offsetof(EFTStructs::GameObjectManager, cameraObjects));
	auto lastCamera_object = mem->Read<uint64_t>(this->offsets.gameObjectManager + offsetof(EFTStructs::GameObjectManager, lastCamera));
	if (!camera_objects || !lastCamera_object)
		return false;

	if (!(this->offsets.fpsCamera = GetObjectFromList(camera_objects, lastCamera_object, _xor_("FPS Camera"))))
		return false;

	/*
	auto tagged_objects = mem->Read<std::array<uint64_t, 2>>(this->offsets.gameObjectManager + offsetof(EFTStructs::GameObjectManager, lastTaggedObject));
	if (!tagged_objects[0] || !tagged_objects[1])
		return false;

	if (!(this->offsets.fpsCamera = GetObjectFromList(tagged_objects[1], tagged_objects[0], _xor_("FPS Camera"))))
		return false;
	*/

	//std::cout << "--------------END InitOffsets()--------------\n";
	return true;

}

bool EFTData::UpdatePlayerList() {
    int playercount = (int)mem->ReadChain(this->offsets.gameWorld, { 0x30, 0x18, 0x28, 0x80, 0x18 });

}

bool EFTData::refreshPlayerCount() {
    uint64_t registeredPlayers = mem->Read<uint64_t>(this->offsets.localGameWorld + this->offsets.localGameWorld_offsets.registeredPlayers);
    if (!registeredPlayers)
        return false;

    uint64_t list_base = mem->Read<uint64_t>(registeredPlayers + offsetof(EFTStructs::List, listBase));
    int playerCount = mem->Read<int>(registeredPlayers + offsetof(EFTStructs::List, itemCount));

    if (playerCount == this->playercount) {
        return true;
    }
    else {
        this->playercount = playerCount;
        return false;
    }
}

FVector EFTData::GetPosition(uint64_t posAddr)
{
	Vector3 pos = mem->Read<Vector3>(posAddr);
	return FVector(pos.x, pos.y, pos.z);
}

//may need to comeback and rotate this angle
float EFTData::GetLookingAngle(uint64_t player)
{
    uint64_t mContext = mem->Read<uint64_t>(player + this->offsets.Player.movementContext);
    Vector2 angles = mem->Read<Vector2>(mContext + this->offsets.movement.direction); //(+/- 360 , +/- 1)
    float angle = angles.x; /// +/- 360

    if (angle < 0) {
        angle = 360 + angle;
    }

    //std::cout << angle << std::endl;
    return angle;
}

std::string getBotType(int role) {
    switch (role)
    {
    case WildSpawnType::marksman:
        return ("Marksman");
    case WildSpawnType::assault:
        return ("Assault");
    case WildSpawnType::bossTest:
        return ("Boss Test");
    case WildSpawnType::bossBully:
        return ("Boss Bully");
    case WildSpawnType::followerTest:
        return ("Follower Test");
    case WildSpawnType::followerBully:
        return ("Follower Bully");
    case WildSpawnType::bossKilla:
        return ("Boss Killa");
    case WildSpawnType::bossKojaniy:
        return ("Boss Kojaniy");
    case WildSpawnType::followerKojaniy:
        return ("Follower Kojaniy");
    case WildSpawnType::pmcBot:
        return ("Raider");
    case WildSpawnType::cursedAssault:
        return ("Cursed Assault");
    case WildSpawnType::bossGluhar:
        return ("Boss Gluhar");
    case WildSpawnType::followerGluharAssault:
        return ("Follower Gluhar Assault");
    case WildSpawnType::followerGluharSecurity:
        return ("Follower Gluhar Security");
    case WildSpawnType::followerGluharScout:
        return ("Follower Gluhar Scout");
    case WildSpawnType::followerGluharSnipe:
        return ("Follower Gluhar Snipe");
    case WildSpawnType::followerSanitar:
        return ("Follower Sanitar");
    case WildSpawnType::bossSanitar:
        return ("Boss Sanitar");
    case WildSpawnType::test:
        return ("Test");
    case WildSpawnType::assaultGroup:
        return ("Assault Group");
    case WildSpawnType::sectantWarrior:
        return ("Sectant Warrior");
    case WildSpawnType::sectantPriest:
        return ("Sectant Priest");
    case WildSpawnType::bossTagilla:
        return ("Boss Tagilla");
    case WildSpawnType::followerTagilla:
        return ("Follower Tagilla");
    case WildSpawnType::exUsec:
        return ("Ex Usec");
    default:
        return("Unknown scav");
    }
}

FVector EFTData::getBonePos(uint64_t player,int boneId) {

    uint64_t playerBody = mem->Read<uint64_t>(player + this->offsets.Player.playerBody);
    uint64_t skeleton = mem->Read<uint64_t>(playerBody + this->offsets.Playerbody.SkeletonRootJoint);
    uint64_t values = mem->Read<uint64_t>(skeleton + this->offsets.Skeleton.values);
    uint64_t BoneList = mem->Read<uint64_t>(values + offsetof(EFTStructs::List, listBase)) + offsetof(EFTStructs::ListInternal, firstEntry); //Listbase then first entry 0x10] + 0x20
    uint64_t bone = mem->Read<uint64_t>(BoneList + 0x8 * boneId);
    uint64_t boneTransform = mem->ReadChain(bone, { 0x10,0x38 });   //idk where these offsets come from
    Vector3  boneCords = mem->Read<Vector3>(boneTransform + transformPos);

    //std::cout << boneCords.x << " , " << boneCords.y << std::endl;
    return FVector(boneCords.x, boneCords.y, boneCords.z);
}

bool EFTData::setupPlayer(uint64_t playerAddress) {
    EFTPlayer player;
    player.instance = playerAddress;


    uint64_t playerProfile = mem->Read<uint64_t>(playerAddress + this->offsets.Player.profile);
    uint64_t playerInfo = mem->Read<uint64_t>(playerProfile + this->offsets.profile.information);
    uint64_t playerName = mem->Read<uint64_t>(playerInfo + this->offsets.information.playerName);


    int registrationDate = mem->Read<int>(playerInfo + this->offsets.information.registrationDate);
    int playerSide = mem->Read<int>(playerInfo + this->offsets.information.playerSide);

    player.position = this->GetPosition(player.instance + this->offsets.Player.position);
    player.headPos  = this->getBonePos(player.instance, Bones::HumanBase);//currently setting player.position to head position

    if (playerName && registrationDate > 0) //controlled by an actual human
    {
        int32_t nameLength = mem->Read<int32_t>(playerName + this->offsets.unicodeString.length);
        if (nameLength > 128)
            return false;
        player.name = wstring_to_string(readWCharString((DWORD64)(playerName + this->offsets.unicodeString.stringBase), (int)nameLength));

        switch (playerSide) {
        case 1:
            player.type = "usec";
            break;
        case 2:
            player.type = "bear";
            break;
        default:
            player.type = "player";
            break;
        }
    }
    else if (playerName) {  //an AI
        uint64_t settings = mem->Read<uint64_t>(playerInfo + this->offsets.information.settings);
        int32_t role = mem->Read<int32_t>(settings + this->offsets.settings.role);
        std::string SpawnType = getBotType(role);
        //std::cout << "Type:\t" << SpawnType << std::endl;
        player.type = SpawnType;
    }

    // Leave this at the end to have all the data.
    if (mem->Read<int>(player.instance + 0x18))
    {
        std::cout << player.position.x << " " << player.position.y << " " << player.position.z << std::endl;
        std::cout << player.headPos.x << " " << player.headPos.y << " " << player.headPos.z << "\n\n\n" << std::endl;

        //player.lookAngle = this->GetLookingAngle(mem->Read<Vector4>(player.instance + this->offsets.Player.looking));
        //std::cout << player.name << std::endl;
        player.lookAngle = this->GetLookingAngle(player.instance);
        this->localPlayer = player;
        this->localPlayer.position = player.position;
    }
    else {
        this->players.emplace_back(player);
    }
    return true;
}


/*
FVector EFTData::GetPosition(uint64_t transform)
{
	auto transform_internal = mem->Read<uint64_t>(transform + 0x10);

	auto matrices = mem->Read<uint64_t>(transform_internal + 0x38);
	auto index = mem->Read<int>(transform_internal + 0x40);

	mem->ReadBuffer((uintptr_t)(matrices + 0x18), &matrix_list_base, sizeof(matrix_list_base));

	mem->ReadBuffer((uintptr_t)(matrices + 0x20), &dependency_index_table_base, sizeof(dependency_index_table_base));

	static auto get_dependency_index = [this](uint64_t base, int32_t index)
	{
		mem->ReadBuffer((uintptr_t)(base + index * 4), &index, sizeof(index));
		return index;
	};

	static auto get_matrix_blob = [this](uint64_t base, uint64_t offs, float* blob, uint32_t size) {
		mem->ReadBuffer((uintptr_t)(base + offs), blob, size);
	};

	int32_t index_relation = get_dependency_index(dependency_index_table_base, index);

	FVector ret_value;
	{
		float* base_matrix3x4 = (float*)malloc(64),
			* matrix3x4_buffer0 = (float*)((uint64_t)base_matrix3x4 + 16),
			* matrix3x4_buffer1 = (float*)((uint64_t)base_matrix3x4 + 32),
			* matrix3x4_buffer2 = (float*)((uint64_t)base_matrix3x4 + 48);

		get_matrix_blob(matrix_list_base, index * 48, base_matrix3x4, 16);

		__m128 xmmword_1410D1340 = { -2.f, 2.f, -2.f, 0.f };
		__m128 xmmword_1410D1350 = { 2.f, -2.f, -2.f, 0.f };
		__m128 xmmword_1410D1360 = { -2.f, -2.f, 2.f, 0.f };

		while (index_relation >= 0)
		{
			uint32_t matrix_relation_index = 6 * index_relation;

			// paziuret kur tik 3 nureadina, ten translationas, kur 4 = quatas ir yra rotationas.
			get_matrix_blob(matrix_list_base, 8 * matrix_relation_index, matrix3x4_buffer2, 16);
			__m128 v_0 = *(__m128*)matrix3x4_buffer2;

			get_matrix_blob(matrix_list_base, 8 * matrix_relation_index + 32, matrix3x4_buffer0, 16);
			__m128 v_1 = *(__m128*)matrix3x4_buffer0;

			get_matrix_blob(matrix_list_base, 8 * matrix_relation_index + 16, matrix3x4_buffer1, 16);
			__m128i v9 = *(__m128i*)matrix3x4_buffer1;

			__m128* v3 = (__m128*)base_matrix3x4; // r10@1
			__m128 v10; // xmm9@2
			__m128 v11; // xmm3@2
			__m128 v12; // xmm8@2
			__m128 v13; // xmm4@2
			__m128 v14; // xmm2@2
			__m128 v15; // xmm5@2
			__m128 v16; // xmm6@2
			__m128 v17; // xmm7@2

			v10 = _mm_mul_ps(v_1, *v3);
			v11 = _mm_castsi128_ps(_mm_shuffle_epi32(v9, 0));
			v12 = _mm_castsi128_ps(_mm_shuffle_epi32(v9, 85));
			v13 = _mm_castsi128_ps(_mm_shuffle_epi32(v9, -114));
			v14 = _mm_castsi128_ps(_mm_shuffle_epi32(v9, -37));
			v15 = _mm_castsi128_ps(_mm_shuffle_epi32(v9, -86));
			v16 = _mm_castsi128_ps(_mm_shuffle_epi32(v9, 113));

			v17 = _mm_add_ps(
				_mm_add_ps(
					_mm_add_ps(
						_mm_mul_ps(
							_mm_sub_ps(
								_mm_mul_ps(_mm_mul_ps(v11, (__m128)xmmword_1410D1350), v13),
								_mm_mul_ps(_mm_mul_ps(v12, (__m128)xmmword_1410D1360), v14)),
							_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(v10), -86))),
						_mm_mul_ps(
							_mm_sub_ps(
								_mm_mul_ps(_mm_mul_ps(v15, (__m128)xmmword_1410D1360), v14),
								_mm_mul_ps(_mm_mul_ps(v11, (__m128)xmmword_1410D1340), v16)),
							_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(v10), 85)))),
					_mm_add_ps(
						_mm_mul_ps(
							_mm_sub_ps(
								_mm_mul_ps(_mm_mul_ps(v12, (__m128)xmmword_1410D1340), v16),
								_mm_mul_ps(_mm_mul_ps(v15, (__m128)xmmword_1410D1350), v13)),
							_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(v10), 0))),
						v10)),
				v_0);

			*v3 = v17;

			index_relation = get_dependency_index(dependency_index_table_base, index_relation);
		}

		ret_value = *(FVector*)base_matrix3x4;
		delete[] base_matrix3x4;
	}

	return ret_value;
}
*/

//sets up players and extracts
bool EFTData::Read() {
	//std::cout << "--------------IN READ()--------------\n";

    /*
    * 
    *          SETUP ALL PLAYERS
    * 
    */

	this->players.clear();
	{
	uint64_t registeredPlayers = mem->Read<uint64_t>(this->offsets.localGameWorld + this->offsets.localGameWorld_offsets.registeredPlayers);
	if (!registeredPlayers)
		return false;

	uint64_t list_base = mem->Read<uint64_t>(registeredPlayers + offsetof(EFTStructs::List, listBase));
	int playerCount = mem->Read<int>(registeredPlayers + offsetof(EFTStructs::List, itemCount));
	if (playerCount <= 0 || !list_base)
		return false;
	//std::cout << "PlayerCount: " << playerCount << std::endl;

	constexpr auto BUFFER_SIZE = 128;

	uint64_t player_buffer[BUFFER_SIZE];
	mem->ReadBuffer(list_base + offsetof(EFTStructs::ListInternal, firstEntry), player_buffer, sizeof(uint64_t) * playerCount);

	for (int i = 0; i < playerCount; i++) { //loop through all players... bots, pmc, bosses, etc..
		this->setupPlayer(mem->Read<uint64_t>(list_base + offsetof(EFTStructs::ListInternal, firstEntry) + i * sizeof(uint64_t)));    
	}

	}
	
    /*
    *
    *          SETUP ALL EXTRACTS
    *
    */

	this->extracts.clear();
	{
	uint64_t exit_controller = mem->Read<uint64_t>(this->offsets.localGameWorld + 0x18);

	if (!exit_controller)
		return false;

	uint64_t exit_point = mem->Read<uint64_t>(exit_controller + 0x20);
	int exit_count = mem->Read<int>(exit_point + 0x18);

	if (exit_count <= 0 || !exit_point)
		return false;

	constexpr auto BUFFER_SIZE = 24;

	uint64_t extract_buffer[BUFFER_SIZE];
	ReadBuffer(exit_point + offsetof(EFTStructs::ListInternal, firstEntry), extract_buffer, exit_count);

	EFTExtract extract;

	for (int i = 0; i < exit_count; i++)
	{
		extract.instance = extract_buffer[i];
		
		if (!EFTData::Instance()->open_extract(extract.instance))
			continue;

		uint64_t transform = mem->ReadChain(extract.instance, { 0x10, 0x30, 0x30, 0x8, 0x28 });
		//extract.location = GetPosition(transform);

		uint64_t extract_name = mem->ReadChain(extract.instance, { 0x58, 0x10 });
		if (extract_name)
		{
			int32_t nameLength = mem->Read<int32_t>(extract_name + this->offsets.unicodeString.length);
			extract.name = wstring_to_string(readWCharString((DWORD64)(extract_name + this->offsets.unicodeString.stringBase), (int)nameLength));
			//std::cout << extract.name << std::endl;
		}

		this->extracts.emplace_back(extract);

	}
	}
	
	//std::cout << "--------------END READ()--------------\n";
}

std::string findItemID(uint64_t itemInstance) {
	uint64_t itemClass = mem->Read<uint64_t>(itemInstance + oItemClass);
	uint64_t itemProfile = mem->Read<uint64_t>(itemClass + oItemProfile);
	uint64_t itemIDClass = mem->Read<uint64_t>(itemProfile + oItemID);
	int IDLength = mem->Read<int>(itemIDClass + oIDLength);
	std::string itemId = wstring_to_string(readWCharString((DWORD64)(itemIDClass + oItemIDString), IDLength));
	return itemId;
}

std::string readStringFromMem(uint64_t stringAddr) {
	std::array<char, 64> name_buffer;
	name_buffer = mem->Read<std::array<char, 64>>(stringAddr);
	name_buffer[63] = '\0';
	return name_buffer.data();
}

bool EFTData::loopThroughList() {
	//std::cout << "--------------BEGIN loopThroughList()--------------\n";

    /*
    *
    *          SETUP ALL LOOT
    *
    */

    this->lootDict = {};//clear lootdict
	uint64_t lootListOuter = mem->Read<uint64_t>(this->offsets.localGameWorld + this->offsets.localGameWorld_offsets.lootList);	//0x60
	int lootCount = mem->Read<uint64_t>(lootListOuter + offsetof(EFTStructs::List, itemCount));
	uint64_t lootList = mem->Read<uint64_t>(lootListOuter + offsetof(EFTStructs::List, listBase));	//0x10

	constexpr auto BUFFER_SIZE = 2000;
	uint64_t lootBuffer[BUFFER_SIZE];
	ReadBuffer(lootList + offsetof(EFTStructs::ListInternal, firstEntry), lootBuffer, lootCount);//0x20


    //Begin looping through all loot
	EFTLoot loot;
	std::array<char, 64> name_buffer;
	for (int i = 0; i < lootCount; i++)
	{
		loot.instance = lootBuffer[i];
		uint64_t transform = mem->ReadChain(loot.instance, { 0x10, 0x30, 0x30, 0x8, 0x38 });
		loot.origin = mem->Read<Vector3>(transform + 0x90);
		uint64_t lootName = mem->ReadChain(loot.instance, { 0x10, 0x30,0x60 });
		if (lootName)
		{
            loot.name = readStringFromMem(lootName);
			std::string isContainer = readStringFromMem(mem->ReadChain(loot.instance, { 0x0, 0x0, 0x48 }));
			

            //Check loot types
            if (isContainer.compare("LootableContainer") == 0) {
				//std::cout << "Item is a lootable container" << std::endl;
			}
			else if (isContainer.compare("Corpse") == 0) {
				//std::cout << "Item is a corpse" << std::endl;

			}
            else if (loot.name.compare("Script") == 0) {
                //std::cout << "Item is a Script" << std::endl;
            }
            else if (loot.name.find("quest") != std::string::npos) {
                //std::cout << "Item is a Quest" << std::endl;
            }
            else {
                loot.id = findItemID(loot.instance);
                if (!this->ItemIdDict[loot.id].empty()) {   //if the item id isn't in our itemIdDictionary use default name
                    loot.name = this->ItemIdDict[loot.id];
                }
            }
            
            //At to the lootdictionary we are storing
			if (this->lootDict.count(loot.name) == 0) {
				std::vector<EFTLoot> lootVec;
				lootVec.push_back(loot);
				this->lootDict.insert({ loot.name, lootVec });
			}
			else {
				this->lootDict[loot.name].push_back(loot);
			}

		}
		this->loots.emplace_back(loot);

	}
    //std::cout << "-----------------------------END LOOTLOOP---------------------\n\n\n\n";
	return true;
}

uint64_t EFTData::GetObjectFromList(uint64_t listPtr, uint64_t lastObjectPtr, const char* objectName)
{

    /*
    *
    *          FIND THE GAMEWORLD
    *
    */

	using EFTStructs::BaseObject;
	char name[256];
	uint64_t classNamePtr = 0x0;
	BaseObject activeObject = mem->Read<BaseObject>(listPtr);
	BaseObject lastObject = mem->Read<BaseObject>(lastObjectPtr);
	int c = 0;

	if (activeObject.object != 0x0)
	{
		while (activeObject.object != 0 && activeObject.object != lastObject.object)
		{
			classNamePtr = mem->Read<uint64_t>(activeObject.object + 0x60);
			//mem->ReadBuffer(classNamePtr + 0x0, &name, sizeof(name));
			std::string result = readCharString(classNamePtr, 255);
			if (strcmp(result.c_str(), objectName) == 0)
			{
				return activeObject.object;
			}

			activeObject = mem->Read<BaseObject>(activeObject.nextObjectLink);
		}
	}
	if (lastObject.object != 0x0)
	{
		classNamePtr = mem->Read<uint64_t>(lastObject.object + 0x60);
		std::string result = readCharString(classNamePtr, 255);
		if (strcmp(result.c_str(), objectName) == 0)
		{
			return lastObject.object;
		}
	}

	return uint64_t();
}

bool EFTData::IsAiming(uint64_t	 instance)
{
	uint64_t m_pbreath = mem->ReadChain(instance, { this->offsets.Player.proceduralWeaponAnimation, 0x28 });
	return mem->Read<bool>(m_pbreath + 0x88);
}

uint64_t EFTData::get_mpcamera(uint64_t instance)
{
	static std::vector<uint64_t> temp{ this->offsets.Player.proceduralWeaponAnimation, 0x88, 0x20 };

	return mem->ReadChain(instance, temp);
}

uint64_t EFTData::getbone_matrix(uint64_t instance)
{
	static std::vector<uint64_t> temp{ this->offsets.Player.playerBody, 0x28, 0x28, 0x10 };

	return mem->ReadChain(instance, temp);
}

bool EFTData::IsPlayer(uint64_t instance)
{
	static std::vector<uint64_t> tempchain{ this->offsets.Player.profile, this->offsets.profile.information };

	uint64_t information = mem->ReadChain(instance, tempchain);

	if (mem->Read<int32_t>(information + 0x54) != 0)
		return true;

	return false;
}

bool EFTData::open_extract(uint64_t extract)
{
	if (!extract)
		return false;

	int32_t status = mem->Read<int32_t>(extract + 0xA8); /* NotOpen = 1// Imcpmpleterequirement = 2 // Countdown = 3 // Open = 4 // Pending = 5 // Awaot ,amial Activation = 6*/

	if (status == 4)
		return true;


	return false;
}



/*
	for (int i = 0; i <= EntityCount; i++)
	{
		DWORD64 Entity = mem->Read<DWORD64>(EntityBuffer + 0x20 + (i * 0x8));
		if (Entity <= 100000) continue;
		DWORD64 Object = mem->Read<DWORD64>(Entity + 0x10);
		if (Object <= 100000) continue;
		DWORD64 ObjectClass = mem->Read<DWORD64>(Object + 0x30);
		if (ObjectClass <= 100000) continue;
		DWORD64 ObjectName = mem->Read<DWORD64>(ObjectClass + 0x60);
		std::string name = readCharString(ObjectName, 30);
		if (name.find(std::string("Local")) != std::string::npos) {//if local is contained in class name
			//printf("\nName: %s\n", name.c_str());
			BasePlayer* Player = (BasePlayer*)mem->Read<DWORD64>(Object + 0x28);

			if (!mem->Read<DWORD64>(mem->Read<DWORD64>(Object + 0x28) + 0x50) || mem->Read<bool>(mem->Read<DWORD64>(Object + 0x28) + 0x18) || !mem->Read<DWORD64>(mem->Read<DWORD64>(Object + 0x28) + oPlayerModel)) continue;
			if (Player != LocalPlayer.BasePlayer) {
				//printf("LocalPlayer %lld\n", Player->GetSteamID());
				mfound = false;
			}

			//Vector3 pos = Player->GetPosition();
			//printf("lp pos %f %f %f\n", pos.x, pos.y, pos.z);
			LocalPlayer.BasePlayer = Player;
			//printf("LocalPlayer %lld\n", Player->GetSteamID());
			LP_isValid = true;

			//once LP is found break out of for loop - Decreases LAG
			break;
		}
	}
	*/

	/*
		//lootlist: local + 0x58

		//itemList: lootlist + 0x10
		//count: lootlist + 0x18

		//firstItem: itemList + 0x20			aka lootList + 0x58] 0x10] 0x20]
		//secondItem: itemList + 0x28			aka lootList + 0x58] 0x10] 0x28]

		//GameObject: firstItem + 0x10] 0x30] 0x60]

		//
		//print loot
		DWORD64 lootList = mem->Read<DWORD64>(this->offsets.localGameWorld + 0x58);
		DWORD64 itemList = mem->Read<DWORD64>(lootList + 0x10);
		auto loot_objects = mem->Read<std::array<uint64_t, 2>>(itemList + 0x28);
		int lootCount = mem->Read<int>(lootList + 0x18);

		GetObjectFromList(loot_objects[1], loot_objects[0], _xor_("LedX"));
		*/