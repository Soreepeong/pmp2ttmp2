#include "pch.h"

#include "PenumbraEnums.h"

namespace std {
	void from_json(const nlohmann::json& j, std::optional<std::string>& o) {
		o = j.is_null() ? std::optional<std::string>{} : std::optional<std::string>{ j.get<std::string>() };
	}
}

void penumbra::from_json(const nlohmann::json& j, GroupOption& o) {
	o = {
		.Name = j.value<std::optional<std::string>>("Name", {}),
		.Description = j.value<std::optional<std::string>>("Description", {}),
		.Files = j.value<std::map<std::string, std::string>>("Files", {}),
		.FileSwaps = j.value<std::map<std::string, std::string>>("FileSwaps", {}),
	};
	if (const auto mi = j.find("Manipulations"); mi != j.end() && mi->is_array()) {
		for (const auto& item : *mi) {
			const auto manip = item.find("Manipulation");
			if (!manip->is_object())
				continue;

			const auto type = item.value<MetaManipulationType>("Type", MetaManipulationType::Unknown);
			const auto entry = manip->find("Entry");
			if (entry == manip->end())
				continue;

			switch (type) {
				case MetaManipulationType::Imc:
					o.Manipulations.Imc.insert_or_assign(
						ImcIdentifier{
							.PrimaryId = manip->value<PrimaryId>("PrimaryId", {}),
							.Variant = manip->value<Variant>("Variant", {}),
							.ObjectType = manip->value<ObjectType>("ObjectType", {}),
							.SecondaryId = manip->value<SecondaryId>("SecondaryId", {}),
							.EquipSlot = manip->value<EquipSlot>("EquipSlot", {}),
							.BodySlot = manip->value<BodySlot>("BodySlot", {}),
						},
						ImcEntry{
							.MaterialId = entry->value<uint8_t>("MaterialId", {}),
							.DecalId = entry->value<uint8_t>("DecalId", {}),
							.VfxId = entry->value<uint8_t>("VfxId", {}),
							.MaterialAnimationId = entry->value<uint8_t>("MaterialAnimationId", {}),
							.AttributeMask = entry->value<uint16_t>("AttributeMask", {}),
							.SoundId = entry->value<uint8_t>("SoundId", {}),
						});
					break;
				case MetaManipulationType::Eqdp:
					o.Manipulations.Eqdp.insert_or_assign(
						EqdpIdentifier{
							.Gender = manip->value<Gender>("Gender", {}),
							.Race = manip->value<ModelRace>("Race", {}),
							.SetId = manip->value<PrimaryId>("SetId", {}),
							.Slot = manip->value<EquipSlot>("Slot", {}),
						},
						static_cast<EqdpEntry>(entry->get<uint16_t>()));
					break;
				case MetaManipulationType::Eqp:
					o.Manipulations.Eqp.insert_or_assign(
						EqpIdentifier{
							.SetId = manip->value<PrimaryId>("SetId", {}),
							.Slot = manip->value<EquipSlot>("Slot", {}),
						},
						static_cast<EqpEntry>(entry->get<uint64_t>()));
					break;
				case MetaManipulationType::Est:
					o.Manipulations.Est.insert_or_assign(
						EstIdentifier{
							.Gender = manip->value<Gender>("Gender", {}),
							.Race = manip->value<ModelRace>("Race", {}),
							.SetId = manip->value<PrimaryId>("SetId", {}),
							.Slot = manip->value<EstType>("Slot", {}),
						},
						entry->get<uint16_t>());
					break;
				case MetaManipulationType::Gmp:
					o.Manipulations.Gmp.insert_or_assign(
						GmpIdentifier{
							.SetId = manip->value<PrimaryId>("SetId", {}),
						},
						GmpEntry{
							.Enabled = manip->value<bool>("Enabled", {}),
							.Animated = manip->value<bool>("Animated", {}),
							.RotationA = manip->value<uint16_t>("RotationA", {}),
							.RotationB = manip->value<uint16_t>("RotationB", {}),
							.RotationC = manip->value<uint16_t>("RotationC", {}),
							.UnknownA = manip->value<uint8_t>("UnknownA", {}),
							.UnknownB = manip->value<uint8_t>("UnknownB", {}),
						});
					break;
				case MetaManipulationType::Rsp:
					o.Manipulations.Rsp.insert_or_assign(
						RspIdentifier{
							.SubRace = manip->value<SubRace>("SubRace", {}),
							.Attribute = manip->value<RspAttribute>("Attribute", {}),
						},
						entry->get<float>());
					break;
				case MetaManipulationType::GlobalEqp:
					o.Manipulations.GlobalEqp.insert(GlobalEqpManipulation{
						.Type = manip->value<GlobalEqpType>("Type", {}),
						.Condition = manip->value<PrimaryId>("Condition", {}),
						});
					break;
			}
		}
	}
}

