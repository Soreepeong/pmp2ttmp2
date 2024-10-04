#include "pch.h"

#include "PenumbraEnums.h"

DEFINE_ENUM_FLAG_OPERATORS(penumbra::EqdpEntry);

HINSTANCE g_hInstance;

int wmain(int argc, wchar_t** argv) {
	std::system("cls");

	if (argc < 2) {
		fwprintf(stderr, L"Usage: %s file_name1 [file_name2] [file_name3] ...\n", argv[0]);
		return -1;
	}

	// https://github.com/tzutalin/minizip/blob/master/src/miniunz.c
	zlib_filefunc64_def zffunc;
#ifdef _WIN32
	fill_win32_filefunc64W(&zffunc);
#else
	fill_fopen64_filefunc(&zffunc);
#endif

	for (int argi = 1; argi < argc; argi++) {
		const auto argpath = std::filesystem::path(argv[argi]);
		if (argpath.extension() != ".pmp") {
			fwprintf(stderr, L"Ignoring: %s\n", argv[argi]);
			continue;
		}

		wprintf(L"Working on: %s\n", argpath.c_str());

		const auto zf = unzOpen2_64(argpath.c_str(), &zffunc);
		if (!zf) {
			fprintf(stderr, "unzOpen2_64: failed to open file\n");
			return -1;
		}

		unz_global_info64 gi;
		if (const auto unzerr = unzGetGlobalInfo64(zf, &gi); unzerr != UNZ_OK) {
			fprintf(stderr, "unzGetGlobalInfo64: failed with %d\n", unzerr);
			return -1;
		}

		std::vector<penumbra::Group> groups;
		std::map<std::string, xivres::textools::mods_json> modsJsons;
		penumbra::Meta meta;

		auto ttmpWriter = xivres::textools::simple_ttmp2_writer(std::filesystem::path(argpath).replace_extension(".ttmp2"));
		ttmpWriter.begin_packed(0);

		std::string namebuf;
		std::vector<char> databuf;
		for (decltype(gi.number_entry) i = 0; i < gi.number_entry; i++) {
			if (i != 0) {
				if (const auto unzerr = unzGoToNextFile(zf); unzerr != UNZ_OK) {
					fprintf(stderr, "unzGoToNextFile: failed with %d\n", unzerr);
					return -1;
				}
			}

			unz_file_info64 fi;
			if (const auto unzerr = unzGetCurrentFileInfo64(zf, &fi, nullptr, 0, nullptr, 0, nullptr, 0); unzerr != UNZ_OK) {
				fprintf(stderr, "unzGetCurrentFileInfo64: failed with %d\n", unzerr);
				return -1;
			}

			namebuf.clear();
			namebuf.reserve(fi.size_filename + 1);
			namebuf.resize(fi.size_filename);
			if (const auto unzerr = unzGetCurrentFileInfo64(zf, &fi, namebuf.data(), fi.size_filename + 1, nullptr, 0, nullptr, 0); unzerr != UNZ_OK) {
				fprintf(stderr, "unzGetCurrentFileInfo64: failed with %d\n", unzerr);
				return -1;
			}

			printf("\tWorking on: %s\n", namebuf.c_str());

			databuf.clear();
			databuf.resize(fi.uncompressed_size);
			if (const auto unzerr = unzOpenCurrentFile(zf); unzerr != UNZ_OK) {
				fprintf(stderr, "unzOpenCurrentFile: failed with %d\n", unzerr);
				return -1;
			}
			for (size_t i = 0; i < fi.uncompressed_size;) {
				if (const auto unzerr = unzReadCurrentFile(zf, &databuf[i], static_cast<int>(std::min<size_t>(65536, fi.uncompressed_size - i))); unzerr < 0) {
					fprintf(stderr, "unzReadCurrentFile: failed with %d\n", unzerr);
					return -1;
				} else if (unzerr == 0) {
					fprintf(stderr, "unzReadCurrentFile: failed to fully read the current file.\n");
					return -1;
				} else {
					i += unzerr;
				}
			}
			if (const auto unzerr = unzCloseCurrentFile(zf); unzerr != UNZ_OK) {
				fprintf(stderr, "unzCloseCurrentFile: failed with %d\n", unzerr);
				return -1;
			}

			if (namebuf == "default_mod.json") {
				if (groups.empty())
					groups.push_back({});
				from_json(nlohmann::json::parse(databuf.cbegin(), databuf.cend()), groups[0]);
				continue;
			} else if (namebuf.starts_with("group_") && namebuf.ends_with(".json")) {
				const auto groupIndex = static_cast<size_t>(std::strtoull(&namebuf[6], nullptr, 10));
				if (groups.size() <= groupIndex)
					groups.resize(groupIndex + 1);
				from_json(nlohmann::json::parse(databuf.cbegin(), databuf.cend()), groups[groupIndex]);
				for (auto& option : groups[groupIndex].Options) {
					for (auto& kv : option.Files) {
						for (auto& c : kv.second)
							c = c == '\\' ? '/' : c;
					}
				}
				continue;
			} else if (namebuf == "meta.json") {
				from_json(nlohmann::json::parse(databuf.cbegin(), databuf.cend()), meta);
				continue;
			}

			for (const auto& group : groups) {
				for (const auto& option : group.Options) {
					for (const auto& kv : option.Files) {
						if (kv.second == namebuf)
							goto found;
					}
				}
			}

			continue;
		found:

			if (namebuf.ends_with(".mdl")) {
				ttmpWriter.add_packed(xivres::compressing_packed_stream<xivres::model_compressing_packer>("dummy/dummy", std::make_shared<xivres::memory_stream>(std::span(databuf.begin(), databuf.size())), Z_BEST_COMPRESSION, true));
			} else if (namebuf.ends_with(".tex")) {
				if (databuf.size() >= 80) {
					auto& texHeader = *reinterpret_cast<xivres::texture::header*>(databuf.data());
					const auto mipOffsets = std::span(reinterpret_cast<uint32_t*>(&databuf[sizeof(xivres::texture::header)]), 13);
					for (auto i = 1; i < texHeader.MipmapCount; i++) {
						if (mipOffsets[i] >= databuf.size()) {
							printf("\t\tFixing invalid mipmap offsets: %d to %d\n", *texHeader.MipmapCount, i);
							texHeader.MipmapCount = i;
							for (; i < 13; i++)
								mipOffsets[i] = mipOffsets[i - 1];
							break;
						}
					}

					texHeader.LodOffsets[0] = std::min<uint32_t>(texHeader.MipmapCount - 1, texHeader.LodOffsets[0]);
					texHeader.LodOffsets[1] = std::min<uint32_t>(texHeader.MipmapCount - 1, std::max<uint32_t>(texHeader.LodOffsets[0], texHeader.LodOffsets[1]));
					texHeader.LodOffsets[2] = std::min<uint32_t>(texHeader.MipmapCount - 1, std::max<uint32_t>(texHeader.LodOffsets[1], texHeader.LodOffsets[2]));
				}
				ttmpWriter.add_packed(xivres::compressing_packed_stream<xivres::texture_compressing_packer>("dummy/dummy", std::make_shared<xivres::memory_stream>(std::span(databuf.begin(), databuf.size())), Z_BEST_COMPRESSION, true));
			} else {
				ttmpWriter.add_packed(xivres::compressing_packed_stream<xivres::standard_compressing_packer>("dummy/dummy", std::make_shared<xivres::memory_stream>(std::span(databuf.begin(), databuf.size())), Z_BEST_COMPRESSION, true));
			}
			modsJsons.insert_or_assign(namebuf, ttmpWriter.ttmpl().SimpleModsList.back());
			ttmpWriter.ttmpl().SimpleModsList.pop_back();
		}

		unzClose(zf);

		auto& ttmpl = ttmpWriter.ttmpl();
		ttmpl = {
			.TTMPVersion = "1.3w",
			.Name = meta.Name,
			.Author = meta.Author,
			.Version = meta.Version,
			.Description = meta.Description,
			.Url = meta.Website,
			.MinimumFrameworkVersion = "1.3.0.0",
		};
		for (const auto& group : groups) {
			switch (group.Type) {
				case penumbra::GroupType::Single:
				case penumbra::GroupType::Multi: {
					auto& page = ttmpl.ModPackPages.emplace_back();
					page = {
						.PageIndex = static_cast<int>(ttmpl.ModPackPages.size()),
						.ModGroups = {
							{
								.GroupName = group.Name.value_or("Untitled"),
								.SelectionType = group.Type == penumbra::GroupType::Single ? "Single" : "Multi",
							},
						},
					};
					for (const auto& option : group.Options) {
						const auto optionIndex = static_cast<int>(page.ModGroups[0].OptionList.size());
						auto& option2 = page.ModGroups[0].OptionList.emplace_back();
						option2 = {
							.Name = option.Name.value_or("Untitled"),
							.Description = option.Description.value_or(""),
							.GroupName = page.ModGroups[0].GroupName,
							.SelectionType = page.ModGroups[0].SelectionType,
							.IsChecked = !!(group.DefaultSettings & (1ULL << optionIndex)),
						};
						for (const auto& file : option.Files) {
							auto& file2 = option2.ModsJsons.emplace_back();
							const auto& src = modsJsons.at(file.second);
							file2 = {
								.Name = file.first,
								.Category = src.Category,
								.FullPath = xivres::util::unicode::convert<std::string>(file.first, &xivres::util::unicode::lower),
								.ModOffset = src.ModOffset,
								.ModSize = src.ModSize,
								.DatFile = xivres::path_spec(file.first).packname(),
								.IsDefault = src.IsDefault,
							};
						}

						std::map<std::string, penumbra::MetaDictionary> metas;

						for (const auto& [k, v] : option.Manipulations.Imc)
							metas[penumbra::ManipToPath(k)].Imc.insert_or_assign(k, v);
						for (const auto& [k, v] : option.Manipulations.Eqp)
							metas[penumbra::ManipToPath(k)].Eqp.insert_or_assign(k, v);
						for (const auto& [k, v] : option.Manipulations.Eqdp)
							metas[penumbra::ManipToPath(k)].Eqdp.insert_or_assign(k, v);
						for (const auto& [k, v] : option.Manipulations.Est)
							metas[penumbra::ManipToPath(k)].Est.insert_or_assign(k, v);
						for (const auto& [k, v] : option.Manipulations.Gmp)
							metas[penumbra::ManipToPath(k)].Gmp.insert_or_assign(k, v);
						metas.erase("");

						std::vector<uint8_t> metabuf;
						for (const auto& [k, v] : metas) {
							const auto metaHeaderSize =
								(v.Imc.empty() ? 0 : 1) +
								(v.Eqp.empty() ? 0 : 1) +
								(v.Eqdp.empty() ? 0 : 1) +
								(v.Est.empty() ? 0 : 1) +
								(v.Gmp.empty() ? 0 : 1);
							if (metaHeaderSize == 0)
								continue;

							const auto metaCount =
								v.Imc.size() +
								v.Eqp.size() +
								v.Eqdp.size() +
								v.Est.size() +
								v.Gmp.size();

							size_t eqpSize = 0;
							for (const auto& [k2, v2] : v.Eqp) {
								switch (k2.Slot) {
									case penumbra::EquipSlot::Body:
										eqpSize += 2;
										break;
									case penumbra::EquipSlot::Legs:
									case penumbra::EquipSlot::Hands:
									case penumbra::EquipSlot::Feet:
										eqpSize += 1;
										break;
									case penumbra::EquipSlot::Head:
										eqpSize += 3;
										break;
								}
							}

							metabuf.clear();
							metabuf.resize(
								size_t{}

								// version
								+ 4

								// zero-terminated path
								+ k.size() + 1

								// header
								+ 12

								// offset to entry locators
								+ 4

								// entry locators
								+ (12 * metaCount)

								+ (sizeof(xivres::image_change_data::entry) * v.Imc.size())
								+ (sizeof(xivres::textools::metafile::equipment_deformer_parameter_entry) * v.Eqdp.size())
								+ eqpSize
								+ (sizeof(xivres::textools::metafile::ex_skeleton_table_entry_t) * v.Est.size())
								+ (sizeof(xivres::textools::metafile::equipment_and_gimmick_parameter_entry) * v.Gmp.size())
							);

							size_t ptr = 0;
							*reinterpret_cast<int*>(&metabuf[ptr]) = xivres::textools::metafile::Version_Value;
							ptr += 4;

							memcpy(&metabuf[ptr], k.c_str(), k.size());
							metabuf[ptr + k.size()] = 0;
							ptr += k.size() + 1;

							*reinterpret_cast<int*>(&metabuf[ptr]) = metaHeaderSize;
							ptr += 4;

							*reinterpret_cast<int*>(&metabuf[ptr]) = 12;
							ptr += 4;

							*reinterpret_cast<int*>(&metabuf[ptr]) = static_cast<int>(ptr + 4);
							ptr += 4;

							auto locatorPtr = reinterpret_cast<xivres::textools::metafile::entry_locator*>(metabuf.data() + ptr);
							auto dataPtr = metabuf.data() + ptr + metaCount * 12;
							if (!v.Imc.empty()) {
								locatorPtr->Type = xivres::textools::metafile::meta_types::Imc;
								locatorPtr->Offset = static_cast<uint32_t>(dataPtr - metabuf.data());
								for (const auto& [k2, v2] : v.Imc) {
									*reinterpret_cast<xivres::image_change_data::entry*>(dataPtr) = {
										.MaterialId = v2.MaterialId,
										.DecalId = v2.DecalId,
										.AttributeAndSound = static_cast<uint16_t>(v2.AttributeMask | (static_cast<uint16_t>(v2.SoundId) << 10)),
										.VfxId = v2.VfxId,
										.MaterialAnimationId = v2.MaterialAnimationId,
									};
									dataPtr += sizeof(xivres::image_change_data::entry);
								}
							}

							if (!v.Eqdp.empty()) {
								locatorPtr->Type = xivres::textools::metafile::meta_types::Eqdp;
								locatorPtr->Offset = static_cast<uint32_t>(dataPtr - metabuf.data());
								for (const auto& [k2, v2] : v.Eqdp) {
									bool b1, b2;
									switch (k2.Slot) {
										case penumbra::EquipSlot::Head:
											b1 = penumbra::EqdpEntry::Invalid != (v2 & penumbra::EqdpEntry::Head1);
											b2 = penumbra::EqdpEntry::Invalid != (v2 & penumbra::EqdpEntry::Head2);
											break;
										case penumbra::EquipSlot::Body:
											b1 = penumbra::EqdpEntry::Invalid != (v2 & penumbra::EqdpEntry::Body1);
											b2 = penumbra::EqdpEntry::Invalid != (v2 & penumbra::EqdpEntry::Body2);
											break;
										case penumbra::EquipSlot::Hands:
											b1 = penumbra::EqdpEntry::Invalid != (v2 & penumbra::EqdpEntry::Hands1);
											b2 = penumbra::EqdpEntry::Invalid != (v2 & penumbra::EqdpEntry::Hands2);
											break;
										case penumbra::EquipSlot::Legs:
											b1 = penumbra::EqdpEntry::Invalid != (v2 & penumbra::EqdpEntry::Legs1);
											b2 = penumbra::EqdpEntry::Invalid != (v2 & penumbra::EqdpEntry::Legs2);
											break;
										case penumbra::EquipSlot::Feet:
											b1 = penumbra::EqdpEntry::Invalid != (v2 & penumbra::EqdpEntry::Feet1);
											b2 = penumbra::EqdpEntry::Invalid != (v2 & penumbra::EqdpEntry::Feet2);
											break;
										case penumbra::EquipSlot::Ears:
											b1 = penumbra::EqdpEntry::Invalid != (v2 & penumbra::EqdpEntry::Ears1);
											b2 = penumbra::EqdpEntry::Invalid != (v2 & penumbra::EqdpEntry::Ears2);
											break;
										case penumbra::EquipSlot::Neck:
											b1 = penumbra::EqdpEntry::Invalid != (v2 & penumbra::EqdpEntry::Neck1);
											b2 = penumbra::EqdpEntry::Invalid != (v2 & penumbra::EqdpEntry::Neck2);
											break;
										case penumbra::EquipSlot::Wrists:
											b1 = penumbra::EqdpEntry::Invalid != (v2 & penumbra::EqdpEntry::Wrists1);
											b2 = penumbra::EqdpEntry::Invalid != (v2 & penumbra::EqdpEntry::Wrists2);
											break;
										case penumbra::EquipSlot::RFinger:
											b1 = penumbra::EqdpEntry::Invalid != (v2 & penumbra::EqdpEntry::RingR1);
											b2 = penumbra::EqdpEntry::Invalid != (v2 & penumbra::EqdpEntry::RingR2);
											break;
										case penumbra::EquipSlot::LFinger:
											b1 = penumbra::EqdpEntry::Invalid != (v2 & penumbra::EqdpEntry::RingL1);
											b2 = penumbra::EqdpEntry::Invalid != (v2 & penumbra::EqdpEntry::RingL2);
											break;
										default:
											throw std::invalid_argument("?");
									}
									*reinterpret_cast<xivres::textools::metafile::equipment_deformer_parameter_entry*>(dataPtr) = {
										.RaceCode = static_cast<uint16_t>(penumbra::CombinedRace(k2.Gender, k2.Race)),
										.Value = static_cast<uint8_t>(b1 ? b2 ? 3 : 1 : b2 ? 2 : 0),
									};
									dataPtr += sizeof(xivres::textools::metafile::equipment_deformer_parameter_entry);
								}
							}

							if (!v.Eqp.empty()) {
								locatorPtr->Type = xivres::textools::metafile::meta_types::Eqp;
								locatorPtr->Offset = static_cast<uint32_t>(dataPtr - metabuf.data());
								for (const auto& [k2, v2] : v.Eqp) {
									switch (k2.Slot) {
										case penumbra::EquipSlot::Body:
											for (auto i = 0; i < 2; i++)
												*dataPtr++ = static_cast<uint8_t>(static_cast<uint64_t>(v2) >> (8 * i));
											break;
										case penumbra::EquipSlot::Legs:
										case penumbra::EquipSlot::Hands:
										case penumbra::EquipSlot::Feet:
											*dataPtr++ = static_cast<uint8_t>(v2);
											break;
										case penumbra::EquipSlot::Head:
											for (auto i = 0; i < 3; i++)
												*dataPtr++ = static_cast<uint8_t>(static_cast<uint64_t>(v2) >> (8 * i));
											break;
									}
								}
							}

							if (!v.Est.empty()) {
								locatorPtr->Type = xivres::textools::metafile::meta_types::Est;
								locatorPtr->Offset = static_cast<uint32_t>(dataPtr - metabuf.data());
								for (const auto& [k2, v2] : v.Est) {
									*reinterpret_cast<xivres::textools::metafile::ex_skeleton_table_entry_t*>(dataPtr) = {
										.RaceCode = static_cast<uint16_t>(penumbra::CombinedRace(k2.Gender, k2.Race)),
										.SetId = k2.SetId,
										.SkelId = v2,
									};
									dataPtr += sizeof(xivres::textools::metafile::ex_skeleton_table_entry_t);
								}
							}

							if (!v.Gmp.empty()) {
								locatorPtr->Type = xivres::textools::metafile::meta_types::Gmp;
								locatorPtr->Offset = static_cast<uint32_t>(dataPtr - metabuf.data());
								for (const auto& [k2, v2] : v.Gmp) {
									*reinterpret_cast<xivres::textools::metafile::equipment_and_gimmick_parameter_entry*>(dataPtr) = {
										.Enabled = v2.Enabled ? 1u : 0u,
										.Animated = v2.Animated ? 1u : 0u,
										.RotationA = v2.RotationA,
										.RotationB = v2.RotationB,
										.RotationC = v2.RotationC,
										.UnknownA = v2.UnknownA,
										.UnknownB = v2.UnknownB,
									};
									dataPtr += sizeof(xivres::textools::metafile::equipment_and_gimmick_parameter_entry);
								}
							}

							ttmpWriter.add_packed(xivres::compressing_packed_stream<xivres::standard_compressing_packer>("dummy/dummy", std::make_shared<xivres::memory_stream>(std::span(metabuf.begin(), metabuf.end())), Z_BEST_COMPRESSION, true));
							auto& file2 = option2.ModsJsons.emplace_back();
							const auto& src = ttmpWriter.ttmpl().SimpleModsList.back();
							file2 = {
								.Name = k,
								.Category = src.Category,
								.FullPath = xivres::util::unicode::convert<std::string>(k, &xivres::util::unicode::lower),
								.ModOffset = src.ModOffset,
								.ModSize = src.ModSize,
								.DatFile = xivres::path_spec(k).packname(),
								.IsDefault = src.IsDefault,
							};
							ttmpWriter.ttmpl().SimpleModsList.pop_back();
						}

					}
					break;
				}
			}
		}

		ttmpWriter.end_packed();
		ttmpWriter.close();
	}
	return 0;
}