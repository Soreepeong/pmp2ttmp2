#pragma once

#include <cinttypes>
#include <map>
#include <set>
#include <string>

#include <nlohmann/json_fwd.hpp>

namespace penumbra {
	typedef uint32_t ModelCharaId;
	typedef uint32_t BNpcId;
	typedef uint32_t ENpcId;
	typedef uint32_t BNpcNameId;
	typedef uint32_t MountId;
	typedef uint32_t CompanionId;
	typedef uint32_t OrnamentId;
	typedef uint32_t NpcId;
	typedef uint16_t SecondaryId;
	typedef uint16_t PrimaryId;
	typedef uint8_t Variant;
	typedef uint8_t StainId;
	typedef StainId StainIds;
	typedef uint16_t BonusItemId;
	typedef uint32_t ItemId;
	typedef uint64_t CustomItemId;
	typedef uint32_t IconId;
	typedef uint16_t WorldId;
	typedef uint8_t JobId;
	typedef uint8_t JobGroupId;
	typedef uint8_t CharacterLevel;
	typedef uint16_t ObjectIndex;

	enum class EstType : uint8_t {
		Unknown = 0,
		Hair = 72,
		Face = 73,
		Body = 74,
		Head = 75,
	};

	enum class BodySlot : uint8_t {
		Unknown,
		Hair,
		Face,
		Tail,
		Body,
		Ear,
	};

	enum class EquipSlot : uint8_t {
		Unknown = 0,
		MainHand = 1,
		OffHand = 2,
		Head = 3,
		Body = 4,
		Hands = 5,
		Belt = 6,
		Legs = 7,
		Feet = 8,
		Ears = 9,
		Neck = 10,
		Wrists = 11,
		RFinger = 12,
		BothHand = 13,
		LFinger = 14,
		HeadBody = 15,
		BodyHandsLegsFeet = 16,
		SoulCrystal = 17,
		LegsFeet = 18,
		FullBody = 19,
		BodyHands = 20,
		BodyLegsFeet = 21,
		ChestHands = 22,
		Nothing = 23,
		All = 24,
	};

	enum class FileType : uint8_t {
		Unknown,
		Sound,
		Imc,
		Vfx,
		Animation,
		Pap,
		MetaInfo,
		Material,
		Texture,
		Model,
		Shader,
		Font,
		Environment,
	};

	enum class ObjectType : uint8_t {
		Unknown,
		Vfx,
		DemiHuman,
		Accessory,
		World,
		Housing,
		Monster,
		Icon,
		LoadingScreen,
		Map,
		Interface,
		Equipment,
		Character,
		Weapon,
		Font,
	};

	enum class Race : uint8_t {
		Unknown,
		Hyur,
		Elezen,
		Lalafell,
		Miqote,
		Roegadyn,
		AuRa,
		Hrothgar,
		Viera,
	};

	enum class Gender : uint8_t {
		Unknown,
		Male,
		Female,
		MaleNpc,
		FemaleNpc,
	};

	enum class ModelRace : uint8_t {
		Unknown,
		Midlander,
		Highlander,
		Elezen,
		Lalafell,
		Miqote,
		Roegadyn,
		AuRa,
		Hrothgar,
		Viera,
	};

	enum class SubRace : uint8_t {
		Unknown,
		Midlander,
		Highlander,
		Wildwood,
		Duskwight,
		Plainsfolk,
		Dunesfolk,
		SeekerOfTheSun,
		KeeperOfTheMoon,
		Seawolf,
		Hellsguard,
		Raen,
		Xaela,
		Helion,
		Lost,
		Rava,
		Veena,
	};

	enum class GenderRace : uint16_t {
		Unknown = 0,
		MidlanderMale = 101,
		MidlanderMaleNpc = 104,
		MidlanderFemale = 201,
		MidlanderFemaleNpc = 204,
		HighlanderMale = 301,
		HighlanderMaleNpc = 304,
		HighlanderFemale = 401,
		HighlanderFemaleNpc = 404,
		ElezenMale = 501,
		ElezenMaleNpc = 504,
		ElezenFemale = 601,
		ElezenFemaleNpc = 604,
		MiqoteMale = 701,
		MiqoteMaleNpc = 704,
		MiqoteFemale = 801,
		MiqoteFemaleNpc = 804,
		RoegadynMale = 901,
		RoegadynMaleNpc = 904,
		RoegadynFemale = 1001,
		RoegadynFemaleNpc = 1004,
		LalafellMale = 1101,
		LalafellMaleNpc = 1104,
		LalafellFemale = 1201,
		LalafellFemaleNpc = 1204,
		AuRaMale = 1301,
		AuRaMaleNpc = 1304,
		AuRaFemale = 1401,
		AuRaFemaleNpc = 1404,
		HrothgarMale = 1501,
		HrothgarMaleNpc = 1504,
		HrothgarFemale = 1601,
		HrothgarFemaleNpc = 1604,
		VieraMale = 1701,
		VieraMaleNpc = 1704,
		VieraFemale = 1801,
		VieraFemaleNpc = 1804,
		UnknownMaleNpc = 9104,
		UnknownFemaleNpc = 9204,
	};