void penumbra::from_json(const nlohmann::json& j, Group& o) {
	o = {
		.Version = j.value<int>("Version", {}),
		.Name = j.value<std::optional<std::string>>("Name", {}),
		.Description = j.value<std::optional<std::string>>("Description", {}),
		.Image = j.value<std::optional<std::string>>("Image", {}),
		.Priority = j.value<int>("Priority", {}),
		.DefaultSettings = j.value<uint64_t>("DefaultSettings", {}),
		.Type = j.value<GroupType>("Type", {}),
		.Options = j.value<std::vector<GroupOption>>("Options", {}),
	};
}

void penumbra::from_json(const nlohmann::json& j, Meta& o) {
	o = {
		.FileVersion = j.value<int>("FileVersion", {}),
		.Name = j.value<std::string>("Name", {}),
		.Author = j.value<std::string>("Author", {}),
		.Description = j.value<std::string>("Description", {}),
		.Version = j.value<std::string>("Version", {}),
		.Website = j.value<std::string>("Website", {}),
		.Image = j.value<std::string>("Image", {}),
		.ModTags = j.value<std::vector<std::string>>("ModTags", {}),
	};
}

bool penumbra::IsAccessory(EquipSlot value) {
	switch (value) {
		case EquipSlot::Ears:
		case EquipSlot::Neck:
		case EquipSlot::RFinger:
		case EquipSlot::LFinger:
		case EquipSlot::Wrists:
			return true;
		default:
			return false;
	}
}

std::string penumbra::ToSuffix(EquipSlot value) {
	switch (value) {
		case EquipSlot::Head: return "met";
		case EquipSlot::Hands: return "glv";
		case EquipSlot::Legs: return "dwn";
		case EquipSlot::Feet: return "sho";
		case EquipSlot::Body: return "top";
		case EquipSlot::Ears: return "ear";
		case EquipSlot::Neck: return "nek";
		case EquipSlot::RFinger: return "rir";
		case EquipSlot::LFinger: return "ril";
		case EquipSlot::Wrists: return "wrs";
		default: return "unk";
	}
}

std::string penumbra::ToSuffix(BodySlot value) {
	switch (value) {
		case BodySlot::Ear: return "zear";
		case BodySlot::Face: return "face";
		case BodySlot::Hair: return "hair";
		case BodySlot::Body: return "body";
		case BodySlot::Tail: return "tail";
		default: throw std::invalid_argument("invalid slot");
	}
}