	enum class RspAttribute : uint8_t {
		MaleMinSize,
		MaleMaxSize,
		MaleMinTail,
		MaleMaxTail,
		FemaleMinSize,
		FemaleMaxSize,
		FemaleMinTail,
		FemaleMaxTail,
		BustMinX,
		BustMinY,
		BustMinZ,
		BustMaxX,
		BustMaxY,
		BustMaxZ,
		NumAttributes,
	};

	enum class GlobalEqpType {
		DoNotHideEarrings,
		DoNotHideNecklace,
		DoNotHideBracelets,
		DoNotHideRingR,
		DoNotHideRingL,
		DoNotHideHrothgarHats,
		DoNotHideVieraHats,
	};

	enum class EqdpEntry : uint16_t {
		Invalid = 0,
		Head1 = 0b0000000001,
		Head2 = 0b0000000010,
		HeadMask = 0b0000000011,

		Body1 = 0b0000000100,
		Body2 = 0b0000001000,
		BodyMask = 0b0000001100,

		Hands1 = 0b0000010000,
		Hands2 = 0b0000100000,
		HandsMask = 0b0000110000,

		Legs1 = 0b0001000000,
		Legs2 = 0b0010000000,
		LegsMask = 0b0011000000,

		Feet1 = 0b0100000000,
		Feet2 = 0b1000000000,
		FeetMask = 0b1100000000,

		Ears1 = 0b0000000001,
		Ears2 = 0b0000000010,
		EarsMask = 0b0000000011,

		Neck1 = 0b0000000100,
		Neck2 = 0b0000001000,
		NeckMask = 0b0000001100,

		Wrists1 = 0b0000010000,
		Wrists2 = 0b0000100000,
		WristsMask = 0b0000110000,

		RingR1 = 0b0001000000,
		RingR2 = 0b0010000000,
		RingRMask = 0b0011000000,

		RingL1 = 0b0100000000,
		RingL2 = 0b1000000000,
		RingLMask = 0b1100000000,

		FullMask = 0b1111111111,
	};

	enum class EqpEntry : uint64_t {
		BodyEnabled = 0x00'01ull,
		BodyHideWaist = 0x00'02ull,
		BodyHideThighs = 0x00'04ull,
		BodyHideGlovesS = 0x00'08ull,
		Unk4 = 0x00'10ull,
		BodyHideGlovesM = 0x00'20ull,
		BodyHideGlovesL = 0x00'40ull,
		BodyHideGorget = 0x00'80ull,
		BodyShowLeg = 0x01'00ull,
		BodyShowHand = 0x02'00ull,
		BodyShowHead = 0x04'00ull,
		BodyShowNecklace = 0x08'00ull,
		BodyShowBracelet = 0x10'00ull,
		BodyShowTail = 0x20'00ull,
		BodyDisableBreastPhysics = 0x40'00ull,
		BodyUsesEvpTable = 0x80'00ull,
		BodyMask = 0xFF'FFull,

		LegsEnabled = 0x01ull << 16,
		LegsHideKneePads = 0x02ull << 16,
		LegsHideBootsS = 0x04ull << 16,
		LegsHideBootsM = 0x08ull << 16,
		Unk20 = 0x10ull << 16,
		LegsShowFoot = 0x20ull << 16,
		LegsShowTail = 0x40ull << 16,
		Unk23 = 0x80ull << 16,
		LegsMask = 0xFFull << 16,

		HandsEnabled = 0x01ull << 24,
		HandsHideElbow = 0x02ull << 24,
		HandsHideForearm = 0x04ull << 24,
		Unk27 = 0x08ull << 24,
		HandShowBracelet = 0x10ull << 24,
		HandShowRingL = 0x20ull << 24,
		HandShowRingR = 0x40ull << 24,
		Unk31 = 0x80ull << 24,
		HandsMask = 0xFFull << 24,

		FeetEnabled = 0x01ull << 32,
		FeetHideKnee = 0x02ull << 32,
		FeetHideCalf = 0x04ull << 32,
		FeetHideAnkle = 0x08ull << 32,
		Unk36 = 0x10ull << 32,
		Unk37 = 0x20ull << 32,
		Unk38 = 0x40ull << 32,
		Unk39 = 0x80ull << 32,
		FeetMask = 0xFFull << 32,

		HeadEnabled = 0x00'00'01ull << 40,
		HeadHideScalp = 0x00'00'02ull << 40,
		HeadHideHair = 0x00'00'04ull << 40,
		HeadShowHairOverride = 0x00'00'08ull << 40,
		HeadHideNeck = 0x00'00'10ull << 40,
		HeadShowNecklace = 0x00'00'20ull << 40,
		Unk46 = 0x00'00'40ull << 40,
		HeadShowEarrings = 0x00'00'80ull << 40,
		HeadShowEarringsHuman = 0x00'01'00ull << 40,
		HeadShowEarringsAura = 0x00'02'00ull << 40,
		HeadShowEarHuman = 0x00'04'00ull << 40,
		HeadShowEarMiqote = 0x00'08'00ull << 40,
		HeadShowEarAuRa = 0x00'10'00ull << 40,
		HeadShowEarViera = 0x00'20'00ull << 40,
		Unk54 = 0x00'40'00ull << 40,
		Unk55 = 0x00'80'00ull << 40,
		HeadShowHrothgarHat = 0x01'00'00ull << 40,
		HeadShowVieraHat = 0x02'00'00ull << 40,
		HeadUsesEvpTable = 0x04'00'00ull << 40,
		Unk59 = 0x08'00'00ull << 40,
		Unk60 = 0x10'00'00ull << 40,
		Unk61 = 0x20'00'00ull << 40,
		Unk62 = 0x40'00'00ull << 40,
		Unk63 = 0x80'00'00ull << 40,
		HeadMask = 0xFF'FF'FFull << 40,
	};

	enum class GroupType {
		Unknown,
		Single,
		Multi,
		Imc
	};

	enum class MetaManipulationType : uint8_t {
		Unknown = 0,
		Imc = 1,
		Eqdp = 2,
		Eqp = 3,
		Est = 4,
		Gmp = 5,
		Rsp = 6,
		GlobalEqp = 7,
	};

	NLOHMANN_JSON_SERIALIZE_ENUM(EstType, {
		{ EstType::Unknown, "Unknown" },
		{ EstType::Hair, "Hair" },
		{ EstType::Face, "Face" },
		{ EstType::Body, "Body" },
		{ EstType::Head, "Head" },
		});

	NLOHMANN_JSON_SERIALIZE_ENUM(BodySlot, {
		{ BodySlot::Unknown, "Unknown" },
		{ BodySlot::Hair, "Hair" },
		{ BodySlot::Face, "Face" },
		{ BodySlot::Tail, "Tail" },
		{ BodySlot::Body, "Body" },
		{ BodySlot::Ear, "Ear" },
		});

	NLOHMANN_JSON_SERIALIZE_ENUM(EquipSlot, {
		{ EquipSlot::Unknown, "Unknown" },
		{ EquipSlot::MainHand, "MainHand" },
		{ EquipSlot::OffHand, "OffHand" },
		{ EquipSlot::Head, "Head" },
		{ EquipSlot::Body, "Body" },
		{ EquipSlot::Hands, "Hands" },
		{ EquipSlot::Belt, "Belt" },
		{ EquipSlot::Legs, "Legs" },
		{ EquipSlot::Feet, "Feet" },
		{ EquipSlot::Ears, "Ears" },
		{ EquipSlot::Neck, "Neck" },
		{ EquipSlot::Wrists, "Wrists" },
		{ EquipSlot::RFinger, "RFinger" },
		{ EquipSlot::BothHand, "BothHand" },
		{ EquipSlot::LFinger, "LFinger" },
		{ EquipSlot::HeadBody, "HeadBody" },
		{ EquipSlot::BodyHandsLegsFeet, "BodyHandsLegsFeet" },
		{ EquipSlot::SoulCrystal, "SoulCrystal" },
		{ EquipSlot::LegsFeet, "LegsFeet" },
		{ EquipSlot::FullBody, "FullBody" },
		{ EquipSlot::BodyHands, "BodyHands" },
		{ EquipSlot::BodyLegsFeet, "BodyLegsFeet" },
		{ EquipSlot::ChestHands, "ChestHands" },
		{ EquipSlot::Nothing, "Nothing" },
		{ EquipSlot::All, "All" },
		});

	NLOHMANN_JSON_SERIALIZE_ENUM(FileType, {
		{ FileType::Unknown, "Unknown" },
		{ FileType::Sound, "Sound" },
		{ FileType::Imc, "Imc" },
		{ FileType::Vfx, "Vfx" },
		{ FileType::Animation, "Animation" },
		{ FileType::Pap, "Pap" },
		{ FileType::MetaInfo, "MetaInfo" },
		{ FileType::Material, "Material" },
		{ FileType::Texture, "Texture" },
		{ FileType::Model, "Model" },
		{ FileType::Shader, "Shader" },
		{ FileType::Font, "Font" },
		{ FileType::Environment, "Environment" },
		});