penumbra::GenderRace penumbra::CombinedRace(Gender gender, ModelRace modelRace) {
	switch (gender) {
		case Gender::Male:
			switch (modelRace) {
				case ModelRace::Midlander: return GenderRace::MidlanderMale;
				case ModelRace::Highlander: return GenderRace::HighlanderMale;
				case ModelRace::Elezen: return GenderRace::ElezenMale;
				case ModelRace::Lalafell: return GenderRace::LalafellMale;
				case ModelRace::Miqote: return GenderRace::MiqoteMale;
				case ModelRace::Roegadyn: return GenderRace::RoegadynMale;
				case ModelRace::AuRa: return GenderRace::AuRaMale;
				case ModelRace::Hrothgar: return GenderRace::HrothgarMale;
				case ModelRace::Viera: return GenderRace::VieraMale;
				default: return GenderRace::Unknown;
			}
		case Gender::MaleNpc:
			switch (modelRace) {
				case ModelRace::Midlander: return GenderRace::MidlanderMaleNpc;
				case ModelRace::Highlander: return GenderRace::HighlanderMaleNpc;
				case ModelRace::Elezen: return GenderRace::ElezenMaleNpc;
				case ModelRace::Lalafell: return GenderRace::LalafellMaleNpc;
				case ModelRace::Miqote: return GenderRace::MiqoteMaleNpc;
				case ModelRace::Roegadyn: return GenderRace::RoegadynMaleNpc;
				case ModelRace::AuRa: return GenderRace::AuRaMaleNpc;
				case ModelRace::Hrothgar: return GenderRace::HrothgarMaleNpc;
				case ModelRace::Viera: return GenderRace::VieraMaleNpc;
				default: return GenderRace::Unknown;
			}
		case Gender::Female:
			switch (modelRace) {
				case ModelRace::Midlander: return GenderRace::MidlanderFemale;
				case ModelRace::Highlander: return GenderRace::HighlanderFemale;
				case ModelRace::Elezen: return GenderRace::ElezenFemale;
				case ModelRace::Lalafell: return GenderRace::LalafellFemale;
				case ModelRace::Miqote: return GenderRace::MiqoteFemale;
				case ModelRace::Roegadyn: return GenderRace::RoegadynFemale;
				case ModelRace::AuRa: return GenderRace::AuRaFemale;
				case ModelRace::Hrothgar: return GenderRace::HrothgarFemale;
				case ModelRace::Viera: return GenderRace::VieraFemale;
				default: return GenderRace::Unknown;
			}
		case Gender::FemaleNpc:
			switch (modelRace) {
				case ModelRace::Midlander: return GenderRace::MidlanderFemaleNpc;
				case ModelRace::Highlander: return GenderRace::HighlanderFemaleNpc;
				case ModelRace::Elezen: return GenderRace::ElezenFemaleNpc;
				case ModelRace::Lalafell: return GenderRace::LalafellFemaleNpc;
				case ModelRace::Miqote: return GenderRace::MiqoteFemaleNpc;
				case ModelRace::Roegadyn: return GenderRace::RoegadynFemaleNpc;
				case ModelRace::AuRa: return GenderRace::AuRaFemaleNpc;
				case ModelRace::Hrothgar: return GenderRace::HrothgarFemaleNpc;
				case ModelRace::Viera: return GenderRace::VieraFemaleNpc;
				default: return GenderRace::Unknown;
			}
		default: return GenderRace::Unknown;
	}
}

std::string penumbra::ManipToPath(ImcIdentifier manip) {
	const auto path = manip.GamePath();
	switch (manip.ObjectType) {
		case ObjectType::Accessory:
		case ObjectType::Equipment:
			return path.substr(0, path.size() - 4) + "_" + ToSuffix(manip.EquipSlot) + ".meta";
		case ObjectType::Character:
			return path.substr(0, path.size() - 4) + "_" + ToSuffix(manip.BodySlot) + ".meta";
		default:
			return path.substr(0, path.size() - 4) + ".meta";
	}
}

std::string penumbra::ManipToPath(EqdpIdentifier manip) {
	return IsAccessory(manip.Slot)
		? std::format("chara/accessory/a{:04}/a{:04}_{}.meta", manip.SetId, manip.SetId, ToSuffix(manip.Slot))
		: std::format("chara/equipment/e{:04}/e{:04}_{}.meta", manip.SetId, manip.SetId, ToSuffix(manip.Slot));
}

std::string penumbra::ManipToPath(EqpIdentifier manip) {
	return IsAccessory(manip.Slot)
		? std::format("chara/accessory/a{:04}/a{:04}_{}.meta", manip.SetId, manip.SetId, ToSuffix(manip.Slot))
		: std::format("chara/equipment/e{:04}/e{:04}_{}.meta", manip.SetId, manip.SetId, ToSuffix(manip.Slot));
}

std::string penumbra::ManipToPath(EstIdentifier manip) {
	const auto raceCode = std::format("{:04}", static_cast<int>(CombinedRace(manip.Gender, manip.Race)));
	switch (manip.Slot) {
		case EstType::Hair:
			return std::format("chara/human/c{}/obj/hair/h{:04}/c{}h{:04}_hir.meta", raceCode, manip.SetId, raceCode, manip.SetId);
		case EstType::Face:
			return std::format("chara/human/c{}/obj/hair/h{:04}/c{}h{:04}_fac.meta", raceCode, manip.SetId, raceCode, manip.SetId);
		case EstType::Body:
			return std::format("chara/equipment/e{:04}/e{:04}_{}.meta", manip.SetId, manip.SetId, ToSuffix(EquipSlot::Body));
		case EstType::Head:
			return std::format("chara/equipment/e{:04}/e{:04}_{}.meta", manip.SetId, manip.SetId, ToSuffix(EquipSlot::Head));
		default:
			return "";
	};
}

std::string penumbra::ManipToPath(GmpIdentifier manip) {
	return std::format("chara/equipment/e{:04}/e{:04}_{}.meta", manip.SetId, manip.SetId, ToSuffix(EquipSlot::Head));
}