	NLOHMANN_JSON_SERIALIZE_ENUM(ObjectType, {
		{ ObjectType::Unknown, "Unknown" },
		{ ObjectType::Vfx, "Vfx" },
		{ ObjectType::DemiHuman, "DemiHuman" },
		{ ObjectType::Accessory, "Accessory" },
		{ ObjectType::World, "World" },
		{ ObjectType::Housing, "Housing" },
		{ ObjectType::Monster, "Monster" },
		{ ObjectType::Icon, "Icon" },
		{ ObjectType::LoadingScreen, "LoadingScreen" },
		{ ObjectType::Map, "Map" },
		{ ObjectType::Interface, "Interface" },
		{ ObjectType::Equipment, "Equipment" },
		{ ObjectType::Character, "Character" },
		{ ObjectType::Weapon, "Weapon" },
		{ ObjectType::Font, "Font" },
		});

	NLOHMANN_JSON_SERIALIZE_ENUM(Race, {
		{ Race::Unknown, "Unknown" },
		{ Race::Hyur, "Hyur" },
		{ Race::Elezen, "Elezen" },
		{ Race::Lalafell, "Lalafell" },
		{ Race::Miqote, "Miqote" },
		{ Race::Roegadyn, "Roegadyn" },
		{ Race::AuRa, "AuRa" },
		{ Race::Hrothgar, "Hrothgar" },
		{ Race::Viera, "Viera" },
		});

	NLOHMANN_JSON_SERIALIZE_ENUM(Gender, {
		{ Gender::Unknown, "Unknown" },
		{ Gender::Male, "Male" },
		{ Gender::Female, "Female" },
		{ Gender::MaleNpc, "MaleNpc" },
		{ Gender::FemaleNpc, "FemaleNpc" },
		});

	NLOHMANN_JSON_SERIALIZE_ENUM(ModelRace, {
		{ ModelRace::Unknown, "Unknown" },
		{ ModelRace::Midlander, "Midlander" },
		{ ModelRace::Highlander, "Highlander" },
		{ ModelRace::Elezen, "Elezen" },
		{ ModelRace::Lalafell, "Lalafell" },
		{ ModelRace::Miqote, "Miqote" },
		{ ModelRace::Roegadyn, "Roegadyn" },
		{ ModelRace::AuRa, "AuRa" },
		{ ModelRace::Hrothgar, "Hrothgar" },
		{ ModelRace::Viera, "Viera" },
		});

	NLOHMANN_JSON_SERIALIZE_ENUM(SubRace, {
		{ SubRace::Unknown, "Unknown" },
		{ SubRace::Midlander, "Midlander" },
		{ SubRace::Highlander, "Highlander" },
		{ SubRace::Wildwood, "Wildwood" },
		{ SubRace::Duskwight, "Duskwight" },
		{ SubRace::Plainsfolk, "Plainsfolk" },
		{ SubRace::Dunesfolk, "Dunesfolk" },
		{ SubRace::SeekerOfTheSun, "SeekerOfTheSun" },
		{ SubRace::KeeperOfTheMoon, "KeeperOfTheMoon" },
		{ SubRace::Seawolf, "Seawolf" },
		{ SubRace::Hellsguard, "Hellsguard" },
		{ SubRace::Raen, "Raen" },
		{ SubRace::Xaela, "Xaela" },
		{ SubRace::Helion, "Helion" },
		{ SubRace::Lost, "Lost" },
		{ SubRace::Rava, "Rava" },
		{ SubRace::Veena, "Veena" },
		});

	NLOHMANN_JSON_SERIALIZE_ENUM(GenderRace, {
		{ GenderRace::Unknown, "Unknown" },
		{ GenderRace::MidlanderMale, "MidlanderMale" },
		{ GenderRace::MidlanderMaleNpc, "MidlanderMaleNpc" },
		{ GenderRace::MidlanderFemale, "MidlanderFemale" },
		{ GenderRace::MidlanderFemaleNpc, "MidlanderFemaleNpc" },
		{ GenderRace::HighlanderMale, "HighlanderMale" },
		{ GenderRace::HighlanderMaleNpc, "HighlanderMaleNpc" },
		{ GenderRace::HighlanderFemale, "HighlanderFemale" },
		{ GenderRace::HighlanderFemaleNpc, "HighlanderFemaleNpc" },
		{ GenderRace::ElezenMale, "ElezenMale" },
		{ GenderRace::ElezenMaleNpc, "ElezenMaleNpc" },
		{ GenderRace::ElezenFemale, "ElezenFemale" },
		{ GenderRace::ElezenFemaleNpc, "ElezenFemaleNpc" },
		{ GenderRace::MiqoteMale, "MiqoteMale" },
		{ GenderRace::MiqoteMaleNpc, "MiqoteMaleNpc" },
		{ GenderRace::MiqoteFemale, "MiqoteFemale" },
		{ GenderRace::MiqoteFemaleNpc, "MiqoteFemaleNpc" },
		{ GenderRace::RoegadynMale, "RoegadynMale" },
		{ GenderRace::RoegadynMaleNpc, "RoegadynMaleNpc" },
		{ GenderRace::RoegadynFemale, "RoegadynFemale" },
		{ GenderRace::RoegadynFemaleNpc, "RoegadynFemaleNpc" },
		{ GenderRace::LalafellMale, "LalafellMale" },
		{ GenderRace::LalafellMaleNpc, "LalafellMaleNpc" },
		{ GenderRace::LalafellFemale, "LalafellFemale" },
		{ GenderRace::LalafellFemaleNpc, "LalafellFemaleNpc" },
		{ GenderRace::AuRaMale, "AuRaMale" },
		{ GenderRace::AuRaMaleNpc, "AuRaMaleNpc" },
		{ GenderRace::AuRaFemale, "AuRaFemale" },
		{ GenderRace::AuRaFemaleNpc, "AuRaFemaleNpc" },
		{ GenderRace::HrothgarMale, "HrothgarMale" },
		{ GenderRace::HrothgarMaleNpc, "HrothgarMaleNpc" },
		{ GenderRace::HrothgarFemale, "HrothgarFemale" },
		{ GenderRace::HrothgarFemaleNpc, "HrothgarFemaleNpc" },
		{ GenderRace::VieraMale, "VieraMale" },
		{ GenderRace::VieraMaleNpc, "VieraMaleNpc" },
		{ GenderRace::VieraFemale, "VieraFemale" },
		{ GenderRace::VieraFemaleNpc, "VieraFemaleNpc" },
		{ GenderRace::UnknownMaleNpc, "UnknownMaleNpc" },
		{ GenderRace::UnknownFemaleNpc, "UnknownFemaleNpc" },
		});

	NLOHMANN_JSON_SERIALIZE_ENUM(RspAttribute, {
		{ RspAttribute::MaleMinSize, "MaleMinSize" },
		{ RspAttribute::MaleMaxSize, "MaleMaxSize" },
		{ RspAttribute::MaleMinTail, "MaleMinTail" },
		{ RspAttribute::MaleMaxTail, "MaleMaxTail" },
		{ RspAttribute::FemaleMinSize, "FemaleMinSize" },
		{ RspAttribute::FemaleMaxSize, "FemaleMaxSize" },
		{ RspAttribute::FemaleMinTail, "FemaleMinTail" },
		{ RspAttribute::FemaleMaxTail, "FemaleMaxTail" },
		{ RspAttribute::BustMinX, "BustMinX" },
		{ RspAttribute::BustMinY, "BustMinY" },
		{ RspAttribute::BustMinZ, "BustMinZ" },
		{ RspAttribute::BustMaxX, "BustMaxX" },
		{ RspAttribute::BustMaxY, "BustMaxY" },
		{ RspAttribute::BustMaxZ, "BustMaxZ" },
		{ RspAttribute::NumAttributes, "NumAttributes" },
		});

	NLOHMANN_JSON_SERIALIZE_ENUM(GlobalEqpType, {
		{ GlobalEqpType::DoNotHideEarrings, "DoNotHideEarrings" },
		{ GlobalEqpType::DoNotHideNecklace, "DoNotHideNecklace" },
		{ GlobalEqpType::DoNotHideBracelets, "DoNotHideBracelets" },
		{ GlobalEqpType::DoNotHideRingR, "DoNotHideRingR" },
		{ GlobalEqpType::DoNotHideRingL, "DoNotHideRingL" },
		{ GlobalEqpType::DoNotHideHrothgarHats, "DoNotHideHrothgarHats" },
		{ GlobalEqpType::DoNotHideVieraHats, "DoNotHideVieraHats" },
		});

	NLOHMANN_JSON_SERIALIZE_ENUM(EqdpEntry, {
		{ EqdpEntry::Invalid, "Invalid" },
		{ EqdpEntry::Head1, "Head1" },
		{ EqdpEntry::Head2, "Head2" },
		{ EqdpEntry::HeadMask, "HeadMask" },

		{ EqdpEntry::Body1, "Body1" },
		{ EqdpEntry::Body2, "Body2" },
		{ EqdpEntry::BodyMask, "BodyMask" },

		{ EqdpEntry::Hands1, "Hands1" },
		{ EqdpEntry::Hands2, "Hands2" },
		{ EqdpEntry::HandsMask, "HandsMask" },

		{ EqdpEntry::Legs1, "Legs1" },
		{ EqdpEntry::Legs2, "Legs2" },
		{ EqdpEntry::LegsMask, "LegsMask" },

		{ EqdpEntry::Feet1, "Feet1" },
		{ EqdpEntry::Feet2, "Feet2" },
		{ EqdpEntry::FeetMask, "FeetMask" },

		{ EqdpEntry::Ears1, "Ears1" },
		{ EqdpEntry::Ears2, "Ears2" },
		{ EqdpEntry::EarsMask, "EarsMask" },

		{ EqdpEntry::Neck1, "Neck1" },
		{ EqdpEntry::Neck2, "Neck2" },
		{ EqdpEntry::NeckMask, "NeckMask" },

		{ EqdpEntry::Wrists1, "Wrists1" },
		{ EqdpEntry::Wrists2, "Wrists2" },
		{ EqdpEntry::WristsMask, "WristsMask" },

		{ EqdpEntry::RingR1, "RingR1" },
		{ EqdpEntry::RingR2, "RingR2" },
		{ EqdpEntry::RingRMask, "RingRMask" },

		{ EqdpEntry::RingL1, "RingL1" },
		{ EqdpEntry::RingL2, "RingL2" },
		{ EqdpEntry::RingLMask, "RingLMask" },

		{ EqdpEntry::FullMask, "FullMask" },
		});

	NLOHMANN_JSON_SERIALIZE_ENUM(EqpEntry, {
		{ EqpEntry::BodyEnabled, "BodyEnabled" },
		{ EqpEntry::BodyHideWaist, "BodyHideWaist" },
		{ EqpEntry::BodyHideThighs, "BodyHideThighs" },
		{ EqpEntry::BodyHideGlovesS, "BodyHideGlovesS" },
		{ EqpEntry::Unk4, "Unk4" },
		{ EqpEntry::BodyHideGlovesM, "BodyHideGlovesM" },
		{ EqpEntry::BodyHideGlovesL, "BodyHideGlovesL" },
		{ EqpEntry::BodyHideGorget, "BodyHideGorget" },
		{ EqpEntry::BodyShowLeg, "BodyShowLeg" },
		{ EqpEntry::BodyShowHand, "BodyShowHand" },
		{ EqpEntry::BodyShowHead, "BodyShowHead" },
		{ EqpEntry::BodyShowNecklace, "BodyShowNecklace" },
		{ EqpEntry::BodyShowBracelet, "BodyShowBracelet" },
		{ EqpEntry::BodyShowTail, "BodyShowTail" },
		{ EqpEntry::BodyDisableBreastPhysics, "BodyDisableBreastPhysics" },
		{ EqpEntry::BodyUsesEvpTable, "BodyUsesEvpTable" },
		{ EqpEntry::BodyMask, "BodyMask" },

		{ EqpEntry::LegsEnabled, "LegsEnabled" },
		{ EqpEntry::LegsHideKneePads, "LegsHideKneePads" },
		{ EqpEntry::LegsHideBootsS, "LegsHideBootsS" },
		{ EqpEntry::LegsHideBootsM, "LegsHideBootsM" },
		{ EqpEntry::Unk20, "Unk20" },
		{ EqpEntry::LegsShowFoot, "LegsShowFoot" },
		{ EqpEntry::LegsShowTail, "LegsShowTail" },
		{ EqpEntry::Unk23, "Unk23" },
		{ EqpEntry::LegsMask, "LegsMask" },

		{ EqpEntry::HandsEnabled, "HandsEnabled" },
		{ EqpEntry::HandsHideElbow, "HandsHideElbow" },
		{ EqpEntry::HandsHideForearm, "HandsHideForearm" },
		{ EqpEntry::Unk27, "Unk27" },
		{ EqpEntry::HandShowBracelet, "HandShowBracelet" },
		{ EqpEntry::HandShowRingL, "HandShowRingL" },
		{ EqpEntry::HandShowRingR, "HandShowRingR" },
		{ EqpEntry::Unk31, "Unk31" },
		{ EqpEntry::HandsMask, "HandsMask" },

		{ EqpEntry::FeetEnabled, "FeetEnabled" },
		{ EqpEntry::FeetHideKnee, "FeetHideKnee" },
		{ EqpEntry::FeetHideCalf, "FeetHideCalf" },
		{ EqpEntry::FeetHideAnkle, "FeetHideAnkle" },
		{ EqpEntry::Unk36, "Unk36" },
		{ EqpEntry::Unk37, "Unk37" },
		{ EqpEntry::Unk38, "Unk38" },
		{ EqpEntry::Unk39, "Unk39" },
		{ EqpEntry::FeetMask, "FeetMask" },

		{ EqpEntry::HeadEnabled, "HeadEnabled" },
		{ EqpEntry::HeadHideScalp, "HeadHideScalp" },
		{ EqpEntry::HeadHideHair, "HeadHideHair" },
		{ EqpEntry::HeadShowHairOverride, "HeadShowHairOverride" },
		{ EqpEntry::HeadHideNeck, "HeadHideNeck" },
		{ EqpEntry::HeadShowNecklace, "HeadShowNecklace" },
		{ EqpEntry::Unk46, "Unk46" },
		{ EqpEntry::HeadShowEarrings, "HeadShowEarrings" },
		{ EqpEntry::HeadShowEarringsHuman, "HeadShowEarringsHuman" },
		{ EqpEntry::HeadShowEarringsAura, "HeadShowEarringsAura" },
		{ EqpEntry::HeadShowEarHuman, "HeadShowEarHuman" },
		{ EqpEntry::HeadShowEarMiqote, "HeadShowEarMiqote" },
		{ EqpEntry::HeadShowEarAuRa, "HeadShowEarAuRa" },
		{ EqpEntry::HeadShowEarViera, "HeadShowEarViera" },
		{ EqpEntry::Unk54, "Unk54" },
		{ EqpEntry::Unk55, "Unk55" },
		{ EqpEntry::HeadShowHrothgarHat, "HeadShowHrothgarHat" },
		{ EqpEntry::HeadShowVieraHat, "HeadShowVieraHat" },
		{ EqpEntry::HeadUsesEvpTable, "HeadUsesEvpTable" },
		{ EqpEntry::Unk59, "Unk59" },
		{ EqpEntry::Unk60, "Unk60" },
		{ EqpEntry::Unk61, "Unk61" },
		{ EqpEntry::Unk62, "Unk62" },
		{ EqpEntry::Unk63, "Unk63" },
		{ EqpEntry::HeadMask, "HeadMask" },
		});

	NLOHMANN_JSON_SERIALIZE_ENUM(GroupType, {
		{ GroupType::Unknown, "Unknown" },
		{ GroupType::Single, "Single" },
		{ GroupType::Multi, "Multi" },
		{ GroupType::Imc, "Imc" },
		});

	NLOHMANN_JSON_SERIALIZE_ENUM(MetaManipulationType, {
		{ MetaManipulationType::Unknown, "Unknown" },
		{ MetaManipulationType::Imc, "Imc" },
		{ MetaManipulationType::Eqdp, "Eqdp" },
		{ MetaManipulationType::Eqp, "Eqp" },
		{ MetaManipulationType::Est, "Est" },
		{ MetaManipulationType::Gmp, "Gmp" },
		{ MetaManipulationType::Rsp, "Rsp" },
		{ MetaManipulationType::GlobalEqp, "GlobalEqp" },
		});

	struct GlobalEqpManipulation {
		GlobalEqpType Type;
		PrimaryId Condition;

		bool operator<(const GlobalEqpManipulation& r) const {
			if (Type != r.Type) return Type < r.Type;
			if (Condition != r.Condition) return Condition < r.Condition;
			return false;
		}
	};

	struct ImcIdentifier {
		PrimaryId PrimaryId;
		Variant Variant;
		ObjectType ObjectType;
		SecondaryId SecondaryId;
		EquipSlot EquipSlot;
		BodySlot BodySlot;

		bool operator<(const ImcIdentifier& r) const {
			if (PrimaryId != r.PrimaryId) return PrimaryId < r.PrimaryId;
			if (Variant != r.Variant) return Variant < r.Variant;
			if (ObjectType != r.ObjectType) return ObjectType < r.ObjectType;
			if (SecondaryId != r.SecondaryId) return SecondaryId < r.SecondaryId;
			if (EquipSlot != r.EquipSlot) return EquipSlot < r.EquipSlot;
			if (BodySlot != r.BodySlot) return BodySlot < r.BodySlot;
			return false;
		}

		std::string GamePath() const {
			switch (ObjectType) {
				case ObjectType::Accessory: return std::format("chara/accessory/a{:04}/a{:04}.imc", PrimaryId, PrimaryId);
				case ObjectType::Equipment: return std::format("chara/equipment/e{:04}/e{:04}.imc", PrimaryId, PrimaryId);
				case ObjectType::DemiHuman: return std::format("chara/demihuman/d{:04}/obj/equipment/e{:04}/e{:04}.imc", PrimaryId, SecondaryId, SecondaryId);
				case ObjectType::Monster: return std::format("chara/monster/m{:04}/obj/body/b{:04}/b{:04}.imc", PrimaryId, SecondaryId, SecondaryId);
				case ObjectType::Weapon: return std::format("chara/weapon/w{:04}/obj/body/b{:04}/b{:04}.imc", PrimaryId, SecondaryId, SecondaryId);
				default: return "";
			}
		}
	};

	struct EqpIdentifier {
		PrimaryId SetId;
		EquipSlot Slot;

		bool operator<(const EqpIdentifier& r) const {
			if (SetId != r.SetId) return SetId < r.SetId;
			if (Slot != r.Slot) return Slot < r.Slot;
			return false;
		}
	};

	struct EqdpIdentifier {
		Gender Gender;
		ModelRace Race;
		PrimaryId SetId;
		EquipSlot Slot;

		bool operator<(const EqdpIdentifier& r) const {
			if (Gender != r.Gender) return Gender < r.Gender;
			if (Race != r.Race) return Race < r.Race;
			if (SetId != r.SetId) return SetId < r.SetId;
			if (Slot != r.Slot) return Slot < r.Slot;
			return false;
		}
	};

	struct EstIdentifier {
		Gender Gender;
		ModelRace Race;
		PrimaryId SetId;
		EstType Slot;

		bool operator<(const EstIdentifier& r) const {
			if (Gender != r.Gender) return Gender < r.Gender;
			if (Race != r.Race) return Race < r.Race;
			if (SetId != r.SetId) return SetId < r.SetId;
			if (Slot != r.Slot) return Slot < r.Slot;
			return false;
		}
	};

	struct RspIdentifier {
		SubRace SubRace;
		RspAttribute Attribute;

		bool operator<(const RspIdentifier& r) const {
			if (SubRace != r.SubRace) return SubRace < r.SubRace;
			if (Attribute != r.Attribute) return Attribute < r.Attribute;
			return false;
		}
	};

	struct GmpIdentifier {
		PrimaryId SetId;

		bool operator<(const GmpIdentifier& r) const {
			if (SetId != r.SetId) return SetId < r.SetId;
			return false;
		}
	};

	struct GlobalEqupManipulation {
		GlobalEqpType Type;
		PrimaryId Condition;

		bool operator<(const GlobalEqupManipulation& r) const {
			if (Type != r.Type) return Type < r.Type;
			if (Condition != r.Condition) return Condition < r.Condition;
			return false;
		}
	};

	struct ImcEntry {
		uint8_t MaterialId;
		uint8_t DecalId;
		uint8_t VfxId;
		uint8_t MaterialAnimationId;
		uint16_t AttributeMask;
		uint8_t SoundId;
	};

	struct GmpEntry {
		bool Enabled;
		bool Animated;
		uint16_t RotationA;
		uint16_t RotationB;
		uint16_t RotationC;
		uint8_t UnknownA;
		uint8_t UnknownB;
	};

	struct MetaDictionary {
		std::map<ImcIdentifier, ImcEntry> Imc;
		std::map<EqpIdentifier, EqpEntry> Eqp;
		std::map<EqdpIdentifier, EqdpEntry> Eqdp;
		std::map<EstIdentifier, uint16_t> Est;
		std::map<RspIdentifier, float> Rsp;
		std::map<GmpIdentifier, GmpEntry> Gmp;
		std::set<GlobalEqpManipulation> GlobalEqp;
	};

	struct GroupOption {
		std::optional<std::string> Name;
		std::optional<std::string> Description;
		std::map<std::string, std::string> Files;
		std::map<std::string, std::string> FileSwaps;
		MetaDictionary Manipulations;
	};

	struct Group {
		int Version;
		std::optional<std::string> Name;
		std::optional<std::string> Description;
		std::optional<std::string> Image;
		int Priority;
		uint64_t DefaultSettings; // flags

		GroupType Type;
		std::vector<GroupOption> Options;
	};

	struct Meta {
		int FileVersion;
		std::string Name;
		std::string Author;
		std::string Description;
		std::string Version;
		std::string Website;
		std::string Image;
		std::vector<std::string> ModTags;
	};

	// void to_json(nlohmann::json& j, const GroupOption& o);
	void from_json(const nlohmann::json& j, GroupOption& o);
	// void to_json(nlohmann::json& j, const Group& o);
	void from_json(const nlohmann::json& j, Group& o);
	// void to_json(nlohmann::json& j, const Meta& o);
	void from_json(const nlohmann::json& j, Meta& o);

	bool IsAccessory(EquipSlot value);

	std::string ToSuffix(EquipSlot value);
	std::string ToSuffix(BodySlot value);

	GenderRace CombinedRace(Gender gender, ModelRace modelRace);

	std::string ManipToPath(ImcIdentifier manip);
	std::string ManipToPath(EqdpIdentifier manip);
	std::string ManipToPath(EqpIdentifier manip);
	std::string ManipToPath(EstIdentifier manip);
	std::string ManipToPath(GmpIdentifier manip);
}
